#include    "Socrates.h"
#include    "SoKeys.h"
#include    "SoMath.h"

#include    "BdMan.h"

#include    "BdGfxData.h"
#include    "BdScroll.h"
#include    "BdStats.h"
#include    "BdMap.h"
#include    "BdRnd.h"
#include    "BdVblank.h"
#include    "BdBackground.h"


#define MAN_WALK_ANIMS          8

//----------------------------------------------------------------------------

static const u16 Man_Graphic[MAN_TYPES_MAX] = {
    GFX_MAN, 
    GFX_MAN_BLINK1, 
    GFX_MAN_BLINK2, 
    GFX_MAN_TAP1, 
    GFX_MAN_TAP2,
    GFX_MAN_LEFT1, 
    GFX_MAN_LEFT2, 
    GFX_MAN_LEFT3, 
    GFX_MAN_LEFT4,  
    GFX_MAN_LEFT5, 
    GFX_MAN_LEFT6, 
    GFX_MAN_LEFT7, 
    GFX_MAN_LEFT8,  
    GFX_MAN_RIGHT1, 
    GFX_MAN_RIGHT2, 
    GFX_MAN_RIGHT3, 
    GFX_MAN_RIGHT4,
    GFX_MAN_RIGHT5, 
    GFX_MAN_RIGHT6, 
    GFX_MAN_RIGHT7, 
    GFX_MAN_RIGHT8,
    GFX_MAN_BIRTH1,
    GFX_MAN_BIRTH2,
    GFX_MAN_BIRTH3,
    GFX_MAN_BIRTH4,
    GFX_MAN_BIRTH5,
    GFX_MAN_BIRTH6,
    GFX_MAN_BIRTH7,
    GFX_MAN_BIRTH8
};

static u16 Man_Tile[MAP_TYPES_MAX*4]__attribute__ ((section (".ewram")));

//----------------------------------------------------------------------------

static int              nManX;
static int              nManY;
static bool             boManHome;
static bool             boManAlive;
static bool             boManGrab;
static bool             boManPut;
static bool             boManStarted;
static bool             boManBorn;
static u32              uManMoveType;

static u32              uManGfxCount;
static int              nManRequestX;
static int              nManRequestY;
static int              nManRequestPrevX;
static int              nManRequestPrevY;
static int              nManLastDirection;
static int              nManSpecial;

static u32              uManControlTimer;
static const u32        uManControlDelay = 10;
static u32              uManBornTimer;
static const u32        uManBornDelay = 216;
static const u32        uManBirthDelay = 8;

static u32              uTeleportDst = 0;
static u32              uSwitchDoor = 0;
static bool             uManHasBomb = false;
static bool             uPassedUnderDwall = false;
//----------------------------------------------------------------------------

void Man_Init(void)
{
    int nGraphic;

    // get indexed tiles from graphics
    for (nGraphic = 0; nGraphic < MAN_TYPES_MAX; nGraphic++)
    {
        Man_Tile[nGraphic * 4 + 0] = BdBackgroundTileFromGraphic(Man_Graphic[nGraphic]);
        Man_Tile[nGraphic * 4 + 1] = BdBackgroundTileFromGraphic(Man_Graphic[nGraphic] + 1);
        Man_Tile[nGraphic * 4 + 2] = BdBackgroundTileFromGraphic(Man_Graphic[nGraphic] + 40);
        Man_Tile[nGraphic * 4 + 3] = BdBackgroundTileFromGraphic(Man_Graphic[nGraphic] + 41);
    }

    uManHasBomb = false;

    uTeleportDst = 0;
}

//----------------------------------------------------------------------------

