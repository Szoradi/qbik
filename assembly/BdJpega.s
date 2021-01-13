@ jpeg5.s -
@
@  Support GAS assembly code for jpeg5.c
@ and possibly later versions.
@ v1.0318 - Original version

        .ARM
        .ALIGN
        .GLOBL  JPGGetByte

@ Entry: -
@ Exit: r0 = 8bit value

JPGGetByte:
        ldr     r2,_JPGfindex
        ldr     r1,[r2]
        ldrb    r0,[r1],#1
        str     r1,[r2]
        bx      lr

        .GLOBL  JPGGetWord

@ Entry: -
@ Exit: r0 = 16bit value

JPGGetWord:
        ldr     r2,_JPGfindex
        ldr     r0,[r2]
        add     r1,r0,#2
        str     r1,[r2]
        ldrb    r1,[r0],#1
        ldrb    r0,[r0]
        orr     r0,r0,r1,lsl #8
        bx      lr

_JPGfindex:
        .word   JPGfindex

        .GLOBL  JPGNextBit

@ Entry: -
@ Exit: r0 = 1bit value (0 or 1)

JPGNextBit:
        ldr     r1,0f
        ldrb    r0,[r1]
        add     r2,r0,r0
        strb    r2,[r1]         @ curByte <<= 1
        mov     r0,r0,lsr #7    @ return = CurByte >> 7;
        ldr     r1,1f
        ldrb    r2,[r1]
        movs    r2,r2,lsr #1
        strb    r2,[r1]         @ curBits >>= 1
        bxne    lr              @ curBits !=0, so exit

        stmfd   sp!,{r0}
        mov     r2,#128
        strb    r2,[r1]         @ curBits = 128

@ Get a byte
        ldr     r2,_JPGfindex
        ldr     r1,[r2]
        ldrb    r0,[r1],#1
        str     r1,[r2]         @ r0 = next byte

        ldr     r1,0f
        strb    r0,[r1]         @ curByte = JPGGetByte();
        cmps    r0,#255
        bne     9f
@ curByte == 255

@ Get a byte
        ldr     r1,[r2]
        ldrb    r0,[r1],#1
        str     r1,[r2]         @ r0 = next byte

        cmps    r0,#0xd9
        bne     9f

        ldr     r1,_JPGEOI
        mov     r0,#1
        strb    r0,[r1]         @ EOI = 1

        ldmfd   sp!,{r0}
        mov     r0,#0
        bx      lr

9:
        ldmfd   sp!,{r0}
        bx      lr

0:      .word   JPGcurByte
1:      .word   JPGcurBits
_JPGEOI:
        .word   JPGeoi

        .GLOBL  JPGClear128Bytes

@ Entry: r0 = array address
@ Exit: -

JPGClear128Bytes:
        stmfd   sp!,{r4}
        mov     r1,#0
        mov     r2,#0
        mov     r3,#0
        mov     r4,#0
        stmia   r0!,{r1-r4}
        stmia   r0!,{r1-r4}
        stmia   r0!,{r1-r4}
        stmia   r0!,{r1-r4}
        stmia   r0!,{r1-r4}
        stmia   r0!,{r1-r4}
        stmia   r0!,{r1-r4}
        stmia   r0!,{r1-r4}
        ldmfd   sp!,{r4}
        bx      lr

        .GLOBL  JPGDecode

@ r0 = &inArray
@ r1 = temp
@ r2 = &EOI
@ r3 = index & curVal
@ r4 = cnt up 256
@ r5 = temp
@ r6 = cnt down 256
@ r7 = L
@ r8 = r0 save
@ r9 = MatchFound

@ Entry: r0 = Huffman table address
@ Exit:  r0 = coefficient

JPGDecode:
        stmfd   sp!,{r3-r9,r14}

        mov     r5,r0
        ldr     r3,_JPGfindex
        ldr     r4,[r3]

@ Get a byte
        mov     r1,r4
        ldrb    r0,[r1],#1
        str     r1,[r3]

        cmps    r0,#255
        strne   r4,[r3]              @ findex -= 1
        bne     _JD9

        bl      JPGGetByte
        cmps    r0,#0xd0
        strcc   r4,[r3]              @ findex -= 2
        bcc     _JD9

        cmps    r0,#0xd8
        strcs   r4,[r3]              @ findex -= 2
        bcs     _JD9

        ldr     r1,_HM11
        ldrb    r0,[r1]
        sub     r0,r0,#1             @ r0 = curBits - 1;

        ldr     r1,_HM12
        ldrb    r2,[r1]
        and     r1,r2,r0             @ r1 = curByte & n2
        cmps    r1,r0
        bne     _JD9

        ldr     r1,_JPGEOI
        mov     r0,#1
        strb    r0,[r1]              @ EOI = 1

        b       _HM8

