#include <zephyr/kernel.h>
#include "profile.h"
#include "../assets/custom_fonts.h"

LV_IMG_DECLARE(profiles);

static void draw_inactive_profiles(lv_obj_t *canvas, const struct status_state *state) {
    lv_draw_image_dsc_t img_dsc;
    lv_draw_image_dsc_init(&img_dsc);

    toucan_canvas_draw_img(canvas, 85, 143, &profiles, &img_dsc);
}

static void draw_active_profile(lv_obj_t *canvas, const struct status_state *state) {
    lv_draw_rect_dsc_t rect_white_dsc;
    init_rect_dsc(&rect_white_dsc, LVGL_FOREGROUND);

    int offset = state->active_profile_index * 10;

    toucan_canvas_draw_rect(canvas, 85 + offset, 143, 8, 8, &rect_white_dsc);
}

void draw_profile_status(lv_obj_t *canvas, const struct status_state *state) {
    draw_inactive_profiles(canvas, state);
    draw_active_profile(canvas, state);

    // Name of the active profile (CONFIG_ZMK_BT_PROFILE_<n>_NAME), above the
    // profile dots / output label row.
    const char *name = bt_profile_name(state->active_profile_index);
    if (name[0] != '\0') {
        lv_draw_label_dsc_t label_dsc;
        init_label_dsc(&label_dsc, LVGL_FOREGROUND, &quinquefive_8, LV_TEXT_ALIGN_LEFT);
        toucan_canvas_draw_text(canvas, 12, 120, 120, &label_dsc, (char *)name);
    }
}