void Man_Begin(void)
{
    int    nLine;
    int    nCol;

    for (nLine=0; nLine < MAP_MAX_Y; nLine++)
    {
        for (nCol=0; nCol < MAP_MAX_X; nCol++)
        {
            if (uMap[nCol][nLine] == MAP_START)
            {
                nManX = nCol; 
                nManY = nLine;
            }
        }
    }

    boManHome = false;
    boManAlive = true;
    boManStarted = false;
    boManBorn = false;

    uManGfxCount = 0;
    nManRequestX = 0;
    nManRequestY = 0;
    nManLastDirection = MAN_LEFT1;
    nManSpecial = MAN_NORMAL;

    BdVblankTimerSet(&uManControlTimer, 0);
    BdVblankTimerSet(&uManBornTimer, uManBornDelay);
}

//----------------------------------------------------------------------------

void Man_Render(void)
{
    int    nTileIndex;                                               
    int    nWalkCount;
    
    nTileIndex = MAN_NORMAL;

    if (boManStarted && boManAlive)
    {
        if (nManRequestX == nManRequestPrevX && nManRequestY == nManRequestPrevY)
        {
            uManGfxCount++;
        }
        else
        {
            nManSpecial = MAN_NORMAL;
            uManGfxCount = 0;
        }

        if (nManRequestX > 0)   nTileIndex = MAN_RIGHT1;
        if (nManRequestX < 0)   nTileIndex = MAN_LEFT1;
        if (nManRequestY > 0)   nTileIndex = nManLastDirection;
        if (nManRequestY < 0)   nTileIndex = nManLastDirection;

        if (nTileIndex != MAN_NORMAL)
        {
            nManLastDirection = nTileIndex;
            nWalkCount = (uManGfxCount % (MAN_WALK_ANIMS * 2))/2;

            // cycle the walk anim
            if (nWalkCount >= MAN_WALK_ANIMS) 
                nTileIndex += MAN_WALK_ANIMS*2 - 1 - nWalkCount;
            else
                nTileIndex += nWalkCount;
        }
        else // man not moving
        {
            if (nManSpecial == MAN_NORMAL)
            {
                uManGfxCount = 0;
                if (BdRnd(100)<1) nManSpecial = MAN_TAP1;
                if (BdRnd(100)<1) nManSpecial = MAN_BLINK1;
            }
       
            if (nManSpecial == MAN_BLINK1)
            {
                nTileIndex = MAN_BLINK1 + (uManGfxCount % 4) / 2;
                if ((uManGfxCount % 4) == 3)
                {
                    nManSpecial = MAN_NORMAL;
                }
            }

            if (nManSpecial == MAN_TAP1)
            {
                nTileIndex = MAN_TAP1 + (uManGfxCount % 16) / 8;
                if (BdRnd(100)<2) 
                {
                    nManSpecial = MAN_NORMAL;
                }
            }
        }

        nManRequestPrevX = nManRequestX;
        nManRequestPrevY = nManRequestY;
    }

    if (boManBorn && boManAlive && !Map_FlashingWhite())
    {
        if (nManSpecial >= MAN_BIRTH_1 && nManSpecial <= MAN_BIRTH_8)
        {
            nTileIndex = nManSpecial;
        }

        Man_TileDraw( nManX - Scroll_GetX(), nManY - Scroll_GetY(), nTileIndex);
    }
}

//----------------------------------------------------------------------------

