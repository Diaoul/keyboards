// Copyright 2026 Antoine Bertin (@Diaoul)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "diaoul.c"
#include "version.h"
#include <lib/lib8tion/lib8tion.h>

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE] = LAYOUT_split_3x6_3(
  KC_GRV  , KC_Q , KC_W , KC_F , KC_P   , KC_B    ,                          KC_J    , KC_L    , KC_U    , KC_Y   , KC_QUOT , KC_MINS,
  KC_ESC  , HR_A , HR_R , HR_S , HR_T   , KC_G    ,                          KC_M    , HR_N    , HR_E    , HR_I   , HR_O    , KC_QUES,
  OS_LSFT , KC_Z , KC_X , KC_C , KC_D   , KC_V    ,                          KC_K    , KC_H    , KC_COMM , KC_DOT , KC_SLSH , KC_UNDS,
                                 QK_REP , NUM_TAB , NAV_SPC ,     SYM_BSPC , SYM_ENT , KC_COLN
),

[SYM] = LAYOUT_split_3x6_3(
  KC_GRV  , KC_AT   , KC_LT   , KC_GT   , KC_MINS , KC_PIPE ,                        KC_CIRC , KC_LBRC , KC_RBRC , KC_DLR  , KC_QUOT , _______,
  _______ , KC_EXLM , KC_ASTR , KC_UNDS , KC_EQL  , KC_AMPR ,                        KC_HASH , KC_LPRN , KC_RPRN , KC_SCLN , KC_DQUO , _______,
  _______ , KC_TILD , KC_PLUS , KC_LCBR , KC_RCBR , KC_PERC ,                        _______ , KC_COLN , KC_COMM , KC_DOT  , KC_SLSH , _______,
                                          _______ , KC_BSLS , KC_SPC ,     _______ , _______ , _______
),

[NUM] = LAYOUT_split_3x6_3(
  _______ , _______ , _______ , _______ , _______ , _______ ,                         KC_PERC , KC_7    , KC_8 , KC_9 , KC_COLN  , KC_COMM,
  _______ , KC_LALT , KC_LGUI , KC_LSFT , KC_LCTL , _______ ,                         KC_PLUS , KC_1    , KC_2 , KC_3 , KC_MINUS , KC_DOT ,
  _______ , _______ , _______ , _______ , _______ , _______ ,                         KC_ASTR , KC_4    , KC_5 , KC_6 , KC_SLSH  , _______,
                                          _______ , _______ , _______ ,     KC_BSPC , KC_0    , _______
),

[NAV] = LAYOUT_split_3x6_3(
  _______ , _______ , _______ , _______ , _______ , _______ ,                         RM_TOGG , RM_VALD , RM_VALU , RM_NEXT , RM_HUEU , RM_HUED,
  _______ , KC_LALT , KC_LGUI , KC_LSFT , KC_LCTL , _______ ,                         KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , RM_SATU , RM_SATD,
  _______ , _______ , _______ , _______ , _______ , _______ ,                         KC_HOME , KC_PGDN , KC_PGUP , KC_END  , RM_SPDU , RM_SPDD,
                                          _______ , _______ , _______ ,     KC_BSPC , _______ , _______
),

[FUN] = LAYOUT_split_3x6_3(
  _______ , _______ , _______ , _______ , _______ , _______ ,                         _______ , KC_F7   , KC_F8 , KC_F9 , KC_F10 , _______,
  _______ , KC_LALT , KC_LGUI , KC_LSFT , KC_LCTL , _______ ,                         _______ , KC_F1   , KC_F2 , KC_F3 , KC_F11 , _______,
  _______ , _______ , _______ , _______ , _______ , _______ ,                         _______ , KC_F4   , KC_F5 , KC_F6 , KC_F12 , _______,
                                          _______ , _______ , _______ ,     _______ , _______ , _______
)
};
// clang-format on

void keyboard_pre_init_user(void) {
    // Liatris power LED (https://docs.splitkb.com/product-guides/liatris/power-led), lit while low
    gpio_set_pin_output(24);
    gpio_write_pin_high(24);
}

#ifdef OLED_ENABLE
// rotated 270, so a line is as wide as the panel is tall
#    define OLED_LINE_WIDTH OLED_DISPLAY_HEIGHT

static uint8_t art_shift = 0;

