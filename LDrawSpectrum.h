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
    LXCustomPlot *m_customPlot;

    QTimer m_pUpdateTimer;
    QList<QCPGraph *> m_pGraphs;

private slots:
    void update();
};

#endif // DIALOG_H
