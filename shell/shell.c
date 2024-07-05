#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"
#include "kernel.h"

static inline void clearScreen(void);

/// @brief ZoulOS shell Initialization
/// @param  
void ShellInit(void)
{

    // start shell
    ShellStart();

    
}


void ShellStart(void)
{
    clearScreen();

    printf("-------------- ZoulOS V%d.%d.%d --------------\r\n\r\n",MAJOR_VERSION,MINOR_VERSION,PATHC_VERSION);

    printf("- For help type: HELP \r\n");
    
    printf("Z:\\>");

    while(1)
    {
        if(USART_ReceiveData(TERMINAL))
        {
            printf("%c",(uint8_t)USART_ReceiveData(USART1));
        }
    }

}


static inline void clearScreen(void)
{
    printf("\033[2J");
}