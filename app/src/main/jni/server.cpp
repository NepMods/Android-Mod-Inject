#include <list>
#include <vector>
#include <string.h>
#include <pthread.h>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>

#include "Includes/Logger.h"
#include "Includes/obfuscate.h"
#include "Includes/Utils.h"
#include <SOCKET/server.h>
#include "KittyMemory/MemoryPatch.h"

//Target lib here
#define targetLibName OBFUSCATE("libFileA.so")

#include "Includes/Macros.h"


enum Mode {
    InitMode = 1,
    HackMode = 2,
    StopMode = 3,
    EspMode = 99,
};


struct Request {
    int Mode;
    bool boolean;
    int value;
    int screenWidth;
    int screenHeight;
};

#define maxplayerCount 54

struct PlayerData {
    char PlayerName[64];
    // string *Test;
    float Health;
    float Distance2;
    bool get_IsDieing;
    bool isBot;
    Vector3 CloseEnemyHeadLocation;
    Vector3 HeadLocation;
    Vector3 ToeLocation;
    Vector2 RShoulder;
    Vector3 LShoulder;
    Vector3 Toe;
    Vector3 Hip;
    Vector3 Head;
    int x;
    int y;
    int z;
    int id;
    int h;
    char debug[60];
};

struct Response {
    bool Success;
    int PlayerCount;
    PlayerData Players[maxplayerCount];
};

SocketServer server;

int InitServer() {
    if (!server.Create()) {
        return -1;
    }
    if (!server.Bind()) {
        return -1;
    }
    if (!server.Listen()) {
        return -1;
    }
    return 0;
}
enum f {
    f1 = 4,
    f2 = 5,
    f3 = 6,
    f4 = 7,
    f5 = 8,
    f6 = 9,
    f7 = 10,
    f8 = 11,
    f9 = 12,
    f10 = 13,
};
// fancy struct for patches for kittyMemory
struct My_Patches {
    // let's assume we have patches for these functions for whatever game
    // like show in miniMap boolean function
    MemoryPatch GodMode,
    GodMode2,
    SliderExample;
    // etc...
} hexPatches;

bool feature1, feature2, featureHookToggle, Health;
int sliderValue = 1, level = 0;
void *instanceBtn;

// Hooking examples. Assuming you know how to write hook
void (*AddMoneyExample)(void *instance, int amount);

bool (*old_get_BoolExample)(void *instance);
bool get_BoolExample(void *instance) {
    if (instance != NULL && featureHookToggle) {
        return true;
    }
    return old_get_BoolExample(instance);
}

float (*old_get_FloatExample)(void *instance);
float get_FloatExample(void *instance) {
    if (instance != NULL && sliderValue > 1) {
        return (float) sliderValue;
    }
    return old_get_FloatExample(instance);
}

int (*old_Level)(void *instance);
int Level(void *instance) {
    if (instance != NULL && level) {
        return (int) level;
    }
    return old_Level(instance);
}

void (*old_FunctionExample)(void *instance);
void FunctionExample(void *instance) {
    instanceBtn = instance;
    if (instance != NULL) {
        if (Health) {
            *(int *) ((uint64_t) instance + 0x48) = 999;
        }
    }
    return old_FunctionExample(instance);
}



void createDataList(Response& response) {}


void *CreateServer(void *) {
    if (InitServer() == 0) {
        if (server.Accept()) {
            Request request {};
            while (server.receive((void*)&request) > 0) {
                Response response {};
                if (request.Mode == Mode::InitMode) {
                    response.Success = true;
                } else if (request.Mode == Mode::HackMode) {

                    response.Success = true;
                } else if (request.Mode == Mode::EspMode) {

                    createDataList(response);
                    response.Success = true;
                } else if (request.Mode == f::f1) {

                    feature2 = request.boolean;

                    if (feature2) {
                        // To print bytes you can do this
                        //if (hexPatches.GodMode.Modify()) {
                        //    LOGD(OBFUSCATE("Current Bytes: %s"),
                        //         hexPatches.GodMode.get_CurrBytes().c_str());
                        //}
                        hexPatches.GodMode.Modify();
                        hexPatches.GodMode2.Modify();
                        //LOGI(OBFUSCATE("On"));
                    } else {
                        hexPatches.GodMode.Restore();
                        hexPatches.GodMode2.Restore();
                        //LOGI(OBFUSCATE("Off"));
                    }
                    response.Success = true;
                } else if (request.Mode == f::f2) {
                    sliderValue = request.value;
                    response.Success = true;
                } else if (request.Mode == f::f3) {
                    int value = request.value;
                    switch (value) {
                        //For noobies
                        case 0:
                            hexPatches.SliderExample = MemoryPatch::createWithHex(
                                targetLibName, string2Offset(
                                    OBFUSCATE("0x100000")),
                                OBFUSCATE(
                                    "00 00 A0 E3 1E FF 2F E1"));
                            hexPatches.SliderExample.Modify();
                            break;
                        case 1:
                            hexPatches.SliderExample = MemoryPatch::createWithHex(
                                targetLibName, string2Offset(
                                    OBFUSCATE("0x100000")),
                                OBFUSCATE("01 00 A0 E3 1E FF 2F E1"));
                            hexPatches.SliderExample.Modify();
                            break;
                        case 2:
                            hexPatches.SliderExample = MemoryPatch::createWithHex(
                                targetLibName,
                                string2Offset(
                                    OBFUSCATE("0x100000")),
                                OBFUSCATE(
                                    "02 00 A0 E3 1E FF 2F E1"));
                            hexPatches.SliderExample.Modify();
                            break;
                    }
                    response.Success = true;
                } else if (request.Mode == f::f4) {
                    int value = request.value;
                    switch (value) {
                        case 0:
                            LOGD(OBFUSCATE("Selected item 1"));
                            break;
                        case 1:
                            LOGD(OBFUSCATE("Selected item 2"));
                            break;
                        case 2:
                            LOGD(OBFUSCATE("Selected item 3"));
                            break;
                    }
                    response.Success = true;
                } else if (request.Mode == f::f5) {
                    int value = request.value;

                    response.Success = true;
                } else if (request.Mode == f::f6) {
                    featureHookToggle = request.boolean;
                    response.Success = true;
                } else if (request.Mode == f::f7) {
                    level = request.value;
                    response.Success = true;
                }
                server.sendX((void*)& response, sizeof(response));
            }
        }
    }
    return nullptr;
}


