#pragma once

#include <stdint.h>
#include <vector>
#include <array>
#include <deque>

enum class frmCmdType : uint8_t
{

    // System configuration
    HANDSHAKE = 0x00,
    SET_BAUD = 0x01,
    READ_BAUD = 0x02,
    GET_MEM_MODE = 0x06,
    SET_MEM_MODE = 0x07,
    ENTER_STOP_MODE = 0x08,
    SCR_UPDATE = 0x0A,
    GET_SCR_ROTATION = 0x0C,
    SET_SCR_ROTATION = 0x0D,
    LOAD_FONT = 0x0E,
    LOAD_PIC = 0x0F,
    // Display configuration
    SET_COLOR = 0x10,
    GET_COLOR = 0x11,
    GET_EN_FONT = 0x1C,
    GET_CH_FONT = 0x1D,
    SET_EN_FONT = 0x1E,
    SET_CH_FONT = 0x1F,
    // Drawing
    DRAW_PIXEL = 0x20,
    DRAW_LINE = 0x22,
    FILL_RECT = 0x24,
    DRAW_RECT = 0x25,
    DRAW_CIRCLE = 0x26,
    FILL_CIRCLE = 0x27,
    DRAW_TRIANGLE = 0x28,
    FILL_TRIANGLE = 0x29,
    FILL_SCR_BG = 0x2E,
    // Text
    DRAW_STRING = 0x30,
    // Image
    DRAW_BITMAP = 0x70,
    // Invalid
    INVALID = 0xFF,
};

#if 0

/* Color define */
#define    WHITE                    0x03
#define    GRAY                     0x02
#define    DARK_GRAY                0x01
#define    BLACK                    0x00

/* Frame buff size */
#define     FRAME_BUFF_SIZE         512	
/* Frame start byte */
#define     START                   0xA5
/* Frame end sequence */
#define     END_0                   0xCC
#define     END_1                   0x33
#define     END_2                   0xC3
#define     END_3                   0x3C


/*
FONT
*/
#define    GBK32                              0x01
#define    GBK48                              0x02
#define    GBK64                              0x03

#define    ASCII32                            0x01
#define    ASCII48                            0x02
#define    ASCII64                            0x03

/* Memory Mode */
#define    MEM_NAND                           0
#define    MEM_TF                             1

/*
set screen rotation
*/
#define    EPD_NORMAL                         0              //screen normal
#define    EPD_INVERSION                      1              //screen inversion

#endif

class CmdFrame
{
public:
    CmdFrame() = default;
    ~CmdFrame() = default;

    // Frame length without data.
    // Contains Header/Len*2/Cmd/End*4/Parity only.
    static const uint8_t frmLenNoData = 0x09;
    // The frmData can be as large as 1024 bytes, set to 255 here to save space.
    // TODO: Increase the array size?
    static const uint8_t frmLenMax = 0xFF;

    // Create a new command frame with specified type and data
    void createFrm(const frmCmdType &cmd, const std::deque<uint8_t> &data);
    // Create a new command frame with specified type and empth data
    void createFrm(const frmCmdType &cmd);
    // Serialize frame data into a deque
    std::deque<uint8_t> &serializeFrm(void);

private:
    const uint8_t frmHeader = 0xA5; // Header
    uint16_t frmLen = frmLenNoData; // Length
    frmCmdType frmCmd = frmCmdType::INVALID; // Command type
    std::deque<uint8_t> frmData = { }; // Data
    const std::deque<uint8_t> frmEnd = { 0xCC, 0x33, 0xC3, 0x3C }; // End
    uint8_t frmParity = 0x00; // Parity: XOR from header to end


    // Serialized bytes to be sent to UART port.
    std::deque<uint8_t> serializedFrm;

};

