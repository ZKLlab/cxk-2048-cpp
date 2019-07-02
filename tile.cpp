#include "tile.h"

static int currentIndex = 0;

Tile::Tile(int value, int row, int col) :
    index(currentIndex++),
    value(value),
    i(row),
    j(col)
{}

int Tile::getX() const
{
    return j * TILE_WIDTH + (j + 1) * GUTTER_WIDTH;
}

int Tile::getY() const
{
    return i * TILE_WIDTH + (i + 1) * GUTTER_WIDTH;
}

int Tile::getFontPixelSize() const
{
    switch (value)
    {
    case 2:
        return 20;
    case 4:
        return 28;
    case 8:
        return 18;
    case 16:
        return 18;
    case 32:
        return 16;
    case 64:
        return 28;
    case 128:
        return 28;
    case 256:
        return 40;
    case 512:
        return 40;
    case 1024:
        return 28;
    case 2048:
        return 28;
    case 4096:
        return 20;
    default:
        return 18;
    }
}

std::string Tile::getValueText() const
{
    std::ostringstream output;
    output << value;
    return output.str();
}

std::string Tile::getForeColor() const
{
    switch (value)
    {
    case 2:
    case 4:
        return "#776e65";
    default:
        return "#f9f6f2";
    }
}

std::string Tile::getBackgroundColor() const
{
    switch (value)
    {
    case 2:
        return "#eee4da";
    case 4:
        return "#ede0c8";
    case 8:
        return "#f2b179";
    case 16:
        return "#f59563";
    case 32:
        return "#f67c5f";
    case 64:
        return "#f65e3b";
    case 128:
        return "#edcf72";
    case 256:
        return "#edcc61";
    case 512:
        return "#edc850";
    case 1024:
        return "#edc53f";
    case 2048:
        return "#edc22e";
    default:
        return "#3c3a32";
    }
}

std::string Tile::getText() const
{
    switch (value)
    {
    case 2:
        return "大家好";
    case 4:
        return "我是";
    case 8:
        return "练习时长";
    case 16:
        return "两年半的";
    case 32:
        return "个人练习生";
    case 64:
        return "CXK";
    case 128:
        return "喜欢";
    case 256:
        return "唱";
    case 512:
        return "跳";
    case 1024:
        return "RAP";
    case 2048:
        return "篮球";
    case 4096:
        return "MUSIC";
    default:
        return "鸡你太美";
    }
}
