rc.exe MyResource.rc 
cl.exe /c /EHsc GuruDarshan.cpp
link.exe GuruDarshan.obj MyResource.res /SUBSYSTEM:WINDOWS
