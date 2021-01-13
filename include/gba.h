#ifndef GBA_H
#define GBA_H

#include "Socrates.h"

/*
 #########################################################################################

    A G B   Hardware  Macros

 #########################################################################################  
*/

//Memory locations

#define MEM_SYSROM                      0x00000000      // System ROM, for BIOS Calls
#define MEM_EXRAM                       0x02000000      // External WRAM, slow, also used for Multiboot uploads
#define MEM_RAM                         0x03000000      // Fast CPU internal RAM
#define MEM_IO                          0x04000000      // Register Base, all HW Registers are in here.
#define MEM_PAL                         0x05000000      // Palette Base
#define MEM_PAL_BG                      0x05000000      // Palette for BG
#define MEM_PAL_OBJ                     0x05000200      // Palette for OBJ
#define MEM_VRAM                        0x06000000      // GBA Video RAM
#define MEM_BG                      0x06000000  // GBA Video RAM (in BG mode)
#define MEM_OBJ             0x06010000  // OBJ memoryspace (32 kBytes)
#define MEM_OAM                         0x07000000      // Object control space for sprites
#define MEM_ROM0                        0x08000000      // Rom Space 0 (fastest, 0 wait)
#define MEM_ROM1                        0x0A000000      // Rom Space 1 (1 wait)
#define MEM_ROM2                        0x0C000000      // Rom Space 2 (slowest, 2 wait)
#define MEM_SRAM                        0x0E000000      // Gamepak SRAM, if any.

// Base block locations

#define MEM_CHR_BB(x)       (0x06000000 + (x*0x4000))

#define MEM_SYSROM_SIZE             0x00004000
#define MEM_EXRAM_SIZE              0x00040000
#define MEM_RAM_SIZE                0x00008000
#define MEM_PAL_SIZE                0x00000400
#define MEM_VRAM_SIZE               0x00018000
#define MEM_BG_MODE0_SIZE               0x00010000
#define MEM_BG_MODE1_SIZE               0x00010000
#define MEM_BG_MODE2_SIZE               0x00010000
#define MEM_BG_MODE3_BUFSIZE    0x00014000
#define MEM_BG_MODE4_BUFSIZE    0x0000A000
#define MEM_BG_MODE5_BUFSIZE    0x0000A000
#define MEM_BG_SIZE                     0x00010000
#define MEM_BG_SIZE                     0x00010000
#define MEM_OBJ_SIZE            0x00008000
#define MEM_OAM_SIZE                0x00000400
#define MEM_ROM0_SIZE               0x02000000
#define MEM_ROM1_SIZE               0x02000000
#define MEM_ROM2_SIZE               0x02000000
#define MEM_SRAM_SIZE               0x00010000

// Memory Pointers

#define MEM_SYSROM_PTR                  (u8*) 0x00000000        // System ROM, for BIOS Calls
#define MEM_EXRAM_PTR                   (u8*) 0x02000000        // External WRAM, slow, also used for Multiboot uploads
#define MEM_RAM_PTR                             (u8*) 0x03000000        // Fast CPU internal RAM
#define MEM_IO_PTR                              (u8*) 0x04000000        // Register Base, all HW Registers are in here.
#define MEM_PAL_PTR                             (u8*) 0x05000000        // Palette Base
#define MEM_PAL_BG_PTR                  (u8*) 0x05000000        // Palette for BG
#define MEM_PAL_OBJ_PTR                 (u8*) 0x05000200        // Palette for OBJ
#define MEM_VRAM_PTR                    (u8*) 0x06000000        // GBA Video RAM
#define MEM_BG_PTR                  (u8*) 0x06000000    // GBA Video RAM
#define MEM_BG_MODE0_PTR            (u8*) 0x06000000    // GBA Video RAM
#define MEM_BG_MODE1_PTR            (u8*) 0x06000000    // GBA Video RAM
#define MEM_BG_MODE2_PTR            (u8*) 0x06000000    // GBA Video RAM
#define MEM_BG_MODE3_PTR            (u8*) 0x06000000    // GBA Video RAM
#define MEM_BG_MODE4_PTR(buf)   (u8*) (0x06000000+ buf * 0xA000)        // GBA Video RAM
#define MEM_BG_MODE5_PTR(buf)   (u8*) (0x06000000+ buf * 0xA000)        // GBA Video RAM
#define MEM_OBJ_PTR             (u8*) 0x06010000  // OBJ memoryspace (32 kBytes)
#define MEM_OAM_PTR                             (u8*) 0x07000000        // Object control space for sprites
#define MEM_ROM0_PTR                    (u8*) 0x08000000        // Rom Space 0 (fastest, 0 wait)
#define MEM_ROM1_PTR                    (u8*) 0x0A000000        // Rom Space 1 (1 wait)
#define MEM_ROM2_PTR                    (u8*) 0x0C000000        // Rom Space 2 (slowest, 2 wait)
#define MEM_SRAM_PTR                    (u8*) 0x0E000000        // Gamepak SRAM, if any.

// Base block pointers

#define MEM_CHR_BB_PTR(x)       ((u8*) 0x06000000 + (x*0x4000))
#define MEM_SCR_BB_PTR(x)       ((u16*) (0x06000000 + (x*0x800)))

/* 
----------------------------------------------------
 IO 0x000 --    DISCNT          Display Control Register

        Controls Display features such as video modes
        and visibility of display components
----------------------------------------------------    
*/

#define R_DISCNT                *(volatile u16 *) MEM_IO        // Display Control register

/* Masks */

#define V_DISCNT_BGMODE_MSK             0xFFF8                  // BGMode, can be set to 1-5
#define V_DISCNT_BUFSEL_MSK             0xFFEF                  // Display buffer selecton (0 or 1)
#define V_DISCNT_HBLOBJ_MSK             0xFFDF                  // Enable OBJ processing in HBL (0=enable)
#define V_DISCNT_OBJMAP_MSK             0xFFBF                  // OBJ mapping format (0=2d 1=1d)
#define V_DISCNT_FRCBLK_MSK             0xFF7F                  // Force image system to show blank screen
#define V_DISCNT_BG0_MSK                0xFEFF                  // Enable BG0 display
#define V_DISCNT_BG1_MSK                0xFDFF                  // Enable BG1 display
#define V_DISCNT_BG2_MSK                0xFBFF                  // Enable BG2 display
#define V_DISCNT_BG3_MSK                0xF7FF                  // Enable BG3 display
#define V_DISCNT_OBJ_MSK                0xEFFF                  // Enable OBJ display
#define V_DISCNT_WIN0_MSK               0xDFFF                  // Enable Window 0 display
#define V_DISCNT_WIN1_MSK               0xBFFF                  // Enable Window 1 display
#define V_DISCNT_WINO_MSK               0x7FFF                  // Enable OBJ Window display

/* Macros */

#define M_DISCNT_BGMODE_SET(x)  (R_DISCNT &= V_DISCNT_BGMODE_MSK);\
                                                                (R_DISCNT |= x);                                                                // Set BGMODE(x)
#define M_DISCNT_BUFSEL(x)              (R_DISCNT &= V_DISCNT_BUFSEL_MSK); \
                                (R_DISCNT |= (x<<4));                           // Display buffer X
#define M_DISCNT_BUFSEL_0               (R_DISCNT &= V_DISCNT_BUFSEL_MSK);                              // Display buffer 0
#define M_DISCNT_BUFSEL_1               (R_DISCNT |= 0x0010);                                                   // Display buffer 1
#define M_DISCNT_HBLOBJ_ENA             (R_DISCNT &= V_DISCNT_HBLOBJ_MSK)                               // Enable OBJ processing
#define M_DISCNT_HBLOBJ_DIS             (R_DISCNT |= 0x0020);                                                   // Disable OBJ processing
#define M_DISCNT_OBJMAP_2D              (R_DISCNT &= V_DISCNT_OBJMAP_MSK);                              // OBJ mapping format (0=2d 1=1d)
#define M_DISCNT_OBJMAP_1D              (R_DISCNT |= 0x0040);                                                   // OBJ mapping format (0=2d 1=1d)
#define M_DISCNT_FRCBLK_DIS             (R_DISCNT &= V_DISCNT_FRCBLK_MSK);                              // Image system normal operation
#define M_DISCNT_FRCBLK_ENA             (R_DISCNT |= 0x0080);                                                   // Image system forced to blank
#define M_DISCNT_BG0_OFF                (R_DISCNT &= V_DISCNT_BG0_MSK);                                 // Disable BG0 display
#define M_DISCNT_BG0_ON                 (R_DISCNT |= 0x0100);                                                   // Enable BG0 display
#define M_DISCNT_BG1_ON                 (R_DISCNT |= 0x0200);                                                   // Enable BG1 display
#define M_DISCNT_BG1_OFF                (R_DISCNT &= V_DISCNT_BG1_MSK);                                 // Disable BG1 display
#define M_DISCNT_BG2_ON                 (R_DISCNT |= 0x0400);                                                   // Enable BG2 display
#define M_DISCNT_BG2_OFF                (R_DISCNT &= V_DISCNT_BG2_MSK);                                 // Disable BG2 display
#define M_DISCNT_BG3_ON                 (R_DISCNT |= 0x0800);                                                   // Enable BG3 display
#define M_DISCNT_BG3_OFF                (R_DISCNT &= V_DISCNT_BG3_MSK);                                 // Disable BG3 display
#define M_DISCNT_OBJ_ON                 (R_DISCNT |= 0x1000);                                                   // Enable OBJ display
#define M_DISCNT_OBJ_OFF                (R_DISCNT &= V_DISCNT_OBJ_MSK);                                 // Disable OBJ display
#define M_DISCNT_WIN0_ON                (R_DISCNT |= 0x2000);                                                   // Enable WIN0 display
#define M_DISCNT_WIN0_OFF               (R_DISCNT &= V_DISCNT_WIN0_MSK);                                // Disable WIN0 display
#define M_DISCNT_WIN1_ON                (R_DISCNT |= 0x4000);                                                   // Enable WIN1 display
#define M_DISCNT_WIN1_OFF               (R_DISCNT &= V_DISCNT_WIN1_MSK);                                // Disable WIN1 display
#define M_DISCNT_WINO_ON                (R_DISCNT |= 0x8000);                                                   // Enable WINO display
#define M_DISCNT_WINO_OFF               (R_DISCNT &= V_DISCNT_WINO_MSK);                                // Disable WINO display

                                                                                // roll bit and or new 0s
#define M_DISCNT_BGX_SET(x,active)      (R_DISCNT &= ((0xFEFF<<x) | 0xFF ) ); \
                                        (R_DISCNT |= (active<<8)<<x);

/* 
--------------------------------------------------
  IO 0x006 --   VCNT            Vertical Line Counter
--------------------------------------------------
*/

#define R_VCNT                  *(volatile u16 *)(MEM_IO + 0x06)                // Vertical counter(0-227)

/* Masks */
#define V_VCNT_MSK                      0x00FF                          // Mask for the value.

/* Functions */
#define F_VCNT_CURRENT_SCANLINE R_VCNT

/* 
---------------------------------------------------
  IO 0x004 --   DISSTAT         Display Status Register

        Controls Display features such as blanking,
        and Display interrupts.
---------------------------------------------------     
*/

#define R_DISSTAT               *(volatile u16 *)(MEM_IO + 0x04)                // Display Status register

/* Constants */
#define V_DISSTAT_VBLSTAT               0x0001                  // Vertical Blank Status, 1 if Vblank is active
#define V_DISSTAT_HBLSTAT               0x0002                  // Horizontal Blank Status, 1 if Hblank is active
#define V_DISSTAT_VCNTEVAL              0x0004                  // 1 if V_DISSTAT_VCNT matches current scanline

