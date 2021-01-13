#include    "Socrates.h"
#include    "SoMath.h"

#include    "BdMap.h"

#include    "BdMapData.h"
#include    "BdGfxdata.h"
#include    "BdScroll.h"
#include    "BdStats.h"
#include    "BdMusic.h"
#include    "BdVblank.h"
#include    "BdMenu.h"
#include    "BdMan.h"
#include    "BdRnd.h"
#include    "BdBackground.h"

//----------------------------------------------------------------------------

u16 uMap[MAP_MAX_X][MAP_MAX_Y]__attribute__ ((section (".ewram")));

const u16 Map_Graphic[MAP_TYPES_MAX] = 
{
    GFX_EARTH,              // MAP_EARTH,                                
    GFX_BB_1,               // MAP_EARTH_1,                              
    GFX_BB_2,               // MAP_EARTH_2,                              
    GFX_BB_3,               // MAP_EARTH_3,                              
    GFX_BB_4,               // MAP_EARTH_4,                              
    GFX_WALL,               // MAP_WALL,                                 
    GFX_WALL,               // MAP_DWALL, // MAP_GWALL                   
    GFX_DOOR_1,             // MAP_DOOR_1,                               
    GFX_DOOR_2,             // MAP_DOOR_2,                               
    GFX_DOOR_3,             // MAP_DOOR_3,                               
    GFX_KEY_1,              // MAP_KEY_1,                                
    GFX_KEY_2,              // MAP_KEY_2,                                
    GFX_KEY_3,              // MAP_KEY_3,                                
    GFX_BOMB,               // MAP_BOMB,                                 
    GFX_DIAMOND_1,          // MAP_DIAMOND,                              
    GFX_BOULDER,            // MAP_BOULDER,                              
    GFX_GROUND_EARTH,       // MAP_EDGE2,
    GFX_GROUND_ROCK,        // MAP_EDGE3,                                
    GFX_BLANK,              // MAP_BLANK,                                
    GFX_GROUND_DISTURBED,   // MAP_EDGE4,                                
    GFX_SKY_1,              // MAP_SKY_1,                                
    GFX_SKY_2,              // MAP_SKY_2,                                
    GFX_SKY_3,              // MAP_SKY_3,                                
    GFX_SKY_4,              // MAP_SKY_4,                                
    GFX_SKY_5,              // MAP_SKY_5,                                
    GFX_SKY_6,              // MAP_SKY_6,                                
    GFX_SKY_7,              // MAP_SKY_7,                                
    GFX_SKY_8,              // MAP_SKY_8,                                
    GFX_SKY_9,              // MAP_SKY_9,                                
    GFX_SKY_10,             // MAP_SKY_10,                               
    GFX_EDGE,               // MAP_EDGE,                                 
    GFX_EDGE,               // MAP_START,                                
    GFX_SQUARE_L1,          // MAP_SQUARE_L,                               
    GFX_BUTTERFLY_L1,       // MAP_BUTTERFLY_L,                            
    GFX_GREEN_L1,           // MAP_GREEN_L,                                
    GFX_HOME,               // MAP_HOME,                                 
    GFX_DOOR_4,             // MAP_SWITCH_DOOR_1,                        
    GFX_DOOR_4,             // MAP_SWITCH_DOOR_2,                        
    GFX_DOOR_4,             // MAP_SWITCH_DOOR_3,                        
    GFX_DOOR_4,             // MAP_SWITCH_DOOR_4,                        
    GFX_DOOR_4,             // MAP_SWITCH_DOOR_5,                        
    GFX_DOOR_4,             // MAP_SWITCH_DOOR_6,                        
    GFX_DOOR_4,             // MAP_SWITCH_DOOR_7,                        
    GFX_DOOR_4,             // MAP_SWITCH_DOOR_8,                        
    GFX_DOOR_4,             // MAP_SWITCH_DOOR_9,                        
    GFX_DOOR_4,             // MAP_SWITCH_DOOR_10,                       
    GFX_SWITCH_OFF,         // MAP_SWITCH_OFF_1,                             
    GFX_SWITCH_OFF,         // MAP_SWITCH_OFF_2,                             
    GFX_SWITCH_OFF,         // MAP_SWITCH_OFF_3,                             
    GFX_SWITCH_OFF,         // MAP_SWITCH_OFF_4,                             
    GFX_SWITCH_OFF,         // MAP_SWITCH_OFF_5,                             
    GFX_SWITCH_OFF,         // MAP_SWITCH_OFF_6,                             
    GFX_SWITCH_OFF,         // MAP_SWITCH_OFF_7,                             
    GFX_SWITCH_OFF,         // MAP_SWITCH_OFF_8,                             
    GFX_SWITCH_OFF,         // MAP_SWITCH_OFF_9,                             
    GFX_SWITCH_OFF,         // MAP_SWITCH_OFF_10,                            
    GFX_TELEPORT_1,         // MAP_TELEPORT_1,                           
    GFX_TELEPORT_1,         // MAP_TELEPORT_2,                           
    GFX_TELEPORT_1,         // MAP_TELEPORT_3,                           
    GFX_TELEPORT_1,         // MAP_TELEPORT_4,                           
    GFX_TELEPORT_1,         // MAP_TELEPORT_5,                           
    GFX_TELEPORT_1,         // MAP_TELEPORT_6,                           
    GFX_TELEPORT_1,         // MAP_TELEPORT_7,                           
    GFX_TELEPORT_1,         // MAP_TELEPORT_8,                           
    GFX_TELEPORT_1,         // MAP_TELEPORT_9,                           
    GFX_TELEPORT_1,         // MAP_TELEPORT_10,                          
    GFX_TELEPORT_1,         // MAP_TELEPORT_A_1,                         
    GFX_TELEPORT_1,         // MAP_TELEPORT_A_2,                         
    GFX_TELEPORT_1,         // MAP_TELEPORT_A_3,                         
    GFX_TELEPORT_1,         // MAP_TELEPORT_A_4,                         
    GFX_TELEPORT_1,         // MAP_TELEPORT_A_5,                         
    GFX_TELEPORT_1,         // MAP_TELEPORT_A_6,                         
    GFX_TELEPORT_1,         // MAP_TELEPORT_A_7,                         
    GFX_TELEPORT_1,         // MAP_TELEPORT_A_8,                         
    GFX_TELEPORT_1,         // MAP_TELEPORT_A_9,                         
    GFX_TELEPORT_1,         // MAP_TELEPORT_A_10,                        
    GFX_MAN,                // MAP_MAN,                                  
    GFX_BOULDER,            // MAP_BOULDER_FALLING,                      
    GFX_DIAMOND_1,          // MAP_DIAMOND_FALLING,                      
    GFX_DOOR1_OPEN,         // MAP_DOOR1_OPEN,                           
    GFX_DOOR2_OPEN,         // MAP_DOOR2_OPEN,                           
    GFX_DOOR3_OPEN,         // MAP_DOOR3_OPEN,                           
    GFX_SWITCH_ON,          // MAP_SWITCH_ON_1,                             
    GFX_SWITCH_ON,          // MAP_SWITCH_ON_2,                             
    GFX_SWITCH_ON,          // MAP_SWITCH_ON_3,                             
    GFX_SWITCH_ON,          // MAP_SWITCH_ON_4,                             
    GFX_SWITCH_ON,          // MAP_SWITCH_ON_5,                             
    GFX_SWITCH_ON,          // MAP_SWITCH_ON_6,                             
    GFX_SWITCH_ON,          // MAP_SWITCH_ON_7,                             
    GFX_SWITCH_ON,          // MAP_SWITCH_ON_8,                             
    GFX_SWITCH_ON,          // MAP_SWITCH_ON_9,                             
    GFX_SWITCH_ON,          // MAP_SWITCH_ON_10,                            
    GFX_DOOR4_OPEN,         // MAP_SWITCH_DOOR_OPEN_1, 
    GFX_DOOR4_OPEN,         // MAP_SWITCH_DOOR_OPEN_2, 
    GFX_DOOR4_OPEN,         // MAP_SWITCH_DOOR_OPEN_3, 
    GFX_DOOR4_OPEN,         // MAP_SWITCH_DOOR_OPEN_4, 
    GFX_DOOR4_OPEN,         // MAP_SWITCH_DOOR_OPEN_5, 
    GFX_DOOR4_OPEN,         // MAP_SWITCH_DOOR_OPEN_6, 
    GFX_DOOR4_OPEN,         // MAP_SWITCH_DOOR_OPEN_7, 
    GFX_DOOR4_OPEN,         // MAP_SWITCH_DOOR_OPEN_8, 
    GFX_DOOR4_OPEN,         // MAP_SWITCH_DOOR_OPEN_9, 
    GFX_DOOR4_OPEN,         // MAP_SWITCH_DOOR_OPEN_10,
    GFX_HOME_OPEN,          // MAP_HOME_OPEN
    GFX_SQUARE_R1,          // MAP_SQUARE_R,                               
    GFX_BUTTERFLY_R1,       // MAP_BUTTERFLY_R,                            
    GFX_GREEN_R1,           // MAP_GREEN_R,                                
/*
    GFX_MAN_UNBIRTH1,
    GFX_MAN_UNBIRTH2,
    GFX_MAN_UNBIRTH3,
    GFX_MAN_UNBIRTH4,
    GFX_MAN_UNBIRTH5,
    GFX_MAN_UNBIRTH6,
    GFX_MAN_UNBIRTH7,
    GFX_MAN_UNBIRTH8,
*/
    GFX_BLANK,              // MAP_BASE_MAX,

    GFX_SQUARE_L1,          // MAP_SQUARE_NOT_MOVED,
    GFX_BUTTERFLY_L1,       // MAP_BUTTERFLY_NOT_MOVED,
    GFX_GREEN_L1,           // MAP_GREEN_NOT_MOVED,
    GFX_EDGE,               // MAP_START_1,
    GFX_BLANK,              // MAP_START_2,
    GFX_DIAMOND_1,          // MAP_DIAMOND_1,
    GFX_DIAMOND_2,          // MAP_DIAMOND_2,
    GFX_DIAMOND_3,          // MAP_DIAMOND_3,
    GFX_DIAMOND_4,          // MAP_DIAMOND_4,
    GFX_DIAMOND_5,          // MAP_DIAMOND_5,
    GFX_DIAMOND_6,          // MAP_DIAMOND_6,
    GFX_DIAMOND_7,          // MAP_DIAMOND_5,
    GFX_DIAMOND_8,          // MAP_DIAMOND_6,
    GFX_DEATH_1,            // MAP_DEATH_1,
    GFX_DEATH_2,            // MAP_DEATH_2,
    GFX_DEATH_3,            // MAP_DEATH_3,
    GFX_DEATH_4,            // MAP_DEATH_4,
    GFX_DEATH_5,            // MAP_DEATH_5,
    GFX_DEATH_6,            // MAP_DEATH_6,
    GFX_DEATH_7,            // MAP_DEATH_7,
    GFX_DEATH_8,            // MAP_DEATH_8,
    GFX_BFLY_DEATH_1,       // MAP_BFLY_DEATH_1,
    GFX_BFLY_DEATH_1,       // MAP_BFLY_DEATH_2,
    GFX_BFLY_DEATH_2,       // MAP_BFLY_DEATH_3,
    GFX_BFLY_DEATH_3,       // MAP_BFLY_DEATH_4,
    GFX_BFLY_DEATH_4,       // MAP_BFLY_DEATH_5,
    GFX_BUTTERFLY_L1,       // MAP_BUTTERFLY_L1,     
    GFX_BUTTERFLY_L2,       // MAP_BUTTERFLY_L2,
    GFX_BUTTERFLY_L3,       // MAP_BUTTERFLY_L3,
    GFX_BUTTERFLY_L4,       // MAP_BUTTERFLY_L4,
    GFX_SQUARE_L1,          // MAP_SQUARE_L1,
    GFX_SQUARE_L2,          // MAP_SQUARE_L2,
    GFX_SQUARE_L3,          // MAP_SQUARE_L3,
    GFX_SQUARE_L4,          // MAP_SQUARE_L4,
    GFX_GREEN_L1,           // MAP_GREEN_L1,
    GFX_GREEN_L2,           // MAP_GREEN_L2,
    GFX_GREEN_L3,           // MAP_GREEN_L3,
    GFX_GREEN_L4,           // MAP_GREEN_L4
    GFX_DWALL_1,            // MAP_DWALL_1,
    GFX_DWALL_2,            // MAP_DWALL_2,
    GFX_DWALL_3,            // MAP_DWALL_3,
    GFX_DWALL_4,            // MAP_DWALL_4,
    GFX_WHITE,              // MAP_WHITE,
    GFX_BOULDER,            // MAP_DWALL_BOULDER,
    GFX_DIAMOND_1,          // MAP_DWALL_DIAMOND,
    GFX_BOMB_ON_1,          // MAP_BOMB_ON_1,
    GFX_BOMB_ON_2,          // MAP_BOMB_ON_2,
    GFX_BOMB_ON_3,          // MAP_BOMB_ON_3,
    GFX_BOMB_ON_4,          // MAP_BOMB_ON_4,
    GFX_BOMB_ON_5,          // MAP_BOMB_ON_5,
    GFX_BOMB_ON_6,          // MAP_BOMB_ON_6,
    GFX_BOMB_ON_7,          // MAP_BOMB_ON_7,
    GFX_BOMB_ON_8,          // MAP_BOMB_ON_8 
    GFX_BUTTERFLY_R1,       // MAP_BUTTERFLY_R1,     
    GFX_BUTTERFLY_R2,       // MAP_BUTTERFLY_R2,
    GFX_BUTTERFLY_R3,       // MAP_BUTTERFLY_R3,
    GFX_BUTTERFLY_R4,       // MAP_BUTTERFLY_R4,
    GFX_SQUARE_R1,          // MAP_SQUARE_R1,
    GFX_SQUARE_R2,          // MAP_SQUARE_R2,
    GFX_SQUARE_R3,          // MAP_SQUARE_R3,
    GFX_SQUARE_R4,          // MAP_SQUARE_R4,
    GFX_GREEN_R1,           // MAP_GREEN_R1,
    GFX_GREEN_R2,           // MAP_GREEN_R2,
    GFX_GREEN_R3,           // MAP_GREEN_R3,
    GFX_GREEN_R4,           // MAP_GREEN_R4
};

