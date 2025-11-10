/*
 * Copyright (C) 2025 UpbeatTech Inc. All Rights Reserved
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * This file contains code derived from software originally developed by LVGL Kft.
 *
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX short identifier: Apache-2.0
 */

/**
 * MIT License
 *
 * -----------------------------------------------------------------------------
 * Copyright (c) 2025 LVGL Kft
 * -----------------------------------------------------------------------------
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next paragraph)
 * shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */


/**
 * @file lv_win.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "../label/lv_label.h" //Mimi
#include "lv_win_private.h"
#include "../../core/lv_obj_class_private.h"
#include "../../../lvgl.h"
#if LV_USE_WIN

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void lv_win_constructor(const lv_obj_class_t * class_p, lv_obj_t * obj);

/**********************
 *  STATIC VARIABLES
 **********************/
const lv_obj_class_t lv_win_class = {
    .constructor_cb = lv_win_constructor,
    .width_def = LV_PCT(100),
    .height_def = LV_PCT(100),
    .base_class = &lv_obj_class,
    .instance_size = sizeof(lv_win_t),
    .name = "lv_win",
};
/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * lv_win_create(lv_obj_t * parent)
{
    LV_LOG_INFO("begin");
    lv_obj_t * obj = lv_obj_class_create_obj(&lv_win_class, parent);
    lv_obj_class_init_obj(obj);
    return obj;
}

lv_obj_t * lv_win_add_title(lv_obj_t * win, const char * txt)
{
    lv_obj_t * header = lv_win_get_header(win);
    lv_obj_t * title = lv_label_create(header);
    lv_label_set_long_mode(title, LV_LABEL_LONG_MODE_DOTS);
    lv_label_set_text(title, txt);
    lv_obj_set_flex_grow(title, 1);
    return title;
}

lv_obj_t * lv_win_add_button(lv_obj_t * win, const void * icon, int32_t btn_w)
{
    lv_obj_t * header = lv_win_get_header(win);
    lv_obj_t * btn = lv_button_create(header);
    lv_obj_set_size(btn, btn_w, LV_PCT(100));

    if(icon) {
        lv_obj_t * img = lv_image_create(btn);
        lv_image_set_src(img, icon);
        lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
    }

    return btn;
}

lv_obj_t * lv_win_get_header(lv_obj_t * win)
{
    return lv_obj_get_child(win, 0);
}

lv_obj_t * lv_win_get_content(lv_obj_t * win)
{
    return lv_obj_get_child(win, 1);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void lv_win_constructor(const lv_obj_class_t * class_p, lv_obj_t * obj)
{
    LV_UNUSED(class_p);
    lv_obj_t * parent = lv_obj_get_parent(obj);
    lv_obj_set_size(obj, lv_obj_get_width(parent), lv_obj_get_height(parent));
    lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_COLUMN);

    lv_obj_t * header = lv_obj_create(obj);
    lv_obj_set_size(header, LV_PCT(100), lv_display_get_dpi(lv_obj_get_display(obj)) / 2);
    lv_obj_set_flex_flow(header, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(header, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    lv_obj_t * cont = lv_obj_create(obj);
    lv_obj_set_flex_grow(cont, 1);
    lv_obj_set_width(cont, LV_PCT(100));
}

#endif
