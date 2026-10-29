#include "sky.h"

#include <lib/lib8tion/lib8tion.h>
#include <string.h>

static const sky_t *current;
static uint8_t      rows;
static uint8_t      shift;
// pixels the effects invert from the art this frame
static uint8_t flip[SKY_MASK_SIZE];

static uint16_t art_index(int16_t x, int16_t y) {
    return y / 8 * current->width + (x % current->width + current->width) % current->width;
}

// x wraps like the drifting art does
static bool art_pixel(int16_t x, int16_t y) {
    return y >= 0 && y < rows && (pgm_read_byte(&current->art[art_index(x, y)]) >> (y % 8) & 1);
}

// in art coordinates; the last write to a pixel wins
static void write_pixel(int16_t x, int16_t y, bool on) {
    if (y < 0 || y >= rows) {
        return;
    }
    const uint16_t i = art_index(x, y);
    if (i >= SKY_MASK_SIZE) {
        return;
    }
    if (art_pixel(x, y) != on) {
        flip[i] |= 1 << (y % 8);
    } else {
        flip[i] &= ~(1 << (y % 8));
    }
}

static void update_drift(void) {
    static uint32_t timer = 0;
    if (timer_elapsed32(timer) > SKY_DRIFT_INTERVAL) {
        timer = timer_read32();
        shift = (shift + 1) % current->width;
    }
}

typedef struct {
    uint8_t  x;
    uint8_t  y;
    bool     plus; // drawn as a plus in the art rather than a dot
    bool     cross; // a dot that grows diagonally, so dots differ from one another
    uint8_t  speed; // in 1/8, so pulses vary in length
    uint16_t offset;
} star_t;

static star_t  stars[SKY_MAX_STARS];
static uint8_t star_count;
static bool    stars_detected;

static uint8_t art_neighbours(int16_t x, int16_t y) {
    uint8_t count = 0;
    for (int8_t dy = -1; dy <= 1; dy++) {
        for (int8_t dx = -1; dx <= 1; dx++) {
            count += (dx || dy) && art_pixel(x + dx, y + dy);
        }
    }
    return count;
}

// a star is a lone pixel or the centre of a plus
static void detect_stars(void) {
    stars_detected = true;
    star_count     = 0;
    for (int16_t y = 0; y < current->star_rows && star_count < SKY_MAX_STARS; y++) {
        for (int16_t x = 0; x < current->width && star_count < SKY_MAX_STARS; x++) {
            if (!art_pixel(x, y)) {
                continue;
            }
            const uint8_t neighbours = art_neighbours(x, y);
            const bool    plus       = neighbours == 4 && art_pixel(x - 1, y) && art_pixel(x + 1, y) && art_pixel(x, y - 1) && art_pixel(x, y + 1);
            if (neighbours == 0 || plus) {
                stars[star_count++] = (star_t){.x = x, .y = y, .plus = plus, .cross = !plus && (random8() & 1), .speed = random8_min_max(8, SKY_STAR_MAX_SPEED + 1), .offset = random16()};
            }
        }
    }
}

static void draw_star_ring(const star_t *star, int8_t r, bool diagonal, bool on) {
    const int8_t d = diagonal ? r : 0;
    write_pixel(star->x - r, star->y - d, on);
    write_pixel(star->x + r, star->y + d, on);
    write_pixel(star->x + d, star->y - r, on);
    write_pixel(star->x - d, star->y + r, on);
}

