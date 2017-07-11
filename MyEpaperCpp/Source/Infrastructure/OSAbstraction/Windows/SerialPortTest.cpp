// main.cpp : Defines the entry point for the console application.  
//  

#include "stdafx.h"  
#include "Infrastructure/OSAbstraction/Windows/SerialPort.h"
#include <iostream>  

using std::cout;
using std::endl;

int notmain(int argc, char* argv[])
{

    CSerialPort mySerialPort;

    if (!mySerialPort.InitPort(7))
    {
        std::cout << "initPort fail !" << std::endl;
        return -1;
    }
    else
    {
        std::cout << "initPort success !" << std::endl;
    }

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

    cout << "Sending data..." << endl;
    unsigned char dataOut[10] = { 'H', 'e', 'l', 'l', 'o', '!' };
    mySerialPort.WriteData(dataOut, 6);

    Sleep(100);

    UINT bytesCnt = 0;
    do {
        bytesCnt = mySerialPort.GetBytesInCOM();
    } while (bytesCnt == 0);

    cout << "Received bytes[" << bytesCnt << "]: ";

    for (UINT i = 0; i != bytesCnt; i++)
    {
        char dataIn = '@';
        mySerialPort.ReadChar(dataIn);
        cout << dataIn << " ";
    }

    cout << endl;
    

    return 0;
}