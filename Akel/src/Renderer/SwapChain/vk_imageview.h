// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 10/04/2022

#ifndef __AK_VK_IMAGE_VIEW__
#define __AK_VK_IMAGE_VIEW__

#include <Akpch.h>

namespace Ak
{
	class ImageView
	{
		public:
			void init(class SwapChain* swapchain, VkImage& image);
			inline void destroy() noexcept
			{
				static_assert(_image != VK_NULL_HANDLE, "trying to destroy an uninit image view");
				vkDestroyImageView(Render_Core::get().getDevice().get(), _image, nullptr);
			}

            inline VkImageView& operator()() const noexcept { return _image; }
            inline VkImageView& get() const noexcept { return _image; }

		private:
			VkImageView _image = VK_NULL_HANDLE;
	};
}

#endif // __AK_VK_IMAGE_VIEW__
