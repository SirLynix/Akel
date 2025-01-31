// This file is a part of Akel
// Authors : @kbz_8
// Created : 24/09/2021
// Updated : 01/04/2022

#ifndef __AK_VK_ALLOCATOR_GPU__
#define __AK_VK_ALLOCATOR_GPU__

#include <Akpch.h>
#include "heap.h"
#include "chunk.h"

namespace Ak
{
    class Allocator_GPU
    {
        public:
            Allocator_GPU(VkPhysicalDevice physicalDevice, VkDevice device, VkAllocationCallbacks* callbacks, size_t pageSize);

            GPU_Mem_Chunk allocChunk(VkMemoryRequirements requirements, VkMemoryPropertyFlags flags);
            void freeChunk(GPU_Mem_Chunk chunk);

            ~Allocator_GPU() = default;

        private:
            VkPhysicalDevice _physicalDevice;
            VkDevice _device;
            VkAllocationCallbacks* _callbacks;

            std::vector<GPU_Heap> _heaps;
            std::unordered_map<VkDeviceMemory, GPU_Page*> _pageMap;
    };
}

#endif // __AK_VK_ALLOCATOR_GPU__
