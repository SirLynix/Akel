-- This file is a part of Akel
-- Author : @kbz_8
-- Created : 02/10/2021
-- Updated : 07/05/2022

-- Globals settings
add_repositories("local-repo libs")

add_requires("libsdl_image", "libsdl", "libsdl_ttf", "libsndfile", "openal-soft", "spirv-reflect", "vulkan-headers", "vulkan-loader", "vulkan-validationlayers", "imgui_sdl_vk v1.87-docking")

add_rules("mode.debug", "mode.release")
set_languages("cxx17")

set_objectdir("build-int/$(os)_$(arch)")
set_targetdir("build/$(os)_$(arch)")

-- Lib Akel Build
target("Akel")
	set_default(true)
	set_kind("shared")
	add_files("Akel/src/**.cpp")
	add_includedirs("Akel/src", "libs/include")

	if is_mode("debug") then
		add_defines("AK_DEBUG")
	elseif is_mode("release") then
		add_defines("AK_RELEASE")
	end

	add_defines("MAIN_PATH=\"$(projectdir)/\"")

	set_pcxxheader("Akel/src/Akpch.h")
	add_defines("SDL_MAIN_HANDLED")
	add_packages("libsdl_image", "libsdl", "libsdl_ttf", "spirv-reflect", "libsndfile", "openal-soft", "vulkan-headers", "vulkan-loader", "vulkan-validationlayers", "imgui_sdl_vk")

	on_load(function(target)
		os.cp("$(projectdir)/libs/packages/i/imgui_sdl_vk/install/libimgui_sdl_vk.so", "build/$(os)_$(arch)/")
    end);
target_end() -- optional but I think the code is cleaner with this

-- Editor Build
target("Akel Studio")
	set_default(true)
    set_kind("binary")
	add_includedirs("Akel/src", "Akel_Studio/src", "libs/include")
    add_deps("Akel")
    add_files("Akel_Studio/src/**.cpp")

	add_packages("imgui_sdl_vk")
	set_pcxxheader("Akel_Studio/src/AkSpch.h")

	if is_mode("debug") then
		add_defines("AK_STUDIO_DEBUG")
	elseif is_mode("release") then
		add_defines("AK_STUDIO_RELEASE")
	end
target_end() -- optional but I think the code is cleaner with this

-- Rectangle Demo Build
target("RectDemo")
	set_default(false)
    set_kind("binary")
	add_packages("imgui_sdl_vk")
    add_deps("Akel")
	add_includedirs("Akel/src", "SandBox/rect/src", "libs/include")
    add_files("SandBox/rect/src/*.cpp")
target_end() -- optional but I think the code is cleaner with this

-- Cube Demo Build
target("CubeDemo")
	set_default(false)
    set_kind("binary")
	add_packages("imgui_sdl_vk")
    add_deps("Akel")
	add_includedirs("Akel/src", "SandBox/cube/src", "libs/include")
    add_files("SandBox/cube/src/*.cpp")
target_end() -- optional but I think the code is cleaner with this

-- Kila tester Build
target("Kila_tester")
	set_default(false)
    set_kind("binary")
	add_packages("imgui_sdl_vk")
    add_deps("Akel")
	add_includedirs("Akel/src", "Tests/Kila", "libs/include")
    add_files("Tests/Kila/*.cpp")
target_end() -- optional but I think the code is cleaner with this
