# DWM (Dynamic Window Manager)

![Preview](https://raw.github.com/razobeckett/dwm/readme/assets/preview.png)
### User Guide:
- Look for `/* user constants */` in `config.def.h` to set your preferred terminal and file manager for keybinds.
- Scripts used for specific functionalities are available in my [dotfiles repository](https://github.com/razobeckett/dotfiles), e.g., FN key functionality.
- Application rules are defined in a separate file called `apprules.h`.
> **Info:** Remove the `xset` command from the autostart in `config.def.h` to experience normal keyboard speed.

### How to install:
-  Arch Linux:
```
sudo pacman -S --needed base-devel xorg-server xorg-xinit libx11 libxinerama libxft git vim && \
	git clone https://github.com/razobeckett/dwm && \
	cd dwm && sudo make clean install
```

### Keybinds
> **Info:** These are just a few basic keybinds to get started; explore `config.def.h` for more.

| Keybind              | Function                                  |
| -------------------- | ----------------------------------------- |
| Space + Return       | Opens the terminal.                       |
| CTRL + p             | Opens rofi (app search).                  |
| ALT + Space          | Opens dmenu.                              |
| ALT + [1..0]         | Switches between tags (workspaces).       |
| ALT + SHIFT + [1..0] | Moves window between tags (workspaces).   |
| ALT + SHIFT + L/H    | Moves window right and left respectively. |

### Addition Utilities used with setup:
- **picom**: Enables effects and animations.
- **slstatus**: Displays system status and date/time.
- **rofi**: Facilitates application search.
- **volumeicon**: Allows volume adjustment using the mouse.
- **nm-applet**: Manages WiFi and network icons.
- **xfce4-clipman**: Provides a GUI clipboard manager.
- **nitrogen**: Manages wallpapers.
- **touchegg**: Enables mouse gestures.
- **Nerd Font** (Default: JetBrainsMono Nerd Font) - You can change the font in `config.def.h`.

> **Caution:** this is heavily modified ; if you want to apply any patch, it recommended to patch manually.
