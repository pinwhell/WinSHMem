#pragma once

#include <string>
#include <Windows.h>
#include <memory>

class WindowsSharedMemory {
public:
	WindowsSharedMemory();
	~WindowsSharedMemory();

	void* getEntry() const;

protected:
	void setName(const std::string& name);
	void setSize(size_t size);
	bool Open();
	bool TryCreate();
	bool TryOpen();
private:
	HANDLE mhMem;
	std::string mName;
	void* mEntry;
	size_t mSize;
};

template<typename T>
class SharedMemObject : public WindowsSharedMemory {
public:
	SharedMemObject();
	SharedMemObject(const std::string& name);
	virtual bool Init();
	T* get();
	T* operator->();
};

template<typename T>
class HostSharedObject : public SharedMemObject<T> {
public:
	HostSharedObject();
	HostSharedObject(const std::string& name);
	bool Init() override;
};

template<typename T>
inline SharedMemObject<T>::SharedMemObject()
{
	// Setting Size of Object by Default
	setSize(sizeof(T));
}

template<typename T>
inline SharedMemObject<T>::SharedMemObject(const std::string& name)
{
	setName(name);
	setSize(sizeof(T));
}

template<typename T>
inline bool SharedMemObject<T>::Init()
{
	if (Open() == false)
		return false;

	return true;
}

template<typename T>
inline T* SharedMemObject<T>::operator->()
{
	return get();
}

template<typename T>
inline T* SharedMemObject<T>::get()
{
	return (T*) getEntry();
}

template<typename T>
inline HostSharedObject<T>::HostSharedObject()
{
}

template<typename T>
inline HostSharedObject<T>::HostSharedObject(const std::string& name)
	: SharedMemObject<T>(name)
{
}

template<typename T>
inline bool HostSharedObject<T>::Init()
{
	if (SharedMemObject<T>::TryCreate() == false)
		return false;

	if (SharedMemObject<T>::Init() == false)
		return false;

	return true;
}
