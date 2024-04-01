# DWM (Dynamic Window Manager)

![Preview](assets/preview.png)

### User Guide:

- Look for `/* user constants */` in `config.def.h` to set your preferred terminal and file manager for keybinds.
- Scripts used for specific functionalities are available in my [dotfiles](https://github.com/RazoBeckett/dotfiles/tree/main/.local/bin) repository, e.g., FN key functionality.
- Application rules are defined in a separate file called `apprules.h`.
  > **Info:** Remove the `xset` command from the autostart in `config.def.h` to experience normal keyboard speed.

### How to install:

- Arch Linux:

  ```bash
  sudo pacman -S --needed base-devel xorg-server xorg-xinit libx11 libxinerama libxft git vim && \
  	git clone https://github.com/razobeckett/dwm && \
  	cd dwm && sudo make clean install
  ```

- Ubuntu/Debian:

  ```bash
  sudo apt install build-essential xorg libx11-dev libxinerama-dev libxft-dev git vim && \
    git clone https://github.com/razobeckett/dwm && \
    cd dwm && sudo make clean install
  ```

- After installation, you can start dwm using:
  - for Xinit:
    - put `exec dwm` in `~/.xinitrc` at the end on new line
    - now run `startx`
  - for display manager:
    - paste [dwm.desktop](dwm.desktop) file in `/usr/share/xsessions/`
    - restart your display manager or system

### Keybinds

> **Info:** These are just a few basic keybinds to get started; explore `config.def.h` for more.

| Keybind              | Function                                  |
| -------------------- | ----------------------------------------- |
| Super + Return       | Opens the terminal.                       |
| Super + Space        | Opens dmenu.                              |
| Super + p            | Opens rofi (app search).                  |
| Super + e            | Opens filemanager (PCManFM).              |
| Super + f            | Opens FireFox.                            |
| Super + b            | Opens Brave-Browser.                      |
| ALT + [1..0]         | Switches between tags (workspaces).       |
| ALT + SHIFT + [1..0] | Moves window between tags (workspaces).   |
| ALT + SHIFT + L/H    | Moves window right and left respectively. |
| ALT + Q              | Closes the window.                        |

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

> **Caution:** This has been heavily modified; if you wish to apply any patches, it is recommended to do so manually.
