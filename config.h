/* See LICENSE file for copyright and license details. */

/* appearance */
static const int refreshrate = 144;				/* framerate of window-dragging actions */
static const unsigned int borderpx = 4;     	/* border pixel of windows */
static const int gappx = 10;       				/* gaps between windows */
static const unsigned int snap = 32;       		/* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray = 1;     			/* 0 means no systray */
static const int showbar = 1;        			/* 0 means no bar */
static const int topbar = 0;        			/* 0 means bottom bar */
#define ICONSIZE 24   							/* icon size */
#define ICONSPACING 8 							/* space between icon and title */
static const char *fonts[] = { "monospace:size=12:dpi=120:antialias=true:autohint=true" };
static const char light[] = "#3971ed";
static const char dark[] = "#1d1f21";
static const char *colors[][3] = {
	/*             { fg,   bg,    border }   */
	[SchemeNorm] = { light, dark, dark },
	[SchemeSel]  = { dark, light, light },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* window swallowing */
static const int swaldecay = 3;
static const int swalretroactive = 1;
/* static const char swalsymbol[] = "👅"; */

/* layout(s) */
static const float mfact = 0.55; 	 /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    	 /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#include <X11/XF86keysym.h>
#include "selfrestart.c"

static Key keys[] = {
	/* modifier         key        function        argument */
	{ MODKEY,           XK_Return, spawn, 		   SHCMD("st") },
	{ MODKEY, 	        XK_d,	   spawn,          SHCMD("j4-dmenu-desktop") },
	{ MODKEY|ShiftMask, XK_d,	   spawn,          SHCMD("passmenu") },
	{ MODKEY,           XK_b,      togglebar,      {0} },
	{ MODKEY,           XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,           XK_k,      focusstack,     {.i = -1 } },
/*	{ MODKEY,           XK_i,      incnmaster,     {.i = +1 } }, */
/*	{ MODKEY,           XK_d,      incnmaster,     {.i = -1 } }, */
	{ MODKEY,           XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,           XK_l,      setmfact,       {.f = +0.05} },
/*	{ MODKEY,           XK_Return, zoom,           {0} }, */
	{ MODKEY,           XK_Tab,    view,           {0} },
	{ MODKEY,           XK_q,      killclient,     {0} },
	{ MODKEY,           XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,           XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,           XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,           XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask, XK_space,  togglefloating, {0} },
	{ MODKEY,           XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask, XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,           XK_Left,   focusmon,       {.i = -1 } },
	{ MODKEY,           XK_Right,  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask, XK_Left,   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask, XK_Right,  tagmon,         {.i = +1 } },
	{ MODKEY,           XK_u,      swalstopsel,    {0} },
	{ MODKEY,           XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,           XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask, XK_equal,  setgaps,        {.i = 0  } },

	TAGKEYS( XK_1, 0)
	TAGKEYS( XK_2, 1)
	TAGKEYS( XK_3, 2)
	TAGKEYS( XK_4, 3)
	TAGKEYS( XK_5, 4)
	TAGKEYS( XK_6, 5)
	TAGKEYS( XK_7, 6)
	TAGKEYS( XK_8, 7)
	TAGKEYS( XK_9, 8)

	{ 0,      XK_Print,  			spawn, SHCMD("scrot -f ~/img/scrot.jpg -os") },
	{ MODKEY, XK_Print,  			spawn, SHCMD("scrot -f ~/img/scrot.jpg -o") },
	{ MODKEY, XK_Pause,  			spawn, SHCMD("xset dpms force suspend") },
	{ MODKEY, XK_Scroll_Lock,  		spawn, SHCMD("killall Xorg") },

	/* volume related extra keys */
	{ 0, XF86XK_AudioMute, 			spawn, SHCMD("pamixer -t") },
	{ 0, XF86XK_AudioRaiseVolume, 	spawn, SHCMD("pamixer --allow-boost -i 3") },
	{ 0, XF86XK_AudioLowerVolume, 	spawn, SHCMD("pamixer --allow-boost -d 3") },

    { MODKEY|ShiftMask,             XK_r,      self_restart,   {1} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click            event mask      	button     	function        argument */
	{ ClkLtSymbol,      0,              	Button1,	setlayout,      {0} },
	{ ClkLtSymbol,      0,              	Button3,    setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,      0,              	Button2,    zoom,           {0} },
	{ ClkStatusText,    0,              	Button2,    spawn,          SHCMD("st") },
	{ ClkClientWin,     MODKEY,         	Button1,    movemouse,      {0} },
	{ ClkClientWin,     MODKEY,         	Button2,    togglefloating, {0} },
	{ ClkClientWin,    	MODKEY,         	Button3,    resizemouse,    {0} },
	{ ClkClientWin,		MODKEY|ShiftMask, 	Button1,    swalmouse,      {0} },
	{ ClkTagBar,        0,              	Button1,    view,           {0} },
	{ ClkTagBar,        0,              	Button3,    toggleview,     {0} },
	{ ClkTagBar,        MODKEY,         	Button1,    tag,            {0} },
	{ ClkTagBar,        MODKEY,         	Button3,    toggletag,      {0} },
};
