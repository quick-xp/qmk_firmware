// quick-xp keymap for ErgoDox EZ
// 2017 年の quick-xp/qmk_firmware (dev ブランチ, 1e7f348 "wheel") を最新 QMK に移植したもの。
// 置き場所: keyboards/ergodox_ez/keymaps/quick-xp/keymap.c
// ビルド:   qmk compile -kb ergodox_ez/base -km quick-xp
#include QMK_KEYBOARD_H

// Alias
#define K_EISU KC_LNG2 // 英数
#define K_KANA KC_LNG1 // かな
#define TAB_NXT C(KC_TAB)    // 次のタブ
#define TAB_PRV C(S(KC_TAB)) // 前のタブ

// Layers
// 旧版はレイヤー番号が 1 始まりで、空のレイヤー 0 の上に COMMON を載せていた。
// 動きは同じまま 0 始まりに詰めた。
enum layers {
    L_COMMON, // default
    L_NAV,    // mouse and cursor
    L_CONFIG, // config mode
};

// 自作キー
enum custom_keycodes {
    MSTR_AA1 = SAFE_RANGE,  // Maestri: Cmd を 2 回たたいてから 1
    MSTR_AA2,               // Maestri: Cmd を 2 回たたいてから 2
    MSTR_AA3,               // Maestri: Cmd を 2 回たたいてから 3
};
// 右親指の Cmd+1/2/3 はふつうの同時押しなので、自作キーでなく G(KC_n) を使う

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | ESC    |   1! |  2@  |   3# |   4$ |   5% |  6^  |           |   7& |   8* |  9(  |  0)  |  -_  |   +  |  BS    |
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
 *                                        |Cm2→1 |Cm2→2 |       |Cmd+1 | Cmd+2  |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |Cm2→3 |       |Cmd+3 |        |      |
 *                                 |Space | EISU |------|       |------|  KANA  | Space|
 *                                 |      |      | DEL  |       | BS   |        | /NAV |
 *                                 `--------------------'       `----------------------'
 */
[L_COMMON] = LAYOUT_ergodox(
  // left hand
  KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,    KC_6,
  KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,    K_EISU,
  KC_LCTL,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,
  KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,    KC_QUOT,
  KC_CAPS,    KC_LALT,    KC_LGUI,    KC_GRV,     KC_LBRC,

              MSTR_AA1,   MSTR_AA2,
                          MSTR_AA3,
  KC_SPC,     K_EISU,     KC_DEL,

  // right hand
  KC_7,       KC_8,       KC_9,       KC_0,       KC_MINUS,   KC_PLUS,    KC_BSPC,
  K_KANA,     KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_BSLS,
              KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_ENT,
  KC_EQL,     KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_MINUS,
                          KC_RBRC,    KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,

  G(KC_1),    G(KC_2),
  G(KC_3),
  KC_BSPC,    K_KANA,     LT(L_NAV, KC_SPC)
),

/* Keymap: Cursor, Mouse Layer (右親指の Space を押している間)
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F11 |           | F12  |  F6  |  F7  |  F8  |  F9  |  F10 | ->CNF  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        | PREV | M_U  | NEXT | MW_U |  <   |      |           |  >   | Home | PgUp | End  | PgDn |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   CTRL | M_L  | M_D  | M_R  | MW_D |      |------|           |------| Left | Down | Up   | Right|   :  | Accel0 |
 * |--------+------+------+------+------+------|      |           |  /   |------+------+------+------+------+--------|
 * |        |   !  |   @  |   #  |   $  |   %  |      |           |      |   :  |   "  |   *  |   (  |   )  | Accel0 |
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
 * PREV / NEXT = Ctrl+Shift+Tab / Ctrl+Tab (タブ切り替え)
 */
[L_NAV] = LAYOUT_ergodox(
  // left hand
  _______,    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F11,
  _______,    TAB_PRV,    MS_UP,      TAB_NXT,    MS_WHLU,    KC_LT,      _______,
  KC_LCTL,    MS_LEFT,    MS_DOWN,    MS_RGHT,    MS_WHLD,    _______,
  _______,    KC_EXLM,    KC_AT,      KC_HASH,    KC_DLR,     KC_PERC,    _______,
  _______,    _______,    _______,    _______,    MS_BTN3,

              _______,    _______,
                          _______,
  MS_BTN1,    MS_BTN2,    _______,

  // right hand
  KC_F12,     KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     MO(L_CONFIG),
  KC_GT,      KC_HOME,    KC_PGUP,    KC_END,     KC_PGDN,    _______,    _______,
              KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,   KC_COLN,    MS_ACL0,
  KC_SLSH,    S(KC_SCLN), S(KC_QUOT), KC_ASTR,    KC_LPRN,    KC_RPRN,    MS_ACL0,
                          _______,    _______,    _______,    _______,    _______,

  _______,    _______,
  _______,
  _______,    _______,    _______
),

/* Keymap: CONF (NAV で右上端を押している間)
 *
 * ,--------------------------------------------------.
 * |  BOOT  |      |      |      |      |      |      |   BOOT = ファームウェア書き込みモードに入る
 * `--------------------------------------------------'   ほかはすべて透過
 */
[L_CONFIG] = LAYOUT_ergodox(
  // left hand
  QK_BOOT,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,

              _______,    _______,
                          _______,
  _______,    _______,    _______,

  // right hand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
              _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
                          _______,    _______,    _______,    _______,    _______,

  _______,    _______,
  _______,
  _______,    _______,    _______
),
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MSTR_AA1:
        case MSTR_AA2:
        case MSTR_AA3:
            if (record->event.pressed) {
                // Cmd を 2 回たたく。速すぎると Mac が 2 回と数えないので、少し間をあける
                SEND_STRING(SS_TAP(X_LGUI) SS_DELAY(50) SS_TAP(X_LGUI) SS_DELAY(100));
                tap_code(KC_1 + (keycode - MSTR_AA1)); // KC_1, KC_2, KC_3 は連番
            }
            return false;
    }
    return true;
}

// レイヤーに合わせて右手側の LED を点ける (旧版と同じ点き方)
//   COMMON: LED1, NAV: LED2, CONFIG: LED1 + LED2
layer_state_t layer_state_set_user(layer_state_t state) {
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    switch (get_highest_layer(state)) {
        case L_COMMON:
            ergodox_right_led_1_on();
            break;
        case L_NAV:
            ergodox_right_led_2_on();
            break;
        case L_CONFIG:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            break;
        default:
            break;
    }
    return state;
}

// 起動直後は layer_state_set_user が呼ばれないので、COMMON の LED をここで点ける
void keyboard_post_init_user(void) {
    layer_state_set_user(layer_state);
}
