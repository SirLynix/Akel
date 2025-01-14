// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/04/2022
// Updated : 11/04/2022

#include "vk_cmd_buffer.h"

namespace Ak
{
	void CmdBuffer::init()
	{
		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = Render_Core::get().getCmdPool().get();
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = 1;

		if(vkAllocateCommandBuffers(Render_Core::get().getDevice().get(), &allocInfo, &_cmd_buffer) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to allocate command buffer");
	}

	void CmdBuffer::beginRecord(VkCommandBufferUsageFlags usage)
	{
		if(_is_recording)
			return;

		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = usage;
		if(vkBeginCommandBuffer(_cmd_buffer, &beginInfo) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to begin recording command buffer");

		_is_recording = true;
	}

	void CmdBuffer::endRecord()
	{
		if(!_is_recording)
			return;
		if(vkEndCommandBuffer(_cmd_buffer) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to end recording command buffer");

		_is_recording = false;
	}
}
