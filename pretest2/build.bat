@echo off
g++ main.cpp -o main.exe ^
    -I"C:/Program Files/WasmEdge/include" ^
    -L"C:/Program Files/WasmEdge/lib" ^
    -lwasmedge
if %errorlevel% equ 0 (
    echo Compilation successful!
    main.exe
)