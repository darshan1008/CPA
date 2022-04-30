rc.exe MyResources.rc 
cl.exe /c /EHsc toolchain_assembly_dlg.c
link.exe toolchain_assembly_dlg.obj /SUBSYSTEM:WINDOWS

