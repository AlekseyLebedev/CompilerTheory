@for /r %%i in (Samples\*) do @(
		@echo %%i
		@x64\Release\MiniJavaCompiler.exe %%i > Outputs\%%~ni.txt
	)