/* Masks */
#define V_DISSTAT_VBLIRQR_MSK   0xFFF7                  // Set VBL IRQ Request
#define V_DISSTAT_HBLIRQR_MSK   0xFFEF                  // Set HBL IRQ Request
#define V_DISSTAT_VCNTIRQR_MSK  0xFFDF                  // Set VCNT match IRQ Request
#define V_DISSTAT_VCNT_MSK              0x00FF                  // Set scanline to check for with V_DISSTAT_VCNTEVAL

/* Functions */
#define F_DISSTAT_VBL_ACTIVE    (R_DISSTAT & V_DISSTAT_VBLSTAT)                         // true if in VBL
#define F_DISSTAT_HBL_ACTIVE    (R_DISSTAT & V_DISSTAT_HBLSTAT)                         // true if in HBL
#define F_DISSTAT_VCNT_ACTIVE   (R_DISSTAT & V_DISSTAT_VCNTEVAL)                        // true if scanline matches VCNT
#define F_DISSTAT_VCNT_GET              ((R_DISSTAT & V_DISSTAT_VCNT_MSK)>>16)          // returns VCNT


/* Macros */
#define M_DISSTAT_VBLIRQR_ON                    (R_DISSTAT |= 0x0008);                                  //turns on VBL IRQ
#define M_DISSTAT_VBLIRQR_OFF                   (R_DISSTAT &= V_DISSTAT_VBLIRQR_MSK );  //turns off VBL IRQ
#define M_DISSTAT_HBLIRQR_ON                    (R_DISSTAT |= 0x0010);                                  //turns on HBL IRQ
#define M_DISSTAT_HBLIRQR_OFF                   (R_DISSTAT &= V_DISSTAT_HBLIRQR_MSK );  //turns off HBL IRQ
#define M_DISSTAT_VCNTIRQR_ON                   (R_DISSTAT |= 0x0020);                                  //turns on VCNT IRQ
#define M_DISSTAT_VCNTIRQR_OFF                  (R_DISSTAT &= V_DISSTAT_VCNTIRQR_MSK ); //turns off VCNT IRQ
#define M_DISSTAT_VCNT_SET(scanline)    (R_DISSTAT &= V_DISSTAT_VCNT_MSK);\
                                                                                (R_DISSTAT |= (scanline<<16));                  //sets VCNT to scanline(x)



/* 
---------------------------------------------------
  IO 0x008 --   BG0CNT          Background 0 control register

  Controls the display behaviour of BG0
---------------------------------------------------     
*/

#define R_BG0CNT                *(volatile u16 *)(MEM_IO + 0x08)

/* Constants */
#define C_BGXCNT_SCRSIZE_256X256 0x00
#define C_BGXCNT_SCRSIZE_512X256 0x01
#define C_BGXCNT_SCRSIZE_256X512 0x02
#define C_BGXCNT_SCRSIZE_512X512 0x03


/* Masks */
#define V_BG0CNT_SCRSIZE_MSK    0x3FFF  //screensize, can be set to %00-%11
#define V_BG0CNT_SCRBB_MSK      0xE0FF  //screen base block in VRAM (0-31, 2kb incr.)
#define V_BG0CNT_CHRBB_MSK      0xFFF3  //character base block in VRAM (0-3, 16k incr.)
#define V_BG0CNT_PRIO_MSK       0xFFFD  //this bg's priority (0=highest 3=lowest)

/* Functions */

/* Macros */
#define M_BG0CNT_COLMODE_SET_16     (R_BG0CNT &= 0xFF7F); //set mode to 16 colrs / 16 pals
#define M_BG0CNT_COLMODE_SET_256    (R_BG0CNT |= 0x0080); //set mode to 256 colrs / 1 pal
#define M_BG0CNT_MOSAIC_SET_OFF     (R_BG0CNT &= 0xFFBF); //disable mosaic
#define M_BG0CNT_MOSAIC_SET_ON      (R_BG0CNT |= 0x0040); //enable mosaic
#define M_BG0CNT_SCRSIZE_SET(size)  (R_BG0CNT &= V_BG0CNT_SCRSIZE_MSK);\
                                    (R_BG0CNT |= (size<<14));       //sets scrsize to size
#define M_BG0CNT_SCRBB_SET(block)   (R_BG0CNT &= V_BG0CNT_SCRBB_MSK);\
                                    (R_BG0CNT |= (block<<8));   //sets scrbb to block
#define M_BG0CNT_CHRBB_SET(block)   (R_BG0CNT &= V_BG0CNT_CHRBB_MSK);\
                                    (R_BG0CNT |= (block<<2));   //sets chrbb to block
#define M_BG0CNT_PRIO_SET(prio)     (R_BG0CNT &= V_BG0CNT_PRIO_MSK);\
                                    (R_BG0CNT |= prio);         //sets prio to prio :)

/* 
---------------------------------------------------
  IO 0x00A --   BG1CNT          Background 1 control register

  Controls the display behaviour of BG1

    This BG cannot scale/rotate
    Also, for this mode there is no wrapping transparency

---------------------------------------------------     
*/

#define R_BG1CNT                *(volatile u16 *)(MEM_IO + 0x0A)

/* Constants */

/* Masks */
#define V_BG1CNT_SCRSIZE_MSK    0x3FFF  //screensize, can be set to %00-%11
#define V_BG1CNT_SCRBB_MSK      0xE0FF  //screen base block in VRAM (0-31, 2kb incr.)
#define V_BG1CNT_CHRBB_MSK      0xFFF3  //character base block in VRAM (0-3, 16k incr.)
#define V_BG1CNT_PRIO_MSK       0xFFFD  //this bg's priority (0=highest 3=lowest)

/* Functions */

/* Macros */
#define M_BG1CNT_COLMODE_SET_16     (R_BG1CNT &= 0xFF7F); //set mode to 16 colrs / 16 pals
#define M_BG1CNT_COLMODE_SET_256    (R_BG1CNT |= 0x0080); //set mode to 256 colrs / 1 pal
#define M_BG1CNT_MOSAIC_SET_OFF     (R_BG1CNT &= 0xFFBF); //disable mosaic
#define M_BG1CNT_MOSAIC_SET_ON      (R_BG1CNT |= 0x0040); //enable mosaic
#define M_BG1CNT_SCRSIZE_SET(size)  (R_BG1CNT &= V_BG1CNT_SCRSIZE_MSK);\
                                    (R_BG1CNT |= (size<<14));       //sets scrsize to size
#define M_BG1CNT_SCRBB_SET(block)   (R_BG1CNT &= V_BG1CNT_SCRBB_MSK);\
                                    (R_BG1CNT |= (block<<8));   //sets scrbb to block
#define M_BG1CNT_CHRBB_SET(block)   (R_BG1CNT &= V_BG1CNT_CHRBB_MSK);\
                                    (R_BG1CNT |= (block<<2));   //sets chrbb to block
#define M_BG1CNT_PRIO_SET(prio)     (R_BG1CNT &= V_BG1CNT_PRIO_MSK);\
                                    (R_BG1CNT |= prio);         //sets prio to prio :)


/* 
---------------------------------------------------
  IO 0x00C --   BG2CNT          Background 2 control register

  Controls the display behaviour of BG2

  This BG can scale/rotate in BGMode 1 and 2

  ---------------------------------------------------   
*/

#define R_BG2CNT                *(volatile u16 *)(MEM_IO + 0x0C)

/* Constants */

/* Masks */
#define V_BG2CNT_SCRSIZE_MSK    0x3FFF  //screensize, can be set to %00-%11
#define V_BG2CNT_SCRBB_MSK      0xE0FF  //screen base block in VRAM (0-31, 2kb incr.)
#define V_BG2CNT_CHRBB_MSK      0xFFF3  //character base block in VRAM (0-3, 16k incr.)
#define V_BG2CNT_PRIO_MSK       0xFFFD  //this bg's priority (0=highest 3=lowest)

/* Functions */

/* Macros */
#define M_BG2CNT_COLMODE_SET_16     (R_BG2CNT &= 0xFF7F); //set mode to 16 colrs / 16 pals
#define M_BG2CNT_COLMODE_SET_256    (R_BG2CNT |= 0x0080); //set mode to 256 colrs / 1 pal
#define M_BG2CNT_MOSAIC_SET_OFF     (R_BG2CNT &= 0xFFBF); //disable mosaic
#define M_BG2CNT_MOSAIC_SET_ON      (R_BG2CNT |= 0x0040); //enable mosaic
#define M_BG2CNT_SCRSIZE_SET(size)  (R_BG2CNT &= V_BG2CNT_SCRSIZE_MSK);\
                                    (R_BG2CNT |= (size<<14));       //sets scrsize to size
#define M_BG2CNT_SCRBB_SET(block)   (R_BG2CNT &= V_BG2CNT_SCRBB_MSK);\
                                    (R_BG2CNT |= (block<<8));   //sets scrbb to block
#define M_BG2CNT_CHRBB_SET(block)   (R_BG2CNT &= V_BG2CNT_CHRBB_MSK);\
                                    (R_BG2CNT |= (block<<2));   //sets chrbb to block
#define M_BG2CNT_PRIO_SET(prio)     (R_BG2CNT &= V_BG2CNT_PRIO_MSK);\
                                    (R_BG2CNT |= prio);         //sets prio to prio :)
#define M_BG2CNT_WRAP_SET_OFF       (R_BG2CNT &= 0xDFFF); //wrap around display off (transparent)
#define M_BG2CNT_WRAP_SET_ON        (R_BG2CNT |= 0x2000); //wrap around display on 



/* 
---------------------------------------------------
  IO 0x00E --   BG3CNT          Background 3 control register

  Controls the display behaviour of BG3

  This BG can scale/rotate in BGMode 1 and 2

  ---------------------------------------------------   
*/

#define R_BG3CNT                *(volatile u16 *)(MEM_IO + 0x0E)

/* Constants */

/* Masks */
#define V_BG3CNT_SCRSIZE_MSK    0x3FFF  //screensize, can be set to %00-%11
#define V_BG3CNT_SCRBB_MSK      0xE0FF  //screen base block in VRAM (0-31, 2kb incr.)
#define V_BG3CNT_CHRBB_MSK      0xFFF3  //character base block in VRAM (0-3, 16k incr.)
#define V_BG3CNT_PRIO_MSK       0xFFFD  //this bg's priority (0=highest 3=lowest)

/* Functions */

/* Macros */
#define M_BG3CNT_COLMODE_SET_16     (R_BG3CNT &= 0xFF7F); //set mode to 16 colrs / 16 pals
#define M_BG3CNT_COLMODE_SET_256    (R_BG3CNT |= 0x0080); //set mode to 256 colrs / 1 pal
#define M_BG3CNT_MOSAIC_SET_OFF     (R_BG3CNT &= 0xFFBF); //disable mosaic
#define M_BG3CNT_MOSAIC_SET_ON      (R_BG3CNT |= 0x0040); //enable mosaic
#define M_BG3CNT_SCRSIZE_SET(size)  (R_BG3CNT &= V_BG3CNT_SCRSIZE_MSK);\
                                    (R_BG3CNT |= (size<<14));       //sets scrsize to size
#define M_BG3CNT_SCRBB_SET(block)   (R_BG3CNT &= V_BG3CNT_SCRBB_MSK);\
                                    (R_BG3CNT |= (block<<8));   //sets scrbb to block
#define M_BG3CNT_CHRBB_SET(block)   (R_BG3CNT &= V_BG3CNT_CHRBB_MSK);\
                                    (R_BG3CNT |= (block<<2));   //sets chrbb to block
#define M_BG3CNT_PRIO_SET(prio)     (R_BG3CNT &= V_BG3CNT_PRIO_MSK);\
                                    (R_BG3CNT |= prio);         //sets prio to prio :)
