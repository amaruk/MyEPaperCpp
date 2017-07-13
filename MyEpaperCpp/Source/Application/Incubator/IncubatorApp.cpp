#include "Application/Incubator/IncubatorApp.h"
#include <iostream>

using std::cout;
using std::endl;

IncubatorApp::IncubatorApp()
{
}


IncubatorApp::~IncubatorApp()
{
}

#if 0

static void _BaseDraw(void)
{
    int i, j;

    /* draw pixel */
    LibEpdClear();
    for (j = 0; j < 600; j += 50)
    {
        for (i = 0; i < 800; i += 50)
        {
            LibEpdDrawPixel(i, j);
            LibEpdDrawPixel(i, j + 1);
            LibEpdDrawPixel(i + 1, j);
            LibEpdDrawPixel(i + 1, j + 1);
        }
    }
    LibEpdUpdate();

    usleep(3000000);

    /* draw line */
    LibEpdClear();
    for (i = 0; i < 800; i += 100)
    {
        LibEpdDrawLine(0, 0, i, 599);
        LibEpdDrawLine(799, 0, i, 599);
    }
    LibEpdUpdate();
    usleep(3000000);

    /* fill rect */
    LibEpdClear();
    LibEpdSetColor(BLACK, WHITE);
    LibEpdFillRect(10, 10, 100, 100);

    LibEpdSetColor(DARK_GRAY, WHITE);
    LibEpdFillRect(110, 10, 200, 100);

    LibEpdSetColor(GRAY, WHITE);
    LibEpdFillRect(210, 10, 300, 100);

    LibEpdUpdate();
    usleep(3000000);

    /* draw circle */
    LibEpdSetColor(BLACK, WHITE);
    LibEpdClear();
    for (i = 0; i < 300; i += 40)
    {
        LibEpdDrawCircle(399, 299, i);
    }
    LibEpdUpdate();
    usleep(3000000);

    /* fill circle */
    LibEpdClear();
    for (j = 0; j < 6; j++)
    {
        for (i = 0; i < 8; i++)
        {
            LibEpdFillCircle(50 + i * 100, 50 + j * 100, 50);
        }
    }
    LibEpdUpdate();
    usleep(3000000);

    /* draw triangle */
    LibEpdClear();
    for (i = 1; i < 5; i++)
    {
        LibEpdDrawTriangle(399, 249 - i * 50, 349 - i * 50, 349 + i * 50,
            449 + i * 50, 349 + i * 50);
    }
    LibEpdUpdate();
    usleep(3000000);
}
void DrawTextDemo(void)
{
    LibEpdClear();
    printf("Set colours...\n");
    LibEpdSetColor(BLACK, WHITE);
    printf("Display Chinese...\n");
    LibEpdSetChFont(GBK32);
    LibEpdDispString("中文：狐狸", 0, 50);
    LibEpdSetChFont(GBK48);
    LibEpdDispString("中文：熊妈", 0, 100);
    LibEpdSetChFont(GBK64);
    LibEpdDispString("中文：荟雅", 0, 160);

    printf("Display English...\n");
    LibEpdSetEnFont(ASCII32);
    LibEpdDispString("ASCII32: Fox!", 0, 300);
    LibEpdSetEnFont(ASCII48);
    LibEpdDispString("ASCII48: Carrie!", 0, 350);
    LibEpdSetEnFont(ASCII64);
    LibEpdDispString("ASCII64: Aya!", 0, 450);

    usleep(3000000);
    LibEpdUpdate();
}

void DrawBitmapDemo(void)
{
    LibEpdClear();
    LibEpdDispBitmap("PIC4.BMP", 0, 0);
    LibEpdUpdate();
    usleep(5000000);

    LibEpdClear();
    LibEpdDispBitmap("PIC2.BMP", 0, 100);
    LibEpdDispBitmap("PIC3.BMP", 400, 100);
    LibEpdUpdate();
    usleep(5000000);

    LibEpdClear();
    LibEpdDispBitmap("FOXB.BMP", 0, 0);
    LibEpdUpdate();
}

void EpaperText(char *str, int x, int y)
{
    LibEpdClear();
    LibEpdSetColor(BLACK, WHITE);

    LibEpdSetEnFont(ASCII32);
    LibEpdDispString(str, x, y);

    usleep(1000000);
    LibEpdUpdate();
}

#endif

void IncubatorApp::run(void)
{
    epaper.wakeup();
    printf("Handshaking...\n");
    epaper.handshake();
    Sleep(1000);
#if 0
    printf("Updating...\n");
    LibEpdUpdate();
    LibEpdSetMemory(MEM_TF);

    /* base Draw demo */
    _BaseDraw();
    /* Draw text demo */
    DrawTextDemo();
    /* Draw bitmap */
    DrawBitmapDemo();

    LibEpdClear();

    LibEpdClose();

    EpaperText("Hello, BBB.", 0, 300);
#endif

}

bool IncubatorApp::init(void)
{
    if (!serialPort.InitPort(7))
    {
        std::cout << "initPort fail !" << std::endl;
        return false;
    }
    else
    {
        std::cout << "initPort success !" << std::endl;
    }

    return true;
}


