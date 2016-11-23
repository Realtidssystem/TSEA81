@@ Startup code for Simple_OS on ARM architecture
@@ Based on information available at http://balau82.wordpress.com/

@@ fig_begin startup_code
.global start
start:
	ldr sp, =stack_bottom
	bl main
	b .
@@ fig_end startup_code

