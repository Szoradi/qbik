#include	"Socrates.h"

// man types
enum
{
    MAN_NORMAL,
    MAN_BLINK1,
    MAN_BLINK2,
    MAN_TAP1,
    MAN_TAP2,       
    MAN_LEFT1,      
    MAN_LEFT2,      
    MAN_LEFT3,      
    MAN_LEFT4,      
    MAN_LEFT5,
    MAN_LEFT6,
    MAN_LEFT7,
    MAN_LEFT8,
    MAN_RIGHT1,
    MAN_RIGHT2,
    MAN_RIGHT3,
    MAN_RIGHT4,
    MAN_RIGHT5,
    MAN_RIGHT6,
    MAN_RIGHT7,
    MAN_RIGHT8,
    MAN_BIRTH_1,
    MAN_BIRTH_2,
    MAN_BIRTH_3,
    MAN_BIRTH_4,
    MAN_BIRTH_5,
    MAN_BIRTH_6,
    MAN_BIRTH_7,
    MAN_BIRTH_8,

    MAN_TYPES_MAX
};

// man move types
enum
{
    MAN_CANNOT_MOVE,
    MAN_MOVE,
    MAN_PUSH_BOULDER
};

void	Man_Init(void);
void	Man_Begin(void);

void	Man_Render(void);
void	Man_Update1(void);
void	Man_Update2(void);
void	Man_TileDraw(int nX, int nY, int nTileIndex);

u32	Man_CanMove(int nDX, int nDY);
void	Man_Move(int nDX, int nDY);

int	Man_GetX(void);
int	Man_GetY(void);

bool	Man_Home(void);
void	Man_Remove(void);
bool	Man_Alive(void);
bool	Man_Born(void);

//----------------------------------------------------------------------------
