OBJ_BASE_NAMES =tcb_message si_string_lib screen_output si_time_type si_comm \
interrupt tcb_storage task_message time_storage si_message int_status \
si_kernel task console task_id_list timer tcb tcb_list time_list \
ready_list si_semaphore si_condvar tick_handler time_handler \
schedule wait_list si_time si_ui
OBJ_NAMES=

LNK_NAMES =

ASM_OBJ_NAMES=

PROG_BASE_NAME =prog
PROG_NAMES=


define msg 


*** ERROR: you need to do

make <target>

or

make clean

*** Select <target> as one of 

--- x86_host (x86 host - Linux or Cygwin)

--- arm_bb (ARM target - Beagleboard)

---------------------------------------------------


endef

all: 
	$(error $(msg))


OBJ_NAMES_NO_DIR_x86_host =$(addsuffix _x86_host.o, $(OBJ_BASE_NAMES))
OBJ_NAMES_x86_host =$(addprefix ./obj/, $(OBJ_NAMES_NO_DIR_x86_host))
OBJ_NAMES += $(OBJ_NAMES_x86_host)

ASM_OBJ_BASE_NAMES_x86_host =context exceptions
ASM_OBJ_NAMES_NO_DIR_x86_host =$(addsuffix _x86_host.o, $(ASM_OBJ_BASE_NAMES_x86_host))
ASM_OBJ_NAMES_x86_host =$(addprefix ./obj/, $(ASM_OBJ_NAMES_NO_DIR_x86_host))
ASM_OBJ_NAMES += $(ASM_OBJ_NAMES_x86_host)

PROG_NAME_x86_host =$(addsuffix _x86_host, $(PROG_BASE_NAME))
PROG_NAMES += $(PROG_NAME_x86_host)

x86_host: $(PROG_NAME_x86_host)

LIB_BASE_NAME =NO_LIB_BASE_NAME
LIB_NAME_x86_host =$(addprefix lib, $(addsuffix _x86_host.a, $(LIB_BASE_NAME)))

INCLUDE_DIRS_x86_host=
INCLUDE_DIR_FLAGS_x86_host = $(addprefix -I , $(INCLUDE_DIRS_x86_host))

LIB_DIRS_x86_host=
LIB_DIR_FLAGS_x86_host = $(addprefix -L , $(LIB_DIRS_x86_host))

LD_LIBS_x86_host =
LD_LIB_FLAGS_x86_host = $(addprefix -l, $(LD_LIBS_x86_host))

LD_FLAGS_x86_host =-m32

$(PROG_NAME_x86_host): $(OBJ_NAMES_x86_host) $(ASM_OBJ_NAMES_x86_host)
	gcc $(LD_FLAGS_x86_host) -o $@ $^ $(LIB_DIR_FLAGS_x86_host) $(LD_LIB_FLAGS_x86_host)
	@echo -e "\n--- run the program by ./prog_x86_host ---\n"

$(LIB_NAME_x86_host): $(OBJ_NAMES_x86_host) $(ASM_OBJ_NAMES_x86_host)
	ar -rv -o $@ $^ 

ASM_FLAGS_x86_host =--32 --defsym BUILD_X86_HOST=1

./obj/context_x86_host.o: ./arch/x86_host/context.s 
	as $(ASM_FLAGS_x86_host) $< -o $@ 

./obj/exceptions_x86_host.o: ./arch/x86_host/exceptions.s 
	as $(ASM_FLAGS_x86_host) $< -o $@ 

C_FLAGS_x86_host =-c -m32 -Wall -DBUILD_X86_HOST

./obj/tcb_message_x86_host.o: ./src/tcb_message.c ./src/tcb_message.h ./src/task_message.h ./src/task_id_list.h ./src/wait_list.h ./src/ready_list.h ./src/schedule.h ./src/task_message.h ./src/tcb_storage.h ./src/tcb.h ./src/arch_types.h
	gcc $(C_FLAGS_x86_host) $< -o $@ $(INCLUDE_DIR_FLAGS_x86_host)

./obj/si_string_lib_x86_host.o: ./src/si_string_lib.c ./src/si_string_lib.h 
	gcc $(C_FLAGS_x86_host) $< -o $@ $(INCLUDE_DIR_FLAGS_x86_host)

