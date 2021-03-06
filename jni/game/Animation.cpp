#include "Animation.h"
#include <assert.h>

Animation::Animation(const TexturePtr& texture, bool loop)
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
        frames_.insert(std::make_pair(0, frame));
    }
    else
    {
        frames_.insert(std::make_pair(durationMs(), frame));
    }
}

void Animation::render(UInt32 timeMs, const Vector2& pos, UInt32 width, UInt32 height) const
{
    if (frames_.empty())
    {
        return;
    }

    if (loop_)
    {
        timeMs %= durationMs();
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
        return (!loop_ && (timeMs >= durationMs()));
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
        pos.x(), pos.y() + height - 1,
        pos.x() + width - 1, pos.y(),
        pos.x() + width - 1, pos.y() + height - 1
    };

    GLfixed subTexU1 = 0;
    GLfixed subTexU2 = 0;

    if (texture_->width() > 1)
    {
        subTexU1 = (frame.x() * (1U << 16)) / (texture_->width() - 1);
        subTexU2 = ((frame.x() + frame.width() - 1) * (1U << 16)) / (texture_->width() - 1);
    }

    GLfixed subTexV1 = 0;
    GLfixed subTexV2 = 0;

    if (texture_->height() > 1)
    {
        subTexV1 = ((texture_->height() - (frame.y() + frame.height())) * (1U << 16)) / (texture_->height() - 1);
        subTexV2 = ((texture_->height() - 1 - frame.y()) * (1U << 16)) / (texture_->height() - 1);
    }

    GLfixed texCoords[] =
    {
        subTexU1, subTexV1,
        subTexU1, subTexV2,
        subTexU2, subTexV1,
        subTexU2, subTexV2,
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glBindTexture(GL_TEXTURE_2D, texture_->id());

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    glVertexPointer(2, GL_FIXED, 0, &vertices[0]);
    glTexCoordPointer(2, GL_FIXED, 0, &texCoords[0]);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, sizeof(vertices) / (2 * sizeof(vertices[0])));

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

UInt32 Animation::durationMs() const
{
    if (frames_.empty())
    {
        return 0;
    }
    else
    {
        return frames_.rbegin()->first + frames_.rbegin()->second.durationMs();
    }
}
