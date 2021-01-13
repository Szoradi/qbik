#include "Socrates.h"
#include "SoTables.h"
#include "SoPalette.h"

#include "BdCutScene.h"
#include "BdCutSceneData.h"
#include "BdBackground.h"
#include "BdGame.h"
#include "BdMenu.h"
#include "BdMap.h"
#include "BdGif.h"

static u16 uCutSceneFrames = 0;

void BdCutSceneInitialize(void)
{
    u16 pal[256];

    SoPaletteSetBlack(pal, true);
    SoPaletteSetPalette(SO_SCREEN_PALETTE, pal, true);
    SoMode4RendererClearFrontAndBackBuffer();
    SoMode4RendererEnable();
  
    uCutSceneFrames = (Map_WorldGet()-1) * CUTSCENE_FRAMES;
}

void BdCutScene(void)
{
    int w = 0, h = 0;
    u16 pal[256];

    u16 *dst = SoMode4RendererGetBuffer();

    SO_ASSERT(BdGifLoad(pCutSceneData[uCutSceneFrames], dst, pal, &w, &h), "Gif load failed");

    SoDisplayWaitForVBlankStart();

    SoMode4RendererFlip();

    SoPaletteSetPalette( SO_SCREEN_PALETTE, pal, true );

    if(uCutSceneFrames==CUTSCENE_FRAMES)
    {
        SoMode4RendererClearFrontAndBackBuffer();
        BdInitBackground();

        BdMenuStateSet(MENU_LEVEL_START_INIT);
    }

    if(uCutSceneFrames<CUTSCENE_FRAMES)
    {
        uCutSceneFrames++;
    }
}
