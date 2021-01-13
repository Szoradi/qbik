#include "BdJpeg.h"

void JPGToRGB (s16 y0, s16 cb0, s16 cr0, s16 *r0, s16 *g0, s16 *b0);
s16 JPGReceiveBits (u16 cat);

// values for Zig-zag reordering

const u8 JPGZig1 [64] = {
   0,0,1,2,1,0,0,1,2,3,4,3,2,1,0,0,1,2,3,4,5,6,5,4,3,2,1,0,0,1,2,3,
   4,5,6,7,7,6,5,4,3,2,1,2,3,4,5,6,7,7,6,5,4,3,4,5,6,7,7,6,5,6,7,7
   };

const u8 JPGZig2 [64] = {
   0,1,0,0,1,2,3,2,1,0,0,1,2,3,4,5,4,3,2,1,0,0,1,2,3,4,5,6,7,6,5,4,
   3,2,1,0,1,2,3,4,5,6,7,7,6,5,4,3,2,3,4,5,6,7,7,6,5,4,5,6,7,7,6,7
   };

const u16 aanscales[64] = {
   /* precomputed values scaled up by 14 bits */
   16384, 22725, 21407, 19266, 16384, 12873,  8867,  4520,
   22725, 31521, 29692, 26722, 22725, 17855, 12299,  6270,
   21407, 29692, 27969, 25172, 21407, 16819, 11585,  5906,
   19266, 26722, 25172, 22654, 19266, 15137, 10426,  5315,
   16384, 22725, 21407, 19266, 16384, 12873,  8867,  4520,
   12873, 17855, 16819, 15137, 12873, 10114,  6967,  3552,
    8867, 12299, 11585, 10426,  8867,  6967,  4799,  2446,
    4520,  6270,  5906,  5315,  4520,  3552,  2446,  1247
   };

#define FIX_1_082392200  277     /* FIX(1.082392200) */
#define FIX_1_414213562  362     /* FIX(1.414213562) */
#define FIX_1_847759065  473     /* FIX(1.847759065) */
#define FIX_2_613125930  669     /* FIX(2.613125930) */

#define RGB(r,g,b) ((((b)>>3)<<10)+(((g)>>3)<<5)+((r)>>3))

struct JpegType {                      // some type definitions (for coherence)
   u16 Rows;                           // image height
   u16 Cols;                           // image width
   u16 SamplesY;                       // sampling ratios
   u16 SamplesCbCr;
   u16 QuantTableY;                    // quantization table numbers
   u16 QuantTableCbCr;
   u16 HuffDCTableY;                   // huffman table numbers
   u16 HuffDCTableCbCr;
   u16 HuffACTableY;
   u16 HuffACTableCbCr;
   u16 NumComp;                        // number of components
   };

struct JPGHuffmanEntry {                   // a type for huffman tables
   u16 Index;
   s16 Code;
   u16 Length;
   }__attribute__ ((packed));

u8 *src = NULL;

u16 DCTables;
u16 ACTables;
u16 QTables;
u8 curByte;
u8 curBits;
u8 EOI;
struct JPGHuffmanEntry HuffmanDC0[256];
struct JPGHuffmanEntry HuffmanDC1[256];
struct JPGHuffmanEntry HuffmanAC0[256];
struct JPGHuffmanEntry HuffmanAC1[256];
//u16 ZigIndex;
u16 QuantTable[2][8][8];    // 2 quantization tables (Y, CbCr)
struct JpegType Image;
//u16 flen;
//s16 i;

void gfxPixel (u8 x, u8 y, u16 rgb, u32 *vram)
{
   vram[240*y+x] = rgb;
}

u32 JPGpower2 (u16 pwr)
   {
   u8 i;
   u16 total = 1;

   for (i=0; i<pwr; i++)
      total <<= 1;
   return (total);
   }

u8 JPGGetByte ()
   {
   return *src++;
   }

u8 JPGGetWord ()
   {
   u16 i = JPGGetByte() << 8;
   i += JPGGetByte();
   return (i);
   }

u8 JPGNextBit ()
   {
   u8 NextBit;

   curBits >>= 1;
   NextBit = (curByte >> 7) & 1;
   curByte <<= 1;
   if (curBits == 0)
      {
      curBits = 128;
      curByte = JPGGetByte();
      if (curByte == 255)
         if (JPGGetByte() == 0xD9)
            {
            EOI = 1;
            return(0);
            }
      }
   return(NextBit);
   }

