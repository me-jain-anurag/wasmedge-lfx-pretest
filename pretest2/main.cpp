#include <wasmedge/wasmedge.h>
#include <stdio.h>

int main() {
    printf("=== WasmEdge Pre-test 2: Module Linking ===\n\n");

    // Initialize the execution environment with default configurations
    WasmEdge_VMContext *VM = WasmEdge_VMCreate(NULL, NULL);
    
    // Register 'lib.wasm' as a named module so 'calc.wasm' can resolve its imports.
    // In WASM, imports are keyed by module name; here we map the file to "lib".
    WasmEdge_String LibName = WasmEdge_StringCreateByCString("lib");
    WasmEdge_Result Res = WasmEdge_VMRegisterModuleFromFile(VM, LibName, "lib.wasm");
    WasmEdge_StringDelete(LibName); // Clean up the string structure after use
    
    if (!WasmEdge_ResultOK(Res)) {
        printf("Linker Error: Failed to register 'lib.wasm' in the store.\n");
        WasmEdge_VMDelete(VM);
        return 1;
    }

    // Standard pipeline: Load the bytecode, validate semantics, and instantiate the module.
    // This step links the 'calc' module's imports to the 'lib' module we registered above.
    Res = WasmEdge_VMLoadWasmFromFile(VM, "calc.wasm");
    if (WasmEdge_ResultOK(Res)) Res = WasmEdge_VMValidate(VM);
    if (WasmEdge_ResultOK(Res)) Res = WasmEdge_VMInstantiate(VM);

    if (!WasmEdge_ResultOK(Res)) {
        printf("Initialization Error: Failed to load or link 'calc.wasm'.\n");
        WasmEdge_VMDelete(VM);
        return 1;
    }

    // Testing (3 + 5)^2. We wrap values in WasmEdge_Value for the cross-boundary call.
    WasmEdge_Value Params[2] = { WasmEdge_ValueGenI64(3), WasmEdge_ValueGenI64(5) };
    WasmEdge_Value Returns[1];
    WasmEdge_String FuncName = WasmEdge_StringCreateByCString("add_and_square");

    printf("Executing add_and_square(3, 5)...\n");
    Res = WasmEdge_VMExecute(VM, FuncName, Params, 2, Returns, 1);
    WasmEdge_StringDelete(FuncName);

    if (!WasmEdge_ResultOK(Res)) {
        printf("Runtime Error: Execution of 'add_and_square' failed.\n");
        WasmEdge_VMDelete(VM);
        return 1;
    }

    int64_t result = WasmEdge_ValueGetI64(Returns[0]);
    printf("Result: %lld (Expected: 64)\n", result);

    if (result == 64) {
        printf("Verification Passed.\n");
    } else {
        printf("Verification Failed: Mathematics mismatch.\n");
    }

    // Explicitly release resources to prevent leaks
    WasmEdge_VMDelete(VM);
    printf("\n=== Execution Finished ===\n");
    
    return 0;
}