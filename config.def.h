/* See LICENSE file for copyright and license details. */
/* appearance */
static const unsigned int borderpx       = 1;   /* border pixel of windows */
static const unsigned int gappx          = 0;   /* gaps between windows */
static const unsigned int fgappx         = 0;   /* gaps around only one window*/
static const unsigned int snap           = 32;  /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 0;   /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int onlyclient   = 1;        /* 1: keep border even if only client */
static const int showsystray  = 1;        /* 0 means no systray */
static const int showbar      = 1;        /* 0 means no bar */
static const int topbar       = 1;        /* 0 means bottom bar */
static const int titlestyle   = 1;        /* 0: left aligned , 1: center aligned */
static const char *fonts[]    = { "monospace::size=10" };
static const char dmenufont[] = "monospace:size=10";
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_brown[]       = "#361a09";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeTitle] = { col_gray4, col_cyan,  col_cyan },
};

static const char *const autostart[] = {
	"bash", "-c", "$HOME/.local/bin/launch_dwmblocks", NULL, /* You can get this script from my dotfiles repository */
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0" };

#include "apprules.h"

/* layout(s) */
static const float mfact	  = 0.55; /* factor of master area size [0.05..0.95] */
static const int   nmaster        = 1;    /* number of clients in master area */
static const int   resizehints	  = 0;    /* 1 means respect size hints in tiled resizals */
static const int   lockfullscreen = 1;	  /* 1 will force focus on the fullscreen window */

/* Additional layouts includes: */
#include "layouts/grid.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },				 /* first entry is default */
	{ "><>",      NULL },				 /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "HHH",      grid },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ ALTKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ ALTKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ ALTKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ ALTKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define ICONSIZE 20					/* icon size */
#define ICONSPACING 8					/* space between icon and title */
#define SHCMD(cmd)	{ .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define STATUSBAR "dwmblocks"

#include <X11/XF86keysym.h>

/* user commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]	=  { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL }; 
static const char *termcmd[]  = { "st", NULL };

static const Key keys[] = {

	/* FN key functionality */
	{ 0,	XF86XK_AudioRaiseVolume,	spawn,		SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +5% && kill -38 $(pidof dwmblocks)") },
	{ 0,	XF86XK_AudioLowerVolume,	spawn,		SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -5% && kill -38 $(pidof dwmblocks)") },
	{ 0,	XF86XK_AudioMute,		spawn,		SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle && kill -38 $(pidof dwmblocks)") },
	{ 0,	XF86XK_AudioMicMute,		spawn,		SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle && kill -38 $(pidof dwmblocks)") },
	/* Brightness FN (install brightnessctl)*/
	{ 0,	XF86XK_MonBrightnessUp,		spawn,		SHCMD("brightnessctl set +5% && kill -39 $(pidof dwmblocks)") },
	{ 0,	XF86XK_MonBrightnessDown,	spawn,		SHCMD("brightnessctl set 5%- && kill -39 $(pidof dwmblocks)") },

	/* modifier                     key        		function        argument */
	{ MODKEY,			XK_p,		spawn,		{.v = dmenucmd } },
	{ MODKEY|ShiftMask,			XK_Return,		spawn,		{.v = termcmd } },
	{ MODKEY|ALTKEY,		XK_b,      		togglebar,      {0} },
	{ ALTKEY|ShiftMask,		XK_h,      		rotatestack,    {.i = +1 } },
	{ ALTKEY|ShiftMask,		XK_l,      		rotatestack,    {.i = -1 } },
	{ ALTKEY,			XK_h,      		focusstack,     {.i = +1 } },
	{ ALTKEY,			XK_l,      		focusstack,     {.i = -1 } },
	{ MODKEY,			XK_i,      		incnmaster,     {.i = +1 } },
	{ MODKEY,			XK_d,      		incnmaster,     {.i = -1 } },
	{ ALTKEY,			XK_j,      		setmfact,       {.f = -0.05} },
	{ ALTKEY,			XK_k,      		setmfact,       {.f = +0.05} },
	{ ALTKEY,			XK_Return, 		zoom,           {0} },
	{ ALTKEY,			XK_Tab,    		view,           {0} },
	{ ALTKEY,			XK_q,      		killclient,     {0} },
	{ ALTKEY|ControlMask,		XK_q,			killclient,		{.ui = 1} },  // kill unselect
	{ ALTKEY|ShiftMask|ControlMask,	XK_q,			killclient,			{.ui = 2} },  // killall
	{ ALTKEY|ShiftMask,		XK_space,		togglefloating, {0} },
	{ MODKEY|ShiftMask,		XK_t,      		setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,		XK_f,      		setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,		XK_m,      		setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,		XK_g,      		setlayout,      {.v = &layouts[3]} },
	{ MODKEY,			XK_0,      		view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,		XK_0,      		tag,            {.ui = ~0 } },
	{ MODKEY,			XK_comma,  		focusmon,       {.i = -1 } },
	{ MODKEY,			XK_period, 		focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_comma,  		tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,		XK_period, 		tagmon,         {.i = +1 } },
	{ MODKEY|ALTKEY,		XK_BackSpace,		quit,           {1} }, 
	TAGKEYS(			XK_1,           			0)
	TAGKEYS(			XK_2,           			1)
	TAGKEYS(			XK_3,           			2)
	TAGKEYS(			XK_4,           			3)
	TAGKEYS(			XK_5,           			4)
	TAGKEYS(			XK_6,           			5)
	TAGKEYS(			XK_7,					6)
	TAGKEYS(			XK_8,           			7)
	TAGKEYS(			XK_9,           			8)
	TAGKEYS(			XK_0,           			9)
	{ MODKEY,			XK_1,			focusbynum,	{.i = 0} },
	{ MODKEY,			XK_2,			focusbynum,	{.i = 1} },
	{ MODKEY,			XK_3,			focusbynum,	{.i = 2} },
	{ MODKEY,			XK_4,			focusbynum,	{.i = 3} },
	{ MODKEY,			XK_5,			focusbynum,	{.i = 4} },
	{ MODKEY,			XK_6,			focusbynum,	{.i = 5} },
	{ MODKEY,			XK_7,			focusbynum,	{.i = 6} },
	{ MODKEY,			XK_8,			focusbynum,	{.i = 7} },
	{ MODKEY|ShiftMask,     XK_z, unfloatvisible, {0} },
	{ MODKEY|ShiftMask,	    XK_t, unfloatvisible, {.v = &layouts[1]} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigstatusbar,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigstatusbar,   {.i = 5} },
	/* placemouse options, choose which feels more natural:
	 *    0 - tiled position is relative to mouse cursor
	 *    1 - tiled postiion is relative to window center
	 *    2 - mouse pointer warps to window center
	 *
	 * The moveorplace uses movemouse or placemouse depending on the floating state
	 * of the selected client. Set up individual keybindings for the two if you want
	 * to control these separately (i.e. to retain the feature to move a tiled window
	 * into a floating position).
	 */
	{ ClkClientWin,         MODKEY,         Button1,        moveorplace,    {.i = 1} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
