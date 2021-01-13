#ifndef BD_GAME_H
#define BD_GAME_H

#include "Socrates.h"

enum
{
    GAME_DORMANT,
    GAME_PAUSE,
    GAME_INGAME_INIT,
    GAME_INGAME,
    GAME_DONE_INIT,
    GAME_DONE_WAIT,
    GAME_EXPIRED_WAIT,
    GAME_DEAD_WAIT,
    GAME_WIPE_INIT,
    GAME_WIPE_WAIT
};

void    BdGameInit(void);
void    BdGameUpdate(void);
void    BdGameRender(void);
void    BdGameStateSet(u32 uState);
u32     BdGameStateGet(void);
void    BdGameStateSetAfterWipe(u32 uState);

#endif /* BD_GAME_H */
