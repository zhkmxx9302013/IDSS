#include "ttktempmeterwidget.h"

#include <QTimer>
#include <QPainter>

#define S_LONG      3//10
#define S_SPAOK     8 //7
#define S_SHORT     5
#define S_SPACE     3

TTKTempMeterWidget::TTKTempMeterWidget(QWidget *parent)
    : QWidget(parent)
{
    initVariables();
}

void TTKTempMeterWidget::setValue(qreal value)
{
    if(value == m_value)
    {
        return;
    }

    m_bReverse = (value < m_value);
    m_value = value/(m_ratio * 10);
    if(!m_bAnimating)
    {
        m_currentValue = m_value;
    }
    m_updateTimer->start();
}

void TTKTempMeterWidget::setRatio(qreal value)
{
    m_ratio = value;
}

void TTKTempMeterWidget::setAnimating(bool enable)
{
    m_bAnimating = enable;
    update();
}

void TTKTempMeterWidget::updateGraph()
{
    if(m_bReverse)
    {
        m_currentValue -= 0.5;
        if(m_currentValue <= m_value)
        {
            m_updateTimer->stop();
        }
    }
    else
    {
        m_currentValue += 0.5;
        if(m_currentValue >= m_value)
        {
            m_updateTimer->stop();
        }
    }
    update();
}

void TTKTempMeterWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);
    resetVariables();
    drawOuterCircle(&painter);
    drawInnerCircle(&painter);
    drawColorPie(&painter);
    drawCoverCircle(&painter);
    drawMark(&painter);
    drawIndicator(&painter);
    drawCoverBall(&painter);
    drawTextRect(&painter);
    painter.end();
}

//QSize TTKSpeedMeterWidget::sizeHint() const
//{
//    return QSize(300, 300);
//}

//QSize TTKSpeedMeterWidget::minimumSizeHint() const
//{
//    return QSize(200, 200);
//}

void TTKTempMeterWidget::initVariables()
{
    resetVariables();

    m_value = 0;
    m_currentValue = 0;
    m_ratio = 0.1;
    m_units = "℃x10";

    m_updateTimer = new QTimer(this);
    m_updateTimer->setInterval(10);
    connect(m_updateTimer, SIGNAL(timeout()), SLOT(updateGraph()));
    m_singleTimer = new QTimer(this);
    m_singleTimer->setInterval(100);
    connect(m_singleTimer, SIGNAL(timeout()), SLOT(update()));
    m_singleTimer->start();
}

void TTKTempMeterWidget::resetVariables()
{
    m_outerRadius = width()>height() ? height()/2 : width()/2;
    m_innerRadius = m_outerRadius/8*7;
    m_coverCircleRadius = m_outerRadius/8*4 + 10;
    m_colorCircleRadius = m_outerRadius/8*5;
    m_center = rect().center();
}

void TTKTempMeterWidget::drawOuterCircle(QPainter *painter)
{
    painter->save();

    QRadialGradient outerGradient(m_center,  m_outerRadius, m_center);
    outerGradient.setColorAt(0.0, QColor(200, 200, 200));
    outerGradient.setColorAt(0.9, QColor(80, 80, 80));
    outerGradient.setColorAt(0.95, QColor(180, 180, 180));
    outerGradient.setColorAt(1.0, QColor(80, 80, 80));

    painter->setPen(Qt::NoPen);
    painter->setBrush(outerGradient);
    painter->drawEllipse(m_center, m_outerRadius, m_outerRadius);
    painter->restore();
}

void TTKTempMeterWidget::drawInnerCircle(QPainter *painter)
{
    painter->save();
    QRadialGradient innerGradient(m_center, m_innerRadius, m_center);
    innerGradient.setColorAt(0.0, QColor(90, 90, 90));
    innerGradient.setColorAt(0.7, QColor(90, 90, 90));
    innerGradient.setColorAt(1.0, QColor(80, 80, 80));
    painter->setPen(Qt::NoPen);
    painter->setBrush(innerGradient);
    painter->drawEllipse(m_center, m_innerRadius, m_innerRadius);

    painter->restore();
}

void TTKTempMeterWidget::drawMark(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::white);
    painter->translate(m_center);

    qreal dAngle=(qreal)270/140;  // 270
    qreal startAngle = 225;        // 45
    int value = 0;
    QString strValue;

    //Custom by zhaozihe @2018-11-28 10:51:47
    for(int i=0; i<=140; i++)
    {
        painter->save();
        painter->rotate(startAngle);
        if(i%10 == 0)
        {
            strValue = QString::number(value);
            qreal textWidth = fontMetrics().width(strValue);
            qreal textHeight = fontMetrics().height();
            QPointF bottomPot(0, m_colorCircleRadius + S_SPACE);
            QPointF topPot(0, m_colorCircleRadius + S_SPACE + S_SPAOK);
            QPen pen;
            pen.setColor(Qt::white);
            pen.setWidth(3);
            painter->setPen(pen);
            painter->drawLine(bottomPot, topPot);
            value += 10*m_ratio;

            painter->save();

            QFont font;
            qreal fontSize = S_SPAOK / 8.0 * 10.0;
            font.setPointSize(fontSize);
            font.setBold(true);
            font.setFamily("Arial");
            painter->setFont(font);
            QPointF textPot(0 - textWidth/2, m_colorCircleRadius + S_SPACE + S_LONG + S_SPACE + textHeight);
            painter->translate(textPot);
            painter->rotate(180);
            painter->drawText(QPointF(-textWidth, textHeight/2), strValue);
            painter->restore();
        }
        else if(i%5 == 0)
        {

            QPointF bottomPot(0, m_colorCircleRadius + S_SPACE);
            QPointF topPot(0, m_colorCircleRadius + S_SPACE + S_SHORT * 1.5);
            QPen pen;
            pen.setColor(Qt::white);
            pen.setWidth(1.5);
            painter->setPen(pen);
            painter->drawLine(bottomPot, topPot);
//            painter->restore();

        }
        else
        {

        }
        painter->restore();
        startAngle += dAngle;
    }

    painter->restore();
}

