

#include <SD.h>
#include <lvgl.h>

lv_obj_t * title_label;

void initializeDashboard(){
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_scr_act(), LV_OPA_COVER, LV_PART_MAIN);

    title_label = lv_label_create(lv_scr_act());
    lv_label_set_text(title_label, "Agents Monitor");
    lv_obj_set_style_text_color(title_label, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_pos(title_label, 90, 170);
}