#define M_BG3CNT_WRAP_SET_OFF       (R_BG3CNT &= 0xDFFF); //wrap around display off (transparent)
#define M_BG3CNT_WRAP_SET_ON        (R_BG3CNT |= 0x2000); //wrap around display on 



/* 
---------------------------------------------------
  IO 0x00x --   BGXCNT          Background X control register

  These are convienience macros for manipulating
  any of the 4 BG control registers.

  The first parameter in these macros is always x,
  the BGs number.
---------------------------------------------------     
*/
#define R_BGXCNT(x)                 (*(volatile u16 *)(MEM_IO+8+(x*2)))

#define M_BGXCNT_COLMODE_SET(x,mode)    (R_BGXCNT(x) &= 0xFF7F); \
                                        (R_BGXCNT(x) |= (mode<<7));             
#define M_BGXCNT_MOSAIC_SET(x,mode)     (R_BGXCNT(x) &= 0xFFBF); \
                                        (R_BGXCNT(x) |= (mode<<6));             
#define M_BGXCNT_SCRSIZE_SET(x,size)    (R_BGXCNT(x) &= V_BG0CNT_SCRSIZE_MSK);\
                                        (R_BGXCNT(x) |= (size<<14));            //sets scrsize to size
#define M_BGXCNT_SCRBB_SET(x,block)     (R_BGXCNT(x) &= V_BG0CNT_SCRBB_MSK);\
                                        (R_BGXCNT(x) |= (block<<8));            //sets scrbb to block
#define M_BGXCNT_CHRBB_SET(x,block)     (R_BGXCNT(x) &= V_BG0CNT_CHRBB_MSK);\
                                        (R_BGXCNT(x) |= (block<<2));            //sets chrbb to block
#define M_BGXCNT_PRIO_SET(x,prio)       (R_BGXCNT(x) &= V_BG0CNT_PRIO_MSK);\
                                        (R_BGXCNT(x) |= prio);                  //sets prio to prio :)

#define R_BGXSCRLX(x)                *(volatile u16 *)(MEM_IO + 0x10 + (x*4))
#define R_BGXSCRLY(x)                *(volatile u16 *)(MEM_IO + 0x12 + (x*4))

/* 
---------------------------------------------------
  IO 0x10 --    R_BG0SCRLX  BG0 Horizontal offset
                scrolling register
---------------------------------------------------     
*/
#define R_BG0SCRLX              *(volatile u16 *)(MEM_IO + 0x10)

/* Constants */
/* Masks */
#define V_BG0SCRLX_MSK  0xFE00
/* Functions */
/* Macros */
#define M_BG0SCRLX_SET(xoff)    (R_BG0SCRLX &= V_BG0SCRLX_MSK);\
                                (R_BG0SCRLX |= xoff);

/* 
---------------------------------------------------
  IO 0x14 --    R_BG1SCRLX  BG1 Horizontal offset
                scrolling register
---------------------------------------------------     
*/
#define R_BG1SCRLX              *(volatile u16 *)(MEM_IO + 0x14)

/* Constants */
/* Masks */
#define V_BG1SCRLX_MSK  0xFE00
/* Functions */
/* Macros */
#define M_BG1SCRLX_SET(xoff)    (R_BG1SCRLX &= V_BG1SCRLX_MSK);\
                                (R_BG1SCRLX |= xoff);
/* 
---------------------------------------------------
  IO 0x18 --    R_BG2SCRLX  BG2 Horizontal offset
                scrolling register
---------------------------------------------------     
*/
#define R_BG2SCRLX              *(volatile u16 *)(MEM_IO + 0x18)

/* Constants */
/* Masks */
#define V_BG2SCRLX_MSK  0xFE00
/* Functions */
/* Macros */
#define M_BG2SCRLX_SET(xoff)    (R_BG2SCRLX &= V_BG2SCRLX_MSK);\
                                (R_BG2SCRLX |= xoff);
/* 
---------------------------------------------------
  IO 0x1C --    R_BG3SCRLX  BG3 Horizontal offset
                scrolling register
---------------------------------------------------     
*/
#define R_BG3SCRLX              *(volatile u16 *)(MEM_IO + 0x1C)

/* Constants */
/* Masks */
#define V_BG3SCRLX_MSK  0xFE00
/* Functions */
/* Macros */
#define M_BG3SCRLX_SET(xoff)    (R_BG3SCRLX &= V_BG3SCRLX_MSK);\
                                (R_BG3SCRLX |= xoff);


/* 
---------------------------------------------------
  IO 0x12 --    R_BG0SCRLY  BG0 Vertical offset
                scrolling register
---------------------------------------------------     
*/
#define R_BG0SCRLY              *(volatile u16 *)(MEM_IO + 0x12)

/* Constants */
/* Masks */
#define V_BG0SCRLY_MSK  0xFE00
/* Functions */
/* Macros */
#define M_BG0SCRLY_SET(xoff)    (R_BG0SCRLY &= V_BG0SCRLY_MSK);\
                                (R_BG0SCRLY |= xoff);


/* 
---------------------------------------------------
  IO 0x16 --    R_BG1SCRLY  BG1 Vertical offset
                scrolling register
---------------------------------------------------     
*/
#define R_BG1SCRLY              *(volatile u16 *)(MEM_IO + 0x16)

/* Constants */
/* Masks */
#define V_BG1SCRLY_MSK  0xFE00
/* Functions */
/* Macros */
#define M_BG1SCRLY_SET(xoff)    (R_BG1SCRLY &= V_BG1SCRLY_MSK);\
                                (R_BG1SCRLY |= xoff);

/* 
---------------------------------------------------
  IO 0x1A --    R_BG2SCRLY  BG2 Vertical offset
                scrolling register
---------------------------------------------------     
*/
#define R_BG2SCRLY              *(volatile u16 *)(MEM_IO + 0x1A)

/* Constants */
/* Masks */
#define V_BG2SCRLY_MSK  0xFE00
/* Functions */
/* Macros */
#define M_BG2SCRLY_SET(xoff)    (R_BG2SCRLY &= V_BG2SCRLY_MSK);\
                                (R_BG2SCRLY |= xoff);

/* 
---------------------------------------------------
  IO 0x1E --    R_BG3SCRLY  BG3 Vertical offset
                scrolling register
---------------------------------------------------     
*/
#define R_BG3SCRLY              *(volatile u16 *)(MEM_IO + 0x1E)

/* Constants */
/* Masks */
#define V_BG3SCRLY_MSK  0xFE00
/* Functions */
/* Macros */
#define M_BG3SCRLY_SET(xoff)    (R_BG3SCRLY &= V_BG3SCRLY_MSK);\
                                (R_BG3SCRLY |= xoff);


/* 
---------------------------------------------------
  IO 0x20 --    R_BG2ROTDX  BG2 rotation and scaling distance X
                Consider using TOOL_ functions for this.
---------------------------------------------------     
*/
#define R_BG2ROTDX     *(volatile u16 *)(MEM_IO + 0x020)
/* Constants */
/* Masks */
/* Functions */
/* Macros */
#define M_BG2ROTDX_SET(val)  R_BG2ROTDX = CONV_FLOAT_TO_SFP16(val);



/* 
---------------------------------------------------
  IO 0x22 --    R_BG2ROTDMX  BG2 rotation and scaling distance X
                Consider using TOOL_ functions for this.
---------------------------------------------------     
*/
#define R_BG2ROTDMX     *(volatile u16 *)(MEM_IO + 0x022)
/* Constants */
/* Masks */
/* Functions */
/* Macros */
#define M_BG2ROTDMX_SET(val)  R_BG2ROTDMX = CONV_FLOAT_TO_SFP16(val);

/* 
---------------------------------------------------
  IO 0x24 --    R_BG2ROTDY  BG2 rotation and scaling distance Y
                Consider using TOOL_ functions for this.
---------------------------------------------------     
*/
#define R_BG2ROTDY     *(volatile u16 *)(MEM_IO + 0x024)
/* Constants */
/* Masks */
/* Functions */
/* Macros */
#define M_BG2ROTDY_SET(val)  R_BG2ROTDY = CONV_FLOAT_TO_SFP16(val);

/* 
---------------------------------------------------
  IO 0x26 --    R_BG2ROTDMY  BG2 rotation and scaling distance Y
                Consider using TOOL_ functions for this.
---------------------------------------------------     
*/
#define R_BG2ROTDMY     *(volatile u16 *)(MEM_IO + 0x026)
/* Constants */
/* Masks */
/* Functions */
/* Macros */
#define M_BG2ROTDMY_SET(val)  R_BG2ROTDMY = CONV_FLOAT_TO_SFP16(val);

/* 
---------------------------------------------------
  IO 0x30 --    R_BG3ROTDX  BG3 rotation and scaling distance X
                Consider using TOOL_ functions for this.
---------------------------------------------------     
*/
#define R_BG3ROTDX     *(volatile u16 *)(MEM_IO + 0x030)
/* Constants */
/* Masks */
/* Functions */
/* Macros */
#define M_BG3ROTDX_SET(val)  R_BG3ROTDX = CONV_FLOAT_TO_SFP16(val);

/* 
---------------------------------------------------
  IO 0x32 --    R_BG3ROTDMX  BG3 rotation and scaling distance X
                Consider using TOOL_ functions for this.
---------------------------------------------------     
*/
#define R_BG3ROTDMX     *(volatile u16 *)(MEM_IO + 0x032)
/* Constants */
/* Masks */
/* Functions */
/* Macros */
#define M_BG3ROTDMX_SET(val)  R_BG3ROTDMX = CONV_FLOAT_TO_SFP16(val);

/* 
---------------------------------------------------
  IO 0x34 --    R_BG3ROTDY  BG3 rotation and scaling distance Y
                Consider using TOOL_ functions for this.
---------------------------------------------------     
*/
#define R_BG3ROTDY     *(volatile u16 *)(MEM_IO + 0x034)
/* Constants */
/* Masks */
/* Functions */
/* Macros */
#define M_BG3ROTDY_SET(val)  R_BG3ROTDY = CONV_FLOAT_TO_SFP16(val);

/* 
---------------------------------------------------
  IO 0x36 --    R_BG3ROTDMY  BG3 rotation and scaling distance Y
                Consider using TOOL_ functions for this.
---------------------------------------------------     
*/
#define R_BG3ROTDMY     *(volatile u16 *)(MEM_IO + 0x036)
/* Constants */
/* Masks */
/* Functions */
/* Macros */
#define M_BG3ROTDMY_SET(val)  R_BG3ROTDMY = CONV_FLOAT_TO_SFP16(val);



/* 
---------------------------------------------------
  IO 0x28 --    R_BG2ROTX  BG2 rotation and scaling reference
                point X coordinate.
                This register actually spans 2 regs in HW, to
                allow for the following format: 
                1,                19,              8
                sign bit          integer portion  fractional

                remark: includes Reg 0x2A (HighWord of this value)
                Consider using TOOL_ functions for this.
---------------------------------------------------     
*/

#define R_BG2ROTX     *(volatile u32 *)(MEM_IO + 0x028)
/* Constants */
/* Masks */
/* Functions */
/* Macros */
#define M_BG2ROTX_SET(val)  R_BG2ROTX = CONV_FLOAT_TO_SFP32(val);

/* 
---------------------------------------------------
  IO 0x2C --    R_BG2ROTY  BG2 rotation and scaling reference
                point Y coordinate.
                This register actually spans 2 regs in HW, to
                allow for the following format: 
                1,                19,              8
                sign bit          integer portion  fractional

                remark: includes Reg 0x2E (HighWord of this value)
                Consider using TOOL_ functions for this.
---------------------------------------------------     
*/

#define R_BG2ROTY     *(volatile u32 *)(MEM_IO + 0x02C)
/* Constants */
/* Masks */
/* Functions */
/* Macros */
#define M_BG2ROTY_SET(val)  R_BG2ROTY = CONV_FLOAT_TO_SFP32(val);

