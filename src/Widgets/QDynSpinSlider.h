#ifndef QDYNSPINSLIDER_H
#define QDYNSPINSLIDER_H

#include <QWidget>
#include <QDoubleSpinBox>
#include <QScrollBar>
#include <math.h>

class QDynSpinSlider : public QWidget
{
    Q_OBJECT

public:

    QDynSpinSlider(QWidget *parent = 0);
    ~QDynSpinSlider();

    double value;
    double min;
    double max;
    double singleStep;
    double pageStep;

    bool invertedSlide;

    void setRange(double minValue, double maxValue);
    void setDecimals(int decValue);
    void setSuffix(QString suffix);
    void setSingleStep(double stepValue);
    void setPageStep(double stepValue);
    void setInvertedSlide(bool inv);

    QDoubleSpinBox *spinBox;
    QScrollBar *slider;

    void adjustAllSizes(QRect rect);

signals:
    void valueChanged(double newValue);

public slots:
    void setValue(double newValue);

protected slots:
    void setValueFromSpin(double spinValue);
    void setValueFromSlide(int slideValue);
};

#endif // QDYNSPINSLIDER_H
