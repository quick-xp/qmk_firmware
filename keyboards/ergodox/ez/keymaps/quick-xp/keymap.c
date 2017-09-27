// Netable differences vs. the default firmware for the ErgoDox EZ:
// 1. The Cmd key is now on the right side, making Cmd+Space easier.
// 2. The media keys work on MAC (But not on Windows).
#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "mousekey.h"

//Alias
#define K_EISU KC_LANG2
#define K_KANA KC_LANG1
#define _______ KC_TRNS // 仮想レイヤーのキー引き継ぎ
#define XXXXXXX KC_NO // 何もしない

#define C(kc) LCTL(kc)
#define A(kc) LALT(kc)
#define SC(kc) (S(C(kc)))
#define SA(kc) (S(A(kc)))
#define KC_M_WU KC_MS_WH_UP
#define KC_M_WD KC_MS_WH_DOWN
#define KC_M_WL KC_MS_WH_LEFT
#define KC_M_WR KC_MS_WH_RIGHT
#define KC_M_U KC_MS_U
#define KC_M_D KC_MS_D
#define KC_M_L KC_MS_L
#define KC_M_R KC_MS_R
#define KC_M_A0 KC_MS_ACCEL0
#define KC_M_A1 KC_MS_ACCEL1
#define KC_M_A2 KC_MS_ACCEL2
#define KC_M_B1 KC_MS_BTN1
#define KC_M_B2 KC_MS_BTN2
#define KC_M_B3 KC_MS_BTN3
#define KC_NEXT C(KC_TAB)
#define KC_PREV SC(KC_TAB)
#define MOD_CTLS (MOD_BIT(KC_LCTRL) | MOD_BIT(KC_RCTRL))
//Layers
#define L_COMMON 1 //default
#define L_NAV 2 // mouse and cursor
#define L_SYMB 3 // symbols
#define L_CONFIG 4 // config mode

uint16_t hold_timers[MATRIX_ROWS][MATRIX_COLS];

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | ESC    |   1! |  2@  |   3# |   4$ |   5% |  6^  |           |   7& |   8* |  9(  |  0)  |  -_  |  +=  |  BS    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  | EISU |           | KANA |   Y  |   U  |   I  |   O  |  P   |  |\    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Ctrl   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |  ;:  |  ENTER |
 * |--------+------+------+------+------+------|  "'  |           |  =+  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |  /?  |  -_    |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Caps |  Alt |  Cmd |  `~  | [{   |                                       | ]}   |  ←   |  ↓   |  ↑   |  →    |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        |      |      |       |      |        |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 |Space | EISU |------|       |------|  KANA  | Space|
 *                                 |      |      | DEL  |       | BS   |        | /NAV |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[L_COMMON] = KEYMAP(  // layer 0 : default
  // left hand
  KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,    KC_6,
  KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,    K_EISU,
  KC_LCTRL,   KC_A,       KC_S,       KC_D,       KC_F,       KC_G,
  KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,    KC_QUOT,
  KC_CAPS,    KC_LALT,    KC_LGUI,    KC_GRV,     KC_LBRC,

              _______,    _______,
                          _______,
  KC_SPC,      K_EISU,    KC_DEL,


  //righthand
     KC_7,    KC_8,       KC_9,       KC_0,       KC_MINUS,   KC_PLUS,    KC_BSPC,
   K_KANA,    KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_BSLS,
              KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_ENT,
  KC_EQL,     KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_MINUS,
                          KC_RBRC,    KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,

  _______,    _______,
  _______,
  KC_BSPC,    K_KANA,    LT(L_NAV,KC_SPC)
),

/* Keymap: Cursor, Mouse Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F11 |           | F12  |  F6  |  F7  |  F8  |  F9  |  F10 | ->CNF  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        | PREV | M_U  | NEXT | MW_U |  <   |      |           |  >   | Home | PgUp |  End  | PgDn |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   CTRL | M_L  | M_D  | M_R  | MW_D |      |------|           |------| Left | Down | Up   | Right|   :  |   )    |
 * |--------+------+------+------+------+------|      |           |  /   |------+------+------+------+------+--------|
 * |        |   !  |   @  |   #  |   $  |   %  |      |           |      |   :  |   "  |   *  |   (  |   )  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      | MBtn3|                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 | MBtn1| MBtn2|------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[L_NAV] = KEYMAP(
  // left hand
  _______,    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F11,
  _______,    KC_PREV,    KC_M_U,     KC_NEXT,    KC_M_WU,    KC_LT,       _______,
  KC_LCTRL,   KC_M_L,     KC_M_D,     KC_M_R,     KC_M_WD,    _______,
  _______,    KC_EXLM,    KC_AT,      KC_HASH,    KC_DLR,     KC_PERC,    _______,
  _______,    _______,    _______,    _______,    KC_M_B3,

              _______,    _______,
                          _______,
  KC_M_B1,    KC_M_B2,    _______,

  //righthand
  KC_F12,     KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     MO(L_CONFIG),
  KC_GT,      KC_HOME,    KC_PGUP,    KC_END,      KC_PGDN,    _______,    _______,
              KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,   KC_COLN,    KC_M_A0,
  KC_SLSH,    S(KC_SCLN), S(KC_QUOT), KC_ASTR,    KC_LPRN,    KC_RPRN,    KC_M_A0,
                          _______,    _______,    _______,    _______,    _______,

  _______,    _______,
  _______,
  _______,    _______,    _______
),

/* Keymap: CONF
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  RESET |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  COMMON|      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[L_CONFIG] = KEYMAP(
  // left hand
  RESET,         _______,   _______,    _______,    _______,    _______,    _______,
  TG(L_COMMON),  _______,   _______,    _______,    _______,    _______,    _______,
  _______,      _______,    _______,    _______,    _______,    _______,
  _______,      _______,    _______,    _______,    _______,    _______,    _______,
  _______,      _______,    _______,    _______,    _______,

              _______,    _______,
                          _______,
  _______,    _______,    _______,

  //righthand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
              _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
                          _______,    _______,    _______,    _______,    _______,

  _______,    _______,
  _______,
  _______,    _______,    _______
)

};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  layer_move(L_COMMON);
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case L_COMMON:
            // Binary 1 represented by the leds
            // --*
            ergodox_right_led_1_on();
            break;
        case L_NAV:
            // Binary 2 represented by the leds
            // -*-
            ergodox_right_led_2_on();
            break;
        case L_CONFIG:
            // Binary 3 represented by the leds
            // -**
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }
};


