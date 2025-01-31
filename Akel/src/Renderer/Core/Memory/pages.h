// This file is a part of Akel
// Authors : @kbz_8
// Created : 31/03/2022
// Updated : 03/04/2022

#ifndef __AK_VK_MEMORY_PAGES__
#define __AK_VK_MEMORY_PAGES__

#include <Akpch.h>
#include <Core/Memory/unique_ptr_wrapper.h>

namespace Ak
{
	class GPU_Page
	{
		public:
			Page(VkDevice device, size_t size, uint32_t typeIndex, std::unordered_map<VkDeviceMemory, Page*>& pageMap, VkAllocationCallbacks* callbacks);
			Page(Page&& page);

			inline constexpr bool const match(uint32_t typeIndex) const noexcept { return _typeIndex == typeIndex; }
			class GPU_Mem_Chunk tryAlloc(VkMemoryRequirements requirements);
			void free(class GPU_Mem_Chunk chunk);
			
			~Page();

		private:
			struct Flag
			{
				Flag(unsigned int offset, unsigned int size);

				void split(unsigned int start, unsigned int size);
				void merge();

				~Flag() = default;

				Flag* next = nullptr;
				unsigned int offset = 0;
				unsigned int size = 0;
				bool free = true;
			};

			Flag* _head = nullptr;
	        size_t _size = 0;
	        unsique_ptr_w<std::mutex> _mutex;
	        VkDevice _device = VK_NULL_HANDLE;
	        VkDeviceMemory _memory = VK_NULL_HANDLE;
	        VkAllocationCallbacks* _callbacks = nullptr;
	        uint32_t _typeIndex = 0;
	};
}

#endif // __AK_VK_MEMORY_PAGES__
