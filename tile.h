#ifndef TILE_H
#define TILE_H

#include "gamedef.h"
#include <sstream>

class Tile
{
    int index, value, i, j;
public:
    Tile(int value, int row, int col); // 构造函数
    int getX() const; // 获取X坐标
    int getY() const; // 获取Y坐标
    int getFontPixelSize() const; // 获取文字像素尺寸
    std::string getForeColor() const; // 获取前景色
    std::string getBackgroundColor() const; // 获取背景色
    std::string getValueText() const; // 获取值文字
    std::string getText() const; // 获取文字
};

#endif // TILE_H
