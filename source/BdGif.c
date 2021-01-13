#include "Socrates.h"

#include "String.h"

#include "BdGif.h"

#define MAX_CODES     4096

static u32  filepos = 0;
static s32  curr_size = 0;
static s32  clear = 0;
static s32  ending = 0;
static s32  newcodes = 0;
static s32  top_slot = 0;
static s32  slot = 0;
static s32  navail_bytes = 0;
static s32  nbits_left = 0;
static u8   b1 = 0;
static u8  *pbytes = NULL;

static u8   byte_buff[257]__attribute__ ((section (".ewram")));

static void BdGifMemRead(u8 *dst, u16 bytes, const u8 *src)
{
    u16 i;
    u8 *tdst = dst; 

    for(i=0;i<bytes;i++)
    {
        *tdst = src[filepos];
        tdst++;
        filepos++;
    }
}

static u16 BdGifGetw(const u8 *src)
{

    u16 w = src[filepos];
    filepos++;
    w += src[filepos]*256;
    filepos++;
    return w;
}

static u8 BdGifGetc(const u8 *src)
{
    u8 c = src[filepos];
    filepos++;
    return c;
}

static const unsigned long code_mask[13] =
{
   0L,
   0x0001L, 0x0003L,
   0x0007L, 0x000FL,
   0x001FL, 0x003FL,
   0x007FL, 0x00FFL,
   0x01FFL, 0x03FFL,
   0x07FFL, 0x0FFFL
};

static void BdGifInitStaticVars(void)
{
   filepos = 0;
   curr_size = 0;
   clear = 0;
   ending = 0;
   newcodes = 0;
   top_slot = 0;
   slot = 0;
   navail_bytes = 0;
   nbits_left = 0;
   b1 = 0;
   pbytes = NULL;
}

static int get_next_code(const u8 *src)
{
   int  i;
   unsigned long ret;

   if( ! nbits_left )
   {
      if( navail_bytes <= 0 )
      {
         pbytes = byte_buff;
         navail_bytes = BdGifGetc(src);
         if( navail_bytes )
            for( i = 0; i < navail_bytes; ++i )
               byte_buff[i] = (u8)BdGifGetc(src);
      }
      b1 = *pbytes++;
      nbits_left = 8;
      --navail_bytes;
   }
   ret = b1 >> (8 - nbits_left);
   while( curr_size > nbits_left )
   {
      if( navail_bytes <= 0 )
      {
         pbytes = byte_buff;
         navail_bytes = BdGifGetc(src);
         if( navail_bytes )
            for( i = 0; i < navail_bytes; ++i )
               byte_buff[i] = (u8)BdGifGetc(src);
      }
      b1 = *pbytes++;
      ret |= b1 << nbits_left;
      nbits_left += 8;
      --navail_bytes;
   }
   nbits_left -= curr_size;

   return( (int) (ret & code_mask[curr_size]) );
}

u8  stack[MAX_CODES + 1 ]__attribute__ ((section (".ewram")));
u8  suffix[MAX_CODES + 1 ]__attribute__ ((section (".ewram")));
u16 prefix[(MAX_CODES + 1)*2]__attribute__ ((section (".ewram")));

bool BdGifLoad(const u8 *src, u16 *dst, u16 *pal, int *width, int *height)
{
   u8* sp;
   s32 code, palsize, fc, oc, i, j, c;
   u8  size, r, g, b;

   u8  buf[1028];

   u16 bytes = 1;
   u16 aaaa = 0;

   BdGifInitStaticVars();

   BdGifMemRead(buf, 6, src);

   if( strncmp( (char *)buf, "GIF", 3 ) )
   {
      return false;
   }

   BdGifMemRead(buf, 7, src);

   j = 0;

   palsize = 3*(2 << (buf[4] & 7));

   if(pal == NULL)
   {
       filepos+=palsize;
   }
   else for( i = 0; i < palsize; i+=3)
   {
      r = BdGifGetc(src)>>3;
      g = BdGifGetc(src)>>3;
      b = BdGifGetc(src)>>3;
      if (pal)
      {
          pal[j] = SO_RGB(r,g,b);
          j++;
      }
   }

   filepos+=5;

   i = BdGifGetw(src);
   if( width )
      *width = i;

   i = BdGifGetw(src);
   if( height )
      *height = i;

   if(dst == NULL) 
   {
      return true;
   }

   filepos++;

   size = (u8)BdGifGetc(src);
   if( size < 2 || 9 < size )
   {
      return false;
   }

   curr_size = size + 1;
   top_slot = 1 << curr_size;
   clear = 1 << size;
   ending = clear + 1;
   slot = newcodes = ending + 1;
   navail_bytes = nbits_left = 0;
   oc = fc = 0;
   sp = stack;

   while( ((c = get_next_code(src)) != ending) && bytes < 65536 )
   {
      if(c<0) return 0;

      if( c == clear )
      {
         curr_size = size + 1;
         slot = newcodes;
         top_slot = 1 << curr_size;
         while( (c = get_next_code(src)) == clear );
         if( c == ending )
            break;
         if( c >= slot )
            c = 0;
         oc = fc = c;

         if(SO_NUMBER_IS_EVEN(bytes))
         {
             u16 faszom = (u8)(c);
             *dst++ = (faszom<<8)+aaaa;
         }
         else
         {
             aaaa = 0;
             aaaa = (u8)(c);
         }

         bytes++;
      }
      else
      {
         code = c;
         if( code >= slot )
         {
            code = oc;
            *sp++ = (u8)fc;
         }

         while( code >= newcodes )
         {
            *sp++ = suffix[code];
            code = prefix[code];
         }

         *sp++ = (u8)code;

         if( slot < top_slot )
         {
            fc = code;
            suffix[slot] = (u8)fc;
            prefix[slot] = (u16)oc;
            slot++;
            oc = c;
         }

         if( slot >= top_slot && curr_size < 12 )
         {
            top_slot <<= 1;
            ++curr_size;
         }

         while( sp > stack )
         {
            --sp;

            if(SO_NUMBER_IS_EVEN(bytes))
            {
                u16 faszom = (u8)(*sp);
                *dst++ = (faszom<<8)+aaaa;
            }
            else
            {
                aaaa = 0;
                aaaa = (u8)(*sp);
            }

            bytes++;
         }
      }
   }
   return true;
}
