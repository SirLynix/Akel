// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 07/04/2022

#include "vk_swapchain.h"
#include <Renderer/Core/render_core.h>

namespace Ak
{
    void Swapchain::init()
    {
        Swapchain::SwapChainSupportDetails swapChainSupport = querySwapChainSupport(Render_Core::get().getDevice().getPhysicalDevice());

        VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
        VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
        VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

        uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
        if(swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
            imageCount = swapChainSupport.capabilities.maxImageCount;

        VkSwapchainCreateInfoKHR createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.surface = Render_Core::get().getSurface().get();

        createInfo.minImageCount = imageCount;
        createInfo.imageFormat = surfaceFormat.format;
        createInfo.imageColorSpace = surfaceFormat.colorSpace;
        createInfo.imageExtent = extent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        Queues::QueueFamilyIndices indices = Render_Core::get().getQueues().findQueueFamilies(Render_Core::get().getDevice().getPhysicalDevice());
        uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};

        if(indices.graphicsFamily != indices.presentFamily)
		{
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        }
		else
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;

        createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.presentMode = presentMode;
        createInfo.clipped = VK_TRUE;

        createInfo.oldSwapchain = VK_NULL_HANDLE;

        VkDevice device = Render_Core::get().getDevice().get();

        if(vkCreateSwapchainKHR(device, &createInfo, nullptr, &_swapChain) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to create swap chain");

        vkGetSwapchainImagesKHR(device, _swapChain, &imageCount, nullptr);
        swapChainImages.resize(imageCount);
        vkGetSwapchainImagesKHR(device, _swapChain, &imageCount, _swapChainImages.data());

        swapChainImageFormat = surfaceFormat.format;
        swapChainExtent = extent;

        _imageViews.resize(_swapChainImages.size());
        for(size_t i = 0; i < _swapChainImages.size(); i++)
            _imageViews.init(this, _swapChainImages[i]);

        _framebuffers.resize(_imageViews.size());

        for(size_t i = 0; i < _swapChainImageViews.size(); i++)
            _framebuffers.init(this, _imageViews[i]);
    }

    Swapchain::SwapChainSupportDetails Swapchain::querySwapChainSupport(VkPhysicalDevice device)
    {
        Swapchain::SwapChainSupportDetails details;
        VkSurfaceKHR surface = Render_Core::get().getSurface().get();

        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

        uint32_t formatCount = 0;
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

        if(formatCount != 0)
        {
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
        }

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

        if(presentModeCount != 0)
        {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
        }

        return details;
    }

    VkPresentModeKHR Swapchain::chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes)
    {
		if(!Render_Core::get().getWindow()->vsync)
		    return VK_PRESENT_MODE_IMMEDIATE_KHR;

        for(const auto& availablePresentMode : availablePresentModes)
        {
            if(availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
                return availablePresentMode;
        }
        return VK_PRESENT_MODE_FIFO_KHR;
    }

    VkExtent2D Swapchain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
    {
        if(capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
            return capabilities.currentExtent;

        int width, height;
        SDL_Vulkan_GetDrawableSize(Render_Core::get().getWindow()->getNativeWindow(), &width, &height);

        VkExtent2D actualExtent = { static_cast<uint32_t>(width), static_cast<uint32_t>(height) };

        actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
        actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

        return actualExtent;
    }

    void Swapchain::destroy()
    {
        VkDevice device = Render_Core::get().getDevice().get();

        vkDeviceWaitIdle(device);

        for(auto& frameBuffer : _framebuffers)
            frameBuffer.destroy();

        for(auto& imageView : _imageViews)
            imageView.destroy();

        vkDestroySwapchainKHR(device, _swapChain, nullptr);
    }
}