// Drift art sideways, wrapping around, to spread OLED wear
static void update_art_drift(void) {
    static uint32_t timer = 0;
    if (timer_elapsed32(timer) > ART_DRIFT_INTERVAL) {
        timer     = timer_read32();
        art_shift = (art_shift + 1) % OLED_LINE_WIDTH;
    }
}

// Writes the first size bytes of art shifted by art_shift; the masks are in art coordinates and cover the first mask_size bytes
static void render_art(const char *art, uint16_t size, const uint8_t *set, const uint8_t *clear, uint16_t mask_size) {
    for (uint16_t i = 0; i < size; i++) {
        const uint16_t source = i / OLED_LINE_WIDTH * OLED_LINE_WIDTH + (i + art_shift) % OLED_LINE_WIDTH;
        uint8_t        data   = pgm_read_byte(&art[source]);
        if (source < mask_size) {
            data = (data & ~clear[source]) | set[source];
        }
        oled_write_raw_byte(data, i);
    }
}

#    define ART_ROWS (OLED_MATRIX_SIZE / OLED_LINE_WIDTH * 8)
static uint8_t art_set[OLED_MATRIX_SIZE];
static uint8_t art_clear[OLED_MATRIX_SIZE];

// The top rows of the art are sky; a few stars also sit in the line below, above the aurora's rays
#    define SKY_LINES 2
#    define SKY_EFFECT_ROWS (8 * SKY_LINES + 8)

// x wraps like the drifting art does
static bool art_pixel(const char *art, int8_t x, int8_t y) {
    return y >= 0 && y < ART_ROWS && (pgm_read_byte(&art[y / 8 * OLED_LINE_WIDTH + (x + OLED_LINE_WIDTH) % OLED_LINE_WIDTH]) >> (y % 8) & 1);
}

static void mask_pixel(uint8_t *mask, int8_t x, int8_t y) {
    if (y >= 0 && y < ART_ROWS) {
        mask[y / 8 * OLED_LINE_WIDTH + (x + OLED_LINE_WIDTH) % OLED_LINE_WIDTH] |= 1 << (y % 8);
    }
}

typedef struct {
    int8_t   x;
    int8_t   y;
    bool     plus; // drawn as a plus in the art rather than a dot
    bool     cross; // a dot that grows diagonally, so dots differ from one another
    uint8_t  speed; // in 1/8, so pulses vary in length
    uint16_t offset;
} star_t;

typedef struct {
    star_t  stars[MAX_STARS];
    uint8_t count;
    bool    detected;
} starfield_t;

static uint8_t art_neighbours(const char *art, int8_t x, int8_t y) {
    uint8_t count = 0;
    for (int8_t dy = -1; dy <= 1; dy++) {
        for (int8_t dx = -1; dx <= 1; dx++) {
            count += (dx || dy) && art_pixel(art, x + dx, y + dy);
        }
    }
    return count;
}

static void draw_star_ring(uint8_t *mask, const star_t *star, int8_t r, bool diagonal) {
    mask_pixel(mask, star->x - r, star->y - (diagonal ? r : 0));
    mask_pixel(mask, star->x + r, star->y + (diagonal ? r : 0));
    mask_pixel(mask, star->x - (diagonal ? -r : 0), star->y - r);
    mask_pixel(mask, star->x - (diagonal ? r : 0), star->y + r);
}

// Sizes a star steps through, so a 1-bit pixel can brighten without jumping: dark, dot, small plus or x, longer plus, then detached tips
static void draw_star_size(uint8_t *mask, const star_t *star, uint8_t size) {
    if (size >= 1) {
        mask_pixel(mask, star->x, star->y);
    }
    if (size >= 2) {
        draw_star_ring(mask, star, 1, star->cross);
    }
    if (size >= 3) {
        draw_star_ring(mask, star, 2, false);
    }
    if (size >= 4) {
        draw_star_ring(mask, star, 4, false);
    }
}

static uint8_t star_hash(uint8_t star, uint32_t slot, uint8_t salt) {
    uint32_t h = slot * 0x9E3779B1u ^ (star + 1) * 0x85EBCA77u ^ (salt + 7) * 0xC2B2AE3Du;
    h ^= h >> 15;
    h *= 0x2C1B3C6Du;
    h ^= h >> 12;
    return h >> 24;
}

