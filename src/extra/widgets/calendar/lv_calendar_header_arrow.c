/**
 * @file lv_calendar_header_arrow.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_calendar_header_arrow.h"
#if LV_USE_CALENDAR_HEADER_ARROW

#include "lv_calendar.h"
#include "../../layouts/flex/lv_flex.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void month_event_cb(lv_obj_t * btn, lv_event_t e);

/**********************
 *  STATIC VARIABLES
 **********************/
static const char * month_names_def[12] = LV_CALENDAR_DEFAULT_MONTH_NAMES;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * lv_calendar_header_arrow_create(lv_obj_t * parent, lv_obj_t * calendar, lv_coord_t btn_size)
{
    lv_obj_t * header = lv_obj_create(parent, NULL);

    const lv_calendar_date_t * cur_date = lv_calendar_get_showed_date(calendar);

    lv_coord_t w = lv_obj_get_width(calendar);
    lv_obj_set_size(header,  w, LV_SIZE_AUTO);
    lv_obj_set_layout(header, &lv_flex_center_row);

    lv_obj_t * mo_prev = lv_btn_create(header, NULL);
    lv_obj_set_style_content_text(mo_prev,  LV_PART_MAIN, LV_STATE_DEFAULT,  LV_SYMBOL_LEFT);
    lv_obj_set_size(mo_prev, btn_size, btn_size);
    lv_obj_add_event_cb(mo_prev, month_event_cb, calendar);

    lv_obj_t * label = lv_label_create(header, NULL);
    lv_label_set_long_mode(label, LV_LABEL_LONG_SROLL_CIRC);
    lv_obj_set_style_text_align(label,  LV_PART_MAIN, LV_STATE_DEFAULT,  LV_TEXT_ALIGN_CENTER);
    lv_obj_set_flex_grow(label, 1);
    lv_label_set_text_fmt(label, "%d %s", cur_date->year, month_names_def[cur_date->month - 1]);

    lv_obj_t * mo_next = lv_btn_create(header, NULL);
    lv_obj_set_style_content_text(mo_next,  LV_PART_MAIN, LV_STATE_DEFAULT, LV_SYMBOL_RIGHT);
    lv_obj_set_size(mo_next, btn_size, btn_size);
    lv_obj_add_event_cb(mo_next, month_event_cb, calendar);

    return header;
}

/**********************
 *  STATIC FUNCTIONS
 **********************/

static void month_event_cb(lv_obj_t * btn, lv_event_t e)
{
    if(e != LV_EVENT_CLICKED) return;

    lv_obj_t * header = lv_obj_get_parent(btn);
    lv_obj_t * calendar = lv_event_get_user_data();

    const lv_calendar_date_t * d;
    d = lv_calendar_get_showed_date(calendar);
    lv_calendar_date_t newd = *d;

    /*The last child is the right button*/
    if(lv_obj_get_child(header, 0) == btn) {
        if(newd.month == 1) {
            newd.month = 12;
            newd.year --;
        } else {
            newd.month --;
        }
    } else {
        if(newd.month == 12) {
            newd.month = 1;
            newd.year ++;
        } else {
            newd.month ++;
        }
    }

    lv_calendar_set_showed_date(calendar, &newd);

    lv_obj_t * label = lv_obj_get_child(header, 1);
    lv_label_set_text_fmt(label, "%d %s", newd.year, month_names_def[newd.month - 1]);
}

#endif /*LV_USE_CALENDAR_HEADER_ARROW*/
