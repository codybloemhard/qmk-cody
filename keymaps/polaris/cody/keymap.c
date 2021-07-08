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

enum custom_keycodes{
    HMDIR,
    LROTATE,
    LPRINT,
};

char bfl = 0; // base layer, used to rotate bewteen bottom layer
char nbls = 3;

#define L_BASE_CODY 0
#define L_BASE_GAMING 1
#define L_BASE_STDISH 2
#define L_FN 3
#define L_MOUSE 4
#define L_EXTRA 5

// Uses: https://github.com/qmk/qmk_firmware/pull/9404
// So not compatibel with master (yet)
// Build from a modified branch
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

bool process_record_user(uint16_t keycode, keyrecord_t *record){
    switch(keycode){
        case HMDIR:
            if(record->event.pressed) SEND_STRING("~/");
            break;
        case LROTATE:
            if(record->event.pressed){
                bfl = (bfl + 1) % nbls;
                if(bfl == L_BASE_CODY){
                    layer_on(bfl);
                    layer_off(L_BASE_GAMING);
                    layer_off(L_BASE_STDISH);
                }else if(bfl == L_BASE_GAMING){
                    layer_on(bfl);
                    layer_off(L_BASE_CODY);
                    layer_off(L_BASE_STDISH);
                }else if(bfl == L_BASE_STDISH){
                    layer_on(bfl);
                    layer_off(L_BASE_CODY);
                    layer_off(L_BASE_GAMING);
                }
            }
            break;
        case LPRINT:
            if(record->event.pressed){
                if(bfl == L_BASE_CODY)
                    SEND_STRING("#baselayer: cody-qgmlwy\n");
                else if(bfl == L_BASE_GAMING)
                    SEND_STRING("#baselayer: gaming-qgmlwy\n");
                else if(bfl == L_BASE_STDISH)
                    SEND_STRING("#baselayer: standardish-qwerty\n");
            }
            break;
    }
    return true;
}

enum unicode_names {
    FLAT, NAT, SHARP, MAJOR, DIM, HALF, SIX, SEVEN, NINE,
};

const uint32_t PROGMEM unicode_map[] = {
    [FLAT] = 0x266D,  // ♭
    [NAT]  = 0x266E,  // ♮
    [SHARP]  = 0x266F, // ♯
    [MAJOR] = 0x2206, // ∆
    [DIM] = 0x00B0, // °
    [HALF] = 0x00F8, // ø
    [SIX] = 0x2076, // ⁶
    [SEVEN] = 0x2077, // ⁷
    [NINE] = 0x2079, // ⁹
};

enum layer_names {
    _BASE,
    _GAMING,
    _STANDARDISH,
    _FN,
    _MOUSE,
    _L_EXTRA,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_all( /* QGMLWY base layer */
    KC_BSLS,                    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_GRAVE,KC_F13,
    LT(L_MOUSE, KC_TAB),        KC_Q,    KC_G,    KC_M,    KC_L,    KC_W,    KC_Y,    KC_F,    KC_U,    KC_B,    KC_SCLN, KC_LBRC, KC_RBRC,          KC_BSPC,
    KC_LGUI,                    KC_D,    KC_S,    KC_T,    KC_N,    KC_R,    KC_I,    KC_A,    KC_E,    KC_O,    KC_H,    KC_QUOT,                   HMDIR,
    MT(MOD_LCTL, KC_ESC),       _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_J,    KC_K,    KC_P,    KC_COMM, KC_DOT,  KC_SLSH,          KC_CAPS, LROTATE,
    MO(L_EXTRA),                KC_LGUI, KC_LALT,          KC_LSFT,          LT(L_FN, KC_ENT), KC_SPC,                    KC_RALT, KC_ENT,  KC_APP,  KC_RCTL
  ),
  [_GAMING] = LAYOUT_all( /* QGMLWY with base mods on the left */
    KC_ESC,                     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL, KC_GRAVE, KC_F13,
    KC_TAB,                     KC_Q,    KC_G,    KC_M,    KC_L,    KC_W,    KC_Y,    KC_F,    KC_U,    KC_B,    KC_SCLN, KC_LBRC, KC_RBRC,          KC_BSPC,
    KC_LGUI,                    KC_D,    KC_S,    KC_T,    KC_N,    KC_R,    KC_I,    KC_A,    KC_E,    KC_O,    KC_H,    KC_QUOT,                   HMDIR,
    KC_LSFT,                    _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_J,    KC_K,    KC_P,    KC_COMM, KC_DOT,  KC_SLSH,          KC_CAPS, LROTATE,
    KC_LCTL,                    KC_LGUI, KC_LALT,          KC_SPC,           LT(L_FN, KC_ENT), KC_SPC,                    KC_RALT, KC_ENT,  KC_APP,  KC_RCTL
  ),
  [_STANDARDISH] = LAYOUT_all( /* Standardish */
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_BSPC,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,                   KC_ENT,
    KC_LSFT, KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, LROTATE,
    KC_LCTL, KC_LGUI, KC_LALT,          KC_SPC,           MO(L_FN),         KC_SPC,                    KC_RALT, KC_RGUI, KC_APP,  KC_RCTL
  ),
  [_FN] = LAYOUT_all( /* FN */
    RESET,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,
    _______, _______, _______, KC_PGUP, _______, _______, _______, KC_BSPC, KC_UP,   KC_DEL,  _______, _______, _______,          _______,
    _______, _______, KC_HOME, KC_PGDN, KC_END,  _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,                   KC_DEL,
    KC_LSFT, _______, _______, DM_RSTP, DM_REC1, DM_PLY1, DM_REC2, DM_PLY2, KC_ESC,  _______, _______, _______,          _______, LPRINT,
    _______, _______, _______,          KC_ESC,           _______,          KC_ENT,                    _______, _______, _______, _______
  ),
  [_MOUSE] = LAYOUT_all( /* Mouse */
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______, _______, KC_BTN1, KC_MS_U, KC_BTN2, _______, _______, _______,          _______,
    _______, _______, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,                   _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
    _______, _______, _______,          _______,          _______,          _______,                   _______, _______, _______, _______
  ),
  [_L_EXTRA] = LAYOUT_all( /* Extra */
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, X(MAJOR),X(HALF), X(DIM),  _______, _______, _______,          _______,
    _______, _______, _______, _______, _______, _______, _______, X(FLAT), X(NAT),  X(SHARP),_______, _______,                   _______,
    _______, _______, _______, _______, _______, _______, _______, _______, X(SIX),  X(SEVEN),X(NINE), _______,          _______, _______,
    _______, _______, _______,          _______,          _______,          _______,                   _______, _______, _______, _______
  ),
};