// Every star pulses on its own clock like FastLED's TwinkleFOX, fast rise and slow fade, in some of its slots, and dips a size in a few others
static void draw_stars(starfield_t *field, const char *art, uint8_t rows) {
    if (!field->detected) {
        field->detected = true;
        // a star is a lone pixel or the centre of a plus
        for (int8_t y = 0; y < rows && field->count < MAX_STARS; y++) {
            for (int8_t x = 0; x < OLED_LINE_WIDTH && field->count < MAX_STARS; x++) {
                if (!art_pixel(art, x, y)) {
                    continue;
                }
                const uint8_t neighbours = art_neighbours(art, x, y);
                const bool    plus       = neighbours == 4 && art_pixel(art, x - 1, y) && art_pixel(art, x + 1, y) && art_pixel(art, x, y - 1) && art_pixel(art, x, y + 1);
                if (neighbours == 0 || plus) {
                    field->stars[field->count++] = (star_t){.x = x, .y = y, .plus = plus, .cross = !plus && (random8() & 1), .speed = random8_min_max(8, STAR_MAX_SPEED + 1), .offset = random16()};
                }
            }
        }
    }

    const uint32_t now = timer_read32();
    for (uint8_t i = 0; i < field->count; i++) {
        const star_t  *star  = &field->stars[i];
        const uint32_t clock = (now * star->speed >> 3) + star->offset;
        const uint32_t slot  = clock / STAR_PULSE;
        const uint8_t  rest  = star->plus ? 2 : 1;
        uint8_t        size  = rest;
        if (star_hash(i, slot, 0) < STAR_DENSITY) {
            const uint8_t phase      = (clock % STAR_PULSE) * 256 / STAR_PULSE;
            const uint8_t brightness = phase < 86 ? phase * 3 : 255 - (phase - 86) - (phase - 86) / 2;
            size                     = rest + (brightness * ((star->plus ? 4 : 2) - rest) + 127) / 255;
        } else if (star_hash(i, slot, 1) < STAR_DIP_CHANCE && (clock % STAR_PULSE) * 8 / star->speed < STAR_DIP_TIME) {
            size = rest - 1;
        }
        if (size != rest) {
            draw_star_size(art_clear, star, rest);
            draw_star_size(art_set, star, size);
        }
    }
}

// A shooting star now and then, entering from a side or the top at a random angle, with a flickering tail
static void update_and_draw_meteor(void) {
    static uint32_t timer  = 0;
    static uint16_t wait   = METEOR_MIN_WAIT;
    static bool     active = false;
    static int16_t  x, y; // in 1/4 px, so slopes other than 1:2 are possible
    static int8_t   vx, vy;
    static uint8_t  frame;

    if (!active) {
        if (timer_elapsed32(timer) < wait) {
            return;
        }
        active = true;
        vx     = random8_min_max(2, 11) * (random8_max(2) ? 1 : -1);
        vy     = random8_min_max(3, 7);
        // start just off screen so the first step brings it in
        if (random8_max(3) == 0) {
            x = random8_max(OLED_LINE_WIDTH) * 4;
            y = -1;
        } else {
            x = vx > 0 ? -1 : OLED_LINE_WIDTH * 4;
            y = random8_max(SKY_EFFECT_ROWS / 2) * 4;
        }
        frame = 0;
        timer = timer_read32();
    } else if (timer_elapsed32(timer) >= METEOR_FRAME_INTERVAL) {
        timer = timer_read32();
        x += vx;
        y += vy;
        frame++;
    }

    // approximate speed, so the tail spans about one pixel per point at any angle
    const int8_t speed   = MAX(abs(vx), vy) + MIN(abs(vx), vy) / 2;
    bool         visible = false;
    for (int8_t k = 0; k <= METEOR_TAIL; k++) {
        // the far half of the tail flickers so it reads as fading
        if (k > METEOR_TAIL / 2 && (frame + k) % 2) {
            continue;
        }
        const int16_t tx = (x - k * vx * 4 / speed) >> 2;
        const int16_t ty = (y - k * vy * 4 / speed) >> 2;
        if (tx >= 0 && tx < OLED_LINE_WIDTH && ty >= 0 && ty < SKY_EFFECT_ROWS) {
            visible = true;
            // masks are in art coordinates, the meteor flies in screen coordinates
            mask_pixel(art_set, (tx + art_shift) % OLED_LINE_WIDTH, ty);
        }
    }
    if (!visible && frame > 0) {
        active = false;
        wait   = METEOR_MIN_WAIT + random16() % (METEOR_MAX_WAIT - METEOR_MIN_WAIT);
    }
}

