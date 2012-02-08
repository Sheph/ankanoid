#include "Utils.h"
#include <GLES/gl.h>

void drawDebugRectangle(const Vector2& pos, UInt32 width, UInt32 height, bool forSprite)
{
    GLfixed vertices[] =
    {
        pos.x(), pos.y(),
        pos.x(), pos.y() + height - 1,
        pos.x() + width - 1, pos.y() + height - 1,
        pos.x() + width - 1, pos.y()
    };

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);

    glEnableClientState(GL_VERTEX_ARRAY);

    if (forSprite)
    {
        glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    }
    else
    {
        glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    }

    glVertexPointer(2, GL_FIXED, 0, &vertices[0]);

    glDrawArrays(GL_LINE_LOOP, 0, sizeof(vertices) / (2 * sizeof(vertices[0])));

    glDisableClientState(GL_VERTEX_ARRAY);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
}
