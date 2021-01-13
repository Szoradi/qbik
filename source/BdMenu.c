#include    "Socrates.h"
#include    "SoKeys.h"
#include    "SoSpriteManager.h"
#include    "BdMenu.h"
#include    "BdMenuData.h"
#include    "BdGfxData.h"

#include    "string.h"

#include    "BdBackground.h"
#include    "BdVblank.h"
#include    "BdScroll.h"
#include    "BdMusic.h"
#include    "BdGame.h"
#include    "BdGameIntro.h"
#include    "BdCutScene.h"
#include    "BdBlend.h"
#include    "BdMap.h"
#include    "BdMapData.h"
#include    "BdMan.h"
#include    "dsprintf.h"

static u32       uMenuState;
static int       uMenuLevelMax;
static int       uMenuLevel;
static u32       uMainMenuOption;
static u32       uOptionMenuOption;
static u32       uLevelMenuOption;
static u32       uIngameMenuOption;
static u16       uLevelXPos = 0; 
static bool      boMenuLevelsLocked;

static u32       uMenuButtonTimer;
static u32       uMenuButtonTimerLen;
static const u32 uMenuButtonTimerDefault = 40;

static u32       uMenuInfoTimer;
static const u32 uMenuInfoTimerLen       = 350;
static const u32 uMenuInfoGapLen         = 120;

static u16 uLevelChrpos;

#define MAX_LEVELCODE_DIGITS 10
static u16 level[MAX_LEVELCODE_DIGITS]__attribute__ ((section (".ewram")));
static u8 chars[MAX_LEVELCODE_DIGITS]__attribute__ ((section (".ewram")));
//------------------------------------------------------------------------------------

void BdMenuInit(void)
{
    uMenuLevelMax = MAP_NUM_OF - 1;

    uMainMenuOption = MAIN_MENU_NEW_GAME;
    uIngameMenuOption = INGAME_MENU_RESTART;
    uMenuState = MENU_FROLK_INIT;
//    uMenuState = MENU_INIT;
    boMenuLevelsLocked = true;

    BdVblankTimerSet(&uMenuInfoTimer, uMenuInfoTimerLen);

    uMenuButtonTimerLen = 0;
    BdVblankTimerSet(&uMenuButtonTimer, 0);
}

