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
	screens[0] = (unsigned char *) malloc (SCREENWIDTH * SCREENHEIGHT);
}

void I_StartTic (void)
{
	int c;
	int n;
	event_t event;
	int key;

    // jprintf("checking for input...");

    while (true) {
        int release = 0;

		n = sys_read(0, reinterpret_cast<char*>(&c), 1);
        if (n < 1) {
            break;
        }

        if (c > 256) {
            c -= 256;
            release = 1;
        }

		key = 0;
		switch (tolower(c)) {
			case 'w':	// up
				key = KEY_UPARROW;
				break;
			case 'a':	// left
				key = KEY_LEFTARROW;
				break;
			case 's':	// down
				key = KEY_DOWNARROW;
				break;
			case 'd':	// right
				key = KEY_RIGHTARROW;
				break;
			case 'q':	// strafe left
				key = ',';
				break;
			case 'e':	// strafe right
				key = '.';
				break;
			case 'p':	// pause
				key = KEY_PAUSE;
				break;
			case '\n':	// enter
				key = KEY_ENTER;
				break;
			case ' ':	// use
				key = ' ';
				break;
			case 'j':	// fire
				key = KEY_RCTRL;
				break;
            case '/':   // run
                key = KEY_RSHIFT;
                break;
            case 27:  // escape
                key = KEY_ESCAPE;
                break;
			default:
                key = tolower(c);
				break;
		}

		if (key) {
            event.data1 = key;
            if (release) {
                event.type = ev_keyup;
                D_PostEvent(&event);
            }
            else {
                event.type = ev_keydown;
                D_PostEvent(&event);
            }
		}
	}

	// jprintf("finished");
}

void I_ShutdownGraphics(void) {
	I_Quit();
}

// Takes full 8 bit values.
void I_SetPalette (byte* palette) {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uintptr_t c;

	for (uintptr_t i=0 ; i<256 ; i++)
	{
		red = gammatable[usegamma][*palette++] / 4;
		green = gammatable[usegamma][*palette++] / 4;
		blue = gammatable[usegamma][*palette++] / 4;
		sys_swapcolor(i, red, green, blue);
	}
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

    memcpy(mmio_addr, screens[0], SCREENWIDTH * SCREENHEIGHT);
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
