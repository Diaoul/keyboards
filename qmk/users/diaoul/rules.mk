# Firmware size optimizations (see https://docs.qmk.fm/squeezing_avr)
MAGIC_ENABLE = no
GRAVE_ESC_ENABLE = no
SPACE_CADET_ENABLE = no

# Extra features
REPEAT_KEY_ENABLE ?= yes
CAPS_WORD_ENABLE ?= yes
KEY_OVERRIDE_ENABLE ?= no
CUSTOM_SHIFT_KEYS_ENABLE ?= yes
COMBO_ENABLE ?= yes
ACHORDION_ENABLE ?= yes
# AUTOCORRECT_ENABLE ?= yes

SRC += diaoul.c

ifeq ($(strip $(OLED_ENABLE)), yes)
  SRC += features/oled.c
endif
ifeq ($(strip $(KEY_OVERRIDE_ENABLE)), yes)
  SRC += features/overrides.c
endif
ifeq ($(strip $(CUSTOM_SHIFT_KEYS_ENABLE)), yes)
  SRC += features/getreuer/custom_shift_keys.c features/custom_shift_keys.c
  OPT_DEFS += -DCUSTOM_SHIFT_KEYS_ENABLE
endif
ifeq ($(strip $(COMBO_ENABLE)), yes)
  SRC += features/combos.c
endif
ifeq ($(strip $(ACHORDION_ENABLE)), yes)
  SRC += features/getreuer/achordion.c
  OPT_DEFS += -DACHORDION_ENABLE
endif
