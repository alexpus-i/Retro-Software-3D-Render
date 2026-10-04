@echo off

:: Создаем папку build, если её ещё нет
if not exist build mkdir build

:: Копируем SDL3.dll в папку сборки, если её там нет
if not exist "build\SDL3.dll" (
    if exist "SDL3.dll" (
        move "SDL3.dll" "build\"
    ) else (
        echo  Warning: SDL3.dll not found in root! Ensure it is in build/ or lib/
    )
)

:: Компиляция всех .cpp файлов из папки src
g++ src\*.cpp -I src -I include lib\libSDL3.dll.a -o build\main.exe


if %errorlevel% equ 0 (
    cd build
    main.exe
    cd ..
) else (
    echo  Compilation failed.
    pause
)