static u16       Map_Tile[MAP_TYPES_MAX*4];
static u16       Map_RenderMod[MAP_BASE_MAX];

//----------------------------------------------------------------------------

const  int       nMapDirDeltaX[MAP_DIR_MAX] = { -1,  0,  1,  0};
const  int       nMapDirDeltaY[MAP_DIR_MAX] = {  0, -1,  0,  1};

#define MAP_DIRECTION_SHIFT     (8)

//----------------------------------------------------------------------------

static u32       uMapUpdateTimer;
static const u32 uMapUpdateDelay = 10;

static u32       uMapGfxTimer;
static u32       uMapGfxCount;
static const u32 uMapGfxTimerLen = 1;

static bool      boMapFlashWhite;
static bool      nMapFlashWhiteCount;

static bool      boMapTransition;
static u8        nMapTransitionRnd[MAP_MAX_X][MAP_MAX_Y];
static int       nMapTransitionCount;
static int       nMapTransitionStep;
static const u32 uMapTransitionLength = 140;

static u16       *pMap_DrawDestStart;
//----------------------------------------------------------------------------

void Map_Init(void)
{
    int    nGraphic;
    int    nX;
    int    nY;

    // get indexed tiles from graphics
    for (nGraphic = 0; nGraphic < MAP_TYPES_MAX; nGraphic++)
    {
        Map_Tile[nGraphic * 4 + 0] = BdBackgroundTileFromGraphic(Map_Graphic[nGraphic]);
        Map_Tile[nGraphic * 4 + 1] = BdBackgroundTileFromGraphic(Map_Graphic[nGraphic] + 1);
        Map_Tile[nGraphic * 4 + 2] = BdBackgroundTileFromGraphic(Map_Graphic[nGraphic] + 40);
        Map_Tile[nGraphic * 4 + 3] = BdBackgroundTileFromGraphic(Map_Graphic[nGraphic] + 41);
    }

    for (nY = 0; nY < MAP_MAX_Y; nY++)
    {
        for (nX = 0; nX < MAP_MAX_X; nX++)
        {
//            nMapTransitionRnd[nX][nY] = Rnd(uMapTransitionLength);
            nMapTransitionRnd[nX][nY] = (SoMathRand()>>25);
        }
    }

    for (nGraphic = 0; nGraphic < MAP_BASE_MAX; nGraphic++)
    {
        Map_RenderMod[nGraphic] = nGraphic;
    }
}

