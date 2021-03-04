// Nordic libraries
#include <ble.h>
#include <gap.h>
#include <rng.h>
#include <timer.h>

//standard libraries
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//#include "ble_nus.h"
//#include "nrf.h"
#include <ble_advdata.h>
#include <nordic_common.h>
//#include <nrf_error.h>

//#include <eddystone.h>
//simple ble
// From the simple_ble library in https://github.com/lab11/nrf5x-base
// Included in the libnrfserialization.a library.

#include <button.h>
#include <led.h>

#include <simple_ble.h>
#include <simple_adv.h>
//#include <nrf51_serialization.h>
//RTOS tock
#include <console.h>
#include <tock.h>




// Sizes in bytes
#define DEVICE_NAME_SIZE 13
#define UUIDS_SIZE 4
#define MANUFACTURER_DATA_SIZE 2
#define FAKE_EVENT_DATA_SIZE 2


//callback for switch (
static void button_callback(int btn_num,
                                int val,
                                __attribute__ ((unused)) int arg2,
                                __attribute__ ((unused)) void *ud) {
  if (val == 1) {
    led_toggle(btn_num);
  }
}

/*******************************************************************************
 * MAIN
 ******************************************************************************/

 /*******************************************************************************
  * BLE
  ******************************************************************************/

 uint16_t conn_handle = BLE_CONN_HANDLE_INVALID;

 // Intervals for advertising and connections
 simple_ble_config_t ble_config = {
   .platform_id       = 0x00,                // used as 4th octect in device BLE address
   .device_id         = DEVICE_ID_DEFAULT,
   .adv_name          = "opossum-pouch",
   .adv_interval      = MSEC_TO_UNITS(500, UNIT_0_625_MS),
   .min_conn_interval = MSEC_TO_UNITS(1000, UNIT_1_25_MS),
   .max_conn_interval = MSEC_TO_UNITS(1250, UNIT_1_25_MS)
 };

 void app_error_fault_handler(__attribute__ ((unused)) uint32_t error_code,
                              __attribute__ ((unused)) uint32_t line_num,
                              __attribute__ ((unused)) uint32_t info) {
   // Ignore errors. With serialization, these happen because a packet
   // was framed wrong or corrupted between the nRF and the main processor.
   // The application can continue.
 }

 // State for UART library.
 //static ble_nus_t m_nus;

 void ble_address_set (void) {
   // nop
   // Need to redefine this function so that we do not try to set the address
   // on the main processor.
 }

 // Called when each advertisement is received.
void ble_evt_adv_report (ble_evt_t* p_ble_evt) {
  // Follow the nRF SDK data structures to get to the advertising data.
  // More doc here:
  // http://infocenter.nordicsemi.com/topic/com.nordic.infocenter.s130.api.v2.0.0/structble__gap__evt__adv__report__t.html
  ble_gap_evt_adv_report_t* adv = (ble_gap_evt_adv_report_t*) &p_ble_evt->evt.gap_evt.params.adv_report;

  // Print some details about the discovered advertisement.
  printf("Recv Advertisement: [%02x:%02x:%02x:%02x:%02x:%02x] RSSI: %d, Len: %d\n",
         adv->peer_addr.addr[5], adv->peer_addr.addr[4], adv->peer_addr.addr[3],
         adv->peer_addr.addr[2], adv->peer_addr.addr[1], adv->peer_addr.addr[0],
         adv->rssi, adv->dlen);

  // Also toggle the first LED.
  //led_toggle(0);
}


 void ble_evt_user_handler (ble_evt_t* p_ble_evt) {
   ble_gap_conn_params_t conn_params;
   memset(&conn_params, 0, sizeof(conn_params));
   conn_params.min_conn_interval = ble_config.min_conn_interval;
   conn_params.max_conn_interval = ble_config.max_conn_interval;
   conn_params.slave_latency     = SLAVE_LATENCY;
   conn_params.conn_sup_timeout  = CONN_SUP_TIMEOUT;

   switch (p_ble_evt->header.evt_id) {
     case BLE_GAP_EVT_CONN_PARAM_UPDATE:
       // just update them right now
       sd_ble_gap_conn_param_update(0, &conn_params);
       break;
   }
 }

 // This gets called with the serial data from the BLE central.
// static void nus_data_handler(ble_nus_t* p_nus, uint8_t* p_data, uint16_t length) {
//   UNUSED_PARAMETER(p_nus);

   // In this app, just print it to the console.
   //putnstr((char*) p_data, length);
 //}

 void ble_evt_connected(ble_evt_t* p_ble_evt) {
   ble_common_evt_t *common = (ble_common_evt_t*) &p_ble_evt->evt;
   conn_handle = common->conn_handle;

//   ble_nus_on_ble_evt(&m_nus, p_ble_evt);
 }

 void ble_evt_disconnected(ble_evt_t* p_ble_evt) {
   conn_handle = BLE_CONN_HANDLE_INVALID;

//   ble_nus_on_ble_evt(&m_nus, p_ble_evt);
 }

 // On a write, need to forward that to NUS library.
 void ble_evt_write(ble_evt_t* p_ble_evt) {
//   ble_nus_on_ble_evt(&m_nus, p_ble_evt);
 }

 void ble_error (uint32_t error_code) {
   printf("BLE ERROR: Code = %d\n", (int)error_code);
 }

 void services_init (void) {
   uint32_t err_code = 0;
   //ble_nus_init_t nus_init;
   //memset(&nus_init, 0, sizeof(nus_init));
   //nus_init.data_handler = nus_data_handler;
   //err_code = ble_nus_init(&m_nus, &nus_init);
   APP_ERROR_CHECK(err_code);
 }

