#ifndef GAMECONTAINERWIDGET_H
#define GAMECONTAINERWIDGET_H

#include "gamedef.h"
#include "tile.h"
#include <list>
#include <random>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <QUrl>
#include <QDir>
#include <QColor>
#include <QWidget>
#include <QPainter>
#include <QMessageBox>
#include <QSoundEffect>
#include <QStandardPaths>
#include <vector>
#include <QInputDialog>
#include <QLineEdit>
#include <QString>
#include <exception>
#include <algorithm>

class GameContainer : public QWidget
{
    Q_OBJECT
public:
    explicit GameContainer(QWidget *parent = nullptr); // 构造函数
    void addTile(int value, int row, int col); // 增加方块
    void move(int direction); // 移动方块
    void generateRandomTile(); // 生成随机方块
    void newGame(); // 新游戏
    std::vector<std::vector<Tile *>> getTilesMatrix(); // 获取方块矩阵
    int getScore() const; // 获取分数
    void updateScore(int value); // 更新(增加)分数
    void resetScore(); // 重置分数
    std::string serialize(); // 序列化游戏状态
    std::string partSerialize(); // 序列化游戏状态(不含道具状态)
    void deserialize(); // 反序列化游戏状态
    void partDeserialize(); // 反序列化游戏状态(不含道具状态)
    void recordFile(); // 储存游戏状态到文件
    void readFile(); // 从文件读取游戏状态
    void eliminateCol(); // 消除一列
    void eliminateRow(); // 消除一行
    void retract(); // 回退一步
    void cleanTiles(); // 清除多余方块
    int getWinTile() const; // 获取获胜方块
    void setWinTile(int value); // 设置获胜方块
    int judge(); // 判断游戏输赢状态
    void playSoundEffect(int value); // 播放音效
    void updateInformation(); // 更新序列
    void recordScore(int score, std::string nameThis); // 记录分数排行榜
    void setHighest();// 获取历史最高分
    void setName(); // 获取玩家姓名
    void initHighest(); // 初始化最高分
    void saveHighest(); // 保存最高分
    void setSoundEffectsVolume(double value);
protected:
    void paintEvent(QPaintEvent *) override;
private:
    int score, highest, winTile;
    double soundEffectsVolume;
    std::string information;
    std::string tempInformation;
    std::list<Tile> tiles;
    bool propFlag;
    int propEliminateCol;
    int propEliminateRow;
    int propRetraction;
    std::vector<int> scoreList;
    std::vector<std::string> nameList;
    std::string name;
signals:
    void scoreUpdated(int);
    void bestScoreUpdated(int);
    void soundEffectsVolumeChanged(int);
    void rankingListUpdated(const std::string &);
public slots:
};

#endif // GAMECONTAINERWIDGET_H
