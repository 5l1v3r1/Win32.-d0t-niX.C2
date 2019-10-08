@echo off

rem Copy Visual Studio Repository to VMware Share
rd "Z:\VMware Shared Folder UpDown\N0T-iLLerka.X-beta\Win32.N0T-iLLerka.X\N0T-iLLerka" /s /q
xcopy "D:\Visual Studio Data\source\repos\N0T-iLLerka.X-beta" "Z:\VMware Shared Folder UpDown\N0T-iLLerka.X-beta\" /i /s /v /y