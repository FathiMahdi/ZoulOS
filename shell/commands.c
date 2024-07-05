#include "commands.h"
#include "shell.h"


// local functions
static void TerminalInit(void);


/// @brief shell command handler
/// @param Command 
void CommandHandler(const char Command)
{


    // reboot
    if(strcmp(Command,"reboot")==0)
    {
        // system restart
        NVIC_SystemReset();
    }
}




