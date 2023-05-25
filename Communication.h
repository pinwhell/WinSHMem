#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <atomic>

#define SHARED_MEMORY_NAME "Global\\TestSHMem"

#pragma pack(push, 1)

struct MySharedObject {
	MySharedObject() {}

	void Reset()
	{
		mbWasWritedByHost = false;
		mbWasReadedByGuest = false;
		memset(mString, 0x0, sizeof(mString));
	}

	MySharedObject& operator=(const MySharedObject& other)
	{
		return *this;
	}

	std::atomic_bool mbWasWritedByHost;
	std::atomic_bool mbWasReadedByGuest;
	char mString[256] { 0 };
};

#pragma pack(pop)
