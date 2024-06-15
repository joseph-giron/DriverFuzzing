#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>
#include <cstdint>
#define IOCTL 0x1234
// To get device names, run the enumdevices.exe
// For IOCTL code numbers, run the Enum-IOCTL-Codes.exe
// see https://learn.microsoft.com/en-us/windows/win32/api/ioapiset/nf-ioapiset-deviceiocontrol

extern "C" int LLVMFuzzerTestOneInput(const uint8_t * data, size_t size) 
{
    const char* devicePath = "\\\\.\\YourDeviceObjectPath";

    HANDLE hDevice = CreateFileA(
        devicePath,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hDevice == INVALID_HANDLE_VALUE) 
    {
        return 0;
    }

    // Call DeviceIoControl with the input data
    DWORD bytesReturned;

    DeviceIoControl(
        hDevice,
        IOCTL, // Replace with your IOCTL code
        (LPVOID)data,
        (DWORD)size,
        NULL,
        0,
        &bytesReturned,
        NULL
    );

    CloseHandle(hDevice);

    return 0;
}
extern "C" int LLVMFuzzerInitialize(int* argc, char*** argv) 
{
    printf("...test...");
    getchar();
    return 0;
}