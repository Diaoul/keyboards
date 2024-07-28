# Caps Word (see https://docs.qmk.fm/features/caps_word)
CAPS_WORD_ENABLE = yes

# Configuration
COMBO_ENABLE = no

# Load configuration-specific code
ifeq ($(strip $(COMBO_ENABLE)), yes)
	SRC += combos.c
endif
