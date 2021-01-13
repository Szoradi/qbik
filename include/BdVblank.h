#ifndef BD_VBLANK_H
#define BD_VBLANK_H

#include "Socrates.h"

void    BdVblankInit(void);
void    BdVblankHandler(void);
void    BdVblankWait(void);
u32     BdVblankFrameCounterGet(void);
void    BdVblankTimerSet(u32 *uTimer, u32 uLength);
bool    BdVblankTimerMature(u32 *uTimer);

#endif /* BD_VBLANK_H */
