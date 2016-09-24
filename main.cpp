#include "ApplicationManager.h"

#include <iostream>

int main()
{
	ActionType ActType;
	//Create an object of ApplicationManager
	ApplicationManager AppManager;

	try
	{
	    do
        {
            //Read user action
            ActType = AppManager.GetUserAction();

            //Execute the action
            AppManager.ExecuteAction(ActType);

            //Update the drawing window
            AppManager.UpdateInterface();
            AppManager.SyncInterface();
        } while (ActType != EXIT);
	}
	catch(const char* Error)
	{
	    std::cerr << Error << std::endl;
	    exit(1);
	}
    return 0;
}
