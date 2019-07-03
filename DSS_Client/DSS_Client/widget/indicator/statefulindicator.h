#ifndef STATEFULINDICATOR_H
#define STATEFULINDICATOR_H

#include <QWidget>
#include "widget/indicator/indicator.h"

class StatefulIndicator : public QWidget
{
public:
    StatefulIndicator(QWidget *parent = 0)
        : QWidget(parent)
    {
        m_green = new LightWidget(Qt::green);
        QPalette pal = palette();
        pal.setColor(QPalette::Background, Qt::black);
        setPalette(pal);
        setAutoFillBackground(true);
    }

    LightWidget *redLight() const
        { return m_red; }
    LightWidget *yellowLight() const
        { return m_yellow; }
    LightWidget *greenLight() const
        { return m_green; }

    QState *createLightState(LightWidget *light, int duration, QState *parent = 0)
    {
        QState *lightState = new QState(parent);
        QTimer *timer = new QTimer(lightState);
        timer->setInterval(duration);
        timer->setSingleShot(true);
        QState *timing = new QState(lightState);
        QObject::connect(timing, SIGNAL(entered()), light, SLOT(turnOn()));
        QObject::connect(timing, SIGNAL(entered()), timer, SLOT(start()));
        QObject::connect(timing, SIGNAL(exited()), light, SLOT(turnOff()));
        QFinalState *done = new QFinalState(lightState);
        timing->addTransition(timer, SIGNAL(timeout()), done);
        lightState->setInitialState(timing);
        return lightState;
    }

private:
    LightWidget *m_red;
    LightWidget *m_yellow;
    LightWidget *m_green;
};
#endif // STATEFULINDICATOR_H
