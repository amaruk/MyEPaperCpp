#include "Application/Incubator/IncubatorApp.h"
#include "Middleware/Epaper/EpaperController.h"
#include <iostream>

using std::cout;
using std::endl;

IncubatorApp::IncubatorApp()
{
}


IncubatorApp::~IncubatorApp()
{
}

void IncubatorApp::run(void)
{
}

bool IncubatorApp::init(void)
{

    CSerialPort serial;

    if (!serial.InitPort(7))
    {
        std::cout << "initPort fail !" << std::endl;
        return false;
    }
    else
    {
        std::cout << "initPort success !" << std::endl;
    }

    EpaperController epaper = EpaperController(serial);

    return true;
}


