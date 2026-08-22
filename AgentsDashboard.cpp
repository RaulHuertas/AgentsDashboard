

#include <SD.h>
#include <lvgl.h>

lv_obj_t * title_label;
lv_obj_t * status_circles[4] = {nullptr, nullptr, nullptr, nullptr};

static const lv_color_t STATUS_COLORS[4] = {
    lv_color_hex(0xFFEA00), // Hi-viz yellow
    lv_color_hex(0x7B2CBF), // Purple
    lv_color_hex(0xFF3B30), // Red
    lv_color_hex(0x007BFF)  // Blue
};

void setStatusCircleColor(uint8_t circle_index, int color) {
    if (circle_index >= 4 ) {
        return;
    }

    if (status_circles[circle_index] == nullptr) {
        return;
    }

    lv_obj_set_style_bg_color(status_circles[circle_index], STATUS_COLORS[color], LV_PART_MAIN);
    lv_obj_set_style_border_color(status_circles[circle_index], STATUS_COLORS[color], LV_PART_MAIN);
}

void initializeDashboard(){
    //Draw the background
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_scr_act(), LV_OPA_COVER, LV_PART_MAIN); 
    //Draw the title
    title_label = lv_label_create(lv_scr_act());
    lv_label_set_text(title_label, "Agents Monitor");
    lv_obj_set_style_text_color(title_label, lv_color_white(), LV_PART_MAIN);
    lv_obj_center(title_label);
    //Draw status circles
    static const lv_align_t alignments[4] = {
        LV_ALIGN_TOP_LEFT,
        LV_ALIGN_TOP_RIGHT,
        LV_ALIGN_BOTTOM_LEFT,
        LV_ALIGN_BOTTOM_RIGHT
    };
    int distanceToBorder = 32;
    int diameter = 68;
    static const lv_coord_t offsets_x[4] = {distanceToBorder, -distanceToBorder, distanceToBorder, -distanceToBorder};
    static const lv_coord_t offsets_y[4] = {distanceToBorder, distanceToBorder, -distanceToBorder, -distanceToBorder};

    for (uint8_t i = 0; i < 4; i++) {
        status_circles[i] = lv_obj_create(lv_scr_act());
        lv_obj_set_size(status_circles[i], diameter, diameter);
        lv_obj_set_style_radius(status_circles[i], LV_RADIUS_CIRCLE, LV_PART_MAIN);
        lv_obj_set_style_bg_opa(status_circles[i], LV_OPA_COVER, LV_PART_MAIN);
        lv_obj_set_style_bg_color(status_circles[i], STATUS_COLORS[i], LV_PART_MAIN);
        lv_obj_set_style_border_width(status_circles[i], 2, LV_PART_MAIN);
        lv_obj_set_style_border_color(status_circles[i], STATUS_COLORS[i], LV_PART_MAIN);
        lv_obj_align(status_circles[i], alignments[i], offsets_x[i], offsets_y[i]);
    }
}