//----------------------------------------------------------------------------

void Map_Begin(u32 uLevel)
{

    u8    *pSrc = pMapData[uLevel];
    int    nX = 0, nY = 0;
    int    namelen = *pSrc++;
    u8     levelcode[16];
    u8    *lc = &levelcode[0];

    BdBackgroundClear(1);

    while(namelen--)
    {
        *lc++ = *pSrc++;
    }

    pSrc++;

    Stats_DiamondRequiredSet(*pSrc);
    pSrc++;
    Stats_TimerSet(*pSrc);
    pSrc++;

    for(nY=0;nY<MAP_MAX_Y;nY++)
    {
        for(nX=0;nX<MAP_MAX_X;nX++)
        {
            uMap[nX][nY] = *pSrc++;
        }
    }

    BdVblankTimerSet(&uMapUpdateTimer, 0);
    uMapGfxTimer = 0;
    uMapGfxCount = 0;
    boMapFlashWhite = false;
    Map_TransitionBegin(1);
}

//----------------------------------------------------------------------------

void Map_UpdateTimerClear(void)
{
    BdVblankTimerSet(&uMapUpdateTimer, 0);
}       

void Map_Process1(void)
{
    int    nLine;
    int    nCol;
    int    nTile;
    int    nDirection;

    for (nLine = 1; nLine < MAP_MAX_Y-1; nLine++)
    {
        for (nCol = 1; nCol < MAP_MAX_X-1; nCol++)
        {
            nTile = uMap[nCol][nLine] & MAP_TILE_MASK;
            switch (nTile)
            {
                case MAP_BOULDER_FALLING :
                {
                    uMap[nCol][nLine] = MAP_BOULDER + (MAP_DIR_DOWN << MAP_DIRECTION_SHIFT);
                    break;
                }
                case MAP_DIAMOND_FALLING :
                {
                    uMap[nCol][nLine] = MAP_DIAMOND + (MAP_DIR_DOWN << MAP_DIRECTION_SHIFT);
                    break;
                }
                case MAP_SQUARE_L :
                {
                    nDirection = (uMap[nCol][nLine] >> MAP_DIRECTION_SHIFT);
                    uMap[nCol][nLine] = MAP_SQUARE_NOT_MOVED + (nDirection << MAP_DIRECTION_SHIFT);
                    break;
                }
                case MAP_BUTTERFLY_L :
                {
                    nDirection = (uMap[nCol][nLine] >> MAP_DIRECTION_SHIFT);
                    uMap[nCol][nLine] = MAP_BUTTERFLY_NOT_MOVED + (nDirection << MAP_DIRECTION_SHIFT);
                    break;
                }
                case MAP_GREEN_L :
                {
                    nDirection = (uMap[nCol][nLine] >> MAP_DIRECTION_SHIFT);
                    uMap[nCol][nLine] = MAP_GREEN_NOT_MOVED + (nDirection << MAP_DIRECTION_SHIFT);
                    break;
                }
                case MAP_BFLY_DEATH_1 :
                {
                    uMap[nCol][nLine] = MAP_BFLY_DEATH_2;
                    break;
                }
                case MAP_DWALL:
                {
                    Map_ProcessDWall( nCol, nLine); 
                    break;
                }
            }
        }
    }
}

