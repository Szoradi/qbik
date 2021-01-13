#include "SoIntManager.h"

#include "BdBackground.h"
#include "BdVblank.h"
#include "BdBlend.h"
#include "BdMusic.h"
#include "BdGame.h"
#include "BdMenu.h"
#include "BdRnd.h"

static void BdGameEngineSetup(void)
{
    SoDisplayInitialize();
    SoIntManagerInitialize();
    SoMathRandSeed(34329046);

    BdRndInit();

    BdBlendInit();
    BdVblankInit();

    BdMusicInit();

    BdGameInit();
    BdMenuInit();
}

static void BdGameEngineUpdate()
{
    SoKeysUpdate();

    BdMenuUpdate();
    BdGameUpdate();

    BdMusicUpdate();

    BdGameRender();
    BdMenuRender();

    BdBlendUpdate();
    BdBlendRender();

    BdVblankWait();

    BdBackgroundUpdate(0);
    BdBackgroundUpdate(1);
    BdBackgroundUpdate(2);
}

void BdGameEngine()
{
    BdGameEngineSetup();

    for (;;)
    { 
        BdGameEngineUpdate();
    }
}
