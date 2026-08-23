# Firmware size optimizations (see https://docs.qmk.fm/squeezing_avr)
LTO_ENABLE = yes
# CONSOLE_ENABLE = no
# COMMAND_ENABLE = no
# MOUSEKEY_ENABLE = no
# EXTRAKEY_ENABLE = no
GRAVE_ESC_ENABLE = no
SPACE_CADET_ENABLE = no

# Fix compilation warning for Aurora Corne
EXTRAFLAGS += -flto=auto

# Extra features
MAGIC_ENABLE ?= yes
OS_DETECTION_ENABLE ?= yes
REPEAT_KEY_ENABLE ?= yes
CAPS_WORD_ENABLE ?= yes
KEY_OVERRIDE_ENABLE ?= no
COMBO_ENABLE ?= yes
# AUTOCORRECT_ENABLE ?= yes

ifeq ($(strip $(OLED_ENABLE)), yes)
  SRC += features/oled.c
endif
