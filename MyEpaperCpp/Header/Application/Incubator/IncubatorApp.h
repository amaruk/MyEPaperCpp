#pragma once

#include "Infrastructure/OSAbstraction/Windows/SerialPort.h"
#include "Middleware/Epaper/EpaperController.h"

class IncubatorApp
{
public:
    IncubatorApp();
    ~IncubatorApp();

    void run(void);
    bool init(void);

private:
    CSerialPort serialPort;
    EpaperController epaper = EpaperController(serialPort);
};