s16 JPGDecode(struct JPGHuffmanEntry inArray[256])
   {
   u16 n1; u16 n2; u16 i; u16 l;
   s32 CurVal;
   s16 MatchFound;

   if (JPGGetByte() == 255)
      {
      n1 = JPGGetByte();
      src -= 2;
      if ((n1 >= 0xd0) && (n1 <= 0xd7))
         {
         n2 = curBits - 1;
         if ((curByte & n2) == n2)     // if the remaining bits are 1
            {
            EOI = 1;
            return(0);
            }
         }
      }
   else
      src--;

   CurVal = 0;
   MatchFound = -1;
   for (l=1; l<16+1; l++)    // cycle through 16 possible Huffman lengths
      {
      CurVal = (CurVal << 1) + JPGNextBit();
      if (EOI) return(0);
      for (i=0; i<256; i++)              // look for a match in the Huffman table
         {
         if (inArray[i].Length > l) break;
         if (inArray[i].Length == l)
            if (inArray[i].Index == CurVal)
               {
               MatchFound = i;
               break;
               }
         }

      if (MatchFound > -1) break;
      }

   if (MatchFound == -1)
      return(-1);

   return(inArray[MatchFound].Code);  // return the appropriate code
   }

void jpeg_idct_ifast (s16 inarray[8][8], s16 outarray[8][8], u16 QuantNum)
  {
  // The following variables only need 16bits precision
  // but the resulting code is smaller if you use s32.
  s32 tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
  s32 tmp10, tmp11, tmp12, tmp13;
  s32 z5, z10, z11, z12, z13;

  u32 ctr;
  s16 warray[8][8];

  /* Pass 1: process columns from input, store into work array. */

  for (ctr = 0; ctr < 8; ctr++)
    {
    /* Due to quantization, we will usually find that many of the input
     * coefficients are zero, especially the AC terms.  We can exploit this
     * by short-circuiting the IDCT calculation for any column in which all
     * the AC terms are zero.  In that case each output is equal to the
     * DC coefficient (with scale factor as needed).
     * With typical images and quantization tables, half or more of the
     * column DCT calculations can be simplified this way.
     */

    if (inarray[1][ctr] == 0 && inarray[2][ctr] == 0 &&
        inarray[3][ctr] == 0 && inarray[4][ctr] == 0 &&
        inarray[5][ctr] == 0 && inarray[6][ctr] == 0 &&
        inarray[7][ctr] == 0)
      {
      /* AC terms all zero */
      s16 dcval = inarray[0][ctr] * QuantTable[QuantNum][0][ctr];

      warray[0][ctr] = dcval;
      warray[1][ctr] = dcval;
      warray[2][ctr] = dcval;
      warray[3][ctr] = dcval;
      warray[4][ctr] = dcval;
      warray[5][ctr] = dcval;
      warray[6][ctr] = dcval;
      warray[7][ctr] = dcval;

      continue;
      }

    /* Even part */

    tmp0 = inarray[0][ctr] * QuantTable[QuantNum][0][ctr];
    tmp1 = inarray[2][ctr] * QuantTable[QuantNum][2][ctr];
    tmp2 = inarray[4][ctr] * QuantTable[QuantNum][4][ctr];
    tmp3 = inarray[6][ctr] * QuantTable[QuantNum][6][ctr];

    tmp10 = tmp0 + tmp2;	/* phase 3 */
    tmp11 = tmp0 - tmp2;

    tmp13 = tmp1 + tmp3;	/* phases 5-3 */
    tmp12 = (((tmp1 - tmp3)*( FIX_1_414213562)) >> 8) - tmp13; /* 2*c4 */

    tmp0 = tmp10 + tmp13;	/* phase 2 */
    tmp3 = tmp10 - tmp13;
    tmp1 = tmp11 + tmp12;
    tmp2 = tmp11 - tmp12;

    /* Odd part */

    tmp4 = inarray[1][ctr] * QuantTable[QuantNum][1][ctr];
    tmp5 = inarray[3][ctr] * QuantTable[QuantNum][3][ctr];
    tmp6 = inarray[5][ctr] * QuantTable[QuantNum][5][ctr];
    tmp7 = inarray[7][ctr] * QuantTable[QuantNum][7][ctr];

    z13 = tmp6 + tmp5;		/* phase 6 */
    z10 = tmp6 - tmp5;
    z11 = tmp4 + tmp7;
    z12 = tmp4 - tmp7;

    tmp7 = z11 + z13;		/* phase 5 */
    tmp11 = ((z11 - z13) * FIX_1_414213562) >> 8; /* 2*c4 */

    z5 = ((z10 + z12) * FIX_1_847759065) >> 8; /* 2*c2 */
    tmp10 = ((z12 * FIX_1_082392200) >> 8) - z5; /* 2*(c2-c6) */
    tmp12 = ((z10 * - FIX_2_613125930) >> 8) + z5; /* -2*(c2+c6) */

    tmp6 = tmp12 - tmp7;	/* phase 2 */
    tmp5 = tmp11 - tmp6;
    tmp4 = tmp10 + tmp5;

    warray[0][ctr] = (tmp0 + tmp7);
    warray[7][ctr] = (tmp0 - tmp7);
    warray[1][ctr] = (tmp1 + tmp6);
    warray[6][ctr] = (tmp1 - tmp6);
    warray[2][ctr] = (tmp2 + tmp5);
    warray[5][ctr] = (tmp2 - tmp5);
    warray[4][ctr] = (tmp3 + tmp4);
    warray[3][ctr] = (tmp3 - tmp4);
    }

  /* Pass 2: process rows from work array, store into output array. */
  /* Note that we must descale the results by a factor of 8 == 2**3, */
  /* and also undo the PASS1_BITS scaling. */

  for (ctr = 0; ctr < 8; ctr++)
    {
    /* Rows of zeroes can be exploited in the same way as we did with columns.
     * However, the column calculation has created many nonzero AC terms, so
     * the simplification applies less often (typically 5% to 10% of the time).
     * On machines with very fast multiplication, it's possible that the
     * test takes more time than it's worth.  In that case this section
     * may be commented out.
     */

    if (warray[ctr][1] == 0 && warray[ctr][2] == 0 && warray[ctr][3] == 0 && warray[ctr][4] == 0 &&
        warray[ctr][5] == 0 && warray[ctr][6] == 0 && warray[ctr][7] == 0)
      {
      /* AC terms all zero */
      s16 dcval = (warray[ctr][0] >> 5)+128;
      if (dcval<0) dcval = 0;
      if (dcval>255) dcval = 255;

      outarray[ctr][0] = dcval;
      outarray[ctr][1] = dcval;
      outarray[ctr][2] = dcval;
      outarray[ctr][3] = dcval;
      outarray[ctr][4] = dcval;
      outarray[ctr][5] = dcval;
      outarray[ctr][6] = dcval;
      outarray[ctr][7] = dcval;
      continue;
      }

    /* Even part */

    tmp10 = warray[ctr][0] + warray[ctr][4];
    tmp11 = warray[ctr][0] - warray[ctr][4];

    tmp13 = warray[ctr][2] + warray[ctr][6];
    tmp12 = (((warray[ctr][2] - warray[ctr][6]) * FIX_1_414213562) >> 8) - tmp13;

    tmp0 = tmp10 + tmp13;
    tmp3 = tmp10 - tmp13;
    tmp1 = tmp11 + tmp12;
    tmp2 = tmp11 - tmp12;

    /* Odd part */

    z13 = warray[ctr][5] + warray[ctr][3];
    z10 = warray[ctr][5] - warray[ctr][3];
    z11 = warray[ctr][1] + warray[ctr][7];
    z12 = warray[ctr][1] - warray[ctr][7];

    tmp7 = z11 + z13;		/* phase 5 */
    tmp11 = ((z11 - z13) * FIX_1_414213562) >> 8; /* 2*c4 */

    z5 = ((z10 + z12) * FIX_1_847759065) >> 8; /* 2*c2 */
    tmp10 = ((z12 * FIX_1_082392200) >> 8) - z5; /* 2*(c2-c6) */
    tmp12 = ((z10 * - FIX_2_613125930) >> 8) + z5; /* -2*(c2+c6) */

    tmp6 = tmp12 - tmp7;	/* phase 2 */
    tmp5 = tmp11 - tmp6;
    tmp4 = tmp10 + tmp5;

    /* Final output stage: scale down by a factor of 8 and range-limit */

    outarray[ctr][0] = ((tmp0 + tmp7) >> 5)+128;
    if ((outarray[ctr][0])<0)  outarray[ctr][0] = 0;
    if ((outarray[ctr][0])>255) outarray[ctr][0] = 255;

    outarray[ctr][7] = ((tmp0 - tmp7) >> 5)+128;
    if ((outarray[ctr][7])<0)  outarray[ctr][7] = 0;
    if ((outarray[ctr][7])>255) outarray[ctr][7] = 255;

    outarray[ctr][1] = ((tmp1 + tmp6) >> 5)+128;
    if ((outarray[ctr][1])<0)  outarray[ctr][1] = 0;
    if ((outarray[ctr][1])>255) outarray[ctr][1] = 255;

    outarray[ctr][6] = ((tmp1 - tmp6) >> 5)+128;
    if ((outarray[ctr][6])<0)  outarray[ctr][6] = 0;
    if ((outarray[ctr][6])>255) outarray[ctr][6] = 255;

    outarray[ctr][2] = ((tmp2 + tmp5) >> 5)+128;
    if ((outarray[ctr][2])<0)  outarray[ctr][2] = 0;
    if ((outarray[ctr][2])>255) outarray[ctr][2] = 255;

    outarray[ctr][5] = ((tmp2 - tmp5) >> 5)+128;
    if ((outarray[ctr][5])<0)  outarray[ctr][5] = 0;
    if ((outarray[ctr][5])>255) outarray[ctr][5] = 255;

    outarray[ctr][4] = ((tmp3 + tmp4) >> 5)+128;
    if ((outarray[ctr][4])<0)  outarray[ctr][4] = 0;
    if ((outarray[ctr][4])>255) outarray[ctr][4] = 255;

    outarray[ctr][3] = ((tmp3 - tmp4) >> 5)+128;
    if ((outarray[ctr][3])<0)  outarray[ctr][3] = 0;
    if ((outarray[ctr][3])>255) outarray[ctr][3] = 255;

    }
  }