void Man_Update1(void)
{
    int    nDX;
    int    nDY;
    int    nTileLeft;
    int    nTileRight;
    int    nTileUp;
    int    nTileDown;

    nDX = 0;
    nDY = 0;

    if (boManStarted && boManAlive)
    {
        if (SoKeysDown(SO_KEY_UP))    nDY = -1;
        if (SoKeysDown(SO_KEY_DOWN))  nDY = 1;
        if (SoKeysDown(SO_KEY_LEFT))  nDX = -1;
        if (SoKeysDown(SO_KEY_RIGHT)) nDX = 1;

        // don't allow diagonals
        if (nDY != 0)   nDX = 0; 

        if (BdVblankTimerMature(&uManControlTimer))
        {
            nManRequestX = nDX;
            nManRequestY = nDY;

            // check for death by square or butterfly
            nTileLeft  = uMap[nManX - 1][nManY] & MAP_TILE_MASK;
            nTileRight = uMap[nManX + 1][nManY] & MAP_TILE_MASK;
            nTileUp    = uMap[nManX][nManY - 1] & MAP_TILE_MASK;
            nTileDown  = uMap[nManX][nManY + 1] & MAP_TILE_MASK;

            if(nTileUp == MAP_DWALL)
            {
                uPassedUnderDwall = true;
            }

            // felpupososdas
            if(nTileUp == MAP_EDGE2)
            {
                uMap[nManX][nManY-1] = MAP_EDGE4;
            }

            if ((nTileLeft == MAP_SQUARE_L) || 
                (nTileRight == MAP_SQUARE_L) || 
                (nTileUp == MAP_SQUARE_L) || 
                (nTileDown == MAP_SQUARE_L))
            {
                Map_TileExplode( nManX, nManY, false);
                boManAlive = false;
            }

            if ((nTileLeft == MAP_BUTTERFLY_L) || 
                (nTileRight == MAP_BUTTERFLY_L) || 
                (nTileUp == MAP_BUTTERFLY_L) || 
                (nTileDown == MAP_BUTTERFLY_L))
            {
                Map_TileExplode( nManX, nManY, true);
                boManAlive = false;
            }

            if ((nTileLeft == MAP_GREEN_L) || 
                (nTileRight == MAP_GREEN_L) || 
                (nTileUp == MAP_GREEN_L) || 
                (nTileDown == MAP_GREEN_L))
            {
                Map_TileExplode( nManX, nManY, false);
                boManAlive = false;
            }
        }
    }
}

//----------------------------------------------------------------------------

void Man_Update2(void)
{
    int    nTileAbove;

    if (boManStarted && boManAlive)
    {
        if (BdVblankTimerMature(&uManControlTimer))
        {
            // check if caught in an explosion
            if (uMap[nManX][nManY] != MAP_MAN)
            {
                boManAlive = false;
            }

            // move him
            if ((boManAlive) && (nManRequestX != 0 || nManRequestY != 0))
            {
                boManGrab = false;
                if (SoKeysDown(SO_KEY_A))
                {
                    boManGrab = true;
                }

                boManPut = false;
                if (SoKeysDown(SO_KEY_B))
                {
                    boManPut = true;
                }

                uManMoveType = Man_CanMove(nManRequestX, nManRequestY); 
                if (uManMoveType != MAN_CANNOT_MOVE)
                {
                    Man_Move(nManRequestX, nManRequestY);
                }
            }

            // check for death by getting hit on the head
            nTileAbove = uMap[nManX][nManY-1];
            if (nTileAbove == MAP_BOULDER_FALLING || nTileAbove == MAP_DIAMOND_FALLING)
            {
                Map_TileExplode( nManX, nManY, MAP_DEATH_1);
                boManAlive = false;
            }

            BdVblankTimerSet(&uManControlTimer, uManControlDelay);
        }
    }

    if (boManBorn && !boManStarted)
    {
        if (BdVblankTimerMature(&uManBornTimer))
        {
            if (nManSpecial >= MAN_BIRTH_8)
            {
                Stats_TimerStart();
                BdVblankTimerSet(&uManControlTimer, 0);
                Map_UpdateTimerClear();                 // sync map and man timers
                boManStarted = true;
                nManSpecial = MAN_NORMAL;
                uMap[nManX][nManY] = MAP_MAN;
            }
            else
            {
                BdVblankTimerSet(&uManBornTimer, uManBirthDelay);
                nManSpecial++;
            }
        }
    }

    if (!boManBorn)
    {
        if (BdVblankTimerMature(&uManBornTimer))
        {
            BdVblankTimerSet(&uManBornTimer, uManBirthDelay);
            nManSpecial = MAN_BIRTH_1;
            boManBorn = true;
        }
    }
}

//----------------------------------------------------------------------------

