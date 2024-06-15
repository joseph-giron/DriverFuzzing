set progname = "whatever.exe"
set progpath = "c:\\whatever\\whatever"

msvc.exe /JMC /permissive- /ifcOutput "Debug\" /GS /analyze- /W3 /Zc:wchar_t /Zi /fsanitize=fuzzer /Gm- /Od /sdl /Fd"Debug\vc143.pdb" /Zc:inline /fp:precise /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_UNICODE" /D "UNICODE" /errorReport:prompt /fsanitize=address /WX- /Zc:forScope /RTC1 /Gd /Oy- /MDd /FC /Fa"Debug\" /EHsc /nologo /Fo"Debug\" /Fp"Debug\%progname%.pch" /diagnostics:column  

link.exe /OUT:"%progpath%\\%progname%" /MANIFEST /NXCOMPAT /PDB:"%progpath%\\%progname%\Debug\%progname%.pdb" /DYNAMICBASE "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib" /DEBUG /MACHINE:X86 /INCREMENTAL /PGD:"%progpath%\Debug\%progname%.pgd" /SUBSYSTEM:CONSOLE /MANIFESTUAC:"level='asInvoker' uiAccess='false'" /ManifestFile:"Debug\%progname%.exe.intermediate.manifest" /LTCGOUT:"Debug\%progname%.iobj" /ERRORREPORT:PROMPT /ILK:"Debug\%progname%.ilk" /NOLOGO /LIBPATH:"c:\extralibs\dirs" /TLBID:1 

echo "All done"