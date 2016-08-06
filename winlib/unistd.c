#include <minwin.h>
#include <unistd.h>

ssize_t pread(int fd, void *buffer, size_t count, off_t offset)
{
	OVERLAPPED overlapped = { 0 };
	HANDLE native_handle = (HANDLE)_get_osfhandle(fd);
	DWORD retval;

	if (native_handle == INVALID_HANDLE_VALUE) {
		errno = EBADF;
		return -1;
	}

	overlapped.Offset = (DWORD)offset;
	overlapped.OffsetHigh = ((DWORD)offset >> 32);

	if (!ReadFile(native_handle, buffer, (DWORD) count, &retval, &overlapped)) {
		if (GetLastError() != ERROR_IO_PENDING) {
			return -1;
		} else {
			if (!GetOverlappedResult(native_handle, &overlapped, &retval, TRUE)) {
				return -1;
			}
		}
	}

	return retval;
}

ssize_t pwrite(int fd, const void *buffer, size_t count, off_t offset)
{
	OVERLAPPED overlapped = { 0 };
	HANDLE native_handle = (HANDLE)_get_osfhandle(fd);
	DWORD retval;

	if (native_handle == INVALID_HANDLE_VALUE) {
		errno = EBADF;
		return -1;
	}

	overlapped.Offset = (DWORD)offset;
	overlapped.OffsetHigh = ((DWORD)offset >> 32);

	if (!WriteFile(native_handle, buffer, (DWORD)count, &retval, &overlapped)) {
		if (GetLastError() != ERROR_IO_PENDING) {
			return -1;
		}
		else {
			if (!GetOverlappedResult(native_handle, &overlapped, &retval, TRUE)) {
				return -1;
			}
		}
	}

	return retval;
}

int truncate(const char *path, off_t length) {
	HANDLE native_handle;
	DWORD result;
	int retval;

	native_handle = CreateFile(path, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (native_handle == INVALID_HANDLE_VALUE) {
		errno = EBADF;
		return -1;
	}

	/* Insane error checking - from msdn
	   If the function succeeds and lpDistanceToMoveHigh is NULL, the return value is the low-order DWORD of the new file pointer.
	   If the function returns a value other than INVALID_SET_FILE_POINTER, the call to SetFilePointer has succeeded. You do not need to call GetLastError.
	*/
	result = SetFilePointer(native_handle, length, NULL, FILE_BEGIN);
	
	if (result == INVALID_SET_FILE_POINTER) {
		CloseHandle(native_handle);
		return -1;
	}

	retval = SetEndOfFile(native_handle);

	CloseHandle(native_handle);

	return retval;
}

int usleep(unsigned int useconds) {
	static LARGE_INTEGER frequency;
	static int init = 0;
	LARGE_INTEGER start, end, duration;

	if (!init) {
		QueryPerformanceFrequency(&frequency);
		init = 1;
	}

	QueryPerformanceCounter(&start);
	duration.QuadPart = frequency.QuadPart * ((double)useconds / 1000000.0);

	do
	{
		QueryPerformanceCounter(&end);
	} while (end.QuadPart - start.QuadPart < duration.QuadPart);

	return 0;
}

long sysconf(int name) {
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	MEMORYSTATUSEX status;

	switch (name) {
	case _SC_PAGESIZE:
		return sysinfo.dwPageSize;
	case _SC_NPROCESSORS_ONLN:
	case _SC_NPROCESSORS_CONF:
		return sysinfo.dwNumberOfProcessors;
	case _SC_PHYS_PAGES:
		status.dwLength = sizeof(status);
		GlobalMemoryStatusEx(&status);
		return (status.ullTotalPhys / sysinfo.dwPageSize);
	}

	return -1;
}

int flock(int fd, int op)
{
	HANDLE native_handle = (HANDLE)_get_osfhandle(fd);
	/* You must initialize the event to 0, can't cheat with NULL overlapped for unlockfileex */
	OVERLAPPED overlapped = {0, 0, 0, 0, NULL};


	if (native_handle == INVALID_HANDLE_VALUE) {
		errno = EBADF;
		return -1;
	}

	/* Unix unlocks before trying the lock too 
	   but we're not going to check to see if it actually
	   succeeded */
	UnlockFileEx(native_handle, 0, 1, 0, &overlapped);
	/* not yet complete */
	return -1;
}