void BdMenuUpdate(void)
{
    int i;

    switch(uMenuState)
    {
        case MENU_FROLK_INIT :
            BdMusicPlay(MOD_LOGO);
            uMenuState = MENU_FROLK_WAIT;
            break;

        case MENU_FROLK_WAIT :
            if (BdVblankTimerMature(&uMenuInfoTimer))
            {
                uMenuState = MENU_INTRO_INIT;
                BdMusicFadeOut();
                BdVblankTimerSet(&uMenuInfoTimer, 100);
            }
            break;

        case MENU_INTRO_INIT :
            if(BdBlendDone()&&BdMusicFadeDone())
            {
                BdMusicPlay(MOD_INTRO);
                BdGameIntroInitialize();
                uMenuState = MENU_INTRO_WAIT;
            }
            break;

        case MENU_INTRO_WAIT :
            if (BdVblankTimerMature(&uMenuInfoTimer))
            {
                BdGameIntro();
                BdVblankTimerSet(&uMenuInfoTimer, uMenuInfoGapLen);
            }
            if(SoKeysPressed(SO_KEY_A))
                uMenuState = MENU_INIT;
            break;

        case MENU_INIT :
            BdMusicFadeOut();
            uMenuState = MENU_INFO_WAIT_1;
            break;

        case MENU_INFO_WAIT_1 :
            if (BdMusicFadeDone())
            {
                BdInitBackground();
                uMenuState = MENU_PRE_GAME_INIT;
            }
            break;

        case MENU_PRE_GAME_INIT:
            if (BdBlendDone()&&BdMusicFadeDone())
            {
                uMenuLevel = 0;
                Scroll_Init();
                Scroll_Update();
                BdBackgroundLoadMainMenu();
                uMenuState = MENU_PRE_GAME;
                BdBlendTextIn();
                BdMusicPlay(MOD_MENU);
            }
            break;

        case MENU_PRE_GAME :
            SoSpriteManagerDisableSprites();
            if (BdBlendDone())
            {
                if (SoKeysPressed(SO_KEY_DOWN))
                {                   
                    if (uMainMenuOption < MAIN_MENU_MAX-1)
                    {
                        uMainMenuOption++;
                    }
                } 
                if (SoKeysPressed(SO_KEY_UP))
                {
                    if (uMainMenuOption > 0)
                    {
                        uMainMenuOption--;
                    }
                } 
        
                if (SoKeysPressed(SO_KEY_A))
                {
                    switch (uMainMenuOption)
                    {
                        case MAIN_MENU_NEW_GAME:
                            uMenuState = MENU_LEVEL_START_INIT;
                            Scroll_Init();
                            BdBackgroundClear(2);
                            BdBlendTextOut();
                            BdMusicFadeOut();
                        break;

                        case MAIN_MENU_LEVEL_CODE:
                            uMenuState = MENU_LEVEL_CODE_INIT;
                            BdBlendTextOut();
                        break;

                        case MAIN_MENU_REPLAY_INTRO:
                            uMenuState = MENU_INTRO_INIT;
                            BdBackgroundClear(2);
                            BdBlendTextOut();
                            BdMusicFadeOut();
                        break;

                        case MAIN_MENU_OPTIONS:
                            uMenuState = MENU_OPTIONS_INIT;
                            BdBlendTextOut();
                        break;
                    }
                }
            }
            break;

        case MENU_LEVEL_CODE_NONE_INIT:
            if(BdBlendDone())
            {
                BdBackgroundLevelCodeNone();
                BdBlendTextIn();
                uMenuState = MENU_LEVEL_CODE_NONE;
            }
            break;

        case MENU_LEVEL_CODE_NONE:
            if(BdBlendDone())
            {
                if (SoKeysPressed(SO_KEY_A))
                {
                    BdBlendTextOut();
                    uMenuState = MENU_LEVEL_CODE_INIT;
                }
            }
            break;

        case MENU_LEVEL_CODE_INIT:
            if(BdBlendDone())
            {
                BdBackgroundLevelCode();
                BdBlendTextIn();
                uLevelMenuOption = LEVEL_MENU_CHRS1;
                uMenuState = MENU_LEVEL_CODE;
                for(i=0;i<MAX_LEVELCODE_DIGITS;i++)
                {
                    level[i] = 0;
                    chars[i] = 0;
                }
                uLevelChrpos = 0;
            }
            break;

        case MENU_LEVEL_CODE:
            if(BdBlendDone())
            {
                if (SoKeysPressed(SO_KEY_DOWN))
                {
                    if (uLevelMenuOption < LEVEL_MENU_MAX-1)
                    {
                        uLevelMenuOption++;
                    }
                } 
                if (SoKeysPressed(SO_KEY_UP))
                {
                    if (uLevelMenuOption > 0)
                    {
                        uLevelMenuOption--;
                    }
                } 

                if (SoKeysPressed(SO_KEY_LEFT))
                {
                    if (uLevelXPos > 0)
                    {
                        uLevelXPos--;
                    }
                } 

                if (SoKeysPressed(SO_KEY_RIGHT))
                {
                    if (uLevelXPos < 12)
                    {
                        uLevelXPos++;
                    }
                } 

                if (SoKeysPressed(SO_KEY_A))
                {
                    switch (uLevelMenuOption)
                    {
                        case LEVEL_MENU_CHRS1:
                            if(uLevelChrpos<MAX_LEVELCODE_DIGITS)
                            {
                                level[uLevelChrpos] = 46*30+15+uLevelXPos;
                                chars[uLevelChrpos] = uLevelXPos+97;
                                uLevelChrpos++;
                            }
                            break;

                        case LEVEL_MENU_CHRS2:
                            if(uLevelChrpos<MAX_LEVELCODE_DIGITS)
                            {
                                level[uLevelChrpos] = 47*30+15+uLevelXPos;
                                chars[uLevelChrpos] = uLevelXPos+97+13;
                                uLevelChrpos++;
                            }
                            break;

                        case LEVEL_MENU_PLAY:
                            if(uLevelChrpos)
                            for(i=0;i<50;i++)
                            {
                                if(strncmp(((u8*)pMapData[i])+1, chars, (u8)*pMapData[i]))
                                {
                                     uMenuState = MENU_LEVEL_CODE_NONE_INIT;
                                     BdBlendTextOut();
                                }
                                else
                                {
                                     uMenuLevel = i;
                                     uMenuState = MENU_LEVEL_START_INIT;
                                     Scroll_Init();
                                     BdBlendTextOut();
                                     BdMusicFadeOut();
                                     break;
                                }
                            }
                            break;

                        case LEVEL_MENU_RETURN:
                            uMenuState = MENU_PRE_GAME_INIT;
                            BdBlendTextOut();
                            break;
                    }
                }

                if (SoKeysPressed(SO_KEY_B))
                {
                    switch (uLevelMenuOption)
                    {
                        case LEVEL_MENU_CHRS1:
                        case LEVEL_MENU_CHRS2:
                            if(uLevelChrpos>0)
                            {
                                level[uLevelChrpos] = 0;
                                chars[uLevelChrpos] = 0;
                                uLevelChrpos--;
                            }
                            else
                            {
                                level[0] = 0;
                                chars[0] = 0;
                            }
                            break;
                    }
                }
            }
            break;

        case MENU_OPTIONS_INIT:
            if(BdBlendDone())
            {
                BdBackgroundOptions();
                BdBlendTextIn();
                uOptionMenuOption = OPTION_MENU_TIMER;
                uMenuState = MENU_OPTIONS;
            }
            break;

        case MENU_OPTIONS:
            if(BdBlendDone())
            {
                if (SoKeysPressed(SO_KEY_DOWN))
                {
                    if (uOptionMenuOption < OPTION_MENU_MAX-1)
                    {
                        uOptionMenuOption++;
                    }
                } 
                if (SoKeysPressed(SO_KEY_UP))
                {
                    if (uOptionMenuOption > 0)
                    {
                        uOptionMenuOption--;
                    }
                } 
        
                if (SoKeysPressed(SO_KEY_A))
                {
                    switch (uOptionMenuOption)
                    {
                        case OPTION_MENU_TIMER:
                        break;

                        case OPTION_MENU_BRIGHTNESS:
                        break;

                        case OPTION_MENU_MUSIC:
                        break;

                        case OPTION_MENU_SOUND_FX:
                        break;

                        case OPTION_MENU_RETURN:
                            uMenuState = MENU_PRE_GAME_INIT;
                            BdBlendTextOut();
                        break;
                    }
                }
            }
            break;

        case MENU_CUT_SCENE_INIT :
            if(BdGameStateGet()==GAME_DORMANT)
            {
                BdCutSceneInitialize();
                uMenuState = MENU_CUT_SCENE;
            }
            break;

        case MENU_CUT_SCENE:
            if (BdVblankTimerMature(&uMenuInfoTimer))
            {
                BdCutScene();
                BdVblankTimerSet(&uMenuInfoTimer, uMenuInfoGapLen);
            }
            break;

        case MENU_LEVEL_START_INIT :
            if (BdBlendDone()&&BdMusicFadeDone()&&(BdGameStateGet()==GAME_DORMANT))
            {
                u8 buff[16];
                int tmp = uMenuLevel;
        
                BdMusicPlay(MOD_L1+Map_WorldGet());
                BdBackgroundLoadLevelStart();
        
                if (uMenuLevel >= 10)
                {
                    tmp /= 10;
                    tmp *= 10;
                    tmp = uMenuLevel - tmp;
                }

                dsprintf(buff, "%02d;10", tmp+1);
        
                BdBackgroundLevelstartNumberPrint(19, 10, buff);
                // levelcode
                BdBackgroundLevelstartPrint(13, 17, (u8)*pMapData[uMenuLevel], ((u8*)pMapData[uMenuLevel])+1);
        
                uMenuState = MENU_LEVEL_START;
            }
            break;

        case MENU_LEVEL_START :
            if (BdBlendDone())
            {
                if(SoKeysPressed(SO_KEY_A))
                {
                    uMenuState = MENU_DORMANT_INIT;
                    BdGameStateSet(GAME_INGAME_INIT);
                    BdBlendTextOut();
                }
            }
            break;

        case MENU_DORMANT_INIT :
            if (BdBlendDone())
            {
                BdBackgroundLoadGame();
                Map_Init();
                Man_Init();

                uMenuState = MENU_DORMANT;
            }
            break;

        case MENU_DORMANT :
            if (BdBlendDone())
            {
                if ((BdGameStateGet() == GAME_INGAME) && (Man_Born()))
                {
                    if (SoKeysPressed(SO_KEY_START))
                    {
                        BdGameStateSet(GAME_PAUSE);
                        uMenuState = MENU_INGAME_INIT;
                        BdBlendTextIn();
                    }
//-------------
                    if (SoKeysPressed(SO_KEY_R))
                    {
                        if(uMenuLevel<50)
                        {
                            BdGameStateSet(GAME_DONE_WAIT);
                        }
                    }
                    if (SoKeysPressed(SO_KEY_L))
                    {
                        if(uMenuLevel>0)
                        {
                            uMenuLevel-=2;
                            BdGameStateSet(GAME_DONE_WAIT);
                        }
                    }
//-------------
                }
            }
            break;

        case MENU_INGAME_INIT :
            if (BdBlendDone())
            {
                uMenuState = MENU_INGAME;
            }
            break;

        case MENU_INGAME :
            if (SoKeysPressed(SO_KEY_START))
            {
                BdGameStateSet(GAME_INGAME);
                uMenuState = MENU_DORMANT;
                BdBlendTextOut();
            }

            if (SoKeysPressed(SO_KEY_DOWN))
            {
                if (uIngameMenuOption < INGAME_MENU_MAX-1)
                {
                    uIngameMenuOption++;
                }
            } 
            if (SoKeysPressed(SO_KEY_UP))
            {
                if (uIngameMenuOption > 0)
                {
                    uIngameMenuOption--;
                }
            } 

            if (SoKeysPressed(SO_KEY_A))
            {
                switch (uIngameMenuOption)
                {
                    case INGAME_MENU_RESTART:
                    {
                        BdGameStateSet(GAME_WIPE_INIT);
                        BdGameStateSetAfterWipe(GAME_INGAME_INIT);
                        uMenuState = MENU_DORMANT;
                        BdBlendTextOut();
                        break;
                    }
                    case INGAME_MENU_QUIT:
                    {
                        BdGameStateSet(GAME_WIPE_INIT);
                        BdGameStateSetAfterWipe(GAME_DORMANT);
                        uMenuState = MENU_GAME_QUITTING;
                        BdBlendTextOut();
                        BdMusicFadeOut();
                        break;
                    }
                    case INGAME_MENU_CONTINUE:
                    {
                        BdGameStateSet(GAME_INGAME);
                        uMenuState = MENU_DORMANT;
                        BdBlendTextOut();
                    }
                }
            }
            break;

        case MENU_GAME_QUITTING:
            if (BdGameStateGet()==GAME_DORMANT&&BdMusicFadeDone())
            {
                uMenuState = MENU_PRE_GAME_INIT;
            }
            break;

        case MENU_GAME_COMPLETE :
            BdGameStateSet(GAME_DORMANT);
            break;

    }
}

