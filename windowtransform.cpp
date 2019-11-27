#include "windowtransform.h"

windowTransform::windowTransform(b2Vec2 topLeft, b2Vec2 bottomRight, int width, int height) :
    topLeftCorner(topLeft),
    bottomRightCorner(bottomRight),
    windowWidth(width),
    windowHeight(height)
{
    updateTrueCorners();
}
void windowTransform::setBox2dWindow(b2Vec2 topLeft, b2Vec2 bottomRight) {
    this->topLeftCorner = topLeft;
    this->bottomRightCorner = bottomRight;
    updateTrueCorners();
}
void windowTransform::setWindowSize(int width, int height) {
    this->windowWidth = width;
    this->windowHeight = height;
    updateTrueCorners();
}
void windowTransform::updateTrueCorners() {
    b2Vec2 screenCenter = (topLeftCorner+bottomRightCorner);
    screenCenter.x /=2;
    screenCenter.y /=2;
    b2Vec2 size = bottomRightCorner - screenCenter;
    if (abs(windowWidth / size.x) > abs(windowHeight / size.y)) {
        size.x *= abs(windowWidth / size.x) / abs(windowHeight / size.y);
    } else {
        size.y *= abs(windowHeight / size.y) / abs(windowWidth / size.x);
    }
    trueTopLeftCorner = screenCenter - size;
    trueBottomRightCorner = screenCenter + size;
}
int windowTransform::transformX(float x) {
    return int((x - trueTopLeftCorner.x) / (trueBottomRightCorner.x - trueTopLeftCorner.x) * windowWidth);
}
int windowTransform::transformY(float y) {
    return int((y - trueTopLeftCorner.y) / (trueBottomRightCorner.y - trueTopLeftCorner.y) * windowHeight);
}
int windowTransform::transformWidth(float width) {
    return 2* int(windowWidth * (width) / (trueBottomRightCorner.x - trueTopLeftCorner.x));
}
int windowTransform::transformHeight(float height) {
    return 2*int(windowHeight * (height) / (trueTopLeftCorner.y - trueBottomRightCorner.y));
}
float windowTransform::transformAngle(float angle) {
    return -angle * 180 / float(M_PI);
}
