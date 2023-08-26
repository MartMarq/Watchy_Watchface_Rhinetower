#ifndef WATCHY_Tower_H
#define WATCHY_Tower_H

#ifdef WATCHY_SIM
    #include "..\..\Watchy.h"
#else // WATCHY_SIM
    #include <Watchy.h>
#endif // WATCHY_SIM
#include "FreeMonoBoldOblique22pt7b.h"
#include "FreeMonoBoldOblique15pt7b.h"
#include "icons.h"

class WatchyTower : public Watchy{
    using Watchy::Watchy;
    public:
        void drawWatchFace();
        void drawTime();
        void drawBattery();
};

#endif