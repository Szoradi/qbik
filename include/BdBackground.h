#ifndef BD_BACKGROUND_H
#define BD_BACKGROUND_H

#include "Socrates.h"

#define CharBaseBlock(x)		((u8*) 0x06000000 + (x*0x4000))
#define ScreenBaseBlock(x)		((u16*) (0x06000000 + (x*0x800)))

#define TEXTBG_SIZE_256x256		0x00
#define TEXTBG_SIZE_256x512		0x01
#define TEXTBG_SIZE_512x256		0x02
#define TEXTBG_SIZE_512x512		0x03

#define	GFX_SCREEN_PIXEL_WIDTH		240
#define	GFX_SCREEN_PIXEL_HEIGHT		160
#define	GFX_SCREEN_TILE_WIDTH		(GFX_SCREEN_PIXEL_WIDTH/8)
#define	GFX_SCREEN_TILE_HEIGHT		(GFX_SCREEN_PIXEL_HEIGHT/8)
#define	GFX_TILE_MAP_WIDTH		32

#define WRAPAROUND              	0x1

// --------------------------------------------------------------------------------------
// Defines
// --------------------------------------------------------------------------------------

/* Masks */
#define V_BG0CNT_SCRSIZE_MSK    0x3FFF  //screensize, can be set to %00-%11
#define V_BG0CNT_SCRBB_MSK      0xE0FF  //screen base block in VRAM (0-31, 2kb incr.)
#define V_BG0CNT_CHRBB_MSK      0xFFF3  //character base block in VRAM (0-3, 16k incr.)
#define V_BG0CNT_PRIO_MSK       0xFFFD  //this bg's priority (0=highest 3=lowest)

/* 
---------------------------------------------------
  IO 0x00x --   BGXCNT          Background X control register

  These are convienience macros for manipulating
  any of the 4 BG control registers.

  The first parameter in these macros is always x,
  the BGs number.
---------------------------------------------------     
*/
#define BGXCNT(x)                   (*(volatile u16 *)(0x04000000+8+(x*2)))

#define BGXCNT_COLMODE_SET(x,mode)  (BGXCNT(x) &= 0xFF7F); \
                                    (BGXCNT(x) |= (mode<<7));             
#define BGXCNT_MOSAIC_SET(x,mode)   (BGXCNT(x) &= 0xFFBF); \
                                    (BGXCNT(x) |= (mode<<6));             
#define BGXCNT_SCRSIZE_SET(x,size)  (BGXCNT(x) &= V_BG0CNT_SCRSIZE_MSK);\
                                    (BGXCNT(x) |= (size<<14));            //sets scrsize to size
#define BGXCNT_SCRBB_SET(x,block)   (BGXCNT(x) &= V_BG0CNT_SCRBB_MSK);\
                                    (BGXCNT(x) |= (block<<8));            //sets scrbb to block
#define BGXCNT_CHRBB_SET(x,block)   (BGXCNT(x) &= V_BG0CNT_CHRBB_MSK);\
                                    (BGXCNT(x) |= (block<<2));            //sets chrbb to block
#define BGXCNT_PRIO_SET(x,prio)     (BGXCNT(x) &= V_BG0CNT_PRIO_MSK);\
                                    (BGXCNT(x) |= prio);                  //sets prio to prio :)

#define BGXSCRLX(x)                *(volatile u16 *)(0x04000000 + 0x10 + (x*4))
#define BGXSCRLY(x)                *(volatile u16 *)(0x04000000 + 0x12 + (x*4))

typedef struct
{
    u16 *tileData;
    u16 *mapData;
    bool active;
    u8   mosaic;
    u8   priority;
    u8   colorMode;
    u16  size;
    u16  mapSize;
    u32  charBaseBlock;
    u32  screenBaseBlock;
    u32  sbb;
    s16  x_scroll,y_scroll;
    bool flipView;
    u32  bufferView;
    u32  bufferWrite;
}Bg;

void BdEnableBackground(u8 uBackground);
void BdInitBackground(void);
void BdBackgroundLoadMainMenu(void);
void BdBackgroundLoadGame(void);
void BdBackgroundLoadLevelStart(void);

void BdBackgroundLevelCodeNone(void);
void BdBackgroundLevelCode(void);
void BdBackgroundOptions(void);

void BdBackgroundScrollSet(u8 uBackground, int nX, int nY);
void BdBackgroundUpdate(u8 uBackground);
void BdBackgroundFlipBufferWrite(u8 uBackground);
void BdBackgroundFlipBufferView(u8 uBackground);
void BdBackgroundSetAll(u8 uBackground, u16 nTileIndex);
void BdBackgroundSetScreen(u8 uBackground, u16 nTileIndex);
void BdBackgroundClear(u8 uBackground);
u16 *BdBackgroundSbbPtr(u8 uBackground);
u16 BdBackgroundTileFromGraphic(u16 nGraphic);
void BdBackgroundFontPrint(int nXCo, int nYCo, char *szMessage);
void BdBackgroundPutTile(u8 uBackground, int nXCo, int nYCo, u16 tile);
void BdBackgroundnPutTile(u8 uBackground, const u16 *map, int nXCo, int nYCo, int amount, u16 tile_id);
void BdBackgroundPrint(u8 uBackground, u16 amount, const u16 *tiles);
void BdBackgroundLevelstartPrint(int nXCo, int nYCo, u8 num, u8 *szMessage);
void BdBackgroundLevelstartNumberPrint(int nXCo, int nYCo, u8 *szMessage);

#endif /* BD_BACKGROUND_H */
