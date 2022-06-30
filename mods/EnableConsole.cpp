#include <Windows.h>
#include <iostream>

extern "C" {

__attribute__((constructor)) void mod_main() {
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
    freopen("CONIN$", "r", stdin);
}

}