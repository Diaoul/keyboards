# Firmware size optimizations (see https://docs.qmk.fm/squeezing_avr)
MAGIC_ENABLE = no
GRAVE_ESC_ENABLE = no
SPACE_CADET_ENABLE = no

# Extra features
REPEAT_KEY_ENABLE = yes
CAPS_WORD_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
COMBO_ENABLE = yes
# AUTOCORRECT_ENABLE = yes

SRC += diaoul.c

ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += features/oled.c
endif
ifeq ($(strip $(KEY_OVERRIDE_ENABLE)), yes)
	SRC += features/overrides.c
endif

INTROSPECTION_KEYMAP_C = features/combos.c
