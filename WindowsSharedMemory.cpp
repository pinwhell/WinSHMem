#include "WindowsSharedMemory.h"

WindowsSharedMemory::WindowsSharedMemory()
	: mEntry(nullptr)
	, mSize(0)
	, mhMem(0x0)

{}

WindowsSharedMemory::~WindowsSharedMemory()
{}

void WindowsSharedMemory::setName(const std::string & name)
{
	mName = name;
}

void* WindowsSharedMemory::getEntry() const
{
	return mEntry;
}

void WindowsSharedMemory::setSize(size_t size)
{
	mSize = size;
}

bool WindowsSharedMemory::TryCreate()
{
	mhMem = CreateFileMappingA(
		INVALID_HANDLE_VALUE,			// use paging file
		NULL,							// default security
		PAGE_READWRITE,					// read/write access
		0,								// maximum object size (high-order DWORD)
		DWORD(mSize),							// maximum object size (low-order DWORD)
		mName.c_str());                 // name of mapping object

	if (mhMem == NULL)
		return false;

	return true;
}

bool WindowsSharedMemory::TryOpen()
{
	mhMem = OpenFileMappingA(
		FILE_MAP_ALL_ACCESS,
		FALSE,
		mName.c_str()
	);

	if (mhMem == NULL)
		return false;

	return true;
}

bool WindowsSharedMemory::Open()
{
	if (mhMem == NULL) // Hasnt Been Open Yet
	{
		if (TryOpen() == false)
			return false;
	}

	mEntry = (LPVOID)MapViewOfFile(
		mhMem,					// handle to map object
		FILE_MAP_ALL_ACCESS,	// read/write permission
		0,
		0,
		mSize);

	if (mEntry == nullptr)
		return false;

	return true;
}