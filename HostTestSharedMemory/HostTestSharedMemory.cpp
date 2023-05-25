// TestSharedMemory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <WindowsSharedMemory.h>
#include <Communication.h>

int main()
{
    HostSharedObject<MySharedObject> hostAccess(SHARED_MEMORY_NAME);

    if (hostAccess.Init() == false)
        return 1;

    hostAccess->Reset();

    strcpy(hostAccess->mString, "This is a Message Across Process\n");
    hostAccess->mbWasWritedByHost = true;

    printf("Waiting Guest Read Message ...\n");

    while (hostAccess->mbWasReadedByGuest == false)
        Sleep(10);

    return 0;
}