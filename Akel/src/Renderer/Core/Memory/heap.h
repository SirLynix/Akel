// This file is a part of Akel
// Authors : @kbz_8
// Created : 31/03/2022
// Updated : 29/04/2022

#ifndef __AK_VK_GPU_HEAP__
#define __AK_VK_GPU_HEAP__

#include <Akpch.h>
#include <Core/Memory/unique_ptr_wrapper.h>

namespace Ak
{
	class GPU_Heap
	{
		public:
			GPU_Heap(uint32_t heapIndex, size_t pageSize, VkPhysicalDeviceMemoryProperties& props, VkDevice device, VkAllocationCallbacks* callbacks, std::unordered_map<VkDeviceMemory, class GPU_Page*>& pageMap);

	    	inline uint32_t const getIndex() const noexcept { return _heapIndex; }
	        bool const match(VkMemoryRequirements requirements, VkMemoryPropertyFlags flags, uint32_t* typeIndex) const;
	        class GPU_Mem_Chunk allocChunk(VkMemoryRequirements requirements, uint32_t typeIndex);

	    private:
	        struct MemoryType
	        {
	            uint32_t typeIndex = 0;
	            VkMemoryPropertyFlags flags;
	        };

	        uint32_t _heapIndex = 0;
	        size_t _pageSize = 0;
	        VkDevice _device = VK_NULL_HANDLE;
	        VkAllocationCallbacks* _callbacks = nullptr;
	        std::unordered_map<VkDeviceMemory, GPU_Page*>& _pageMap;

	        std::vector<MemoryType> _memoryTypes;
	        std::vector<GPU_Page> _pages;
	        unique_ptr_w<std::mutex> _mutex;
	};
}

#endif // __AK_VK_GPU_HEAP__