void JPGGetBlock (s16 vector[8][8], u16 HuffDCNum, u16 HuffACNum, u16 QuantNum, s16 *dcCoef)
   {
   s16 array2[8][8];
   s32 d; u16 XPos; u16 YPos;
//   u32 Sum;
   u16 bits; u16 zeros; s32 bitVal; u16 ACCount;
   u16 x; u16 y;
//   u16 v; u16 u;
//   s32 temp;
   s16 temp0;
//   u16 Add1 = 0;
   u16 ZigIndex;

   EOI = 0;

   for (x=0; x<8; x++)
      for (y=0; y<8; y++)
         array2[x][y] = 0;

   if (HuffDCNum)
      temp0 = JPGDecode(HuffmanDC1);   // Get the DC coefficient
   else
      temp0 = JPGDecode(HuffmanDC0);   // Get the DC coefficient
//   if (EOI) d = 0;
   *dcCoef = *dcCoef + JPGReceiveBits(temp0);
   array2[0][0] = *dcCoef; //* Quant[QuantNum][0][0];

   XPos = 0; YPos = 0;
   ZigIndex = 1;
   ACCount = 1;
   do
      {
      if (HuffACNum)
         d = JPGDecode(HuffmanAC1);
      else
         d = JPGDecode(HuffmanAC0);
//      if (EOI) d = 0;

      zeros = d >> 4;
      bits = d & 15;
      bitVal = JPGReceiveBits(bits);

      if (bits)
         {
         ZigIndex += zeros;
         ACCount += zeros;
         if (ACCount >= 64) break;

         XPos = JPGZig1[ZigIndex];
         YPos = JPGZig2[ZigIndex];
         ZigIndex++;

         //Read(XPos, YPos);
         array2[XPos][YPos] = bitVal; // * Quant[QuantNum][XPos][YPos];
         ACCount++;
         }
      else
         {
         if (zeros != 15) break;
         ZigIndex += 15;
         ACCount += 16;
         }

      }
   while (ACCount < 64);

//   if (HuffDCNum == Image.HuffDCTableY) Add1 = 128;

   jpeg_idct_ifast (array2, vector, QuantNum);

   }

