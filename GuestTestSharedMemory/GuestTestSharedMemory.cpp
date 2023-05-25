#include <iostream>
#include <WindowsSharedMemory.h>
#include <Communication.h>

int main()
{
	SharedMemObject<MySharedObject> guestAccess(SHARED_MEMORY_NAME);

	printf("Waiting Host ...\n");

	while (guestAccess.Init() == false)
		Sleep(10);

	printf("Waiting Message ...\n");

	while (guestAccess->mbWasWritedByHost == false)
		Sleep(10);

	printf("%s\n", guestAccess->mString);

	guestAccess->mbWasReadedByGuest = true;
}
