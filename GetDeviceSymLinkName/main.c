#include <Windows.h>
#include <Setupapi.h>
#include <stdio.h>
#pragma comment(lib, "Setupapi.lib")

void GetSymbolicLinkFromPDO(const char* physicalDeviceObjectName) {
    HDEVINFO hDevInfo;
    SP_DEVINFO_DATA devInfoData;
    DWORD index = 0;

    hDevInfo = SetupDiGetClassDevs(NULL, NULL, NULL, DIGCF_ALLCLASSES);

    if (hDevInfo == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Failed to get device information set.\n");
        return;
    }

    devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    while (SetupDiEnumDeviceInfo(hDevInfo, index, &devInfoData)) {
        CHAR devicePhysicalObjectName[MAX_PATH];
        if (SetupDiGetDeviceRegistryPropertyA(
                hDevInfo, &devInfoData, SPDRP_PHYSICAL_DEVICE_OBJECT_NAME,
                NULL, (PBYTE)devicePhysicalObjectName, sizeof(devicePhysicalObjectName), NULL)) {
            if (strcmp(physicalDeviceObjectName, devicePhysicalObjectName) == 0) {
                CHAR symbolicLinkName[MAX_PATH];
                if (SetupDiGetDeviceInterfaceDetailA(
                        hDevInfo, &devInfoData, NULL, NULL, NULL, NULL)) {
                    printf("Symbolic Link Name: %s\n", symbolicLinkName);
                }
            }
        }

        index++;
    }

    SetupDiDestroyDeviceInfoList(hDevInfo);
}

int main() {
    const char* physicalDeviceObjectName = "your_physical_device_object_name_here";
    GetSymbolicLinkFromPDO(physicalDeviceObjectName);
    return 0;
}
