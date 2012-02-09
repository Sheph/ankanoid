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

    bool addTexture(zip* archive, const std::string& path, TexturePtr& texture);

    void reload(zip* archive);

    void invalidate();

private:
    typedef std::list<TexturePtr> TextureList;

    TextureCollection(const TextureCollection& other);
    TextureCollection& operator=(const TextureCollection& other);

    bool loadTexture(zip* archive, const std::string& path, TexturePtr& texture);

    void unloadAllTextures();

    TextureList textures_;
};

#endif
