@for /r %%i in (Samples\*) do @(
		@echo %%i
		@x64\Debug\MiniJavaCompiler.exe %%i > Outputs\%%~ni.txt
	)