void* Thread (void *) {
    ProcMap il2cppMap;
    do {
        il2cppMap = KittyMemory::getLibraryMap("libil2cpp.so");
        sleep(1);
    } while (!il2cppMap.isValid());

    #if defined(__aarch64__) //To compile this code for arm64 lib only. Do not worry about greyed out highlighting code, it still works
    // New way to patch hex via KittyMemory without need to  specify len. Spaces or without spaces are fine
    // ARM64 assembly example
    // MOV X0, #0x0 = 00 00 80 D2
    // RET = C0 03 5F D6
    hexPatches.GodMode = MemoryPatch::createWithHex(targetLibName,
        string2Offset(OBFUSCATE("0x123456")),
        OBFUSCATE("00 00 80 D2 C0 03 5F D6"));
    //You can also specify target lib like this
    hexPatches.GodMode2 = MemoryPatch::createWithHex("libtargetLibHere.so",
        string2Offset(OBFUSCATE("0x222222")),
        OBFUSCATE("20 00 80 D2 C0 03 5F D6"));

    // Hook example. Comment out if you don't use hook
    // Strings in macros are automatically obfuscated. No need to obfuscate!
    HOOK("str", FunctionExample, old_FunctionExample);
    HOOK_LIB("libFileB.so", "0x123456", FunctionExample, old_FunctionExample);
    HOOK_NO_ORIG("0x123456", FunctionExample);
    HOOK_LIB_NO_ORIG("libFileC.so", "0x123456", FunctionExample);
    HOOKSYM("__SymbolNameExample", FunctionExample, old_FunctionExample);
    HOOKSYM_LIB("libFileB.so", "__SymbolNameExample", FunctionExample, old_FunctionExample);
    HOOKSYM_NO_ORIG("__SymbolNameExample", FunctionExample);
    HOOKSYM_LIB_NO_ORIG("libFileB.so", "__SymbolNameExample", FunctionExample);

    // Patching offsets directly. Strings are automatically obfuscated too!
    PATCHOFFSET("0x20D3A8", "00 00 A0 E3 1E FF 2F E1");
    PATCHOFFSET_LIB("libFileB.so", "0x20D3A8", "00 00 A0 E3 1E FF 2F E1");

    AddMoneyExample = (void(*)(void *, int))getAbsoluteAddress(targetLibName, 0x123456);

    #else //To compile this code for armv7 lib only.
        // New way to patch hex via KittyMemory without need to specify len. Spaces or without spaces are fine
    // ARMv7 assembly example
    // MOV R0, #0x0 = 00 00 A0 E3
    // BX LR = 1E FF 2F E1
    hexPatches.GodMode = MemoryPatch::createWithHex(targetLibName, //Normal obfuscate
        string2Offset(OBFUSCATE("0x123456")),
        OBFUSCATE("00 00 A0 E3 1E FF 2F E1"));
    //You can also specify target lib like this
    hexPatches.GodMode2 = MemoryPatch::createWithHex("libtargetLibHere.so",
        string2Offset(OBFUSCATE("0x222222")),
        OBFUSCATE("01 00 A0 E3 1E FF 2F E1"));

    // Hook example. Comment out if you don't use hook
    // Strings in macros are automatically obfuscated. No need to obfuscate!
    HOOK("str", FunctionExample, old_FunctionExample);
    HOOK_LIB("libFileB.so", "0x123456", FunctionExample, old_FunctionExample);
    HOOK_NO_ORIG("0x123456", FunctionExample);
    HOOK_LIB_NO_ORIG("libFileC.so", "0x123456", FunctionExample);
    HOOKSYM("__SymbolNameExample", FunctionExample, old_FunctionExample);
    HOOKSYM_LIB("libFileB.so", "__SymbolNameExample", FunctionExample, old_FunctionExample);
    HOOKSYM_NO_ORIG("__SymbolNameExample", FunctionExample);
    HOOKSYM_LIB_NO_ORIG("libFileB.so", "__SymbolNameExample", FunctionExample);

    // Patching offsets directly. Strings are automatically obfuscated too!
    PATCHOFFSET("0x20D3A8", "00 00 A0 E3 1E FF 2F E1");
    PATCHOFFSET_LIB("libFileB.so", "0x20D3A8", "00 00 A0 E3 1E FF 2F E1");

    AddMoneyExample = (void (*)(void *, int)) getAbsoluteAddress(targetLibName, 0x123456);

    LOGI(OBFUSCATE("Done"));
    #endif

    return NULL;

}


__attribute__((constructor))
void lib_main() {
    pthread_t PidThread;
    pthread_create(&PidThread, NULL, Thread, NULL);
    pthread_t ptid;
    pthread_create(&ptid, nullptr, CreateServer, nullptr);

}
