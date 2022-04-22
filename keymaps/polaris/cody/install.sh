#!/bin/sh
if [ -d "$HOME/git/qmk_firmware" ]
then
    if [ ! -f "$HOME/git/qmk_firmware/keyboards/ai03/polaris/config-backup.h" ]; then
        mv ~/git/qmk_firmware/keyboards/ai03/polaris/config.h ~/git/qmk_firmware/keyboards/ai03/polaris/config-backup.h
        echo "\tbacked up config.h"
    fi
    if [ ! -f "$HOME/git/qmk_firmware/keyboards/ai03/polaris/rules.mk" ]; then
        mv ~/git/qmk_firmware/keyboards/ai03/polaris/rules.mk ~/git/qmk_firmware/keyboards/ai03/polaris/rules-backup.mk
        echo "\tbacked up rules.mk"
    fi
    cp config.h ~/git/qmk_firmware/keyboards/ai03/polaris/config.h
    cp rules.mk ~/git/qmk_firmware/keyboards/ai03/polaris/rules.mk
    if [ ! -d "$HOME/git/qmk_firmware/keyboards/ai03/polaris/keymaps/cody" ]; then
        mkdir ~/git/qmk_firmware/keyboards/ai03/polaris/keymaps/cody
    fi
    cp keymap.c ~/git/qmk_firmware/keyboards/ai03/polaris/keymaps/cody/keymap.c
    echo "\tcopied files"
    echo "\tdone!"
else # if you do not keep all your git repos in ~/git you are a heretic and you live your life wrong!
    echo "git/qmk_firmware doesn't exist!"
fi
