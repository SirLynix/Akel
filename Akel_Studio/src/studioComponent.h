// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 06/07/2021
// Updated : 12/03/2022

#ifndef __AK_STUDIO_COMPONENT__
#define __AK_STUDIO_COMPONENT__

#include <AkSpch.h>
#include <Panels/panels.h>

class StudioComponent : public Ak::WindowComponent
{
	public:
		StudioComponent();

		void onAttach() override;
		void onImGuiRender() override;
		void onImGuiEvent(Ak::Input& input) override;
		void onQuit() override;

		~StudioComponent() = default;

	private:
		void drawMainMenuBar();
		void drawAboutWindow();
		void drawOptionsWindow();

		bool _running = true;
		bool _showAbout = false;
		bool _showOpt = false;
		std::array<bool, 1> _opts;

		std::string _eltm_editor_input_buffer;

		std::shared_ptr<Ak::ELTM> _eltm;
		Ak::unique_ptr_w<PanelStack> _stack;
};

#endif // __AK_STUDIO_COMPONENT__
