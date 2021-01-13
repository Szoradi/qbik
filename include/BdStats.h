#ifndef BD_STATS
#define BD_STATS

#include "Socrates.h"

void	Stats_Begin(void);
void	Stats_Update(void);
void	Stats_Render(void);

void	Stats_DiamondGot(void);
void	Stats_DiamondRequiredSet(u32 uDiamonds);
bool	Stats_DiamondGotEnough(void);

void	Stats_TimerSet(u32 uTimer);
bool	Stats_TimerMature(void);
void	Stats_TimerStart(void);

#endif
