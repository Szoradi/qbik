#include "gba.h"

#include "SoPalette.h"

#include "BdBackground.h"
#include "BdScreenmode.h"
#include "BdMenu.h"
#include "BdMap.h"

#include "BdGfxData.h"
#include "BdMenuData.h"
#include "BdLevelStartData.h"

Bg BdBackground[4];

static const u32 uBackgroundMapSize[4] = { 1024, 2048, 2048, 4096 };

void BdEnableBackground(u8 uBackground)
{
    Bg *pBg = &BdBackground[uBackground];

    pBg->bufferView = 0;
    pBg->bufferWrite = 0;
    pBg->sbb = pBg->screenBaseBlock;
    pBg->flipView = false;

    SoBackgroundManagerSetBackgroundEnable(uBackground, pBg->active);
    BGXCNT_PRIO_SET(uBackground, pBg->priority);
    BGXCNT_CHRBB_SET(uBackground, pBg->charBaseBlock);
    BGXCNT_SCRBB_SET(uBackground, pBg->screenBaseBlock);
    BGXCNT_COLMODE_SET(uBackground, pBg->colorMode);
    BGXCNT_SCRSIZE_SET(uBackground, pBg->size);

    pBg->tileData = (u16*)CharBaseBlock(pBg->charBaseBlock);
    pBg->mapData = (u16*)ScreenBaseBlock(pBg->screenBaseBlock);
}

void BdInitBackground(void)
{
    //set mode 2 and enable sprites and 1d mapping
    SetMode(MODE_0 | OBJ_ENABLE | OBJ_MAP_1D);

    // menu layer
    BdBackground[0].active = true;
    BdBackground[0].priority = 0;          // top
    BdBackground[0].charBaseBlock = 0;
    BdBackground[0].screenBaseBlock = 24;
    BdBackground[0].colorMode = 1;
    BdBackground[0].size = TEXTBG_SIZE_256x256;
    BdBackground[0].x_scroll = 0;
    BdBackground[0].y_scroll = 0;
    BdBackground[0].mapSize = uBackgroundMapSize[TEXTBG_SIZE_256x256];

    // text layer
    BdBackground[1].active = true;
    BdBackground[1].priority = 1;          // middle
    BdBackground[1].charBaseBlock = 0;
    BdBackground[1].screenBaseBlock = 26;
    BdBackground[1].colorMode = 1;
    BdBackground[1].size = TEXTBG_SIZE_256x256;
    BdBackground[1].x_scroll = 0;
    BdBackground[1].y_scroll = 0;
    BdBackground[1].mapSize = uBackgroundMapSize[TEXTBG_SIZE_256x256];

    // game layer
    BdBackground[2].active = true;
    BdBackground[2].priority = 2;          // bottom
    BdBackground[2].charBaseBlock = 0;
    BdBackground[2].screenBaseBlock = 28;
    BdBackground[2].colorMode = 1;
    BdBackground[2].size = TEXTBG_SIZE_256x256;
    BdBackground[2].x_scroll = 0;
    BdBackground[2].y_scroll = 0;
    BdBackground[2].mapSize = uBackgroundMapSize[TEXTBG_SIZE_256x256];

    BdEnableBackground(0);
    BdEnableBackground(1);
    BdEnableBackground(2);

    BdBackgroundClear(0);
    BdBackgroundClear(1);
    BdBackgroundClear(2);
}

void BdBackgroundLoadMainMenu(void)
{
    u16 *ptr = ScreenBaseBlock(BdBackground[0].sbb);
    u16 i, j;

    BdBackgroundClear(0); BdBackgroundClear(1); BdBackgroundClear(2);

    SoPaletteSetPalette( SO_SCREEN_PALETTE, mainmenu_pal, true );

    SoDMATransfer(3, &mainmenu_gfx, BdBackground[0].tileData, MAINMENU_GFX_SIZE,
                  SO_DMA_START_NOW | SO_DMA_16 | SO_DMA_SOURCE_INC | SO_DMA_DEST_INC);

    for(i=0;i<20;i++)
       for(j=0;j<30;j++)
          ptr[i*32+j] = mainmenu_map[i*30+j];
}

