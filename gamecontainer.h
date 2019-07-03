#ifndef GAMECONTAINERWIDGET_H
#define GAMECONTAINERWIDGET_H

#include "gamedef.h"
#include "tile.h"
#include <list>
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
    void getTilesMatrix();
private:
    int score;
    std::list<Tile> tiles;
signals:
public slots:
};

#endif // GAMECONTAINERWIDGET_H
