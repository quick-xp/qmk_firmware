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

// ----消す
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
// -----

//Layers
#define L_QUERTY 0 //default
#define L_NAVI 1 // mouse and cursor
#define L_SYMB 2 // symbols
#define L_CONFIG 3 // config mode

uint16_t hold_timers[MATRIX_ROWS][MATRIX_COLS];

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | ESC    |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  | PSCR   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |   <  |           |  >   |   Y  |   U  |   I  |   O  |  P   | CAPS   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | '"     |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |      | -_     |
 * |--------+------+------+------+------+------|  Tab |           |  =+  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |      | +      |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LGUI |      |  \|  |  `~  | [{ /S|                                       | ]} /S|  BS  |  DEL |      | +    |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        |      |      |       |      |        |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | LNAV |       |      |        |      |
 *                                 |      | EISU |------|       |------| KANA   | Enter|
 *                                 |      | /LAlt| ESC  |       | ESC  | /RCtrl | /NAV |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[L_COMMON] = KEYMAP(  // layer 0 : default
  // left hand
  KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       _______,
  KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,         KC_LT,
  KC_QUOT,    _______,    _______,    _______,    _______,    _______,
  KC_LSFT,    _______,    _______,    _______,    _______,    _______,    KC_TAB,
  KC_LGUI,    _______,    KC_BSLS,    KC_GRV,     SFT_T(KC_LBRC),

              _______,    _______,
                          TG(L_LNAV),
  _______,    CK_A_EN,    KC_ESC,


  //righthand
  _______,    KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_PSCR,
  KC_GT,      KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,    KC_CAPS,
              KC_H,       KC_J,       KC_K,       KC_L,       _______,    KC_MINS,
  KC_EQL,     _______,    _______,    _______,    _______,    _______,    KC_PLUS,
                          SFT_T(KC_RBRC),    KC_BSPC,    KC_DEL,     _______,    KC_KP_PLUS,

  _______,    _______,
  _______,
  KC_ESC,     CK_C_JA,    LT(L_NAV,KC_ENT)
),

/* Keymap : QWERTY
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 */
[L_QWERTY] = KEYMAP(
  // left hand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       _______,
  _______,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,
  _______,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,

  //righthand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       _______,
              KC_H,       KC_J,       KC_K,       KC_L,              ,    _______,
  _______,    KC_N,       KC_M,       _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______
),

/* Keymap: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   #  |   $  |   %  |  <   |           |   >  |   ^  |   &  |   *  |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   <    |   1! |   2@ |   3# |   4$ |   5% |------|           |------|   6^ |   7& |   8* |   9( |   0) |   >    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 */
[L_SYMB] = KEYMAP(
    // left hand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    KC_EXLM,    KC_AT,      KC_HASH,    KC_DLR,     KC_PERC,    KC_LT,
  KC_LT,      KC_1,       KC_2,       KC_3,       KC_4,       KC_5,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,

  //righthand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  KC_GT,      KC_CIRC,    KC_AMPR,    KC_ASTR,    _______,    _______,    _______,
              KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_GT,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______
),


/* Keymap: Cursor, Mouse Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F11 |           | F12  |  F6  |  F7  |  F8  |  F9  |  F10 | ->CNF  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      | PREV | M_U  | NEXT | MW_U |  <   |           |  >   | Home | PgUp |  Up  | PgDn |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   (    |   ?  | M_L  | M_D  | M_R  | MW_D |------|           |------| End  | Left | Down | Right|   :  |   )    |
 * |--------+------+------+------+------+------|      |           |  /   |------+------+------+------+------+--------|
 * |        |   !  |   @  |   #  |   $  |   %  |      |           |      |   ^  |   &  |   *  |   (  |   )  |        |
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
  _______,    _______,    KC_PREV,    KC_M_U,     KC_NEXT,    KC_M_WU,    KC_LT,
  KC_LPRN,    KC_QUES,    KC_M_L,     KC_M_D,     KC_M_R,     KC_M_WD,
  _______,    KC_EXLM,    KC_AT,      KC_HASH,    KC_DLR,     KC_PERC,    _______,
  _______,    _______,    _______,    _______,    KC_M_B3,

              _______,    _______,
                          _______,
  KC_M_B1,    KC_M_B2,    _______,

  //righthand
  KC_F12,     KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     MO(L_CONF),
  KC_GT,      KC_HOME,    KC_PGUP,    KC_UP,      KC_PGDN,    _______,    _______,
              KC_END,     KC_LEFT,    KC_DOWN,    KC_RIGHT,   KC_COLN,    KC_M_A0,
  KC_SLSH,    KC_CIRC,    KC_AMPR,    KC_ASTR,    KC_LPRN,    KC_RPRN,    KC_M_A0,
                          _______,    _______,    _______,    _______,    _______,

  _______,    _______,
  _______,
  _______,    _______,    _______
),

/* Keymap: Cursor, Mouse Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      | PgUp |  Up  | PgDn | Home |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      | Left | Down | Right| End  |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | MBtn1  |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      | BS   |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 | LNAV2|      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[L_LNAV] = KEYMAP(
    // left hand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    KC_PGUP,    KC_UP,      KC_PGDN,    KC_HOME,    _______,
  _______,    _______,    KC_LEFT,    KC_DOWN,    KC_RIGHT,   KC_END,
  KC_M_B1,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    KC_BSPC,

              _______,    _______,
                          _______,
  CK_LNAV2,   _______,    _______,

  //righthand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
              _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
                          _______,    _______,    _______,    _______,    _______,

  _______,    _______,
  _______,
  _______,    _______,    _______
),

/* Keymap: Cursor, Mouse Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      | PREV | M_U  | NEXT | MH_U | MBtn3|           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      | M_L  | M_D  | M_R  | MH_D |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------| MBtn2|           |      |------+------+------+------+------+--------|
 * | MBtn1  |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
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
[L_LNAV2] = KEYMAP(
    // left hand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    KC_PREV,    KC_M_U,     KC_NEXT,    KC_M_WU,    KC_M_B3,
  _______,    _______,    KC_M_L,     KC_M_D,     KC_M_R,     KC_M_WD,
  KC_M_B1,    _______,    _______,    _______,    _______,    _______,    KC_M_B2,
  _______,    _______,    _______,    _______,    _______,

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
),

/* Keymap: CONF
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  RESET | Mac  | Win  |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  QWRT  |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  QWDR  |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  game  |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
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
[L_CONF] = KEYMAP(
  // left hand
  RESET,      CK_MAC,     CK_WIN,        _______,    _______,    _______,    _______,
  TO(L_QWDR),       _______,    _______,    _______,    _______,    _______,    _______,
  TO(L_QWERTY),     _______,    _______,    _______,    _______,    _______,
  CK_GAME,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,

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

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void switch_layer (uint8_t layer, bool on) {
  if (on) {
    layer_on(layer);
  } else {
    layer_off(layer);
  }
};

void type_code(uint8_t keycode){
  register_code (keycode);
  unregister_code (keycode);
};

void set_eisu(void){
  type_code (KC_MHEN);
  type_code (KC_LANG2);
};

void set_kana(void){
  type_code (KC_HENK);
  type_code (KC_LANG1);
};

bool is_tap (keyrecord_t *record) {
  return hold_timers[record->event.key.row][record->event.key.col]
  && timer_elapsed (hold_timers[record->event.key.row][record->event.key.col]) < TAPPING_TERM;
}

void mod_tap_action(keyrecord_t *record, uint8_t mod, void (*cb)(void) ) {
  if (record->event.pressed) {
    add_mods(MOD_BIT(mod));
  } else {
    if (is_tap(record)) {
      del_mods(MOD_BIT(mod));
      cb();
    } else {
      unregister_code(mod);
    }
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // record pressed timer
  if (record->event.pressed) {
    hold_timers[record->event.key.row][record->event.key.col] = timer_read();
  }

  switch (keycode) {
    //--layers--

    //layout
    case CK_GAME:
      if (record->event.pressed) {
        layer_move(L_QWERTY);
        layer_on(L_GAME);
      }
      return false;
      break;

    case CK_LNAV2:
      if (record->event.pressed) {
        layer_on(L_LNAV2);
      } else {
        layer_off(L_LNAV2);
        if (is_tap(record)) {
          mousekey_on(KC_M_B1);
          mousekey_send();
          mousekey_off(KC_M_B1);
          mousekey_send();
        }
      }
      return false;
      break;

    //os
    case CK_MAC:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<L_MAC);
      }
      return false;
      break;
    case CK_WIN:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<L_WIN);
      }
      return false;
      break;

    // langs
    case CK_A_EN:
      mod_tap_action(record, KC_LALT, set_eisu);
      return false;
      break;
    case CK_C_JA:
      mod_tap_action(record, KC_RCTL, set_kana);
      return false;
      break;

    // Ctrl-Q -> Alt-F4
    case KC_Q:
      if (
        record->event.pressed
        && (get_mods() & MOD_CTLS)
      ) {
        clear_keyboard();
        add_mods(MOD_BIT(KC_LALT));
        type_code(KC_F4);
        del_mods(MOD_BIT(KC_LALT));
        return false;
      }
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  persistant_default_layer_set(1UL<<L_MAC);
  layer_move(L_QWDR);
};
