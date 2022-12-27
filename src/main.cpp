#include "../include/injectorUtils.h"

int main(){
    DWORD procc_id = NULL;
    char dll_path[MAX_PATH]; // MAX_PATH const is 260
    const char* dll_Name = "Dll1.dll";
    const char* win_Name = "Sin título - Paint";

    if(!GetFullPathName(dll_Name, MAX_PATH, dll_path, nullptr)){
        injectorUtils::error_msg("Error - DLL Path","Error, dll path full name not resolved");
    }
    injectorUtils::get_process_id(win_Name, procc_id);
    if(!procc_id){
        injectorUtils::error_msg("Error - Process Id","Error getting the process Id");
    }
    HANDLE h_process = OpenProcess(PROCESS_ALL_ACCESS, NULL, procc_id);
    if(h_process == nullptr){
        injectorUtils::error_msg("Error - Process Handler","Error opening the process");
    }
    void* allocate_memory = VirtualAllocEx(h_process, nullptr, MAX_PATH, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if(allocate_memory == nullptr){
        injectorUtils::error_msg("Error - Allocating Memory","Error when trying to allocate memory");
        CloseHandle(h_process);
    }
    if(!WriteProcessMemory(h_process, allocate_memory, dll_path, MAX_PATH, nullptr)){
        injectorUtils::error_msg("Error - Writing Memory","Error when trying to write memory");
        CloseHandle(h_process);
        VirtualFreeEx(h_process, allocate_memory, NULL, MEM_RESERVE);
    }
    HANDLE h_thread = CreateRemoteThread(h_process, nullptr, NULL, LPTHREAD_START_ROUTINE(LoadLibraryA), allocate_memory, NULL, nullptr);
    if(h_thread == nullptr){
        injectorUtils::error_msg("Error - Creating Thread","Error when trying to create a thread");
        CloseHandle(h_process);
        VirtualFreeEx(h_process, allocate_memory, NULL, MEM_RESERVE);
    }
    CloseHandle(h_process);
    VirtualFreeEx(h_process, allocate_memory, NULL, MEM_RESERVE);
    MessageBox(NULL, "Success !", "Successfully injection !",NULL);
    return 0;
}