void Man_TileDraw(int nX, int nY, int nTileIndex)
{
    u16   *pDestStart;
    u16   *pDest;

    nX *= 2;
    nY *= 2;

    if ((nX >= 0 && nX < GFX_TILE_MAP_WIDTH) && 
        (nY >= 0 && nY < (GFX_SCREEN_TILE_HEIGHT + 2)))
    {
        pDestStart = BdBackgroundSbbPtr(2);
        pDest = pDestStart + ((nY&31)<<5) + ((nX&31));
        nTileIndex *= 4;

        *pDest = Man_Tile[nTileIndex];
        *(pDest + 1) = Man_Tile[nTileIndex + 1];
        *(pDest + GFX_TILE_MAP_WIDTH) = Man_Tile[nTileIndex + 2];
        *(pDest + GFX_TILE_MAP_WIDTH + 1) = Man_Tile[nTileIndex + 3];
    }
}


void Man_Teleport(int tile)
{
    int    nLine;
    int    nCol;
    int    nTile;

    for (nLine = 1; nLine < MAP_MAX_Y-1; nLine++)
    {
        for (nCol = 1; nCol < MAP_MAX_X-1; nCol++)
        {
            nTile = uMap[nCol][nLine] & MAP_TILE_MASK;

            if(tile == nTile)
            {
                nManX = nCol;
                nManY = nLine;
                uTeleportDst = uMap[nCol][nLine];
//                uMap[nCol][nLine] = MAN_BIRTH_1;
                nManSpecial = MAN_BIRTH_1;
                boManStarted = false;

                break;
            }
        }
    }
}

static void Man_OpenCloseSwitchDoors(int tile, int a, int b, int c)
{
    int    nLine;
    int    nCol;
    int    nTile;
    bool   nAnyDoorsToUpdate = false;

    for (nLine = 1; nLine < MAP_MAX_Y-1; nLine++)
    {
        for (nCol = 1; nCol < MAP_MAX_X-1; nCol++)
        {
            nTile = uMap[nCol][nLine] & MAP_TILE_MASK;

            // update doors
            if((tile+b) == nTile)
            {
                uMap[nCol][nLine] +=c;
                nAnyDoorsToUpdate = true;
            }
        }
    }

    if(nAnyDoorsToUpdate)
    {
        for (nLine = 1; nLine < MAP_MAX_Y-1; nLine++)
        {
            for (nCol = 1; nCol < MAP_MAX_X-1; nCol++)
            {
                nTile = uMap[nCol][nLine] & MAP_TILE_MASK;
    
                // update switches
                if(tile == nTile)
                {
                    uMap[nCol][nLine] +=a;
                }
            }
        }
    }
}