void Map_Process2(void)
{
    int    nLine;
    int    nCol;
    int    nTile;

    for (nLine = 1; nLine < MAP_MAX_Y-1; nLine++)
    {
        for (nCol = 1; nCol < MAP_MAX_X-1; nCol++)
        {
            nTile = uMap[nCol][nLine] & MAP_TILE_MASK;
            switch (nTile)
            {
                case MAP_BOULDER :
                    Map_ProcessDrop(nCol, nLine, MAP_BOULDER_FALLING);
                    break;

                case MAP_DIAMOND :
                    Map_ProcessDrop(nCol, nLine, MAP_DIAMOND_FALLING);
                    break;

                case MAP_SQUARE_NOT_MOVED :
                    Map_ProcessMove(nCol, nLine, MAP_SQUARE_L);
                    break;

                case MAP_BUTTERFLY_NOT_MOVED :
                    Map_ProcessMove(nCol, nLine, MAP_BUTTERFLY_L);
                    break;

                case MAP_GREEN_NOT_MOVED :
                    Map_ProcessMove(nCol, nLine, MAP_GREEN_L);
                    break;

                case MAP_BOMB_ON_1:
                case MAP_BOMB_ON_2:
                case MAP_BOMB_ON_3:
                case MAP_BOMB_ON_4:
                case MAP_BOMB_ON_5:
                case MAP_BOMB_ON_6:
                case MAP_BOMB_ON_7:
                    uMap[nCol][nLine] = nTile + 1;
                    break;

                case MAP_BOMB_ON_8:
                    Map_TileExplode(nCol, nLine, false);
                    break;

                case MAP_DEATH_1 :
                case MAP_DEATH_2 :
                case MAP_DEATH_3 :
                case MAP_DEATH_4 :
                case MAP_DEATH_5 :
                case MAP_DEATH_6 :
                case MAP_DEATH_7 :
                    uMap[nCol][nLine] = nTile + 1;
                    break;

                case MAP_DEATH_8 :
                    uMap[nCol][nLine] = MAP_BLANK;
                    break;

                case MAP_BFLY_DEATH_2 :
                case MAP_BFLY_DEATH_3 :
                case MAP_BFLY_DEATH_4 :
                    uMap[nCol][nLine] = nTile + 1;
                    break;

                case MAP_BFLY_DEATH_5 :
                    uMap[nCol][nLine] = MAP_DIAMOND;
                    break;

                case MAP_DWALL_DIAMOND :
                    uMap[nCol][nLine] = MAP_DIAMOND;
                    break;

                case MAP_DWALL_BOULDER :
                    uMap[nCol][nLine] = MAP_BOULDER;
                    break;
            }
        }
    }
}

