# ⌨️ Keyboards

My [QMK](https://qmk.fm/) keymaps and configurations leveraging [external userspace](https://docs.qmk.fm/newbs_external_userspace).

## Installation

1. Enable direnv `direnv allow`

## Design goals

Ergonomics and programming!
I optimize for English typing with COLEMAK layout and programming (with Neovim) through easy access to frequently used characters.

## Features

- Colemak DH although might consider [alternatives](https://cyanophage.github.io/) like Sturdy or Engram at some point
- [Home row mods](https://precondition.github.io/home-row-mods) using ASGC for easier tiling window manager shortcuts
- Space on left thumb with backspace on the opposite side
- One-Shot shift and [Caps Word](https://docs.qmk.fm/features/caps_word)
- Optimized symbol and navigation layers

## Firmware size

If firmware size is an issue, some [QMK features](https://docs.qmk.fm/#/config_options?id=feature-options) can be disabled:

- [`MAGIC_ENABLE`](https://docs.qmk.fm/#/keycodes_magic)
- [`GRAVE_ESC_ENABLE`](https://docs.qmk.fm/#/feature_grave_esc)
- [`MOUSEKEY_ENABLE`](https://docs.qmk.fm/#/feature_mouse_keys)
- [`SPACE_CADET_ENABLE`](https://docs.qmk.fm/#/feature_space_cadet)

## Flashing

```
qmk flash -kb splitkb/kyria/rev1 -km diaoul
```

Add `:dfu-split-left` or `:dfu-split-right` to the latter to also flash EEPROM for the [`EE_HANDS`](https://docs.qmk.fm/#/feature_split_keyboard?id=handedness-by-eeprom) feature.

## Vizualization

Keymap vizualizations are generated by [keymap-drawer](https://github.com/caksoylar/keymap-drawer)
