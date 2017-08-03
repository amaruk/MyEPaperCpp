#pragma once

#include "Infrastructure/OSAbstraction/Windows/SerialPort.h"
#include "Middleware/Epaper/EpaperController.h"

class IncubatorApp
{
public:
    IncubatorApp(void) = delete;
    IncubatorApp(uint32_t serialPort);
    ~IncubatorApp(void) = default;

	void init(void);
    void run(void);

private:
    EpaperController epaper;
};

