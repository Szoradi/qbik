#include "Socrates.h"
#include "BdRnd.h"

#define	RND_MAX_SEED	2097152

static	u32 uRndSeed;

void BdRndInit(void)
{
    uRndSeed = 0;
}

void BdRndSeedSet(u32 uSeed)
{
    uRndSeed=uSeed;
}

u32 BdRnd(u32 uRange)
{
    u32 uRandomVal;

    uRndSeed = (uRndSeed*1021+1) % RND_MAX_SEED;
    uRandomVal= (uRndSeed*uRange)/RND_MAX_SEED;

    return(uRandomVal);
}

u32 BdRndIWRAM(u32 uRange)
{
    u32 uRandomVal;

    uRndSeed = (uRndSeed*1021+1) % RND_MAX_SEED;
    uRandomVal= (uRndSeed*uRange)/RND_MAX_SEED;

    return(uRandomVal);
}