./obj/screen_output_x86_host.o: ./src/screen_output.c ./src/screen_output.h 
	gcc $(C_FLAGS_x86_host) $< -o $@ $(INCLUDE_DIR_FLAGS_x86_host)

./obj/si_time_type_x86_host.o: ./src/si_time_type.c ./src/si_time_type.h 
	gcc $(C_FLAGS_x86_host) $< -o $@ $(INCLUDE_DIR_FLAGS_x86_host)

./obj/si_comm_x86_host.o: ./src/si_comm.c ./src/si_comm.h ./src/console.h ./src/arch_types.h
	gcc $(C_FLAGS_x86_host) $< -o $@ $(INCLUDE_DIR_FLAGS_x86_host)

./obj/interrupt_x86_host.o: ./src/interrupt.c ./src/interrupt.h ./src/console.h ./src/exceptions.h ./src/arch_types.h ./src/arch_types.h
	gcc $(C_FLAGS_x86_host) $< -o $@ $(INCLUDE_DIR_FLAGS_x86_host)

./obj/tcb_storage_x86_host.o: ./src/tcb_storage.c ./src/tcb_storage.h ./src/tcb.h ./src/tcb_list.h ./src/tcb.h ./src/arch_types.h ./src/arch_types.h ./src/tcb.h ./src/arch_types.h
	gcc $(C_FLAGS_x86_host) $< -o $@ $(INCLUDE_DIR_FLAGS_x86_host)

./obj/task_message_x86_host.o: ./src/task_message.c ./src/task_message.h ./src/task_id_list.h 
	gcc $(C_FLAGS_x86_host) $< -o $@ $(INCLUDE_DIR_FLAGS_x86_host)

./obj/time_storage_x86_host.o: ./src/time_storage.c ./src/time_storage.h ./src/si_time_type.h ./src/si_time_type.h
	gcc $(C_FLAGS_x86_host) $< -o $@ $(INCLUDE_DIR_FLAGS_x86_host)

./obj/si_message_x86_host.o: ./src/si_message.c ./src/si_message.h ./src/task_message.h ./src/tcb_message.h ./src/tcb_storage.h ./src/interrupt.h ./src/task.h ./src/task_message.h ./src/task_message.h ./src/tcb_storage.h ./src/tcb.h ./src/arch_types.h ./src/tcb.h ./src/arch_types.h ./src/arch_types.h
	gcc $(C_FLAGS_x86_host) $< -o $@ $(INCLUDE_DIR_FLAGS_x86_host)

./obj/int_status_x86_host.o: ./src/int_status.c ./src/int_status.h ./src/console.h ./src/arch_types.h
	gcc $(C_FLAGS_x86_host) $< -o $@ $(INCLUDE_DIR_FLAGS_x86_host)

./obj/si_kernel_x86_host.o: ./src/si_kernel.c ./src/si_kernel.h ./src/tcb_storage.h ./src/task.h ./src/ready_list.h ./src/tick_handler.h ./src/time_list.h ./src/time_storage.h ./src/schedule.h ./src/interrupt.h ./src/exceptions.h ./src/int_status.h ./src/console.h ./src/arch_types.h ./src/tcb.h ./src/arch_types.h ./src/arch_types.h ./src/si_time_type.h ./src/arch_types.h ./src/arch_types.h
	gcc $(C_FLAGS_x86_host) $< -o $@ $(INCLUDE_DIR_FLAGS_x86_host)

./obj/task_x86_host.o: ./src/task.c ./src/task.h ./src/arch_types.h ./src/tcb.h ./src/tcb_storage.h ./src/context.h ./src/exceptions.h ./src/console.h ./src/int_status.h ./src/interrupt.h ./src/arch_types.h ./src/arch_types.h ./src/tcb.h ./src/arch_types.h ./src/arch_types.h ./src/arch_types.h ./src/arch_types.h
	gcc $(C_FLAGS_x86_host) $< -o $@ $(INCLUDE_DIR_FLAGS_x86_host)

./obj/console_x86_host.o: ./src/console.c ./src/console.h ./src/screen_output.h ./src/arch_types.h
	gcc $(C_FLAGS_x86_host) $< -o $@ $(INCLUDE_DIR_FLAGS_x86_host)

./obj/task_id_list_x86_host.o: ./src/task_id_list.c ./src/task_id_list.h 
	gcc $(C_FLAGS_x86_host) $< -o $@ $(INCLUDE_DIR_FLAGS_x86_host)

