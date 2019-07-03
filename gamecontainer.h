#ifndef GAMECONTAINERWIDGET_H
#define GAMECONTAINERWIDGET_H

#include "gamedef.h"
#include "tile.h"
#include <list>
#include <QColor>
#include <QWidget>
#include <QPainter>
#include <string>
#include <fstream>

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
    void deserialize(std::string information);
    void recordFile(std::string information);
    std::string readFile();
    int getWinTile() const;
    void setWinTile(int value);
    int judge();
private:
    int score, winTile;
    std::list<Tile> tiles;
signals:
public slots:
};

#endif // GAMECONTAINERWIDGET_H
