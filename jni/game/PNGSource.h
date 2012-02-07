#ifndef _PNGSOURCE_H_
#define _PNGSOURCE_H_

#include "Types.h"
#include "png.h"
#include <iostream>

void setPNGSource(png_structp pngPtr, std::istream* stream);

#endif
