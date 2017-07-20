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


    CSerialPort mySerialPort = CSerialPort(6);

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
    deque<uint8_t> dataOutDeque = { 0xA5, 0x00, 0x09, 0x00, 0xCC, 0x33, 0xC3, 0x3C, 0xAC }; // ASCII: Handshake
    deque<uint8_t> dataInDeque = { 0x21, 0x21, 0x21 }; // ASCII: !!!

    mySerialPort.transaction(dataOutDeque, dataInDeque);

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

    // Should be "OK"
    for (char c : dataInDeque)
    { cout << c; }

    cout << endl;

    return 0;
}