#ifndef GLOBAL_H
#define GLOBAL_H

#include "frontend/mainwindow.h"
#include "backend/mediaclass.h"
#include "backend/back_main.h"

class Backend;

namespace global{
    extern Player* player;
    extern MainWindow* window;
    extern Backend* backend;
}

#endif // GLOBAL_H
