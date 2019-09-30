@echo off

ifEx:
	del "%s" /f
	if exist "%s" (
		goto ifEx
	)

	del "%s" /f