// This file is a part of Akel Studio
// Authors : @kbz_8
// Created : 10/03/2022
// Updated : 10/03/2022

#ifndef __AK_STUDIO_RENDERER_MANAGER__
#define __AK_STUDIO_RENDERER_MANAGER__

#include <AkSpch.h>
#include <Panels/Base/panel.h>

class RendererManager : public Panel
{
    public:
        RendererManager(std::shared_ptr<Ak::ELTM> eltm);

        void onUpdate(Ak::Maths::Vec2<int>& size) override;

        ~RendererManager() = default;

    private:
        void render_sets();
        bool _vsync = false;
        std::string selected;
};

#endif // __AK_STUDIO_RENDERER_MANAGER__
