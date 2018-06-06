#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"

#define BASE 0 // default layer
#define NUMB 1 // numbers
#define MDIA 2 // media keys

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_* 
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_GRV,         KC_EXLM,    KC_AT,   KC_HASH,    KC_DLR,   KC_PERC,   LGUI(KC_R),
        KC_TAB,  KC_QUOT, KC_COMM,KC_DOT,  KC_P,   KC_Y,   KC_NO,
        ALL_T(KC_NO),   KC_A,    KC_O,   KC_E,    KC_U,   KC_I,
        KC_RGHT,        KC_SCLN, KC_Q,   KC_J,    KC_K,   KC_X,   LSFT(KC_ENT),
        KC_LEFT,       KC_LCTL, KC_LALT,  KC_LGUI,   KC_ESC,
                                                            LGUI(KC_C),  LGUI(KC_V),
                                                                      KC_NO,
                                                 KC_LSFT,KC_ENT,LGUI(KC_SPC),
        // right hand
        LGUI(KC_LEFT),    KC_CIRC,   KC_AMPR,   KC_ASTR,  KC_NO,   LSFT(KC_BSLS), LGUI(KC_RGHT),
        LGUI(KC_RCBR),    KC_F,   KC_G,   KC_C,   KC_R,   KC_L, KC_EQL,
                          KC_D,   KC_H,   KC_T,   KC_N,   KC_S, KC_MINS,
        LGUI(KC_LCBR),    KC_B,   KC_M,   KC_W,   KC_V,   KC_Z, KC_UP,
                            MO(MDIA),KC_DEL,KC_BSPC, LSFT(KC_SLSH),KC_DOWN,
        KC_NO,KC_NO,
        KC_NO,
        KC_NO,KC_SPC,MO(NUMB)
    ),
// NUMBERS
[NUMB] = KEYMAP(
       // left hand
       KC_TRNS,KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
       KC_TRNS,KC_TRNS,KC_COMM,KC_DOT,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_1,KC_2, KC_3,KC_4,KC_5,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_SPC,
       // right hand
       KC_F12, KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,
       KC_TRNS, KC_TRNS,   KC_LPRN,   KC_RPRN,    KC_LBRC,    KC_RBRC, KC_EQL,
                KC_6, KC_7,   KC_8,    KC_9,    KC_0, KC_MINS,
       KC_TRNS, KC_TRNS, KC_LCBR, KC_RCBR,KC_SLSH,   KC_BSLS,    KC_TRNS,
                         KC_TRNS,   KC_TRNS,  KC_TRNS,    KC_TRNS,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
// MEDIA, MOUSE, F KEYS
[MDIA] = KEYMAP(
       KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLU, KC_TRNS,
       KC_TRNS, KC_MS_L, KC_MS_R, KC_MS_D, KC_MS_U, KC_VOLD,
       KC_TRNS, KC_TRNS, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_BTN1, KC_BTN2, KC_TRNS,
    // right hand
       KC_TRNS,  KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F12,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
    ),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(NUMB)                // FN1 - Momentary Layer 1 (Numbers)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          register_code(KC_RSFT);
        } else {
          unregister_code(KC_RSFT);
        }
        break;
      }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case NUMB:
            ergodox_right_led_1_on();
            break;
        case MDIA:
            ergodox_right_led_3_on();
            break;
    }
};
