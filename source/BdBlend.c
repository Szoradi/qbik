#include        "BdBlend.h"
#include        "gba.h"

BLEND_TYPE      Blend;

void BdBlendInit(void)
{
    BdBlendClear();
}       

void BdBlendUpdate(void)
{
    if (Blend.nRate > 0)
    {
        Blend.nCount++;
        if (Blend.nCount >= Blend.nRate)
        {
            if (Blend.uCoeffA != Blend.nEndA) 
            {
                Blend.uCoeffA += Blend.nDeltaA;
            }
            if (Blend.uCoeffB != Blend.nEndB)
            {
                Blend.uCoeffB += Blend.nDeltaB;
            }
            if ((Blend.uCoeffA == Blend.nEndA) && (Blend.uCoeffB == Blend.nEndB))
            {
                Blend.nRate = 0;
            }
            Blend.nCount = 0;
        }
    }
}       

void BdBlendRender(void)
{
    R_BLDCNT = *((u16 *) &Blend);
    R_BLDALPHA = *((u16 *) &Blend + 1);
    R_BLDY = *((u16 *) &Blend + 2);
}       

void BdBlendClear(void)
{
    Blend.uPixelABG0 = 0;
    Blend.uPixelABG1 = 0;
    Blend.uPixelABG2 = 0;
    Blend.uPixelABG3 = 0;
    Blend.uPixelASprite = 0;
    Blend.uPixelABackdrop = 0;
    Blend.uBlendMode = 0;
    Blend.uPixelBBG0 = 0;
    Blend.uPixelBBG1 = 0;
    Blend.uPixelBBG2 = 0;
    Blend.uPixelBBG3 = 0;
    Blend.uPixelBSprite = 0;
    Blend.uPixelBBackdrop = 0;
    Blend.uCoeffA = 0;
    Blend.uCoeffB = 0;
    Blend.uFadeStep = 0;

    Blend.nCount = 0;
    Blend.nRate = 0;
    Blend.nDeltaA = 0;
    Blend.nEndA = 0;
    Blend.nDeltaB = 0;
    Blend.nEndB = 0;
}       

BLEND_TYPE *BdBlendGetPtr(void)
{
    return &Blend;
}       

bool BdBlendDone(void)
{
    return (Blend.nRate == 0);
}       

void BdBlendTextIn(void)
{
    Blend.uBlendMode = BLEND_ALPHA;
    Blend.uPixelABG0 = 1;
    Blend.uPixelABG1 = 0;
    Blend.uPixelBBG2 = 1;
    Blend.uPixelBBackdrop = 1;
    Blend.nRate = 1;
    Blend.uCoeffA = 0;
    Blend.nEndA = 16;
    Blend.nDeltaA = 1;
    Blend.uCoeffB = 16;
    Blend.nEndB = 0;
    Blend.nDeltaB = -1;
}       

void BdBlendTextOut(void)
{
    Blend.uBlendMode = BLEND_ALPHA;
    Blend.uPixelABG0 = 1;
    Blend.uPixelABG1 = 0;
    Blend.uPixelBBG2 = 1;
    Blend.uPixelBBackdrop = 1;
    Blend.nRate = 1;
    Blend.uCoeffA = 16;
    Blend.nEndA = 0;
    Blend.nDeltaA = -1;
    Blend.uCoeffB = 0;
    Blend.nEndB = 16;
    Blend.nDeltaB = 1;
}       
