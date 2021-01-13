#include    "Socrates.h"
#include    "BdScroll.h"

#include    "BdMap.h"
#include    "BdMan.h"
#include    "BdBackground.h"

static int       nScrollPosX;
static int       nScrollPosY;

static bool      boScrolling;

static int       nScrollPixelMinX;
static int       nScrollPixelMinY;
static int       nScrollPixelMaxX;
static int       nScrollPixelMaxY;

static const int nScrollScreenMidX = GFX_SCREEN_PIXEL_WIDTH/2;
static const int nScrollScreenMidY = GFX_SCREEN_PIXEL_HEIGHT/2;
static const int nScrollStartMinX  = GFX_SCREEN_PIXEL_WIDTH/3;
static const int nScrollStartMinY  = GFX_SCREEN_PIXEL_HEIGHT/3;
static const int nScrollStartMaxX  = 2 * GFX_SCREEN_PIXEL_WIDTH/3;
static const int nScrollStartMaxY  = 2 * GFX_SCREEN_PIXEL_HEIGHT/3;
static const int nScrollCentreRate = 2;

//------------------------------------------------------------------------

void Scroll_Init(void)
{
    nScrollPosX = nScrollScreenMidX;
    nScrollPosY = nScrollScreenMidY;
    boScrolling = false;
}       

//------------------------------------------------------------------------

void Scroll_Begin(void)
{
    int    nLine;
    int    nCol;
    int    nMinX;
    int    nMinY;
    int    nMaxX;
    int    nMaxY;
    int    nTile;

    // find edges
    nMinX = MAP_MAX_X-1;
    nMaxX = 0;
    nMinY = MAP_MAX_Y-1;
    nMaxY = 0;
    for (nLine=0; nLine<MAP_MAX_Y; nLine++)
    {
        for (nCol=0; nCol<MAP_MAX_X; nCol++)
        {
            nTile = uMap[nCol][nLine];

            switch(nTile)
            {
                case MAP_EDGE:
                case MAP_EDGE2:
                case MAP_EDGE3:
                case MAP_EDGE4:
                case MAP_HOME:
                case MAP_SKY_1:
                case MAP_SKY_2:
                case MAP_SKY_3:
                case MAP_SKY_4:
                case MAP_SKY_5:
                case MAP_SKY_6:
                case MAP_SKY_7:
                case MAP_SKY_8:
                case MAP_SKY_9:
                case MAP_SKY_10:
                    break;

                default:
                    if (nCol < nMinX) nMinX = nCol;
                    if (nCol > nMaxX) nMaxX = nCol;
                    if (nLine < nMinY) nMinY = nLine;
                    if (nLine > nMaxY) nMaxY = nLine;
            }
        }
    } 

    nScrollPixelMinX = (nMinX - 1) * 8 * 2;
    nScrollPixelMaxX = (nMaxX + 2) * 8 * 2;
    nScrollPixelMinY = (nMinY - 1) * 8 * 2;
    nScrollPixelMaxY = (nMaxY + 2) * 8 * 2;
}

//------------------------------------------------------------------------

void Scroll_Update(void)
{
    int    nManPixelPosX;
    int    nManPixelPosY;
    int    nDeltaX;
    int    nDeltaY;

    nManPixelPosX = Man_GetX() * 2 * 8 + 8 - nScrollPosX;
    nManPixelPosY = Man_GetY() * 2 * 8 + 8 - nScrollPosY;
    nDeltaX = 0;
    nDeltaY = 0;

    if (!boScrolling)
    {
        if ((nManPixelPosX > nScrollStartMaxX + nScrollCentreRate) 
         && (GFX_SCREEN_PIXEL_WIDTH + nScrollPosX < nScrollPixelMaxX))
        {
            boScrolling = true;
        }

        if ((nManPixelPosX < nScrollStartMinX - nScrollCentreRate)
         && (nScrollPosX > nScrollPixelMinX))
        {
            boScrolling = true;
        }

        if ((nManPixelPosY > nScrollStartMaxY + nScrollCentreRate) 
         && (GFX_SCREEN_PIXEL_HEIGHT + nScrollPosY < nScrollPixelMaxY))
        {
            boScrolling = true;
        }

        if ((nManPixelPosY < nScrollStartMinY - nScrollCentreRate) 
         && (nScrollPosY > nScrollPixelMinY))
        {
            boScrolling = true;
        }
    }

    if (boScrolling)
    {
        if ((nManPixelPosX > nScrollScreenMidX + nScrollCentreRate) 
         && (GFX_SCREEN_PIXEL_WIDTH + nScrollPosX < nScrollPixelMaxX))
        {
            nDeltaX = nScrollCentreRate;
        }

        if ((nManPixelPosX < nScrollScreenMidX - nScrollCentreRate) 
         && (nScrollPosX > nScrollPixelMinX))
        {
            nDeltaX = -nScrollCentreRate;
        }

        if ((nManPixelPosY > nScrollScreenMidY + nScrollCentreRate) 
         && (GFX_SCREEN_PIXEL_HEIGHT + nScrollPosY < nScrollPixelMaxY))
        {
            nDeltaY = nScrollCentreRate;
        }

        if ((nManPixelPosY < nScrollScreenMidY - nScrollCentreRate) 
         && (nScrollPosY > nScrollPixelMinY))
        {
            nDeltaY = -nScrollCentreRate;
        }
        nScrollPosX += nDeltaX;
        nScrollPosY += nDeltaY;

        if (nDeltaX == 0 && nDeltaY == 0)
        {
            boScrolling = false;
        }
    }
}

//------------------------------------------------------------------------

void Scroll_Render(void)
{
    BdBackgroundScrollSet(2, nScrollPosX % 16, nScrollPosY % 16);
}

//------------------------------------------------------------------------

int Scroll_GetX(void)
{
    return(nScrollPosX/16);
}

//------------------------------------------------------------------------

int Scroll_GetY(void)
{
    return(nScrollPosY/16);
}

//------------------------------------------------------------------------
