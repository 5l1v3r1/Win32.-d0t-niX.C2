@echo off

rem Copy Source to local Git-repo
rd "F:\GitHub Data\Win32.-d0t-niX.C2\BIN" /s /q
rd "F:\GitHub Data\Win32.-d0t-niX.C2\Win32.(d0t)niX.C2" /s /q
xcopy "F:\VMware Data\VMware Shared Folder UpDown\(d0t)niX-repo" "F:\GitHub Data\Win32.-d0t-niX.C2\" /i /s /v /y

rem Remove files of type: [.aps] [.user]
del "F:\GitHub Data\Win32.-d0t-niX.C2\Win32.(d0t)niX.C2\(d0t)niX\*.user" /f
del "F:\GitHub Data\Win32.-d0t-niX.C2\Win32.(d0t)niX.C2\(d0t)niX\Resource-Files\*.aps" /f

rem Move Binaries to BIN folder in local Git-repo
xcopy "F:\GitHub Data\Win32.-d0t-niX.C2\Win32.(d0t)niX.C2\BIN" "F:\GitHub Data\Win32.-d0t-niX.C2\BIN\" /i /s /v /y
rd "F:\GitHub Data\Win32.-d0t-niX.C2\Win32.(d0t)niX.C2\BIN" /s /q

rem remove files of type: [.ilk] [.pdb] [.ipdb] [.iobj] 
del "F:\GitHub Data\Win32.-d0t-niX.C2\BIN\Debug\*.ilk" /f
del "F:\GitHub Data\Win32.-d0t-niX.C2\BIN\Debug\*.pdb" /f
del "F:\GitHub Data\Win32.-d0t-niX.C2\BIN\Release\*.pdb" /f
del "F:\GitHub Data\Win32.-d0t-niX.C2\BIN\Release\*.ipdb" /f
del "F:\GitHub Data\Win32.-d0t-niX.C2\BIN\Release\*.iobj" /f