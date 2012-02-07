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

bool TextureCollection::addTexture(const std::string& path, Texture& texture)
{
    PNGDecoder decoder(path);

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

    if (glGetError() != GL_NO_ERROR)
    {
        /*
         * may need to call glDeleteTextures, but we don't care for this app.
         */

        LOGE("Error generating texture from \"%s\"\n", path.c_str());

        return false;
    }

    texture = Texture(id, decoder.width(), decoder.height());

    textures_.push_back(texture);

    LOGI( "Texture from \"%s\" created: %d, %dx%d\n",
          path.c_str(),
          id,
          decoder.width(),
          decoder.height() );

    return true;
}

void TextureCollection::unloadAllTextures()
{
    for ( TextureList::const_iterator it = textures_.begin();
          it != textures_.end();
          ++it )
    {
        GLuint tmp = it->id();

        glDeleteTextures(1, &tmp);

        /*
         * No error checking for this app.
         */
    }

    textures_.clear();
}
