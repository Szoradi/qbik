@*******************************
@* GBA Graphics Library        *
@*  by Jeff Frohwein           *
@* http://www.devrs.com        *
@*******************************
@ v1.0221 - Original release

@ Draw solid pixel in GBA graphics modes 3/5 in ARM asm
@ Entry: x = pixel X coordinate
@        y = pixel Y coordinate
@    color = pixel color
@     addr = screen base addr
@ (void) gfxPixel (u8 x, u8 y, u16 color, u32 addr);

        .ARM
        .ALIGN
        .GLOBL  gfxPixel

gfxPixel:
        stmfd   sp!,{r4-r5}

        mov     r4,#480
        mul     r5,r4,r1
        add     r5,r5,r0,lsl #1
        add     r4,r5,r3
        strh    r2,[r4]

        ldmfd   sp!,{r4-r5}
        bx      lr