void Map_Update(void)
{
    if (BdVblankTimerMature(&uMapUpdateTimer))
    {
        Map_Process1();
        Map_Process2();

        BdVblankTimerSet(&uMapUpdateTimer, uMapUpdateDelay);
    }

    uMapGfxTimer++;

    if (uMapGfxTimer >= uMapGfxTimerLen)
    {
        uMapGfxTimer = 0;
        uMapGfxCount++;
    }

    if (boMapFlashWhite)
    {
        if (nMapFlashWhiteCount > 0)
        {
            nMapFlashWhiteCount--;
        }
        else
        {
            boMapFlashWhite = false;
        }
    }
}


void Map_ProcessDrop(int nCol, int nLine, int nTarget)
{
    bool    boMoved;
    int     nTileDown;
    int     nTileLeft;
    int     nTileLeftDown;
    int     nTileRight;
    int     nTileRightDown;
    int     nDirection;

    boMoved = false;
    nTileDown =  uMap[nCol][nLine+1];
    if (nTileDown == MAP_BLANK)
    {
         uMap[nCol][nLine+1] = nTarget;
         boMoved = true;
    }

    if (nTileDown == MAP_BOULDER            // fails if boulder falling
     || nTileDown == MAP_DIAMOND
     || nTileDown == MAP_WALL)
    {

        if (!boMoved)
        {
            nTileLeft =  uMap[nCol-1][nLine];
            nTileLeftDown =  uMap[nCol-1][nLine+1];
            if (nTileLeft == MAP_BLANK && nTileLeftDown == MAP_BLANK)
            {
                uMap[nCol-1][nLine] = nTarget;
                boMoved = true;
            }
        }
        if (!boMoved)
        {
            nTileRight =  uMap[nCol+1][nLine];
            nTileRightDown =  uMap[nCol+1][nLine+1];
            if (nTileRight == MAP_BLANK && nTileRightDown == MAP_BLANK)
            {
                uMap[nCol+1][nLine] = nTarget;
                boMoved = true;
            }
        }
    }

    if (boMoved)
    {
        uMap[nCol][nLine] = MAP_BLANK;
    }

    if (!boMoved)
    {
        nDirection = (uMap[nCol][nLine] >> MAP_DIRECTION_SHIFT);
        if (nDirection == MAP_DIR_DOWN)
        {
            nTileDown = nTileDown & MAP_TILE_MASK;
            if ((nTileDown == MAP_SQUARE_L)
             || (nTileDown == MAP_SQUARE_NOT_MOVED))
            {
                Map_TileExplode(nCol, nLine+1, false);
            }

            if ((nTileDown == MAP_BUTTERFLY_L)
             || (nTileDown == MAP_BUTTERFLY_NOT_MOVED))
            {
                Map_TileExplode(nCol, nLine+1, false);
            }

            if ((nTileDown == MAP_GREEN_L)
             || (nTileDown == MAP_GREEN_NOT_MOVED))
            {
                Map_TileExplode(nCol, nLine+1, true);
            }

            if (nTileDown == MAP_BOMB)
            {
                Map_TileExplode(nCol, nLine+1, false);
            }

            uMap[nCol][nLine] = uMap[nCol][nLine] & MAP_TILE_MASK;
        }
    }
}       

