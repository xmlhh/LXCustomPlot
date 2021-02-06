#ifndef DIALOG_H
#define DIALOG_H

#include <QWidget>
#include "LXCustomPlot.h"

class LDrawSpectrum : public QWidget
{
    Q_OBJECT

public:
    LDrawSpectrum(QWidget *parent = 0);
    ~LDrawSpectrum();

protected:
    LXCustomPlot *m_pCustomPlot;
    QTimer m_pUpdateTimer;

private slots:
    void update();
};

#endif // DIALOG_H
