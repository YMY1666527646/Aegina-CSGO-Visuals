#include <Windows.h>

#include "Material.h"
#include "Vectors.h"
#include "VirtualMethod.h"

struct DrawModelState_t{
    void* m_pStudioHdr;
    void* m_pStudioHWData;
    void* m_pRenderable;
    const void* m_pModelToWorld;
    uintptr_t        m_decals;
    int                        m_drawFlags;
    int                        m_lod;
};

struct ModelRenderInfo_t{
    ModelRenderInfo_t(){
        pModelToWorld = NULL;
        pLightingOffset = NULL;
        pLightingOrigin = NULL;
    }
    Vec3 origin;
    Vec3 angles;
    char   pad[0x4];
    void* pRenderable;
    const void* pModel;
    const void* pModelToWorld;
    const void* pLightingOffset;
    const void* pLightingOrigin;
    int flags;
    int entity_index;
    int skin;
    int body;
    int hitboxset;
    uintptr_t instance;
};

class IVModelRender{
public:
    virtual int DrawModel(int flags, void* pRenderable, uintptr_t instance, int entity_index, const void* model, Vec3 const& origin, Vec3 const& angles, int skin, int body, int hitboxset, const void* modelToWorld = NULL, const void* pLightingOffset = NULL) = 0;

    virtual void ForcedMaterialOverride(Material* newMaterial, int nOverrideType = 0, int nOverrides = 0) = 0;
    virtual bool IsForcedMaterialOverride(void) = 0;
    virtual void SetViewTarget(const int* pStudioHdr, int nBodyIndex, const Vec3& target) = 0;
    virtual uintptr_t CreateInstance(void* pRenderable, void* pCache = NULL) = 0;
    virtual void DestroyInstance(uintptr_t handle) = 0;
};