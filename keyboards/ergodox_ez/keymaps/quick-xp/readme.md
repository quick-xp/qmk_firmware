# quick-xp keymap for ErgoDox EZ

2017 年に作ったキーマップ（`keyboards/ergodox/ez/keymaps/quick-xp`）を、2026 年 11 月の最新 QMK に移植したものです。
このブランチの QMK 本体は 2017 年のままなので、ここではビルドできません。
`keymap.c` を最新の QMK にコピーしてビルドします。

## 2017 年版からの変更

- 書き方を最新 QMK に合わせた（`LAYOUT_ergodox`、`KC_LNG1` / `KC_LNG2`、`MS_*`、`QK_BOOT` など）。
- CONFIG レイヤーの `TG(L_COMMON)` を外した（押すとキーボードが効かなくなるため）。
- 親指の上側 6 キーに Maestri 用のキーを割り当てた。
  - 左の 3 キー：Cmd を 2 回たたいてから `1`・`2`・`3`
  - 右の 3 キー：`Cmd + 1`・`Cmd + 2`・`Cmd + 3`

## ビルド

最新の QMK を `~/qmk_firmware` に置き、このフォルダを `~/qmk_firmware/keyboards/ergodox_ez/keymaps/quick-xp/` にコピーしてから実行します。

```bash
docker run --rm -v ~/qmk_firmware:/qmk_firmware -w /qmk_firmware ghcr.io/qmk/qmk_cli qmk compile -kb ergodox_ez/base -km quick-xp
```

`~/qmk_firmware/ergodox_ez_base_quick-xp.hex` ができます。

## 書き込み

1. ZSA の Keymapp で「Flash」を選び、`.hex` を選ぶ。
2. 右親指の Space を押したまま右上端のキーを押し、さらに左上端のキー（`QK_BOOT`）を押して書き込みモードにする。

macOS 27 では、Homebrew の `qmk` と `teensy_loader_cli` は動かなかったので、Docker と Keymapp を使っています。