/*
void _start(void* text_start, void* mem_start, void* memory_len, void* app_heap_break){
  main();
  while(1) {
    yield();
  }
}
*/
 /*******************************************************************************
  * MAIN
  ******************************************************************************/

 int main (void) {
   printf("[BLE] UART over BLE\n");
   // init switch
   button_subscribe(button_callback, NULL);
   int count = button_count();
   for (int i = 0; i < count; i++){
     button_enable_interrupt(i);
   }


   // Setup BLE
   conn_handle = simple_ble_init(&ble_config)->conn_handle;

   // Advertise the UART service
   ble_uuid_t adv_uuid = {0x0001, BLE_UUID_TYPE_VENDOR_BEGIN};
   simple_adv_service(&adv_uuid);
   // Scan for advertisements.
   simple_ble_scan_start();


  int err;
  printf("Opossum Pouch Advertiing\n");

  // declarations of variables to be used in this BLE example application
  uint16_t advertising_interval_ms = 300;
  uint8_t device_name[]            = "opossum pouch";
  uint16_t uuids[]                 = {0x1800, 0x1805};
  uint8_t manufacturer_data[]      = {0x13, 0x37};
  uint8_t fake_event_data[]  = {0x00, 0x00};

  static uint8_t adv_data_buf[ADV_DATA_MAX_SIZE];

  // configure advertisement interval to 300ms
  // configure LE only and discoverable
  printf(" - Initializing BLE... %s\n", device_name);
  AdvData_t adv_data = gap_adv_data_new(adv_data_buf, sizeof(adv_data_buf));

  gap_add_flags(&adv_data, LE_GENERAL_DISCOVERABLE | BREDR_NOT_SUPPORTED);

  // configure device name as TockOS
  printf(" - Setting the device name... %s\n", device_name);
  err = gap_add_device_name(&adv_data, device_name, DEVICE_NAME_SIZE);
  if (err < TOCK_SUCCESS)
    printf("ble_advertise_name, error: %s\r\n", tock_strerror(err));

  // configure list of UUIDs */
  printf(" - Setting the device UUID...\n");
  err = gap_add_service_uuid16(&adv_data, uuids, UUIDS_SIZE);
  if (err < TOCK_SUCCESS)
    printf("ble_advertise_uuid16, error: %s\r\n", tock_strerror(err));

  // configure manufacturer data
  printf(" - Setting manufacturer data...\n");
  err = gap_add_manufacturer_specific_data(&adv_data, manufacturer_data,
                                           MANUFACTURER_DATA_SIZE);
  if (err < TOCK_SUCCESS)
    printf("ble_advertise_manufacturer_specific_data, error: %s\r\n",
           tock_strerror(err));

  // configure service data
  printf(" - Setting service data...\n");
  err = gap_add_service_data(&adv_data, uuids[1], fake_event_data,
                             FAKE_EVENT_DATA_SIZE);
  if (err < TOCK_SUCCESS)
    printf("ble_advertise_service_data, error: %s\r\n", tock_strerror(err));

  // start advertising
  printf(" - Begin advertising! %s\n", device_name);
  err = ble_start_advertising(ADV_NON_CONN_IND, adv_data.buf, adv_data.offset, advertising_interval_ms);
  if (err < TOCK_SUCCESS)
    printf("ble_start_advertising, error: %s\r\n", tock_strerror(err));

  // configuration complete
  printf("Now advertising every %d ms as '%s'\n", advertising_interval_ms,
         device_name);
  return 0;
}