void BdMenuRender(void)
{
    u16 mainmenu = uMainMenuOption * 2;
    u16 ingamemenu = uIngameMenuOption * 2;
    u16 optionmenu = uOptionMenuOption * 2;
    u16 levelmenu = (uLevelMenuOption-2) * 2;
    int i ,startchar;
    u8 world = 0;

    switch(uMenuState)
    {
        case MENU_INIT :
            break;

        case MENU_INFO_WAIT_1 :
        case MENU_INFO_WAIT_2 :
            break;  

        case MENU_DORMANT_INIT :
            BdBackgroundClear(0);
            break;

        case MENU_DORMANT :
            world = Map_WorldGet();

            BdBackgroundnPutTile(1, (const u16*)pTileMapData[world], 0,  0, 30, 768);
            BdBackgroundnPutTile(1, (const u16*)pTileMapData[world], 0,  1, 30, 808);
            BdBackgroundnPutTile(1, (const u16*)pTileMapData[world], 0,  2, 30, 848);

            BdBackgroundnPutTile(1, (const u16*)pTileMapData[world], 0, 18, 30, 888);
            BdBackgroundnPutTile(1, (const u16*)pTileMapData[world], 0, 19, 30, 928);
            break;

        case MENU_PRE_GAME_INIT :
            BdBackgroundClear(1);
            BdBackgroundClear(2);
            break;

        case MENU_PRE_GAME :
            BdBackgroundClear(1);
            BdBackgroundClear(2);

            BdBackgroundnPutTile(2, (const u16*)mainmenu_map, 14, 10+mainmenu, 14, 82*30);
            BdBackgroundnPutTile(2, (const u16*)mainmenu_map, 14, 11+mainmenu, 14, 82*30);
            break;

        case MENU_OPTIONS_INIT :
            BdBackgroundClear(1);
            BdBackgroundClear(2);
            break;

        case MENU_OPTIONS :
            BdBackgroundClear(1);
            BdBackgroundClear(2);

            BdBackgroundnPutTile(2, (const u16*)mainmenu_map, 14, 8+optionmenu, 14, 82*30);
            BdBackgroundnPutTile(2, (const u16*)mainmenu_map, 14, 9+optionmenu, 14, 82*30);
            break;

        case MENU_LEVEL_CODE_NONE_INIT :
            BdBackgroundClear(1);
            BdBackgroundClear(2);
            break;

        case MENU_LEVEL_CODE_NONE :
            BdBackgroundClear(1);
            BdBackgroundClear(2);
            break;

        case MENU_LEVEL_CODE_INIT :
            BdBackgroundClear(1);
            BdBackgroundClear(2);
            break;

        case MENU_LEVEL_CODE :
            BdBackgroundClear(1);
            BdBackgroundClear(2);


            if(uLevelMenuOption<2)
            {
                BdBackgroundnPutTile(2, (const u16*)mainmenu_map, 15 + uLevelXPos, 6 + uLevelMenuOption, 1, 82*30+5);
            }
            else
            {
                BdBackgroundnPutTile(2, (const u16*)mainmenu_map, 14, 13+levelmenu, 14, 82*30);
                BdBackgroundnPutTile(2, (const u16*)mainmenu_map, 14, 14+levelmenu, 14, 82*30);
            }

            // align
            startchar = (13-uLevelChrpos)/2;

            for(i=0;i<MAX_LEVELCODE_DIGITS;i++)
               BdBackgroundnPutTile(2, (const u16*)mainmenu_map, 16+startchar+i, 10, 1, level[i]);
            break;

        case MENU_INGAME_INIT :
            world = Map_WorldGet();

            BdBackgroundClear(0);

            BdBackgroundnPutTile(0, (const u16*)pTileMapData[world], 10,  5, 8, 760);
            BdBackgroundnPutTile(0, (const u16*)pTileMapData[world], 10,  6, 8, 800);
            BdBackgroundnPutTile(0, (const u16*)pTileMapData[world], 10,  7, 8, 840);
            BdBackgroundnPutTile(0, (const u16*)pTileMapData[world], 10,  8, 8, 880);
            BdBackgroundnPutTile(0, (const u16*)pTileMapData[world], 10,  9, 8, 920);
            BdBackgroundnPutTile(0, (const u16*)pTileMapData[world], 10, 10, 8, 960);
            BdBackgroundnPutTile(0, (const u16*)pTileMapData[world], 10, 11, 8, 1000);
            BdBackgroundnPutTile(0, (const u16*)pTileMapData[world], 10, 12, 8, 1040);
            BdBackgroundnPutTile(0, (const u16*)pTileMapData[world], 10, 13, 8, 1080);
            BdBackgroundnPutTile(0, (const u16*)pTileMapData[world], 10, 14, 8, 1120);
            break;

        case MENU_INGAME :
            world = Map_WorldGet();

            switch(8+ingamemenu)
            {
                case 8:
                case 12:
                    BdBackgroundnPutTile(0, (const u16*)pTileMapData[world], 10, 10, 8, 960);
                    break;
                case 10:
                    BdBackgroundnPutTile(0, (const u16*)pTileMapData[world], 10,  8, 8, 880);
                    BdBackgroundnPutTile(0, (const u16*)pTileMapData[world], 10, 12, 8, 1040);
                    break;
            }

            BdBackgroundnPutTile(0, (const u16*)pTileMapData[world], 11, 8 + ingamemenu, 1, 731);
            break;

        case MENU_GAME_QUITTING :
            break;

        case MENU_GAME_COMPLETE :
            break;
    }
}

u32 BdMenuLevelGet(void)
{
    return uMenuLevel;
}

void BdMenuLevelIncrement(void)
{
    if (uMenuLevel < uMenuLevelMax)
    {
        uMenuLevel++;
    }
    else
    {
        uMenuState = MENU_GAME_COMPLETE;
    }
}

void BdMenuStateSet(u32 state)
{
    uMenuState = state;
}
