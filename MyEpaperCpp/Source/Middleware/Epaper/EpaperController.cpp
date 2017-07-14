#include "Middleware/Epaper/EpaperController.h"
#include <iostream>

using std::string;
using std::vector;
using std::deque;
using std::cout;
using std::endl;

// TODO The following pins are not implemented yet
static int s_pin_wakeup = 0;    // Wake up pin
static int s_pin_reset = 0;     // Reset pin
// TODO The following pin level are not implemented yet
const int PIN_LOW = 0;
const int PIN_HIGH = 1;
// TODO The usleep() shall be implemented in OS abstraction layer
void usleep(int us) {};

EpaperController::EpaperController(const CSerialPort &serialInit) : serialPort(serialInit)
{
    serialPort.ClearPort(); // Discard existing data.
    s_pin_wakeup = PIN_LOW;
    s_pin_reset = PIN_LOW;
}

EpaperController::~EpaperController()
{
}

void EpaperController::reset(void)
{
    s_pin_reset = PIN_LOW;
    usleep(10);
    s_pin_reset = PIN_HIGH;
    usleep(500);
    s_pin_reset = PIN_LOW;
    usleep(3000000);
}

void EpaperController::wakeup(void)
{
    s_pin_wakeup = PIN_LOW;
    usleep(10);
    s_pin_wakeup = PIN_HIGH;
    usleep(500);
    s_pin_wakeup = PIN_LOW;
    usleep(10);
}

void EpaperController::enterStopMode(void)
{
    deque<uint8_t> rcvData = {};
    cmdFrame.createFrm(frmCmdType::ENTER_STOP_MODE);

    serialPort.transaction(cmdFrame.serializeFrm(), rcvData);
}

void EpaperController::handshake(void)
{
    deque<uint8_t> rcvData = {};
    cmdFrame.createFrm(frmCmdType::HANDSHAKE);

    serialPort.transaction(cmdFrame.serializeFrm(), rcvData);
    // Returns "OK" if epaper is ready
    // TODO: Check handshake result
}

// Set baudrate
void EpaperController::setBaud(uint32_t baud)
{
    deque<uint8_t> dqBaud = {};
    dqBaud.push_back(static_cast<uint8_t>(((baud >> 24) & 0xFF)));
    dqBaud.push_back(static_cast<uint8_t>(((baud >> 16) & 0xFF)));
    dqBaud.push_back(static_cast<uint8_t>(((baud >> 8) & 0xFF)));
    dqBaud.push_back(static_cast<uint8_t>(((baud) & 0xFF)));

    cmdFrame.createFrm(frmCmdType::SET_BAUD, dqBaud);

    serialPort.WriteData(cmdFrame.serializeFrm());
}

// Read baudrate
void EpaperController::getBaud(void)
{
    deque<uint8_t> rcvData = {};
    cmdFrame.createFrm(frmCmdType::READ_BAUD);

    serialPort.transaction(cmdFrame.serializeFrm(), rcvData);
    // TODO: Read baud in ASCII format
}

// Update the e-paper's screen: Flush buffer to screen.
void EpaperController::scrUpdate(void)
{
    cmdFrame.createFrm(frmCmdType::SCR_UPDATE);

    serialPort.WriteData(cmdFrame.serializeFrm());
}

// Choose memory to be used: mode: MEM_TF(1) or MEM_NAND(0)
void EpaperController::setMemMode(frmCmdMemMode mode)
{
    deque<uint8_t> dqMemMode = {};

    dqMemMode.push_back(static_cast<uint8_t>(mode));
    cmdFrame.createFrm(frmCmdType::SET_MEM_MODE, dqMemMode);

    serialPort.WriteData(cmdFrame.serializeFrm());
}

//  ormal screen (0) or upside down screen (1)
void EpaperController::setScrRot(frmCmdRotation rot)
{
    deque<uint8_t> dqRotation = {};

    dqRotation.push_back(static_cast<uint8_t>(rot));
    cmdFrame.createFrm(frmCmdType::SET_SCR_ROTATION, dqRotation);

    serialPort.WriteData(cmdFrame.serializeFrm());
}

// Clear screen using the background colour
void EpaperController::fillScrBg(void)
{
    cmdFrame.createFrm(frmCmdType::FILL_SCR_BG);

    serialPort.WriteData(cmdFrame.serializeFrm());
}


// Draw single pixel
void EpaperController::drawPixel(int16_t x0, int16_t y0)
{
    deque<uint8_t> dqPixel = {};
    dqPixel.push_back(static_cast<uint8_t>((x0 >> 8) & 0xFF));
    dqPixel.push_back(static_cast<uint8_t>(x0 & 0xFF));
    dqPixel.push_back(static_cast<uint8_t>((y0 >> 8) & 0xFF));
    dqPixel.push_back(static_cast<uint8_t>(y0 & 0xFF));

    cmdFrame.createFrm(frmCmdType::DRAW_PIXEL, dqPixel);

    serialPort.WriteData(cmdFrame.serializeFrm());
}

