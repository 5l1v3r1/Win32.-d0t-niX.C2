@echo off

rem Copy VMware Share to Visual Studio Repository
rd "D:\Visual Studio Data\source\repos\N0T-iLLerka.X-beta\Win32.N0T-iLLerka.X\N0T-iLLerka" /s /q
xcopy "Z:\VMware Shared Folder UpDown\N0T-iLLerka.X-beta" "D:\Visual Studio Data\source\repos\N0T-iLLerka.X-beta\" /i /s /v /y