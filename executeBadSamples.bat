@for /r %%i in (BadSamples\*) do @(
		@echo %%i
		@x64\Release\MiniJavaCompiler.exe %%i > Outputs\%%~ni.txt
	)