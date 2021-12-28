/**
 * @file tuya_app_driver_led.c
 * @author lifan
 * @brief led driver source file
 * @version 1.0
 * @date 2021-06-28
 *
 * @copyright Copyright (c) tuya.inc 2021
 *
 */

#include "tuya_app_driver_led.h"
#include "gpio_8258.h"

/***********************************************************
************************micro define************************
***********************************************************/
/* Led pin */
#define P_LED1  GPIO_PB4    /* P26 */
#define P_LED2  GPIO_PB5    /* P24 */

/***********************************************************
***********************typedef define***********************
***********************************************************/

/***********************************************************
***********************variable define**********************
***********************************************************/

/***********************************************************
***********************function define**********************
***********************************************************/
/**
 * @brief led driver init
 * @param[in] none
 * @return none
 */
void led_init(void)
{
	gpio_set_func(P_LED1, AS_GPIO);
    gpio_set_output_en(P_LED1, 1);
    gpio_write(P_LED1, 1);
    gpio_set_func(P_LED2, AS_GPIO);
    gpio_set_output_en(P_LED2, 1);
    gpio_write(P_LED2, 1);
}

/**
 * @brief set led1 on or off
 * @param[in] b_on_off：led on / led off
 * @return none
 */
void set_led1(bool b_on_off)
{
    static bool s_last_status = 0;
    if (s_last_status != b_on_off) {
        if (b_on_off == ON) {
        	gpio_write(P_LED1, 0);
        } else {
        	gpio_write(P_LED1, 1);
        }
        s_last_status = b_on_off;
    }
}

/**
 * @brief set led2 on or off
 * @param[in] b_on_off：led on / led off
 * @return none
 */
void set_led2(bool b_on_off)
{
    static bool s_last_status = 0;
    if (s_last_status != b_on_off) {
        if (b_on_off == ON) {
        	gpio_write(P_LED2, 0);
        } else {
        	gpio_write(P_LED2, 1);
        }
        s_last_status = b_on_off;
    }
}
