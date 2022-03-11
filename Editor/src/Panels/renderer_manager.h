// This file is a part of the Akel editor
// Authors : @kbz_8
// Created : 10/03/2022
// Updated : 10/03/2022

#ifndef __AK_EDITOR_RENDERER_MANAGER__
#define __AK_EDITOR_RENDERER_MANAGER__

#include <AkEpch.h>
#include <Panels/Base/panel.h>

class RendererManager : public Panel
{
    public:
        RendererManager(std::shared_ptr<Ak::ELTM> eltm);

        void onUpdate(Ak::Maths::Vec2<int>& size) override;

        ~RendererManager() = default;
};

#endif // __AK_EDITOR_RENDERER_MANAGER__