

#include <SD.h>
#include <lvgl.h>
#include <string.h>
#include "AgentsDashboard.h"



Agent::Agent(){
    working = false;
}

Agent agents[NSTATUS];

lv_obj_t * title_label;
lv_obj_t * status_circles[NSTATUS] = {nullptr, nullptr, nullptr, nullptr};
lv_obj_t * status_labels[NSTATUS] = {nullptr, nullptr, nullptr, nullptr};

static const lv_color_t STATUS_COLORS[NSTATUS] = {
    lv_color_hex(0xFFEA00), // Hi-viz yellow
    lv_color_hex(0x7B2CBF), // Purple
    lv_color_hex(0xFF3B30), // Red
    lv_color_hex(0x007BFF)  // Blue
};

static void statusCircleAnimExecCb(void * var, int32_t v) {
    lv_obj_t * circle = (lv_obj_t *)var;
    lv_obj_set_style_bg_opa(circle, (lv_opa_t)v, LV_PART_MAIN);
    lv_obj_set_style_border_opa(circle, (lv_opa_t)v, LV_PART_MAIN);
}

void setStatusCircleColor(uint8_t circle_index, int color) {
    if (circle_index >= NSTATUS) {
        return;
    }
    if (status_circles[circle_index] == nullptr) {
        return;
    }
    lv_obj_set_style_bg_color(status_circles[circle_index], STATUS_COLORS[(int)color], LV_PART_MAIN);
    lv_obj_set_style_border_color(status_circles[circle_index], STATUS_COLORS[(int)color], LV_PART_MAIN);
}

void setStatusCircleAnimation(uint8_t circle_index, bool enable) {
    if (circle_index >= NSTATUS) {
        return;
    }

    lv_obj_t * circle = status_circles[circle_index];
    if (circle == nullptr) {
        return;
    }

    if (enable) {
        lv_anim_del(circle, statusCircleAnimExecCb);

        lv_anim_t anim;
        lv_anim_init(&anim);
        lv_anim_set_var(&anim, circle);
        lv_anim_set_exec_cb(&anim, statusCircleAnimExecCb);
        lv_anim_set_values(&anim, LV_OPA_40, LV_OPA_COVER);
        lv_anim_set_time(&anim, 500);
        lv_anim_set_playback_time(&anim, 500);
        lv_anim_set_repeat_count(&anim, LV_ANIM_REPEAT_INFINITE);
        lv_anim_start(&anim);
    } else {
        lv_anim_del(circle, statusCircleAnimExecCb);
        lv_obj_set_style_bg_opa(circle, LV_OPA_COVER, LV_PART_MAIN);
        lv_obj_set_style_border_opa(circle, LV_OPA_COVER, LV_PART_MAIN);
    }
}

void setStatusCircleLabel(uint8_t circle_index, const char *text) {
    if (circle_index >= NSTATUS) {
        return;
    }
    if (status_labels[circle_index] == nullptr) {
        return;
    }
    if (text == nullptr) {
        text = "";
    }
    int newLen = strlen(text);
    int limitedLen = min(newLen,AGENTS_NAME_MAX_LEN);
    strncpy(agents[circle_index].name, text, limitedLen);
    agents[circle_index].name[limitedLen] = 0;

    lv_label_set_text(status_labels[circle_index], agents[circle_index].name);
    //lv_obj_set_style_text_color(status_labels[circle_index], lv_color_black(), LV_PART_MAIN);
}

void initializeDashboard(){
    for (uint8_t i = 0; i < NSTATUS; i++) {
        agents[i].name[0] = '\0';
    }
    //Draw the background
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_scr_act(), LV_OPA_COVER, LV_PART_MAIN); 
    //Draw the title
    title_label = lv_label_create(lv_scr_act());
    lv_label_set_text(title_label, "Agents Monitor");
    lv_obj_set_style_text_color(title_label, lv_color_white(), LV_PART_MAIN);
    lv_obj_center(title_label);
    //Draw status circles
    static const lv_align_t alignments[NSTATUS] = {
        LV_ALIGN_TOP_LEFT,
        LV_ALIGN_TOP_RIGHT,
        LV_ALIGN_BOTTOM_LEFT,
        LV_ALIGN_BOTTOM_RIGHT
    };
    const lv_coord_t distanceToBorder = 32;
    const lv_coord_t diameter = 76;
    lv_coord_t offsets_x[NSTATUS] = {distanceToBorder, -distanceToBorder, distanceToBorder, -distanceToBorder};
    lv_coord_t offsets_y[NSTATUS] = {distanceToBorder, distanceToBorder, -distanceToBorder, -distanceToBorder};

    for (uint8_t i = 0; i < NSTATUS; i++) {
        status_circles[i] = lv_obj_create(lv_scr_act());
        lv_obj_set_size(status_circles[i], diameter, diameter);
        lv_obj_set_style_radius(status_circles[i], LV_RADIUS_CIRCLE, LV_PART_MAIN);
        lv_obj_set_style_bg_opa(status_circles[i], LV_OPA_COVER, LV_PART_MAIN);
        lv_obj_set_style_bg_color(status_circles[i], STATUS_COLORS[i], LV_PART_MAIN);
        lv_obj_set_style_border_width(status_circles[i], 0, LV_PART_MAIN);
        //lv_obj_set_style_border_color(status_circles[i], STATUS_COLORS[i], LV_PART_MAIN);
        lv_obj_align(status_circles[i], alignments[i], offsets_x[i], offsets_y[i]);

        status_labels[i] = lv_label_create(status_circles[i]);
        lv_label_set_text(status_labels[i], agents[i].name);
        lv_obj_set_style_text_color(status_labels[i], lv_color_black(), LV_PART_MAIN);
        lv_obj_set_style_text_decor(status_labels[i], LV_TEXT_DECOR_NONE, LV_PART_MAIN);
        lv_obj_center(status_labels[i]);
    }
        
}

void changeAgentStatus(int index, bool working, const char* newName){
    agents[index].working = working;
    setStatusCircleLabel((uint8_t)index, newName);
    setStatusCircleAnimation(index, working);
}

bool updateOrPlaceAgentStatus(const char* name, bool working) {
    if (name == nullptr || name[0] == '\0') {
        return false;
    }

    for (uint8_t i = 0; i < NSTATUS; i++) {
        if (strcmp(agents[i].name, name) == 0) {
            agents[i].working = working;
            setStatusCircleAnimation(i, working);
            return true;
        }
    }

    for (uint8_t i = 0; i < NSTATUS; i++) {
        if (agents[i].name[0] == '\0') {
            setStatusCircleLabel(i, name);
            agents[i].working = working;
            setStatusCircleAnimation(i, working);
            return true;
        }
    }

    return false;
}


