A collection of Windows C files I use to fuzz drivers. Includes IOCTL finder, enumeration of device names, and their native paths, as well as the skeleton code to fuzz your own drivers. Utilizes Visual Studio 2022's experimental libfuzzer.

EnumDevices - use this tool to automatically enumerate all device drivers and servics, giving them the proper path names for use with our other projects.
\\.\exampledriver

Enum-IOCTL-Codes - tool for looping through all IOCTL codes 0x00000000 though 0xFFFFFFFF looking for a non error code via DeviceIoControl()

GetDeviceSymLinkName - used in tandam with EnumDevices for the Symbolic link name used with CreateFile and DeviceIoControl()

LibFuzzDeviceIoControl - Bare bones code that allows us to fuzz said drivers using found IOCTL codes and random structure data. Includes pre-compiled DLL's needed to run our libfuzz compiled binaries. Also includes a build script.
