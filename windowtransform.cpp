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
    trueTopLeftCorner = topLeftCorner;
    trueBottomRightCorner = bottomRightCorner;
    printf("%f, %f; %f, %f\n", trueTopLeftCorner.x, trueTopLeftCorner.y, trueBottomRightCorner.x, trueBottomRightCorner.y);
}
int windowTransform::transformX(float x) {
    return int((x - trueTopLeftCorner.x) / (trueBottomRightCorner.x - trueTopLeftCorner.x) * windowWidth);
}
int windowTransform::transformY(float y) {
    return int((y - trueTopLeftCorner.y) / (trueBottomRightCorner.y - trueTopLeftCorner.y) * windowHeight);
}
int windowTransform::transformWidth(float width) {
    return int(windowWidth * (width) / (trueBottomRightCorner.x - trueTopLeftCorner.x));
}
int windowTransform::transformHeight(float height) {
    return -int(windowHeight * (height) / (trueBottomRightCorner.y - trueTopLeftCorner.y));
}
float windowTransform::transformAngle(float angle) {
    return angle * 180 / float(M_PI);
}