// Draw line
void EpaperController::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
{
    deque<uint8_t> dqLine = {};
    dqLine.push_back(static_cast<uint8_t>((x0 >> 8) & 0xFF));
    dqLine.push_back(static_cast<uint8_t>(x0 & 0xFF));
    dqLine.push_back(static_cast<uint8_t>((y0 >> 8) & 0xFF));
    dqLine.push_back(static_cast<uint8_t>(y0 & 0xFF));
    dqLine.push_back(static_cast<uint8_t>((x1 >> 8) & 0xFF));
    dqLine.push_back(static_cast<uint8_t>(x1 & 0xFF));
    dqLine.push_back(static_cast<uint8_t>((y1 >> 8) & 0xFF));
    dqLine.push_back(static_cast<uint8_t>(y1 & 0xFF));

    cmdFrame.createFrm(frmCmdType::DRAW_LINE, dqLine);

    serialPort.WriteData(cmdFrame.serializeFrm());
}

/* Set fore-ground and back-ground colours */
void EpaperController::setColor(frmCmdColor color, frmCmdColor bgcolor)
{
    deque<uint8_t> dqLine = {};
    dqLine.push_back(static_cast<uint8_t>(color));
    dqLine.push_back(static_cast<uint8_t>(bgcolor));

    cmdFrame.createFrm(frmCmdType::SET_COLOR, dqLine);

    serialPort.WriteData(cmdFrame.serializeFrm());
}

// Fill rectangle
void EpaperController::fillRect(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
{
    deque<uint8_t> dqRect = {};
    dqRect.push_back(static_cast<uint8_t>((x0 >> 8) & 0xFF));
    dqRect.push_back(static_cast<uint8_t>(x0 & 0xFF));
    dqRect.push_back(static_cast<uint8_t>((y0 >> 8) & 0xFF));
    dqRect.push_back(static_cast<uint8_t>(y0 & 0xFF));
    dqRect.push_back(static_cast<uint8_t>((x1 >> 8) & 0xFF));
    dqRect.push_back(static_cast<uint8_t>(x1 & 0xFF));
    dqRect.push_back(static_cast<uint8_t>((y1 >> 8) & 0xFF));
    dqRect.push_back(static_cast<uint8_t>(y1 & 0xFF));

    cmdFrame.createFrm(frmCmdType::FILL_RECT, dqRect);

    serialPort.WriteData(cmdFrame.serializeFrm());
}


// Draw circle
void EpaperController::drawCircle(int16_t x0, int16_t y0, int16_t r)
{
    deque<uint8_t> dqCircle = {};
    dqCircle.push_back(static_cast<uint8_t>((x0 >> 8) & 0xFF));
    dqCircle.push_back(static_cast<uint8_t>(x0 & 0xFF));
    dqCircle.push_back(static_cast<uint8_t>((y0 >> 8) & 0xFF));
    dqCircle.push_back(static_cast<uint8_t>(y0 & 0xFF));
    dqCircle.push_back(static_cast<uint8_t>((r >> 8) & 0xFF));
    dqCircle.push_back(static_cast<uint8_t>(r & 0xFF));

    cmdFrame.createFrm(frmCmdType::DRAW_CIRCLE, dqCircle);

    serialPort.WriteData(cmdFrame.serializeFrm());
}

// Fill circle
void EpaperController::fillCircle(int16_t x0, int16_t y0, int16_t r)
{
    deque<uint8_t> dqCircle = {};
    dqCircle.push_back(static_cast<uint8_t>((x0 >> 8) & 0xFF));
    dqCircle.push_back(static_cast<uint8_t>(x0 & 0xFF));
    dqCircle.push_back(static_cast<uint8_t>((y0 >> 8) & 0xFF));
    dqCircle.push_back(static_cast<uint8_t>(y0 & 0xFF));
    dqCircle.push_back(static_cast<uint8_t>((r >> 8) & 0xFF));
    dqCircle.push_back(static_cast<uint8_t>(r & 0xFF));

    cmdFrame.createFrm(frmCmdType::FILL_CIRCLE, dqCircle);

    serialPort.WriteData(cmdFrame.serializeFrm());
}

// Draw triangle
void EpaperController::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
    deque<uint8_t> dpTri = {};
    dpTri.push_back(static_cast<uint8_t>((x0 >> 8) & 0xFF));
    dpTri.push_back(static_cast<uint8_t>(x0 & 0xFF));
    dpTri.push_back(static_cast<uint8_t>((y0 >> 8) & 0xFF));
    dpTri.push_back(static_cast<uint8_t>(y0 & 0xFF));
    dpTri.push_back(static_cast<uint8_t>((x1 >> 8) & 0xFF));
    dpTri.push_back(static_cast<uint8_t>(x1 & 0xFF));
    dpTri.push_back(static_cast<uint8_t>((y1 >> 8) & 0xFF));
    dpTri.push_back(static_cast<uint8_t>(y1 & 0xFF));
    dpTri.push_back(static_cast<uint8_t>((x2 >> 8) & 0xFF));
    dpTri.push_back(static_cast<uint8_t>(x2 & 0xFF));
    dpTri.push_back(static_cast<uint8_t>((y2 >> 8) & 0xFF));
    dpTri.push_back(static_cast<uint8_t>(y2 & 0xFF));

    cmdFrame.createFrm(frmCmdType::DRAW_TRIANGLE, dpTri);

    serialPort.WriteData(cmdFrame.serializeFrm());
}

