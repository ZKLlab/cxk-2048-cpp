#ifndef GAMECONTAINERWIDGET_H
#define GAMECONTAINERWIDGET_H

#include "gamedef.h"
#include "tile.h"
#include <QColor>
#include <QWidget>
#include <QPainter>

class GameContainerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameContainerWidget(QWidget *parent = nullptr);
signals:
public slots:
    void paintEvent(QPaintEvent *) override;
};

#endif // GAMECONTAINERWIDGET_H
