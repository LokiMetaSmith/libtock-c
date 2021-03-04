Bluetooth Low Energy Advertisement App
======================================

An example application that demonstrates how the Bluetooth Low Energy API can be
used to advertise data periodically that runs forever.

The application does the following:
  * Configures advertisement name to used in the advertisement
  * Configures is the device shall be detected
  * Configures the advertisement interval
  * Configures list of UUIDs (generic service and temperature service)
  * Configures Event data to a hard-coded value for demonstration purposes.

Supported Boards
-----------------
- nRF52-Dongle

UART over BLE
=============

This app implements the peripheral side of the
[Nordic UART service](https://infocenter.nordicsemi.com/index.jsp?topic=%2Fcom.nordic.infocenter.sdk5.v11.0.0%2Fble_sdk_app_nus_eval.html&cp=4_0_4_4_2_2_18).
To use:

1. Program this app on a hardware board (imix or Hail).
2. Download the "nRF UART" app on a smartphone.
3. Run `tockloader listen`.
4. In the smartphone app, connect to the device named "tock-uart".
5. Any messages you send will appear in the terminal!

It should be straightforward to re-purpose this app for easy communication
between BLE devices.

Supported Boards
----------------

- Hail
- imix
