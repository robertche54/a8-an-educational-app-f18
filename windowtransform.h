#ifndef WINDOWTRANSFORM_H
#define WINDOWTRANSFORM_H

#include "Box2D/Box2D.h"

class windowTransform
{
private:
    b2Vec2 topLeftCorner;
    b2Vec2 bottomRightCorner;
    int windowWidth;
    int windowHeight;

    void updateTrueCorners();
    b2Vec2 trueTopLeftCorner;
    b2Vec2 trueBottomRightCorner;
public:
    windowTransform(b2Vec2 a, b2Vec2 b, int width, int height);
    void setBox2dWindow(b2Vec2 topLeft, b2Vec2 bottomRight);
    void setWindowSize(int width, int height);

    int transformX(float x);
    int transformY(float y);
    int transformWidth(float x);
    int transformHeight(float y);
    float transformAngle(float angle);
    b2Vec2 windowToWorldCoordinates(int x, int y);
};

#endif // WINDOWTRANSFORM_H
