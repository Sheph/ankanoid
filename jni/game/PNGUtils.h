#ifndef _PNGUTILS_H_
#define _PNGUTILS_H_

#include "Types.h"
#include "png.h"
#include <setjmp.h>

struct PNGError
{
    jmp_buf setjmp_buffer;
};

png_structp PNGCreateReadStruct(PNGError& pngError);

void PNGThrow(png_structp pngPtr);

#define PNGCatch(pngPtr) \
    if (::setjmp(reinterpret_cast<PNGError*>(png_get_error_ptr(pngPtr))->setjmp_buffer))

#endif
