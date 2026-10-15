#pragma once

#include <lvgl.h>
#include <zephyr/kernel.h>
#include "util.h"

struct zmk_widget_screen {
    sys_snode_t node;
    lv_obj_t *obj;
    /* The panel is 1 bpp (CONFIG_LV_COLOR_DEPTH=1), so the canvas is the native
     * format: 1 bit per pixel. Only one buffer: lv_canvas_set_buffer() binds cbuf
     * to the canvas and every draw goes through the canvas object, so the extra
     * buffers this used to carry (97 KB) were never read. */
    LV_ATTRIBUTE_MEM_ALIGN uint8_t cbuf[SCREEN_STRIDE * SCREEN_HEIGHT];
    struct status_state state;
};

int zmk_widget_screen_init(struct zmk_widget_screen *widget, lv_obj_t *parent);
lv_obj_t *zmk_widget_screen_obj(struct zmk_widget_screen *widget);
