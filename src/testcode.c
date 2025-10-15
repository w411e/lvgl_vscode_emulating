/**
 * @file testcode.c
 *
 */
#include "testcode.h"

/**
 * Event handler for button clicking
 */
static void btn_event_cb_mod(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e); // get event code
    lv_obj_t * btn = lv_event_get_target_obj(e); // event object
    button * data = lv_obj_get_user_data(btn);
    if(code == LV_EVENT_CLICKED) { // certain event
        //static uint8_t cnt = 0; // no 0 reset because of static
        data->cnt++;

        /*Get the first child of the button which is the label and change its text*/
        lv_obj_t * label = lv_obj_get_child(btn, 0);
        lv_label_set_text_fmt(label, "%s: %d", data->buttonName, data->cnt);
    }
}

static void btn_event_cb_2(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e); // get event code
    lv_obj_t * btn = lv_event_get_target_obj(e); // event object
    button * data = lv_obj_get_user_data(btn);
    lv_obj_t * label = lv_obj_get_child(btn, 0);
    switch(code){
        case LV_EVENT_PRESSED: // certain event
            data->cnt++;

            /*Get the first child of the button which is the label and change its text*/
            lv_label_set_text_fmt(label, "%d", data->cnt);
            break;
        case LV_EVENT_LONG_PRESSED:
            data->cnt --;
        case LV_EVENT_LONG_PRESSED_REPEAT: // certain event
            data->cnt += 10;

            /*Get the first child of the button which is the label and change its text*/
            lv_label_set_text_fmt(label, "%d", data->cnt);
            break;
    }
}

static void btn_event_cb_sw_src(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e); // get event code
    lv_obj_t * btn = lv_event_get_target_obj(e); // event object
    lv_obj_t * data = lv_obj_get_user_data(btn);
    if(code == LV_EVENT_CLICKED) // certain event
    {
        // switch between screens
        lv_screen_load_anim(data, LV_SCREEN_LOAD_ANIM_MOVE_RIGHT, 200, 100, 0);
    }
}

void init_custom_style(lv_style_t * style){
    lv_style_init(style);
    lv_style_set_arc_rounded(style, false);
    lv_style_set_bg_color(style, lv_color_hex(RED));
    lv_style_set_outline_color(style, lv_color_hex(BLUE));
    lv_style_set_shadow_width(style, 3);
    lv_style_set_pad_all(style, 3);
    lv_style_set_width(style, 100);
    lv_style_set_height(style, 50);
    lv_style_set_border_color(style, lv_color_hex(DEF_2));
    lv_style_set_text_color(style, lv_color_hex(DEF));
}

/**
 * Create a button with a label and react on click event.
 */
