
#ifndef INDICATOR_H
#define INDICATOR_H
#include <QtWidgets>

class LightWidget : public QWidget
{
    Q_OBJECT
//    Q_PROPERTY(bool on READ isOn WRITE setOn)
public:
    LightWidget(const QColor &color, QWidget *parent = 0)
        : QWidget(parent), m_color(color), m_on(false) {}

    bool isOn() const
        { return m_on; }
    void setOn(bool on)
    {
        if (on == m_on)
            return;
        m_on = on;
        update();
    }
    void setColor(const QColor &color)
    {
        m_color = color;
        update();
    }
public slots:
    void turnOff() { setOn(false); }
    void turnOn() { setOn(true); }

protected:
    void paintEvent(QPaintEvent *) override
    {
        if (!m_on)
            return;
        QPainter painter(this);
        int width = 10;
        int height = 10;
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(m_color);
        painter.drawEllipse(0, 0, width, height);
    }

private:
    QColor m_color;
    bool m_on;
};

#endif // INDICATOR_H
