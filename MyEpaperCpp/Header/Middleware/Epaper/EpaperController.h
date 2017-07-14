#pragma once

#include "Infrastructure/OSAbstraction/Windows/SerialPort.h"
#include "Middleware/Epaper/CmdFrame.h"
#include <string>

class EpaperController
{
public:
    EpaperController(void) = default;
    EpaperController(const CSerialPort &serialInit);
    ~EpaperController();

    void reset(void);
    void wakeup(void);
    void enterStopMode(void); // NOT TESTED
    void handshake(void);
    void setBaud(uint32_t baud);
    void getBaud(void); // NOT TESTED
    void scrUpdate(void);
    void setMemMode(frmCmdMemMode mode);
    void setScrRot(frmCmdRotation rotat); // NOT TESTED
    void fillScrBg(void);
    void drawPixel(int16_t x0, int16_t y0);
    void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
    void setColor(frmCmdColor color, frmCmdColor bkcolor);
    void fillRect(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
    void drawCircle(int16_t x0, int16_t y0, int16_t r);
    void fillCircle(int16_t x0, int16_t y0, int16_t r);
    void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2);
    void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2); // NOT TESTED
    void loadFont(void); // NOT TESTED
    void setChFont(frmCmdChFont font);
    void setEnFont(frmCmdEnFont font);
    void drawStr(const std::string &str, int16_t x0, int16_t y0);
    void loadPic(void); // NOT TESTED
    void drawBitmap(const std::string &fileNme, int16_t x0, int16_t y0);

private:
    CSerialPort serialPort;
    CmdFrame cmdFrame;

};

