/*************************************************
*                                                *
*  BMPextra - an extension to EasyBMP            * 
*                                                *
*  Author: Luis Rei                              *
*   email: luis.rei@gmail.com                    *
*                                                *
*          file: BMPextra.cpp                    * 
*    date added: 04-06-2007                      *
* date modified: 04-06-2007                      *
*       version: 1.00                            *
*                                                *
*   License: BSD (revised/modified)              *
* Copyright: 2007 by Luis Rei                    * 
*                                                *
* description: Actual source file                *
*                                                *
*************************************************/


#include "BMPextra.h"

bool pixelIsWhite(RGBApixel pixel)
{
	if ((int)pixel.Blue > 234 && (int)pixel.Green > 234 && (int)pixel.Red > 234)
		return true;


	return false;
}
bool pixelIsBlack(RGBApixel pixel)
{
	if ((int)pixel.Blue < 20 && (int)pixel.Green < 20 && (int)pixel.Red < 20)
		return true;

	return false;
}

