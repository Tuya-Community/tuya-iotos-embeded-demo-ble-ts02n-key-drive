/**
 * @file tuya_app_ts02n_key.c
 * @author lifan
 * @brief ts02n key application source file
 * @version 1.0
 * @date 2021-06-28
 *
 * @copyright Copyright (c) tuya.inc 2021
 *
 */

#include "tuya_app_ts02n_key.h"
#include "tuya_app_driver_led.h"
#include "tuya_app_driver_ts02n_key.h"
#include "tuya_ble_api.h"
#include "tuya_ble_log.h"
#include "gpio_8258.h"
#include "tuya_ble_mutli_tsf_protocol.h"

/***********************************************************
************************micro define************************
***********************************************************/
/* DP ID */
#define DP_ID_KEY                   101
/* DP TYPE */
#define DP_TYPE_KEY                 DT_VALUE

/* Key status */
#define KEY_STA_NO_PRESS            0x00
#define KEY_STA_KEY1_SHORT_PRESS    0x01
#define KEY_STA_KEY2_SHORT_PRESS    0x02
#define KEY_STA_KEY1_LONG_PRESS     0x03
#define KEY_STA_KEY2_LONG_PRESS     0x04

/***********************************************************
***********************typedef define***********************
***********************************************************/
/* DP data struct */
typedef struct {
    uint8_t id;
    dp_type type;
    uint8_t len;
    uint8_t value;
} DP_DATA_T;

/***********************************************************
***********************variable define**********************
***********************************************************/
/* Key callback function */
void key1_short_press_cb_fun();
void key2_short_press_cb_fun();
void key1_long_press_cb_fun();
void key2_long_press_cb_fun();

/* User key define */
TS02N_KEY_DEF_T user_ts02n_key_def_s = {
    .key1_pin = GPIO_PC2,           /* P8 */
    .key2_pin = GPIO_PC3,           /* P7 */
    .key1_short_press_cb = key1_short_press_cb_fun,
    .key2_short_press_cb = key2_short_press_cb_fun,
    .key1_long_press_cb = key1_long_press_cb_fun,
    .key2_long_press_cb = key2_long_press_cb_fun,
    .key1_long_press_time = 5000,   /* 5s */
    .key2_long_press_time = 2000,   /* 2s */
    .scan_time = 10,                /* 10ms */
};

/* DP data value */
uint8_t g_key_status = KEY_STA_NO_PRESS;

/* Flag */
uint8_t g_err_fg = 0;

/***********************************************************
***********************function define**********************
***********************************************************/
/**
 * @brief get dp type
 * @param[in] dp_id：DP ID
 * @return type：DP type
 */
static uint8_t get_dp_type(uint8_t dp_id)
{
    dp_type type = 0;
    switch (dp_id) {
    case DP_ID_KEY:
        type = DP_TYPE_KEY;
        break;
    default:
        break;
    }
    return type;
}

/**
 * @brief report one dp data of smart kettle
 * @param[in] dp_id：DP ID
 * @return none
 */
static void report_one_kettle_dp_data(uint8_t dp_id, uint8_t dp_value)
{
    DP_DATA_T dp_data_s;
    dp_data_s.id = dp_id;
    dp_data_s.type = get_dp_type(dp_id);
    dp_data_s.len = 0x01;
    dp_data_s.value = dp_value;
    tuya_ble_dp_data_report((uint8_t *)&dp_data_s, sizeof(DP_DATA_T));
}

/**
 * @brief key1 short press handler
 * @param[in] none
 * @return none
 */
void key1_short_press_cb_fun()
{
    set_led1(OFF);
    g_key_status = KEY_STA_KEY1_SHORT_PRESS;
    report_one_kettle_dp_data(DP_ID_KEY, KEY_STA_KEY1_SHORT_PRESS);
}

/**
 * @brief key1 long press handler
 * @param[in] none
 * @return none
 */
void key1_long_press_cb_fun()
{
    set_led1(ON);
    g_key_status = KEY_STA_KEY1_LONG_PRESS;
    report_one_kettle_dp_data(DP_ID_KEY, KEY_STA_KEY1_LONG_PRESS);
}

/**
 * @brief key2 short press handler
 * @param[in] none
 * @return none
 */
void key2_short_press_cb_fun()
{
    set_led2(OFF);
    g_key_status = KEY_STA_KEY2_SHORT_PRESS;
    report_one_kettle_dp_data(DP_ID_KEY, KEY_STA_KEY2_SHORT_PRESS);
}

/**
 * @brief key2 long press handler
 * @param[in] none
 * @return none
 */
void key2_long_press_cb_fun()
{
    set_led2(ON);
    g_key_status = KEY_STA_KEY2_LONG_PRESS;
    report_one_kettle_dp_data(DP_ID_KEY, KEY_STA_KEY2_LONG_PRESS);
}

/**
 * @brief ts02n key init
 * @param[in] none
 * @return none
 */
void tuya_app_ts02n_key_init(void)
{
    if (ts02n_key_init(&user_ts02n_key_def_s) != KEY_INIT_OK) {
        g_err_fg = 1;
        TUYA_APP_LOG_ERROR("ts02n key init failed");
        return;
    }
    led_init();
}

/**
 * @brief main loop of ts02n key
 * @param[in] time_inc：time increment
 * @return none
 */
void tuya_app_ts02n_key_loop(void)
{
    if (!g_err_fg) {
        ts02n_key_loop();
    }
}

/**
 * @brief ble connect status change handler of ts02n key
 * @param[in] status: ble connect status
 * @return none
 */
void tuya_app_ts02n_key_ble_connect_status_change_handler(tuya_ble_connect_status_t status)
{
    if (status == BONDING_CONN) {
        report_one_kettle_dp_data(DP_ID_KEY, g_key_status);
    }
}
