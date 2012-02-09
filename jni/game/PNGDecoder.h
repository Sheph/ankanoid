#ifndef _PNGDECODER_H_
#define _PNGDECODER_H_

#include "Types.h"
#include "PNGUtils.h"
#include "zip.h"
#include <fstream>
#include <vector>

/*
 * RGBA8-no-interlace PNG decoder, if PNG file is not RGBA8-no-interlace then 'init' will return false.
 */
class PNGDecoder
{
public:
    explicit PNGDecoder(zip* archive, const std::string& path);
    ~PNGDecoder();

    bool init();

    bool decode(std::vector<Byte>& data);

    inline UInt32 width() const { return width_; }

    inline UInt32 height() const { return height_; }

private:
    PNGDecoder(const PNGDecoder& other);
    PNGDecoder& operator=(const PNGDecoder& other);

    void finish();

    zip_file* stream_;
    PNGError pngError_;
    png_structp pngPtr_;
    png_infop pngInfoPtr_;
    UInt32 width_;
    UInt32 height_;
};

#endif