u16 JPGGetHuffTables (void)
   {
   u16 HuffAmount[17]; //1-16
   u32 l0;
   u16 c0;
   u16 temp0;
   s16 temp1;
   u16 total;
   u16 i;
   u16 t0;
   s32 CurNum;
   u16 CurIndex;
   u16 j;

   l0 = JPGGetWord();
   c0 = 2;
   do
      {
      temp0 = JPGGetByte();
      c0++;
      t0 = (temp0 & 16) >> 4;
      temp0 &= 15;
      switch (t0)
         {
         case 0:        // DC Table
            total = 0;
            for (i=1; i<16+1; i++)
               {
               temp1 = JPGGetByte();
               c0++;
               total += temp1;
               HuffAmount[i] = temp1;
               }
            for (i=0; i<total; i++)
               {
               if (temp0)
                  HuffmanDC1[i].Code = JPGGetByte();
               else
                  HuffmanDC0[i].Code = JPGGetByte();
               c0++;
               }
            CurNum = 0;
            CurIndex = -1;
            for (i=1; i<16+1; i++)
               {
               for (j=1; j<HuffAmount[i]+1; j++)
                  {
                  CurIndex++;
                  if (temp0)
                     {
                     HuffmanDC1[CurIndex].Index = CurNum;
                     HuffmanDC1[CurIndex].Length = i;
                     }
                  else
                     {
                     HuffmanDC0[CurIndex].Index = CurNum;
                     HuffmanDC0[CurIndex].Length = i;
                     }
                  CurNum++;
                  }
               CurNum *= 2;
               }
            DCTables++;
            break;
         case 1:
            total = 0;
            for (i=1; i<16+1; i++)
               {
               temp1 = JPGGetByte();
               c0++;
               total += temp1;
               HuffAmount[i] = temp1;
               }
            for (i=0; i<total; i++)
               {
               if (temp0)
                  HuffmanAC1[i].Code = JPGGetByte();
               else
                  HuffmanAC0[i].Code = JPGGetByte();
               c0++;
               }

            CurNum = 0;
            CurIndex = -1;
            for (i=1; i<16+1; i++)
               {
               for (j=1; j<HuffAmount[i]+1; j++)
                  {
                  CurIndex++;
                  if (temp0)
                     {
                     HuffmanAC1[CurIndex].Index = CurNum;
                     HuffmanAC1[CurIndex].Length = i;
                     }
                  else
                     {
                     HuffmanAC0[CurIndex].Index = CurNum;
                     HuffmanAC0[CurIndex].Length = i;
                     }
                  CurNum++;
                  }
               CurNum *= 2;
               }
            ACTables++;
            break;
         }
      }
   while (c0 < l0);

   return(1);
   }

