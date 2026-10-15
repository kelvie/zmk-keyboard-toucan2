#pragma once

#include <lvgl.h>
#include <zmk/endpoints.h>

#define SCREEN_WIDTH 144
#define SCREEN_HEIGHT 168
/* The panel is 1 bpp (CONFIG_LV_COLOR_DEPTH=1), so the canvas uses the native
 * format: 1 bit per pixel, rows padded to a byte boundary. */
#define SCREEN_STRIDE ((SCREEN_WIDTH + 7) / 8)

#define BUFFER_SIZE 168
#define BUFFER_OFFSET_MIDDLE 0
#define BUFFER_OFFSET_BOTTOM 0

#define LVGL_BACKGROUND lv_color_black()
#define LVGL_FOREGROUND lv_color_white()

struct status_state {
    uint8_t battery;
    uint8_t battery_p;
    bool charging;
    bool charging_p;
    uint8_t wpm;
#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
    struct zmk_endpoint_instance selected_endpoint;
    int active_profile_index;
    bool active_profile_connected;
    bool active_profile_bonded;
    uint8_t layer_index;
    const char *layer_label;
#else
    bool connected;
#endif
};

void to_uppercase(char *str);
const char *bt_profile_name(int idx);
void fill_background(lv_obj_t *canvas);
void init_rect_dsc(lv_draw_rect_dsc_t *rect_dsc, lv_color_t bg_color);
void init_line_dsc(lv_draw_line_dsc_t *line_dsc, lv_color_t color, uint8_t width);
void init_label_dsc(lv_draw_label_dsc_t *label_dsc, lv_color_t color, const lv_font_t *font,
                    lv_text_align_t align);

/* lvgl 9 removed lv_canvas_draw_img/text/rect: drawing into a canvas now goes
 * through a layer that has to be opened and closed around the draw calls. These
 * keep the lvgl 8 call shape so the widget code stays readable. */
void toucan_canvas_draw_img(lv_obj_t *canvas, int32_t x, int32_t y, const lv_img_dsc_t *img,
                            const lv_draw_image_dsc_t *dsc);
void toucan_canvas_draw_text(lv_obj_t *canvas, int32_t x, int32_t y, int32_t max_w,
                             const lv_draw_label_dsc_t *dsc, const char *text);
void toucan_canvas_draw_rect(lv_obj_t *canvas, int32_t x, int32_t y, int32_t w, int32_t h,
                             const lv_draw_rect_dsc_t *dsc);