u32 Man_CanMove(int nDX, int nDY)
{
    u32    uMoveType;
    int    nManNewX;
    int    nManNewY;
    int    nManTarget;
    int    nBoulderTarget;

    nManNewX = nManX + nDX;
    nManNewY = nManY + nDY;
    nManTarget = uMap[nManNewX][nManNewY];

    uMoveType = MAN_CANNOT_MOVE;

    switch(nManTarget)
    {
        case MAP_BLANK:
        case MAP_EARTH:
        case MAP_EARTH_1:
        case MAP_EARTH_2:
        case MAP_EARTH_3:
        case MAP_EARTH_4:
        case MAP_KEY_1:
        case MAP_KEY_2:
        case MAP_KEY_3:
        case MAP_DIAMOND:
            uMoveType = MAN_MOVE;
            break;

        case MAP_DOOR1_OPEN:
        case MAP_DOOR2_OPEN:
        case MAP_DOOR3_OPEN:
        case MAP_HOME_OPEN:
        case MAP_TELEPORT_1:
        case MAP_TELEPORT_2:
        case MAP_TELEPORT_3:
        case MAP_TELEPORT_4:
        case MAP_TELEPORT_5:
        case MAP_TELEPORT_6:
        case MAP_TELEPORT_7:
        case MAP_TELEPORT_8:
        case MAP_TELEPORT_9:
        case MAP_TELEPORT_10:
        case MAP_TELEPORT_A_1:
        case MAP_TELEPORT_A_2:
        case MAP_TELEPORT_A_3:
        case MAP_TELEPORT_A_4:
        case MAP_TELEPORT_A_5:
        case MAP_TELEPORT_A_6:
        case MAP_TELEPORT_A_7:
        case MAP_TELEPORT_A_8:
        case MAP_TELEPORT_A_9:
        case MAP_TELEPORT_A_10:
        case MAP_SWITCH_DOOR_OPEN_1:
        case MAP_SWITCH_DOOR_OPEN_2:
        case MAP_SWITCH_DOOR_OPEN_3:
        case MAP_SWITCH_DOOR_OPEN_4:
        case MAP_SWITCH_DOOR_OPEN_5:
        case MAP_SWITCH_DOOR_OPEN_6:
        case MAP_SWITCH_DOOR_OPEN_7:
        case MAP_SWITCH_DOOR_OPEN_8:
        case MAP_SWITCH_DOOR_OPEN_9:
        case MAP_SWITCH_DOOR_OPEN_10:
            if(!boManGrab)
                uMoveType = MAN_MOVE;
            break;

        case MAP_BOMB:
            if(!uManHasBomb)
            {
                uManHasBomb = true;
                uMoveType = MAN_MOVE;
            }
            break;

        case MAP_SWITCH_OFF_1:
        case MAP_SWITCH_OFF_2:
        case MAP_SWITCH_OFF_3:
        case MAP_SWITCH_OFF_4:
        case MAP_SWITCH_OFF_5:
        case MAP_SWITCH_OFF_6:
        case MAP_SWITCH_OFF_7:
        case MAP_SWITCH_OFF_8:
        case MAP_SWITCH_OFF_9:
        case MAP_SWITCH_OFF_10:
            if(boManGrab)
            Man_OpenCloseSwitchDoors(nManTarget,36,-10,56);
            break;

        case MAP_SWITCH_ON_1:
        case MAP_SWITCH_ON_2:
        case MAP_SWITCH_ON_3:
        case MAP_SWITCH_ON_4:
        case MAP_SWITCH_ON_5:
        case MAP_SWITCH_ON_6:
        case MAP_SWITCH_ON_7:
        case MAP_SWITCH_ON_8:
        case MAP_SWITCH_ON_9:
        case MAP_SWITCH_ON_10:
            if(boManGrab)
            Man_OpenCloseSwitchDoors(nManTarget,-36,10,-56);
            break;

        case MAP_BOULDER:
            nBoulderTarget = uMap[nManNewX+nDX][nManNewY+nDY];
            if (nDY == 0 && nBoulderTarget == MAP_BLANK)
            {
                if (SoMathRand()>>24)
                {
                    uMoveType = MAN_PUSH_BOULDER;
                }
            }
    }

    return(uMoveType);
}

void Man_UpdateDoors(int tile)
{
    int    nLine;
    int    nCol;
    int    nTile;

    for (nLine = 1; nLine < MAP_MAX_Y-1; nLine++)
    {
        for (nCol = 1; nCol < MAP_MAX_X-1; nCol++)
        {
            nTile = uMap[nCol][nLine] & MAP_TILE_MASK;

            if(tile == nTile)
            {
                uMap[nCol][nLine] +=72;
            }
        }
    }
}