./obj/timer_x86_host.o: ./src/timer.c ./src/timer.h ./src/console.h ./src/arch_types.h
	gcc $(C_FLAGS_x86_host) $< -o $@ $(INCLUDE_DIR_FLAGS_x86_host)

./obj/tcb_x86_host.o: ./src/tcb.c ./src/tcb.h ./src/console.h ./src/arch_types.h ./src/arch_types.h
	gcc $(C_FLAGS_x86_host) $< -o $@ $(INCLUDE_DIR_FLAGS_x86_host)

./obj/tcb_list_x86_host.o: ./src/tcb_list.c ./src/tcb_list.h ./src/tcb.h ./src/task_id_list.h ./src/console.h ./src/tcb.h ./src/arch_types.h ./src/arch_types.h ./src/arch_types.h
	gcc $(C_FLAGS_x86_host) $< -o $@ $(INCLUDE_DIR_FLAGS_x86_host)

./obj/time_list_x86_host.o: ./src/time_list.c ./src/time_list.h ./src/tcb_storage.h ./src/task_id_list.h ./src/tcb.h ./src/tcb_list.h ./src/console.h ./src/tcb.h ./src/arch_types.h ./src/arch_types.h ./src/tcb.h ./src/arch_types.h ./src/arch_types.h
	gcc $(C_FLAGS_x86_host) $< -o $@ $(INCLUDE_DIR_FLAGS_x86_host)

./obj/ready_list_x86_host.o: ./src/ready_list.c ./src/ready_list.h ./src/tcb.h ./src/tcb_storage.h ./src/task_id_list.h ./src/tcb_list.h ./src/console.h ./src/arch_types.h ./src/tcb.h ./src/arch_types.h ./src/tcb.h ./src/arch_types.h ./src/arch_types.h
	gcc $(C_FLAGS_x86_host) $< -o $@ $(INCLUDE_DIR_FLAGS_x86_host)

./obj/si_semaphore_x86_host.o: ./src/si_semaphore.c ./src/si_semaphore.h ./src/wait_list.h ./src/interrupt.h ./src/task.h ./src/ready_list.h ./src/schedule.h ./src/tcb_storage.h ./src/tcb.h ./src/arch_types.h ./src/arch_types.h
	gcc $(C_FLAGS_x86_host) $< -o $@ $(INCLUDE_DIR_FLAGS_x86_host)

./obj/si_condvar_x86_host.o: ./src/si_condvar.c ./src/si_condvar.h ./src/task.h ./src/interrupt.h ./src/wait_list.h ./src/ready_list.h ./src/schedule.h ./src/si_semaphore.h ./src/tcb_storage.h ./src/tcb.h ./src/arch_types.h ./src/arch_types.h
	gcc $(C_FLAGS_x86_host) $< -o $@ $(INCLUDE_DIR_FLAGS_x86_host)

./obj/tick_handler_x86_host.o: ./src/tick_handler.c ./src/tick_handler.h ./src/console.h ./src/timer.h ./src/interrupt.h ./src/tcb_storage.h ./src/time_list.h ./src/ready_list.h ./src/schedule.h ./src/time_storage.h ./src/arch_types.h ./src/tcb.h ./src/arch_types.h ./src/si_time_type.h
	gcc $(C_FLAGS_x86_host) $< -o $@ $(INCLUDE_DIR_FLAGS_x86_host)

./obj/time_handler_x86_host.o: ./src/time_handler.c ./src/time_handler.h ./src/task.h ./src/time_list.h ./src/tcb.h ./src/tcb_storage.h ./src/ready_list.h ./src/schedule.h ./src/arch_types.h ./src/arch_types.h ./src/tcb.h ./src/arch_types.h
	gcc $(C_FLAGS_x86_host) $< -o $@ $(INCLUDE_DIR_FLAGS_x86_host)

./obj/schedule_x86_host.o: ./src/schedule.c ./src/schedule.h ./src/ready_list.h ./src/task.h ./src/console.h ./src/arch_types.h ./src/arch_types.h
	gcc $(C_FLAGS_x86_host) $< -o $@ $(INCLUDE_DIR_FLAGS_x86_host)

