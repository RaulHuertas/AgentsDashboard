

#include <SD.h>
#include <lvgl.h>

lv_obj_t * title_label;

void initializeDashboard(){
    lv_obj_t* title_label  = lv_label_create(lv_scr_act());
    lv_label_set_text(title_label, "Agents Monitor");
    lv_obj_set_pos(title_label, 90, 170);
}