void lv_example_get_started_2_mod(void)
{
    // def screen / setup with default
    lv_obj_t * screen_def = lv_screen_active(); // default screen, start
    // def second screen / setup with custom style
    lv_obj_t * screen_2 = lv_obj_create(NULL);  // other screen, loaded via button
    lv_style_t style_default;
    // lv_obj_remove_style_all(screen_2); // remove all styles from second screen
    lv_obj_set_style_layout(screen_2, LV_LAYOUT_FLEX, LV_PART_MAIN); // set flex flow not grid
    lv_obj_set_style_flex_flow(screen_2, LV_FLEX_FLOW_ROW, LV_PART_MAIN); // set children in row
    lv_obj_set_style_flex_grow(screen_2, 0, LV_PART_MAIN); // dont let grow
    lv_obj_set_style_flex_main_place(screen_2, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN); // flex placement alignment
    //lv_obj_set_style_border_width(screen_2, 5, LV_PART_MAIN);
    //lv_obj_set_style_border_color(screen_2, lv_color_hex(WHITE), LV_PART_MAIN);
    // lv_obj_set_style_pad_all(screen_2, 5, LV_PART_MAIN); // set distance between widgets/screen
    // lv_obj_set_style_text_color(screen_2, lv_color_hex(DEF), LV_PART_MAIN);
    // lv_obj_set_style_text_outline_stroke_color(screen_2, lv_color_hex(DEF_2), LV_PART_MAIN);
    // lv_obj_set_style_bg_color(screen_2, lv_color_hex(WHITE), LV_PART_MAIN);
    init_custom_style(&style_default);
    lv_obj_add_style(screen_2, &style_default, 0);


    // button 1
    lv_obj_t * btn1 = lv_button_create(lv_screen_active());     /*Add a button the current screen*/
    lv_obj_set_pos(btn1, 10, 10);                            /*Set its position*/
    lv_obj_set_size(btn1, 120, 50);                          /*Set its size*/
    lv_obj_set_style_text_color(btn1, lv_color_hex(BLACK), LV_PART_MAIN);
    lv_obj_set_style_border_color(btn1, lv_color_hex(YELLOW), LV_PART_MAIN);
    lv_obj_set_style_border_width(btn1, 5, LV_PART_MAIN);
    static button b1;
    lv_strcpy(b1.buttonName, "Button_1");
    b1.cnt = 0;
    lv_obj_set_user_data(btn1, &b1);
    lv_obj_add_event_cb(btn1, btn_event_cb_mod, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/

    lv_obj_t * label1 = lv_label_create(btn1);          /*Add a label to the button*/
    lv_label_set_text(label1, b1.buttonName);                     /*Set the labels text*/
    lv_obj_center(label1);

    // button 2
    lv_obj_t *btn2 = lv_button_create(lv_screen_active());
    lv_obj_set_pos(btn2, 10, 70);
    lv_obj_set_size(btn2, 120, 50);
    static button b2;
    b2.cnt = 0;
    lv_strcpy(b2.buttonName, "0");
    lv_obj_set_user_data(btn2, &b2);
    lv_obj_add_event_cb(btn2, btn_event_cb_2, LV_EVENT_ALL, NULL);

    lv_obj_t *label2 = lv_label_create(btn2);
    lv_label_set_text(label2, b2.buttonName);
    lv_obj_set_style_text_color(label2, lv_color_hex(MAGENTA), LV_PART_MAIN);
    lv_obj_center(label2);

    lv_obj_t *label2_1 = lv_label_create(lv_screen_active());
    lv_label_set_text(label2_1, "Button_2");
    lv_obj_set_style_text_color(label2_1, lv_color_hex(FOREST), LV_PART_MAIN);
    lv_obj_align_to(label2_1, btn2, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);

    // button 3
    lv_obj_t * btn3 = lv_button_create(lv_screen_active());
    lv_obj_set_pos(btn3, 10, 150);
    lv_obj_set_size(btn3, 160, 50);
    lv_obj_set_style_bg_color(btn3, lv_color_hex(WHITE), LV_PART_MAIN);
    lv_obj_add_event_cb(btn3, btn_event_cb_sw_src, LV_EVENT_ALL, NULL);

    lv_obj_t *label3 = lv_label_create(btn3);
    lv_label_set_text(label3, "Switch to Scr 2");
    lv_obj_set_style_text_color(label3, lv_color_hex(GREEN), LV_PART_MAIN);
    lv_obj_center(label3);

    // button 4 (second screen)
    lv_obj_t * btn4 = lv_button_create(screen_2);
    //lv_obj_set_pos(btn4, 10, 150);
    lv_obj_add_style(btn4, &style_default, 0);
    lv_obj_add_event_cb(btn4, btn_event_cb_sw_src, LV_EVENT_ALL, NULL);

    lv_obj_t * btn5 = lv_button_create(screen_2);
    lv_obj_add_style(btn5, &style_default, 0);
    lv_obj_add_event_cb(btn5, btn_event_cb_mod, LV_EVENT_ALL, NULL);

    lv_obj_t * btn6 = lv_button_create(screen_2);
    lv_obj_add_style(btn6, &style_default, 0);
    lv_obj_add_event_cb(btn6, btn_event_cb_mod, LV_EVENT_ALL, NULL);

    lv_obj_t *label4 = lv_label_create(btn4);
    lv_obj_add_style(label4, &style_default, 0);
    lv_label_set_text(label4, "Switch to Scr 1");
    //lv_obj_set_style_text_color(label4, lv_color_hex(GREEN), LV_PART_MAIN);
    // lv_obj_center(label4);

    // button 3 to screen_2, button 4 to screen_def
    lv_obj_set_user_data(btn3, screen_2);
    lv_obj_set_user_data(btn4, screen_def);
}