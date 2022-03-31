// This file is a part of Akel
// Authors : @kbz_8
// Created : 24/09/2021
// Updated : 31/03/2022

#ifndef __AK_VK_ALLOCATOR_GPU__
#define __AK_VK_ALLOCATOR_GPU__

#include <Akpch.h>
#include <Renderer/Memory/chunk.h>

namespace Ak
{
    class Buffer;
    
    class Allocator_GPU
    {
        public:
            Allocator_GPU();

            Buffer& allocBuffer(VkDeviceSize size);
            inline bool canHold(VkDeviceSize size);
            inline bool contains(Buffer& buffer);
            void freeBuffer(const Buffer& buffer);

            ~Allocator_GPU();

        private:
            std::vector<Chunk> _chuncks;
    };
}

#endif // __AK_VK_ALLOCATOR_GPU__