void BdBackgroundLoadGame(void)
{
    u16 level = Map_WorldGet();

    SoPaletteSetPalette( SO_SCREEN_PALETTE, pTilePalData[level], true );

    BdBackgroundClear(0); BdBackgroundClear(1); BdBackgroundClear(2);

    /* Transfer the game tiles */
    SoDMATransfer(3, (void*)pTileGfxData[level], BdBackground[0].tileData, pTileGfxDataSize[level],
                  SO_DMA_START_NOW | SO_DMA_16 | SO_DMA_SOURCE_INC | SO_DMA_DEST_INC);
}

void BdBackgroundLoadLevelStart(void)
{
    u16 level = Map_WorldGet();
    u16 *ptr = ScreenBaseBlock(BdBackground[1].sbb);
    u16 i, j;
    u16 *map = (u16*)pLevelMapData[level];

    SoPaletteSetPalette( SO_SCREEN_PALETTE, pLevelPalData[level], true );

    BdBackgroundSetScreen(0,map[659]); 
    BdBackgroundSetScreen(1,map[659]);
    BdBackgroundSetScreen(2,map[659]);

    /* Transfer the game tiles */
    SoDMATransfer(3, (void*)pLevelGfxData[level], BdBackground[1].tileData, pLevelGfxDataSize[level],
                  SO_DMA_START_NOW | SO_DMA_16 | SO_DMA_SOURCE_INC | SO_DMA_DEST_INC);

    for(i=0;i<20;i++)
       for(j=0;j<30;j++)
          ptr[i*32+j] = map[i*30+j];
}


void BdBackgroundLevelCodeNone(void)
{
    u16 *ptr = ScreenBaseBlock(BdBackground[0].sbb);
    u16 i, j;

    for(i=60;i<80;i++)
       for(j=0;j<30;j++)
          ptr[(i-60)*32+j]=mainmenu_map[i*30+j];
}

void BdBackgroundLevelCode(void)
{
    u16 *ptr = ScreenBaseBlock(BdBackground[0].sbb);
    u16 i, j;

    for(i=40;i<60;i++)
       for(j=0;j<30;j++)
          ptr[(i-40)*32+j]=mainmenu_map[i*30+j];
}

void BdBackgroundOptions(void)
{
    u16 *ptr = ScreenBaseBlock(BdBackground[0].sbb);
    u16 i, j;

    for(i=20;i<40;i++)
       for(j=0;j<30;j++)
          ptr[(i-20)*32+j]=mainmenu_map[i*30+j];
}

void BdBackgroundScrollSet(u8 uBackground, int nX, int nY)
{
    Bg *pBg = &BdBackground[uBackground];
        
    pBg->x_scroll = nX;
    pBg->y_scroll = nY;
}

void BdBackgroundUpdate(u8 uBackground)
{
    Bg  *pBg = &BdBackground[uBackground];
    u32  uSbb;

    BGXSCRLX(uBackground) = pBg->x_scroll;
    BGXSCRLY(uBackground) = pBg->y_scroll;

    if (pBg->flipView)
    {
        pBg->bufferView = 1 - pBg->bufferView;
        uSbb = pBg->screenBaseBlock + (pBg->mapSize>>10) * pBg->bufferView;
        BGXCNT_SCRBB_SET(uBackground, uSbb);
        pBg->flipView = false;
    }
}

void BdBackgroundFlipBufferWrite(u8 uBackground)
{
    Bg  *pBg = &BdBackground[uBackground];

    pBg->bufferWrite = 1 - pBg->bufferWrite;
    pBg->sbb = pBg->screenBaseBlock + (pBg->mapSize>>10) * pBg->bufferWrite;
}

void BdBackgroundFlipBufferView(u8 uBackground)
{
    Bg  *pBg = &BdBackground[uBackground];
    pBg->flipView = true;
}

void BdBackgroundSetAll(u8 uBackground, u16 nTileIndex)
{
    Bg  *pBg = &BdBackground[uBackground];
    u32  uCount;
    u16 *pDest;
    u16  nTile;

    nTile = BdBackgroundTileFromGraphic(nTileIndex);
    pDest = (u16*)ScreenBaseBlock(pBg->sbb);
    uCount = (pBg->mapSize);
    while (uCount > 0)
    {
        *pDest++ = (u16) nTile;
        uCount--;
    }
}

