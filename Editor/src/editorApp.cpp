// This file is a part of the Akel editor
// Authors : @kbz_8
// Created : 08/06/2021
// Updated : 11/03/2022

#include <AkEpch.h>
#include <Akel_main.h>
#include <editorComponent.h>

class Editor : public Ak::Application
{
	public:
		Editor() : Ak::Application("Akel Studio")
		{
			Ak::Core::printEngineInfo();
			add_component<Ak::AudioManager>();
			EditorComponent* editor = Ak::memAlloc<EditorComponent>();
			add_component(editor);
			add_component<Ak::ImGuiComponent>(editor);
		}
		~Editor() = default;
};

Ak::AkelInstance Akel_init()
{
	Ak::AkelInstance project;
		project.project_file_path = std::string(Ak::Core::getMainDirPath() + "Editor/settings");
		project.project_file_name = "editor";
        project.memory_manager_enable_fixed_allocator = false;
		project.imgui_vk_unlimited_framerate = true;
	return project;
}

Ak::Application* Akel_mainApplication()
{
	return Ak::memAlloc<Editor>();
}
