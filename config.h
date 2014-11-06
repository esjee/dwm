#include "mpdcontrol.c"

/* appearance */
static const char font[]            = "terminusmodx 8";

/* normal */
static const char normbordercolor[] = "#000000";
static const char normbgcolor[]     = "#000000";
static const char normfgcolor[]     = "#cccaca";

/* selected */
static const char selbordercolor[]  = "#cccaca";
static const char selbgcolor[]      = "#040463";
static const char selfgcolor[]      = "#eeecec";

static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = False;     /* False means bottom bar */

/* tagging */
static const char *tags[] =
	{"壱", "弐", "参", "肆", "伍", "陸", "漆", "捌", "玖"};

static const Rule rules[] = {
/* class instance title tags mask isfloating monitor */
{ "Gimp",	NULL,	NULL,	1 << 5,	False,	-1 },
};

/* layout */
/* factor of master area size [0.05..0.95] */
static const float mfact      = 0.64;
/* number of clients in master area */
static const int nmaster      = 1;
/* True means respect size hints in tiled resizals */
static const Bool resizehints = False;

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "普通",	tile },    /* first entry is default */
	{ "自由",	NULL },    /* NULL means floating behavior */
	{ "大",		monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,			KEY, view,	{.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,		KEY, toggleview,{.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,		KEY, tag,	{.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY, toggletag,	{.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
#define FIREFOX_GTKFIX ""\
"env GTK2_RC_FILES=/home/plague/.static/firefox-gtkrc "\
"/usr/bin/firefox"

#define SHUTDOWN "sudo /sbin/poweroff"
#define SLEEP "sudo /usr/sbin/pm-suspend"
#define REBOOT "sudo /sbin/reboot"
#define SCROT_FULL "/usr/bin/scrot /home/plague/screenshot.png"

static const char *dmenucmd[] = {
	"/usr/bin/dmenu_run",
	"-f",
	"-b",
	"-fn", font,
	"-nb", normbgcolor,
	"-nf", normfgcolor,
	"-sb", selbgcolor,
	"-sf", selfgcolor,
	NULL };
static const char *termcmd[]  = {
	"/usr/bin/urxvtc",
	NULL };
static const char *volupcmd[] = {
	"/usr/bin/amixer",
	"-q",
	"set",
	"Master",
	"3%+",
	NULL };
static const char *voldowncmd[] = {
	"/usr/bin/amixer",
	"-q",
	"set",
	"Master",
	"3%-",
	NULL };

static Key keys[] = {
	/* modifiers	keys	functions	argument */
	/* window manipulation */
	{ MODKEY,		XK_j,		focusstack,	{.i = +1 } },
	{ MODKEY,		XK_k,		focusstack,	{.i = -1 } },
	//{ MODKEY,		XK_i,		incnmaster,	{.i = +1 } },
	//{ MODKEY,		XK_d,		incnmaster,	{.i = -1 } },
	{ MODKEY|ShiftMask,	XK_j,		pushdown,	{0} },
	{ MODKEY|ShiftMask,	XK_k,		pushup,		{0} },
	{ MODKEY,		XK_f,		zoom,		{0} },
	{ MODKEY,		XK_Tab,		view,		{0} },
	{ MODKEY|ShiftMask,	XK_c,		killclient,	{0} },
	{ MODKEY,		XK_t,		setlayout,	{.v = &layouts[0]} },
	//{ MODKEY,XK_f,ssetlayout,s{.v = &layouts[1]} },
	{ MODKEY,		XK_m,		setlayout,	{.v = &layouts[2]} },
	{ MODKEY,		XK_space,	setlayout,	{0} },
	{ MODKEY|ShiftMask,	XK_space,	togglefloating,	{0} },
	{ MODKEY,		XK_0,		view,		{.ui = ~0 } },
	{ MODKEY|ShiftMask,	XK_0,		tag,		{.ui = ~0 } },
	{ MODKEY,		XK_comma,	focusmon,	{.i = -1 } },
	{ MODKEY,		XK_period,	focusmon,	{.i = +1 } },
	{ MODKEY|ShiftMask,	XK_comma,	tagmon,		{.i = -1 } },
	{ MODKEY|ShiftMask,	XK_period,	tagmon,		{.i = +1 } },

	/* Tag jumping */
	TAGKEYS(XK_1,0)
	TAGKEYS(XK_2,1)
	TAGKEYS(XK_3,2)
	TAGKEYS(XK_4,3)
	TAGKEYS(XK_5,4)
	TAGKEYS(XK_6,5)
	TAGKEYS(XK_7,6)
	TAGKEYS(XK_8,7)
	TAGKEYS(XK_9,8)

	/* applications/hotkeys */
	{ MODKEY,		XK_r,		spawn,		{.v = dmenucmd } },
	{ MODKEY,		XK_Return,	spawn,		{.v = termcmd } },
	{ MODKEY,		XK_s,		spawn,		SHCMD(FIREFOX_GTKFIX) },
	{ MODKEY,		XK_Print,	spawn,		SHCMD(SCROT_FULL) },
	{ MODKEY,		XK_semicolon,	spawn,		SHCMD("/home/plague/bin/_randbg.sh") },

	/* system */
	{ MODKEY|ShiftMask|ControlMask,	XK_F12,		spawn,		 SHCMD(SHUTDOWN) },
	{ MODKEY|ShiftMask|ControlMask,	XK_F11,		spawn,		 SHCMD(REBOOT) },
	{ MODKEY|ShiftMask|ControlMask,	XK_F1,		spawn,		 SHCMD(SLEEP) },
	{ MODKEY|ShiftMask|ControlMask,	XK_q,		quit,		{0} },	/* kill dwm */
	{ MODKEY,			XK_b,		togglebar,	{0} },

	/* volume, music */
	{ MODKEY,			XK_equal,	spawn,		{.v = volupcmd } },
	{ MODKEY,			XK_minus,	spawn,		{.v = voldowncmd } },
	{ MODKEY,			XK_bracketright,mpdchange,	{.i = +1} }, /* next song */
	{ MODKEY,			XK_bracketleft,	mpdchange,	{.i = -1} }, /* prev song */
	{ MODKEY,			XK_p,		mpdcontrol,	{.i = MPD_ARGPAUSE} }, /* pause */
	{ MODKEY|ShiftMask,		XK_p,		mpdcontrol,	{.i = MPD_ARGSTOP} }, /* stop */

	/* modifier                     key        function        argument */

	/* unused keybindings kept here for safekeeping */
	/* resizing windows */
	//{ MODKEY,		XK_h,		setmfact,	{.f = -0.05} },
	//{ MODKEY,		XK_l,		setmfact,	{.f = +0.05} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

/* vim: set ft=c: */
/* vim: set cc=0: */
