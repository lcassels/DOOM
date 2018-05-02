CC = gcc

WARNINGS =	-Waddress                      		\
          	-Warray-bounds                 		\
          	-Wchar-subscripts              		\
          	-Wenum-compare                 		\
          	-Wimplicit-int                 		\
          	-Wimplicit-function-declaration		\
          	-Wcomment                      		\
          	-Wformat=0                    		\
          	-Wmain                         		\
          	-Wmissing-braces               		\
          	-Wnonnull                      		\
          	-Wparentheses                  		\
          	-Wpointer-sign                 		\
          	-Wreturn-type                  		\
          	-Wsequence-point               		\
          	-Wsign-compare                 		\
          	-Wstrict-aliasing              		\
          	-Wstrict-overflow=1            		\
          	-Wswitch                       		\
          	-Wtrigraphs                    		\
          	-Wuninitialized                		\
          	-Wunknown-pragmas              		\
          	-Wunused-function              		\
          	-Wunused-label                 		\
          	-Wunused-value                 		\
          	-Wunused-variable              		\
          	-Wvolatile-register-var


CFLAGS64 = -g $(WARNINGS) -DNORMALUNIX -DLINUX
CFLAGS32 = -w -m32 $(CFLAGS64) -Dx32
LDFLAGS = -L/usr/X11R6/lib
LIBS = -lXext -lX11 -lnsl -lm

# build directories
O32 = x86
O64 = x86_64

# executable name
E = doom

# dependencies (from original doom makefile)
SRCS =  doomdef.c       \
		doomstat.c      \
		dstrings.c      \
		i_system.c      \
		i_sound.c       \
		i_video.c       \
		i_net.c         \
		tables.c        \
		f_finale.c      \
		f_wipe.c        \
		d_main.c        \
		d_net.c         \
		d_items.c       \
		g_game.c        \
		m_menu.c        \
		m_misc.c        \
		m_argv.c        \
		m_bbox.c        \
		m_fixed.c       \
		m_swap.c        \
		m_cheat.c       \
		m_random.c      \
		am_map.c        \
		p_ceilng.c      \
		p_doors.c       \
		p_enemy.c       \
		p_floor.c       \
		p_inter.c       \
		p_lights.c      \
		p_map.c         \
		p_maputl.c      \
		p_plats.c       \
		p_pspr.c        \
		p_setup.c       \
		p_sight.c       \
		p_spec.c        \
		p_switch.c      \
		p_mobj.c        \
		p_telept.c      \
		p_tick.c        \
		p_saveg.c       \
		p_user.c        \
		r_bsp.c         \
		r_data.c        \
		r_draw.c        \
		r_main.c        \
		r_plane.c       \
		r_segs.c        \
		r_sky.c         \
		r_things.c      \
		w_wad.c         \
		wi_stuff.c      \
		v_video.c       \
		st_lib.c        \
		st_stuff.c      \
		hu_stuff.c      \
		hu_lib.c        \
		s_sound.c       \
		z_zone.c        \
		info.c          \
		sounds.c
OBJS32 = $(SRCS:%.c=$(O32)/%.o)
OBJS64 = $(SRCS:%.c=$(O64)/%.o)


all: x32 x64

clean:
	@rm -f *.o *~ *.flc  # from original doom makefile
	@rm -rf $(O32) $(O64)

# build targets
x32: $(O32)/$(E)
x64: $(O64)/$(E)

# 256-color x11 launcher
run32: x32
	xinit '$(shell pwd)/$(O32)/$(E)' -- $(shell which Xephyr) :1 -screen 320x200x8 -br -reset -terminate
run64: x64
	xinit '$(shell pwd)/$(O64)/$(E)' -- $(shell which Xephyr) :1 -screen 320x200x8 -br -reset -terminate


# recipe for ensuring a directory exists
%/.:
	@mkdir -p $@

# 32-bit executable
$(O32)/$(E): $(OBJS32) $(O32)/i_main.o | $(O32)/.
	$(CC) $(CFLAGS32) $(LDFLAGS) $(OBJS32) $(O32)/i_main.o -o $(O32)/$(E) $(LIBS)

# 64-bit executable
$(O64)/$(E): $(OBJS64) $(O64)/i_main.o | $(O64)/.
	$(CC) $(CFLAGS64) $(LDFLAGS) $(OBJS64) $(O64)/i_main.o -o $(O64)/$(E) $(LIBS)

# 32-bit .o files
$(O32)/%.o: %.c | $(O32)/.
	$(CC) $(CFLAGS32) -c $< -o $@

# 64-bit .o files
$(O64)/%.o: %.c | $(O64)/.
	$(CC) $(CFLAGS64) -c $< -o $@

# these are not files
.PHONY: all clean x32 x64

# wipe target files if build doesn't complete
.DELETE_ON_ERROR:
