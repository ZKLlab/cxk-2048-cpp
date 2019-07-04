#include "tile.h"

static int currentIndex = 0;

Tile::Tile(int value, int row, int col) :
    index(currentIndex++),
    value(value),
    i(row),
    j(col),
    scale(0),
    posAnimation(nullptr)
{
    // 移至底层
    lower();
    // 淡入效果
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(parent());
    setGraphicsEffect(effect);
    QPropertyAnimation *fadeInAnimation = new QPropertyAnimation(effect, "opacity");
    fadeInAnimation->setDuration(2 * ANIMATION_DURATION_BASE);
    fadeInAnimation->setStartValue(0);
    fadeInAnimation->setEndValue(1);
    fadeInAnimation->setEasingCurve(QEasingCurve::InOutSine);
    fadeInAnimation->start(QPropertyAnimation::DeleteWhenStopped);
    // 缩放效果
    posAnimation = new ScaleAnimation(false, scale, this, "geometry");
    posAnimation->setDuration(2 * ANIMATION_DURATION_BASE);
    posAnimation->setStartValue(QRect(getX() + TILE_WIDTH / 2, getY() + TILE_WIDTH / 2, 0, 0));
    posAnimation->setEndValue(QRect(getX(), getY(), TILE_WIDTH, TILE_WIDTH));
    posAnimation->setEasingCurve(QEasingCurve::InOutSine);
    posAnimation->start();
}

int Tile::getX() const
{
    return j * TILE_WIDTH + (j + 1) * GUTTER_WIDTH;
}

int Tile::getY() const
{
    return i * TILE_WIDTH + (i + 1) * GUTTER_WIDTH;
}

void Tile::moveTo(int row, int col)
{
    delete posAnimation;
    posAnimation = new ScaleAnimation(false, scale, this, "geometry");
    posAnimation->setDuration(ANIMATION_DURATION_BASE);
    posAnimation->setStartValue(QRect(getX(), getY(), TILE_WIDTH, TILE_WIDTH));
    i = row;
    j = col;
    posAnimation->setEndValue(QRect(getX(), getY(), TILE_WIDTH, TILE_WIDTH));
    posAnimation->setEasingCurve(QEasingCurve::InOutSine);
    posAnimation->start();
}

void Tile::moveToAndDoubleValue(int row, int col)
{
    doubleValue();
    delete posAnimation;
    update();
    posAnimation = new ScaleAnimation(true, scale, this, "geometry");
    posAnimation->setDuration(2 * ANIMATION_DURATION_BASE);
    posAnimation->setStartValue(QRect(getX(), getY(), TILE_WIDTH, TILE_WIDTH));
    i = row;
    j = col;
    posAnimation->setKeyValueAt(0.5, QRect(getX(), getY(), TILE_WIDTH, TILE_WIDTH));
    posAnimation->setKeyValueAt(0.75, QRectF(getX() - 0.1 * TILE_WIDTH, getY() - 0.1 * TILE_WIDTH,
                                             1.2 * TILE_WIDTH, 1.2 * TILE_WIDTH));
    posAnimation->setEndValue(QRect(getX(), getY(), TILE_WIDTH, TILE_WIDTH));
    posAnimation->setEasingCurve(QEasingCurve::InOutSine);
    posAnimation->start();
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

void Tile::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.scale(scale, scale);
    // 绘制背景
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(getBackgroundColor().c_str()));
    painter.drawRoundedRect(0, 0, TILE_WIDTH, TILE_WIDTH, 3, 3);
    // 绘制前景
    painter.setPen(QColor(getForeColor().c_str()));
    // 值
    QFont font = painter.font();
    font.setPixelSize(TILE_VALUE_SIZE);
    painter.setFont(font);
    painter.drawText(QRect(TILE_VALUE_MARGIN_LEFT, TILE_VALUE_MARGIN_TOP,
                           TILE_WIDTH - 2 * TILE_VALUE_MARGIN_LEFT, TILE_WIDTH - 2 * TILE_VALUE_MARGIN_TOP),
                     getValueText().c_str());
    // 文本
    font.setPixelSize(getFontPixelSize());
    painter.setFont(font);
    painter.drawText(QRect(0, 0, TILE_WIDTH, TILE_WIDTH), Qt::AlignCenter, getText().c_str());
}

void Tile::doubleValue()
{
    value *= 2;
    raise(); // 移至顶层
}

int Tile::getRow() const
{
    return i;
}

int Tile::getCol() const
{
    return j;
}

int Tile::getValue() const
{
    return value;
}

Tile::~Tile()
{
    delete posAnimation;
}

void ScaleAnimation::updateCurrentValue(const QVariant &value)
{
    scale = double(value.toRectF().width()) / TILE_WIDTH;
    static_cast<QWidget *>(targetObject())->setGeometry(value.toRect());
    static_cast<QWidget *>(targetObject())->update();
}
