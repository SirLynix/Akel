// This file is a part of Akel
// CREATED : 23/07/2021
// UPDATED : 01/08/2021

#include <Utils/utils.h>
#include <Core/core.h>

namespace Ak
{
    void MemoryManager::init()
    {
    #ifndef AK_USE_JAM_MEMORY_HELPER
        __fixed1.init(16, 100);
        __fixed2.init(32, 200);
        __fixed3.init(96, 400);

        __fixed1.autoResize(true);
        __fixed2.autoResize(true);
        __fixed3.autoResize(true);
    #endif
        __jam.init(4096 * 4096);
        __jam.autoResize(true);
    }
    void MemoryManager::end()
    {
    #ifndef AK_USE_JAM_MEMORY_HELPER
        __fixed1.destroy();
        __fixed2.destroy();
        __fixed3.destroy();
    #endif
        __jam.destroy();
    }
}