// Sizes a star steps through, so a 1-bit pixel can brighten without jumping: dark, dot, small plus or x, longer plus, then detached tips
static void draw_star_size(const star_t *star, uint8_t size, bool on) {
    if (size >= 1) {
        write_pixel(star->x, star->y, on);
    }
    if (size >= 2) {
        draw_star_ring(star, 1, star->cross, on);
    }
    if (size >= 3) {
        draw_star_ring(star, 2, false, on);
    }
    if (size >= 4) {
        draw_star_ring(star, 4, false, on);
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
static void draw_stars(void) {
    if (!stars_detected) {
        detect_stars();
    }
    const uint32_t now = timer_read32();
    for (uint8_t i = 0; i < star_count; i++) {
        const star_t  *star  = &stars[i];
        const uint32_t clock = (now * star->speed >> 3) + star->offset;
        const uint32_t slot  = clock / SKY_STAR_PULSE;
        const uint8_t  rest  = star->plus ? 2 : 1;
        uint8_t        size  = rest;
        if (star_hash(i, slot, 0) < SKY_STAR_DENSITY) {
            const uint8_t phase      = (clock % SKY_STAR_PULSE) * 256 / SKY_STAR_PULSE;
            const uint8_t brightness = phase < 86 ? phase * 3 : 255 - (phase - 86) - (phase - 86) / 2;
            size                     = rest + (brightness * ((star->plus ? 4 : 2) - rest) + 127) / 255;
        } else if (star_hash(i, slot, 1) < SKY_STAR_DIP_CHANCE && (clock % SKY_STAR_PULSE) * 8 / star->speed < SKY_STAR_DIP_TIME) {
            size = rest - 1;
        }
        if (size != rest) {
            draw_star_size(star, rest, false);
            draw_star_size(star, size, true);
        }
    }
}

// A shooting star now and then, entering from a side or the top at a random angle, with a flickering tail
static void draw_meteor(void) {
    static uint32_t timer  = 0;
    static uint16_t wait   = SKY_METEOR_MIN_WAIT;
    static bool     active = false;
    static int16_t  x, y; // in 1/4 px, so slopes other than 1:2 are possible
    static int8_t   vx, vy;
    static uint8_t  frame;

    if (current->meteor_rows == 0) {
        return;
    }
    if (!active) {
        if (timer_elapsed32(timer) < wait) {
            return;
        }
        active = true;
        vx     = random8_min_max(2, 11) * (random8_max(2) ? 1 : -1);
        vy     = random8_min_max(3, 7);
        // start just off screen so the first step brings it in
        if (random8_max(3) == 0) {
            x = random8_max(current->width) * 4;
            y = -1;
        } else {
            x = vx > 0 ? -1 : current->width * 4;
            y = random8_max(current->meteor_rows / 2) * 4;
        }
        frame = 0;
        timer = timer_read32();
    } else if (timer_elapsed32(timer) >= SKY_METEOR_FRAME_INTERVAL) {
        timer = timer_read32();
        x += vx;
        y += vy;
        frame++;
    }

    // approximate speed, so the tail spans about one pixel per point at any angle
    const int8_t speed   = MAX(abs(vx), vy) + MIN(abs(vx), vy) / 2;
    bool         visible = false;
    for (int8_t k = 0; k <= SKY_METEOR_TAIL; k++) {
        // the far half of the tail flickers so it reads as fading
        if (k > SKY_METEOR_TAIL / 2 && (frame + k) % 2) {
            continue;
        }
        const int16_t tx = (x - k * vx * 4 / speed) >> 2;
        const int16_t ty = (y - k * vy * 4 / speed) >> 2;
        if (tx >= 0 && tx < current->width && ty >= 0 && ty < current->meteor_rows) {
            visible = true;
            // the meteor flies in screen coordinates
            write_pixel(tx + shift, ty, true);
        }
    }
    if (!visible && frame > 0) {
        active = false;
        wait   = SKY_METEOR_MIN_WAIT + random16() % (SKY_METEOR_MAX_WAIT - SKY_METEOR_MIN_WAIT);
    }
}

// only pixels with all 8 neighbours lit, so every shape keeps a solid 1px outline
static bool art_solid(int16_t x, int16_t y) {
    for (int8_t dy = -1; dy <= 1; dy++) {
        for (int8_t dx = -1; dx <= 1; dx++) {
            if (!art_pixel(x + dx, y + dy)) {
                return false;
            }
        }
    }
    return true;
}

// Solid aurora pixels, found once per sky as checking eight neighbours per pixel every frame is slow
static uint8_t aurora_solid[SKY_MASK_SIZE];
static bool    aurora_detected;

static void detect_aurora(void) {
    aurora_detected = true;
    memset(aurora_solid, 0, sizeof(aurora_solid));
    for (int16_t y = current->aurora_top; y < current->aurora_bottom; y++) {
        for (int16_t x = 0; x < current->width; x++) {
            const uint16_t i = art_index(x, y);
            if (i < SKY_MASK_SIZE && art_solid(x, y)) {
                aurora_solid[i] |= 1 << (y % 8);
            }
        }
    }
}

// A 1-bit panel has no grey, so solid aurora is dithered to read as light
static void draw_aurora(void) {
    static const uint8_t bayer[4][4] = {{0, 8, 2, 10}, {12, 4, 14, 6}, {3, 11, 1, 9}, {15, 7, 13, 5}};
    static uint32_t      timer       = 0;
    static uint8_t       phase       = 0;

    if (current->aurora_top >= current->aurora_bottom) {
        return;
    }
    if (!aurora_detected) {
        detect_aurora();
    }
    if (timer_elapsed32(timer) >= SKY_AURORA_FRAME_INTERVAL) {
        timer = timer_read32();
        phase += SKY_AURORA_PHASE_STEP;
    }
    const uint16_t end = MIN(current->size, SKY_MASK_SIZE);
    for (uint16_t i = current->aurora_top / 8 * current->width; i < end; i++) {
        if (!aurora_solid[i]) {
            continue;
        }
        const uint8_t x = i % current->width;
        for (uint8_t bit = 0; bit < 8; bit++) {
            if (!(aurora_solid[i] >> bit & 1)) {
                continue;
            }
            const uint8_t y = i / current->width * 8 + bit;
            // faint brighter bands travel down the rays, out of 16 levels
            const uint8_t level = SKY_AURORA_LEVEL - SKY_AURORA_SHIMMER + scale8(sin8(y * 6 - x * 3 - phase), 2 * SKY_AURORA_SHIMMER + 1);
            // the art is lit here and the aurora draws first, so flipping turns the pixel off
            if (bayer[y % 4][x % 4] >= level) {
                flip[i] |= 1 << bit;
            }
        }
    }
}

void sky_render(const sky_t *sky) {
    if (sky != current) {
        current         = sky;
        rows            = sky->size / sky->width * 8;
        shift           = 0;
        stars_detected  = false;
        aurora_detected = false;
    }
    // human-timed mod changes keep the effects from replaying the same sequence every boot
    static uint8_t last_mods = 0;
    if (get_mods() != last_mods) {
        last_mods = get_mods();
        random16_add_entropy(timer_read());
    }

    update_drift();
    memset(flip, 0, MIN(sky->size, SKY_MASK_SIZE));
    draw_aurora();
    draw_stars();
    draw_meteor();
    for (uint16_t i = 0; i < sky->size; i++) {
        const uint16_t source = i / sky->width * sky->width + (i % sky->width + shift) % sky->width;
        uint8_t        data   = pgm_read_byte(&sky->art[source]);
        if (source < SKY_MASK_SIZE) {
            data ^= flip[source];
        }
        oled_write_raw_byte(data, i);
    }
}
