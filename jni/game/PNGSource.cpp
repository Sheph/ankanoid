#include "PNGSource.h"
#include "PNGUtils.h"

static void PNGReadFunc(png_structp pngPtr, png_bytep data, png_size_t length)
{
    std::istream* stream = reinterpret_cast<std::istream*>(::png_get_io_ptr(pngPtr));

    if (!*stream)
    {
        PNGThrow(pngPtr);
    }

    if (static_cast<png_size_t>(stream->gcount()) != length)
    {
        PNGThrow(pngPtr);
    }
}

void setPNGSource(png_structp pngPtr, std::istream* stream)
{
    ::png_set_read_fn(pngPtr, stream, PNGReadFunc);
}
