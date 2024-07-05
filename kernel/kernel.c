#include "kernel.h"
#include "debug.h"
#include "debug.h"
#include "system_ch32v20x.h"
#include "ch32v20x.h"
#include "shell.h"

static void TerminalInit(uint32_t baudrate);
static void HWInit(void);




/// @brief Kernel Initialization
/// @param  void
void KernelInit(void)
{
    // hardware Initialization
    HWInit();

    // shell initialization
    ShellInit();
}


/// @brief start ZoulOS
void KernelStart(void)
{
    ShellStart();
}


/// @brief MCU software reset
/// @param  
void kernelRestart(void)
{
    NVIC_SystemReset();
}



/// @brief Hardware Initialization
/// @param  
static void HWInit(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    SystemCoreClockUpdate();
	
    Delay_Init();

    TerminalInit(TERMINAL_BAUD_RATE);
}


/// @brief Terminal intialization
/// @param baudrate 
static void TerminalInit(uint32_t baudrate)
{
    GPIO_InitTypeDef  GPIO_InitStructure  = {0};
    USART_InitTypeDef USART_InitStructure = {0};
    NVIC_InitTypeDef  NVIC_InitStructure  = {0};


    // enable  clock for (AFIO, PORTA, USART1)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

    // deine Rx Tx pin GPIO speed
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;


    // define terminal Tx pin
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; // Tx pin
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // define terminal rx pin
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; // Rx pin
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // Define UART Mode
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    // Define UART baudrate
    USART_InitStructure.USART_BaudRate = baudrate;

    // define word length
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;

    // define stop bit
    USART_InitStructure.USART_StopBits = USART_StopBits_1;

    // define parity 
    USART_InitStructure.USART_Parity = USART_Parity_No;

    // define flow control
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    
    // UART initialization
    USART_Init(TERMINAL, &USART_InitStructure);

    // enable UART Rx interrupt
    USART_ITConfig(TERMINAL, USART_IT_RXNE, ENABLE);

    // define UART interrupt channel
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;

    // define UART interrupt priority
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;

    // enable interrupt
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    // enable UART Rx interrupt
    NVIC_Init(&NVIC_InitStructure);

    // enable UART
    USART_Cmd(TERMINAL, ENABLE);

}



// void USART1_IRQHandler(void)
// {
//     if(USART_GetITStatus(TERMINAL, USART_IT_RXNE) != RESET)
//     {
//         RxBuffer1[RxCnt1++] = USART_ReceiveData(USART2);

//         if(RxCnt1 == TxSize2)
//         {
//             USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
//             Rxfinish1 = 1;
//         }
//     }
// }