#include "./include/injectorUtils.h"

int main(){
    DWORD procc_id = NULL;
    char dll_path[MAX_PATH];
    const char* dll_Name;
    const char* win_Name;
    std::string auxDll;
    std::string auxWin;

    std::cout << "Ingresa el nombre del archivo DLL" << std::endl;
    std::cin >> auxDll;
    std::cout << "Ingresa el nombre de la ventana a inyectar" << std::endl;
    std::cin >> auxWin;
    dll_Name = auxDll.c_str(); //Convert string to const char*
    win_Name = auxWin.c_str();

    GetFullPathName((LPCWSTR)dll_Name, MAX_PATH, (LPWSTR)dll_path, nullptr);
    injectorUtils::get_process_id(win_Name, procc_id);
    HANDLE h_process = OpenProcess(PROCESS_ALL_ACCESS, NULL, procc_id);
    void* allocate_memory = VirtualAllocEx(h_process, nullptr, MAX_PATH, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    WriteProcessMemory(h_process, allocate_memory, dll_path, MAX_PATH, nullptr);
    HANDLE h_thread = CreateRemoteThread(h_process, nullptr, NULL, LPTHREAD_START_ROUTINE(LoadLibraryA), allocate_memory, NULL, nullptr);
    CloseHandle(h_process);
    VirtualFreeEx(h_process, allocate_memory, NULL, MEM_RESERVE);
    MessageBox(NULL, (LPCWSTR)"Exito", (LPCWSTR)"Inyeccion exitosa",NULL);
    return 0;
}