./obj/wait_list_x86_host.o: ./src/wait_list.c ./src/wait_list.h ./src/tcb_storage.h ./src/tcb_list.h ./src/tcb.h ./src/task_id_list.h ./src/tcb.h ./src/arch_types.h ./src/tcb.h ./src/arch_types.h ./src/arch_types.h
	gcc $(C_FLAGS_x86_host) $< -o $@ $(INCLUDE_DIR_FLAGS_x86_host)

./obj/si_time_x86_host.o: ./src/si_time.c ./src/si_time.h ./src/time_handler.h ./src/time_storage.h ./src/interrupt.h ./src/console.h ./src/si_time_type.h ./src/si_time_type.h ./src/arch_types.h
	gcc $(C_FLAGS_x86_host) $< -o $@ $(INCLUDE_DIR_FLAGS_x86_host)

./obj/si_ui_x86_host.o: ./src/si_ui.c ./src/si_ui.h ./src/simple_os.h ./src/si_comm.h ./src/console.h ./src/si_kernel.h ./src/si_time.h ./src/si_semaphore.h ./src/si_condvar.h ./src/si_message.h ./src/si_ui.h ./src/si_string_lib.h ./src/console.h ./src/arch_types.h ./src/si_time_type.h ./src/tcb_storage.h ./src/tcb.h ./src/arch_types.h ./src/si_semaphore.h ./src/tcb_storage.h ./src/tcb.h ./src/arch_types.h ./src/task_message.h ./src/arch_types.h ./src/arch_types.h
	gcc $(C_FLAGS_x86_host) $< -o $@ $(INCLUDE_DIR_FLAGS_x86_host)

OBJ_NAMES_NO_DIR_arm_bb =$(addsuffix _arm_bb.o, $(OBJ_BASE_NAMES))
OBJ_NAMES_arm_bb =$(addprefix ./obj/, $(OBJ_NAMES_NO_DIR_arm_bb))
OBJ_NAMES += $(OBJ_NAMES_arm_bb)

ASM_OBJ_BASE_NAMES_arm_bb =debug context_int context startup exceptions
ASM_OBJ_NAMES_NO_DIR_arm_bb =$(addsuffix _arm_bb.o, $(ASM_OBJ_BASE_NAMES_arm_bb))
ASM_OBJ_NAMES_arm_bb =$(addprefix ./obj/, $(ASM_OBJ_NAMES_NO_DIR_arm_bb))
ASM_OBJ_NAMES += $(ASM_OBJ_NAMES_arm_bb)

PROG_NAME_arm_bb =$(addsuffix _arm_bb, $(PROG_BASE_NAME))
PROG_NAMES += $(PROG_NAME_arm_bb)

arm_bb: $(PROG_NAME_arm_bb)

LIB_BASE_NAME =NO_LIB_BASE_NAME
LIB_NAME_arm_bb =$(addprefix lib, $(addsuffix _arm_bb.a, $(LIB_BASE_NAME)))

INCLUDE_DIRS_arm_bb=
INCLUDE_DIR_FLAGS_arm_bb = $(addprefix -I , $(INCLUDE_DIRS_arm_bb))

LIB_DIRS_arm_bb=
LIB_DIR_FLAGS_arm_bb = $(addprefix -L , $(LIB_DIRS_arm_bb))

LD_LIBS_arm_bb =
LD_LIB_FLAGS_arm_bb = $(addprefix -l, $(LD_LIBS_arm_bb))

LD_FLAGS_arm_bb =-T arch/arm_bb/link.ld

$(PROG_NAME_arm_bb): $(OBJ_NAMES_arm_bb) $(ASM_OBJ_NAMES_arm_bb) ./arch/arm_bb/link.ld
	arm-none-eabi-ld $(LD_FLAGS_arm_bb) -o $@ $^ $(LIB_DIR_FLAGS_arm_bb) $(LD_LIB_FLAGS_arm_bb)
	arm-none-eabi-objcopy -O srec prog_arm_bb prog_arm_bb.srec
	@echo -e "\n--- run the program by download of srec-file to Beagleboard ---\n"

$(LIB_NAME_arm_bb): $(OBJ_NAMES_arm_bb) $(ASM_OBJ_NAMES_arm_bb) ./arch/arm_bb/link.ld
	arm-none-eabi-ar -rv -o $@ $^ 

ASM_FLAGS_arm_bb =-mcpu=cortex-a8 --defsym BUILD_ARM_BB=1

