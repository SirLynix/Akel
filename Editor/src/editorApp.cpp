// This file is a part of the Akel editor
// CREATED : 08/06/2021
// UPDATED : 20/10/2021

#include <AkEpch.h>
#include <Akel_main.h>
#include <editorComponent.h>

class Editor : public Ak::Application
{
	public:
		Editor() : Ak::Application("Akel_Editor")
		{
			Ak::Core::printEngineInfo();
			add_component(Ak::custom_malloc<EditorComponent>());
		}
		~Editor() = default;
};

Ak::AkelInstance Akel_init()
{
	Ak::AkelInstance project;
		project.project_file_path = std::string(Ak::Core::getMainDirPath() + "Editor/settings");
		project.project_file_name = "editor";
	return project;
}

Ak::Application* Akel_mainApplication()
{
	return Ak::custom_malloc<Editor>();
}
