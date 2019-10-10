@echo off

IfEx:
	del "%s" /f
	if exist "%s" (
		goto IfEx
	)

	del "%s" /f