/* 
---------------------------------------------------
  IO 0x38 --    R_BG3ROTX  BG3 rotation and scaling reference
                point X coordinate.
                This register actually spans 2 regs in HW, to
                allow for the following format: 
                1,                19,              8
                sign bit          integer portion  fractional

                remark: includes Reg 0x3A (HighWord of this value)
                Consider using TOOL_ functions for this.
---------------------------------------------------     
*/

#define R_BG3ROTX     *(volatile u32 *)(MEM_IO + 0x038)
/* Constants */
/* Masks */
/* Functions */
/* Macros */
#define M_BG3ROTX_SET(val)  R_BG3ROTX = CONV_FLOAT_TO_SFP32(val);

/* 
---------------------------------------------------
  IO 0x3C --    R_BG3ROTY  BG3 rotation and scaling reference
                point Y coordinate.
                This register actually spans 2 regs in HW, to
                allow for the following format: 
                1,                19,              8
                sign bit          integer portion  fractional

                remark: includes Reg 0x3E (HighWord of this value)
                Consider using TOOL_ functions for this.
---------------------------------------------------     
*/

#define R_BG3ROTY     *(volatile u32 *)(MEM_IO + 0x03C)
/* Constants */
/* Masks */
/* Functions */
/* Macros */
#define M_BG3ROTY_SET(val)  R_BG3ROTY = CONV_FLOAT_TO_SFP32(val);

/* 
---------------------------------------------------
  IO 0x4c -- R_MOSAIC - Mosaic effect control reg

  This register controls the amount of mosaic applied
  to all BGs and OBJs if the corresponding BGxCNT has
  its mosaic flag turned on

  A Value of 0 in all regs results in a normal 
  display, even with mosaic turned on.

  Since this reg is write only, you can only set ALL
  of the mosaic values at once.
---------------------------------------------------     
*/
#define R_MOSAIC                *(volatile u16 *)(MEM_IO + 0x4C)

/* Constants */
/* Masks */
#define V_MOSAIC_OBJ_VSIZE_MSK  0x0FFF
#define V_MOSAIC_OBJ_HSIZE_MSK  0xF0FF
#define V_MOSAIC_BG_VSIZE_MSK   0xFF0F
#define V_MOSAIC_BG_HSIZE_MSK   0xFFF0

/* Functions */
/* Macros */
#define M_MOSAIC_SET(bgh,bgv,objh,objv)     (R_MOSAIC = bgh | (bgv<<4) |(objh<<8) |(objv<<12) );
/* 
---------------------------------------------------
  IO 0x40 -- R_WIN0X  Window 0 X Positions

  Holds both left and right xpos

---------------------------------------------------     
*/
#define R_WIN0X         *(volatile u16 *)(MEM_IO + 0x40)

/* Constants */
/* Masks */
#define V_WIN0X_LEFT_MSK    0x00FF
#define V_WIN0X_RIGHT_MSK    0xFF00

/* Functions */
/* Macros */
#define M_WIN0X_LEFT_SET(pos)   (R_WIN0X &= V_WIN0X_LEFT_MSK);\
                                (R_WIN0X |= (pos<<8));
#define M_WIN0X_RIGHT_SET(pos)  (R_WIN0X &= V_WIN0X_RIGHT_MSK);\
                                (R_WIN0X |= pos);

/* 
---------------------------------------------------
  IO 0x42 -- R_WIN1X  Window 1 X Positions

  Holds both left and right xpos

---------------------------------------------------     
*/
#define R_WIN1X         *(volatile u16 *)(MEM_IO + 0x42)

/* Constants */
/* Masks */
#define V_WIN1X_LEFT_MSK    0x00FF
#define V_WIN1X_RIGHT_MSK    0xFF00

/* Functions */
/* Macros */
#define M_WIN1X_LEFT_SET(pos)   (R_WIN1X &= V_WIN1X_LEFT_MSK);\
                                (R_WIN1X |= (pos<<8));
#define M_WIN1X_RIGHT_SET(pos)  (R_WIN1X &= V_WIN1X_RIGHT_MSK);\
                                (R_WIN1X |= pos);


/* 
---------------------------------------------------
  IO 0x44 -- R_WIN0Y  Window 0 Y Positions

  Holds both upper and lower ypos

---------------------------------------------------     
*/
#define R_WIN0Y         *(volatile u16 *)(MEM_IO + 0x44)

/* Constants */
/* Masks */
#define V_WIN0Y_UPPER_MSK       0x00FF
#define V_WIN0Y_LOWER_MSK       0xFF00

/* Functions */
/* Macros */
#define M_WIN0Y_UPPER_SET(pos)  (R_WIN0Y &= V_WIN0Y_UPPER_MSK);\
                                (R_WIN0Y |= (pos<<8));
#define M_WIN0Y_LOWER_SET(pos)  (R_WIN0Y &= V_WIN0Y_LOWER_MSK);\
                                (R_WIN0Y |= pos);

/* 
---------------------------------------------------
  IO 0x46 -- R_WIN1Y  Window 1 Y Positions

  Holds both upper and lower ypos

---------------------------------------------------     
*/
#define R_WIN1Y         *(volatile u16 *)(MEM_IO + 0x44)

/* Constants */
/* Masks */
#define V_WIN1Y_UPPER_MSK       0x00FF
#define V_WIN1Y_LOWER_MSK       0xFF00

/* Functions */
/* Macros */
#define M_WIN1Y_UPPER_SET(pos)  (R_WIN1Y &= V_WIN1Y_UPPER_MSK);\
                                (R_WIN1Y |= (pos<<8));
#define M_WIN1Y_LOWER_SET(pos)  (R_WIN1Y &= V_WIN1Y_LOWER_MSK);\
                                (R_WIN1Y |= pos);


/* 
---------------------------------------------------
  IO 0x48 -- R_WININ  Window 0 and 1 display attributes

  Controls which BGs/OBJs appear in the 
  inner area of the window, also switches
  Special Effects.

---------------------------------------------------     
*/
#define R_WININ         *(volatile u16 *)(MEM_IO + 0x48)

/* Constants */
/* Masks */
#define V_WININ_WIN0_DISPLAY_MSK    0xFFE0
#define V_WININ_WIN1_DISPLAY_MSK    0xE0FF

/* Functions */
/* Macros */
#define M_WININ_WIN0_DISPLAY_SET_BG0_ON  (R_WININ &= V_WININ_WIN0_DISPLAY_MSK);\
                                         (R_WININ |= 0x0001);
#define M_WININ_WIN0_DISPLAY_SET_BG1_ON  (R_WININ &= V_WININ_WIN0_DISPLAY_MSK);\
                                         (R_WININ |= 0x0002);
#define M_WININ_WIN0_DISPLAY_SET_BG2_ON  (R_WININ &= V_WININ_WIN0_DISPLAY_MSK);\
                                         (R_WININ |= 0x0004);
#define M_WININ_WIN0_DISPLAY_SET_BG3_ON  (R_WININ &= V_WININ_WIN0_DISPLAY_MSK);\
                                         (R_WININ |= 0x0008);
#define M_WININ_WIN0_DISPLAY_SET_OBJ_ON  (R_WININ &= V_WININ_WIN0_DISPLAY_MSK);\
                                         (R_WININ |= 0x0010);
#define M_WININ_WIN0_DISPLAY_SET_FX_ON   (R_WININ &= V_WININ_WIN0_DISPLAY_MSK);\
                                         (R_WININ |= 0x0020);
#define M_WININ_WIN0_DISPLAY_SET_BG0_OFF (R_WININ &= 0xFFFE);
#define M_WININ_WIN0_DISPLAY_SET_BG1_OFF (R_WININ &= 0xFFFD);
#define M_WININ_WIN0_DISPLAY_SET_BG2_OFF (R_WININ &= 0xFFFB);
#define M_WININ_WIN0_DISPLAY_SET_BG3_OFF (R_WININ &= 0xFFF7);
#define M_WININ_WIN0_DISPLAY_SET_OBJ_OFF (R_WININ &= 0xFFEF);
#define M_WININ_WIN0_DISPLAY_SET_FX_OFF  (R_WININ &= 0xFFDF);


#define M_WININ_WIN1_DISPLAY_SET_BG0_ON  (R_WININ &= V_WININ_WIN1_DISPLAY_MSK);\
                                         (R_WININ |= 0x0100);
#define M_WININ_WIN1_DISPLAY_SET_BG1_ON  (R_WININ &= V_WININ_WIN1_DISPLAY_MSK);\
                                         (R_WININ |= 0x0200);
#define M_WININ_WIN1_DISPLAY_SET_BG2_ON  (R_WININ &= V_WININ_WIN1_DISPLAY_MSK);\
                                         (R_WININ |= 0x0400);
#define M_WININ_WIN1_DISPLAY_SET_BG3_ON  (R_WININ &= V_WININ_WIN1_DISPLAY_MSK);\
                                         (R_WININ |= 0x0800);
#define M_WININ_WIN1_DISPLAY_SET_OBJ_ON  (R_WININ &= V_WININ_WIN1_DISPLAY_MSK);\
                                         (R_WININ |= 0x1000);
#define M_WININ_WIN1_DISPLAY_SET_FX_ON   (R_WININ &= V_WININ_WIN1_DISPLAY_MSK);\
                                         (R_WININ |= 0x2000);
#define M_WININ_WIN1_DISPLAY_SET_BG0_OFF (R_WININ &= 0xFEFF);
#define M_WININ_WIN1_DISPLAY_SET_BG1_OFF (R_WININ &= 0xFDFF);
#define M_WININ_WIN1_DISPLAY_SET_BG2_OFF (R_WININ &= 0xFBFF);
#define M_WININ_WIN1_DISPLAY_SET_BG3_OFF (R_WININ &= 0xF7FF);
#define M_WININ_WIN1_DISPLAY_SET_OBJ_OFF (R_WININ &= 0xEFFF);
#define M_WININ_WIN1_DISPLAY_SET_FX_OFF  (R_WININ &= 0xDFFF);


/* 
---------------------------------------------------
  IO 0x4A -- R_WINOUT  Window 0 and 1 display attributes

  Controls which BGs/OBJs appear outside of
  the area of the window, also switches
  Special Effects.

  In difference to WININ, Win0/1 share the same ON/OFF
  flags, and this reg also controls the OBJ window
---------------------------------------------------     
*/
#define R_WINOUT                *(volatile u16 *)(MEM_IO + 0x4A)

/* Constants */
/* Masks */
#define V_WINOUT_WIN0AND1_DISPLAY_MSK    0xFFE0
#define V_WINOUT_OBJ_DISPLAY_MSK    0xE0FF

/* Functions */
/* Macros */
#define M_WINOUT_WIN0AND1_DISPLAY_SET_BG0_ON    (R_WINOUT &= V_WINOUT_WIN0AND1_DISPLAY_MSK);\
                                                (R_WINOUT |= 0x0001);
#define M_WINOUT_WIN0AND1_DISPLAY_SET_BG1_ON    (R_WINOUT &= V_WINOUT_WIN0AND1_DISPLAY_MSK);\
                                                (R_WINOUT |= 0x0002);
#define M_WINOUT_WIN0AND1_DISPLAY_SET_BG2_ON    (R_WINOUT &= V_WINOUT_WIN0AND1_DISPLAY_MSK);\
                                                (R_WINOUT |= 0x0004);
#define M_WINOUT_WIN0AND1_DISPLAY_SET_BG3_ON    (R_WINOUT &= V_WINOUT_WIN0AND1_DISPLAY_MSK);\
                                                (R_WINOUT |= 0x0008);
