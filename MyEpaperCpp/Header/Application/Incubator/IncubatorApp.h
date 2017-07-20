#pragma once

#include "Infrastructure/OSAbstraction/Windows/SerialPort.h"
#include "Middleware/Epaper/EpaperController.h"

class IncubatorApp
{
public:
    IncubatorApp(void);
    ~IncubatorApp(void);

    void run(void);
    bool init(void);

private:
    CSerialPort serialPort;
    EpaperController epaper;
};

