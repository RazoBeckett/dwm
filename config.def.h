/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 6;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 0;   /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
#define ICONSIZE 18   /* icon size */
#define ICONSPACING 8 /* space between icon and title */
static const char *fonts[]          = { "JetBrains Mono Nerd Font:weight=bold:size=11:antialias=true:hinting=true" };
static const char dmenufont[]       = "JetBrains Mono Nerd Font:weight=bold:size=11:antialias=true:hinting=true"; 
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_brown[]		= "#361a09";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_gray1,  col_brown  },
};

static const char *const autostart[] = {
	"thunar", "--daemon", NULL,
	"slstatus", NULL,
	"nm-applet", NULL,
	"rog-control-center", NULL,
	"picom", "--vsync", "-b", "--animations", "--animation-window-mass", "0.5", "--animation-for-open-window", "zoom", "--animation-stiffness", "500", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define MOD2KEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MOD2KEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MOD2KEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MOD2KEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MOD2KEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
/* system commands */
#include <X11/XF86keysym.h>
static const char *brupcmd[]  = { "/home/razobeckett/.config/suckless/dwm/scripts/brightnessnotifications.sh", "up", NULL };
static const char *brdowncmd[]  = { "/home/razobeckett/.config/suckless/dwm/scripts/brightnessnotifications.sh", "down", NULL };
static const char *upvol[]  = { "/home/razobeckett/.config/suckless/dwm/scripts/volumenotifications.sh", "up", NULL};
static const char *downvol[]  =  { "/home/razobeckett/.config/suckless/dwm/scripts/volumenotifications.sh", "down", NULL};
static const char *mutevol[]  = { "/home/razobeckett/.config/suckless/dwm/scripts/volumenotifications.sh", "mute", NULL};

/* user commands*/
//static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL }; 
static const char *powermenu[] = { "rofi", "-show", "power-menu", "-modi", "power-menu:/home/razobeckett/.local/bin/rofi-power-menu", NULL };
static const char *rofimenu[] = { "rofi", "-show", "drun", "-modi", "drun", "-show-icons", NULL };
static const char *thorium[]  = { "thorium-browser","--proxy-server=socks5://10.11.12.100:1080", NULL };
static const char *whatsapp[]  = { "flatpak", "run", "io.github.mimbrero.WhatsAppDesktop", NULL };
static const char *firefox[] = { "firefox", NULL };
//static const char *firefox[]  = { "flatpak", "run", "org.mozilla.firefox", NULL };
static const char *clipman[]  = { "xfce4-popup-clipman", NULL };
static const char *flameshot[]  = { "flameshot", "gui", NULL };
static const char *thunar[]  = { "thunar", NULL };
static const char *termcmd[]  = { "kitty", NULL };

static const Key keys[] = {
	/* modifier                     key        					function        argument */
	{ MODKEY,                       XK_p,      					spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_b,      					togglebar,      {0} },
	{ MOD2KEY|ShiftMask,           	XK_j,      					rotatestack,    {.i = +1 } },
	{ MOD2KEY|ShiftMask,           	XK_k,      					rotatestack,    {.i = -1 } },
	{ MOD2KEY,                     	XK_j,      					focusstack,     {.i = +1 } },
	{ MOD2KEY,                     	XK_k,      					focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      					incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      					incnmaster,     {.i = -1 } },
	{ MOD2KEY,                     	XK_h,      					setmfact,       {.f = -0.05} },
	{ MOD2KEY,                     	XK_l,      					setmfact,       {.f = +0.05} },
	{ MOD2KEY,                     	XK_Return, 					zoom,           {0} },
	{ MOD2KEY,                     	XK_Tab,    					view,           {0} },
	{ MOD2KEY,                     	XK_q,      					killclient,     {0} },
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
	{ MODKEY|ControlMask|ShiftMask, XK_q,      					quit,           {1} }, /*{ MOD2KEY|ShiftMask,          	XK_q,      quit,           {0} }, */
	TAGKEYS(                        XK_1,                      					0)
	TAGKEYS(                        XK_2,                      					1)
	TAGKEYS(                        XK_3,                      					2)
	TAGKEYS(                        XK_4,                      					3)
	TAGKEYS(                        XK_5,                      					4)
	TAGKEYS(                        XK_6,                      					5)
	TAGKEYS(                        XK_7,                      			   	  	6)
	TAGKEYS(                        XK_8,                      					7)
	TAGKEYS(                        XK_9,                      					8)
	/* FN key functionality */
	{ 0, 							XF86XK_AudioLowerVolume, 	spawn, 			{.v = downvol } },
    { 0, 							XF86XK_AudioMute, 			spawn, 			{.v = mutevol } },
    { 0, 							XF86XK_AudioRaiseVolume, 	spawn, 			{.v = upvol } },
    { 0, 							XF86XK_MonBrightnessUp, 	spawn, 			{.v = brupcmd } },
    { 0, 							XF86XK_MonBrightnessDown, 	spawn, 			{.v = brdowncmd } },
	/* custom shortcuts */
	{ MODKEY,                     	XK_space,  					spawn,      	{.v = rofimenu} },
	{ MODKEY|ShiftMask,				XK_x,	   					spawn,      	{.v = powermenu } },
	{ MODKEY,						XK_e,	   					spawn,		   	{.v = thunar } },
	{ MODKEY,						XK_f,	   					spawn,		   	{.v = firefox } },
	{ MODKEY,						XK_t,	   					spawn,		   	{.v = thorium } },
	{ MODKEY,		                XK_w, 	   					spawn,          {.v = whatsapp } },
	{ MODKEY,		                XK_Return, 					spawn,          {.v = termcmd } },
	{ MODKEY,						XK_v,	   					spawn,	   	   	{.v = clipman } },
	{ MODKEY|ShiftMask,				XK_s,	   					spawn,	   	   	{.v = flameshot } },
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
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
