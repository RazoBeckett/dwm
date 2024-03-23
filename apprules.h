static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class	instance    title       tagsmask     isfloating   monitor */

    // Python Tkinter
    {"tk", NULL, NULL, 0, 1, -1},  // Allow tk on any workspace and make it floating
    {"Tk", NULL, NULL, 0, 1, -1},  // Allow Tk on any workspace and make it floating
    {"!toplevel",NULL, NULL, 0, 1, -1},
    {"Toplevel",NULL, NULL, 0, 1, -1},

    // Applications
    {"dev.warp.Warp", NULL, NULL, 1, 0, -1},
    {"firefox", NULL, NULL, 2, 0, -1},
    {"pcmanfm", NULL, NULL, 1 << 2, 0, -1},	// pcmanfm on 3rd workspace
    {"Pcmanfm", NULL, NULL, 1 << 2, 0, -1},	// Pcmanfm on 3rd workspace
    {"org.gnome.Nautilus", NULL, NULL, 1 << 2, 0, -1},	// Nautilus on 3rd workspace
    {"obsidian", NULL, NULL, 1 << 8, 0, -1},	// obsidian on 9th workspace
};