void Man_Move(int nDX, int nDY)
{
    int    nManTarget;
    int    nNewX;
    int    nNewY;

    if (uManMoveType != MAN_CANNOT_MOVE)
    {
        nNewX = nManX + nDX;
        nNewY = nManY + nDY;
        nManTarget = uMap[nNewX][nNewY];

        if (!boManGrab && !boManPut)
        {
            if(uTeleportDst)
            {
                uMap[nManX][nManY] = uTeleportDst;
                uTeleportDst = 0;
            }
            else if(uPassedUnderDwall)
            {
                uMap[nManX][nManY] = MAP_BOULDER;
                uPassedUnderDwall = false;
            }
            else
            {
                uMap[nManX][nManY] = MAP_BLANK;
            }

            if(uSwitchDoor)
            {
                uMap[nManX][nManY] = uSwitchDoor;
                uSwitchDoor = 0;
            }   
                
            nManX = nNewX;
            nManY = nNewY;
            uMap[nManX][nManY] = MAP_MAN;
        }       
                
        if(boManGrab /*&& !uCantGrab*/)
        {       
            uMap[nNewX][nNewY] = MAP_BLANK;
//            uCantGrab = false;
        }

        if(boManPut && uManHasBomb && (uMap[nNewX][nNewY] == MAP_BLANK))
        {
            uMap[nNewX][nNewY] = MAP_BOMB_ON_1;
            uManHasBomb = false;
        }

        if (uManMoveType == MAN_PUSH_BOULDER)
        {
            uMap[nNewX + nDX][nNewY + nDY] = MAP_BOULDER;
        }

        switch(nManTarget)
        {
            case MAP_DIAMOND:
                Stats_DiamondGot();
                break;

            case MAP_TELEPORT_1:
            case MAP_TELEPORT_2:
            case MAP_TELEPORT_3:
            case MAP_TELEPORT_4:
            case MAP_TELEPORT_5:
            case MAP_TELEPORT_6:
            case MAP_TELEPORT_7:
            case MAP_TELEPORT_8:
            case MAP_TELEPORT_9:
            case MAP_TELEPORT_10:
                Man_Teleport(nManTarget+10);
                uMap[nNewX][nNewY] = nManTarget;
                break;
        
            case MAP_TELEPORT_A_1:
            case MAP_TELEPORT_A_2:
            case MAP_TELEPORT_A_3:
            case MAP_TELEPORT_A_4:
            case MAP_TELEPORT_A_5:
            case MAP_TELEPORT_A_6:
            case MAP_TELEPORT_A_7:
            case MAP_TELEPORT_A_8:
            case MAP_TELEPORT_A_9:
            case MAP_TELEPORT_A_10:
                Man_Teleport(nManTarget-10);
                uMap[nNewX][nNewY] = nManTarget;
                break;

            case MAP_SWITCH_DOOR_OPEN_1:
            case MAP_SWITCH_DOOR_OPEN_2:
            case MAP_SWITCH_DOOR_OPEN_3:
            case MAP_SWITCH_DOOR_OPEN_4:
            case MAP_SWITCH_DOOR_OPEN_5:
            case MAP_SWITCH_DOOR_OPEN_6:
            case MAP_SWITCH_DOOR_OPEN_7:
            case MAP_SWITCH_DOOR_OPEN_8:
            case MAP_SWITCH_DOOR_OPEN_9:
            case MAP_SWITCH_DOOR_OPEN_10:
                uSwitchDoor = nManTarget;
                break;

            case MAP_KEY_1:
                Man_UpdateDoors(MAP_DOOR_1);
                break;

            case MAP_KEY_2:
                Man_UpdateDoors(MAP_DOOR_2);
                break;

            case MAP_KEY_3:
                Man_UpdateDoors(MAP_DOOR_3);
                break;

            case MAP_HOME_OPEN:
                boManHome = true;
                break;
        }
    }
}

//----------------------------------------------------------------------------

int Man_GetX(void)
{
    return(nManX);
}

//----------------------------------------------------------------------------

int Man_GetY(void)
{
    return(nManY);
}

//----------------------------------------------------------------------------

bool Man_Home(void)
{
    return boManHome;
}

//----------------------------------------------------------------------------

void Man_Remove(void)
{
    boManAlive = false;
}

//----------------------------------------------------------------------------

bool Man_Alive(void)
{
    return boManAlive;
}       

//----------------------------------------------------------------------------

bool Man_Born(void)
{
    return boManBorn;
}       

//----------------------------------------------------------------------------