void Map_ProcessMove(int nCol, int nLine, int nTarget)
{
    int     nNextTile;
    int     nNextLine;
    int     nNextCol;
    int     nDirection;

    nDirection = (uMap[nCol][nLine] >> MAP_DIRECTION_SHIFT);

    if(nTarget == MAP_BUTTERFLY_L) 
    {
        int dx = (nCol-Man_GetX());
        int dy = (nLine-Man_GetY());
    
        if((dx*dx)>(dy*dy))
        {
            if(dx>0) nDirection = MAP_DIR_RIGHT;
            else nDirection = MAP_DIR_LEFT;
        }
        else
        {
            if(dy>0) nDirection = MAP_DIR_UP;
            else nDirection = MAP_DIR_DOWN;
        }
    }

    nNextCol = nCol + nMapDirDeltaX[nDirection];
    nNextLine = nLine + nMapDirDeltaY[nDirection];
    nNextTile = uMap[nNextCol][nNextLine];

    if ((nNextTile == MAP_BLANK)||((MAP_SWITCH_DOOR_OPEN_1<=nNextTile)&&(MAP_SWITCH_DOOR_OPEN_10>=nNextTile)))
    {
        uMap[nNextCol][nNextLine] = nTarget + (nDirection << MAP_DIRECTION_SHIFT);
        uMap[nCol][nLine] = MAP_BLANK;
    }
    else
    {
        nDirection = (uMap[nCol][nLine] >> MAP_DIRECTION_SHIFT);
        nNextCol = nCol + nMapDirDeltaX[nDirection];
        nNextLine = nLine + nMapDirDeltaY[nDirection];
        nNextTile = uMap[nNextCol][nNextLine];

        if ((nNextTile == MAP_BLANK)||((MAP_SWITCH_DOOR_OPEN_1<=nNextTile)&&(MAP_SWITCH_DOOR_OPEN_10>=nNextTile)))
        {
            uMap[nNextCol][nNextLine] = nTarget + (nDirection << MAP_DIRECTION_SHIFT);
            uMap[nCol][nLine] = MAP_BLANK;
        }
        else
        {
            if(nTarget == MAP_BUTTERFLY_L)
            {
                nDirection = (nDirection + MAP_DIR_MAX - 1) % MAP_DIR_MAX;
            }
            else
            {
                nDirection = BdRndIWRAM(MAP_DIR_MAX);
            }

            uMap[nCol][nLine] = nTarget + (nDirection << MAP_DIRECTION_SHIFT);
        }
    }
}

