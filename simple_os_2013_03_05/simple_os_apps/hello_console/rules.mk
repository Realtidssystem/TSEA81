ifndef SIMPLE_OS_DIR
    define msg 

ERROR: You must set SIMPLE_OS_DIR to the simple_os directory in the Simple_OS installation
e.g. /home/<your_id>/simple_os_<version>/simple_os
use setenv SIMPLE_OS_DIR dirname in tcsh, and use export SIMPLE_OS_DIR=dirname in bash

    endef
    $(error $(msg))
endif

C_FLAGS +=-c -Wall
INCLUDE_FLAGS = -I $(SIMPLE_OS_DIR)/src
LIB_FLAGS =-L $(SIMPLE_OS_DIR) -lsimple_os_$(TARGET_SUFFIX)

C_FILES = $(basename $(notdir $(wildcard src/*.c)))
OBJECTS = $(addprefix obj/, $(addsuffix _$(TARGET_SUFFIX).o, $(C_FILES)))
H_FILES = $(wildcard src/*.h)

prog_$(TARGET_SUFFIX): $(OBJECTS)
	$(LD) $(LD_FLAGS) -o $@ $^ $(LIB_FLAGS)

obj/%_$(TARGET_SUFFIX).o: src/%.c $(H_FILES)
	$(CC) $(C_FLAGS) $< -o $@ $(INCLUDE_FLAGS)

clean: 
	rm ./obj/*_$(TARGET_SUFFIX).o