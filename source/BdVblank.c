#include "BdVblank.h"
#include "SoIntManager.h"
#include "BdMusic.h"

static volatile u32    uFrameCounter;

void BdVblankHandler(void)
{
    uFrameCounter++;
    kramWorker();
}

void BdVblankInit(void)
{
    uFrameCounter = 0;

    SoIntManagerEnableInterruptMaster();
    SoIntManagerSetInterruptHandler(SO_INTERRUPT_TYPE_VBLANK, (void *)BdVblankHandler);
    SoIntManagerEnableInterrupt(SO_INTERRUPT_TYPE_VBLANK);
}

void BdVblankWait(void)
{
    u32 uFrameCounterPrevious;

    uFrameCounterPrevious = uFrameCounter;
    while ( uFrameCounterPrevious == uFrameCounter);
}

u32 BdVblankFrameCounterGet(void)
{
    return uFrameCounter;
}

void BdVblankTimerSet(u32 *uTimer, u32 uLength)
{
    *uTimer = (uFrameCounter + uLength);
}

bool BdVblankTimerMature(u32 *uTimer)
{
    if (uFrameCounter >= *uTimer)
    {
        return true;
    }
    return false;
}
