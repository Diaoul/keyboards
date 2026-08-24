# Keyboards

QMK keymaps for Aurora Corne, Kyria, and Skeletyl. External userspace with community modules.

## Boards

| Board    | Target                            | MCU        | RGB          | Flash       |
|----------|-----------------------------------|------------|--------------|-------------|
| Corne    | `splitkb/aurora/corne/rev1`       | RP2040     | `rgb_matrix` | roomy       |
| Kyria    | `splitkb/kyria/rev1`              | atmega32u4 | `rgblight`   | constrained |
| Skeletyl | `bastardkb/skeletyl/v2/splinky_3` | RP2040     | `rgb_matrix` | roomy       |

Corne is the daily driver; it has 3 thumbs per side and no encoder. Kyria has 5 thumbs per side plus two encoders — mirror the Corne's layout rather than exploiting the extras, since divergence costs muscle memory when switching.

## Layout

- `qmk/users/diaoul/` — shared userspace (tap-hold, combos, custom shift, OLED). Behaviour belongs here.
- `qmk/keyboards/<vendor>/<board>/keymaps/diaoul/` — matrix and board-specific hardware only (OLED art, encoders)
- `qmk/modules/getreuer` — getreuer's modules (submodule)
- `qmk/qmk_firmware/` — QMK firmware (submodule, pinned to a release tag; the tag lives in `.gitmodules` as `branch =` so Renovate bumps it)

## Build

`~/.config/qmk/qmk.ini` sets `qmk_home`, `overlay_dir`, and the default keymap, so `qmk` works from any directory with no env setup. Build targets are listed in `qmk/qmk.json`.

```bash
qmk compile -kb <target> -km diaoul
```

**Compile all three boards after any change under `qmk/users/diaoul/`.** They do not share a platform, and a change that is free on RP2040 can overflow the Kyria.

Flashing needs physical access and bootloader entry — that is the user's job. An agent's work ends at a verified compile; hand over the command rather than attempting it.

## Traps

**Kyria flash ceiling.** AVR, and the build sits near the limit. Size-check every shared change there; the compile output reports the exact figure. `kyria_logo` in its `keymap.c` is a slave-only bitmap worth roughly a kilobyte — the intended reclaim. A routine Renovate QMK bump can break this build for reasons unrelated to the PR.

**RGB defines are subsystem-specific.** `RGBLIGHT_*` silently does nothing on `rgb_matrix` boards and vice versa. `RGBLIGHT_SLEEP` sits in the shared config and has no effect on Corne or Skeletyl. RGBLIGHT also has no idle-timeout option; `RGB_MATRIX_TIMEOUT` exists (default `0`, disabled).

**OS detection was tried and rejected.** `OS_DETECTION_ENABLE` plus a `CG_SWAP` callback worked but detected unreliably in practice. macOS Ctrl/GUI remapping is handled by Karabiner on the host instead. Do not reintroduce it.

**Splits: flash both halves** whenever transport config changes (baud, timeout, transport options). A mismatch presents as one dark half with no keys or OLED — indistinguishable from a hardware fault.

**Check the pinned source, not docs.qmk.fm.** The public docs track master and describe features generically; this repo pins a tag and the driver in use may differ. Example: the serial docs require an external pull-up resistor, which is false for the RP2040 `vendor` PIO driver used here — it enables the MCU-internal one.

## Tap-hold is load-bearing

`get_quick_tap_term` in `users/diaoul/diaoul.c` returns `0` for mod-taps and layer-taps, inverted from QMK's documented example. This is deliberate and mirrors getreuer's own keymap: holding a tap-hold key right after tapping it repeats the tap, which costs mod triggers during fast typing. `QK_REP` on the left thumb covers repetition instead, and plain keycodes on layers (e.g. `KC_BSPC` on NAV) still auto-repeat natively.

**Flow Tap does not supersede this.** They cover different windows — Flow Tap fires when a key follows the previous one within `FLOW_TAP_TERM` and short-circuits before quick tap is consulted; quick tap only decides after a pause. getreuer runs both together. Other tap-hold types fall through to `QUICK_TAP_TERM` on purpose: `TT()` and the one-shot tap toggle need it to toggle at all.

Do not "fix" this wholesale. Same for `CHORDAL_HOLD`, `FLOW_TAP_TERM`, `SPECULATIVE_HOLD` and the per-key `TAPPING_TERM` overrides — all tuned against real misfire complaints.

## Updating

Renovate opens the version-bump PRs. After merging one, run `mise run update` (alias `mise u`) to sync submodules locally.

## Reference keymaps

### getreuer — Pascal Getreuer
- Keymap: https://github.com/getreuer/qmk-keymap
- Modules (submoduled here): https://github.com/getreuer/qmk-modules
- Blog: https://getreuer.info/posts/keyboards/index.html
- FAQs (HRM tips, quick tap rationale): https://getreuer.info/posts/keyboards/faqs/index.html
- Notable: Achordion/chordal hold, custom shift keys, select-word macro, repeat key, exhaustive per-decision documentation

### precondition
- Keymap: https://github.com/precondition/dactyl-manuform-keymap
- Blog: https://precondition.github.io/home-row-mods
- Notable: canonical home row mods guide, per-key tapping term strategies, mod-tap order (GACS vs SCAG), combo design
