@echo off

rem Copy Source-Code with Binaries to local Git-repo
rd "Win32.N0T-iLLerka.X" /s /q
xcopy "F:\Visual Studio Data\source\repos\Win32.N0T-iLLerka.X" "F:\GitHub Data\N0T-iLLerka.X\Win32.N0T-iLLerka.X\" /i /s /v /y

rem remove files of type: [.aps] [.user]
del "Win32.N0T-iLLerka.X\N0T-iLlerka\N0T-iLLerka.vcxproj.user" /f
del "Win32.N0T-iLLerka.X\N0T-iLlerka\Resource-Files\*.aps" /f

rem Move Binaries to BIN folder in local Git-repo
xcopy "F:\GitHub Data\N0T-iLLerka.X\Win32.N0T-iLLerka.X\BIN" "F:\GitHub Data\N0T-iLLerka.X\BIN\" /i /s /v /y
rd "Win32.N0T-iLLerka.X\BIN" /s /q

rem remove files of type: [.ilk] [.pdb] [.ipdb] [.iobj] 
del "BIN\Debug\*.ilk" /f
del "BIN\Debug\*.pdb" /f
del "BIN\Release\*.pdb" /f
del "BIN\Release\*.ipdb" /f
del "BIN\Release\*.iobj" /f