#include "PNGUtils.h"

static void PNGErrorFunc(png_structp pngPtr, png_const_charp msg)
{
    PNGError* error = reinterpret_cast<PNGError*>(png_get_error_ptr(pngPtr));
    ::longjmp(error->setjmp_buffer, 1);
}

static void PNGWarningFunc(png_structp pngPtr, png_const_charp msg)
{
}

png_structp PNGCreateReadStruct(PNGError& pngError)
{
    return ::png_create_read_struct(PNG_LIBPNG_VER_STRING, &pngError, PNGErrorFunc, PNGWarningFunc);
}

void PNGThrow(png_structp pngPtr)
{
    ::png_error(pngPtr, "");
}
