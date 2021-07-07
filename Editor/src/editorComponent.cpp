// This file is a part of the Akel editor
// CREATED : 06/07/2021
// UPDATED : 07/07/2021

#include <editorComponent.h>

EditorComponent::EditorComponent() : Ak::ImGuiComponent("Akel Editor") {}

void EditorComponent::onAttach()
{
	Ak::ImGuiComponent::onAttach();
	Ak::ImGuiComponent::Window::setSetting<position>(100, 1000);
	Ak::ImGuiComponent::Window::setSetting<dimensions>(1250, 950);
	//Ak::ImGuiComponent::Window::setSetting<visible>(false);
}
void EditorComponent::onImGuiRender()
{
	ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

	ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
	bool show_another_window;
	ImGui::Checkbox("Another Window", &show_another_window);

	float f = 0.0f;
	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

	int counter = 0;
	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		counter++;
	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}
void EditorComponent::onQuit()
{
	Ak::ImGuiComponent::onQuit();
}

