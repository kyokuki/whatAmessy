STACK_SZIE EQU 0x00000500
	AREA STACK,NOINIT,READWRITE,ALIGN=3
STACK_MEN SPACE STACK_SZIE
__stack_top

	PRESERVE8
	THUMB
	
	AREA    VECT, DATA, READONLY
	EXPORT  __Vectors

__Vectors       DCD     __stack_top              ; Top of Stack
	DCD     Start             				; Reset Handler
	DCD     NMI_Handler               ; NMI Handler
	DCD     HardFault_Handler         ; Hard Fault Handler
	DCD     MemManage_Handler         ; MPU Fault Handler
	DCD     BusFault_Handler          ; Bus Fault Handler
	DCD     UsageFault_Handler        ; Usage Fault Handler
	DCD     0                         ; Reserved
	DCD     0                         ; Reserved
	DCD     0                         ; Reserved
	DCD     0                         ; Reserved
	DCD     SVC_Handler               ; SVCall Handler
	DCD     DebugMon_Handler          ; Debug Monitor Handler
	DCD     0                         ; Reserved
	DCD     PendSV_Handler            ; PendSV Handler
	DCD     SysTick_Handler           ; SysTick Handler

	; External Interrupts	
	DCD     0            ; 16: Watchdog Timer
  DCD     0         ; 17: Timer0
  DCD     0         ; 18: Timer1
  DCD     0         ; 19: Timer2
  DCD     0         ; 20: Timer3
  DCD     UART0_IRQHandler          ; 21: UART0
  DCD     0          ; 22: UART1
  DCD     0          ; 23: UART2



	AREA	VECTPROC,CODE,READONLY
NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

UART0_IRQHandler
	
	push {lr}
	ldr r1,=0x4000c000
	ldr r0,[r1]
	;mov r0,#'a'
	bl sendbyte
	pop {pc}



	IMPORT SystemInit
	IMPORT UARTInit
	;IMPORT UART0_SendByte
	
	align 4
	AREA	STARTCODE,CODE,READONLY
	ENTRY

;start--------------------------	
Start
	
	bl SystemInit
	
	;uart init
	bl UARTInit
	DSB
	mov r0,#5
	bl EnableIRQ
	ldr r0,=0x4000c004
	ldr r1,=0x00000001
	str r1,[r0]
	
	;call c proc UART0_SendByte to send char
	;str lr,[sp,#-4]!
	;mov r0,#'c'
	;bl UART0_SendByte
		
	
	;mov r0,#'e'
	bl sendstring
deadloop
	b deadloop
;endp------------------------------

;EnableIRQ-------------------------
EnableIRQ
    PUSH   {R0-R2, LR} 
    AND.W  R1,    R0,    #0x1F
    MOV    R2,    #1 
    LSL    R2,    R2,    R1
    AND.W  R1,    R0,    #0xE0
    LSR    R1,    R1,    #3
    LDR    R0,    =0xE000E100
    STR    R2,    [R0, R1]
    POP    {R0-R2, PC}
;endp-------------------

;send string------------
sendstring
	push {r0-r3,lr}
	ldr r1,=HELLO
sendbloop	
	ldrb r0,[r1],#1
	cbz r0,sendend
	bl sendbyte
	b sendbloop
sendend	
	pop {r0-r3,pc}
;endp-------------------

;send byte--------------
sendbyte
	push {r1-r3,lr}
	ldr r2,=0x4000c014
sendloop
	ldr r1,[r2]
	tst r1,#0x20
	beq sendloop
	ldr r3,=0x4000c000
	str r0,[r3]
	pop {r1-r3,pc}
;endp--------------------	
	
HELLO
	DCB "hello world !\n",0
RCVBUF space 1
	
	align 4
	END