void TTKTempMeterWidget::drawCoverBall(QPainter *painter)
{
    painter->save();

    qreal ballRadius = m_outerRadius/7;
    m_coverBallRadius = ballRadius;
    QRadialGradient ballGradient(m_center, ballRadius, m_center);
    ballGradient.setColorAt(0.0, QColor(140, 140, 140));
    ballGradient.setColorAt(0.7, QColor(140, 140, 140));
    ballGradient.setColorAt(1.0, QColor(60, 60, 60));
    painter->setBrush(ballGradient);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(m_center, ballRadius, ballRadius);

    painter->restore();
}

void TTKTempMeterWidget::drawTextRect(QPainter *painter)
{
    painter->save();
    qreal rectWidth = m_coverCircleRadius/5;

    QPointF topLeftPot(m_center.x() -2.5*rectWidth, m_center.y() + rectWidth*2);
    QPointF bottomRightPot(topLeftPot.x()+5*rectWidth, topLeftPot.y()+rectWidth*2);
    QRectF textRect(topLeftPot, bottomRightPot);

    qreal fontSize = textRect.height()/2.53;
    QFont font;
    font.setPointSize(fontSize);
    font.setBold(true);
    font.setFamily("Arial");
    painter->setFont(font);
    painter->setOpacity(1.0);
    painter->setPen(Qt::white);

    painter->drawText(textRect, Qt::AlignCenter, QString("%1\n").arg(m_units));


    QPointF valTopLeftPot(m_center.x() -2.5*rectWidth, m_center.y() - rectWidth*3.4);
    QPointF valBottomRightPot(valTopLeftPot.x()+5*rectWidth, valTopLeftPot.y()+rectWidth*2);
    QRectF valTextRect(valTopLeftPot, valBottomRightPot);
    fontSize = textRect.height()/2.0;
    font.setPointSize(fontSize);
    painter->setFont(font);
    painter->drawText(valTextRect, Qt::AlignCenter, QString("%1").arg(m_value));
    painter->restore();
}

void TTKTempMeterWidget::drawCoverCircle(QPainter *painter)
{
    painter->save();
    painter->setBrush(QColor(90, 90, 90));
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(m_center, m_coverCircleRadius, m_coverCircleRadius);
    painter->restore();
}

void TTKTempMeterWidget::drawColorPie(QPainter *painter)
{
    painter->save();
    QPen pen;
    pen.setWidth(3);
    QPointF topLeftPot(m_center.x() - m_colorCircleRadius, m_center.y() - m_colorCircleRadius);
    QPointF bottomRightPot(m_center.x() + m_colorCircleRadius, m_center.y() + m_colorCircleRadius);
    m_colorCircleRect = QRectF(topLeftPot, bottomRightPot);
    painter->setPen(Qt::NoPen);
    //Custom by zhaozihe @2018-11-28 10:51:47
    // Invert factor
    int invertFactor = - 180 *16;
    QConicalGradient greenGradient(m_center, m_innerRadius);
    greenGradient.setColorAt(0.0, QColor(0, 30, 0));
    greenGradient.setColorAt(0.25, QColor(0, 230, 0));
    greenGradient.setColorAt(1.0, QColor(0, 230, 0));
    pen.setColor(Qt::green);
    painter->setPen(pen);
    painter->drawPie(m_colorCircleRect, 45*16 + invertFactor, 180*16);

    pen.setColor(QColor(218, 218, 0));
    painter->setPen(pen);
    painter->drawPie(m_colorCircleRect, 0*16 + invertFactor, 45*16 );

    pen.setColor(QColor(240, 50, 50));
    painter->setPen(pen);
    painter->drawPie(m_colorCircleRect, 0 + invertFactor, -45*16 );

    painter->restore();
}

void TTKTempMeterWidget::drawIndicator(QPainter *painter)
{
    painter->save();

    painter->translate(m_center);
    qreal increment = (qreal)270/140;
    qreal changedAngle = -135 + increment*m_currentValue;
    painter->rotate(changedAngle);

    QPointF topPot(0, m_colorCircleRadius + S_LONG);
    QPointF bottomLeftPot(-m_coverBallRadius/3, 0);
    QPointF bottomRightPot(m_coverBallRadius/3, 0);
    painter->setPen(Qt::NoPen);

    QLinearGradient indicatorGradient(topPot, bottomLeftPot);
    indicatorGradient.setColorAt(0.0, QColor(236, 187, 62));
    indicatorGradient.setColorAt(0.5, QColor(220, 147, 0));
    indicatorGradient.setColorAt(1.0, QColor(236, 187, 62));

    painter->setBrush(indicatorGradient);
    QVector<QPointF> potVec;
    potVec.push_back(topPot);
    potVec.push_back(bottomLeftPot);
    potVec.push_back(bottomRightPot);

    painter->drawPolygon(potVec);
    painter->restore();
}
