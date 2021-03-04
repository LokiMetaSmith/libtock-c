//Switch hardware IO
// \file
// This program waits for button presses on each of the buttons attached
// to a board and toggles the LED with the same index. For example, if the first
// button is pressed, the first LED is toggled. If the third button is pressed,
// the third LED is toggled.

#include <button.h>
#include <led.h>
#include <ipc.h>

// Callback for button presses.
//   btn_num: The index of the button associated with the callback
//   val: 1 if pressed, 0 if depressed
int * ble_service;

static void button_callback(int btn_num,
                            int val,
                            __attribute__ ((unused)) int arg2,
                            __attribute__ ((unused)) void *ud) {
  if (val == 1) {
    led_toggle(btn_num);
  }
}
//pid: pid from the calling application
// len: length of buffer
// buff: pointer to shared buffer
//  uint8_t* buffer = (uint8_t*) buff;
//  uint8_t command = buffer[0];
static void ipc_callback(int pid, int len, int buff, void* ud){

}

int main(void) {
  *ble_service = ipc_discover("org.tockos.opossum-pouch.ipc.ble");

  button_subscribe(button_callback, NULL);

  // Enable interrupts on each button.
  int count = button_count();
  for (int i = 0; i < count; i++) {
    button_enable_interrupt(i);
  }



  return 0;
}