// The aurora sits between the sky and the tree tops, which reach up into line 11
#    define AURORA_FIRST_LINE SKY_LINES
#    define AURORA_LINES 9
#    define AURORA_END_ROW (8 * (AURORA_FIRST_LINE + AURORA_LINES))

// A 1-bit panel has no grey, so solid aurora is dithered to read as light
static void draw_aurora(const char *art) {
    static const uint8_t bayer[4][4]                              = {{0, 8, 2, 10}, {12, 4, 14, 6}, {3, 11, 1, 9}, {15, 7, 13, 5}};
    static uint8_t       dithered[AURORA_LINES * OLED_LINE_WIDTH] = {0};
    static bool          detected                                 = false;
    static uint32_t      timer                                    = 0;
    static uint8_t       phase                                    = 0;

    if (!detected) {
        detected = true;
        // only pixels with all 8 neighbours lit, so rays and every shape keep a solid 1px outline
        for (uint8_t y = 8 * AURORA_FIRST_LINE; y < AURORA_END_ROW; y++) {
            for (uint8_t x = 0; x < OLED_LINE_WIDTH; x++) {
                bool solid = true;
                for (int8_t dy = -1; dy <= 1 && solid; dy++) {
                    for (int8_t dx = -1; dx <= 1 && solid; dx++) {
                        solid = art_pixel(art, x + dx, y + dy);
                    }
                }
                if (solid) {
                    dithered[(y / 8 - AURORA_FIRST_LINE) * OLED_LINE_WIDTH + x] |= 1 << (y % 8);
                }
            }
        }
    }
    if (timer_elapsed32(timer) >= AURORA_FRAME_INTERVAL) {
        timer = timer_read32();
        phase += AURORA_PHASE_STEP;
    }

    for (uint16_t i = 0; i < sizeof(dithered); i++) {
        const uint8_t x = i % OLED_LINE_WIDTH;
        for (uint8_t bit = 0; bit < 8; bit++) {
            if (!(dithered[i] >> bit & 1)) {
                continue;
            }
            const uint8_t y = (AURORA_FIRST_LINE + i / OLED_LINE_WIDTH) * 8 + bit;
            // faint brighter bands travel down the rays, out of 16 levels
            const uint8_t level = AURORA_LEVEL - AURORA_SHIMMER + scale8(sin8(y * 6 - x * 3 - phase), 2 * AURORA_SHIMMER + 1);
            if (bayer[y % 4][x % 4] >= level) {
                art_clear[AURORA_FIRST_LINE * OLED_LINE_WIDTH + i] |= 1 << bit;
            }
        }
    }
}

static void render_sky_art(const char *art, uint16_t size) {
    static starfield_t field;

    update_art_drift();
    memset(art_set, 0, sizeof(art_set));
    memset(art_clear, 0, sizeof(art_clear));
    draw_aurora(art);
    draw_stars(&field, art, SKY_EFFECT_ROWS);
    update_and_draw_meteor();
    render_art(art, size, art_set, art_clear, sizeof(art_set));
}

// Exhaust streaming out of the username, faster the faster you type
static void render_exhaust(uint8_t line) {
    static struct {
        uint16_t x; // in 1/16 px
        uint8_t  life;
        uint8_t  row;
        int8_t   spread;
        uint8_t  speed;
    } particles[EXHAUST_PARTICLES];
    static uint32_t timer = 0;

    if (timer_elapsed32(timer) < EXHAUST_FRAME_INTERVAL) {
        return;
    }
    timer = timer_read32();

    const uint8_t wpm                      = get_current_wpm();
    uint8_t       columns[OLED_LINE_WIDTH] = {0};
    for (uint8_t i = 0; i < EXHAUST_PARTICLES; i++) {
        if ((particles[i].x += particles[i].speed + wpm / 4) / 16 >= particles[i].life) {
            particles[i].x = 0;
            // the product skews lifetimes short, so the trail is dense at the source and thins out
            particles[i].life   = 3 + random8_max(30) * random8_max(30) / 28;
            particles[i].row    = random8_min_max(2, 5);
            particles[i].spread = (int8_t)random8_max(5) - 2;
            particles[i].speed  = random8_min_max(2, 6);
        }
        const uint8_t x = particles[i].x / 16;
        const int8_t  y = particles[i].row + particles[i].spread * x / 10;
        // row 7 stays empty to keep a gap above the next line
        if (x < OLED_LINE_WIDTH && y >= 0 && y <= 6) {
            columns[x] |= 1 << y;
        }
    }
    for (uint8_t x = 0; x < OLED_LINE_WIDTH; x++) {
        oled_write_raw_byte(columns[x], line * OLED_LINE_WIDTH + x);
    }
}

