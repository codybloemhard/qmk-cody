# qmk-cody

Just a little repo for my keymaps.

## keymaps

This is a directory with my keymaps.

## Compile and flash keymaps

To compile or flash a keymap, make sure you are in the `qmk_firmware` directory.
The command is as follows: `make keyboard:keymap:flash`.
In the current directory there is a directory names `keyboards` with many directories with designers.
For example `keyboards/ai03`. Inside that there are directories for keyboards, for example `keyboards/ai03/polaris`.
Inside that you can find files including `config.h`, `rules.mk` and a directory `keymaps`.
Inside that are some keymaps, for example `keyboards/ai03/polaris/default`.
To compile the default keymap for polaris, for example, you can do `make ai03/polaris:default`.
Make sure you are in the `qmk_firmware` directory.
To compile and flash a keymap to your keyboard you need to make sure your keyboard is in bootloader mode.
On polaris this can be done by holding the top-left key or the reset button while plugging it in.
The board will not work in booloader mode.
Flash the board with the right flash parameter, this changes per board, for polaris it is `dfu`.
If QMK is installed on root use `sudo` with the make command.

## Install QMK on Artix Linux

You can install it with the unofficial qmk arch package:
```
sudo pacman -S qmk
git clone https://github.com/qmk/qmk_firmware.git
cd qmk_firmware
qmk setup
make ai03/polaris:cody:dfu # test a keymap
```
If that doesn't work or you want to follow the guide
(https://github.com/qmk/qmk_firmware/blob/master/docs/newbs_getting_started.md)
you need to change some stuff. Qmk setup will not recognize Artix and can't install the dependencies for you.
You need to do this yourself:
```
sudo pacman -S python-pip libffi
python3 -m pip install --user qmk
pip install --upgrade pip
add .local/bin to path
fish_add_path ~/.local/bin
sudo pacman -S dfu-util dfu-programmer avrdude avr-gcc arm-none-eabi-gcc avr-libc
git clone https://github.com/qmk/qmk_firmware.git
cd qmk_firmware
qmk setup
make ai03/polaris:cody:dfu # test a keymap
```
