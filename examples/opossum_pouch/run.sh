#!/usr/bin/env bash
# constructor script for building and deploying different apps into a single device
# Apps
APP1=switch
APP1_TAB=$APP1/build/$APP1.tab

APP2=power
APP2_TAB=$APP2/build/$APP2.tab

APP3=ble
APP3_TAB=$APP3/build/$APP3.tab

APP4=db
APP4_TAB=$APP4/build/$APP4.tab

# erase apps
tockloader erase-apps --jlink --board nrf52dk --arch cortex-m4 --app-address 0x20000 --jtag-device nrf52

# build apps
make -C $APP1
make -C $APP2
make -C $APP3
make -C $APP4

# flash apps
tockloader install --jlink --board nrf52dk --arch cortex-m4 \
--app-address 0x20000 --jtag-device nrf52 $APP1_TAB
tockloader install --jlink --board nrf52dk --arch cortex-m4 \
--app-address 0x20000 --jtag-device nrf52 $APP2_TAB
tockloader install --jlink --board nrf52dk --arch cortex-m4 \
--app-address 0x20000 --jtag-device nrf52 $APP3_TAB
tockloader install --jlink --board nrf52dk --arch cortex-m4 \
--app-address 0x20000 --jtag-device nrf52 $APP4_TAB
