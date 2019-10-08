@echo off

rem Copy Source to local Git-repo
rd "F:\GitHub Data\N0T-iLLerka.X\BIN" /s /q
rd "F:\GitHub Data\N0T-iLLerka.X\Win32.N0T-iLLerka.X" /s /q
xcopy "F:\VMware Data\VMware Shared Folder UpDown\N0T-iLLerka.X-beta" "F:\GitHub Data\N0T-iLLerka.X\" /i /s /v /y

rem Remove files of type: [.aps] [.user]
del "F:\GitHub Data\N0T-iLLerka.X\Win32.N0T-iLLerka.X\N0T-iLLerka\N0T-iLLerka.vcxproj.user" /f
del "F:\GitHub Data\N0T-iLLerka.X\Win32.N0T-iLLerka.X\N0T-iLLerka\Resource-Files\*.aps" /f

rem Move Binaries to BIN folder in local Git-repo
xcopy "F:\GitHub Data\N0T-iLLerka.X\Win32.N0T-iLLerka.X\BIN" "F:\GitHub Data\N0T-iLLerka.X\BIN\" /i /s /v /y
rd "F:\GitHub Data\N0T-iLLerka.X\Win32.N0T-iLLerka.X\BIN" /s /q

rem remove files of type: [.ilk] [.pdb] [.ipdb] [.iobj] 
del "F:\GitHub Data\N0T-iLLerka.X\BIN\Debug\*.ilk" /f
del "F:\GitHub Data\N0T-iLLerka.X\BIN\Debug\*.pdb" /f
del "F:\GitHub Data\N0T-iLLerka.X\BIN\Release\*.pdb" /f
del "F:\GitHub Data\N0T-iLLerka.X\BIN\Release\*.ipdb" /f
del "F:\GitHub Data\N0T-iLLerka.X\BIN\Release\*.iobj" /f