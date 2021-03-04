# Makefile for user application

# Specify this directory relative to the current application.
#TOCK_USERLAND_BASE_DIR = ../../libtock-c
TOCK_USERLAND_BASE_DIR = ../..
# Which files to compile.
C_SRCS := $(wildcard *.c)

APP_HEAP_SIZE = 4096

# External libraries used
EXTERN_LIBS += $(TOCK_USERLAND_BASE_DIR)/simple-ble
## External libraries used for debug and message passing
#EXTERN_LIBS += $(TOCK_USERLAND_BASE_DIR)/libnrfserialization
$(info EXTERN_LIBS is $(EXTERN_LIBS))
# Include userland master makefile. Contains rules and flags for actually
# building the application.
include $(TOCK_USERLAND_BASE_DIR)/AppMakefile.mk

# Include simple-ble's Makefile so it's rebuilt automatically
include $(TOCK_USERLAND_BASE_DIR)/simple-ble/Makefile
