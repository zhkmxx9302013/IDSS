#ifndef TTKALTITUDEMETERWIDGET_H
#define TTKALTITUDEMETERWIDGET_H


#include <QWidget>
#include "ttkglobaldefine.h"

/*!
* @author Greedysky <greedysky@163.com>
*/
class TTK_EXTRAS_EXPORT TTKAltitudeMeterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TTKAltitudeMeterWidget(QWidget *parent = 0);
    void setAltType(const int type); //设置高度类型
    void setValue(qreal value);
    qreal value() const { return m_value;}

    void setRatio(qreal value);
    qreal ratio() const { return m_ratio;}

    void setAnimating(bool enable);
    bool isAnimating() const { return m_bAnimating;}

private Q_SLOTS:
    void updateGraph();

protected:
    virtual void paintEvent(QPaintEvent *event) override;
//    QSize sizeHint() const;
//    QSize minimumSizeHint() const;

private:
    void initVariables();
    void resetVariables();
    void drawOuterCircle(QPainter *painter);
    void drawInnerCircle(QPainter *painter);
    void drawMark(QPainter *painter);
    void drawCoverCircle(QPainter *painter);
    void drawColorPie(QPainter *painter);
    void drawIndicator(QPainter *painter);
    void drawCoverBall(QPainter *painter);
    void drawTextRect(QPainter *painter);

    qreal m_outerRadius, m_innerRadius;
    qreal m_coverCircleRadius, m_colorCircleRadius;
    qreal m_coverBallRadius;
    QPointF m_center;
    QString m_units;
    QRectF m_colorCircleRect;
    qreal m_value, m_ratio, m_currentValue, m_gaugeValue;
    QTimer *m_updateTimer, *m_singleTimer;
    bool m_bReverse, m_bAnimating;

    int m_altType;

};

#endif // TTKALTITUDEMETERWIDGET_H
