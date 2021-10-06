#pragma once
#include <Windows.h>

namespace VirtualMethod
{
    template <typename T, size_t Idx, typename ...Args>
    constexpr T call(void* classBase, Args... args) noexcept
    {
        return (*reinterpret_cast<T(__thiscall***)(void*, Args...)>(classBase))[Idx](classBase, args...);
    }
}

#define VIRTUAL_METHOD(returnType, name, idx, args, argsRaw) \
returnType name args noexcept \
{ \
    return VirtualMethod::call<returnType, idx>argsRaw; \
}

#define INCONSTRUCTIBLE(className) \
className() = delete; \
className(className&&) = delete; \
className(const className&) = delete; \
className& operator=(const className&) = delete;

#define WIN32_LINUX(win32, linux) win32

 enum class MaterialVarFlag {
     NO_DRAW = 1 << 2,
     IGNOREZ = 1 << 15,
     WIREFRAME = 1 << 28
 };

class Material {
public:
    INCONSTRUCTIBLE(Material)

        VIRTUAL_METHOD(const char*, getName, 0, (), (this))
        VIRTUAL_METHOD(void, colorModulate, 28, (float r, float g, float b), (this, r, g, b))
        VIRTUAL_METHOD(void, setMaterialVarFlag, 29, (MaterialVarFlag flag, bool on), (this, flag, on))
};

class MaterialSystem {
public:
    INCONSTRUCTIBLE(MaterialSystem)

        VIRTUAL_METHOD(short, firstMaterial, 86, (), (this))
        VIRTUAL_METHOD(short, nextMaterial, 87, (short handle), (this, handle))
        VIRTUAL_METHOD(short, invalidMaterial, 88, (), (this))
        VIRTUAL_METHOD(Material*, getMaterial, 89, (short handle), (this, handle))
};

