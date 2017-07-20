// main.cpp : Defines the entry point for the console application.  
//  

#include "stdafx.h"  
#include "Infrastructure/OSAbstraction/Windows/SerialPort.h"
#include "Middleware/Epaper/EpaperController.h"
#include <iostream>  

using std::cout;
using std::endl;
using std::deque;

int not_main(int argc, char* argv[])
{


    CSerialPort mySerialPort = CSerialPort();
    if (!mySerialPort.InitPort(6))
    {
        std::cout << "initPort fail !" << std::endl;
        return false;
    }
    else
    {
        std::cout << "initPort success !" << std::endl;
    }
    EpaperController epaper = EpaperController(mySerialPort);
    epaper.wakeup();
    epaper.handshake();

#if 1
    CmdFrame cmdFrame;
    deque<uint8_t> rcvData = {};
    cmdFrame.createFrm(frmCmdType::HANDSHAKE);

    if (!mySerialPort.transaction(cmdFrame.serializeFrm(), rcvData))
    {
        cout << "Handshake failed." << endl;
    }

    cout << "RX: ";
    for (uint8_t ch : rcvData)
    {
        cout << ch;
    }
    cout << endl;
#endif

    cout << "***** Test transaction *****" << endl;
    deque<uint8_t> dataOutDeque = { 0xA5, 0x00, 0x09, 0x00, 0xCC, 0x33, 0xC3, 0x3C, 0xAC }; // ASCII: Serial
    deque<uint8_t> dataInDeque = { 0x21, 0x21, 0x21 }; // ASCII: !!!

    mySerialPort.transaction(dataOutDeque, dataInDeque);

    for (char c : dataInDeque)
    {
        cout << c;
    }
    cout << endl;

#if 0
    CSerialPort mySerialPort = CSerialPort();

    if (!mySerialPort.InitPort(6))
    {
        std::cout << "/!\\ Fatal Error: initPort fail!" << std::endl;
        return -1;
    }
    else
    { ; }

#if 0
    if (!mySerialPort.OpenListenThread())
    {
        std::cout << "OpenListenThread fail !" << std::endl;
    }
    else
    {
        std::cout << "OpenListenThread success !" << std::endl;
    }
#endif

    cout << "***** Test transaction *****" << endl;
    deque<uint8_t> dataOutDeque = { 0xA5, 0x00, 0x09, 0x00, 0xCC, 0x33, 0xC3, 0x3C, 0xAC }; // ASCII: Serial
    deque<uint8_t> dataInDeque = { 0x21, 0x21, 0x21 }; // ASCII: !!!

    mySerialPort.transaction(dataOutDeque, dataInDeque);

    //mySerialPort.WriteData(dataOutDeque);

    //unsigned char dataOutAry[10] = { 'H', 'e', 'l', 'l', 'o', '!' };
    //mySerialPort.WriteData(dataOutAry, 6);

    //Sleep(100);

#if 0
    UINT bytesCnt = 0;
    do {
        bytesCnt = mySerialPort.rcvBufSize();
    } while (bytesCnt == 0);

    cout << "Received bytes[" << bytesCnt << "]: ";

    for (UINT i = 0; i != bytesCnt; i++)
    {
        char dataIn = '@';
        mySerialPort.ReadChar(dataIn);
        cout << dataIn;
    }
#endif

    //mySerialPort.ReadChar(dataInDeque);

    for (char c : dataInDeque)
    { cout << c; }

    cout << endl;
#endif

    return 0;
}