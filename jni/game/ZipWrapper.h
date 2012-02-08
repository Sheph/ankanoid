#ifndef _ZIPWRAPPER_H_
#define _ZIPWRAPPER_H_

#include "Types.h"
#include <zip.h>

class ZipWrapper
{
public:
    ZipWrapper(const std::string& path)
    : archive_(zip_open(path.c_str(), 0, NULL))
    {
    }

    ~ZipWrapper()
    {
        if (archive_)
        {
            zip_close(archive_);
            archive_ = NULL;
        }
    }

    zip* archive() { return archive_; }

private:
    zip* archive_;
};

#endif
