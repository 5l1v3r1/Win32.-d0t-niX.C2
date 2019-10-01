@echo off
rd "Win32.N0T-iLLerka.X" /s /q

xcopy "F:\Visual Studio Data\source\repos\Win32.N0T-iLLerka.X" "F:\GitHub Data\N0T-iLLerka.X\Win32.N0T-iLLerka.X\" /E /V /Y

rd "Win32.N0T-iLLerka.X\N0T-iLLerka\Release" /s /q
rd "Win32.N0T-iLLerka.X\N0T-iLLerka\Debug" /s /q

del "Win32.N0T-iLLerka.X\N0T-iLLerka\Resource-Files\N0T-iLLerka.aps" /f
del "Win32.N0T-iLLerka.X\N0T-iLLerka\N0T-iLLerka.vcxproj.user" /f

del "Win32.N0T-iLLerka.X\Release\N0T-iLLerka.iobj" /f
del "Win32.N0T-iLLerka.X\Release\N0T-iLLerka.ipdb" /f
del "Win32.N0T-iLLerka.X\Release\N0T-iLLerka.pdb" /f
del "Win32.N0T-iLLerka.X\Debug\N0T-iLLerka.pdb" /f
del "Win32.N0T-iLLerka.X\Debug\N0T-iLLerka.ilk" /f