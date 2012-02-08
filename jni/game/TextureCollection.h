#ifndef _TEXTURECOLLECTION_H_
#define _TEXTURECOLLECTION_H_

#include "Types.h"
#include "Texture.h"
#include "zip.h"
#include <list>

class TextureCollection
{
public:
    TextureCollection();
    ~TextureCollection();

    bool addTexture(zip* archive, const std::string& path, Texture& texture);

private:
    typedef std::list<Texture> TextureList;

    TextureCollection(const TextureCollection& other);
    TextureCollection& operator=(const TextureCollection& other);

    void unloadAllTextures();

    TextureList textures_;
};

#endif
