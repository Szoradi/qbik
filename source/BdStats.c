#include 	"BdStats.h"

#include	"BdMap.h"
#include	"BdMusic.h"
#include	"BdMenu.h"
#include        "dsprintf.h"
#include	"BdBackground.h"

//------------------------------------------------------------------------

#define 	STATS_TIMER_DIVIDE_SCALER	(2<<16)

//------------------------------------------------------------------------

static u32      uStatsDiamondsGot;
static u32      uStatsDiamondsRequired;
static bool     boStatsDiamondsGotEnough;
static bool     boStatsTimerStarted;
static u32      uStatsTimer;

//------------------------------------------------------------------------

void Stats_Begin(void)
{
    uStatsDiamondsGot = 0;
    boStatsDiamondsGotEnough = false;
    boStatsTimerStarted = false;
}

//------------------------------------------------------------------------

void Stats_Update(void)
{
    if (boStatsTimerStarted && uStatsTimer > 0)
    {
        uStatsTimer--; // based on number of updates not on real time 
    }
}	

//------------------------------------------------------------------------

void Stats_Render(void)
{
    char str[64];
    int tmp = BdMenuLevelGet();

    if(uStatsDiamondsRequired <= uStatsDiamondsGot)
        dsprintf(str,"%03d",0);
    else
        dsprintf(str,"%03d",uStatsDiamondsRequired - uStatsDiamondsGot);

    BdBackgroundFontPrint( 1, 19, str);

    dsprintf(str,"%03d",(((uStatsTimer + 59) * (STATS_TIMER_DIVIDE_SCALER / 60)) / STATS_TIMER_DIVIDE_SCALER));
 
    BdBackgroundFontPrint( 24, 1, str);

    if (tmp >= 10)
    {
        tmp /= 10;
        tmp *= 10;
        tmp = BdMenuLevelGet() - tmp;
    }

    dsprintf(str, "%03d", tmp+1);

    BdBackgroundFontPrint( 0, 1, str);
}

//------------------------------------------------------------------------

void Stats_DiamondGot(void)
{
    uStatsDiamondsGot++;

    if (uStatsDiamondsGot == uStatsDiamondsRequired)
    {
        BdMusicPlaySfx(SFX_ALL_DIAMONDS_GOT);
//        Map_FlashWhite();
        boStatsDiamondsGotEnough = true;
    }
    else
    {
        BdMusicPlaySfx(SFX_GRAB_DIAMOND);
    }
}

//------------------------------------------------------------------------

void Stats_DiamondRequiredSet(u32 uDiamonds)
{
    uStatsDiamondsRequired = uDiamonds;
}

//-----------------------------------------------------------------------

bool Stats_DiamondGotEnough(void)
{
    return boStatsDiamondsGotEnough;
}

//-----------------------------------------------------------------------

void Stats_TimerSet(u32 uTimer)
{
    uStatsTimer = uTimer * 60;
}	

//-----------------------------------------------------------------------

bool Stats_TimerMature(void)
{
    if (uStatsTimer == 0)
    {
        return true;
    }
    return false;
}	

//-----------------------------------------------------------------------

void Stats_TimerStart(void)
{
    boStatsTimerStarted = true;
}	

//-----------------------------------------------------------------------
