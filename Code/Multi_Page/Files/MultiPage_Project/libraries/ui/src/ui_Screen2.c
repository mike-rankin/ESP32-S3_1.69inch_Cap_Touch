// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.1
// LVGL version: 8.3.11
// Project name: MultiPage_Project

#include "ui.h"

void ui_Screen2_screen_init(void)
{
    ui_Screen2 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_Screen2, &ui_img_texture_background_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TopButton1 = lv_obj_create(ui_Screen2);
    lv_obj_set_width(ui_TopButton1, 15);
    lv_obj_set_height(ui_TopButton1, 15);
    lv_obj_set_x(ui_TopButton1, 125);
    lv_obj_set_y(ui_TopButton1, 0);
    lv_obj_set_align(ui_TopButton1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_TopButton1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_TopButton1, lv_color_hex(0x737173), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_TopButton1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_TopButton1, lv_color_hex(0x737173), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_TopButton1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MiddleButton1 = lv_obj_create(ui_Screen2);
    lv_obj_set_width(ui_MiddleButton1, 56);
    lv_obj_set_height(ui_MiddleButton1, 100);
    lv_obj_set_x(ui_MiddleButton1, 108);
    lv_obj_set_y(ui_MiddleButton1, 26);
    lv_obj_set_align(ui_MiddleButton1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_MiddleButton1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MiddleButton1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MiddleButton1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_MiddleButton1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_MiddleButton1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_MiddleButton1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtomButton1 = lv_obj_create(ui_Screen2);
    lv_obj_set_width(ui_ButtomButton1, 15);
    lv_obj_set_height(ui_ButtomButton1, 15);
    lv_obj_set_x(ui_ButtomButton1, 125);
    lv_obj_set_y(ui_ButtomButton1, 60);
    lv_obj_set_align(ui_ButtomButton1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_ButtomButton1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtomButton1, lv_color_hex(0x737173), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtomButton1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_ButtomButton1, lv_color_hex(0x737173), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_ButtomButton1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TopSwitch = lv_switch_create(ui_Screen2);
    lv_obj_set_width(ui_TopSwitch, 81);
    lv_obj_set_height(ui_TopSwitch, 34);
    lv_obj_set_x(ui_TopSwitch, -81);
    lv_obj_set_y(ui_TopSwitch, -69);
    lv_obj_set_align(ui_TopSwitch, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_TopSwitch, lv_color_hex(0x3991AB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_TopSwitch, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_TopSwitch, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_TopSwitch, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_TopSwitch, 1, LV_PART_MAIN | LV_STATE_DEFAULT);


    ui_TopFanLabel = lv_label_create(ui_Screen2);
    lv_obj_set_width(ui_TopFanLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_TopFanLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_TopFanLabel, -83);
    lv_obj_set_y(ui_TopFanLabel, -100);
    lv_obj_set_align(ui_TopFanLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_TopFanLabel, "Fan#1");
    lv_obj_set_style_text_color(ui_TopFanLabel, lv_color_hex(0x050505), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TopFanLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BottomSwitch = lv_switch_create(ui_Screen2);
    lv_obj_set_width(ui_BottomSwitch, 81);
    lv_obj_set_height(ui_BottomSwitch, 34);
    lv_obj_set_x(ui_BottomSwitch, -79);
    lv_obj_set_y(ui_BottomSwitch, 6);
    lv_obj_set_align(ui_BottomSwitch, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_BottomSwitch, lv_color_hex(0x3991AB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BottomSwitch, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_BottomSwitch, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_BottomSwitch, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_BottomSwitch, 1, LV_PART_MAIN | LV_STATE_DEFAULT);


    ui_BottomFanLabel = lv_label_create(ui_Screen2);
    lv_obj_set_width(ui_BottomFanLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BottomFanLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_BottomFanLabel, -83);
    lv_obj_set_y(ui_BottomFanLabel, -30);
    lv_obj_set_align(ui_BottomFanLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BottomFanLabel, "Fan#2");
    lv_obj_set_style_text_color(ui_BottomFanLabel, lv_color_hex(0x050505), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_BottomFanLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Button1 = lv_btn_create(ui_Screen2);
    lv_obj_set_width(ui_Button1, 62);
    lv_obj_set_height(ui_Button1, 50);
    lv_obj_set_x(ui_Button1, -78);
    lv_obj_set_y(ui_Button1, 79);
    lv_obj_set_align(ui_Button1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Button1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Button1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Button1, lv_color_hex(0x3991AC), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Button1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Button1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Button1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Button1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LedButton = lv_label_create(ui_Screen2);
    lv_obj_set_width(ui_LedButton, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LedButton, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LedButton, -79);
    lv_obj_set_y(ui_LedButton, 40);
    lv_obj_set_align(ui_LedButton, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LedButton, "Led");
    lv_obj_set_style_text_color(ui_LedButton, lv_color_hex(0x050505), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LedButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Fan1 = lv_img_create(ui_Screen2);
    lv_img_set_src(ui_Fan1, &ui_img_fan_png);
    lv_obj_set_width(ui_Fan1, LV_SIZE_CONTENT);   /// 100
    lv_obj_set_height(ui_Fan1, LV_SIZE_CONTENT);    /// 100
    lv_obj_set_x(ui_Fan1, 29);
    lv_obj_set_y(ui_Fan1, -68);
    lv_obj_set_align(ui_Fan1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Fan1, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Fan1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_Fan1, 175);

    ui_Fan2 = lv_img_create(ui_Screen2);
    lv_img_set_src(ui_Fan2, &ui_img_fan_png);
    lv_obj_set_width(ui_Fan2, LV_SIZE_CONTENT);   /// 100
    lv_obj_set_height(ui_Fan2, LV_SIZE_CONTENT);    /// 100
    lv_obj_set_x(ui_Fan2, 28);
    lv_obj_set_y(ui_Fan2, 4);
    lv_obj_set_align(ui_Fan2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Fan2, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Fan2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_Fan2, 175);

    ui_Panel2 = lv_obj_create(ui_Screen2);
    lv_obj_set_width(ui_Panel2, 15);
    lv_obj_set_height(ui_Panel2, 15);
    lv_obj_set_x(ui_Panel2, 125);
    lv_obj_set_y(ui_Panel2, 30);
    lv_obj_set_align(ui_Panel2, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Panel2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_GreenLed = lv_obj_create(ui_Screen2);
    lv_obj_set_width(ui_GreenLed, 40);
    lv_obj_set_height(ui_GreenLed, 40);
    lv_obj_set_x(ui_GreenLed, 26);
    lv_obj_set_y(ui_GreenLed, 71);
    lv_obj_set_align(ui_GreenLed, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_GreenLed, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_GreenLed, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_GreenLed, lv_color_hex(0x23D167), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_GreenLed, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_GreenLed, lv_color_hex(0x20D262), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui_GreenLed, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_color(ui_GreenLed, lv_color_hex(0x20D262), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_opa(ui_GreenLed, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui_GreenLed, 75, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_spread(ui_GreenLed, 5, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_add_event_cb(ui_MiddleButton1, ui_event_MiddleButton1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_TopSwitch, ui_event_TopSwitch, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BottomSwitch, ui_event_BottomSwitch, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Button1, ui_event_Button1, LV_EVENT_ALL, NULL);

}