#define M_WINOUT_WIN0AND1_DISPLAY_SET_OBJ_ON    (R_WINOUT &= V_WINOUT_WIN0AND1_DISPLAY_MSK);\
                                                (R_WINOUT |= 0x0010);
#define M_WINOUT_WIN0AND1_DISPLAY_SET_FX_ON     (R_WINOUT &= V_WINOUT_WIN0AND1_DISPLAY_MSK);\
                                                (R_WINOUT |= 0x0020);
#define M_WINOUT_WIN0AND1_DISPLAY_SET_BG0_OFF   (R_WINOUT &= 0xFFFE);
#define M_WINOUT_WIN0AND1_DISPLAY_SET_BG1_OFF   (R_WINOUT &= 0xFFFD);
#define M_WINOUT_WIN0AND1_DISPLAY_SET_BG2_OFF   (R_WINOUT &= 0xFFFB);
#define M_WINOUT_WIN0AND1_DISPLAY_SET_BG3_OFF   (R_WINOUT &= 0xFFF7);
#define M_WINOUT_WIN0AND1_DISPLAY_SET_OBJ_OFF   (R_WINOUT &= 0xFFEF);
#define M_WINOUT_WIN0AND1_DISPLAY_SET_FX_OFF    (R_WINOUT &= 0xFFDF);

#define M_WINOUT_OBJ_DISPLAY_SET_BG0_ON         (R_WINOUT &= V_WINOUT_OBJ_DISPLAY_MSK);\
                                                (R_WINOUT |= 0x0100);
#define M_WINOUT_OBJ_DISPLAY_SET_BG1_ON         (R_WINOUT &= V_WINOUT_OBJ_DISPLAY_MSK);\
                                                (R_WINOUT |= 0x0200);
#define M_WINOUT_OBJ_DISPLAY_SET_BG2_ON         (R_WINOUT &= V_WINOUT_OBJ_DISPLAY_MSK);\
                                                (R_WINOUT |= 0x0400);
#define M_WINOUT_OBJ_DISPLAY_SET_BG3_ON         (R_WINOUT &= V_WINOUT_OBJ_DISPLAY_MSK);\
                                                (R_WINOUT |= 0x0800);
#define M_WINOUT_OBJ_DISPLAY_SET_OBJ_ON         (R_WINOUT &= V_WINOUT_OBJ_DISPLAY_MSK);\
                                                (R_WINOUT |= 0x1000);
#define M_WINOUT_OBJ_DISPLAY_SET_FX_ON          (R_WINOUT &= V_WINOUT_OBJ_DISPLAY_MSK);\
                                                (R_WINOUT |= 0x2000);
#define M_WINOUT_OBJ_DISPLAY_SET_BG0_OFF        (R_WINOUT &= 0xFEFF);
#define M_WINOUT_OBJ_DISPLAY_SET_BG1_OFF        (R_WINOUT &= 0xFDFF);
#define M_WINOUT_OBJ_DISPLAY_SET_BG2_OFF        (R_WINOUT &= 0xFBFF);
#define M_WINOUT_OBJ_DISPLAY_SET_BG3_OFF        (R_WINOUT &= 0xF7FF);
#define M_WINOUT_OBJ_DISPLAY_SET_OBJ_OFF        (R_WINOUT &= 0xEFFF);
#define M_WINOUT_OBJ_DISPLAY_SET_FX_OFF         (R_WINOUT &= 0xDFFF);



//---------------------------------------------------
//  Blending Control
//---------------------------------------------------   


#define R_BLDCNT                *(volatile u16 *)(MEM_IO + 0x50)
#define R_BLDALPHA              *(volatile u16 *)(MEM_IO + 0x52)
#define R_BLDY                  *(volatile u16 *)(MEM_IO + 0x54)

//---------------------------------------------------   
// DMA
//---------------------------------------------------   

#define MEM_DMABASE             (MEM_IO + 0x0B0)

/*
---------------------------------------------------
Sound notes:

---------------------------------------------------
*/

/* 
---------------------------------------------------
  IO 0x060 -- R_SND1CNT1
  First control register for GBC-like sound channel
  1. This channel can generate rectangular 
  waveforms with sweep (frequency change) and envelope
  (volume change). Also needs setting of 
  R_SND1CNT2 and R_SND1CNT3 . The sound is output
  when you write the initialization bit of R_SND1CNT3.
  this is autoatically done when using M_SND1CNT3_SETUP
---------------------------------------------------     
*/

#define R_SND1CNT1              *(volatile u16 *)(MEM_IO + 0x60)

/* Constants */
#define V_SND1CNT1_SWEEP_FADEMODE_UP    0x0000
#define V_SND1CNT1_SWEEP_FADEMODE_DOWN  0x0080

/* Masks */
#define V_SND1CNT1_SWEEP_TIME_MASK      0xFF8F
#define V_SND1CNT1_NUM_SWEEPS_MASK      0xFFF8

/* Functions */
/* Macros */
#define M_SND1CNT1_SETUP(sweep_time,num_sweeps,fademode) \
                                                                                                ( R_SND1CNT1 =  (sweep_time << 4) | \
                                                                                                                                (fademode <<3 ) | \
                                                                                                                                 num_sweeps \
                                                                                                );
#define M_SND1CNT1_SWEEP_TIME_SET(x)                    (R_SND1CNT1 &= V_SND1CNT1_SWEEP_TIME_MASK);\
                                                (R_SND1CNT1 |= (x<<4));
#define M_SND1CNT1_NUM_SWEEPS_SET(x)                    (R_SND1CNT1 &= V_SND1CNT1_NUM_SWEEPS_MASK);\
                                                (R_SND1CNT1 |= x);
#define M_SND1CNT1_SWEEP_DIR_SET_ASCENDING              (R_SND1CNT1 &= 0xFF7F);
#define M_SND1CNT1_SWEEP_DIR_SET_DESCENDING             (R_SND1CNT1 |= 0x0080);


/* 
---------------------------------------------------
  IO 0x062 -- R_SND1CNT2
  see R_SND1CNT1 for details
  envelope initial setting 0-15 (mute-full volume)
  length setting is NOT READABLE!
---------------------------------------------------     
*/

#define R_SND1CNT2              *(volatile u16 *)(MEM_IO + 0x62)

/* Constants */
#define V_SND1CNT2_VOL_FADEMODE_UP              0x0800
#define V_SND1CNT2_VOL_FADEMODE_DOWN    0x0000

/* Masks */
#define V_SND1CNT2_INITIAL_ENVELOPE_MASK                0x0FFF
#define V_SND1CNT2_ENVELOPE_NUMSTEPS_MASK               0xF8FF
#define V_SND1CNT2_WAVEFORM_DUTY_MASK                   0xFF3F
#define V_SND1CNT2_SOUND_LEN_MASK                               0xFFC0


/* Functions */
/* Macros */
#define M_SND1CNT2_SETUP(initial_vol,fademode,vol_numstep,snd_len,wave_duty) \
                                                                                                (R_SND1CNT2 =   (initial_vol << 12) | \
                                                                                                                                (fademode << 11) | \
                                                                                                                                (vol_numstep << 8) | \
                                                                                                                                (wave_duty << 6) | \
                                                                                                                                (snd_len) \
                                                                                                );

#define M_SND1CNT2_INITIAL_ENVELOPE_SET(x)              (R_SND1CNT2 &= V_SND1CNT2_INITIAL_ENVELOPE_MASK);\
                                                (R_SND1CNT2 |= (x<<12));
#define M_SND1CNT2_ENVELOPE_NUMSTEPS_SET(x)             (R_SND1CNT2 &= V_SND1CNT2_ENVELOPE_NUMSTEPS_MASK);\
                                                (R_SND1CNT2 |= (x<<8));
#define M_SND1CNT2_WAVEFORM_DUTY_SET(x)                 (R_SND1CNT2 &= V_SND1CNT2_WAVEFORM_DUTY_MASK);\
                                                (R_SND1CNT2 |= (x<<6));
#define M_SND1CNT2_ENVELOPE_DIR_ATTENUATE               (R_SND1CNT2 &= 0xF7FF);
#define M_SND1CNT2_ENVELOPE_DIR_AMPLIFY                 (R_SND1CNT2 |= 0x0800);

/* 
---------------------------------------------------
  IO 0x064 -- R_SND1CNT3
  see R_SND1CNT1 for details
---------------------------------------------------     
*/

#define R_SND1CNT3              *(volatile u16 *)(MEM_IO + 0x64)

/* Constants */
/* Masks */
#define V_SND1CNT3_FREQUENCY_MASK                       0xF800


/* Functions */
/* Macros */
#define M_SND1CNT3_SETUP(frequency,loopmode)    (R_SND1CNT3 = 0x8000 | \
                                                                                                (loopmode << 14) | \
                                                                                                frequency \
                                                                                                );

#define M_SND1CNT3_SOUND_LEN_COUNTDOWN                  (R_SND1CNT3 |= 0x4000);
#define M_SND1CNT3_SOUND_LEN_CONTINOUS                  (R_SND1CNT3 &= 0xBFFF);



/* 
---------------------------------------------------
  IO 0x068 -- R_SND2CNT1
  Sound2 envelope control.

  see R_SND1CNT1 for details
  envelope initial setting 0-15 (mute-full volume)
  length setting is NOT READABLE!
---------------------------------------------------     
*/

#define R_SND2CNT1              *(volatile u16 *)(MEM_IO + 0x68)

/* Constants */
#define V_SND2CNT1_VOL_FADEMODE_UP              0x0800
#define V_SND2CNT1_VOL_FADEMODE_DOWN    0x0000

/* Masks */
#define V_SND2CNT1_INITIAL_ENVELOPE_MASK                0x0FFF
#define V_SND2CNT1_ENVELOPE_NUMSTEPS_MASK               0xF8FF
#define V_SND2CNT1_WAVEFORM_DUTY_MASK                   0xFF3F
#define V_SND2CNT1_SOUND_LEN_MASK                               0xFFC0


/* Functions */
/* Macros */
#define M_SND2CNT1_SETUP(initial_vol,fademode,vol_numstep,snd_len,wave_duty) \
                                                                                                (R_SND2CNT1 =   (initial_vol << 12) | \
                                                                                                                                (fademode << 11) | \
                                                                                                                                (vol_numstep << 8) | \
                                                                                                                                (wave_duty << 6) | \
                                                                                                                                (snd_len) \
                                                                                                );

#define M_SND2CNT1_INITIAL_ENVELOPE_SET(x)              (R_SND2CNT1 &= V_SND2CNT1_INITIAL_ENVELOPE_MASK);\
                                                (R_SND2CNT1 |= (x<<12));
#define M_SND2CNT1_ENVELOPE_NUMSTEPS_SET(x)             (R_SND2CNT1 &= V_SND2CNT1_ENVELOPE_NUMSTEPS_MASK);\
                                                (R_SND2CNT1 |= (x<<8));
#define M_SND2CNT1_WAVEFORM_DUTY_SET(x)                 (R_SND2CNT1 &= V_SND2CNT1_WAVEFORM_DUTY_MASK);\
                                                (R_SND2CNT1 |= (x<<6));
#define M_SND2CNT1_ENVELOPE_DIR_ATTENUATE               (R_SND2CNT1 &= 0xF7FF);
#define M_SND2CNT1_ENVELOPE_DIR_AMPLIFY                 (R_SND2CNT1 |= 0x0800);

/* 
---------------------------------------------------
  IO 0x06C -- R_SND2CNT2
  Sound2 frequency control and initialization
  see R_SND1CNT1 for details
---------------------------------------------------     
*/

#define R_SND2CNT2              *(volatile u16 *)(MEM_IO + 0x6C)

/* Constants */
/* Masks */
#define V_SND2CNT2_FREQUENCY_MASK                       0xF800


