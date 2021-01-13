#ifndef BD_BLEND_H
#define BD_BLEND_H

#include "Socrates.h"

enum
{
    BLEND_OFF,
    BLEND_ALPHA,
    BLEND_FADE_IN,
    BLEND_FADE_OUT
};

typedef struct
{
    u32    uPixelABG0:1;
    u32    uPixelABG1:1;
    u32    uPixelABG2:1;
    u32    uPixelABG3:1;
    u32    uPixelASprite:1;
    u32    uPixelABackdrop:1;
    u32    uBlendMode:2;
    u32    uPixelBBG0:1;
    u32    uPixelBBG1:1;
    u32    uPixelBBG2:1;
    u32    uPixelBBG3:1;
    u32    uPixelBSprite:1;
    u32    uPixelBBackdrop:1;
    u32    uUnused1:2;

    u32    uCoeffA:5;
    u32    uUnused2:3;
    u32    uCoeffB:5;
    u32    uUnused3:3;

    u32    uFadeStep:5;
    u32    uUnused4:11;

    int    nCount;
    int    nRate;
    int    nDeltaA;
    int    nEndA;
    int    nDeltaB;
    int    nEndB;
} BLEND_TYPE;

void        BdBlendInit(void);
void        BdBlendUpdate(void);
void        BdBlendRender(void);
void        BdBlendClear(void);
BLEND_TYPE *BdBlendGetPtr(void);
bool        BdBlendDone(void);

void        BdBlendTextIn(void);
void        BdBlendTextOut(void);

#endif /* BD_BLEND_H */