void BdBackgroundSetScreen(u8 uBackground, u16 nTileIndex)
{
    Bg  *pBg = &BdBackground[uBackground];
    u32  uCount;
    u32 *pDest;
    u16  nTile;
    u32  nTileComposite;

    nTile = nTileIndex;
    pDest = (u32 *) ScreenBaseBlock(pBg->sbb);
    uCount = ((GFX_TILE_MAP_WIDTH * GFX_SCREEN_TILE_HEIGHT) / 2);
    nTileComposite = nTile + (nTile << 16);
    while (uCount > 0)
    {
        *pDest++ = nTileComposite;
        uCount--;
    }
}

void BdBackgroundClear(u8 uBackground)
{                                                   
    Bg  *pBg = &BdBackground[uBackground];
    u32  uCount;
    u32  nTileComposite;

    uCount = (GFX_TILE_MAP_WIDTH * GFX_SCREEN_TILE_HEIGHT);

    nTileComposite = 0 + (0 << 16);         // clear 2 entries each write

    SoDMATransfer(3, &nTileComposite, ScreenBaseBlock(pBg->sbb), uCount, 
                  SO_DMA_START_NOW | SO_DMA_16 | SO_DMA_SOURCE_FIX | SO_DMA_DEST_INC);
}       

u16 *BdBackgroundSbbPtr(u8 uBackground)
{
    Bg  *pBg = &BdBackground[uBackground];
    
    return (u16*)ScreenBaseBlock(pBg->sbb);
}

u16 BdBackgroundTileFromGraphic(u16 nGraphic)
{
    u16 level = Map_WorldGet();

    const u16 *proba = pTileMapData[level];

    return proba[nGraphic];
}

void BdBackgroundFontPrint(int nXCo, int nYCo, char *szMessage)
{
    Bg  *pBg = &BdBackground[0];
    u8  *pSrc;
    u16 *pDest;

    int i=0;
    const u16 *ss = (const u16*)pTileMapData[Map_WorldGet()];

    pDest = ScreenBaseBlock(pBg->sbb) + (nYCo<<5) + nXCo;
    pSrc = szMessage;

    while (*pSrc != 0)
    {
        *pDest++ = ss[(*pSrc) + 504 - 48 - i*40];
        pSrc++;
        i++;
    }
}

void BdBackgroundLevelstartPrint(int nXCo, int nYCo, u8 num, u8 *szMessage)
{
    Bg  *pBg = &BdBackground[0];
    u8  *pSrc;
    u16 *pDest;

    const u16 *ss = (const u16*)pLevelMapData[Map_WorldGet()];

    pDest = ScreenBaseBlock(pBg->sbb) + (nYCo<<5) + nXCo;
    pSrc = szMessage;

    while (num)
    {
        u8 a = (*pSrc) - 97;
        if(a>22)a--;

        *pDest++ = ss[a + 30*20];
        pSrc++;
        num--;
    }
}

void BdBackgroundLevelstartNumberPrint(int nXCo, int nYCo, u8 *szMessage)
{
    Bg  *pBg = &BdBackground[0];
    u8  *pSrc;
    u16 *pDest;

    const u16 *ss = (const u16*)pLevelMapData[Map_WorldGet()];

    pDest = ScreenBaseBlock(pBg->sbb) + (nYCo<<5) + nXCo;
    pSrc = szMessage;

    while (*pSrc)
    {
        *pDest++ = ss[(*pSrc) - 48 + 30*20 + 25];
        pSrc++;
    }
}

void BdBackgroundPutTile(u8 uBackground, int nXCo, int nYCo, u16 tile)
{
    Bg  *pBg = &BdBackground[uBackground];
    u16 *pDest;

    pDest = ScreenBaseBlock(pBg->sbb) + (nYCo<<5) + nXCo;
    *pDest++ = tile;
}

void BdBackgroundnPutTile(u8 uBackground, const u16 *map, int nXCo, int nYCo, int amount, u16 tile_id)
{
    Bg  *pBg = &BdBackground[uBackground];
    u16 *pDest;
    u16 tile = tile_id;
    int no = amount;

    pDest = ScreenBaseBlock(pBg->sbb) + (nYCo<<5) + nXCo;

    while(no--)
        *pDest++ = map[tile++];
}

void BdBackgroundPrint(u8 uBackground, u16 amount, const u16 *tiles)
{
    Bg  *pBg = &BdBackground[uBackground];
    u16 *pDest = ScreenBaseBlock(pBg->sbb);
    u16 *t = (u16*)tiles;

    while(amount--)
       *pDest++ = *t++;
}
