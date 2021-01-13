#include    "Socrates.h"

#define MAP_MAX_X 40
#define MAP_MAX_Y 22

// map data available externally
extern u16 uMap[MAP_MAX_X][MAP_MAX_Y];

// map types
enum
{
    MAP_EARTH,
    MAP_EARTH_1,
    MAP_EARTH_2,
    MAP_EARTH_3,
    MAP_EARTH_4,
    MAP_WALL,
    MAP_DWALL, // MAP_GWALL
    MAP_DOOR_1,
    MAP_DOOR_2,
    MAP_DOOR_3,
    MAP_KEY_1,
    MAP_KEY_2,
    MAP_KEY_3,
    MAP_BOMB,
    MAP_DIAMOND,
    MAP_BOULDER,
    MAP_EDGE2,
    MAP_EDGE3,
    MAP_BLANK,
    MAP_EDGE4,
    MAP_SKY_1,
    MAP_SKY_2,
    MAP_SKY_3,
    MAP_SKY_4,
    MAP_SKY_5,
    MAP_SKY_6,
    MAP_SKY_7,
    MAP_SKY_8,
    MAP_SKY_9,
    MAP_SKY_10,
    MAP_EDGE,
    MAP_START,
    MAP_SQUARE_L,
    MAP_BUTTERFLY_L,
    MAP_GREEN_L,
    MAP_HOME,
    MAP_SWITCH_DOOR_1,
    MAP_SWITCH_DOOR_2,
    MAP_SWITCH_DOOR_3,
    MAP_SWITCH_DOOR_4,
    MAP_SWITCH_DOOR_5,
    MAP_SWITCH_DOOR_6,
    MAP_SWITCH_DOOR_7,
    MAP_SWITCH_DOOR_8,
    MAP_SWITCH_DOOR_9,
    MAP_SWITCH_DOOR_10,
    MAP_SWITCH_OFF_1,
    MAP_SWITCH_OFF_2,
    MAP_SWITCH_OFF_3,
    MAP_SWITCH_OFF_4,
    MAP_SWITCH_OFF_5,
    MAP_SWITCH_OFF_6,
    MAP_SWITCH_OFF_7,
    MAP_SWITCH_OFF_8,
    MAP_SWITCH_OFF_9,
    MAP_SWITCH_OFF_10,
    MAP_TELEPORT_1,
    MAP_TELEPORT_2,
    MAP_TELEPORT_3,
    MAP_TELEPORT_4,
    MAP_TELEPORT_5,
    MAP_TELEPORT_6,
    MAP_TELEPORT_7,
    MAP_TELEPORT_8,
    MAP_TELEPORT_9,
    MAP_TELEPORT_10,
    MAP_TELEPORT_A_1,
    MAP_TELEPORT_A_2,
    MAP_TELEPORT_A_3,
    MAP_TELEPORT_A_4,
    MAP_TELEPORT_A_5,
    MAP_TELEPORT_A_6,
    MAP_TELEPORT_A_7,
    MAP_TELEPORT_A_8,
    MAP_TELEPORT_A_9,
    MAP_TELEPORT_A_10,
    MAP_MAN,
    MAP_BOULDER_FALLING,
    MAP_DIAMOND_FALLING,
    MAP_DOOR1_OPEN,
    MAP_DOOR2_OPEN,
    MAP_DOOR3_OPEN,
    MAP_SWITCH_ON_1, 
    MAP_SWITCH_ON_2, 
    MAP_SWITCH_ON_3, 
    MAP_SWITCH_ON_4, 
    MAP_SWITCH_ON_5, 
    MAP_SWITCH_ON_6, 
    MAP_SWITCH_ON_7, 
    MAP_SWITCH_ON_8, 
    MAP_SWITCH_ON_9, 
    MAP_SWITCH_ON_10,
    MAP_SWITCH_DOOR_OPEN_1,
    MAP_SWITCH_DOOR_OPEN_2,
    MAP_SWITCH_DOOR_OPEN_3,
    MAP_SWITCH_DOOR_OPEN_4,
    MAP_SWITCH_DOOR_OPEN_5,
    MAP_SWITCH_DOOR_OPEN_6,
    MAP_SWITCH_DOOR_OPEN_7,
    MAP_SWITCH_DOOR_OPEN_8,
    MAP_SWITCH_DOOR_OPEN_9,
    MAP_SWITCH_DOOR_OPEN_10,
    MAP_HOME_OPEN,
    MAP_SQUARE_R,
    MAP_BUTTERFLY_R,
    MAP_GREEN_R,
    MAP_BASE_MAX,                                   // end of base types
    
