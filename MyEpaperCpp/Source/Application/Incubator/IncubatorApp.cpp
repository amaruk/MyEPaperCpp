#include "stdafx.h"
#include "Application/Incubator/IncubatorApp.h"
#include <iostream>

using std::cout;
using std::endl;

IncubatorApp::IncubatorApp(uint32_t serialPort) : 
    epaper(serialPort)
{
    return;
#ifdef DEBUG_CALL_SEQUENCE
    cout << "CALL: IncubatorApp(...)" << endl;
#endif
}

static void drawBasic(EpaperController &epaper)
{
    int i, j;

    /* draw pixel */
    epaper.fillScrBg();
    for (j = 0; j < 600; j += 50)
    {
        for (i = 0; i < 800; i += 50)
        {
            epaper.drawPixel(i, j);
            epaper.drawPixel(i, j + 1);
            epaper.drawPixel(i + 1, j);
            epaper.drawPixel(i + 1, j + 1);
        }
    }

    epaper.scrUpdate();
    Sleep(3000);

    /* draw line */
    epaper.fillScrBg();
    for (i = 0; i < 800; i += 100)
    {
        epaper.drawLine(0, 0, i, 599);
        epaper.drawLine(799, 0, i, 599);
    }

    epaper.scrUpdate();
    Sleep(3000);

    /* fill rect */
    epaper.fillScrBg();
    epaper.setColor(frmCmdColor::BLACK, frmCmdColor::WHITE);
    epaper.fillRect(10, 10, 100, 100);

    epaper.setColor(frmCmdColor::DARK_GRAY, frmCmdColor::WHITE);
    epaper.fillRect(110, 10, 200, 100);

    epaper.setColor(frmCmdColor::GRAY, frmCmdColor::WHITE);
    epaper.fillRect(210, 10, 300, 100);

    epaper.scrUpdate();
    Sleep(3000);

    /* draw circle */
    epaper.setColor(frmCmdColor::BLACK, frmCmdColor::WHITE);
    epaper.fillScrBg();
    for (i = 0; i < 300; i += 40)
    {
        epaper.drawCircle(399, 299, i);
    }
    
    epaper.scrUpdate();
    Sleep(3000);

    /* fill circle */
    epaper.fillScrBg();
    for (j = 0; j < 6; j++)
    {
        for (i = 0; i < 8; i++)
        {
            epaper.fillCircle(50 + i * 100, 50 + j * 100, 50);
        }
    }

    epaper.scrUpdate();
    Sleep(3000);

    /* draw triangle */
    epaper.fillScrBg();
    for (i = 1; i < 5; i++)
    {
        epaper.drawTriangle(399, 249 - i * 50, 349 - i * 50, 349 + i * 50,
            449 + i * 50, 349 + i * 50);
    }

    epaper.scrUpdate();
    Sleep(3000);
}

void drawText(EpaperController &epaper)
{
    epaper.fillScrBg();
    cout << "Set colours..." << endl;
    epaper.setColor(frmCmdColor::BLACK, frmCmdColor::WHITE);
    cout << "Display Chinese..." << endl;
    epaper.setChFont(frmCmdChFont::GBK32);
    epaper.drawChStr(L"中文：狐狸", 0, 50);
    epaper.setChFont(frmCmdChFont::GBK48);
    epaper.drawChStr(L"中文：熊妈", 0, 100);
    epaper.setChFont(frmCmdChFont::GBK64);
    epaper.drawChStr(L"中文：荟雅", 0, 160);

    cout << "Display English..." << endl;
    epaper.setEnFont(frmCmdEnFont::ASCII32);
    epaper.drawEnStr("ASCII32: Fox!", 0, 300);
    epaper.setEnFont(frmCmdEnFont::ASCII48);
    epaper.drawEnStr("ASCII48: Carrie!", 0, 350);
    epaper.setEnFont(frmCmdEnFont::ASCII64);
    epaper.drawEnStr("ASCII64: Aya!", 0, 450);

    Sleep(3000);
    epaper.scrUpdate();
}

void drawBitmap(EpaperController &epaper)
{
    epaper.fillScrBg();

    epaper.drawBitmap("PIC4.BMP", 0, 0);
    epaper.scrUpdate();
    Sleep(5000);

    epaper.fillScrBg();
    epaper.drawBitmap("PIC2.BMP", 0, 100);
    epaper.drawBitmap("PIC3.BMP", 400, 100);
    epaper.scrUpdate();
    Sleep(5000);

    epaper.fillScrBg();
    epaper.drawBitmap("BLACK.BMP", 0, 0);
    epaper.scrUpdate();
    Sleep(5000);

    epaper.fillScrBg();
    epaper.drawBitmap("WHITE.BMP", 0, 0);
    epaper.scrUpdate();

    epaper.fillScrBg();
    epaper.drawBitmap("GIMP.BMP", 0, 0);
    epaper.scrUpdate();
    Sleep(5000);
}

void IncubatorApp::init(void)
{
	// Handshake with Epaper and do basic settings
	epaper.wakeup();
	cout << "Handshaking..." << endl;
	epaper.handshake();

	Sleep(1000);

	cout << "Cleaning..." << endl;
	epaper.scrUpdate();
	cout << "Set Mode to TF..." << endl;
	epaper.setMemMode(frmCmdMemMode::MEM_TF);

	// TODO: Show Startup Logo screen here.
}

void IncubatorApp::run(void)
{

#if 0
    // Basic draw API
    cout << "drawBasic..." << endl;
    drawBasic(epaper);

    // Text draw API
    cout << "drawText..." << endl;
    drawText(epaper);

    // Bitmap draw
    cout << "drawBitmap..." << endl;
    drawBitmap(epaper);
#endif

#if 0
    cout << "Find out display area." << endl;

    /* draw line */
    {
      epaper.setColor(frmCmdColor::BLACK, frmCmdColor::WHITE);
      epaper.fillScrBg();
      // (0,0)      (799,0)
      // (0,599)    (799,599)
      epaper.drawLine(0, 0, 799, 0);
      epaper.drawLine(0, 0, 0, 599);
      epaper.drawLine(799, 0, 799, 599);
      epaper.drawLine(0, 599, 799, 599);
    }

    epaper.scrUpdate();
    Sleep(3000);
#else
    epaper.setColor(frmCmdColor::BLACK, frmCmdColor::WHITE);
    epaper.fillScrBg();
    epaper.drawBitmap("GIMP.BMP", 0, 0);


    epaper.drawLine(0, 0, 799, 0);
    epaper.drawLine(0, 0, 0, 599);
    epaper.drawLine(799, 0, 799, 599);
    epaper.drawLine(0, 599, 799, 599);

    epaper.scrUpdate();
    Sleep(5000);
#endif

}


