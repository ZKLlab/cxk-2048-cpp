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
private:
    int score;
    std::list<Tile> tiles;
public:
    explicit GameContainer(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *) override;
signals:
public slots:
};

#endif // GAMECONTAINERWIDGET_H
