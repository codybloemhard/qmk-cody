/* Copyright 2019 Ryota Goto
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#define L_BASE_STD 0
#define L_BASE_GAME 1
#define L_BASE_QWERTY 2
#define L_UP 3
#define L_DOWN 4
#define L_FN 5
#define L_MOUSE 6
#define L_BLS 7

enum custom_keycodes{
    PLACEHOLDER = SAFE_RANGE,
    HMDIR,
    LSTD,
    LGAMING,
    LQWERTY,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record){
    switch(keycode){
        case HMDIR:
            if(record->event.pressed) SEND_STRING("~/");
            break;
        case LSTD:
            if(record->event.pressed){
                layer_on(L_BASE_STD);
                layer_off(L_BASE_GAME);
                layer_off(L_BASE_QWERTY);
            }
            break;
        case LGAMING:
            if(record->event.pressed){
                layer_on(L_BASE_GAME);
                layer_off(L_BASE_STD);
                layer_off(L_BASE_QWERTY);
            }
            break;
        case LQWERTY:
            if(record->event.pressed){
                layer_on(L_BASE_QWERTY);
                layer_off(L_BASE_STD);
                layer_off(L_BASE_GAME);
            }
            break;
    }
    return true;
}

// Uses: https://github.com/qmk/qmk_firmware/pull/9404
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Immediately select the hold action when another key is pressed.
        case LT(L_FN, KC_ENT):
            return true;
        // Do not select the hold action when another key is pressed.
        default:
            return false;
    }
}

#define K_TAB LT(L_MOUSE, KC_TAB)
#define K_CAP MT(MOD_LGUI, KC_0)
#define K_SHF MT(MOD_LCTL, KC_ESC)
#define K_LFN LT(L_FN, KC_ENT)
#define HN_U LT(L_UP, KC_N)
#define HA_U LT(L_UP, KC_A)
#define HE_D LT(L_DOWN, KC_E)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [L_BASE_STD] = LAYOUT_all(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_EQL,  _______, _______, _______,  _______, KC_F13,
    K_TAB,   KC_Q,    KC_G,    KC_M,    KC_L,    KC_W,    KC_Y,    KC_F,    KC_U,    KC_B,    KC_SCLN, KC_MINS, _______,           KC_BSPC,
    K_CAP,   KC_D,    KC_S,    KC_T,    HN_U,    KC_R,    KC_I,    HA_U,    HE_D,    KC_O,    KC_H,    KC_QUOT,                    _______,
    K_SHF,   _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_J,    KC_K,    KC_P,    KC_COMM, KC_DOT,  KC_SLSH,          MO(L_BLS),KC_CAPS,
    _______, _______, KC_LALT,          KC_LSFT,          K_LFN,   KC_SPC,                             KC_RALT, _______, KC_APP,   KC_RCTL
  ),
  [L_BASE_GAME] = LAYOUT_all(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_GRAVE, KC_F13,
    KC_TAB,  KC_Q,    KC_G,    KC_M,    KC_L,    KC_W,    KC_Y,    KC_F,    KC_U,    KC_B,    KC_SCLN, KC_LBRC, KC_RBRC,           KC_BSPC,
    KC_LGUI, KC_D,    KC_S,    KC_T,    KC_N,    KC_R,    KC_I,    KC_A,    KC_E,    KC_O,    KC_H,    KC_QUOT,                    HMDIR,
    KC_LSFT, _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_J,    KC_K,    KC_P,    KC_COMM, KC_DOT,  KC_SLSH,          MO(L_BLS),KC_CAPS,
    KC_LCTL, KC_LGUI, KC_LALT,          KC_SPC,           K_LFN,   KC_SPC,                             KC_RALT, LSTD,    KC_APP,   KC_RCTL
  ),
  [L_BASE_QWERTY] = LAYOUT_all(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS,  KC_DEL,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,           KC_BSPC,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,                    KC_ENT,
    KC_LSFT, KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          MO(L_BLS),KC_RSFT,
    KC_LCTL, KC_LGUI, KC_LALT,          KC_SPC,           MO(L_FN),         KC_SPC,                    KC_RALT, KC_RGUI, KC_APP,   KC_RCTL
  ),
  [L_UP] = LAYOUT_all(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_GRV,  KC_TILD, _______, _______, _______,
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, _______,
    _______, _______, _______, _______, _______, KC_BSLS, KC_PIPE, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______,          _______,          _______,          _______,                   _______, _______, _______, _______
  ),
  [L_DOWN] = LAYOUT_all(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, KC_RBRC, KC_RCBR, KC_RPRN, KC_EQL,  _______, _______, _______, _______, _______, _______, _______, _______,
    _______, HMDIR,   KC_LBRC, KC_LCBR, KC_LPRN, KC_PLUS, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, KC_BSLS, KC_PIPE, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______,          _______,          _______,          _______,                   _______, _______, _______, _______
  ),
  [L_FN] = LAYOUT_all(
    QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,
    _______, _______, _______, KC_PGUP, _______, _______, _______, KC_BSPC, KC_UP,   KC_DEL,  _______, _______, _______,          _______,
    _______, _______, KC_HOME, KC_PGDN, KC_END,  _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,                   KC_DEL,
    KC_LSFT, _______, _______, DM_RSTP, DM_REC1, DM_PLY1, DM_REC2, DM_PLY2, KC_ESC,  _______, _______, _______,          _______, _______,
    _______, _______, _______,          KC_ESC,           _______,          KC_ENT,                    _______, _______, _______, _______
  ),
  [L_MOUSE] = LAYOUT_all(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______, _______, KC_BTN1, KC_MS_U, KC_BTN2, _______, _______, _______,          _______,
    _______, _______, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,                   _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
    _______, _______, _______,          _______,          _______,          _______,                   _______, _______, _______, _______
  ),
  [L_BLS] = LAYOUT_all(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, LSTD,    LGAMING, LQWERTY, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
    _______, _______, _______,          _______,          _______,          _______,                   _______, _______, _______, _______
  ),
};

