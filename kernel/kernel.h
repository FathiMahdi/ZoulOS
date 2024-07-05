#ifndef KERNEL_H_
#define KERNEL_H_


#include <stdint.h>
#include <stdbool.h>


// OS version
#define MAJOR_VERSION 0
#define MINOR_VERSION 1
#define PATHC_VERSION 0


// clock configuration
#define SYSTEM_FCLK 18000000 // Hz



// terminal uart port
#define TERMINAL             USART1
#define TERMINAL_BAUD_RATE   115200 // bit/s



// global functions 
void KernelInit(void);
void KernelStart(void);
void kernelRestart(void);
bool kernelLoad(uint32_t prgram_address);



#endif