#ifndef BD_MUSIC_H
#define BD_MUSIC_H

#include "Socrates.h"

#include "krawall.h"
#include "../modules/modules.h"
#include "../modules/samples.h"

#define SFX_ALL_DIAMONDS_GOT 129
#define SFX_BOMB 130
#define SFX_BOMB_FUSE 131
#define SFX_BOULDER_FALLS 132
#define SFX_TELEPORT 133
#define SFX_PUSH_BOULDER 134
#define SFX_SWITCH 135
#define SFX_EXIT 136
#define SFX_DIAMOND_FALLS 137
#define SFX_DOOR_OPEN 138
#define SFX_GRAB_DIAMOND 139
#define SFX_GRAB_BOMB 140

typedef enum
{
    MOD_L1,
    MOD_L2, 
    MOD_L3, 
    MOD_L4, 
    MOD_L5,
    MOD_LOGO,
    MOD_INTRO,   
    MOD_MENU, 
    MOD_OUTRO,
}BD_MUSICS;

void BdMusicInit();
void BdMusicPlay();
void BdMusicStop();
void BdMusicPause();
void BdMusicUnPause();
void BdMusicFadeIn();
void BdMusicFadeOut();
bool BdMusicFadeDone();
void BdMusicUpdate();
void BdMusicPlaySfx(int no);

#endif /* BD_MUSIC_H */
