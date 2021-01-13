#include "Socrates.h"
#include "SoTables.h"
#include "SoPalette.h"
#include "SoDma.h"

#include "BdGameIntro.h"
#include "BdGameIntroData.h"
#include "BdMenu.h"
#include "BdGif.h"

static int uIntroFrames = 0;

void BdGameIntroInitialize(void)
{
    u16 pal[256];

    SoPaletteSetBlack(pal, true);
    SoPaletteSetPalette(SO_SCREEN_PALETTE, pal, true);
    SoMode4RendererClearFrontAndBackBuffer();
    SoMode4RendererEnable();

    uIntroFrames = 0;
}

void BdGameIntro(void)
{
    int w = 0, h = 0;
    u16 pal[256];

    u16 *dst = SoMode4RendererGetBuffer();

    SO_ASSERT(BdGifLoad(pIntroData[uIntroFrames], dst, pal, &w, &h), "Gif load failed");
    SoDisplayWaitForVBlankStart();

    SoMode4RendererFlip();

    SoPaletteSetPalette( SO_SCREEN_PALETTE, pal, true );

    if(uIntroFrames==INTRO_FRAMES)
    {
        SoMode4RendererClearFrontAndBackBuffer();
        BdMenuStateSet(MENU_INIT);
    }

    if(uIntroFrames<INTRO_FRAMES)
    {
        uIntroFrames++;
    }
}
