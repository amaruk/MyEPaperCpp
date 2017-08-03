// This project is designed to control Waveshare 4.3 inch E-Paper UART module.
// I don't like any license, so feel free to clone and use this project.
// Some of third party source code is collected from Internet.
// If I used your source code in a wrong way (Oh, I really hate license),
// please send me an Email: amaruk@163.com
//
// Version History:
//
//   Version 0.0.1
//   Date: 2017-07-09
//   Author: Amaruk
//   Description: Not decided yet what I'm going to make at the moment. Will find it out later.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Application\Incubator\IncubatorApp.h"

using std::cout;
using std::endl;

int main()
{
    IncubatorApp app = IncubatorApp(6);
	app.init();
    app.run();

    return 0;
}