./obj/debug_arm_bb.o: ./arch/arm/debug.s 
	arm-none-eabi-as $(ASM_FLAGS_arm_bb) $< -o $@ 

./obj/context_int_arm_bb.o: ./arch/arm/context_int.s 
	arm-none-eabi-as $(ASM_FLAGS_arm_bb) $< -o $@ 

./obj/context_arm_bb.o: ./arch/arm/context.s 
	arm-none-eabi-as $(ASM_FLAGS_arm_bb) $< -o $@ 

./obj/startup_arm_bb.o: ./arch/arm/startup.s 
	arm-none-eabi-as $(ASM_FLAGS_arm_bb) $< -o $@ 

./obj/exceptions_arm_bb.o: ./arch/arm_bb/exceptions.s 
	arm-none-eabi-as $(ASM_FLAGS_arm_bb) $< -o $@ 

C_FLAGS_arm_bb =-c -mcpu=cortex-a8 -Wall -DBUILD_ARM_BB

./obj/tcb_message_arm_bb.o: ./src/tcb_message.c ./src/tcb_message.h ./src/task_message.h ./src/task_id_list.h ./src/wait_list.h ./src/ready_list.h ./src/schedule.h ./src/task_message.h ./src/tcb_storage.h ./src/tcb.h ./src/arch_types.h
	arm-none-eabi-gcc $(C_FLAGS_arm_bb) $< -o $@ $(INCLUDE_DIR_FLAGS_arm_bb)

./obj/si_string_lib_arm_bb.o: ./src/si_string_lib.c ./src/si_string_lib.h 
	arm-none-eabi-gcc $(C_FLAGS_arm_bb) $< -o $@ $(INCLUDE_DIR_FLAGS_arm_bb)

./obj/screen_output_arm_bb.o: ./src/screen_output.c ./src/screen_output.h 
	arm-none-eabi-gcc $(C_FLAGS_arm_bb) $< -o $@ $(INCLUDE_DIR_FLAGS_arm_bb)

./obj/si_time_type_arm_bb.o: ./src/si_time_type.c ./src/si_time_type.h 
	arm-none-eabi-gcc $(C_FLAGS_arm_bb) $< -o $@ $(INCLUDE_DIR_FLAGS_arm_bb)

./obj/si_comm_arm_bb.o: ./src/si_comm.c ./src/si_comm.h ./src/console.h ./src/arch_types.h
	arm-none-eabi-gcc $(C_FLAGS_arm_bb) $< -o $@ $(INCLUDE_DIR_FLAGS_arm_bb)

./obj/interrupt_arm_bb.o: ./src/interrupt.c ./src/interrupt.h ./src/console.h ./src/exceptions.h ./src/arch_types.h ./src/arch_types.h
	arm-none-eabi-gcc $(C_FLAGS_arm_bb) $< -o $@ $(INCLUDE_DIR_FLAGS_arm_bb)

./obj/tcb_storage_arm_bb.o: ./src/tcb_storage.c ./src/tcb_storage.h ./src/tcb.h ./src/tcb_list.h ./src/tcb.h ./src/arch_types.h ./src/arch_types.h ./src/tcb.h ./src/arch_types.h
	arm-none-eabi-gcc $(C_FLAGS_arm_bb) $< -o $@ $(INCLUDE_DIR_FLAGS_arm_bb)

./obj/task_message_arm_bb.o: ./src/task_message.c ./src/task_message.h ./src/task_id_list.h 
	arm-none-eabi-gcc $(C_FLAGS_arm_bb) $< -o $@ $(INCLUDE_DIR_FLAGS_arm_bb)

./obj/time_storage_arm_bb.o: ./src/time_storage.c ./src/time_storage.h ./src/si_time_type.h ./src/si_time_type.h
	arm-none-eabi-gcc $(C_FLAGS_arm_bb) $< -o $@ $(INCLUDE_DIR_FLAGS_arm_bb)

./obj/si_message_arm_bb.o: ./src/si_message.c ./src/si_message.h ./src/task_message.h ./src/tcb_message.h ./src/tcb_storage.h ./src/interrupt.h ./src/task.h ./src/task_message.h ./src/task_message.h ./src/tcb_storage.h ./src/tcb.h ./src/arch_types.h ./src/tcb.h ./src/arch_types.h ./src/arch_types.h
	arm-none-eabi-gcc $(C_FLAGS_arm_bb) $< -o $@ $(INCLUDE_DIR_FLAGS_arm_bb)

