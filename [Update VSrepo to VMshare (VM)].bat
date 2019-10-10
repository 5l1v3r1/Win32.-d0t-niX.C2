@echo off

rem Copy Visual Studio Repository to VMware Share
rd "Z:\VMware Shared Folder UpDown\(d0t)niX-repo\Win32.(d0t)niX.C2\(d0t)niX" /s /q
xcopy "D:\Visual Studio Data\source\repos\(d0t)niX-repo" "Z:\VMware Shared Folder UpDown\(d0t)niX-repo\" /i /s /v /y