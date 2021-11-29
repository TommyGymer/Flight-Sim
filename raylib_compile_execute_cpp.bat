::@echo off
:: .
:: Compile your examples using:  raylib_compile_execute.bat raylib/examples/core/core_basic_window.c
:: .
:: > Setup required Environment
:: -------------------------------------
::set RAYLIB_INCLUDE_DIR="raylib\src"
::set RAYLIB_LIB_DIR=".\raylib\src"
::set RAYLIB_RES_FILE=".\raylib\src\raylib.rc.data"
::set COMPILER_DIR=".\raylib"
::set COMPILER_LIBS=-lmsvcrt -lopengl32 -lgdi32 -lwinmm -lkernel32 -lshell32 -luser32 -L%RAYLIB_INCLUDE_DIR%
::set PATH=%PATH%;%COMPILER_DIR%
:: Get full filename path for input file %1
set FILENAME=%~f1
set NAMEPART=%FILENAME:~0,-2%
::cd %~dp0
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
::gcc -o %NAMEPART%.exe %FILENAME% %RAYLIB_RES_FILE% -s -O2 -Wall -Iexternal -DPLATFORM_DESKTOP -I%RAYLIB_INCLUDE_DIR% -I%RAYLIB_LIB_DIR% %COMPILER_LIBS%
::gcc -Wall %FILENAME% -o %NAMEPART%.exe -I%RAYLIB_INCLUDE_DIR%
g++ -MMD -MP -c -std=c++17 -I include src/main.cpp -o bin/main.o
g++  bin/main.o -o bin/app -L lib/Windows -l raylib -Wl,--allow-multiple-definition -pthread -lopengl32 -lgdi32 -lwinmm -mwindows -static -static-libgcc -static-libstdc++
bin/app.exe
:: .
:: > Executing program
:: -------------------------
::cmd /c if exist %NAMEPART%.exe %NAMEPART%.exe