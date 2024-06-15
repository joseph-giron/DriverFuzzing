#include <stdio.h>
#include <windows.h>
// Replace with the actual device path from EnumerateDevices. The \Device\Name is an alias for \\\\.\\Name
const char* devicePath = "\\\\.\\YourDeviceObjectPath";

BOOL IsUserAdmin() 
{
    BOOL fIsAdmin = FALSE;
    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    PSID AdministratorsGroup;

    if (AllocateAndInitializeSid(&NtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID,
    DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &AdministratorsGroup)) 
	{
        if (!CheckTokenMembership(NULL, AdministratorsGroup, &fIsAdmin)) 
		{
            fIsAdmin = FALSE;
        }

        FreeSid(AdministratorsGroup);
    }
    return fIsAdmin;
}

int main() 
{

	if(!IsUserAdmin())
	{
		printf("Running this as a non admin means you might not be able communicate with the driver!\r\n");
	}
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
        DWORD error = GetLastError();
        fprintf(stderr, "Failed to open device. Error code: %lu\n", error);
        return error;
    }
	
    // Enumerate and process IOCTL codes
	// Looking at MS include files, there only seemns to be about 65535 codes (max size of signed int)
	// however microft claims there is no limit in the documentation so you could make it 
	// 0x00000000-0xffffffff but that might take a while. Ditto for 64 bit integer ranges.
    for (DWORD ioctlCode = 0x0000; ioctlCode <= 0xffff; ioctlCode++) 
	{
        DWORD bytesReturned;
        BOOL success = DeviceIoControl(
            hDevice,
            ioctlCode,
            NULL,
            0,
            NULL,
            0,
            &bytesReturned,
            NULL
        );

        if(success) 
		{
            printf("IOCTL code 0x%08lx succeeded.\n", ioctlCode);
        } 
		else 
		{
            DWORD error = GetLastError();
            fprintf(stderr, "IOCTL code 0x%08lx failed. Error code: %lu\n", ioctlCode, error);
        }
    }

    // Close the device handle
    CloseHandle(hDevice);
	getchar();
    return 0;
}
