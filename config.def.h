/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx       = 2;       /* border pixel of windows */
static const unsigned int gappx          = 4;       /* gaps between windows */
static const unsigned int fgappx         = 18;      /* gaps around only one window*/
static const unsigned int snap           = 32;      /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 0;   /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray  = 1;        /* 0 means no systray */
static const int showbar      = 1;        /* 0 means no bar */
static const int topbar       = 1;        /* 0 means bottom bar */
static const char *fonts[]    = { "JetBrains Mono Nerd Font:weight=bold:size=11:antialias=true:hinting=true" };
static const char dmenufont[] = "JetBrains Mono Nerd Font:weight=bold:size=12:antialias=true:hinting=true"; 

static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_brown[]       = "#361a09";
static const char dracula_purple[]  = "#bd93f9";
static const char dracula_green[]   = "#54f37f";
static const char reddish[]         = "#700500";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_gray1, dracula_green },
};

static const char *const autostart[] = {
	"nitrogen", "--restore", NULL,
	"slstatus", NULL,
	"xfce4-clipman", NULL,
	"nm-applet", "--indicator", NULL,
	"volumeicon", NULL,
	"rog-control-center", NULL,
	"picom", "-b", NULL,
	"touchegg", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",	    NULL,			NULL,		0,				  1,			 -1 },
	{ "Firefox",  NULL,			NULL,		1 << 8,			0,			 -1 },
};

/* layout(s) */
static const float mfact		      = 0.55; /* factor of master area size [0.05..0.95] */
static const int   nmaster        = 1;    /* number of clients in master area */
static const int   resizehints	  = 0;    /* 1 means respect size hints in tiled resizals */
static const int   lockfullscreen = 1;	  /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },				 /* first entry is default */
	{ "><>",      NULL },				 /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
#define ICONSIZE	20					/* icon size */
#define ICONSPACING 8					/* space between icon and title */
#define SHCMD(cmd)	{ .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
/* system commands */
#include <X11/XF86keysym.h>
static const char *brupcmd[]	   = { "brightification", "up", NULL };
static const char *brdowncmd[]   = { "brightification", "down", NULL };
static const char *upvol[]		   = { "volufication", "up", NULL};
static const char *downvol[]	   = { "volufication", "down", NULL};
static const char *mutevol[]	   = { "volufication", "mute", NULL};

/* user constants */
#define TERMINAL "alacritty"
#define FILEMANAGER "pcmanfm"

/* user commands */
static const char *dmenucmd[]		= { "dmenu_run", "-c", "-l", "7", "-fn", dmenufont, NULL }; 
static const char *powermenu[]  = {"pm", NULL};
//static const char *powermenu[]		= { "rofi", "-show", "power-menu", "-modi","power-menu:/home/razobeckett/.local/bin/rofi-power-menu", NULL };
static const char *rofisearch[]	= { "rofi", "-show", "drun", "-modi", "drun", "-show-icons", "-font", "JetBrainsMono", "Nerd", "Font", "12", NULL };
static const char *rofiemoji[]	= { "rofi", "-modi", "emoji", "-show", "emoji", "-font", "JoyPixels", "12", NULL };

static const Key keys[] = {

	/* FN key functionality */
	{ 0,							XF86XK_AudioLowerVolume,	spawn,			{.v = downvol } },
	{ 0,							XF86XK_AudioMute,			    spawn,			{.v = mutevol } },
	{ 0,							XF86XK_AudioRaiseVolume,	spawn,			{.v = upvol } },
	{ 0,							XF86XK_MonBrightnessUp,		spawn,			{.v = brupcmd } },
	{ 0,							XF86XK_MonBrightnessDown,	spawn,			{.v = brdowncmd } },

	/* modifier                     key        					function        argument */
	{ MODKEY,                       XK_p,      					spawn,          {.v = rofisearch } },
	{ MODKEY|ALTKEY,                XK_b,      					togglebar,      {0} },
	{ ALTKEY|ShiftMask,           	XK_h,      					rotatestack,    {.i = +1 } },
	{ ALTKEY|ShiftMask,           	XK_l,      					rotatestack,    {.i = -1 } },
	{ ALTKEY,                     	XK_h,      					focusstack,     {.i = +1 } },
	{ ALTKEY,                     	XK_l,      					focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      					incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      					incnmaster,     {.i = -1 } },
	{ ALTKEY,                     	XK_j,      					setmfact,       {.f = -0.05} },
	{ ALTKEY,                     	XK_k,      					setmfact,       {.f = +0.05} },
	{ ALTKEY,                     	XK_Return, 					zoom,           {0} },
	{ ALTKEY,                     	XK_Tab,    					view,           {0} },
	{ ALTKEY,                     	XK_q,      					killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_t,      					setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      					setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      					setlayout,      {.v = &layouts[2]} },
	/*{ MODKEY,                       XK_space,  				  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  					togglefloating, {0} },*/
	{ MODKEY,                       XK_0,      					view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      					tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  					focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, 					focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  					tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, 					tagmon,         {.i = +1 } },
	{ MODKEY|ALTKEY,				        XK_BackSpace,				quit,           {1} }, 
	TAGKEYS(                        XK_1,                      					0)
	TAGKEYS(                        XK_2,                      					1)
	TAGKEYS(                        XK_3,                      					2)
	TAGKEYS(                        XK_4,                      					3)
	TAGKEYS(                        XK_5,                      					4)
	TAGKEYS(                        XK_6,                      					5)
	TAGKEYS(                        XK_7,										            6)
	TAGKEYS(                        XK_8,                      					7)
	TAGKEYS(                        XK_9,                      					8)
	TAGKEYS(                        XK_0,                      					9)

	/* custom shortcuts */
  { MODKEY,						XK_space,			  spawn,      	{.v = dmenucmd } },
  { MODKEY,						XK_period,			spawn,      	{.v = rofiemoji} },
  { MODKEY,						XK_grave,				spawn,  		  {.v = powermenu } },
  { MODKEY,						XK_Return,			spawn,        {.v = (const char*[]){ TERMINAL, NULL }} },
  { MODKEY,						XK_e,						spawn,			  {.v = (const char*[]){ FILEMANAGER, NULL }} },
  { MODKEY,						XK_f,						spawn,			  {.v = (const char*[]){ "firefox", NULL }} },
  { MODKEY,						XK_b,						spawn,			  {.v = (const char*[]){ "brave", NULL }} },
  { MODKEY,						XK_n,						spawn,			  {.v = (const char*[]){ "nitrogen", NULL }} },
  { MODKEY,						XK_w,						spawn,        {.v = (const char*[]){ "whatsapp-for-linux", NULL }} },
  { MODKEY,						XK_v,						spawn,	   		{.v = (const char*[]){ "xfce4-popup-clipman", NULL }} },
  { MODKEY|ShiftMask,	XK_s,			      spawn,	   		{.v = (const char*[]){ "flameshot", "gui", NULL }} },
  { MODKEY,						XK_l,						spawn,        SHCMD("dm-tool lock") },
  { MODKEY|ShiftMask,	XK_l,						spawn,        SHCMD("xrdb -load ~/.config/Xresources") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = powermenu } },
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
	{ ClkClientWin,         ALTKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
