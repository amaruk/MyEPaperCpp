#pragma once

#include "Infrastructure/OSAbstraction/Windows/SerialPort.h"
#include "Middleware/Epaper/CmdFrame.h"

class EpaperController
{
public:
    EpaperController(const CSerialPort &serialInit);
    ~EpaperController();

    void reset(void); // Reset the epaper module
    void wakeup(void); // Wakeup the epaper module
    void handshake(void);
#if 0

    void LibEpdSetBaud(long baud);
    void lib_epd_read_baud(void);
    void LibEpdSetMemory(unsigned char mode);
    void LibEpdEnterStopMode(void);
    void LibEpdUpdate(void);
    void LibEpdScreenRotation(unsigned char mode);
    void LibEpdLoadFont(void);
    void LibEpdLoadPic(void);

    void LibEpdSetColor(unsigned char color, unsigned char bkcolor);
    void LibEpdSetEnFont(unsigned char font);
    void LibEpdSetChFont(unsigned char font);

    void LibEpdDrawPixel(int x0, int y0);
    void LibEpdDrawLine(int x0, int y0, int x1, int y1);
    void LibEpdFillRect(int x0, int y0, int x1, int y1);
    void LibEpdDrawCircle(int x0, int y0, int r);
    void LibEpdFillCircle(int x0, int y0, int r);
    void LibEpdDrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2);
    void LibEpdFillTriangle(int x0, int y0, int x1, int y1, int x2, int y2);
    void LibEpdClear(void);

    void LibEpdDispChar(unsigned char ch, int x0, int y0);
    void LibEpdDispString(const void * p, int x0, int y0);

    void LibEpdDispBitmap(const void * p, int x0, int y0);
#endif

private:
    CSerialPort serialPort;
    CmdFrame cmdFrame;

};