static void render_logo(void) {
    // clang-format off
    static const char PROGMEM aurora_logo[] = {
        0x00, 0x00, 0x00, 0xe0, 0x00, 0xf8, 0xc0, 0xf8, 0xe0, 0xc0, 0xfc, 0x00, 0x7e, 0x18, 0x00, 0x80,
        0x00, 0x02, 0x80, 0xf0, 0x00, 0xc0, 0x80, 0xf8, 0xc0, 0xe0, 0x70, 0x60, 0x3c, 0x38, 0x3c, 0x1c,
        0x00, 0x3f, 0x0c, 0x0f, 0x1f, 0x03, 0x07, 0x01, 0xc3, 0x00, 0xe0, 0x80, 0x00, 0xe0, 0x80, 0xf8,
        0x80, 0xc0, 0xf7, 0xc7, 0x6f, 0x7b, 0x39, 0x30, 0x00, 0x80, 0x00, 0xc0, 0x00, 0xc0, 0xc2, 0xe0,
        0x00, 0x40, 0x38, 0x30, 0x38, 0x1e, 0x18, 0x1e, 0x0f, 0x0c, 0x07, 0x07, 0x07, 0x03, 0x03, 0x21,
        0x21, 0x31, 0x30, 0x18, 0x18, 0x1c, 0x08, 0x0c, 0x0e, 0x07, 0x06, 0x07, 0x03, 0x43, 0x03, 0x01,
        0x4c, 0xcc, 0xc2, 0xc2, 0x41, 0x49, 0x09, 0x2b, 0x2a, 0x6a, 0x6e, 0x24, 0x24, 0x04, 0x92, 0x92,
        0xb1, 0xf1, 0xf1, 0xf2, 0xe6, 0xa4, 0xa4, 0x04, 0x04, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28
    };
    // clang-format on
    static starfield_t field;

    update_art_drift();
    memset(art_set, 0, sizeof(aurora_logo));
    memset(art_clear, 0, sizeof(aurora_logo));
    draw_stars(&field, aurora_logo, SKY_EFFECT_ROWS);
    render_art(aurora_logo, sizeof(aurora_logo), art_set, art_clear, sizeof(aurora_logo));
}

// "v" QMK_VERSION in 3x5 glyphs on the username's baseline, too wide for 5 font cells; returns columns used
static uint8_t build_qmk_version(uint8_t columns[OLED_LINE_WIDTH]) {
    // one byte per column, LSB at the top
    static const uint8_t PROGMEM digits[10][3] = {
        {0x1F, 0x11, 0x1F}, {0x12, 0x1F, 0x10}, {0x1D, 0x15, 0x17}, {0x15, 0x15, 0x1F}, {0x07, 0x04, 0x1F},
        {0x17, 0x15, 0x1D}, {0x1F, 0x15, 0x1D}, {0x01, 0x01, 0x1F}, {0x1F, 0x15, 0x1F}, {0x17, 0x15, 0x1F},
    };
    static const char PROGMEM version[] = "v" QMK_VERSION;

    uint8_t width = 0;
    for (uint8_t i = 0; i < sizeof(version) - 1; i++) {
        const char c = pgm_read_byte(&version[i]);
        if (c >= '0' && c <= '9' && width + 3 <= OLED_LINE_WIDTH) {
            for (uint8_t j = 0; j < 3; j++) {
                columns[width++] = pgm_read_byte(&digits[c - '0'][j]) << 2;
            }
        } else if (c == 'v' && width + 3 <= OLED_LINE_WIDTH) {
            columns[width++] = 0x0C << 2;
            columns[width++] = 0x10 << 2;
            columns[width++] = 0x0C << 2;
        } else if (c == '.' && width < OLED_LINE_WIDTH) {
            columns[width++] = 0x10 << 2;
        } else {
            continue;
        }
        if (width < OLED_LINE_WIDTH) {
            columns[width++] = 0;
        }
    }
    return width;
}

