#include "doomstat.h"
#include "i_system.h"
#include "v_video.h"
#include "m_argv.h"
#include "d_main.h"

#include "doomdef.h"

#include "p-lib.hh"


unsigned char* mmio_addr = reinterpret_cast<unsigned char*>(0x3000000);

// Called by D_DoomMain,
// determines the hardware configuration
// and sets up the video mode
void I_InitGraphics (void) {
    static int		firsttime=1;
    if (!firsttime)
		return;
    firsttime = 0;

    sys_map_screen(mmio_addr);
	screens[0] = mmio_addr;
}

void I_StartTic (void)
{
	// TODO: this should do input event handling
}

void I_ShutdownGraphics(void) {
	I_Quit();
}

// Takes full 8 bit values.
void I_SetPalette (byte* palette) {
	// pretty sure palette is 256 bytes long
}

void I_FinishUpdate (void) {
	static int	lasttic;
    int		tics;
    int		i;

	// draws little dots on the bottom of the screen
    if (devparm) {
		i = I_GetTime();
		tics = i - lasttic;
		lasttic = i;
		if (tics > 20) tics = 20;

		for (i=0 ; i<tics*2 ; i+=2)
		    screens[0][ (SCREENHEIGHT-1)*SCREENWIDTH + i] = 0xff;
		for ( ; i<20*2 ; i+=2)
		    screens[0][ (SCREENHEIGHT-1)*SCREENWIDTH + i] = 0x0;
    }
}

// Wait for vertical retrace or pause a bit.
void I_WaitVBL(int count);

void I_ReadScreen (byte* scr) {
    memcpy (scr, screens[0], SCREENWIDTH*SCREENHEIGHT);
}

void I_BeginRead (void);
void I_EndRead (void);


// Stubbed in source:
void I_UpdateNoBlit (void) {}
void I_StartFrame (void) {}
