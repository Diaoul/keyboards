#pragma once

#include QMK_KEYBOARD_H

// Defaults below can be overridden in config.h

// Art drift, which spreads OLED wear
#ifndef SKY_DRIFT_INTERVAL
#    define SKY_DRIFT_INTERVAL 10000 // ms per pixel
#endif
// Largest art a sky can animate, in bytes
#ifndef SKY_MASK_SIZE
#    define SKY_MASK_SIZE OLED_MATRIX_SIZE
#endif

// Stars
#ifndef SKY_MAX_STARS
#    define SKY_MAX_STARS 16
#endif
#ifndef SKY_STAR_PULSE
#    define SKY_STAR_PULSE 400 // one rise and fade, in ms
#endif
#ifndef SKY_STAR_DENSITY
#    define SKY_STAR_DENSITY 22 // share of pulse slots in which a star twinkles, out of 256
#endif
#ifndef SKY_STAR_DIP_CHANCE
#    define SKY_STAR_DIP_CHANCE 10 // share of the other slots in which a star dips, out of 256
#endif
#ifndef SKY_STAR_DIP_TIME
#    define SKY_STAR_DIP_TIME 150 // in ms
#endif
#ifndef SKY_STAR_MAX_ACTIVE
#    define SKY_STAR_MAX_ACTIVE 2 // stars animating at once
#endif

// Shooting star
#ifndef SKY_METEOR_FRAME_INTERVAL
#    define SKY_METEOR_FRAME_INTERVAL 40 // in ms
#endif
#ifndef SKY_METEOR_TAIL
#    define SKY_METEOR_TAIL 5 // in pixels
#endif
#ifndef SKY_METEOR_MIN_WAIT
#    define SKY_METEOR_MIN_WAIT 10000 // in ms
#endif
#ifndef SKY_METEOR_MAX_WAIT
#    define SKY_METEOR_MAX_WAIT 40000 // in ms, at most 65535
#endif

// Aurora
#ifndef SKY_AURORA_FRAME_INTERVAL
#    define SKY_AURORA_FRAME_INTERVAL 100 // in ms
#endif
#ifndef SKY_AURORA_PHASE_STEP
#    define SKY_AURORA_PHASE_STEP 4 // a ripple takes 256 / step frames to pass
#endif
#ifndef SKY_AURORA_LEVEL
#    define SKY_AURORA_LEVEL 9 // lit share of solid aurora, out of 16
#endif
#ifndef SKY_AURORA_SHIMMER
#    define SKY_AURORA_SHIMMER 2 // levels the ripple adds or removes
#endif

enum {
    SKY_DOT, // a pixel in the art, growing into a small plus
    SKY_DOT_X, // a pixel in the art, growing into a small x
    SKY_PLUS, // a plus in the art, growing out to detached tips
};

typedef struct {
    uint8_t x; // in art coordinates, so the star drifts with the art
    uint8_t y;
    uint8_t shape;
} sky_star_t;

// Art animated as a night sky: its stars twinkle, a shooting star crosses it and its solid areas shimmer
typedef struct {
    const char       *art; // PROGMEM, in OLED buffer order
    uint16_t          size; // in bytes, at most SKY_MASK_SIZE
    uint8_t           width; // pixels per OLED line
    const sky_star_t *stars; // at most SKY_MAX_STARS
    uint8_t           star_count;
    uint8_t           meteor_rows; // a shooting star crosses the rows above this, 0 for none
    uint8_t           aurora_top; // solid areas from this row to aurora_bottom shimmer, equal for none
    uint8_t           aurora_bottom;
} sky_t;

// Renders the sky from the top of the OLED; one sky per display, as they share state
void sky_render(const sky_t *sky);
