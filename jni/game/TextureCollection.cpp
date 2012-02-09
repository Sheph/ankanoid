#include "TextureCollection.h"
#include "PNGDecoder.h"
#include "Logger.h"
#include <GLES/gl.h>

TextureCollection::TextureCollection()
{
}

TextureCollection::~TextureCollection()
{
    unloadAllTextures();
}

bool TextureCollection::addTexture(zip* archive, const std::string& path, TexturePtr& texture)
{
    if (!loadTexture(archive, path, texture))
    {
        return false;
    }

    textures_.push_back(texture);

    return true;
}

void TextureCollection::reload(zip* archive)
{
    for ( TextureList::iterator it = textures_.begin();
          it != textures_.end();
          ++it )
    {
        std::string path = (*it)->path();

        loadTexture(archive, path, *it);
    }
}

bool TextureCollection::loadTexture(zip* archive, const std::string& path, TexturePtr& texture)
{
    texture.reset(new Texture());

    PNGDecoder decoder(archive, path);

    if (!decoder.init())
    {
        LOGE("Unable to load texture from \"%s\"\n", path.c_str());

        return false;
    }

    std::vector<Byte> data;

    if (!decoder.decode(data))
    {
        LOGE("Error decoding texture from \"%s\"\n", path.c_str());
        return false;
    }

    GLuint id;

    glGenTextures(1, &id);

    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, decoder.width(), decoder.height(), 0, GL_RGBA,
                  GL_UNSIGNED_BYTE, (GLvoid*)&data[0] );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    if (glGetError() != GL_NO_ERROR)
    {
        /*
         * may need to call glDeleteTextures, but we don't care for this app.
         */

        LOGE("Error generating texture from \"%s\"\n", path.c_str());

        return false;
    }

    *texture = Texture(path, id, decoder.width(), decoder.height());

    LOGI( "Texture from \"%s\" created: %d, %dx%d\n",
          path.c_str(),
          texture->id(),
          texture->width(),
          texture->height() );

    return true;
}

void TextureCollection::unloadAllTextures()
{
    for ( TextureList::const_iterator it = textures_.begin();
          it != textures_.end();
          ++it )
    {
        GLuint tmp = (*it)->id();

        glDeleteTextures(1, &tmp);

        /*
         * No error checking for this app.
         */
    }

    textures_.clear();
}
