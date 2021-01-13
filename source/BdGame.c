#include "Socrates.h"
#include "BdGame.h"

#include "BdMap.h"
#include "BdMapData.h"
#include "BdBlend.h"
#include "BdVblank.h"
#include "BdScroll.h"
#include "BdMusic.h"
#include "BdStats.h"
#include "BdMenu.h"
#include "BdMan.h"
#include "BdBackground.h"

//------------------------------------------------------------------------------------

static u32       uGameState;
static u32       uGameTimer;
static u32       uGameNextTimer;
static u32       uGameStartTimer;
static u32       uGameStatsTimer;
static const u32 uGameStartWaitLen = 120;
static const u32 uGameStatsWaitLen = 180;
static const u32 uGameDoneWaitLen = 200;
static const u32 uGameWipeWaitLen = 40;
static const u32 uGameNextWaitLen = 60;
static bool      boGameStartDisplay;
static u32       uGameStateAfterWipe;
static bool      boGameStartFadeIn;
static bool      boGameStartedFadeOut;
static bool      boGameStatsFadeIn;

void BdGameInit(void)
{
    Map_Init();
    Man_Init();
    Scroll_Init();

    boGameStartDisplay = false;
    boGameStartedFadeOut = false;
    boGameStartFadeIn = false;
    boGameStatsFadeIn = true;
    uGameState = GAME_DORMANT;
}

void BdGameUpdate(void)
{
    switch(uGameState)
    {
        case GAME_PAUSE:
        case GAME_DORMANT:
            break;

        case GAME_INGAME_INIT:

            if (BdBlendDone())
            {
                Map_Begin(BdMenuLevelGet());
                Stats_Begin();
                Man_Begin();
                Scroll_Begin();
            
                boGameStartedFadeOut = false;
                boGameStatsFadeIn = false;
                boGameStartDisplay = true;
            
                boGameStartFadeIn = false;
            
                BdVblankTimerSet(&uGameStartTimer, uGameStartWaitLen);
                BdVblankTimerSet(&uGameStatsTimer, uGameStatsWaitLen);
                uGameState = GAME_INGAME;
            }
            break;

        case GAME_INGAME:
            Man_Update1();
            Map_Update();
            Man_Update2();
            Scroll_Update();
            Stats_Update();

            if (Man_Home())
            {
                uGameState = GAME_DONE_INIT;
            }

            if (!Man_Alive())
            {
                BdVblankTimerSet(&uGameNextTimer, uGameNextWaitLen);
                uGameState = GAME_DEAD_WAIT;
            }

            if (Stats_TimerMature())
            {
                BdVblankTimerSet(&uGameNextTimer, uGameNextWaitLen);
                uGameState = GAME_EXPIRED_WAIT;
            }

            break;

        case GAME_DONE_INIT:
            BdVblankTimerSet(&uGameTimer, uGameDoneWaitLen);
            BdVblankTimerSet(&uGameNextTimer, uGameNextWaitLen);
            BdMusicPlaySfx(SFX_EXIT);
            uGameState = GAME_DONE_WAIT;
            break;

        case GAME_DONE_WAIT:
            if (BdVblankTimerMature(&uGameNextTimer))
            {
                if (SoKeysDown(SO_KEY_A) || 
                    SoKeysDown(SO_KEY_START) || 
                    BdVblankTimerMature(&uGameTimer))
                {
                    BdMenuLevelIncrement();

                    switch(BdMenuLevelGet())
                    {
                        case 10:
                        case 20:
                        case 30:
                        case 40:
                            BdMenuStateSet(MENU_CUT_SCENE_INIT);
                            uGameState = GAME_WIPE_INIT;
                            uGameStateAfterWipe = GAME_DORMANT;
                            break;

                        default:
                            BdMenuStateSet(MENU_LEVEL_START_INIT);
                            uGameState = GAME_WIPE_INIT;
                            uGameStateAfterWipe = GAME_DORMANT;
                            break;
                    }
                }                          
            }
            break;

        case GAME_EXPIRED_WAIT:
            if (BdVblankTimerMature(&uGameNextTimer))
            {
                if (SoKeysDown(SO_KEY_A) || 
                    SoKeysDown(SO_KEY_START))
                {
                    uGameState = GAME_WIPE_INIT;
                    uGameStateAfterWipe = GAME_INGAME_INIT;
                }
            }
            break;

        case GAME_DEAD_WAIT:

            Map_Update();

            if (BdVblankTimerMature(&uGameNextTimer))
            {
                if (SoKeysDown(SO_KEY_A) || 
                    SoKeysDown(SO_KEY_START))
                {
                    uGameState = GAME_WIPE_INIT;
                    uGameStateAfterWipe = GAME_INGAME_INIT;
                }
            }
            break;

        case GAME_WIPE_INIT:
            Man_Remove();
            Map_TransitionBegin(-4);
//            Blend_TextOut();
            BdVblankTimerSet(&uGameTimer, uGameWipeWaitLen);
            uGameState = GAME_WIPE_WAIT;
            break;

        case GAME_WIPE_WAIT:
            if (BdVblankTimerMature(&uGameTimer))
            {
                uGameState = uGameStateAfterWipe;
            }
            break;
    }
}

//------------------------------------------------------------------------------------

void BdGameRender(void)
{
    switch(uGameState)
    {
        case GAME_PAUSE:
        case GAME_DORMANT:
            break;

        case GAME_INGAME:
        case GAME_DONE_WAIT:
        case GAME_WIPE_WAIT:
        case GAME_DEAD_WAIT:
            BdBackgroundFlipBufferWrite(2);
            Map_Render();
            Man_Render();
            BdBackgroundFlipBufferView(2);
        
            Scroll_Render();
            Stats_Render();
            break;

        case GAME_EXPIRED_WAIT:
            BdBackgroundFontPrint( 8,10, "TIME UP");
            break;
    }
}

void BdGameStateSet(u32 uState)
{
    uGameState = uState;
}

u32 BdGameStateGet(void)
{
    return(uGameState);
}
                              
void BdGameStateSetAfterWipe(u32 uState)
{
    uGameStateAfterWipe = uState;
}       

