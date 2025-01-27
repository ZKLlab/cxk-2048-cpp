#ifndef TILE_H
#define TILE_H

#include "gamedef.h"
#include <iostream>
#include <sstream>
#include <QWidget>
#include <QPainter>
#include <QVariant>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

class ScaleAnimation : public QPropertyAnimation
{
public:
    ScaleAnimation(bool doubleValueRequired, double &scale, QObject *target, const QByteArray &propertyName, QObject *parent = nullptr) :
        QPropertyAnimation(target, propertyName, parent),
        scale(scale),
        doubleValueRequired(doubleValueRequired)
    {}
protected:
    void updateCurrentValue(const QVariant &value);
private:
    double &scale;
    bool doubleValueRequired;
};

class Tile : public QWidget
{
    Q_OBJECT
public:
    Tile(int value, int row, int col); // 构造函数
    int getX() const; // 获取X坐标
    int getY() const; // 获取Y坐标
    void moveTo(int row, int col); // 移动到
    void doubleValue(); // 值翻倍
    void moveToAndDoubleValue(int row, int col); // 移动且值翻倍
    int getFontPixelSize() const; // 获取文字像素尺寸
    std::string getForeColor() const; // 获取前景色
    std::string getBackgroundColor() const; // 获取背景色
    std::string getValueText() const; // 获取值文字
    std::string getText() const; // 获取文字
    int getRow() const; // 获取行号
    int getCol() const; // 获取列号
    int getValue() const; // 获取值
    ~Tile() override;
protected:
    void paintEvent(QPaintEvent *) override;
private:
    int index, value, i, j, x, y;
    double scale;
    ScaleAnimation *posAnimation;
signals:
public slots:
};

#endif // TILE_H