u16 JPGGetImageAttr (void)
   {
   u32 temp4;
   u16 temp0;
   u16 temp1;
   u16 i;
   u16 id;

   temp4 = JPGGetWord();          //Length of segment
   temp0 = JPGGetByte();          // Data precision
   if (temp0 != 8)
      return(0);                  // we do not support 12 or 16-bit samples
   Image.Rows = JPGGetWord();     // Image Height
   Image.Cols = JPGGetWord();     // Image Width
   temp0 = JPGGetByte();          // Number of components
   for (i=1; i<temp0+1; i++)
      {
      id = JPGGetByte();
      switch (id)
         {
         case 1:
            temp1 = JPGGetByte();
            Image.SamplesY = (temp1 & 15) * (temp1 >> 4);
            Image.QuantTableY = JPGGetByte();
            break;
         case 2:
         case 3:
            temp1 = JPGGetByte();
            Image.SamplesCbCr = (temp1 & 15) * (temp1 >> 4);
            Image.QuantTableCbCr = JPGGetByte();
            break;
         }
      }
   return(1);
   }

u8 JPGGetQuantTables(void)
   {
   u32 l0 = JPGGetWord();
   u16 c0 = 2;
   u16 temp0;
   u16 xp;
   u16 yp;
   u16 i;
   u16 ZigIndex;

   do
      {
      temp0 = JPGGetByte();
      c0++;
      if (temp0 & 0xf0)
         return(0);        //we don't support 16-bit tables

      temp0 &= 15;
      ZigIndex = 0;
      xp = 0;
      yp = 0;
      for (i=0; i<64; i++)
         {
         xp = JPGZig1[ZigIndex];
         yp = JPGZig2[ZigIndex];
         ZigIndex++;
         /* For AA&N IDCT method, multipliers are equal to quantization
          * coefficients scaled by scalefactor[row]*scalefactor[col], where
          *   scalefactor[0] = 1
          *   scalefactor[k] = cos(k*PI/16) * sqrt(2)    for k=1..7
          */
         QuantTable[temp0][xp][yp] = (JPGGetByte() * aanscales[(xp<<3) + yp]) >> 12;
         c0++;
         }
      QTables++;
      }
   while (c0 < l0);

   return(1);
   }

u16 JPGGetSOS (void)
   {
   u32 temp4;
   u16 temp0;
   u16 temp1;
   u16 temp2;
   u16 i;

   temp4 = JPGGetWord();
   temp0 = JPGGetByte();

   if ((temp0 != 1) && (temp0 != 3))
      return(0);
   Image.NumComp = temp0;
   for (i=1; i<temp0+1; i++)
      {
      temp1 = JPGGetByte();
      switch (temp1)
         {
         case 1:
            temp2 = JPGGetByte();
            Image.HuffACTableY = temp2 & 15;
            Image.HuffDCTableY = temp2 >> 4;
            break;
         case 2:
            temp2 = JPGGetByte();
            Image.HuffACTableCbCr = temp2 & 15;
            Image.HuffDCTableCbCr = temp2 >> 4;
            break;
         case 3:
            temp2 = JPGGetByte();
            Image.HuffACTableCbCr = temp2 & 15;
            Image.HuffDCTableCbCr = temp2 >> 4;
            break;
         default:
            return(0);
         }
      }
   src += 3;
   return(1);
   }

