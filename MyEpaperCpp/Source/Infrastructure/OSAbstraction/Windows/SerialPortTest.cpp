// main.cpp : Defines the entry point for the console application.  
//  

#include "stdafx.h"  
#include "Infrastructure/OSAbstraction/Windows/SerialPort.h"
#include <iostream>  

using std::cout;
using std::endl;
using std::deque;

int main(int argc, char* argv[])
{

    CSerialPort mySerialPort;

    if (!mySerialPort.InitPort(7))
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
    deque<uint8_t> dataOutDeque = { 0x53, 0x65, 0x72, 0x69, 0x61, 0x6C }; // ASCII: Serial
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

    

    return 0;
}