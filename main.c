
#include <stdint.h>
#include <string.h>
#include "nordic_common.h"
#include "nrf.h"
#include "nrf_sdm.h"
#include "app_error.h"
#include "ble.h"
#include "ble_err.h"
#include "ble_hci.h"
#include "ble_srv_common.h"
#include "ble_advdata.h"
#include "ble_advertising.h"
#include "ble_bas.h"
#include "ble_hrs.h"
#include "ble_dis.h"
#include "ble_conn_params.h"
#include "sensorsim.h"
#include "nrf_sdh.h"
#include "nrf_sdh_ble.h"
#include "nrf_sdh_soc.h"
#include "app_timer.h"
#include "bsp_btn_ble.h"
#include "peer_manager.h"
#include "peer_manager_handler.h"
#include "fds.h"
#include "nrf_ble_gatt.h"
#include "nrf_ble_lesc.h"
#include "nrf_ble_qwr.h"
#include "ble_conn_state.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_drv_clock.h"

#include "HY_BLE.h"
#include "HY_Framework.h"

#include "Message.h"

#include "nrf_gpio.h"
#include "nrfx_gpiote.h"
#include "HY_GPIOTE.h"


// when timeout run one time
static void HY_BLE_Update_HeartRate_Event(void){

  static heart=60;

  NRF_LOG_INFO("HY_BLE_Update_HeartRate_Event");
  ble_hearrate_update(heart++);

  if (heart > 200)
    heart=60;
}



static void Timeout_1000ms_Event(int prm0,int prm1){
    NRF_LOG_INFO("Timeout_1000ms_Event");
    HY_BLE_Update_HeartRate_Event();

}

static void Timeout_20ms_Event(int prm0,int prm1){
    //NRF_LOG_INFO("20ms")
}



int main(void){
    
    int nEvent = INVALID_EVENT;  //-1
    Message_Init();
    HY_initFramework();
    TIM_Init();
    ble_init();
    HY_gpio_init();

        

    TIM_RegisterHandler(Timeout_1000ms_Event, 1000);
    TIM_RegisterHandler(Timeout_20ms_Event, 20);
    

      while (1)
      {
            while (ProcessMessage());

            ble_hy_idele_state_handle();

      }
      
        
}





