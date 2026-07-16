#ifndef __DMA_H__
#define __DMA_H__

#include "driver/inc/SLMCU.h"                   // Device header
#include "driver/inc/public.h"

/* =========================================================================================================================== */
/* ================                                       DMA data_struct                                     ================ */
/* =========================================================================================================================== */
typedef struct {                               /*!< (@ 0x20001900) DMA_DATA_Type Structure                                  	*/
	__IO uint32_t   *SOURCE;                     /*!< (@ 0x00000000) Primary source_end_ptr                                     */
	__IO uint32_t   *DESTION;                    /*!< (@ 0x00000004) Primary destion_end_ptr                                    */
	//	union {
	//		__IO uint32_t CTL_b;                          /*!< (@ 0x00000008) DMA countrl Register                                     */   
	struct {
	__IO uint32_t CYCLE_CTRL   	 	: 3;          
	__IO uint32_t NEXT_USEBURST     : 1;     
	__IO uint32_t N_MINUS_1	 		: 10; 	
	__IO uint32_t R_POWER	 		: 4; 
	__I  uint32_t			 		: 7;
	__IO uint32_t	CIRC	 		: 1;
	__IO uint32_t	DATA_SIZE		: 2;
	__IO uint32_t	SRC_INC	 		: 2;
	__IO uint32_t	DST_INC	 		: 2;                                        
	} CTL;
	//  } ;                                    
	__I  uint32_t   RESERVED0;
	__IO uint32_t   *ALT_SOURCE;                 /*!< (@ 0x00000010) Alternate source_end_ptr                                   */
	__IO uint32_t   *ALT_DESTION;                /*!< (@ 0x00000014) Alternate destion_end_ptr                                  */
	//	union {
	//		__IO uint32_t ALT_CTL;               /*!< (@ 0x00000000) DMA countrl Register                                     */   
	struct {
	__IO uint32_t CYCLE_CTRL   	  	: 3;          
	__IO uint32_t NEXT_USEBURST   	: 1;     
	__IO uint32_t N_MINUS_1	  		: 10; 	
	__IO uint32_t R_POWER	  		: 4; 
	__I  uint32_t			  		: 7;
	__IO uint32_t	CIRC	  		: 1;
	__IO uint32_t	DATA_SIZE 		: 2;
	__IO uint32_t	SRC_INC	  		: 2;
	__IO uint32_t	DST_INC	  		: 2;                                        
	} ALT_CTL;
	//  } ;                                      
	__I  uint32_t   RESERVED1;	
}DMA_DATA_Type;

#define DMA_CH0_BASE                0x20001900UL
#define DMA_CH1_BASE                0x20001920UL
#define DMA_CH2_BASE                0x20001940UL
#define DMA_CH3_BASE                0x20001960UL
#define DMA_CH4_BASE                0x20001980UL
#define DMA_CH5_BASE                0x200019A0UL
#define DMA_CH0                     ((DMA_DATA_Type*)                DMA_CH0_BASE)
#define DMA_CH1                     ((DMA_DATA_Type*)                DMA_CH1_BASE)
#define DMA_CH2                     ((DMA_DATA_Type*)                DMA_CH2_BASE)
#define DMA_CH3                     ((DMA_DATA_Type*)                DMA_CH3_BASE)
#define DMA_CH4                     ((DMA_DATA_Type*)                DMA_CH4_BASE)
#define DMA_CH5                     ((DMA_DATA_Type*)                DMA_CH5_BASE)

#define DMA_ALT_CH0_BASE                0x20001910UL
#define DMA_ALT_CH1_BASE                0x20001930UL
#define DMA_ALT_CH2_BASE                0x20001950UL
#define DMA_ALT_CH3_BASE                0x20001970UL
#define DMA_ALT_CH4_BASE                0x20001990UL
#define DMA_ALT_CH5_BASE                0x200019B0UL
#define DMA_ALT_CH0                     ((DMA_DATA_Type*)                DMA_ALT_CH0_BASE)
#define DMA_ALT_CH1                     ((DMA_DATA_Type*)                DMA_ALT_CH1_BASE)
#define DMA_ALT_CH2                     ((DMA_DATA_Type*)                DMA_ALT_CH2_BASE)
#define DMA_ALT_CH3                     ((DMA_DATA_Type*)                DMA_ALT_CH3_BASE)
#define DMA_ALT_CH4                     ((DMA_DATA_Type*)                DMA_ALT_CH4_BASE)
#define DMA_ALT_CH5                     ((DMA_DATA_Type*)                DMA_ALT_CH5_BASE)

