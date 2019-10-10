@echo off

rem Copy VMware Share to Visual Studio Repository
rd "D:\Visual Studio Data\source\repos\(d0t)niX-repo\Win32.(d0t)niX.C2\(d0t)niX" /s /q
xcopy "Z:\VMware Shared Folder UpDown\(d0t)niX-repo" "D:\Visual Studio Data\source\repos\(d0t)niX-repo\" /i /s /v /y