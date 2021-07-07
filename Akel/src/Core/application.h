// This file is a part of Akel
// CREATED : 08/06/2021
// UPDATED : 07/07/2021

#ifndef __AK_APPLICATION__
#define __AK_APPLICATION__

#include <Akpch.h>
#include <Core/Components/components.h>
#include <Platform/input.h>
#include <Modules/ImGui/imgui_component.h>
#include <Utils/utils.h>

namespace Ak
{
	class Input;
	class ImGuiComponent;

	class Application : public ComponentStack
	{
		public:
			Application(const char* name);
			void run();
			~Application();

		private:
			const char* _name = "";
			Input _in;
			ImGuiComponent* _imgui;
	};
}

#endif // __AK_APPLICATION__

