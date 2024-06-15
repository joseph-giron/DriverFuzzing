#include <stdio.h>
#include <windows.h>
#include <Setupapi.h>
#pragma comment(lib, "Setupapi.lib")


void ReplaceDevicePath(char* devicePath) 
{
    const char* searchStr = "\\Device\\";
    const char* replaceStr = "\\\\.\\";
    char* match;

    while ((match = strstr(devicePath, searchStr)) != NULL) 
	{
        memmove(match + strlen(replaceStr), match + strlen(searchStr), strlen(match + strlen(searchStr)) + 1);
        memcpy(match, replaceStr, strlen(replaceStr));
    }
}

void EnumerateDevices() 
{
    HDEVINFO hDevInfo;
    SP_DEVINFO_DATA devInfoData;
    DWORD index = 0;

    hDevInfo = SetupDiGetClassDevs(NULL, NULL, NULL, DIGCF_PRESENT | DIGCF_ALLCLASSES);

    if (hDevInfo == INVALID_HANDLE_VALUE) 
	{
        printf("Failed to get device information set.\r\n");
        return;
    }

    devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    FILE* file = fopen("output.txt", "w");
    if (file == NULL) 
	{
        fprintf(stderr, "Failed to open output.txt for writing.\n");
        SetupDiDestroyDeviceInfoList(hDevInfo);
        return;
    }

    while (SetupDiEnumDeviceInfo(hDevInfo, index, &devInfoData)) 
	{
		CHAR friendlyName[MAX_PATH];
        CHAR deviceLocationPaths[MAX_PATH];
		CHAR deviceDescription[MAX_PATH];

        if (SetupDiGetDeviceRegistryPropertyA(
                hDevInfo, &devInfoData, SPDRP_FRIENDLYNAME,
                NULL, (PBYTE)friendlyName, sizeof(friendlyName), NULL)) 
		{
   			printf("Friendly Name:\r\n %s \r\n",friendlyName);
			fprintf(file, "Friendly Name:\r\n %s \r\n", friendlyName);
        }
		if (SetupDiGetDeviceRegistryPropertyA(
                hDevInfo, &devInfoData, SPDRP_DEVICEDESC,
                NULL, (PBYTE)deviceDescription, sizeof(deviceDescription), NULL)) 
		{
            printf("Device Description:\r\n %s \r\n", deviceDescription);
			fprintf(file,"Device Description:\r\n %s \r\n", deviceDescription);
        }


        if (SetupDiGetDeviceRegistryPropertyA(
                hDevInfo, &devInfoData, SPDRP_PHYSICAL_DEVICE_OBJECT_NAME,
                NULL, (PBYTE)deviceLocationPaths, sizeof(deviceLocationPaths), NULL)) 
		{

			ReplaceDevicePath(deviceLocationPaths);
   			printf("Device Location Path:\r\n %s \r\n",deviceLocationPaths);
			fprintf(file, "Device Location Path:\r\n %s \r\n", deviceLocationPaths);
        }

        index++;
    }
	fclose(file);
    SetupDiDestroyDeviceInfoList(hDevInfo);
}

int main() 
{
	EnumerateDevices();
	getchar();
    return 0;
}