u32 gfxJpeg (u8 x0, u8 y0, const u8 *data, u8 *vram)
   {
   u8 exit = 1;
//   u16 u,v;
//   s16 x;
   s16 y;
//   float t;
   u16 Restart = 0;
   u16 XPos; u16 YPos;
   s16 dcY; s16 dcCb; s16 dcCr;
   u16 xindex; u16 yindex;
   u16 mcu;
   s16 YVector1[8][8];              // 4 vectors for Y attribute
   s16 YVector2[8][8];              // (not all may be needed)
   s16 YVector3[8][8];
   s16 YVector4[8][8];
   s16 CbVector[8][8];              // 1 vector for Cb attribute
   s16 CrVector[8][8];              // 1 vector for Cr attribute

   u16 i,j;
   u16 i2; u16 j2;
   s16 cb; s16 cr;
   u16 xj;
   u16 yi;
   s16 r; s16 g; s16 b;

   src = data;

   QTables = 0;     // Initialize some checkpoint variables
   ACTables = 0;
   DCTables = 0;

   if (JPGGetByte() == 0xff)
      {
      if (JPGGetByte() == 0xd8)
         exit = 0;
      }

   // Exit if not a JPEG file
   if (exit)
      return(0);

   while (!exit)
      {
      if (JPGGetByte() == 0xff)
         {
         switch (JPGGetByte())
            {
            case 0x00: //not important
               break;
            case 0xc0: //SOF0
               JPGGetImageAttr();
               break;
            case 0xc1: //SOF1
               JPGGetImageAttr();
               break;
            case 0xc4: //DHT
               if ((ACTables < 2) || (DCTables < 2))
                  JPGGetHuffTables();
               break;
            case 0xc9: //SOF9
               break;
            case 0xd9: //EOI
               exit = 1;
               break;
            case 0xda: //SOS
               JPGGetSOS();
               if ( ((DCTables == 2) &&
                     (ACTables == 2) &&
                     (QTables == 2)) ||
                     (Image.NumComp == 1) )
                  {
                  EOI = 0;
                  exit = 1;        // Go on to secondary control loop
                  }
               break;
            case 0xdb: //DQT
               if (QTables < 2)
                  JPGGetQuantTables();
               break;
            case 0xdd: //DRI
               Restart = JPGGetWord();
               break;
            case 0xe0: //APP0
               (void) JPGGetWord();        // Length of segment
               src += 5;
               (void) JPGGetByte();        // Major revision
               (void) JPGGetByte();        // Minor revision
               (void) JPGGetByte();        // Density definition
               (void) JPGGetByte();        // X density
               (void) JPGGetByte();        // Y density
               (void) JPGGetByte();        // Thumbnail width
               (void) JPGGetByte();        // Thumbnail height
               break;
            case 0xfe: //COM
               break;
            }
         }
      }

   XPos = 0;
   YPos = 0;                            // Initialize active variables
   dcY = 0; dcCb = 0; dcCr = 0;
   xindex = 0; yindex = 0; mcu = 0;
   r = 0; g = 0; b = 0;

   curBits = 128;                // Start with the seventh bit
   curByte = JPGGetByte();       // Of the first byte

   switch (Image.NumComp)        // How many components does the image have?
     {
     case 3:                     // 3 components (Y-Cb-Cr)
       {
       switch (Image.SamplesY)   // What's the sampling ratio of Y to CbCr?
         {
         case 4:                 // 4 pixels to 1

           do                    // Process 16x16 blocks of pixels
             {
             JPGGetBlock (YVector1, Image.HuffDCTableY,    Image.HuffACTableY,    Image.QuantTableY,    &dcY);
             JPGGetBlock (YVector2, Image.HuffDCTableY,    Image.HuffACTableY,    Image.QuantTableY,    &dcY);
             JPGGetBlock (YVector3, Image.HuffDCTableY,    Image.HuffACTableY,    Image.QuantTableY,    &dcY);
             JPGGetBlock (YVector4, Image.HuffDCTableY,    Image.HuffACTableY,    Image.QuantTableY,    &dcY);
             JPGGetBlock (CbVector, Image.HuffDCTableCbCr, Image.HuffACTableCbCr, Image.QuantTableCbCr, &dcCb);
             JPGGetBlock (CrVector, Image.HuffDCTableCbCr, Image.HuffACTableCbCr, Image.QuantTableCbCr, &dcCr);
             // YCbCr vectors have been obtained

             for (i=0; i<8; i++)  // Draw top left 8x8 pixels
               for (j=0; j<8; j++)
                 {
                 y = YVector1[i][j];
                 i2 = i >> 1;
                 j2 = j >> 1;
                 cb = CbVector[i2][j2];
                 cr = CrVector[i2][j2];
                 JPGToRGB (y, cb, cr, &r, &g, &b);
                 xj = xindex + j;
                 yi = yindex + i;
                 if ( (xj < Image.Cols) && (yi < Image.Rows) )
                   gfxPixel (xj + x0, yi + y0, RGB(r, g, b), (u32*)vram);
                 }
             for (i=0; i<8; i++)  // Draw top right 8x8 pixels
               for (j=8; j<16; j++)
                 {
                 y = YVector2[i][j - 8];
                 i2 = i >> 1;
                 j2 = j >> 1;
                 cb = CbVector[i2][j2];
                 cr = CrVector[i2][j2];
                 JPGToRGB (y, cb, cr, &r, &g, &b);
                 xj = xindex + j;
                 yi = yindex + i;
                 if ((xj < Image.Cols) && (yi < Image.Rows))
                   gfxPixel (xj + x0, yi + y0, RGB(r, g, b), (u32*)vram);
                 }
             for (i=8; i<16; i++)  // Draw bottom left 8x8 pixels
               for (j=0; j<8; j++)
                 {
                 y = YVector3[i - 8][j];
                 i2 = i >> 1;
                 j2 = j >> 1;
                 cb = CbVector[i2][j2];
                 cr = CrVector[i2][j2];
                 JPGToRGB (y, cb, cr, &r, &g, &b);
                 xj = xindex + j;
                 yi = yindex + i;
                 if ((xj < Image.Cols) && (yi < Image.Rows))
                   gfxPixel (xj + x0, yi + y0, RGB(r, g, b), (u32*)vram);
                 }
             for (i=8; i<16; i++)          // Draw bottom right 8x8 pixels
               for (j=8; j<16; j++)
                 {
                 y = YVector4[i - 8][j - 8];
                 i2 = i >> 1;
                 j2 = j >> 1;
                 cb = CbVector[i2][j2];
                 cr = CrVector[i2][j2];
                 JPGToRGB (y, cb, cr, &r, &g, &b);
                 xj = xindex + j;
                 yi = yindex + i;
                 if ((xj < Image.Cols) && (yi < Image.Rows))
                   gfxPixel (xj + x0, yi + y0, RGB(r, g, b), (u32*)vram);
                 }
             xindex += 16;
             if (xindex >= Image.Cols)
                {
                xindex = 0; yindex += 16; mcu = 1;
                }
             if ((mcu == 1) && (Restart != 0))    //Execute the restart interval
                {
                curByte = JPGGetByte(); curByte = JPGGetByte(); curByte = JPGGetByte();
                curBits = 128;
                dcY = 0; dcCb = 0; dcCr = 0; mcu = 0;  //Reset the DC value
                }
             }
//           while ((findex < flen) && (yindex < Image.Rows));
           while (yindex < Image.Rows);
           break;
         case 2:           // 2 pixels to 1
           do
             {
             JPGGetBlock (YVector1, Image.HuffDCTableY,    Image.HuffACTableY,    Image.QuantTableY,    &dcY);
             JPGGetBlock (YVector2, Image.HuffDCTableY,    Image.HuffACTableY,    Image.QuantTableY,    &dcY);
             JPGGetBlock (CbVector, Image.HuffDCTableCbCr, Image.HuffACTableCbCr, Image.QuantTableCbCr, &dcCb);
             JPGGetBlock (CrVector, Image.HuffDCTableCbCr, Image.HuffACTableCbCr, Image.QuantTableCbCr, &dcCr);
             // YCbCr vectors have been obtained

             for (i=0; i<8; i++)       // Draw left 8x8 pixels
               for (j=0; j<8; j++)
                 {
                 y = YVector1[i][j];
                 i2 = i >> 1;
                 j2 = j >> 1;
                 cb = CbVector[i2][j2];
                 cr = CrVector[i2][j2];
                 JPGToRGB (y, cb, cr, &r, &g, &b);
                 xj = xindex + j;
                 yi = yindex + i;
                 if ((xj < Image.Cols) && (yi < Image.Rows))
                   gfxPixel (xj + x0, yi + y0, RGB(r, g, b), (u32*)vram);
                 }

             for (i=0; i<8; i++)       // Draw right 8x8 pixels
               for (j=8; j<16; j++)
                 {
                 y = YVector2[i][j - 8];
                 i2 = i >> 1;
                 j2 = j >> 1;
                 cb = CbVector[i2][j2];
                 cr = CrVector[i2][j2];
                 JPGToRGB (y, cb, cr, &r, &g, &b);
                 xj = xindex + j;
                 yi = yindex + i;
                 if ((xj < Image.Cols) && (yi < Image.Rows))
                   gfxPixel (xj + x0, yi + y0, RGB(r, g, b), (u32*)vram);
                 }
             xindex += 16;
             if (xindex >= Image.Cols)
               {
               xindex = 0; yindex += 8; mcu = 1;
               }
             if ((mcu == 1) && (Restart != 0))  // execute the restart interval
               {
               curByte = JPGGetByte(); curByte = JPGGetByte(); curByte = JPGGetByte();
               curBits = 128;
               dcY = 0; dcCb = 0; dcCr = 0; mcu = 0;
               }
             }
//           while ((findex < flen) && (yindex < Image.Rows));
           while (yindex < Image.Rows);
           break;
         case 1:        // 1 pixel to 1
           do
             {
             JPGGetBlock (YVector1, Image.HuffDCTableY,    Image.HuffACTableY,    Image.QuantTableY,    &dcY);
             JPGGetBlock (CbVector, Image.HuffDCTableCbCr, Image.HuffACTableCbCr, Image.QuantTableCbCr, &dcCb);
             JPGGetBlock (CrVector, Image.HuffDCTableCbCr, Image.HuffACTableCbCr, Image.QuantTableCbCr, &dcCr);
             // YCbCr vectors have been obtained

             for (i=0; i<8; i++)            // Draw 8x8 pixels
               for (j=0; j<8; j++)
                 {
                 y = YVector1[i][j];
                 i2 = i >> 1;
                 j2 = j >> 1;
                 cb = CbVector[i2][j2];
                 cr = CrVector[i2][j2];
                 JPGToRGB (y, cb, cr, &r, &g, &b);
                 xj = xindex + j;
                 yi = yindex + i;
                 if ((xj < Image.Cols) && (yi < Image.Rows))
                   gfxPixel (xj + x0, yi + y0, RGB(r, g, b), (u32*)vram);
                 }

             xindex += 8;
             if (xindex >= Image.Cols)
               {
               xindex = 0; yindex += 8; mcu = 1;
               }
             if ((mcu == 1) && (Restart != 0))  // execute the restart interval
               {
               curByte = JPGGetByte(); curByte = JPGGetByte(); curByte = JPGGetByte();
               curBits = 128;
               dcY = 0; dcCb = 0; dcCr = 0; mcu = 0;
               }
             }
//           while ((findex < flen) && (yindex < Image.Rows));
           while (yindex < Image.Rows);
           break;
         }  // Ratio
       }
     case 1:
       do
         {
         JPGGetBlock (YVector1, Image.HuffDCTableY, Image.HuffACTableY, Image.QuantTableY, &dcY);
         // Y vector has been obtained

         for (i=0; i<8; i++)           // Draw 8x8 pixels
           for (j=0; j<8; j++)
             {
             y = YVector1[i][j];
             if (y < 0) y = 0;
             if (y > 255) y = 255;
             xj = xindex + j;
             yi = yindex + i;
             if ((xj < Image.Cols) && (yi < Image.Rows))
               gfxPixel (xj + x0, yi + y0, RGB(y, y, y), (u32*)vram);
             }

// Get setup to draw next block
         xindex += 8;
         if (xindex >= Image.Cols)
           {
           xindex = 0; yindex += 8; mcu = 1;
           }

         if ((mcu == 1) && (Restart != 0))   // execute the restart interval
           {
           curByte = JPGGetByte(); curByte = JPGGetByte(); curByte = JPGGetByte();
           curBits = 128;
           dcY = 0; mcu = 0;
           }
         }
//       while ((findex <flen) && (yindex < Image.Rows));
       while (yindex < Image.Rows);
       break;
     }

   return(1);
   }

s16 JPGReceiveBits (u16 cat)
   {
   u32 temp0 = 0;
   u16 i;
   s32 ReceiveBits;

   for (i=0; i<cat; i++)
      temp0 = temp0 * 2 + JPGNextBit();
   if ((temp0*2) >= (JPGpower2(cat)) )
      ReceiveBits = temp0;
   else
      ReceiveBits = -(JPGpower2(cat) - 1) + temp0;
   return (ReceiveBits);
   }

void JPGToRGB (s16 y0, s16 cb0, s16 cr0, s16 *r0, s16 *g0, s16 *b0)
   {
   // Do color space conversion from YCbCr to RGB
   *r0 = (y0) + (((cr0-128) * 45) >> 5);
   *g0 = (y0) - (((cb0-128) * 11) >> 5) - (((cr0-128) * 23) >> 5);
   *b0 = (y0) + (((cb0-128) * 57) >> 5);
   if (*r0 > 255) *r0 = 255;
   if (*r0 < 0) *r0 = 0;
   if (*g0 > 255) *g0 = 255;
   if (*g0 < 0) *g0 = 0;
   if (*b0 > 255) *b0 = 255;
   if (*b0 < 0) *b0 = 0;
   }
