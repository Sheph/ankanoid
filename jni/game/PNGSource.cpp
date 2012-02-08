#include "PNGSource.h"
#include "PNGUtils.h"

static void PNGReadFunc(png_structp pngPtr, png_bytep data, png_size_t length)
{
    zip_file* stream = reinterpret_cast<zip_file*>(::png_get_io_ptr(pngPtr));

    if (!stream)
    {
        PNGThrow(pngPtr);
    }

    if (zip_fread(stream, data, length) != static_cast<int>(length))
    {
        PNGThrow(pngPtr);
    }
}

void setPNGSource(png_structp pngPtr, zip_file* stream)
{
    ::png_set_read_fn(pngPtr, stream, PNGReadFunc);
}
