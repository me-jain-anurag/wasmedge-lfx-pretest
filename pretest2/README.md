# Pre-test 2: WasmEdge C API Implementation

## Overview

This implementation demonstrates WebAssembly module linking using the WasmEdge C API.

## Files

- `lib.wat` / `lib.wasm` - Library module providing basic arithmetic functions (add, mul)
- `calc.wat` / `calc.wasm` - Calculator module that imports from lib and provides add_and_square function
- `main.cpp` - C++ host application using WasmEdge C API
- `build.bat` - Compilation script for Windows
- `screenshot.png` - Execution results

## Architecture
```
main.cpp (Host Application)
    ↓
  VM Context
    ↓
  Registers: lib.wasm as "lib"
    ↓
  Loads: calc.wasm (imports from "lib")
    ↓
  Executes: add_and_square(3, 5) → 64
```

## How It Works

1. **lib.wasm** provides two exported functions:
   - `add(a, b)` - Returns a + b
   - `mul(a, b)` - Returns a × b

2. **calc.wasm** imports these functions and provides:
   - `add_and_square(a, b)` - Returns (a + b)²

3. **main.cpp** orchestrates the execution:
   - Creates WasmEdge VM
   - Registers lib.wasm as "lib" module
   - Loads and instantiates calc.wasm
   - Executes add_and_square with test values
   - Verifies results

## Building and Running
```bash
# Compile WAT to WASM (if needed)
wat2wasm lib.wat -o lib.wasm
wat2wasm calc.wat -o calc.wasm

# Build and run
./build.bat
```

## Test Results

**Test Case:** `add_and_square(3, 5)`
- Expected: (3 + 5)² = 64
- Actual: 64
- Status: **PASSED**

## Environment

- **OS:** Windows 11
- **Compiler:** MinGW-w64 GCC
- **WasmEdge:** version 0.16.1
- **Build Tool:** Custom batch script (build.bat)