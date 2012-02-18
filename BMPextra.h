/*************************************************
*                                                *
*  BMPextra - an extension to EasyBMP            * 
*                                                *
*  Author: Luis Rei                              *
*   email: luis.rei@gmail.com                    *
*                                                *
*          file: BMPextra.h                      * 
*    date added: 04-06-2007                      *
* date modified: 04-06-2007                      *
*       version: 1.00                            *
*                                                *
*   License: BSD (revised/modified)              *
* Copyright: 2007 by Luis Rei                    * 
*                                                *
* description: include file - includes EasyBMP   *
*                                                *
*************************************************/

#ifndef BMPEXTRA_H_
#define BMPEXTRA_H_

#include "EasyBMP.h"

bool pixelIsWhite(RGBApixel pixel);
bool pixelIsBlack(RGBApixel pixel);
void clearNoise(BMP *img);

#endif /*BMPEXTRA_H_*/
