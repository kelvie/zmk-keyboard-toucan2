#include <zephyr/kernel.h>
#include "util.h"
#include <ctype.h>
#include <string.h>


void to_uppercase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
}

/* Labels for the bluetooth profiles, set with CONFIG_ZMK_BT_PROFILE_<n>_NAME.
 * Empty (the default) means "draw nothing", i.e. plain BT 1..5 dots. */
static const char *const bt_profile_names[] = {
    CONFIG_ZMK_BT_PROFILE_0_NAME,
    CONFIG_ZMK_BT_PROFILE_1_NAME,
    CONFIG_ZMK_BT_PROFILE_2_NAME,
    CONFIG_ZMK_BT_PROFILE_3_NAME,
    CONFIG_ZMK_BT_PROFILE_4_NAME,
};

const char *bt_profile_name(int idx) {
    if (idx < 0 || idx >= (int)ARRAY_SIZE(bt_profile_names)) {
        return "";
    }
    return bt_profile_names[idx];
}

void fill_background(lv_obj_t *canvas) {
    lv_canvas_fill_bg(canvas, LVGL_BACKGROUND, LV_OPA_COVER);
}

void toucan_canvas_draw_img(lv_obj_t *canvas, int32_t x, int32_t y, const lv_img_dsc_t *img,
                            const lv_draw_image_dsc_t *dsc) {
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_image_dsc_t draw_dsc;
    lv_draw_image_dsc_init(&draw_dsc);
    if (dsc != NULL) {
        draw_dsc = *dsc;
    }
    draw_dsc.src = img;

    lv_area_t area = {.x1 = x,
                      .y1 = y,
                      .x2 = x + (int32_t)img->header.w - 1,
                      .y2 = y + (int32_t)img->header.h - 1};

    lv_draw_image(&layer, &draw_dsc, &area);
    lv_canvas_finish_layer(canvas, &layer);
}

void toucan_canvas_draw_text(lv_obj_t *canvas, int32_t x, int32_t y, int32_t max_w,
                             const lv_draw_label_dsc_t *dsc, const char *text) {
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_label_dsc_t draw_dsc;
    lv_draw_label_dsc_init(&draw_dsc);
    if (dsc != NULL) {
        draw_dsc = *dsc;
    }
    draw_dsc.text = text;
    draw_dsc.text_length = text ? strlen(text) : 0;

    int32_t line_height = draw_dsc.font ? lv_font_get_line_height(draw_dsc.font) : 16;
    lv_area_t area = {.x1 = x,
                      .y1 = y,
                      .x2 = x + max_w - 1,
                      .y2 = y + line_height - 1};

    lv_draw_label(&layer, &draw_dsc, &area);
    lv_canvas_finish_layer(canvas, &layer);
}

void toucan_canvas_draw_rect(lv_obj_t *canvas, int32_t x, int32_t y, int32_t w, int32_t h,
                             const lv_draw_rect_dsc_t *dsc) {
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_rect_dsc_t draw_dsc;
    lv_draw_rect_dsc_init(&draw_dsc);
    if (dsc != NULL) {
        draw_dsc = *dsc;
    }

    lv_area_t area = {.x1 = x, .y1 = y, .x2 = x + w - 1, .y2 = y + h - 1};

    lv_draw_rect(&layer, &draw_dsc, &area);
    lv_canvas_finish_layer(canvas, &layer);
}

void init_label_dsc(lv_draw_label_dsc_t *label_dsc, lv_color_t color, const lv_font_t *font,
                    lv_text_align_t align) {
    lv_draw_label_dsc_init(label_dsc);
    label_dsc->color = color;
    label_dsc->font = font;
    label_dsc->align = align;
}

void init_rect_dsc(lv_draw_rect_dsc_t *rect_dsc, lv_color_t bg_color) {
    lv_draw_rect_dsc_init(rect_dsc);
    rect_dsc->bg_color = bg_color;
}

void init_line_dsc(lv_draw_line_dsc_t *line_dsc, lv_color_t color, uint8_t width) {
    lv_draw_line_dsc_init(line_dsc);
    line_dsc->color = color;
    line_dsc->width = width;
}