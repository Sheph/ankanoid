#ifndef _PNGSOURCE_H_
#define _PNGSOURCE_H_

#include "Types.h"
#include "png.h"
#include "zip.h"
#include <iostream>

void setPNGSource(png_structp pngPtr, zip_file* stream);

#endif