/* Functions */
/* Macros */
#define M_SND2CNT2_SETUP(frequency,loopmode)    (R_SND2CNT2 = 0x8000 | \
                                                                                                (loopmode << 14) | \
                                                                                                frequency \
                                                                                                );

#define M_SND2CNT2_SOUND_LEN_COUNTDOWN                  (R_SND2CNT2 |= 0x4000);
#define M_SND2CNT2_SOUND_LEN_CONTINOUS                  (R_SND2CNT2 &= 0xBFFF);



/* 
---------------------------------------------------
  IO 0x070 -- R_SND3CNT1
  This AGB sound channel outputs wave data from waveform
  RAM, as CGB was already able to. The amount of waveform 
  data that can be selected is doubled to 16*16bits, divided
  into 2 banks of 8*16 bits. These can be written by the user
  by accessing MEM_IO+0x90. After writing the 8 first words,
  you can perform bank switching, then, you can write the second
  batch of data into the same memory space. 

  Be aware that the bank NOT specified in this register is the
  one that you are writing to.

  The waveform can either be played from the first/second
  4*16 bits (bank mode) or from the whole 8*16 bits. If you
  set it to double bank output mode, the specified sound bank
  is played first, then the other one.
---------------------------------------------------     
*/

#define R_SND3CNT1              *(volatile u16 *)(MEM_IO + 0x70)

/* Constants */
/* Masks */
/* Functions */
/* Macros */
#define M_SND3CNT1_OUTPUT_ON                        (R_SND3CNT1 |= 0x0080);
#define M_SND3CNT1_OUTPUT_OFF                       (R_SND3CNT1 &= 0xFF7F);
#define M_SND3CNT1_BANK_SET_1                       (R_SND3CNT1 |= 0x0040);
#define M_SND3CNT1_BANK_SET_0                       (R_SND3CNT1 &= 0xFFBF);
#define M_SND3CNT1_WAVEFORM_SINGLEBANK      (R_SND3CNT1 |= 0x0020);
#define M_SND3CNT1_WAVEFORM_DOUBLEBANK      (R_SND3CNT1 &= 0xFFDF);

/* 
---------------------------------------------------
  IO 0x072 -- R_SND3CNT2
  Sound3 volume and length settings.
  See R_SND3CNT1 for more information
  FORCE_75PERC = Force a specific envelope. Usually, set this 0.
  OUTPUT_LEVEL = 0 Mute
                 1 Normal output
                 2 Shift contents right 1 bit (4 bit blocks in WAV data)
                 3 Shift contents right 2 bit (4 bit blocks in WAV data)
  LENGTH       = Set to 0 for 1 sec long sound... 255 for 1/256 sec sound 
---------------------------------------------------     
*/

#define R_SND3CNT2              *(volatile u16 *)(MEM_IO + 0x72)

/* Constants */
/* Masks */
/* Functions */
/* Macros */
#define M_SND3CNT2_SETUP(force75perc, \
                         outputlevel, \
                         soundlen) \
                                            (R_SND3CNT2 =   (force75perc<<15) | \
                                                                                                            (outputlevel << 13) | \
                                                                                                            frequency \
                                                                                                            );

/* 
---------------------------------------------------
  IO 0x074 -- R_SND3CNT3
  Sound3 frequency and initialization settings.
---------------------------------------------------
*/

#define R_SND3CNT3              *(volatile u16 *)(MEM_IO + 0x74)

/* Constants */
/* Masks */
/* Functions */
/* Macros */
#define M_SND3CNT3_SETUP(frequency,loopmode)    (R_SND3CNT3 = 0x8000 | \
                                                                                                (loopmode << 14) | \
                                                                                                frequency \
                                                                                                );



/* 
---------------------------------------------------
  IO 0x090-0x09F -- R_SND3WAVX
  Sound3 Waveform RAM. Range is from 0x90 to 09F.
  Write to this is performed by setting the bank 
  you do NOT want to write to in SND3CNT1 first,
  and then perform the write. This is implemented
  like this so you can write one bank while playing the
  other one. So, set Bank 1 if you want to write Bank 0
  and vice versa. Not setting the bank will produce
  weird behaviour obviously.

  Allowed values for the x/regno parameter in this are
  0-7 (since there are 8*16 bits per bank to write to)

  Alsosee R_SND3CNT1 dormore details on this.
---------------------------------------------------
*/

#define R_SND3WAVX(x)           *(volatile u16 *)(MEM_IO + 0x90 + (x*2))

/* Constants */
/* Masks */
/* Functions */
/* Macros */
#define M_SND3WAVX_WRITE(regno,data)    (R_SND3WAVX(regno) = data);




/* 
---------------------------------------------------
  IO 0x078 -- R_SND4CNT1
  Sound4 envelope and lenght settings
  Sound4 is a circuit that generates white noise.
  env_ini      = initial volume (0-15)
  env_dir      = 0=attenuate 1=amplify
  env_numsteps = number of envelope steps (0-7)
  soundlen     = 0-63 (0=1sec ... 63=1/256 sec)
---------------------------------------------------
*/

#define R_SND4CNT1              *(volatile u16 *)(MEM_IO + 0x78)

/* Constants */
/* Masks */
/* Functions */
/* Macros */
#define M_SND4CNT1_SETUP(env_ini, \
                         env_dir, \
                         env_numsteps, \
                         sound_len)\
                                                (R_SND4CNT1 =  \
                                                                                                (env_ini << 12) | \
                                                                                                (env_dir << 11) | \
                                                                                                (env_numsteps << 8) | \
                                                                                                sound_len \
                                                                                                );


/* 
---------------------------------------------------
  IO 0x07C -- R_SND4CNT2
  Sound4 counter and initialization settings
  Sound4 is a circuit that generates white noise.
  counter shift = 0x00 - 0x0D
  counter step  = 0=15 steps 1=7 steps
  div_ratio     = n/a
---------------------------------------------------
*/

#define R_SND4CNT2              *(volatile u16 *)(MEM_IO + 0x7C)

/* Constants */
/* Masks */
/* Functions */
/* Macros */
#define M_SND4CNT2_SETUP(counter_shift, \
                         counter_step, \
                         div_ratio, \
                         loopmode)      \
                                                (R_SND4CNT2 = 0x8000 | \
                                                                                                (loopmode << 14) | \
                                                                                                (counter_shift << 4) | \
                                                                                                (counter_step << 3) | \
                                                                                                div_ratio \
                                                                                                );


/* 
---------------------------------------------------
  IO 0x080 -- R_SNDCNT1
  Do not confuse this with SNDxCNT1, this reg is
  the overall sound control.
---------------------------------------------------     
*/

#define R_SNDCNT1               *(volatile u16 *)(MEM_IO + 0x80)

/* Constants */
/* Masks */
#define V_SNDCNT1_VOLUME_LEFT_MASK                      0xFF8F
#define V_SNDCNT1_VOLUME_RIGHT_MASK                     0xFFF8


/* Functions */
/* Macros */
#define M_SNDCNT1_VOLUME_LEFT_SET(x)            (R_SNDCNT1 &= V_SNDCNT1_VOLUME_LEFT_MASK);\
                                            (R_SNDCNT1 |= (x<<4));
#define M_SNDCNT1_VOLUME_RIGHT_SET(x)           (R_SNDCNT1 &= V_SNDCNT1_VOLUME_RIGHT_MASK);\
                                            (R_SNDCNT1 |= x);

#define M_SNDCNT1_OUTPUT_LEFT_ALL_ON            (R_SNDCNT1 |= 0xF000);
#define M_SNDCNT1_OUTPUT_LEFT_SOUND1_ON         (R_SNDCNT1 |= 0x1000);
#define M_SNDCNT1_OUTPUT_LEFT_SOUND2_ON         (R_SNDCNT1 |= 0x2000);
#define M_SNDCNT1_OUTPUT_LEFT_SOUND3_ON         (R_SNDCNT1 |= 0x4000);
#define M_SNDCNT1_OUTPUT_LEFT_SOUND4_ON         (R_SNDCNT1 |= 0x8000);
#define M_SNDCNT1_OUTPUT_LEFT_ALL_OFF           (R_SNDCNT1 &= 0x0FFF);
#define M_SNDCNT1_OUTPUT_LEFT_SOUND1_OFF        (R_SNDCNT1 &= 0xEFFF);
#define M_SNDCNT1_OUTPUT_LEFT_SOUND2_OFF        (R_SNDCNT1 &= 0xDFFF);
#define M_SNDCNT1_OUTPUT_LEFT_SOUND3_OFF        (R_SNDCNT1 &= 0xBFFF);
#define M_SNDCNT1_OUTPUT_LEFT_SOUND4_OFF        (R_SNDCNT1 &= 0x7FFF);
#define M_SNDCNT1_OUTPUT_RIGHT_ALL_ON           (R_SNDCNT1 |= 0x0F00);
#define M_SNDCNT1_OUTPUT_RIGHT_SOUND1_ON        (R_SNDCNT1 |= 0x0100);
#define M_SNDCNT1_OUTPUT_RIGHT_SOUND2_ON        (R_SNDCNT1 |= 0x0200);
#define M_SNDCNT1_OUTPUT_RIGHT_SOUND3_ON        (R_SNDCNT1 |= 0x0400);
#define M_SNDCNT1_OUTPUT_RIGHT_SOUND4_ON        (R_SNDCNT1 |= 0x0800);
#define M_SNDCNT1_OUTPUT_RIGHT_ALL_OFF          (R_SNDCNT1 &= 0xF0FF);
#define M_SNDCNT1_OUTPUT_RIGHT_SOUND1_OFF       (R_SNDCNT1 &= 0xFEFF);
#define M_SNDCNT1_OUTPUT_RIGHT_SOUND2_OFF       (R_SNDCNT1 &= 0xFDFF);
#define M_SNDCNT1_OUTPUT_RIGHT_SOUND3_OFF       (R_SNDCNT1 &= 0xFBFF);
#define M_SNDCNT1_OUTPUT_RIGHT_SOUND4_OFF       (R_SNDCNT1 &= 0xF7FF);

/* 
---------------------------------------------------
  IO 0x084 -- R_SNDCNT2
  Do not confuse this with SNDxCNT2, this reg is
  the overall sound control.
---------------------------------------------------     
*/

#define R_SNDCNT2               *(volatile u16 *)(MEM_IO + 0x84)

/* Constants */
/* Masks */
/* Functions */
#define F_SNDCNT2_SOUND1_ON        (R_SNDCNT2 & 0x0001)
#define F_SNDCNT2_SOUND2_ON        (R_SNDCNT2 & 0x0002)
#define F_SNDCNT2_SOUND3_ON        (R_SNDCNT2 & 0x0004)
#define F_SNDCNT2_SOUND4_ON        (R_SNDCNT2 & 0x0008)

/* Macros */
#define M_SNDCNT2_SOUND_MASTER_ON   (R_SNDCNT2 |= 0x0080);
#define M_SNDCNT2_SOUND_MASTER_OFF  (R_SNDCNT2 &= 0xFF7F);
#define M_SNDCNT2_SOUND1_ON         (R_SNDCNT2 |= 0x0001);
#define M_SNDCNT2_SOUND2_ON         (R_SNDCNT2 |= 0x0002);
#define M_SNDCNT2_SOUND3_ON         (R_SNDCNT2 |= 0x0004);
#define M_SNDCNT2_SOUND4_ON         (R_SNDCNT2 |= 0x0008);
#define M_SNDCNT2_SOUND1_OFF        (R_SNDCNT2 &= 0xFFFE);
#define M_SNDCNT2_SOUND2_OFF        (R_SNDCNT2 &= 0xFFFD);
#define M_SNDCNT2_SOUND3_OFF        (R_SNDCNT2 &= 0xFFFB);
#define M_SNDCNT2_SOUND4_OFF        (R_SNDCNT2 &= 0xFFF7);


