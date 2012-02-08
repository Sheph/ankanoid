#include "PNGDecoder.h"
#include "PNGSource.h"
#include <assert.h>

PNGDecoder::PNGDecoder(zip* archive, const std::string& path)
: stream_(archive ? zip_fopen(archive, path.c_str(), 0) : NULL),
  pngPtr_(NULL),
  pngInfoPtr_(NULL),
  width_(0),
  height_(0)
{
}

PNGDecoder::~PNGDecoder()
{
    finish();
}

bool PNGDecoder::init()
{
    assert(!pngPtr_);

    if (pngPtr_)
    {
        return false;
    }

    pngPtr_ = PNGCreateReadStruct(pngError_);

    if (!pngPtr_)
    {
        return false;
    }

    PNGCatch(pngPtr_)
    {
        return false;
    }

    pngInfoPtr_ = ::png_create_info_struct(pngPtr_);

    if (!pngInfoPtr_)
    {
        return false;
    }

    setPNGSource(pngPtr_, stream_);

    ::png_read_info(pngPtr_, pngInfoPtr_);

    int bitDepth, colorType, interlaceType;

    ::png_get_IHDR(pngPtr_, pngInfoPtr_, &width_, &height_, &bitDepth, &colorType, &interlaceType, NULL, NULL);

    if ((width_ == 0) || (height_ == 0))
    {
        return false;
    }

    if (colorType != PNG_COLOR_TYPE_RGB_ALPHA)
    {
        return false;
    }

    if (bitDepth != 8)
    {
        return false;
    }

    if (interlaceType != PNG_INTERLACE_NONE)
    {
        return false;
    }

    ::png_read_update_info(pngPtr_, pngInfoPtr_);

    if (::png_get_rowbytes(pngPtr_, pngInfoPtr_) != (width_ * 4))
    {
        return false;
    }

    return true;
}

bool PNGDecoder::decode(std::vector<Byte>& data)
{
    assert(pngPtr_);

    if (!pngPtr_)
    {
        return false;
    }

    PNGCatch(pngPtr_)
    {
        finish();

        return false;
    }

    png_size_t rowBytes = ::png_get_rowbytes(pngPtr_, pngInfoPtr_);

    data.resize(rowBytes * height_);

    std::vector<png_bytep> rowPointers(height_);

    for (UInt32 i = 0; i < height_; ++i)
    {
        rowPointers[height_ - 1 - i] = &data[0] + i * rowBytes;
    }

    ::png_read_image(pngPtr_, &rowPointers[0]);

    finish();

    return true;
}

void PNGDecoder::finish()
{
    if (pngPtr_)
    {
        PNGCatch(pngPtr_)
        {
            pngPtr_ = NULL;
            pngInfoPtr_ = NULL;

            if (stream_)
            {
                zip_fclose(stream_);
                stream_ = NULL;
            }

            return;
        }

        ::png_destroy_read_struct(&pngPtr_, (pngInfoPtr_ ? &pngInfoPtr_ : NULL), NULL);

        pngPtr_ = NULL;
        pngInfoPtr_ = NULL;
    }

    if (stream_)
    {
        zip_fclose(stream_);
        stream_ = NULL;
    }
}
