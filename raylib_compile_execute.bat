::@echo off
:: .
:: Compile your examples using:  raylib_compile_execute.bat raylib/examples/core/core_basic_window.c
:: .
:: > Setup required Environment
:: -------------------------------------
set RAYLIB_INCLUDE_DIR=".\raylib\src"
set RAYLIB_LIB_DIR=".\raylib\src"
set RAYLIB_RES_FILE=".\raylib\src\raylib.rc.data"
set COMPILER_DIR=".\tcc"
set COMPILER_LIBS=-lmsvcrt -lraylib -lopengl32 -lgdi32 -lwinmm -lkernel32 -lshell32 -luser32 -Wl,-subsystem=gui
set PATH=%PATH%;%COMPILER_DIR%
:: Get full filename path for input file %1
set FILENAME=%~f1
set NAMEPART=%FILENAME:~0,-2%
cd %~dp0
:: .
:: > Cleaning latest build
:: ---------------------------
cmd /c if exist %NAMEPART%.exe del /F %NAMEPART%.exe
:: .
:: > Compiling program
:: --------------------------
:: -s        : Remove all symbol table and relocation information from the executable
:: -O2       : Optimization Level 2, this option increases both compilation time and the performance of the generated code
:: -std=c99  : Use C99 language standard
:: -Wall     : Enable all compilation Warnings
:: -mwindows : Compile a Windows executable, no cmd window
tcc -o %NAMEPART%.exe %FILENAME% %RAYLIB_RES_FILE% -s -O2 -std=c99 -Wall -Iexternal -DPLATFORM_DESKTOP -I%RAYLIB_INCLUDE_DIR% -I%RAYLIB_LIB_DIR% %COMPILER_LIBS%
:: .
:: > Executing program
:: -------------------------
cmd /c if exist %NAMEPART%.exe %NAMEPART%.exe