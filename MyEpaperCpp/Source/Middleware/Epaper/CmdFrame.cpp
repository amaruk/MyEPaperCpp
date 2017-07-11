#include "Middleware/Epaper/CmdFrame.h"


void CmdFrame::updateFrm(const frmCmdType &cmd, const std::vector<uint8_t> &data)
{
    frmCmd = cmd;
    frmData = data;
}
