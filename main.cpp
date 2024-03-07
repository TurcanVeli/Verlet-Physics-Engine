#include <iostream>

#include "Core.h"
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"


int main()
{
    Core Enginecore;

    while (Enginecore.isRunning())
    {
        Enginecore.pollEvent();
        ImGui::SFML::Update(*Enginecore.window, Enginecore.clock.restart());
        if (Enginecore.Sim_State == state::PLAY)
        {
            Enginecore.update();

        }
        Enginecore.updateMousePos();

        Enginecore.Gui();

        Enginecore.render();



    }
    ImGui::SFML::Shutdown();
    return 0;
}