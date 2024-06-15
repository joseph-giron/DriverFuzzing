#include <iostream>
#include <Windows.h>
#include <stdio.h>
#define drivername L"\\\\.\\\PHYSICALDRIVE0"

struct fakeforfuzzer {
	const char* first;
	DWORD second;
	DWORD third;
	int length;
};
extern "C" int LLVMFuzzerTestOneInput(const uint8_t * Data, size_t Size) {
	

	STORAGE_PROPERTY_QUERY query;
	_STORAGE_PROPERTY_ID qq;
	_STORAGE_ADAPTER_SERIAL_NUMBER yy;
	DISK_GEOMETRY test;
	
	query.QueryType = PropertyStandardQuery;
	query.PropertyId = StorageDeviceProperty;
	

	HANDLE device = CreateFile(TEXT("\\\\.\\PhysicalDrive0"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL,
		OPEN_EXISTING, 0, NULL);
	if (device == INVALID_HANDLE_VALUE) {
		std::cout << "Fail to CreateFile(\"\\\\.\\PhysicalDrive0\"): Error - " << GetLastError();
	}
	STORAGE_PROPERTY_QUERY query = {};
	query.PropertyId = StorageAdapterProperty;
	query.QueryType = PropertyStandardQuery;
	STORAGE_ADAPTER_DESCRIPTOR descriptor = {};
	DWORD read;

	bool res = DeviceIoControl(device, IOCTL_STORAGE_QUERY_PROPERTY, &query, sizeof(STORAGE_PROPERTY_QUERY),
		&descriptor, sizeof(STORAGE_DESCRIPTOR_HEADER), &read, NULL);
	if (!res) {
		std::cout << "GetTransferMode() : Error - " << GetLastError() << std::endl;
		return;
	}
	else {
		std::cout << "HDD TransferMode: ";
		if (descriptor.AdapterUsesPio)
			std::cout << "PIO " << descriptor.AdapterUsesPio << std::endl;
		else
			std::cout << "DMA" << std::endl;
	}
	CloseHandle(device);

		
	return 0;  // Values other than 0 and -1 are reserved for future use.
}

void printTransferMode() {
	
}