/* 
---------------------------------------------------
  IO 0x100 --   R_TIM0COUNT
  This holds the value TimerX is counting up to (from
  0) before firing an interrupt. Attributes in
  TIMXCNT affect the counting process.
  After you write to this register, this value is saved
  in the hardware and, if the tmer is running, counts 
  down. 

  Once it reaches 0, if enabled, interrupts are fired,
  and the value you set before is restored back from the hardware
  automatically. 

  To overwrite the current value, write a new
  value into it. If you read from this register, you will get the
  value that the timer is currently at when downcounting. 

  Thx to costis for this info.
---------------------------------------------------     
*/
#define R_TIM0COUNT             *(volatile u16 *)(MEM_IO + 0x100)

/* Functions */
#define F_TIM0COUNT_GET_CURRENT_VALUE  (R_TIM0COUNT)

/* Macros */
#define M_TIM0COUNT_SET(value)  (R_TIM0COUNT=value);

/* 
---------------------------------------------------
  IO 0x102 --   R_TIM0CNT
  Controls Attributes of the timer counting process

  Speed select:
  Setting -- Countup interval
  00         59,595 nanos (running 16,78MHz)
  01         3,841  micrs (running clock/64)
  10         15,256 micrs (running clock/256)
  11         61,025 micrs (running clock/1024)
---------------------------------------------------     
*/
#define R_TIM0CNT               *(volatile u16 *)(MEM_IO + 0x102)

/* Masks */
#define V_TIM0CNT_SPEED_SELECT_MSK  0xFFFC
/* Macros */
#define M_TIM0CNT_SPEED_SELECT_SET(value)   (R_TIM0CNT &= V_TIM0CNT_SPEED_SELECT_MSK);\
                                            (R_TIM0CNT |= value);
#define M_TIM0CNT_TIMER_START               (R_TIM0CNT |= 0x0080);
#define M_TIM0CNT_TIMER_STOP                (R_TIM0CNT &= 0xFF7F);
#define M_TIM0CNT_IRQ_ENABLE                (R_TIM0CNT |= 0x0040);
#define M_TIM0CNT_IRQ_DISABLE               (R_TIM0CNT &= 0xFFBF);

/* 
---------------------------------------------------
  IO 0x104 --   R_TIM1COUNT
  This holds the value TimerX is counting up to (from
  0) before firing an interrupt. Attributes in
  TIMXCNT affect the counting process
  After you write to this register, this value is saved
  in the hardware and, if the tmer is running, counts 
  down. 

  Once it reaches 0, if enabled, interrupts are fired,
  and the value you set before is restored back from the hardware
  automatically. 

  To overwrite the current value, write a new
  value into it. If you read from this register, you will get the
  value that the timer is currently at when downcounting. 

  Thx to costis for this info.
---------------------------------------------------     
*/
#define R_TIM1COUNT             *(volatile u16 *)(MEM_IO + 0x104)

/* Functions */
#define F_TIM1COUNT_GET_CURRENT_VALUE  (R_TIM1COUNT)

/* Macros */
#define M_TIM1COUNT_SET(value)  (R_TIM1COUNT=value);

/* 
---------------------------------------------------
  IO 0x106 --   R_TIM1CNT
  Controls Attributes of the timer counting process

  Speed select:
  Setting -- Countup interval
  00         59,595 nanos (running 16,78MHz)
  01         3,841  micrs (running clock/64)
  10         15,256 micrs (running clock/256)
  11         61,025 micrs (running clock/1024)
---------------------------------------------------     
*/
#define R_TIM1CNT               *(volatile u16 *)(MEM_IO + 0x102)

/* Masks */
#define V_TIM1CNT_SPEED_SELECT_MSK  0xFFFC
/* Macros */
#define M_TIM1CNT_SPEED_SELECT_SET(value)   (R_TIM1CNT &= V_TIM1CNT_SPEED_SELECT_MSK);\
                                            (R_TIM1CNT |= value);
#define M_TIM1CNT_TIMER_START               (R_TIM1CNT |= 0x0080);
#define M_TIM1CNT_TIMER_STOP                (R_TIM1CNT &= 0xFF7F);
#define M_TIM1CNT_IRQ_ENABLE                (R_TIM1CNT |= 0x0040);
#define M_TIM1CNT_IRQ_DISABLE               (R_TIM1CNT &= 0xFFBF);

/* 
---------------------------------------------------
  IO 0x108 --   R_TIM2COUNT
  This holds the value TimerX is counting up to (from
  0) before firing an interrupt. Attributes in
  TIMXCNT affect the counting process
  After you write to this register, this value is saved
  in the hardware and, if the tmer is running, counts 
  down. 

  Once it reaches 0, if enabled, interrupts are fired,
  and the value you set before is restored back from the hardware
  automatically. 

  To overwrite the current value, write a new
  value into it. If you read from this register, you will get the
  value that the timer is currently at when downcounting. 

  Thx to costis for this info.
---------------------------------------------------     
*/
#define R_TIM2COUNT             *(volatile u16 *)(MEM_IO + 0x108)

/* Functions */
#define F_TIM2COUNT_GET_CURRENT_VALUE  (R_TIM2COUNT)

/* Macros */
#define M_TIM2COUNT_SET(value)  (R_TIM2COUNT=value);

/* 
---------------------------------------------------
  IO 0x10A --   R_TIM2CNT
  Controls Attributes of the timer counting process

  Speed select:
  Setting -- Countup interval
  00         59,595 nanos (running 16,78MHz)
  01         3,841  micrs (running clock/64)
  10         15,256 micrs (running clock/256)
  11         61,025 micrs (running clock/1024)
---------------------------------------------------     
*/
#define R_TIM2CNT               *(volatile u16 *)(MEM_IO + 0x102)

/* Masks */
#define V_TIM2CNT_SPEED_SELECT_MSK  0xFFFC
/* Macros */
#define M_TIM2CNT_SPEED_SELECT_SET(value)   (R_TIM2CNT &= V_TIM2CNT_SPEED_SELECT_MSK);\
                                            (R_TIM2CNT |= value);
#define M_TIM2CNT_TIMER_START               (R_TIM2CNT |= 0x0080);
#define M_TIM2CNT_TIMER_STOP                (R_TIM2CNT &= 0xFF7F);
#define M_TIM2CNT_IRQ_ENABLE                (R_TIM2CNT |= 0x0040);
#define M_TIM2CNT_IRQ_DISABLE               (R_TIM2CNT &= 0xFFBF);

/* 
---------------------------------------------------
  IO 0x10C --   R_TIM3COUNT
  This holds the value TimerX is counting up to (from
  0) before firing an interrupt. Attributes in
  TIMXCNT affect the counting process
  After you write to this register, this value is saved
  in the hardware and, if the tmer is running, counts 
  down. 

  Once it reaches 0, if enabled, interrupts are fired,
  and the value you set before is restored back from the hardware
  automatically. 

  To overwrite the current value, write a new
  value into it. If you read from this register, you will get the
  value that the timer is currently at when downcounting. 

  Thx to costis for this info.
---------------------------------------------------     
*/
#define R_TIM3COUNT             *(volatile u16 *)(MEM_IO + 0x10C)

/* Functions */
#define F_TIM3COUNT_GET_CURRENT_VALUE  (R_TIM3COUNT)

/* Macros */
#define M_TIM3COUNT_SET(value)  (R_TIM3COUNT=value);


/* 
---------------------------------------------------
  IO 0x10E --   R_TIM3CNT
  Controls Attributes of the timer counting process

  Speed select:
  Setting -- Countup interval
  00         59,595 nanos (running 16,78MHz)
  01         3,841  micrs (running clock/64)
  10         15,256 micrs (running clock/256)
  11         61,025 micrs (running clock/1024)
---------------------------------------------------     
*/
#define R_TIM3CNT               *(volatile u16 *)(MEM_IO + 0x10E)

/* Masks */
#define V_TIM3CNT_SPEED_SELECT_MSK  0xFFFC
/* Macros */
#define M_TIM3CNT_SPEED_SELECT_SET(value)   (R_TIM3CNT &= V_TIM3CNT_SPEED_SELECT_MSK);\
                                            (R_TIM3CNT |= value);
#define M_TIM3CNT_TIMER_START               (R_TIM3CNT |= 0x0080);
#define M_TIM3CNT_TIMER_STOP                (R_TIM3CNT &= 0xFF7F);
#define M_TIM3CNT_IRQ_ENABLE                (R_TIM3CNT |= 0x0040);
#define M_TIM3CNT_IRQ_DISABLE               (R_TIM3CNT &= 0xFFBF);

/* 
---------------------------------------------------
  IO 0x130 --   R_CTRLINPUT

  This register holds the values of the controller
  buttons. 1 means not pressed, 0 means pressed.
---------------------------------------------------     
*/
#define R_CTRLINPUT             *(volatile u16 *)(MEM_IO + 0x130)

/* Constants */
/* Masks */
#define V_CTRLINPUT_MSK  0xFC00
/* Functions */
#define F_CTRLINPUT_A_PRESSED        (~R_CTRLINPUT & 0x0001)
#define F_CTRLINPUT_B_PRESSED       ((~R_CTRLINPUT & 0x0002)>>1)
#define F_CTRLINPUT_SELECT_PRESSED  ((~R_CTRLINPUT & 0x0004)>>2)
#define F_CTRLINPUT_START_PRESSED   ((~R_CTRLINPUT & 0x0008)>>3)
#define F_CTRLINPUT_RIGHT_PRESSED   ((~R_CTRLINPUT & 0x0010)>>4)
#define F_CTRLINPUT_LEFT_PRESSED    ((~R_CTRLINPUT & 0x0020)>>5)
#define F_CTRLINPUT_UP_PRESSED      ((~R_CTRLINPUT & 0x0040)>>6)
#define F_CTRLINPUT_DOWN_PRESSED    ((~R_CTRLINPUT & 0x0080)>>7)
#define F_CTRLINPUT_R_PRESSED       ((~R_CTRLINPUT & 0x0100)>>8)
#define F_CTRLINPUT_L_PRESSED       ((~R_CTRLINPUT & 0x0200)>>9)
/* Macros */




/* 
---------------------------------------------------
  IO 0x132 -- R_CTRLINT  Controller Interrupt Request Register

  Will fire a controller interrupt if the flagged 
  conditions are met. You can flag any key, and give
  the interrupt condition of AND (all specified keys
  pressed) or OR (any specified key pressed) when 
  choosing multiple keys. 
---------------------------------------------------     
*/
#define R_CTRLINT               *(volatile u16 *)(MEM_IO + 0x132)

/* Constants */
/* Masks */
#define V_CTRLINT_MSK  0xFC00
/* Functions */
/* Macros */
#define M_CTRLINT_IRQ_DISABLE       (R_CTRLINT &= 0xBFFF);
#define M_CTRLINT_IRQ_ENABLE        (R_CTRLINT |= 0x4000);

#define M_CTRLINT_IRQ_COND_AND      (R_CTRLINT |= 0x8000);
#define M_CTRLINT_IRQ_COND_OR       (R_CTRLINT &= 0x7FFF);

#define M_CTRLINT_KEY_SET_A         (R_CTRLINT |= 0x0001);
#define M_CTRLINT_KEY_SET_B         (R_CTRLINT |= 0x0002);
#define M_CTRLINT_KEY_SET_SELECT    (R_CTRLINT |= 0x0004);
#define M_CTRLINT_KEY_SET_START     (R_CTRLINT |= 0x0008);
#define M_CTRLINT_KEY_SET_RIGHT     (R_CTRLINT |= 0x0010);
#define M_CTRLINT_KEY_SET_LEFT      (R_CTRLINT |= 0x0020);
#define M_CTRLINT_KEY_SET_UP        (R_CTRLINT |= 0x0040);
#define M_CTRLINT_KEY_SET_DOWN      (R_CTRLINT |= 0x0080);
#define M_CTRLINT_KEY_SET_R         (R_CTRLINT |= 0x0100);
#define M_CTRLINT_KEY_SET_L         (R_CTRLINT |= 0x0200);