int raw_init(void){
    //int8_t m_random_vector[VECTOR_LENGTH];            // Result buffer.
    //uint8_t m_min[VECTOR_LENGTH] = {0x00, 0x00, 0xFF}; // Lower bound as big-endian.
    //uint8_t m_max[VECTOR_LENGTH] = {0x00, 0xFF, 0xFF}; // Upper bound as big-endian.
    // Initialize crypto library.
    //ret_val = nrf_crypto_init();
    //APP_ERROR_CHECK(ret_val);
    // Generate a random vector of specified length.
    //ret_val = nrf_crypto_rng_vector_generate(m_random_vector, VECTOR_LENGTH);
    //APP_ERROR_CHECK(ret_val);
    // Generate a constrained random vector of specified length.
    //ret_val = nrf_crypto_rng_vector_generate_in_range(m_random_vector,
    //                                            m_min,
    //                                            m_max,
    //                                            VECTOR_LENGTH);
    //APP_ERROR_CHECK(ret_val);
    unsigned char device_name[] = "OpossumPouchInit";
    uint8_t adata[ADV_DATA_MAX_SIZE]; // 31
    memset(adata,0x00,sizeof(adata));
    adata[0]=30;
    adata[1]=BLE_GAP_AD_TYPE_MANUFACTURER_SPECIFIC_DATA;
    rng_sync(&adata[2],29,29);
    AdvData_t rand_adv_data = gap_adv_data_new(adata,sizeof(adata));
    return gap_add_device_name(&rand_adv_data,device_name, sizeof(device_name)-1);
    //retv == sd_ble_gap_adv_data_set(adata,sizeof(adata),NULL,0);
}

void advertising_init(void){

    //static unsigned char advdata;
    //memset(&advdata,0x00,sizeof(advdata));
    //advdata.flags = BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE;
    //ble_adv_modes_config_t options = {0};
    //options.ble_adv_fast_enabled == BLE_ADV_FAST_ENABLED;
  //options.ble_adv_fast_interval = APP_ADV_INTERVAL;
  //options.ble_adv_fast_timeout  = APP_ADV_TIMEOUT_IN_SECONDS;
  //err_code = ble_advertising_init(&advdata, NULL, &options, on_adv_evt, NULL);
  ///APP_ERROR_CHECK(err_code);

  //uint8_t adv_data[13] = {0};
  uint8_t sr_data[20] = {0};

    // flags for discoverable/connectable
    static unsigned char aadata = {
      0x02, // ad field length = 2 bytes
      0x01,   // ad field type = 0x01 [Flags)
      0x06, // flags = 0x06, connectable/undirected
    // tx power field advertisement, iOS apps may need this
      0x02, // ad field length = 2 bytes
      0x0a,    // ad field type = 0x0A [TX Power)
      0x03, // TX power in dBm
  // NOTE: TX power is a signed 8-bit value, and is not changed automatically
    // when using "hardware_set_txpower[<power>)". This may be anywhere from -23
    // to +3 based on your settings. Negative values may be converted to two's
    // complement form by adding 256, so for example -23 dBm would be 233 or 0xE9.

    // custom manufacturer
      0x06, // ad field length = 5 bytes [arbitrary, maybe more or less but minimum 3)
      0xff, // ad field type = 0xFF [Manufacturer Specific Data)
      0xff, // unknown/prototype Company Identifier Code - octet 2
      0xff, // unknown/prototype Company Identifier Code - octet 1
      0xb1, // custom data byte //1 [can be anything)
      0xb2, // custom data byte //2 [can be anything)
      0xb3, // custom data byte //3 (can be anything)
    // NOTE: manufacturer data fields should contain the Company Identifier Code
    // in order to stay within BT 4.0 spec. You should also ideally obtain an
    // an official Company Identifier Code, but 0xFFFF is suitable for development.
    // (this is why the minimum ad field length for this is 3, so the CIC fits)
    0x08,  //length of name data
    0x09,  //complete local name
    'O','p','o','s','s','u','m',
    0xe, // Length of this data
    0x24, // URI
    0x17, // 'https:'
    '/', '/', 't', 'o', 'c', 'k', 'o', 's', '.', 'o', 'r', 'g'
    // More bytes are possible here, but not necessary for this demo.
    // Compare with automatically generated ad packets from other
    // demo projects to see what else you might put here, or read
    // the relevant portions of the Bluetooth 4.0 Core Spec document
    // for greater detail.
  };
//  gap_add_device_name(&adv_data,device_name, sizeof(device_name)-1);
    // -------------------------------
    // build custom scan response data
    // -------------------------------

    // get Bluetooth MAC address of this device (NOTE: this is little-endian!)

  sr_data[0] = 0x13;  // ad field length = 19 bytes (0x13)
  sr_data[1] = 0x09;   // ad field type = 0x09 (Complete local name)
  sr_data[2] = 0x06;  // 'M'
  sr_data[3] = 0x79;  // 'y'
  sr_data[4] = 0x20;  // ' '
  sr_data[5] = 0x57;  // 'W'
  sr_data[6] = 0x69;  // 'i'
  sr_data[7] = 0x64;  // 'd'
  sr_data[8] = 0x67;  // 'g'
  sr_data[9] = 0x65;  // 'e'
  sr_data[10] = 0x74; // 't'
  sr_data[11] = 0x20; // ' '
  sr_data[12] = 0x01;
  sr_data[13] = 0x02;
  sr_data[14] = 0x03;
  sr_data[15] = 0x04;
  sr_data[16] = 0x05;
  sr_data[17] = 0x06;
  sr_data[18] = 0x07;
  sr_data[19] = 0x08;

 AdvData_t adv_data = gap_adv_data_new(aadata,sizeof(aadata));
 gap_add_service_data(&adv_data, 13, sr_data, 20);

}
