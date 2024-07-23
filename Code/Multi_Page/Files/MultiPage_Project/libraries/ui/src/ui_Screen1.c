// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.1
// LVGL version: 8.3.11
// Project name: MultiPage_Project

#include "ui.h"

void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_Screen1, &ui_img_background_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Image4 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_Image4, &ui_img_watchface3_png);
    lv_obj_set_width(ui_Image4, LV_SIZE_CONTENT);   /// 240
    lv_obj_set_height(ui_Image4, LV_SIZE_CONTENT);    /// 240
    lv_obj_set_x(ui_Image4, -72);
    lv_obj_set_y(ui_Image4, -51);
    lv_obj_set_align(ui_Image4, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image4, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_Image4, 130);

    ui_Image2 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_Image2, &ui_img_partly_cloudy_png);
    lv_obj_set_width(ui_Image2, LV_SIZE_CONTENT);   /// 32
    lv_obj_set_height(ui_Image2, LV_SIZE_CONTENT);    /// 32
    lv_obj_set_x(ui_Image2, 94);
    lv_obj_set_y(ui_Image2, -84);
    lv_obj_set_align(ui_Image2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image2, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_Image2, 500);

    ui_DateLabel = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_DateLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_DateLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_DateLabel, 0);
    lv_obj_set_y(ui_DateLabel, 94);
    lv_obj_set_align(ui_DateLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DateLabel, "Tuesday June 11, 2024");
    lv_obj_set_style_text_color(ui_DateLabel, lv_color_hex(0xF9F6F6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DateLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_DateLabel, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label2 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label2, 97);
    lv_obj_set_y(ui_Label2, -41);
    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label2, "25° C");
    lv_obj_set_style_text_color(ui_Label2, lv_color_hex(0xF9F6F6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label2, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_HourHand = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_HourHand, &ui_img_clockwise_hour_png);
    lv_obj_set_width(ui_HourHand, LV_SIZE_CONTENT);   /// 18
    lv_obj_set_height(ui_HourHand, LV_SIZE_CONTENT);    /// 98
    lv_obj_set_x(ui_HourHand, -72);
    lv_obj_set_y(ui_HourHand, -79);
    lv_obj_set_align(ui_HourHand, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_HourHand, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_HourHand, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_HourHand, 125);

    ui_MinuteHand = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_MinuteHand, &ui_img_clockwise_min_png);
    lv_obj_set_width(ui_MinuteHand, LV_SIZE_CONTENT);   /// 18
    lv_obj_set_height(ui_MinuteHand, LV_SIZE_CONTENT);    /// 157
    lv_obj_set_x(ui_MinuteHand, -72);
    lv_obj_set_y(ui_MinuteHand, -71);
    lv_obj_set_align(ui_MinuteHand, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MinuteHand, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_MinuteHand, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_MinuteHand, 125);

    ui_SecondHand = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_SecondHand, &ui_img_clockwise_sec_png);
    lv_obj_set_width(ui_SecondHand, LV_SIZE_CONTENT);   /// 31
    lv_obj_set_height(ui_SecondHand, LV_SIZE_CONTENT);    /// 180
    lv_obj_set_x(ui_SecondHand, -72);
    lv_obj_set_y(ui_SecondHand, -79);
    lv_obj_set_align(ui_SecondHand, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_SecondHand, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_SecondHand, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_SecondHand, 100);

    ui_TopButton = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_TopButton, 50);
    lv_obj_set_height(ui_TopButton, 106);
    lv_obj_set_x(ui_TopButton, 109);
    lv_obj_set_y(ui_TopButton, 29);
    lv_obj_set_align(ui_TopButton, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_TopButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_blend_mode(ui_TopButton, LV_BLEND_MODE_MULTIPLY, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_TopButton, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MiddleButton = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_MiddleButton, 15);
    lv_obj_set_height(ui_MiddleButton, 15);
    lv_obj_set_x(ui_MiddleButton, 125);
    lv_obj_set_y(ui_MiddleButton, 30);
    lv_obj_set_align(ui_MiddleButton, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_MiddleButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MiddleButton, lv_color_hex(0x757070), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MiddleButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_MiddleButton, lv_color_hex(0x737173), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_MiddleButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BottomButton = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_BottomButton, 15);
    lv_obj_set_height(ui_BottomButton, 15);
    lv_obj_set_x(ui_BottomButton, 125);
    lv_obj_set_y(ui_BottomButton, 60);
    lv_obj_set_align(ui_BottomButton, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_BottomButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_BottomButton, lv_color_hex(0x737173), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BottomButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_BottomButton, lv_color_hex(0x737173), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_BottomButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel1 = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_Panel1, 15);
    lv_obj_set_height(ui_Panel1, 15);
    lv_obj_set_x(ui_Panel1, 125);
    lv_obj_set_y(ui_Panel1, 0);
    lv_obj_set_align(ui_Panel1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Panel1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_TopButton, ui_event_TopButton, LV_EVENT_ALL, NULL);

}
