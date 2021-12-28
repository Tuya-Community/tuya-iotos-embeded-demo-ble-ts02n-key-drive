
/**
 * @file tuya_app_ts02n_key.h
 * @author lifan
 * @brief ts02n key application header file
 * @version 1.0
 * @date 2021-06-28
 *
 * @copyright Copyright (c) tuya.inc 2021
 *
 */

#ifndef __TUYA_APP_TS02N_KEY_H__
#define __TUYA_APP_TS02N_KEY_H__

#include "tuya_ble_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************
************************micro define************************
***********************************************************/

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
 * @brief ts02n key init
 * @param[in] none
 * @return none
 */
void tuya_app_ts02n_key_init(void);

/**
 * @brief main loop of ts02n key
 * @param[in] time_inc：time increment
 * @return none
 */
void tuya_app_ts02n_key_loop(void);

/**
 * @brief ble connect status change handler of ts02n key
 * @param[in] status: ble connect status
 * @return none
 */
void tuya_app_ts02n_key_ble_connect_status_change_handler(tuya_ble_connect_status_t status);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TUYA_APP_TS02N_KEY_H__ */
