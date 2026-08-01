# Keyboards

QMK keymaps for Aurora Corne, Kyria, and Skeletyl. External userspace with community modules.

## Structure

- `qmk/users/diaoul/` — shared userspace (tap-hold, combos, custom shift, OLED)
- `qmk/keyboards/<vendor>/<board>/keymaps/diaoul/keymap.c` — per-board matrix
- `qmk/modules/getreuer` — getreuer's modules (submodule)
- `qmk/qmk_firmware/` — QMK firmware (submodule, pinned to a release tag; the tag lives in `.gitmodules` as `branch =` so Renovate bumps it)

## Updating

Renovate opens the version-bump PRs. After merging one, run `mise run update` (alias `mise u`) to sync submodules locally.

## Reference keymaps

### getreuer — Pascal Getreuer
- Keymap: https://github.com/getreuer/qmk-keymap
- Modules (submoduled here): https://github.com/getreuer/qmk-modules
- Blog: https://getreuer.info/posts/keyboards/index.html
- Notable: Achordion/chordal hold, custom shift keys, select-word macro, repeat key, exhaustive per-decision documentation

### precondition
- Keymap: https://github.com/precondition/dactyl-manuform-keymap
- Blog: https://precondition.github.io/home-row-mods
- Notable: canonical home row mods guide, per-key tapping term strategies, mod-tap order (GACS vs SCAG), combo design
