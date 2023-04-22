#pragma once

namespace rpgui::common
{
    class Activatable
    {
    private:
        
    public:

        bool isActive = false;
        
        virtual ~Activatable() {}

        virtual void HandleActive() = 0;
    };

    
} // namespace rpgui::common
