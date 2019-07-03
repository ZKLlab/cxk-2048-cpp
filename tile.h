#ifndef TILE_H
#define TILE_H

#include "gamedef.h"
#include <sstream>
#include <QWidget>
#include <QPainter>
#include <QPropertyAnimation>

class Tile : public QWidget
{
    Q_OBJECT
public:
    Tile(int value, int row, int col); // 构造函数
    int getX() const; // 获取X坐标
    int getY() const; // 获取Y坐标
    void moveTo(int row, int col); // 移动到
    void doubleValue(); // 值翻倍
    int getFontPixelSize() const; // 获取文字像素尺寸
    std::string getForeColor() const; // 获取前景色
    std::string getBackgroundColor() const; // 获取背景色
    std::string getValueText() const; // 获取值文字
    std::string getText() const; // 获取文字
    void paintEvent(QPaintEvent *) override;
private:
    int index, value, i, j, x, y;
signals:
public slots:
};

#endif // TILE_H
