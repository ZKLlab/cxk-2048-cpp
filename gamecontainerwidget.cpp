#include "gamecontainerwidget.h"

GameContainerWidget::GameContainerWidget(QWidget *parent) : QWidget(parent)
{

}

void GameContainerWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    // 绘制背景
    painter.setBrush(QColor("#bbada0"));
    painter.drawRoundedRect(0, 0, CONTAINER_WIDTH, CONTAINER_WIDTH, 6, 6);
    // 绘制格子
    painter.setBrush(QColor(238, 228, 218, 90));
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            painter.drawRoundedRect(j * TILE_WIDTH + (j + 1) * GUTTER_WIDTH, i * TILE_WIDTH + (i + 1) * GUTTER_WIDTH,
                                    TILE_WIDTH, TILE_WIDTH,
                                    3, 3);
        }
    }
    // 绘制方块（测试）
    int value = 2;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Tile tempTile(value, i, j);

            // 绘制背景
            painter.setPen(Qt::NoPen);
            painter.setBrush(QColor(tempTile.getBackgroundColor().c_str()));

            painter.drawRoundedRect(tempTile.getX(), tempTile.getY(),
                                    TILE_WIDTH, TILE_WIDTH,
                                    3, 3);

            // 绘制前景
            painter.setPen(QColor(tempTile.getForeColor().c_str()));

            // 值
            QFont font = painter.font();
            font.setPixelSize(TILE_VALUE_SIZE);
            painter.setFont(font);

            painter.drawText(QRect(tempTile.getX() + TILE_VALUE_MARGIN, tempTile.getY() + TILE_VALUE_MARGIN,
                                   TILE_WIDTH - 2 * TILE_VALUE_MARGIN, TILE_WIDTH - 2 * TILE_VALUE_MARGIN),
                             tempTile.getValueText().c_str());

            // 文本
            font.setPixelSize(tempTile.getFontPixelSize());
            painter.setFont(font);

            painter.drawText(QRect(tempTile.getX(), tempTile.getY(), TILE_WIDTH, TILE_WIDTH),
                             Qt::AlignCenter,
                             tempTile.getText().c_str());

            value *= 2;
        }
    }
}