void Map_ProcessDWall(int nCol, int nLine) 
{
    int     nTileUp;
    int     nDirection;

    nTileUp =  uMap[nCol][nLine-1];
    nDirection = nTileUp >> MAP_DIRECTION_SHIFT; 
    nTileUp =  nTileUp & MAP_TILE_MASK;
    if ((nTileUp == MAP_BOULDER || nTileUp == MAP_DIAMOND) && (nDirection == MAP_DIR_DOWN))
    {
        uMap[nCol][nLine-1] = MAP_BLANK;
        if (uMap[nCol][nLine+1] == MAP_BLANK)
        {
            uMap[nCol][nLine+1] = MAP_DWALL_DIAMOND;
        }
    }
}       

void Map_TileExplode(int nX, int nY, bool diamond)
{
    int    nLine;
    int    nCol;
    u16    *var;

    BdMusicPlaySfx(SFX_BOMB);

    for (nLine=0; nLine<3; nLine++)
    {
        for (nCol=0; nCol<3; nCol++)
        {
            var = &uMap[nX - 1 + nCol][nY - 1 + nLine];

            switch(*var)
            {
                case MAP_EDGE:
                case MAP_EDGE3:
                case MAP_DIAMOND_1:
                case MAP_DIAMOND_2:
                case MAP_DIAMOND_3:
                case MAP_DIAMOND_4:
                case MAP_DIAMOND_5:
                case MAP_DIAMOND_6:
                case MAP_DIAMOND_7:
                case MAP_DIAMOND_8:
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
                case MAP_KEY_1:
                case MAP_KEY_2:
                case MAP_KEY_3:
                case MAP_DOOR_1:
                case MAP_DOOR_2:
                case MAP_DOOR_3:
                case MAP_SWITCH_DOOR_1:
                case MAP_SWITCH_DOOR_2:
                case MAP_SWITCH_DOOR_3:
                case MAP_SWITCH_DOOR_4:
                case MAP_SWITCH_DOOR_5:
                case MAP_SWITCH_DOOR_6:
                case MAP_SWITCH_DOOR_7:
                case MAP_SWITCH_DOOR_8:
                case MAP_SWITCH_DOOR_9:
                case MAP_SWITCH_DOOR_10:
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
                    break;

                case MAP_EDGE2:
                    *var = MAP_EDGE4;
                    break;

                case MAP_BOMB:
                case MAP_GREEN_L:
                case MAP_BUTTERFLY_L:
                case MAP_SQUARE_L:
                    *var = MAP_BOMB_ON_8;
                    break;

                default:
                    *var = MAP_DEATH_1;
            }
        }
    }

    if(diamond)
    {
        uMap[nX][nY] = MAP_BFLY_DEATH_1;
    }
}       

void Map_Render(void)
{
    Map_DrawPrepare ();

    Map_Draw(Scroll_GetX(), Scroll_GetY());

    if (boMapTransition)
    {
        nMapTransitionCount += nMapTransitionStep;
        if (nMapTransitionCount < 0)
        {
            nMapTransitionCount = 0;
        }
        if (nMapTransitionCount >= uMapTransitionLength)
        {
            boMapTransition = false;
        }
    }

}

//----------------------------------------------------------------------------

