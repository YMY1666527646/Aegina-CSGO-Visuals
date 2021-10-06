#include <Windows.h>
#include <string>
#include "MaterialSystem.h"
#include "CreateInterface.h"

void MainThread(HMODULE hModule) {
    MaterialSystem* VMaterialInterface = (MaterialSystem*)GetInterface("materialsystem.dll", "VMaterialSystem080");

    for (auto i = VMaterialInterface->firstMaterial(); i != VMaterialInterface->invalidMaterial(); i = VMaterialInterface->nextMaterial(i)) {
        auto material = VMaterialInterface->getMaterial(i);
        if (!material) { continue; }
        if (std::strstr(material->getName(), "models/player/") || std::strstr(material->getName(), "models/weapons/v_models")) {
            material->colorModulate(255, 255, 255);
            material->setMaterialVarFlag(MaterialVarFlag::IGNOREZ, true);
        }
    }
    FreeLibraryAndExitThread(hModule, 0);
}

BOOL WINAPI DllMain(HMODULE hModule ,DWORD ul_reason_for_call, LPARAM lParam){
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		CreateThread(0, 0, LPTHREAD_START_ROUTINE(MainThread), hModule, 0, 0);
	}

}