// Fill triangle
void EpaperController::fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
    deque<uint8_t> dpTri = {};
    dpTri.push_back(static_cast<uint8_t>((x0 >> 8) & 0xFF));
    dpTri.push_back(static_cast<uint8_t>(x0 & 0xFF));
    dpTri.push_back(static_cast<uint8_t>((y0 >> 8) & 0xFF));
    dpTri.push_back(static_cast<uint8_t>(y0 & 0xFF));
    dpTri.push_back(static_cast<uint8_t>((x1 >> 8) & 0xFF));
    dpTri.push_back(static_cast<uint8_t>(x1 & 0xFF));
    dpTri.push_back(static_cast<uint8_t>((y1 >> 8) & 0xFF));
    dpTri.push_back(static_cast<uint8_t>(y1 & 0xFF));
    dpTri.push_back(static_cast<uint8_t>((x2 >> 8) & 0xFF));
    dpTri.push_back(static_cast<uint8_t>(x2 & 0xFF));
    dpTri.push_back(static_cast<uint8_t>((y2 >> 8) & 0xFF));
    dpTri.push_back(static_cast<uint8_t>(y2 & 0xFF));

    cmdFrame.createFrm(frmCmdType::FILL_TRIANGLE, dpTri);

    serialPort.WriteData(cmdFrame.serializeFrm());
}

// Load font from TF to NAND
void EpaperController::loadFont(void)
{
    cmdFrame.createFrm(frmCmdType::LOAD_FONT);

    serialPort.WriteData(cmdFrame.serializeFrm());
}

// Set Chinese font: 1:32dot 2:48dot 3:64dot
void EpaperController::setChFont(frmCmdChFont font)
{
    deque<uint8_t> dqFont = {};

    dqFont.push_back(static_cast<uint8_t>(font));
    cmdFrame.createFrm(frmCmdType::SET_CH_FONT, dqFont);

    serialPort.WriteData(cmdFrame.serializeFrm());
}

// Set English font: 1:32dot 2:48dot 3:64dot
void EpaperController::setEnFont(frmCmdEnFont font)
{
    deque<uint8_t> dqFont = {};

    dqFont.push_back(static_cast<uint8_t>(font));
    cmdFrame.createFrm(frmCmdType::SET_EN_FONT, dqFont);

    serialPort.WriteData(cmdFrame.serializeFrm());
}

// Display text
void EpaperController::drawStr(const string &str, int16_t x0, int16_t y0)
{
    deque<uint8_t> dpStr = {};
    dpStr.push_back(static_cast<uint8_t>((x0 >> 8) & 0xFF));
    dpStr.push_back(static_cast<uint8_t>(x0 & 0xFF));
    dpStr.push_back(static_cast<uint8_t>((y0 >> 8) & 0xFF));
    dpStr.push_back(static_cast<uint8_t>(y0 & 0xFF));

    for (char ch : str)
    { dpStr.push_back(static_cast<uint8_t>(ch)); }

    cmdFrame.createFrm(frmCmdType::DRAW_STRING, dpStr);

    serialPort.WriteData(cmdFrame.serializeFrm());
}

// Load BMP from TF to NAND
void EpaperController::loadPic(void)
{
    cmdFrame.createFrm(frmCmdType::LOAD_PIC);

    serialPort.WriteData(cmdFrame.serializeFrm());
}

// Display BMP. Bitmap file name string maximum length is 11
void EpaperController::drawBitmap(const string &fileNme, int16_t x0, int16_t y0)
{
    deque<uint8_t> dpFileName = {};
    dpFileName.push_back(static_cast<uint8_t>((x0 >> 8) & 0xFF));
    dpFileName.push_back(static_cast<uint8_t>(x0 & 0xFF));
    dpFileName.push_back(static_cast<uint8_t>((y0 >> 8) & 0xFF));
    dpFileName.push_back(static_cast<uint8_t>(y0 & 0xFF));

    for (char ch : fileNme)
    {
        dpFileName.push_back(static_cast<uint8_t>(ch));
    }

    cmdFrame.createFrm(frmCmdType::DRAW_BITMAP, dpFileName);

    serialPort.WriteData(cmdFrame.serializeFrm());
}