/* =========================================================================================================================== */
/* ================                                       DMA Task_struct                                     ================ */
/* =========================================================================================================================== */
typedef struct {                               /*!< (@ 0x20000100) DMA_DATA_Type Structure                                  	*/
  __IO uint32_t   *SOURCE;                     /*!< (@ 0x00000000) Primary source_end_ptr                                     */
  __IO uint32_t   *DESTION;                    /*!< (@ 0x00000004) Primary destion_end_ptr                                    */
//	union {
//		__IO uint32_t CTL;                          /*!< (@ 0x00000000) DMA countrl Register                                     */   
	struct {
	__IO uint32_t CYCLE_CTRL   	    : 3;          
	__IO uint32_t NEXT_USEBURST     : 1;     
	__IO uint32_t N_MINUS_1			: 10; 	
	__IO uint32_t R_POWER			: 4;  
	__I  uint32_t					: 7;
	__IO uint32_t	CIRC			: 1;
	__IO uint32_t	DATA_SIZE		: 2;
	__IO uint32_t	SRC_INC			: 2;
	__IO uint32_t	DST_INC			: 2;                                        
	} CTL;
//  } ;                                    
	__I  uint32_t   RESERVED0;
} TASK_Type;

#define TASK0_BASE		0x200019C0UL
#define TASK1_BASE		0x200019D0UL
#define TASK2_BASE		0x200019E0UL
#define TASK3_BASE		0x200019F0UL
#define TASK0           ((TASK_Type*)                TASK0_BASE)
#define TASK1           ((TASK_Type*)                TASK1_BASE)
#define TASK2           ((TASK_Type*)                TASK2_BASE)
#define TASK3           ((TASK_Type*)                TASK3_BASE)

#define TASK4_BASE		                0x20001A00UL
#define TASK5_BASE					          0x20001A10UL
#define TASK6_BASE					          0x20001A20UL
#define TASK7_BASE					          0x20001A30UL
#define TASK4                     ((TASK_Type*)                TASK4_BASE)
#define TASK5                     ((TASK_Type*)                TASK5_BASE)
#define TASK6                     ((TASK_Type*)                TASK6_BASE)
#define TASK7                     ((TASK_Type*)                TASK7_BASE)

#define TASK8_BASE		                0x20001A40UL
#define TASK9_BASE					          0x20001A50UL
#define TASK10_BASE					          0x20001A60UL
#define TASK11_BASE					          0x20001A70UL
#define TASK8                     ((TASK_Type*)                TASK8_BASE)
#define TASK9                     ((TASK_Type*)                TASK9_BASE)
#define TASK10                    ((TASK_Type*)                TASK10_BASE)
#define TASK11                    ((TASK_Type*)                TASK11_BASE)

//Dsize,Sinc,Dinc
#define D_BYTE  	0
#define D_HFWORD	1
#define D_WORD	  	2
#define D_NO		3

//chx
#define DMA_CTL_CH0 		0x01
#define DMA_CTL_CH1			0x02
#define DMA_CTL_CH2			0x04
#define DMA_CTL_CH3			0x08
#define DMA_CTL_CH4			0x10
#define DMA_CTL_CH5			0x20

#define use_burst_0 		0x00
#define use_burst_1 		0x01

typedef enum
{
	REQ_SEL_UART0_TX = 0x00,     /* REQx_SEL = 0x00 */
	REQ_SEL_UART0_RX = 0x01,     /* REQx_SEL = 0x01 */
	REQ_SEL_UART1_TX = 0x02,     /* REQx_SEL = 0x02 */
	REQ_SEL_UART1_RX = 0x03,     /* REQx_SEL = 0x03 */
	REQ_SEL_UART2_TX = 0x04,     /* REQx_SEL = 0x04 */
	REQ_SEL_UART2_RX = 0x05,     /* REQx_SEL = 0x05 */

	REQ_SEL_SPI0_TX  = 0x08,     /* REQx_SEL = 0x08 */
	REQ_SEL_SPI0_RX  = 0x09,     /* REQx_SEL = 0x09 */

	REQ_SEL_ERU0	= 0x0c,     /* REQx_SEL = 0x0c */
	REQ_SEL_ERU1	= 0x0d,     /* REQx_SEL = 0x0d */
	REQ_SEL_ERU2	= 0x0e,     /* REQx_SEL = 0x0e */
	REQ_SEL_ERU3	= 0x0f,     /* REQx_SEL = 0x0f */
}REQ_SEL_TypeDef;


extern volatile uint8_t	D_data0[100];
extern volatile uint8_t	D_data1[100];

void DMA_Config(DMA_DATA_Type* DMA_CHx,uint8_t chx,uint8_t req0_sel);
void DMA_ERU_Config(DMA_DATA_Type* DMA_CHx,uint8_t chx,uint8_t req0_sel);
void Ram0_ini(void);
void Ram1_Clear(void);

#endif