#define M_CTRLINT_KEY_CLR_A         (R_CTRLINT &= 0xFFFE);
#define M_CTRLINT_KEY_CLR_B         (R_CTRLINT &= 0xFFFD);
#define M_CTRLINT_KEY_CLR_SELECT    (R_CTRLINT &= 0xFFFB);
#define M_CTRLINT_KEY_CLR_START     (R_CTRLINT &= 0xFFF7);
#define M_CTRLINT_KEY_CLR_RIGHT     (R_CTRLINT &= 0xFFEF);
#define M_CTRLINT_KEY_CLR_LEFT      (R_CTRLINT &= 0xFFDF);
#define M_CTRLINT_KEY_CLR_UP        (R_CTRLINT &= 0xFFBF);
#define M_CTRLINT_KEY_CLR_DOWN      (R_CTRLINT &= 0xFF7F);
#define M_CTRLINT_KEY_CLR_R         (R_CTRLINT &= 0xFEFF);
#define M_CTRLINT_KEY_CLR_L         (R_CTRLINT &= 0xFDFF);





/* 
---------------------------------------------------
  IO 0x208 -- R_INTMST  Interrupt Enable Master Register

  If this register is set to 0, NO IRQs are executed
  If set to 1, normal IRQ operation happens
---------------------------------------------------     
*/
#define R_INTMST                *(volatile u16 *)(MEM_IO + 0x208)

/* Constants */
/* Masks */
/* Functions */
#define F_INTMST_ENABLED     (R_INTMST & 0x1)
/* Macros */
#define M_INTMST_ENABLE      (R_INTMST |= 1);
#define M_INTMST_DISABLE     (R_INTMST &= 0);


/* 
---------------------------------------------------
  IO 0x200 -- R_INTENA  Interrupt Enable Register

  In this register, you can set up all interrupts
  manually, if they should occur or not.
---------------------------------------------------     
*/
#define R_INTENA                *(volatile u16 *)(MEM_IO + 0x200)

/* Constants */
/* Masks */
/* Functions */
/* Macros */
#define M_INTENA_VBL_ENABLE       (R_INTENA |= 0x0001);
#define M_INTENA_HBL_ENABLE       (R_INTENA |= 0x0002);
#define M_INTENA_VCNT_ENABLE      (R_INTENA |= 0x0004);
#define M_INTENA_TIM0_ENABLE      (R_INTENA |= 0x0008);
#define M_INTENA_TIM1_ENABLE      (R_INTENA |= 0x0010);
#define M_INTENA_TIM2_ENABLE      (R_INTENA |= 0x0020);
#define M_INTENA_TIM3_ENABLE      (R_INTENA |= 0x0040);
#define M_INTENA_SIO_ENABLE       (R_INTENA |= 0x0080);
#define M_INTENA_DMA0_ENABLE      (R_INTENA |= 0x0100);
#define M_INTENA_DMA1_ENABLE      (R_INTENA |= 0x0200);
#define M_INTENA_DMA2_ENABLE      (R_INTENA |= 0x0400);
#define M_INTENA_DMA3_ENABLE      (R_INTENA |= 0x0800);
#define M_INTENA_KEY_ENABLE      (R_INTENA |= 0x1000);
#define M_INTENA_CART_ENABLE      (R_INTENA |= 0x2000);

#define M_INTENA_VBL_DISABLE       (R_INTENA &= 0xFFFE);
#define M_INTENA_HBL_DISABLE       (R_INTENA &= 0xFFFD);
#define M_INTENA_VCNT_DISABLE      (R_INTENA &= 0xFFFB);
#define M_INTENA_TIM0_DISABLE      (R_INTENA &= 0xFFF7);
#define M_INTENA_TIM1_DISABLE      (R_INTENA &= 0xFFEF);
#define M_INTENA_TIM2_DISABLE      (R_INTENA &= 0xFFDF);
#define M_INTENA_TIM3_DISABLE      (R_INTENA &= 0xFFBF);
#define M_INTENA_SIO_DISABLE       (R_INTENA &= 0xFF7F);
#define M_INTENA_DMA0_DISABLE      (R_INTENA &= 0xFEFF);
#define M_INTENA_DMA1_DISABLE      (R_INTENA &= 0xFDFF);
#define M_INTENA_DMA2_DISABLE      (R_INTENA &= 0xFBFF);
#define M_INTENA_DMA3_DISABLE      (R_INTENA &= 0xF7FF);
#define M_INTENA_KEY_DISABLE      (R_INTENA &= 0xEFFF);
#define M_INTENA_CART_DISABLE      (R_INTENA &= 0xDFFF);


/* 
---------------------------------------------------
  IO 0x202 -- R_INTREQ  Interrupt Request Register

  In this register, you can see which hardware
  devices in the GBA generated interrupts

  Also, you can reset currently scheduled interrupts
  by invoking M_INTREQ_*_RESET. I am not 100% sure if
  this really does it, but i heard it is the way to do
  it, although, to me, R_INTREQ seems read-only.
---------------------------------------------------     
*/
#define R_INTREQ                *(volatile u16 *)(MEM_IO + 0x202)

/* Constants */
/* Masks */
/* Functions */
#define F_INTREQ_VBL_STATUS  (R_INTREQ & 0x0001)
#define F_INTREQ_HBL_STATUS  ((R_INTREQ & 0x0002)>>1)
#define F_INTREQ_VCNT_STATUS ((R_INTREQ & 0x0004)>>2)
#define F_INTREQ_TIM0_STATUS ((R_INTREQ & 0x0008)>>3)
#define F_INTREQ_TIM1_STATUS ((R_INTREQ & 0x0010)>>4)
#define F_INTREQ_TIM2_STATUS ((R_INTREQ & 0x0020)>>5)
#define F_INTREQ_TIM3_STATUS ((R_INTREQ & 0x0040)>>6)
#define F_INTREQ_SIO_STATUS  ((R_INTREQ & 0x0080)>>7)
#define F_INTREQ_DMA0_STATUS ((R_INTREQ & 0x0100)>>8)
#define F_INTREQ_DMA1_STATUS ((R_INTREQ & 0x0200)>>9)
#define F_INTREQ_DMA2_STATUS ((R_INTREQ & 0x0400)>>10)
#define F_INTREQ_DMA3_STATUS ((R_INTREQ & 0x0800)>>11)
#define F_INTREQ_KEY_STATUS ((R_INTREQ & 0x1000)>>12)
#define F_INTREQ_CART_STATUS ((R_INTREQ & 0x2000)>>13)

/* Macros */

#define M_INTREQ_VBL_RESET       (R_INTREQ |= 0x0001);
#define M_INTREQ_HBL_RESET       (R_INTREQ |= 0x0002);
#define M_INTREQ_VCNT_RESET      (R_INTREQ |= 0x0004);
#define M_INTREQ_TIM0_RESET      (R_INTREQ |= 0x0008);
#define M_INTREQ_TIM1_RESET      (R_INTREQ |= 0x0010);
#define M_INTREQ_TIM2_RESET      (R_INTREQ |= 0x0020);
#define M_INTREQ_TIM3_RESET      (R_INTREQ |= 0x0040);
#define M_INTREQ_SIO_RESET       (R_INTREQ |= 0x0080);
#define M_INTREQ_DMA0_RESET      (R_INTREQ |= 0x0100);
#define M_INTREQ_DMA1_RESET      (R_INTREQ |= 0x0200);
#define M_INTREQ_DMA2_RESET      (R_INTREQ |= 0x0400);
#define M_INTREQ_DMA3_RESET      (R_INTREQ |= 0x0800);
#define M_INTREQ_KEY_RESET      (R_INTREQ |= 0x1000);
#define M_INTREQ_CART_RESET      (R_INTREQ |= 0x2000);


//--------------------------------------------------------
// additionals:
//--------------------------------------------------------

// enable/disable GBA multiboot

#define MULTIBOOT volatile const int __gba_multiboot;  

// linker related

//#define CODE_IN_EWRAM __attribute__ ((section (".ewram"), long_call)) GCC > 3.0
//#define CODE_IN_IWRAM __attribute__ ((section (".iwram"), long_call)) GCC > 3.0
#define CODE_IN_EWRAM __attribute__ ((section (".ewram")))
#define CODE_IN_IWRAM __attribute__ ((section (".iwram")))
#define VAR_IN_EWRAM __attribute__ ((section (".ewram"))) = {0}
#define VAR_IN_IWRAM __attribute__ ((section (".iwram"))) = {0}


// example: char myarray[1000] MEM_IN_EWRAM || void myfunction(void) MEM_IN_IWRAM;

/*
--------------------------------------------------------
 conversion defines
--------------------------------------------------------
*/
#define RGB(r,g,b) ((((b)>>3)<<10)+(((g)>>3)<<5)+((r)>>3))

#define PI 3.1415926
#define RADIAN(n) (((float)n)/(float)180*PI)


#define CONV_U8_TO_UFP16(n)     ((ufp16)(n<<8))
#define CONV_U8_TO_UFP32(n)     ((ufp32)(n<<8))
#define CONV_U16_TO_UFP32(n)    ((ufp32)(n<<8))
#define CONV_S8_TO_SFP16(n)     ((sfp16)(n<<8))
#define CONV_S8_TO_SFP32(n)     ((sfp32)( (n & 0x7F)<<8) | (n & 0x80)<<24) )
#define CONV_S16_TO_SFP32(n)    ((sfp32)( (n & 0x7FFF)<<8) | (n & 0x8000)<<16) )

#define CONV_UFP16_TO_U8(n)     ((u8)(n>>8))
#define CONV_UFP32_TO_U8(n)     ((u8)(n>>8))
#define CONV_UFP32_TO_U16(n)    ((u16)(n>>8))
#define CONV_SFP16_TO_S8(n)     ((s8)(n>>8))
#define CONV_SFP32_TO_S8(n)     ((s8)(n & 0x7F0000)>>16) | (n & 0x80000000)>>24))

#define CONV_FLOAT_TO_SFP16(n)  ((sfp16)(n*256))
#define CONV_FLOAT_TO_SFP32(n)  ((sfp32)(n*256))


/* 
---------------------------------------------------
      GFX defines
      Just some general stuff on GBA GFX hardware
      that is not related to any registers.
---------------------------------------------------     
*/

#define GFX_MODE3_WIDTH  240
#define GFX_MODE4_WIDTH  240
#define GFX_MODE5_WIDTH  160
#define GFX_MODE3_HEIGHT 160
#define GFX_MODE4_HEIGHT 160
#define GFX_MODE5_HEIGHT 140

/* 
---------------------------------------------------

      Music defines 
          (GBC/GBA specific frequency table)
      Very experimental, only for playing around
          Actually thought of removing these, but if you
          wanna do some silly music, you might like them :)
---------------------------------------------------     
*/

#define SND_FREQU_A_1 1750
#define SND_FREQU_H_1 1782
#define SND_FREQU_C_2 1797
#define SND_FREQU_CIS_2 1811
#define SND_FREQU_D_2 1824 
#define SND_FREQU_DIS_2 1837
#define SND_FREQU_E_2 1849
#define SND_FREQU_F_2 1860
#define SND_FREQU_FIS_2 1870
#define SND_FREQU_G_2 1880
#define SND_FREQU_GIS_2 1890
#define SND_FREQU_A_2 1899
#define SND_FREQU_CIS_2 1811

// End of the file.

#endif
