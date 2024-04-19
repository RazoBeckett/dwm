# DWM (Dynamic Window Manager)

![Preview](assets/preview.png)

# User Guide:

- Application rules are defined in a separate file called `apprules.h`.

## BUILD INSTRUCTIONS

### compile dependencies:

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

### How to compile:

- Clone the repository and change directory:

  ```bash
  git clone https://github.com/razobeckett/dwm && cd dwm
  ```

  - Compile and install:
    ```bash
    make clean install
    ```
    > NOTE: If you are not a root user, you can use `doas` or `sudo` to run the command.

- After compiling, you can start the window manager using the following methods:
  - for Xinit:
    - put `exec dwm` in `~/.xinitrc` at the end on new line
    - now run `startx`
  - for display manager:
    - paste [dwm.desktop](dwm.desktop) file in `/usr/share/xsessions/`
    - restart your display manager or system

### Keybinds

> **Info:** These are just a few basic keybinds to get started; you can always add and modify them in `config.h`.

| Keybind              | Function                                  |
| -------------------- | ----------------------------------------- |
| Super + Return       | Opens the terminal.                       |
| Super + Space        | Opens dmenu.                              |
| ALT + [1..0]         | Switches between tags (workspaces).       |
| ALT + SHIFT + [1..0] | Moves window between tags (workspaces).   |
| ALT + SHIFT + L/H    | Moves window right and left respectively. |
| ALT + Q              | Closes the window.                        |

### Addition Utilities used with setup:

- **picom**: Enables effects and animations.
- [**dwmblocks-async**](https://github.com/UtkarshVerma/dwmblocks-async): Displays system status and date/time.

> **Caution:** This has been heavily modified; if you wish to apply any patches, it is recommended to do so manually.
