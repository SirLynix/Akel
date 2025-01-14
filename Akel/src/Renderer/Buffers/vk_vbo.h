// This file is a part of Akel
// Authors : @kbz_8
// Created : 29/04/2022
// Updated : 30/04/2022

#ifndef __AK_VK_VBO__
#define __AK_VK_VBO__

#include "vk_buffer.h"

namespace Ak
{
	class VBO : public Buffer
	{
		public:
			inline void create(uint32_t size) { Buffer::create(Buffer::kind::dynamic, size, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT); }

			void setData(uint32_t size, const void* data);
			void setSubData(uint32_t offset, uint32_t size, const void* data);

			inline void bind() noexcept { vkCmdBindVertexBuffers(Render_Core::get().getActiveCmdBuffer().get(), 0, 1, &_buffer, &_mem_chunck.offset); }

		private:
			uint32_t _used_size = 0;
	};

	class C_VBO : public Buffer
	{
		public:
			inline void create(uint32_t size, const void* data) { Buffer::create(Buffer::kind::constant, size, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, data); }
			inline void bind() noexcept { vkCmdBindVertexBuffers(Render_Core::get().getActiveCmdBuffer().get(), 0, 1, &_buffer, &_mem_chunck.offset); }
	};
}

#endif // __AK_VK_VBO__
