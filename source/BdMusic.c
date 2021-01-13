#include "Socrates.h"

#include "BdMusic.h"

#define MUSIC_VOLUME_MAX 128
#define MUSIC_VOLUME_MIN 0

static u32  uMusicVolume   = 0;
static u32  uFadeDelta     = 0;
static u32  uFadeResult    = 0;
static bool uMusicPlaying  = false;

const Module * const musics[10] = {
&mod_l11, &mod_l21, &mod_l31, &mod_l41, &mod_l51,
&mod_logo, &mod_intro, &mod_menu, &mod_outro
};

void BdMusicInit()
{
    SoIntManagerSetInterruptHandler(SO_INTERRUPT_TYPE_TIMER_1, (void *)kradInterrupt);
    SoIntManagerEnableInterrupt(SO_INTERRUPT_TYPE_TIMER_1);

    kragInit( KRAG_INIT_STEREO );                       // init krawall
    kramSetSFXVol(128);
}

void BdMusicPlaySfx(int no)
{
    kramPlay( samples[ no ], 1, 0 );
}

void BdMusicPlay(BD_MUSICS no)
{
    if(!uMusicPlaying)
    {
        krapPlay( musics[no], KRAP_MODE_LOOP, 0 );       // play module
        uMusicVolume = 128;
        uFadeResult = 128;
        uMusicPlaying = true;
    }
}

void BdMusicStop()
{
    krapStop();
    uMusicPlaying = false;
}

void BdMusicPause()
{
    krapPause(true);
}

void BdMusicUnPause()
{
    krapUnpause();
}

void BdMusicFadeIn()
{
    uFadeDelta = 2;
    uFadeResult = 128;
}

void BdMusicFadeOut()
{
    uFadeDelta = -2;
    uFadeResult = 0;
}

bool BdMusicFadeDone()
{
    if(uFadeResult==uMusicVolume)
    {
        BdMusicStop();
    }
    return (uFadeResult==uMusicVolume);
}

void BdMusicUpdate()
{
    if((uMusicVolume!=uFadeResult)&&
       (uMusicVolume<=MUSIC_VOLUME_MAX)&&
       (uMusicVolume>=MUSIC_VOLUME_MIN))
        uMusicVolume += uFadeDelta;

    krapSetMusicVol( uMusicVolume, false);
}
