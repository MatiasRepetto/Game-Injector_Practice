#ifndef INJECTORUTILS
#define INJECTORUTILS

#include <Windows.h>
#include <iostream>
#include <string>
#include <thread>
#include <libloaderapi.h>

class injectorUtils{
    private:
    public:
        static void get_process_id(const char*, DWORD &);
        static void error_msg(const char*, const char*);
        static bool dll_exist(const char*); 
};

#endif