#include "Animation.h"
#include <assert.h>

Animation::Animation(const Texture& texture, bool loop)
: texture_(texture),
  loop_(loop)
{
}

Animation::~Animation()
{
}

void Animation::addFrame(const AnimationFrame& frame)
{
    if (frames_.empty())
    {
        frames_.insert(std::make_pair(frame.durationMs(), frame));
    }
    else
    {
        frames_.insert(std::make_pair(
            frames_.rbegin()->second.durationMs() + frame.durationMs(), frame));
    }
}

void Animation::render(UInt32 timeMs, const Vector2& pos, UInt32 width, UInt32 height) const
{
    if (frames_.empty())
    {
        return;
    }

    AnimationFrameMap::const_iterator it = frames_.upper_bound(timeMs);

    --it;

    assert(it != frames_.end());

    renderFrame(it->second, pos, width, height);
}

bool Animation::finished(UInt32 timeMs) const
{
    if (frames_.empty())
    {
        return true;
    }
    else
    {
        return (timeMs > frames_.rbegin()->second.durationMs());
    }
}

void Animation::renderFrame( const AnimationFrame& frame,
                             const Vector2& pos,
                             UInt32 width,
                             UInt32 height ) const
{
    GLfixed vertices[] =
    {
        pos.x(), pos.y(),
        pos.x(), pos.y() + height,
        pos.x() + width, pos.y(),
        pos.x() + width, pos.y() + height
    };

    GLfixed subTexU1 = (frame.x() * (1U << 16)) / texture_.width();
    GLfixed subTexV1 = (frame.y() * (1U << 16)) / texture_.height();
    GLfixed subTexU2 = ((frame.x() + frame.width()) * (1U << 16)) / texture_.width();
    GLfixed subTexV2 = ((frame.y() + frame.height()) * (1U << 16)) / texture_.height();

    GLfixed texCoords[] =
    {
        subTexU1, subTexV1,
        subTexU1, subTexV2,
        subTexU2, subTexV1,
        subTexU2, subTexV2,
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    glVertexPointer(2, GL_FIXED, 0, &vertices[0]);
    glTexCoordPointer(2, GL_FIXED, 0, &texCoords[0]);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, sizeof(vertices) / (2 * sizeof(vertices[0])));

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}