    MAP_SQUARE_NOT_MOVED,
    MAP_BUTTERFLY_NOT_MOVED,
    MAP_GREEN_NOT_MOVED,
    MAP_START_1,
    MAP_START_2,
    MAP_DIAMOND_1,
    MAP_DIAMOND_2,
    MAP_DIAMOND_3,
    MAP_DIAMOND_4,
    MAP_DIAMOND_5,
    MAP_DIAMOND_6,
    MAP_DIAMOND_7,
    MAP_DIAMOND_8,
    MAP_DEATH_1,
    MAP_DEATH_2,
    MAP_DEATH_3,
    MAP_DEATH_4,
    MAP_DEATH_5,
    MAP_DEATH_6,
    MAP_DEATH_7,
    MAP_DEATH_8,
    MAP_BFLY_DEATH_1,
    MAP_BFLY_DEATH_2,
    MAP_BFLY_DEATH_3,
    MAP_BFLY_DEATH_4,
    MAP_BFLY_DEATH_5,
    MAP_BUTTERFLY_L1,
    MAP_BUTTERFLY_L2,
    MAP_BUTTERFLY_L3,
    MAP_BUTTERFLY_L4,
    MAP_SQUARE_L1,
    MAP_SQUARE_L2,
    MAP_SQUARE_L3,
    MAP_SQUARE_L4,
    MAP_GREEN_L1,
    MAP_GREEN_L2,
    MAP_GREEN_L3,
    MAP_GREEN_L4,
    MAP_DWALL_1,
    MAP_DWALL_2,
    MAP_DWALL_3,
    MAP_DWALL_4,
    MAP_WHITE,
    MAP_DWALL_BOULDER,
    MAP_DWALL_DIAMOND,
    MAP_BOMB_ON_1,
    MAP_BOMB_ON_2,
    MAP_BOMB_ON_3,
    MAP_BOMB_ON_4,
    MAP_BOMB_ON_5,
    MAP_BOMB_ON_6,
    MAP_BOMB_ON_7,
    MAP_BOMB_ON_8,
    MAP_BUTTERFLY_R1,
    MAP_BUTTERFLY_R2,
    MAP_BUTTERFLY_R3,
    MAP_BUTTERFLY_R4,
    MAP_SQUARE_R1,
    MAP_SQUARE_R2,
    MAP_SQUARE_R3,
    MAP_SQUARE_R4,
    MAP_GREEN_R1,
    MAP_GREEN_R2,
    MAP_GREEN_R3,
    MAP_GREEN_R4,

    MAP_TYPES_MAX
};

enum
{
    MAP_DIR_RIGHT,
    MAP_DIR_UP,
    MAP_DIR_LEFT,
    MAP_DIR_DOWN,

    MAP_DIR_MAX,
};

enum
{
    MAP_DWALL_WAITING,      
    MAP_DWALL_GOING,        
    MAP_DWALL_DONE  
};

#define MAP_TILE_MASK           (0xFF)

//----------------------------------------------------------------------------

void    Map_Init(void);
void    Map_Begin(u32 uLevel);
void    Map_UpdateTimerClear(void);

void    Map_Update(void);
void    Map_Process1(void);
void    Map_Process2(void);
void    Map_ProcessDrop(int nCol, int nLine, int nTarget);
void    Map_ProcessMove(int nCol, int nLine, int nTarget);
void    Map_ProcessDWall(int nCol, int nLine);
void    Map_ProcessGreen(int nCol, int nLine);
void    Map_TileExplode(int nX, int nY, bool diamond);
void    Map_TileExplode_IWRAM(int nX, int nY, bool diamond);

void    Map_Render(void);
void    Map_DrawPrepare(void);
void    Map_Draw(int nX, int nY);

u8      Map_WorldGet(void);

void    Map_FlashWhite(void);
bool    Map_FlashingWhite(void);
void    Map_TransitionBegin(int nStep);

//----------------------------------------------------------------------------
