// This file is a part of Akel
// CREATED : 05/04/2021
// UPDATED : 29/06/2021

#include <Core/core.h>
#include <Utils/utils.h>

namespace Ak::Core
{
    bool isVulkanSupported()
    {
        VkInstance instance;
	    VkInstanceCreateInfo createInfo{};
	    createInfo.enabledLayerCount = 0;
	    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO; 
        if(vkCreateInstance(&createInfo, nullptr, &instance) == VK_SUCCESS)
            return true;
        return false;
    }

    void printEngineInfo()
    {
        std::cout << bold
		<< "    ___     __          __ 		" << std::endl
		<< "   /   |   / /__ ___   / /		" << std::endl
		<< "  / /| |  / //_// _ \\ / / 		" << std::endl
		<< " / ___ | / ,<  /  __// /  		" << std::endl
		<< "/_/  |_|/_/|_| \\___//_/  		" << std::endl 
    	<< "By Malo DAVID - 2021" << std::endl;
	}

	void printEngineCodeInfo()
	{
		std::cout
		<< "Language : C++ (C++17)" << std::endl
		<< "Graphics : Vulkan, SDL_Image" << std::endl
		<< "Window : SDL2, ImGUI" << std::endl
		<< "Sounds : SDL_mixer" << std::endl;
	}
}
