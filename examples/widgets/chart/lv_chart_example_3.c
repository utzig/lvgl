#include "../../../lvgl.h"
#if LV_USE_CHART

static void event_cb(lv_obj_t * chart, lv_event_t e)
{
    if(e == LV_EVENT_DRAW_PART_BEGIN) {
        lv_obj_draw_hook_dsc_t * hook_dsc = lv_event_get_param();
        if(hook_dsc->part == LV_PART_MARKER && hook_dsc->sub_part_id == LV_CHART_AXIS_X) {
            const char * month[] = {"Jan", "Febr", "March", "Apr", "May", "Jun", "July", "Aug", "Sept", "Oct", "Nov", "Dec"};
            lv_snprintf(hook_dsc->text, sizeof(hook_dsc->text), "%s", month[hook_dsc->id]);
        }
    }
}

/**
 * Add ticks and labels to the axis and demonstrate scrolling
 */
void lv_ex_chart_3(void)
{
    /*Create a chart*/
    lv_obj_t * chart;
    chart = lv_chart_create(lv_scr_act(), NULL);
    lv_obj_set_size(chart, 200, 150);
    lv_obj_align(chart, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_chart_set_type(chart, LV_CHART_TYPE_BAR);
    lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, 100);
    lv_chart_set_range(chart, LV_CHART_AXIS_SECONDARY_Y, 0, 400);
    lv_chart_set_point_count(chart, 12);
    lv_obj_add_event_cb(chart, event_cb, NULL);

    /*Add ticks and label to every axis*/
    lv_chart_set_axis_tick(chart, LV_CHART_AXIS_X, 10, 5, 12, 3, true, 40);
    lv_chart_set_axis_tick(chart, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 6, 2, true, 50);
    lv_chart_set_axis_tick(chart, LV_CHART_AXIS_SECONDARY_Y, 10, 5, 3, 4, true, 50);

    /*Zoom in a little in X*/
    lv_chart_set_zoom_x(chart, 800);

    /*Add two data series*/
    lv_chart_series_t * ser1 = lv_chart_add_series(chart, LV_COLOR_RED, LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_series_t * ser2 = lv_chart_add_series(chart, LV_COLOR_GREEN, LV_CHART_AXIS_SECONDARY_Y);

    /*Set the next points on 'ser1'*/
    lv_chart_set_next_value(chart, ser1, 31);
    lv_chart_set_next_value(chart, ser1, 66);
    lv_chart_set_next_value(chart, ser1, 10);
    lv_chart_set_next_value(chart, ser1, 89);
    lv_chart_set_next_value(chart, ser1, 63);
    lv_chart_set_next_value(chart, ser1, 56);
    lv_chart_set_next_value(chart, ser1, 32);
    lv_chart_set_next_value(chart, ser1, 35);
    lv_chart_set_next_value(chart, ser1, 57);
    lv_chart_set_next_value(chart, ser1, 85);
    lv_chart_set_next_value(chart, ser1, 22);
    lv_chart_set_next_value(chart, ser1, 58);

    lv_coord_t * ser2_array =  lv_chart_get_array(chart, ser2);
    /*Directly set points on 'ser2'*/
    ser2_array[0] = 92;
    ser2_array[1] = 71;
    ser2_array[2] = 61;
    ser2_array[3] = 15;
    ser2_array[4] = 21;
    ser2_array[5] = 35;
    ser2_array[6] = 35;
    ser2_array[7] = 58;
    ser2_array[8] = 31;
    ser2_array[9] = 53;
    ser2_array[10] = 33;
    ser2_array[11] = 73;

    lv_chart_refresh(chart); /*Required after direct set*/
}

#endif