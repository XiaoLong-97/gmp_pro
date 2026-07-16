;/**************************************************************************//**
; * @file     startup_SPC6Lxx.s
; * @brief    CMSIS Core Device Startup File for
; *           SPC6L Device Series
; * @version  V1.08
; * @date     30. 11. 2022
; *
; * @note
; *
; ******************************************************************************/
;/* Copyright (c) 2011 - 2012 ARM LIMITED
;
;   All rights reserved.
;   Redistribution and use in source and binary forms, with or without
;   modification, are permitted provided that the following conditions are met:
;   - Redistributions of source code must retain the above copyright
;     notice, this list of conditions and the following disclaimer.
;   - Redistributions in binary form must reproduce the above copyright
;     notice, this list of conditions and the following disclaimer in the
;     documentation and/or other materials provided with the distribution.
;   - Neither the name of ARM nor the names of its contributors may be used
;     to endorse or promote products derived from this software without
;     specific prior written permission.
;   *
;   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
;   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
;   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
;   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
;   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
;   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
;   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
;   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
;   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
;   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
;   POSSIBILITY OF SUCH DAMAGE.
;   ---------------------------------------------------------------------------*/
;/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;*/


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000200

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000100

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             	; Reset Handler
                DCD     NMI_Handler               	; NMI Handler
                DCD     HardFault_Handler         	; Hard Fault Handler
                DCD     0                         	; Reserved
                DCD     0                         	; Reserved
                DCD     0                         	; Reserved
                DCD     0                         	; Reserved
                DCD     0                         	; Reserved
                DCD     0                         	; Reserved
                DCD     0                         	; Reserved
                DCD     SVC_Handler               	; SVCall Handler
                DCD     0                         	; Reserved
                DCD     0                         	; Reserved
                DCD     PendSV_Handler            	; PendSV Handler
                DCD     SysTick_Handler           	; SysTick Handler

                ; External Interrupts
                DCD     UART0_IRQHandler			;  0: UART0 Handler
                DCD     UART1_IRQHandler			;  1: UART1 Handler
                DCD     0 							;  2: Reserved
                DCD     SPI0_IRQHandler				;  3: SPI0 Handler
                DCD     EXINT_IRQHandler			;  4: EXINT Handler
                DCD     ACMP0_IRQHandler			;  5: ACMP0 Handler
                DCD     0    						;  6: Reserved
                DCD     ACMP1_IRQHandler			;  7: ACMP1 Handler
                DCD     BT40_IRQHandler     		;  8: BT40 Handler
                DCD     BT41_IRQHandler   			;  9: BT41 Handler
                DCD     ACMP2_IRQHandler			; 10: ACMP2 Handler
                DCD     DMA_IRQHandler    			; 11: DMA Handler
                DCD     COPROC_IRQHandler    		; 12: COPROC Handler
                DCD     SYS_IRQHandler    			; 13: SYS Handler
                DCD     WWDT_IRQHandler				; 14: WWDT Handler
                DCD     IWDT_IRQHandler    			; 15: IWDT Handler
		        DCD     BT00_IRQHandler       		; 16: BT00 Handler
                DCD     BT01_IRQHandler       		; 17£ºBT01 Handler
                DCD     BT10_IRQHandler       		; 18£ºBT10 Handler
                DCD     ADC0_IRQHandler    			; 19£ºADC0 Handler
                DCD     ADC1_IRQHandler      		; 20£ºADC1 Handler
                DCD     ADC2_IRQHandler   			; 21£ºADC2 Handler
                DCD     ADC_IRQHandler      		; 22£ºADC Handler
                DCD     PWM0_IRQHandler      		; 23£ºPWM0 Handler
                DCD     0							; 24£ºReserved
                DCD     0      						; 25£ºReserved
                DCD     BT11_IRQHandler				; 26£ºBT11 Handler
                DCD     PWM_IRQHandler   			; 27£ºPWM Handler
                DCD     0   						; 28£ºReserved
				DCD     0   						; 29£ºReserved
				DCD     0   						; 30£ºReserved
                DCD     0 							; 31£ºReserved
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             	[WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               	[WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler			[WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               	[WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            	[WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler          	[WEAK]
                B       .
                ENDP
Reserved_IRQHandler PROC
                EXPORT  Reserved_IRQHandler       [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  UART0_IRQHandler			[WEAK]
                EXPORT  UART1_IRQHandler			[WEAK]
                EXPORT  SPI0_IRQHandler				[WEAK]
                EXPORT  EXINT_IRQHandler			[WEAK]					
				EXPORT  ACMP0_IRQHandler		    [WEAK]
				EXPORT  ACMP1_IRQHandler		    [WEAK]
                EXPORT  BT40_IRQHandler           	[WEAK]
                EXPORT  BT41_IRQHandler   	   		[WEAK]
				EXPORT  ACMP2_IRQHandler		    [WEAK]					
                EXPORT  DMA_IRQHandler    	  		[WEAK]
                EXPORT  COPROC_IRQHandler     	 	[WEAK]
                EXPORT  SYS_IRQHandler    	  		[WEAK]
                EXPORT  WWDT_IRQHandler				[WEAK]
                EXPORT	IWDT_IRQHandler    	   		[WEAK]
                EXPORT	BT00_IRQHandler    	   		[WEAK]
                EXPORT	BT01_IRQHandler    	   		[WEAK]
                EXPORT	BT10_IRQHandler    	   		[WEAK]					
                EXPORT	ADC0_IRQHandler    	 		[WEAK]
                EXPORT	ADC1_IRQHandler        		[WEAK]
                EXPORT	ADC2_IRQHandler   	  		[WEAK]
                EXPORT	ADC_IRQHandler          	[WEAK]
                EXPORT	PWM0_IRQHandler           	[WEAK]
                EXPORT	BT11_IRQHandler    	   		[WEAK]
                EXPORT	PWM_IRQHandler   	 	   	[WEAK]
UART0_IRQHandler		
UART1_IRQHandler		 	 		
SPI0_IRQHandler
EXINT_IRQHandler	
ACMP0_IRQHandler
ACMP1_IRQHandler
BT40_IRQHandler      
BT41_IRQHandler
ACMP2_IRQHandler
DMA_IRQHandler    	     	
COPROC_IRQHandler      	 
SYS_IRQHandler    	   	
WWDT_IRQHandler		  	
IWDT_IRQHandler
BT00_IRQHandler
BT01_IRQHandler
BT10_IRQHandler
ADC0_IRQHandler    	    	
ADC1_IRQHandler         	
ADC2_IRQHandler   	    	
ADC_IRQHandler       	
PWM0_IRQHandler
BT11_IRQHandler
PWM_IRQHandler
  	  	 	

                B       .

                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap PROC
                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDP

                ALIGN

                ENDIF


                END
