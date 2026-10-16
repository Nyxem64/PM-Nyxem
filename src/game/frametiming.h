#ifndef _UNK_0C0A70_H_
#define _UNK_0C0A70_H_
#include <ultra64.h>

extern s32 lastFrameCounter;
extern s32 currentFrameCounter;
extern s32 speedgraphframes;

#if defined (BUGFIX_R1)
extern f32 jpD_800484CC;
extern f32 jpD_800484D0;
#endif

extern s32 previousFrameCounter;
extern s32 halfFrameCounter;
extern s32 isFrameCounterOdd;
extern s32 halfMinusPreviousCounter;
extern u32 copy_of_osgetcount_value_0;
extern u32 copy_of_osgetcount_value_1;
extern s32 frameDelay;

#ifndef TARGET_N64
/* GE_TICKHZ sub-field ticking (contract in frametiming.c): portTickDelta is the
 * fractional field delta for this tick (0.5 at 120Hz), portTickCadence the last
 * whole-field delta held across 0-delta sub-ticks, and portTickHz() the
 * configured rate (60 = classic, 0 = uncapped, forced to 60 while a demo is
 * recording). */
extern f32 portTickDelta;
extern s32 portTickCadence;
/* Smoothed presentation stats, written by gfx_sdl2's title-stat pass
 * (500ms window) for the midas.ini show_fps in-game overlay. 0 headless. */
extern s32 g_PortStatFps;
extern s32 g_PortStatTps;
s32 portTickHz(void);           /* 60 = classic, 0 = uncapped, else that literal rate */
u32 portTickGateCounts(void);   /* boss.c tick admission threshold, in counts */
u32 portTickFieldGateCounts(void); /* gate that yields exactly 60 ticks/s (front end) */
s32 portPaceDue(u32 *stamp, u32 counts); /* real-time pacing for display-list work */
s32 portTickIntroPaceDue(s32 fields);    /* held front-end tick due (advancing deadline) */
s32 portGunbarrelBloodDiv(void);         /* blood-drip divisor (1=30fps, 2=15fps
                                          * half - drip only) */
void portTickIntroPaceReset(void);
void portTickSetHz(s32 hz);     /* midas.ini [display] tickhz; GE_TICKHZ still wins */
void portTickSetHwPace(s32 on); /* tickhz=hw: the console's frame pacing on the 60 Hz sim (frametiming.c) */
s32 portTickHwPace(void);       /* 1 = hold frames for the modelled N64 fields (not during demos / recording) */
s32 portHwPaceFields(void);     /* the fields the last frame would have cost the console, 1..6 */
/* Sub-field smoothing (see frametiming.c "Sub-field SMOOTHING"):
 * portAnimTicks() = fractional anim ticks this tick (== g_ClockTimer when the
 * delta is whole); portLagStep advances `x = x*d + in` by delta fields exactly;
 * GE_NOSMOOTH=1 restores field stepping at a raised rate. */
s32 portSmoothOn(void);
f32 portAnimTicks(void);
f32 portTickFieldPhase(void); /* sub-field phase [0,1) banked by the field carry */
void portLagStep(f32 *x, f32 d, f32 in, f32 delta);
void portDecayStep(f32 *x, f32 d, f32 delta);
#endif

void waitForNextFrame(void);

#endif
