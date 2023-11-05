From 8b1d33db9cbc03bf12df398bb14e62389efc70a3 Mon Sep 17 00:00:00 2001
From: ViliamKovac1223 <viliamkovac1223@gmail.com>
Date: Sun, 9 Oct 2022 16:29:28 -0400
Subject: [PATCH] add alt-tab functionality

Co-authored-by: Daniel Gerblick <daniel.gerblick@gmail.com>
---
 config.def.h |  11 ++-
 dwm.c        | 218 +++++++++++++++++++++++++++++++++++++++++++++++++++
 2 files changed, 228 insertions(+), 1 deletion(-)

diff --git a/config.def.h b/config.def.h
index 061ad66..7a9e3b1 100644
--- a/config.def.h
+++ b/config.def.h
@@ -1,5 +1,13 @@
 /* See LICENSE file for copyright and license details. */
 
+/* alt-tab configuration */
+static const unsigned int tabModKey 		= 0x40;	/* if this key is hold the alt-tab functionality stays acitve. This key must be the same as key that is used to active functin altTabStart `*/
+static const unsigned int tabCycleKey 		= 0x17;	/* if this key is hit the alt-tab program moves one position forward in clients stack. This key must be the same as key that is used to active functin altTabStart */
+static const unsigned int tabPosY 			= 1;	/* tab position on Y axis, 0 = bottom, 1 = center, 2 = top */
+static const unsigned int tabPosX 			= 1;	/* tab position on X axis, 0 = left, 1 = center, 2 = right */
+static const unsigned int maxWTab 			= 600;	/* tab menu width */
+static const unsigned int maxHTab 			= 200;	/* tab menu height */
+
 /* appearance */
 static const unsigned int borderpx  = 1;        /* border pixel of windows */
 static const unsigned int snap      = 32;       /* snap pixel */
@@ -71,7 +79,7 @@ static const Key keys[] = {
 	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
 	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
 	{ MODKEY,                       XK_Return, zoom,           {0} },
-	{ MODKEY,                       XK_Tab,    view,           {0} },
+	{ MODKEY,                       XK_q,	   view,           {0} },
 	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
 	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
 	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
@@ -84,6 +92,7 @@ static const Key keys[] = {
 	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
 	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
 	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
+	{ Mod1Mask,             		XK_Tab,    altTabStart,	   {0} },
 	TAGKEYS(                        XK_1,                      0)
 	TAGKEYS(                        XK_2,                      1)
 	TAGKEYS(                        XK_3,                      2)
diff --git a/dwm.c b/dwm.c
index e5efb6a..f606311 100644
--- a/dwm.c
+++ b/dwm.c
@@ -40,6 +40,7 @@
 #include <X11/extensions/Xinerama.h>
 #endif /* XINERAMA */
 #include <X11/Xft/Xft.h>
+#include <time.h>
 
 #include "drw.h"
 #include "util.h"
@@ -119,6 +120,11 @@ struct Monitor {
 	int by;               /* bar geometry */
 	int mx, my, mw, mh;   /* screen size */
 	int wx, wy, ww, wh;   /* window area  */
+	int altTabN;		  /* move that many clients forward */
+	int nTabs;			  /* number of active clients in tag */
+	int isAlt; 			  /* 1,0 */
+	int maxWTab;
+	int maxHTab;
 	unsigned int seltags;
 	unsigned int sellt;
 	unsigned int tagset[2];
@@ -127,8 +133,10 @@ struct Monitor {
 	Client *clients;
 	Client *sel;
 	Client *stack;
+	Client ** altsnext; /* array of all clients in the tag */
 	Monitor *next;
 	Window barwin;
+	Window tabwin;
 	const Layout *lt[2];
 };
 
@@ -234,6 +242,9 @@ static int xerror(Display *dpy, XErrorEvent *ee);
 static int xerrordummy(Display *dpy, XErrorEvent *ee);
 static int xerrorstart(Display *dpy, XErrorEvent *ee);
 static void zoom(const Arg *arg);
+void drawTab(int nwins, int first, Monitor *m);
+void altTabStart(const Arg *arg);
+static void altTabEnd();
 
 /* variables */
 static const char broken[] = "broken";
@@ -477,6 +488,7 @@ cleanup(void)
 	Monitor *m;
 	size_t i;
 
+	altTabEnd();
 	view(&a);
 	selmon->lt[selmon->sellt] = &foo;
 	for (m = mons; m; m = m->next)
@@ -644,6 +656,7 @@ createmon(void)
 	m->topbar = topbar;
 	m->lt[0] = &layouts[0];
 	m->lt[1] = &layouts[1 % LENGTH(layouts)];
+	m->nTabs = 0;
 	strncpy(m->ltsymbol, layouts[0].symbol, sizeof m->ltsymbol);
 	return m;
 }
@@ -1648,6 +1661,211 @@ spawn(const Arg *arg)
 	}
 }
 
