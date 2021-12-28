/**
 * @file tuya_app_driver_led.h
 * @author lifan
 * @brief led driver header file
 * @version 1.0
 * @date 2021-06-28
 *
 * @copyright Copyright (c) tuya.inc 2021
 *
 */


#ifndef __TUYA_APP_DRIVER_LED_H__
#define __TUYA_APP_DRIVER_LED_H__

#include "tuya_ble_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************
************************micro define************************
***********************************************************/
#define OFF 0
#define ON  (!OFF)

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
void led_init(void);

/**
 * @brief set led1 on or off
 * @param[in] b_on_off：led on / led off
 * @return none
 */
void set_led1(bool b_on_off);

/**
 * @brief set led2 on or off
 * @param[in] b_on_off：led on / led off
 * @return none
 */
void set_led2(bool b_on_off);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TUYA_APP_DRIVER_LED_H__ */