./obj/int_status_arm_bb.o: ./src/int_status.c ./src/int_status.h ./src/console.h ./src/arch_types.h
	arm-none-eabi-gcc $(C_FLAGS_arm_bb) $< -o $@ $(INCLUDE_DIR_FLAGS_arm_bb)

./obj/si_kernel_arm_bb.o: ./src/si_kernel.c ./src/si_kernel.h ./src/tcb_storage.h ./src/task.h ./src/ready_list.h ./src/tick_handler.h ./src/time_list.h ./src/time_storage.h ./src/schedule.h ./src/interrupt.h ./src/exceptions.h ./src/int_status.h ./src/console.h ./src/arch_types.h ./src/tcb.h ./src/arch_types.h ./src/arch_types.h ./src/si_time_type.h ./src/arch_types.h ./src/arch_types.h
	arm-none-eabi-gcc $(C_FLAGS_arm_bb) $< -o $@ $(INCLUDE_DIR_FLAGS_arm_bb)

./obj/task_arm_bb.o: ./src/task.c ./src/task.h ./src/arch_types.h ./src/tcb.h ./src/tcb_storage.h ./src/context.h ./src/exceptions.h ./src/console.h ./src/int_status.h ./src/interrupt.h ./src/arch_types.h ./src/arch_types.h ./src/tcb.h ./src/arch_types.h ./src/arch_types.h ./src/arch_types.h ./src/arch_types.h
	arm-none-eabi-gcc $(C_FLAGS_arm_bb) $< -o $@ $(INCLUDE_DIR_FLAGS_arm_bb)

./obj/console_arm_bb.o: ./src/console.c ./src/console.h ./src/screen_output.h ./src/arch_types.h
	arm-none-eabi-gcc $(C_FLAGS_arm_bb) $< -o $@ $(INCLUDE_DIR_FLAGS_arm_bb)

./obj/task_id_list_arm_bb.o: ./src/task_id_list.c ./src/task_id_list.h 
	arm-none-eabi-gcc $(C_FLAGS_arm_bb) $< -o $@ $(INCLUDE_DIR_FLAGS_arm_bb)

./obj/timer_arm_bb.o: ./src/timer.c ./src/timer.h ./src/console.h ./src/arch_types.h
	arm-none-eabi-gcc $(C_FLAGS_arm_bb) $< -o $@ $(INCLUDE_DIR_FLAGS_arm_bb)

./obj/tcb_arm_bb.o: ./src/tcb.c ./src/tcb.h ./src/console.h ./src/arch_types.h ./src/arch_types.h
	arm-none-eabi-gcc $(C_FLAGS_arm_bb) $< -o $@ $(INCLUDE_DIR_FLAGS_arm_bb)

./obj/tcb_list_arm_bb.o: ./src/tcb_list.c ./src/tcb_list.h ./src/tcb.h ./src/task_id_list.h ./src/console.h ./src/tcb.h ./src/arch_types.h ./src/arch_types.h ./src/arch_types.h
	arm-none-eabi-gcc $(C_FLAGS_arm_bb) $< -o $@ $(INCLUDE_DIR_FLAGS_arm_bb)

./obj/time_list_arm_bb.o: ./src/time_list.c ./src/time_list.h ./src/tcb_storage.h ./src/task_id_list.h ./src/tcb.h ./src/tcb_list.h ./src/console.h ./src/tcb.h ./src/arch_types.h ./src/arch_types.h ./src/tcb.h ./src/arch_types.h ./src/arch_types.h
	arm-none-eabi-gcc $(C_FLAGS_arm_bb) $< -o $@ $(INCLUDE_DIR_FLAGS_arm_bb)

./obj/ready_list_arm_bb.o: ./src/ready_list.c ./src/ready_list.h ./src/tcb.h ./src/tcb_storage.h ./src/task_id_list.h ./src/tcb_list.h ./src/console.h ./src/arch_types.h ./src/tcb.h ./src/arch_types.h ./src/tcb.h ./src/arch_types.h ./src/arch_types.h
	arm-none-eabi-gcc $(C_FLAGS_arm_bb) $< -o $@ $(INCLUDE_DIR_FLAGS_arm_bb)