static void render_qmk_version(uint8_t line) {
    uint8_t       columns[OLED_LINE_WIDTH] = {0};
    const uint8_t width                    = build_qmk_version(columns);
    const uint8_t offset                   = (OLED_LINE_WIDTH - width + 1) / 2; // width includes a trailing gap
    for (uint8_t x = 0; x < OLED_LINE_WIDTH; x++) {
        oled_write_raw_byte(x >= offset && x - offset < width ? columns[x - offset] : 0, line * OLED_LINE_WIDTH + x);
    }
}

// Shown only while every modifier is held, so it stays out of the way and off the burn-in budget
static bool qmk_version_requested(void) {
    static bool     holding = false;
    static uint32_t since   = 0;
    const uint8_t   mods    = get_mods();
    if (!((mods & MOD_MASK_CTRL) && (mods & MOD_MASK_SHIFT) && (mods & MOD_MASK_ALT) && (mods & MOD_MASK_GUI))) {
        holding = false;
        return false;
    }
    if (!holding) {
        holding = true;
        since   = timer_read32();
    }
    return timer_elapsed32(since) > QMK_VERSION_HOLD_TIME;
}

static void render_kb_LED_state(uint8_t col, uint8_t line) {
    led_t led_usb_state = host_keyboard_led_state();
    oled_set_cursor(col, line);
    oled_write_P(led_usb_state.num_lock ? PSTR("N ") : PSTR("  "), false);
    oled_write_P(led_usb_state.caps_lock ? PSTR("C ") : PSTR("  "), false);
    oled_write_P(led_usb_state.scroll_lock ? PSTR("S") : PSTR(" "), false);
}