+void
+altTab()
+{
+	/* move to next window */
+	if (selmon->sel != NULL && selmon->sel->snext != NULL) {
+		selmon->altTabN++;
+		if (selmon->altTabN >= selmon->nTabs)
+			selmon->altTabN = 0; /* reset altTabN */
+
+		focus(selmon->altsnext[selmon->altTabN]);
+		restack(selmon);
+	}
+
+	/* redraw tab */
+	XRaiseWindow(dpy, selmon->tabwin);
+	drawTab(selmon->nTabs, 0, selmon);
+}
+
+void
+altTabEnd()
+{
+	if (selmon->isAlt == 0)
+		return;
+
+	/*
+	* move all clients between 1st and choosen position,
+	* one down in stack and put choosen client to the first position 
+	* so they remain in right order for the next time that alt-tab is used
+	*/
+	if (selmon->nTabs > 1) {
+		if (selmon->altTabN != 0) { /* if user picked original client do nothing */
+			Client *buff = selmon->altsnext[selmon->altTabN];
+			if (selmon->altTabN > 1)
+				for (int i = selmon->altTabN;i > 0;i--)
+					selmon->altsnext[i] = selmon->altsnext[i - 1];
+			else /* swap them if there are just 2 clients */
+				selmon->altsnext[selmon->altTabN] = selmon->altsnext[0];
+			selmon->altsnext[0] = buff;
+		}
+
+		/* restack clients */
+		for (int i = selmon->nTabs - 1;i >= 0;i--) {
+			focus(selmon->altsnext[i]);
+			restack(selmon);
+		}
+
+		free(selmon->altsnext); /* free list of clients */
+	}
+
+	/* turn off/destroy the window */
+	selmon->isAlt = 0;
+	selmon->nTabs = 0;
+	XUnmapWindow(dpy, selmon->tabwin);
+	XDestroyWindow(dpy, selmon->tabwin);
+}
+
+void
+drawTab(int nwins, int first, Monitor *m)
+{
+	/* little documentation of functions */
+	/* void drw_rect(Drw *drw, int x, int y, unsigned int w, unsigned int h, int filled, int invert); */
+	/* int drw_text(Drw *drw, int x, int y, unsigned int w, unsigned int h, unsigned int lpad, const char *text, int invert); */
+	/* void drw_map(Drw *drw, Window win, int x, int y, unsigned int w, unsigned int h); */
+
+	Client *c;
+	int h;
+
+	if (first) {
+		Monitor *m = selmon;
+		XSetWindowAttributes wa = {
+			.override_redirect = True,
+			.background_pixmap = ParentRelative,
+			.event_mask = ButtonPressMask|ExposureMask
+		};
+
+		selmon->maxWTab = maxWTab;
+		selmon->maxHTab = maxHTab;
+
+		/* decide position of tabwin */
+		int posX = selmon->mx;
+		int posY = selmon->my;
+		if (tabPosX == 0)
+			posX += 0;
+		if (tabPosX == 1)
+			posX += (selmon->mw / 2) - (maxWTab / 2);
+		if (tabPosX == 2)
+			posX += selmon->mw - maxWTab;
+
+		if (tabPosY == 0)
+			posY += selmon->mh - maxHTab;
+		if (tabPosY == 1)
+			posY += (selmon->mh / 2) - (maxHTab / 2);
+		if (tabPosY == 2)
+			posY += 0;
+
+		h = selmon->maxHTab;
+		/* XCreateWindow(display, parent, x, y, width, height, border_width, depth, class, visual, valuemask, attributes); just reference */
+		m->tabwin = XCreateWindow(dpy, root, posX, posY, selmon->maxWTab, selmon->maxHTab, 2, DefaultDepth(dpy, screen),
+								CopyFromParent, DefaultVisual(dpy, screen),
+								CWOverrideRedirect|CWBackPixmap|CWEventMask, &wa); /* create tabwin */
+
+		XDefineCursor(dpy, m->tabwin, cursor[CurNormal]->cursor);
+		XMapRaised(dpy, m->tabwin);
+
+	}
+
+	h = selmon->maxHTab  / m->nTabs;
+
+	int y = 0;
+	int n = 0;
+	for (int i = 0;i < m->nTabs;i++) { /* draw all clients into tabwin */
+		c = m->altsnext[i];
+		if(!ISVISIBLE(c)) continue;
+		/* if (HIDDEN(c)) continue; uncomment if you're using awesomebar patch */
+
+		n++;
+		drw_setscheme(drw, scheme[(c == m->sel) ? SchemeSel : SchemeNorm]);
+		drw_text(drw, 0, y, selmon->maxWTab, h, 0, c->name, 0);
+		y += h;
+	}
+
+	drw_setscheme(drw, scheme[SchemeNorm]);
+	drw_map(drw, m->tabwin, 0, 0, selmon->maxWTab, selmon->maxHTab);
+}
+
+void
+altTabStart(const Arg *arg)
+{
+	selmon->altsnext = NULL;
+	if (selmon->tabwin)
+		altTabEnd();
+
+	if (selmon->isAlt == 1) {
+		altTabEnd();
+	} else {
+		selmon->isAlt = 1;
+		selmon->altTabN = 0;
+
+		Client *c;
+		Monitor *m = selmon;
+
+		m->nTabs = 0;
+		for(c = m->clients; c; c = c->next) { /* count clients */
+			if(!ISVISIBLE(c)) continue;
+			/* if (HIDDEN(c)) continue; uncomment if you're using awesomebar patch */
+
+			++m->nTabs;
+		}
+
+		if (m->nTabs > 0) {
+			m->altsnext = (Client **) malloc(m->nTabs * sizeof(Client *));
+
+			int listIndex = 0;
+			for(c = m->stack; c; c = c->snext) { /* add clients to the list */
+				if(!ISVISIBLE(c)) continue;
+				/* if (HIDDEN(c)) continue; uncomment if you're using awesomebar patch */
+
+				m->altsnext[listIndex++] = c;
+			}
+
+			drawTab(m->nTabs, 1, m);
+
+			struct timespec ts = { .tv_sec = 0, .tv_nsec = 1000000 };
+
+			/* grab keyboard (take all input from keyboard) */
+			int grabbed = 1;
+			for (int i = 0;i < 1000;i++) {
+				if (XGrabKeyboard(dpy, DefaultRootWindow(dpy), True, GrabModeAsync, GrabModeAsync, CurrentTime) == GrabSuccess)
+					break;
+				nanosleep(&ts, NULL);
+				if (i == 1000 - 1)
+					grabbed = 0;
+			}
+
+			XEvent event;
+			altTab();
+			if (grabbed == 0) {
+				altTabEnd();
+			} else {
+				while (grabbed) {
+					XNextEvent(dpy, &event);
+					if (event.type == KeyPress || event.type == KeyRelease) {
+						if (event.type == KeyRelease && event.xkey.keycode == tabModKey) { /* if super key is released break cycle */
+							break;
+						} else if (event.type == KeyPress) {
+							if (event.xkey.keycode == tabCycleKey) {/* if XK_s is pressed move to the next window */
+								altTab();
+							}
+						}
+					}
+				}
+
+				c = selmon->sel;
+				altTabEnd(); /* end the alt-tab functionality */
+				/* XUngrabKeyboard(display, time); just a reference */
+				XUngrabKeyboard(dpy, CurrentTime); /* stop taking all input from keyboard */
+				focus(c);
+				restack(selmon);
+			}
+		} else {
+			altTabEnd(); /* end the alt-tab functionality */
+		}
+	}
+}
+
 void
 tag(const Arg *arg)
 {
-- 
2.37.3

