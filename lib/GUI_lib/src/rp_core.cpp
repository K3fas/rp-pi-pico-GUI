#include "rp_core.hpp"
#include "IVGA.hpp"

void rpgui::core::MainApp::Update()
{
    updateOnCore1();
}

void rpgui::core::MainApp::updateOnCore1()
{
    ProcessMouseInput();
    ProcessMouseMovement();
    if (waitVSync)
    {
        IVGA::IWaitVSync();
    }
    DrawPages();
}