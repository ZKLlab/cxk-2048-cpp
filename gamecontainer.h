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
    explicit GameContainer(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *) override;
    void addTile(int value, int row, int col);
    void move();
    void generateRandomTile();
    void newGame();
    std::vector<std::vector<Tile *>> getTilesMatrix();
    int getScore() const;
    void updateScore(int value);
    std::string serialize();
    void deserialize();
    void recordFile();
    void readFile();
    void elmcol();
    void elmrow();
    void retract();
    int getWinTile() const;
    void setWinTile(int value);
    int judge();
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
