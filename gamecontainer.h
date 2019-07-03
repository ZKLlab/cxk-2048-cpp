#ifndef GAMECONTAINERWIDGET_H
#define GAMECONTAINERWIDGET_H

#include "gamedef.h"
#include "tile.h"
#include <list>
#include <string>
#include <fstream>
#include <QColor>
#include <QWidget>
#include <QPainter>

class GameContainer : public QWidget
{
    Q_OBJECT
public:
    explicit GameContainer(QWidget *parent = nullptr); // 构造函数
    void addTile(int value, int row, int col); // 增加方块
    void move(); // 移动方块
    void generateRandomTile(); // 生成随机方块
    void newGame(); // 新游戏
    std::vector<std::vector<Tile *>> getTilesMatrix(); // 获取方块矩阵
    int getScore() const; // 获取分数
    void updateScore(int value); // 更新(增加)分数
    std::string serialize(); // 序列化游戏状态
    void deserialize(); // 反序列化游戏状态
    void recordFile(); // 储存游戏状态到文件
    void readFile(); // 从文件读取游戏状态
    void elmcol(); // 消除一列
    void elmrow(); // 消除一行
    void retract(); // 回退一步
    int getWinTile() const; // 获取获胜方块
    void setWinTile(int value); // 设置获胜方块
    int judge(); // 判断游戏输赢状态
protected:
    void paintEvent(QPaintEvent *) override;
private:
    int score, winTile;
    std::string information;
    std::list<Tile> tiles;
    bool prop_flag;
    int prop_elmcol;
    int prop_elmrow;
    int prop_retraction;
signals:
public slots:
};

#endif // GAMECONTAINERWIDGET_H
