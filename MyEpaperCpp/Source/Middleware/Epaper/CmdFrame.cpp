#include "Middleware/Epaper/CmdFrame.h"


CmdFrame & CmdFrame::operator=(const CmdFrame & frm)
{
    frmLen = frm.frmLen;
    frmCmd = frm.frmCmd;
    frmData = frm.frmData;
    return *this;
}

void CmdFrame::createFrm(const frmCmdType &cmd, const std::deque<uint8_t> &data)
{
    frmCmd = cmd;
    frmData = data;
}

void CmdFrame::createFrm(const frmCmdType & cmd)
{
    frmCmd = cmd;
    frmData.clear(); // Clean up the data part
}

std::deque<uint8_t>& CmdFrame::serializeFrm(void)
{
    frmParity = 0x00; // Initialize parity
    frmLen = static_cast<uint16_t>(frmLenNoData) + 
             static_cast<uint16_t>(frmData.size()); // Calculate length
    serializedFrm.clear(); // Clear serialized deque

    // Deal with Header
    serializedFrm.push_back(frmHeader);
    frmParity ^= frmHeader;

    // Deal with length
    uint8_t lenPart = static_cast<uint8_t>(frmLen >> 8);
    serializedFrm.push_back(lenPart);
    frmParity ^= lenPart;
    lenPart = static_cast<uint8_t>(frmLen & 0xFF);
    serializedFrm.push_back(lenPart);
    frmParity ^= lenPart;

    // Deal with command type
    serializedFrm.push_back(static_cast<uint8_t>(frmCmd));
    frmParity ^= static_cast<uint8_t>(frmCmd);
    
    // Deal with data
    for (uint8_t data : frmData)
    {
        serializedFrm.push_back(data);
        frmParity ^= data;
    }

    // Deal with end
    for (uint8_t data : frmEnd)
    {
        serializedFrm.push_back(data);
        frmParity ^= data;
    }

    // Deal with parity
    serializedFrm.push_back(frmParity);

    return serializedFrm;
}
