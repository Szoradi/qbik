#ifndef BD_RND_H
#define BD_RND_H

#include "Socrates.h"
         
void	BdRndInit(void);
void	BdRndSeedSet(u32 uSeed);
u32	BdRnd(u32 uRange);
u32	BdRndIWRAM(u32 uRange) CODE_IN_IWRAM;

#endif /* BD_RND_H */
