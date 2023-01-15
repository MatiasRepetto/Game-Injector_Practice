#include <Windows.h>
#include "..\include\vendor\luajit\src\lua.hpp"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        // Crea una instancia del intérprete Lua
        lua_State* L = luaL_newstate();
        luaL_openlibs(L); // Abre las librerías estándar de Lua

        // Carga el script desde un archivo
        if (luaL_loadfile(L, "scriptToInject.lua")) {
            printf("Error al cargar el script: %s\n", lua_tostring(L, -1));
            lua_pop(L, 1); // Elimina el mensaje de error de la pila
        }
        else {
            // Ejecuta el script
            if (lua_pcall(L, 0, 0, 0)) {
                printf("Error al ejecutar el script: %s\n", lua_tostring(L, -1));
                lua_pop(L, 1); // Elimina el mensaje de error de la pila
            }
        }

        lua_close(L); // Cierra el intérprete Lua
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