void Map_DrawPrepare(void)
{
    Map_RenderMod[MAP_START] = MAP_START_1 + (uMapGfxCount % 32) / 16;
    Map_RenderMod[MAP_DIAMOND] = MAP_DIAMOND_1 + (uMapGfxCount % 16) / 2;
    Map_RenderMod[MAP_DIAMOND_FALLING] = MAP_DIAMOND_1 + (uMapGfxCount % 16) / 2;
    Map_RenderMod[MAP_SQUARE_L] = MAP_SQUARE_L1 + (uMapGfxCount % 4);
    Map_RenderMod[MAP_BUTTERFLY_L] = MAP_BUTTERFLY_L1 + (uMapGfxCount % 4);
    Map_RenderMod[MAP_GREEN_L] = MAP_GREEN_L1 + (uMapGfxCount % 4);
    Map_RenderMod[MAP_SQUARE_R] = MAP_SQUARE_R1 + (uMapGfxCount % 4);
    Map_RenderMod[MAP_BUTTERFLY_R] = MAP_BUTTERFLY_R1 + (uMapGfxCount % 4);
    Map_RenderMod[MAP_GREEN_R] = MAP_GREEN_R1 + (uMapGfxCount % 4);

    if (Stats_DiamondGotEnough())
    {
        int    nLine, nTile, nCol;
        u16    *var;

        for (nLine = 1; nLine < MAP_MAX_Y-1; nLine++)
        {
            for (nCol = 1; nCol < MAP_MAX_X-1; nCol++)
            {
                var   = &uMap[nCol][nLine];
                nTile = *var & MAP_TILE_MASK;
     
                if(MAP_HOME == nTile)
                    *var = MAP_HOME_OPEN;
            }
        }
    }

    pMap_DrawDestStart = BdBackgroundSbbPtr(2);
}

//----------------------------------------------------------------------------

void Map_Draw(int nX, int nY)
{
    int    nLine;
    int    nCol;
    u16    nTileIndex, nTileDir;
    u16    nTile;
    u16    *pDest;
    u16    *pSrc;

    if (boMapFlashWhite)
    {
        nTileIndex = MAP_WHITE;
        nTileIndex *= 4;
        nTile = Map_Tile[nTileIndex];

        pDest = pMap_DrawDestStart;
        for (nLine=0; nLine< GFX_SCREEN_TILE_HEIGHT + 2; nLine++)
        {
            for (nCol=0; nCol< GFX_TILE_MAP_WIDTH; nCol++)
            {
                *pDest++ = nTile;
            }
        }
    }
    else
    {
        for (nLine=0; nLine< (GFX_SCREEN_TILE_HEIGHT/2) + 1; nLine++)
        {
            for (nCol=0; nCol< (GFX_SCREEN_TILE_WIDTH/2) + 1; nCol++)
            {
                if (boMapTransition && nMapTransitionRnd[nCol+nX][nLine+nY] > nMapTransitionCount)
                {
                    nTileIndex = MAP_EDGE;
                }
                else
                {
                    nTileIndex = uMap[nCol+nX][nLine+nY] & MAP_TILE_MASK;
                    nTileDir = uMap[nCol+nX][nLine+nY] >> MAP_DIRECTION_SHIFT;

                    if (nTileIndex < MAP_BASE_MAX)
                    {
                        if(((nTileIndex==MAP_SQUARE_L) ||
                            (nTileIndex==MAP_BUTTERFLY_L) ||
                            (nTileIndex==MAP_GREEN_L)) &&
                            (nTileDir==MAP_DIR_LEFT))
                           nTileIndex+=71;
                        nTileIndex = Map_RenderMod[nTileIndex];
                    }
                }

                pDest = pMap_DrawDestStart + (nLine << 6) + (nCol << 1);
                pSrc = (u16 *) &Map_Tile[nTileIndex * 4];
                *pDest = *pSrc++;
                *(pDest + 1) = *pSrc++;
                *(pDest + GFX_TILE_MAP_WIDTH) = *pSrc++;
                *(pDest + GFX_TILE_MAP_WIDTH + 1) = *pSrc++;
            }
        }
    }
}

//----------------------------------------------------------------------------

void Map_FlashWhite(void)
{
    boMapFlashWhite = true;
    nMapFlashWhiteCount = 5;
}       

//----------------------------------------------------------------------------

bool Map_FlashingWhite(void)
{
    return(boMapFlashWhite);
}       

//----------------------------------------------------------------------------

void Map_TransitionBegin(int nStep)
{
    boMapTransition = true;
    nMapTransitionStep = nStep;
    if (nStep > 0)
    {
        nMapTransitionCount = 0;
    }
    else
    {
        nMapTransitionCount = uMapTransitionLength;
    }
}       

//----------------------------------------------------------------------------

u8 Map_WorldGet(void)
{
    u8    *pSrc = pMapData[BdMenuLevelGet()];
    int    namelen = *pSrc++;

    while(namelen--)
    {
        *pSrc++;
    }

    return *pSrc;
}
