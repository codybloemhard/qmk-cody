# qmk-guide-arch
This is a little guide on how to get started with QMK on Arch Linux.
If you change some commands it should work with other distro's as well.
## Install
Clone the QMK repo: `git clone https://github.com/qmk/qmk_firmware.git`.
Go inside the qmk_firmware director: `cd qmk_firmware`.
Runs the install script, this will install the right packages for you: `util/linux_install.sh`.
You might need to confirm some prompts.
Then run `make git-submodule` to install the last bits.
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
When flashing, make sure to be a root user or use sudo as it will not find your board otherwise.
For example: `sudo make a03/polaris:default:dfu`.
Replug your board and observe the changes.
## Make a new keymap
To make a new keymap, go to the `keyboards` directory and find your board.
Then go to the keymaps dir of your board and choose a existing keymap to base yours on.
Copy the dir of that keymap inside the `keymaps` dir.
For example: 
```
cd keyboards/ai03/polaris/keymaps
cp default my-keymap
```
Now you can edit your keymap inside it's dir.
When in the `qmk_firmware` dir you can flash it by doing `make ai03/polaris:my-keymap:dfu`, for example.
