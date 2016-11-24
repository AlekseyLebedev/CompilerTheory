@for /r %%i in (BadSamples\*) do @(
		@echo %%i
		@x64\Debug\MiniJavaCompiler.exe %%i > Outputs\%%~ni.txt
	)