_JD9:
        mov     r0,r5

        mov     r9,#-1               @ MatchFound = -1
        mov     r8,r0

        mov     r3,#0
        mov     r7,#1
_HM0:
        bl      JPGNextBit
        add     r3,r0,r3,lsl #1      @ CurVal = (CurVal << 1) + JPGNextBit()

        mov     r0,r8
        ldr     r2,_JPGEOI

        ldrb    r5,[r2]              @ r8 = EOI
        cmps    r5,#0
        bne     _HM8

        mov     r6,#256
        mov     r4,#0
_HM1:
        ldrh    r5,[r0,#4]           @ r5 = inArray[i].Length
        cmps    r7, r5
        bcc     _HM6
        bne     _HM3

        ldrh    r5,[r0]              @ r5 = inArray[i].Index
        cmps    r3,r5

        moveq   r9,r4
        beq     _HM6
_HM3:
        add     r0,r0,#6             @ Size of packed structure element is 6 bytes
        add     r4,r4,#1
        subs    r6,r6,#1
        bne     _HM1
_HM6:
        adds    r5,r9,#1
        cmps    r5,#0
        bne     _HM7

        add     r7,r7,#1
        cmps    r7,#17
        bne     _HM0

_HM7:
        mov     r2,r8
        mov     r0,r9
        ldmfd   sp!,{r3-r9,r14}
                                     @ rtn(1)
        adds    r1,r0,#1
        bxeq    lr                   @ if (MatchFound == -1) return(-1);

        add     r1,r0,r0,lsl #1
        add     r1,r1,r1
        add     r0,r1,#2             @ r1 = 6 * MatchFound + .Code
        ldrh    r0,[r2,r0]           @ return(inArray[MatchFound].Code)
        bx      lr

_HM8:
        ldmfd   sp!,{r3-r9,r14}      @ return(0)
        mov     r0,#0
        bx      lr

_HM11:  .word   JPGcurBits
_HM12:  .word   JPGcurByte

        .GLOBL  JPGReceiveBits

@ r0 = cat
@ r1 = power2(cat)
@ r2 = destroyed by JPGNextBit
@ r3 = temp0
@ r4 = cat
@ r5 = temp0 << 1
@ r6 = cat

@ Entry: r0 = bits
@ Exit:  r0 = bitVal

JPGReceiveBits:
        cmps    r0,#0
        bxeq    lr

        stmfd   sp!,{r1-r5,r14}
        mov     r4,r0
        mov     r5,r0
        mov     r3,#0
1:
        bl      JPGNextBit
        add     r3,r0,r3,lsl #1
        subs    r5,r5,#1
        bne     1b

        mov     r5,r3,lsl #1         @ r5 = temp0 << 1
        mov     r1,#1
        mov     r1,r1,lsl r4         @ r1 = 2 ^ (cat)

        mov     r0,r3
        cmps    r5,r1

        subcc   r0,r3,r1
        addcc   r0,r0,#1             @ return = -(JPGpower2(cat) - 1) + temp0

        ldmfd   sp!,{r1-r5,r14}
        bx      lr


        .GLOBL  JPGGetBlockBits

@ r0 = temp
@ r1 = destroyed by JPGDecode
@ r2 = destroyed by JPGDecode
@ r3 = zeros
@ r4 = bits
@ r5 = temp
@ r6 = HuffACNum
@ r7 = JPGZig1
@ r8 = JPGZig2
@ r9 = ZigIndex
@ r10 = &array2
@ r11 = ACCount

@ Entry: r0 = HuffACNum, r1 = &array2[]
@ Exit:  -

JPGGetBlockBits:
        stmfd   sp!,{r4-r11,r14}

        mov     r2,#11
        mov     r6,r0
        ldr     r7,_GBB3
        ldr     r8,_GBB4
        mov     r9,#1
        mov     r10,r1
        mov     r11,#1
1:
        cmps    r6,#0                @ if (HuffACNum)
        ldrne   r0,_GBB2             @   d = JPGDecode(HuffmanAC1)
                                     @ else
        ldreq   r0,_GBB1             @   d = JPGDecode(HuffmanAC0)
        bl      JPGDecode

        mov     r3,r0,asr #4         @ zeros = d >> 4
        and     r4,r0,#0xf           @ bits = d & 15

        mov     r0,r4
        bl      JPGReceiveBits

        cmps    r4,#0
        beq     2f

        add     r9,r9,r3             @ ZigIndex += zeros
        add     r11,r11,r3           @ ACCount += zeros
        cmps    r11,#64
        bcs     4f

        ldrb    r5,[r7,r9]
        ldrb    r4,[r8,r9]
        add     r5,r4,r5,lsl #3
        add     r5,r5,r5
        strh    r0,[r10,r5]          @ array2[(JPGZig1[ZigIndex]<<3) + JPGZig2[ZigIndex]] = bitVal
        add     r9,r9,#1             @ ZigIndex++
        add     r11,r11,#1           @ ACCount++
        b       3f
2:
        cmps    r3,#15               @ if (zeros != 15) break
        bne     4f
        add     r9,r9,#15            @ ZigIndex += 15
        add     r11,r11,#16          @ ACCount += 16
3:
        cmps    r11,#64
        bcc     1b                   @ while (ACCount < 64)
4:
        ldmfd   sp!,{r4-r11,r14}
        bx      lr

_GBB1:  .word   JPGHuffmanAC0
_GBB2:  .word   JPGHuffmanAC1
_GBB3:  .word   JPGZig1
_GBB4:  .word   JPGZig2

        .GLOBL  JPGDraw8x8

@ r0 = temp
@ r1 = temp
@ r2 = temp
@ r3 = vram address
@ r4 = &Vector[]
@ r5 = i offset
@ r6 = j offset
@ r7 = i count
@ r8 = j count
@ r9 = temp
@ r10 = temp
@ r11 = temp
@ r12 = temp

@ Entry: r0 = &YVector[], r1 = i, r2 = j, r3 = vram address
@ Exit: -

JPGDraw8x8:
        stmfd   sp!,{r4-r12}

        mov     r4,r0
        mov     r5,r1
        mov     r6,r2
        mov     r7,#0
        mov     r8,#0
1:
        add     r0,r8,r7,lsl #3
        add     r0,r0,r0
        ldrsh   r0,[r4,r0]           @ r0 = YVector[(i<<3)+j]

        add     r1,r5,r7
        mov     r1,r1,lsr #1         @ r1 = (i+io) >> 1
        add     r2,r6,r8
        mov     r2,r2,lsr #1         @ r2 = (j+jo) >> 1

        add     r10,r2,r1,lsl #3
        add     r10,r10,r10
        ldr     r12,_D88b
        ldrsh   r9,[r12,r10]         @ r9 = CbVector[(i2<<3)+j2]

        ldr     r12,_D88r
        ldrsh   r10,[r12,r10]        @ r10 = CrVector[(i2<<3)+j2]

        sub     r1,r10,#128
        mov     r11,#45
        mul     r2,r1,r11
        add     r11,r0,r2,asr #5     @ r11 = red = y + (((cr-128) * 45) >> 5)

@ Range limit red to 0-255

        cmps    r11,#0x80000000
        movcs   r11,#0
        cmps    r11,#0x100
        movcs   r11,#0xff

@ r12 = blue = y + (((cb-128) * 57) >> 5)

        sub     r1,r9,#128
        mov     r12,#57
        mul     r2,r1,r12
        add     r12,r0,r2,asr #5

@ Range limit blue to 0-255

        cmps    r12,#0x80000000
        movcs   r12,#0
        cmps    r12,#0x100
        movcs   r12,#0xff

@ r10 = green = y - (((cb-128) * 11) >> 5) - (((cr-128) * 23) >> 5)

        mov     r2,#11
        mul     r2,r1,r2
        sub     r9,r0,r2,asr #5      @ r9 = ((cb0))

        sub     r1,r10,#128
        mov     r2,#23
        mul     r2,r1,r2

        sub     r10,r9,r2,asr #5

@ range limit to 0-255

        cmps    r10,#0x80000000
        movcs   r10,#0
        cmps    r10,#0x100
        movcs   r10,#0xff

@ Convert RGB (24bit) to BGR (16bit)
@  r2 = ((((B) >> 3) << 10)+(((G) >> 3) << 5)+((R) >> 3))

        mov     r2,r11,lsr #3
        mov     r1,r10,lsr #3
        add     r2,r2,r1,lsl #5
        mov     r1,r12,lsr #3
        add     r2,r2,r1,lsl #10     @ r2 = 16bit color

@ Prepare x & y coordinates

        ldr     r12,_D88xi
        ldrh    r10,[r12]
        add     r0,r10,r8            @ xj
        add     r0,r0,r6

        ldr     r12,_D88yi
        ldrh    r11,[r12]
        add     r1,r11,r7            @ yi
        add     r1,r1,r5

@ Plot pixel at r0,r1 using color r2 at screen address r3

        mov     r10,#480
        mul     r11,r10,r1
        add     r11,r11,r0,lsl #1
        add     r10,r11,r3
        strh    r2,[r10]

        add     r8,r8,#1
        cmps    r8,#8
        bne     1b

        mov     r8,#0

        add     r7,r7,#1
        cmps    r7,#8
        bne     1b

        ldmfd   sp!,{r4-r12}
        bx      lr

_D88xi: .word   JPGXOrigin
_D88yi: .word   JPGYOrigin
_D88b:  .word   JPGCbVector
_D88r:  .word   JPGCrVector

