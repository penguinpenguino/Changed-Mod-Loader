#include <Windows.h>
#include <iostream>
#include <stdlib.h>
#include <dirent.h>
#include <string>
#include <fstream>
#include <tlhelp32.h>

bool inject(std::string DLLPath, HANDLE target) {
    char dll[MAX_PATH];
    GetFullPathName(DLLPath.c_str(), MAX_PATH, dll, NULL);
    LPVOID mem = VirtualAllocEx(target, 0, strlen(dll) + 1, MEM_COMMIT, PAGE_READWRITE);
    WriteProcessMemory(target, mem, (LPVOID)dll, strlen(dll) + 1, 0);
    HANDLE thread = CreateRemoteThread(target, NULL, 0, (LPTHREAD_START_ROUTINE)GetProcAddress(LoadLibrary("kernel32"), "LoadLibraryA"), mem, 0, NULL);
    if (thread == NULL) { return false; }
	WaitForSingleObject(thread, INFINITE);
	CloseHandle(thread);
    VirtualFreeEx(target, mem, 0, MEM_RELEASE);
    return true;
}

HANDLE GetHandle() {
    PROCESSENTRY32 proc;
    proc.dwSize = sizeof(PROCESSENTRY32);
    HANDLE ret = NULL;
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (Process32First(snap, &proc) == TRUE) {
        while (Process32Next(snap, &proc) == TRUE) {
            if (strcmp(proc.szExeFile, "Game.exe") == 0) {
                ret = OpenProcess(PROCESS_ALL_ACCESS, FALSE, proc.th32ProcessID);
                break;
            }
        }
    }
    CloseHandle(snap);
    return ret;
}

int main(int argc, char** argv) {
	AllocConsole();
    freopen("CONOUT$", "w", stdout);
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	CreateProcess("Game.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    WaitForSingleObject(pi.hProcess, INFINITE);
    std::string ModPath = ".\\mods\\";
    HANDLE target = GetHandle();
    while (target == NULL) {
        target = GetHandle();
        GetLastError();
        Sleep(1);
    }
    int s = 0;
    struct dirent *file;
    std::string FileName;
    DIR *dir = opendir(ModPath.c_str());
    if (dir != NULL) {
        while ((file = readdir(dir)) != NULL) {
            FileName = file->d_name;
            if (FileName.substr(FileName.find_last_of(".") + 1) == "dll") {
                if (inject(ModPath + FileName, target)) { std::cout << "Loaded " << FileName << std::endl; s++; }
                else { std::cout << "Failed to load " << FileName << std::endl; }
            }
        }
    } else {
        std::cout << "Fatal! Could not open mod directory (./mods/)" << std::endl;
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        CloseHandle(target);
        return 1;
    }
    std::cout << "\nLoaded " << s << " mods" << std::endl;
	if (argc > 1 && strcmp(argv[1], "--wait") == 0) { WaitForSingleObject(target, INFINITE); }
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    CloseHandle(target);
    return 0;
}