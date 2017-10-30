#include "QDynWindowStyles.h"

int QDynStyleCleanlooks::pixelMetric(PixelMetric metric, const QStyleOption * option, const QWidget * widget) const
{
    int s = QCleanlooksStyle::pixelMetric(metric, option, widget);

    if (metric == QStyle::PM_SmallIconSize)
    {
    s = 24;
    }

    return s;
}

int QDynStylePlastique::pixelMetric(PixelMetric metric, const QStyleOption * option, const QWidget * widget) const
{
    int s = QPlastiqueStyle::pixelMetric(metric, option, widget);

    if (metric == QStyle::PM_SmallIconSize)
    {
    s = 24;
    }

    return s;
}

int QDynStyleWindowsVista::pixelMetric(PixelMetric metric, const QStyleOption * option, const QWidget * widget) const
{
    int s = QWindowsVistaStyle::pixelMetric(metric, option, widget);

    if (metric == QStyle::PM_SmallIconSize)
    {
    s = 24;
    }

    return s;
}

int QDynStyleWindowsXP::pixelMetric(PixelMetric metric, const QStyleOption * option, const QWidget * widget) const
{
    int s = QWindowsXPStyle::pixelMetric(metric, option, widget);

    if (metric == QStyle::PM_SmallIconSize)
    {
    s = 24;
    }

    return s;
}
