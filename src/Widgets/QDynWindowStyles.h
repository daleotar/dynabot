#ifndef QDYNWINDOWSTYLES_H
#define QDYNWINDOWSTYLES_H

#include <QCleanlooksStyle>
#include <QPlastiqueStyle>
#include <QWindowsVistaStyle>
#include <QWindowsXPStyle>

class QDynStyleCleanlooks : public QCleanlooksStyle
{
    Q_OBJECT

public:

    int pixelMetric(PixelMetric metric, const QStyleOption * option = 0, const QWidget * widget = 0 ) const;
};

class QDynStylePlastique : public QPlastiqueStyle
{
    Q_OBJECT

public:

    int pixelMetric(PixelMetric metric, const QStyleOption * option = 0, const QWidget * widget = 0 ) const;
};

class QDynStyleWindowsVista : public QWindowsVistaStyle
{
    Q_OBJECT

public:

    int pixelMetric(PixelMetric metric, const QStyleOption * option = 0, const QWidget * widget = 0 ) const;
};

class QDynStyleWindowsXP : public QWindowsXPStyle
{
    Q_OBJECT

public:

    int pixelMetric(PixelMetric metric, const QStyleOption * option = 0, const QWidget * widget = 0 ) const;
};

#endif // QDYNWINDOWSTYLES_H