bool oled_task_user(void) {
    // Animations dirty the buffer every frame, and the driver's OLED_TIMEOUT restarts on every dirty render
    if (last_input_activity_elapsed() > OLED_TIMEOUT) {
        oled_off();
        return false;
    }
    // human-timed mod changes keep the effects from replaying the same sequence every boot
    static uint8_t last_mods = 0;
    if (get_mods() != last_mods) {
        last_mods = get_mods();
        random16_add_entropy(timer_read());
    }
    if (is_keyboard_left()) {
        render_logo();
        render_user(0, 5);
        render_exhaust(6);
        render_kb_LED_state(0, 7);
        render_layer_state(0, 8);
        if (qmk_version_requested()) {
            render_qmk_version(11);
        } else {
            for (uint8_t x = 0; x < OLED_LINE_WIDTH; x++) {
                oled_write_raw_byte(0, 11 * OLED_LINE_WIDTH + x);
            }
        }
        render_mod_status_alt_gui(get_mods() | get_oneshot_mods(), 0, 12);
        render_mod_status_shift_ctrl(get_mods() | get_oneshot_mods(), is_caps_word_on_split(), 0, 14);
    } else {
        // clang-format off
        static const char PROGMEM aurora_art[] = {
            0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x1c, 0x08, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x40,
            0xe0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x80,
            0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x80, 0x00, 0xf0, 0x00, 0x00, 0xc0,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
            0x80, 0x00, 0xc0, 0x00, 0xfe, 0x00, 0xfc, 0x00, 0xff, 0x20, 0xff, 0xf0, 0x0f, 0xf0, 0x00, 0xff,
            0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x00, 0xf8, 0x00, 0x00, 0xf8,
            0xff, 0x10, 0xff, 0x84, 0xff, 0x60, 0xff, 0x36, 0xff, 0x0f, 0xff, 0x3f, 0x00, 0x5f, 0x00, 0x05,
            0x80, 0x00, 0x80, 0x00, 0xc0, 0x38, 0x00, 0xec, 0xf0, 0x00, 0xfb, 0x80, 0xff, 0xf0, 0xff, 0xef,
            0xff, 0xe8, 0xff, 0x03, 0xff, 0x0c, 0xff, 0x00, 0xff, 0x00, 0x03, 0x00, 0x00, 0xf8, 0x00, 0x80,
            0xff, 0x20, 0xff, 0xd0, 0xff, 0xe0, 0xfe, 0xf8, 0xff, 0xfc, 0xff, 0xff, 0x0f, 0xff, 0x01, 0x3f,
            0xff, 0x00, 0x0f, 0x00, 0x01, 0x00, 0x03, 0x00, 0xfe, 0x80, 0xfe, 0x00, 0xc0, 0xff, 0xc4, 0xfb,
            0xff, 0xfe, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0x07, 0xff, 0x03, 0x3f, 0x00, 0x0f, 0xc0, 0x00,
            0x00, 0x00, 0xb8, 0x00, 0xff, 0x40, 0xbe, 0xf0, 0xff, 0xf1, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff,
            0x1f, 0xff, 0x67, 0x00, 0xef, 0x00, 0x1f, 0x00, 0x00, 0x07, 0x00, 0x00, 0xe0, 0x00, 0xff, 0xf0,
            0xff, 0x88, 0xff, 0xc4, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0x7f, 0x0f, 0xff,
            0x00, 0x07, 0xfe, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0xc0, 0x3f, 0xf8, 0xe7, 0xff,
            0xff, 0xff, 0xff, 0x1f, 0xff, 0xff, 0x1f, 0x3f, 0x01, 0xff, 0x0b, 0x00, 0xff, 0x00, 0x00, 0x05,
            0x00, 0x00, 0x00, 0xe0, 0x00, 0xf8, 0x60, 0x80, 0xfe, 0xe3, 0xfc, 0xff, 0x1e, 0xff, 0xff, 0x23,
            0xff, 0x09, 0xff, 0x20, 0x00, 0x3f, 0x02, 0x00, 0x00, 0x0f, 0x00, 0x40, 0x00, 0xc0, 0x00, 0xfc,
            0xe0, 0xfc, 0xf0, 0xff, 0xff, 0x7f, 0xfc, 0xff, 0x0f, 0xff, 0x07, 0x1f, 0x00, 0x01, 0x0f, 0x00,
            0x0f, 0x00, 0x81, 0x70, 0x0c, 0xf0, 0x80, 0x00, 0x00, 0xe4, 0xf8, 0xe6, 0x70, 0x3f, 0xcf, 0xff,
            0x1f, 0xff, 0x48, 0xff, 0x0f, 0x00, 0x07, 0x00, 0x00, 0x43, 0x60, 0xf8, 0xf0, 0xfe, 0x38, 0xfe,
            0x00, 0xfc, 0x03, 0x00, 0xc8, 0x72, 0xcf, 0xfc, 0x00, 0x03, 0x0f, 0x01, 0xe0, 0x1c, 0xe0, 0x03,
            0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x06, 0xf9, 0x00, 0x03, 0x00, 0x07,
            0xff, 0x00, 0x10, 0x12, 0xc9, 0xf0, 0xcf, 0xb4, 0x7f, 0x80, 0xe0, 0x1e, 0x01, 0x40, 0x65, 0x5e,
            0xe0, 0x00, 0x00, 0xf0, 0x0c, 0xf0, 0x00, 0x80, 0x7e, 0x01, 0x80, 0x93, 0xfc, 0xc0, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x89, 0x18, 0x2c, 0x46, 0x00, 0x07, 0x21, 0x10, 0x10, 0x80, 0x09, 0x13,
            0x31, 0xbf, 0xff, 0x00, 0x08, 0x1a, 0xf7, 0x0f, 0x00, 0x00, 0x44, 0x45, 0x34, 0xbf, 0xb8, 0x00,
            0x10, 0x10, 0xa8, 0xf4, 0x18, 0x11, 0x1c, 0x78, 0xfb, 0x0e, 0x10, 0x18, 0xa4, 0xf8, 0x10, 0x20,
            0x18, 0x09, 0x1f, 0x6c, 0xea, 0x1f, 0x28, 0x60, 0x30, 0x38, 0xe0, 0xc0, 0x42, 0x33, 0x21, 0x00
        };
        // clang-format on
        render_sky_art(aurora_art, sizeof(aurora_art));
    }
    return false;
}
#endif
