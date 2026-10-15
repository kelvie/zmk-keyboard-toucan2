#include <zephyr/kernel.h>
#include "util.h"
#include <ctype.h>


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
    lv_draw_rect_dsc_t rect_black_dsc;
    rect_black_dsc.bg_color = lv_color_white();  // set background color to white
    init_rect_dsc(&rect_black_dsc, LVGL_BACKGROUND);

    lv_canvas_draw_rect(canvas, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, &rect_black_dsc);
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