// WIP

#if _WIN64
#error Must be compiled as a 32-bit DLL
#endif

#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>


// Defines

#define ModMain extern "C" __attribute__((constructor))
#define ModExit extern "C" __attribute__((destructor))


// Forward Declarations

int ModuleMemStart(char* ModuleName);
int ProcessMemStart();
bool InTitleScreen();
bool CallFuncFromMainThread(void(*funcPtr)());


// Variables

int MemStart = ProcessMemStart();


// Functions

int ModuleMemStart(char* ModuleName) { return (int)GetModuleHandle(ModuleName); }

int ProcessMemStart() { return ModuleMemStart("Game.exe"); }

bool InTitleScreen() {
    uintptr_t loc = ModuleMemStart("RGSS202E.dll") + 0x17B520;
    return !(*reinterpret_cast<bool*>(loc));
}

bool CallFuncFromMainThread(void(*funcPtr)()) {
    LPVOID mem = VirtualAllocEx(GetCurrentProcess(), 0, 1, MEM_COMMIT, PAGE_READWRITE);
    HANDLE thread = CreateRemoteThread(GetCurrentProcess(), NULL, 0, (LPTHREAD_START_ROUTINE)funcPtr, mem, 0, NULL);
    if (thread == NULL) { return false; }
    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);
    VirtualFreeEx(GetCurrentProcess(), mem, 0, MEM_RELEASE);
    return true;
}