./obj/si_semaphore_arm_bb.o: ./src/si_semaphore.c ./src/si_semaphore.h ./src/wait_list.h ./src/interrupt.h ./src/task.h ./src/ready_list.h ./src/schedule.h ./src/tcb_storage.h ./src/tcb.h ./src/arch_types.h ./src/arch_types.h
	arm-none-eabi-gcc $(C_FLAGS_arm_bb) $< -o $@ $(INCLUDE_DIR_FLAGS_arm_bb)

./obj/si_condvar_arm_bb.o: ./src/si_condvar.c ./src/si_condvar.h ./src/task.h ./src/interrupt.h ./src/wait_list.h ./src/ready_list.h ./src/schedule.h ./src/si_semaphore.h ./src/tcb_storage.h ./src/tcb.h ./src/arch_types.h ./src/arch_types.h
	arm-none-eabi-gcc $(C_FLAGS_arm_bb) $< -o $@ $(INCLUDE_DIR_FLAGS_arm_bb)

./obj/tick_handler_arm_bb.o: ./src/tick_handler.c ./src/tick_handler.h ./src/console.h ./src/timer.h ./src/interrupt.h ./src/tcb_storage.h ./src/time_list.h ./src/ready_list.h ./src/schedule.h ./src/time_storage.h ./src/arch_types.h ./src/tcb.h ./src/arch_types.h ./src/si_time_type.h
	arm-none-eabi-gcc $(C_FLAGS_arm_bb) $< -o $@ $(INCLUDE_DIR_FLAGS_arm_bb)

./obj/time_handler_arm_bb.o: ./src/time_handler.c ./src/time_handler.h ./src/task.h ./src/time_list.h ./src/tcb.h ./src/tcb_storage.h ./src/ready_list.h ./src/schedule.h ./src/arch_types.h ./src/arch_types.h ./src/tcb.h ./src/arch_types.h
	arm-none-eabi-gcc $(C_FLAGS_arm_bb) $< -o $@ $(INCLUDE_DIR_FLAGS_arm_bb)

./obj/schedule_arm_bb.o: ./src/schedule.c ./src/schedule.h ./src/ready_list.h ./src/task.h ./src/console.h ./src/arch_types.h ./src/arch_types.h
	arm-none-eabi-gcc $(C_FLAGS_arm_bb) $< -o $@ $(INCLUDE_DIR_FLAGS_arm_bb)

./obj/wait_list_arm_bb.o: ./src/wait_list.c ./src/wait_list.h ./src/tcb_storage.h ./src/tcb_list.h ./src/tcb.h ./src/task_id_list.h ./src/tcb.h ./src/arch_types.h ./src/tcb.h ./src/arch_types.h ./src/arch_types.h
	arm-none-eabi-gcc $(C_FLAGS_arm_bb) $< -o $@ $(INCLUDE_DIR_FLAGS_arm_bb)

./obj/si_time_arm_bb.o: ./src/si_time.c ./src/si_time.h ./src/time_handler.h ./src/time_storage.h ./src/interrupt.h ./src/console.h ./src/si_time_type.h ./src/si_time_type.h ./src/arch_types.h
	arm-none-eabi-gcc $(C_FLAGS_arm_bb) $< -o $@ $(INCLUDE_DIR_FLAGS_arm_bb)

./obj/si_ui_arm_bb.o: ./src/si_ui.c ./src/si_ui.h ./src/simple_os.h ./src/si_comm.h ./src/console.h ./src/si_kernel.h ./src/si_time.h ./src/si_semaphore.h ./src/si_condvar.h ./src/si_message.h ./src/si_ui.h ./src/si_string_lib.h ./src/console.h ./src/arch_types.h ./src/si_time_type.h ./src/tcb_storage.h ./src/tcb.h ./src/arch_types.h ./src/si_semaphore.h ./src/tcb_storage.h ./src/tcb.h ./src/arch_types.h ./src/task_message.h ./src/arch_types.h ./src/arch_types.h
	arm-none-eabi-gcc $(C_FLAGS_arm_bb) $< -o $@ $(INCLUDE_DIR_FLAGS_arm_bb)


clean: 
	rm -f $(PROG_NAMES) $(OBJ_NAMES) $(ASM_OBJ_NAMES) $(LNK_NAMES)
