#include "LDrawSpectrum.h"
#include <QVBoxLayout>

#ifndef __ONEPLOT__
    #define __ONEPLOT__
#elif !defined __TWOPLOT__
    #define __TWOPLOT__
#elif !defined __FORPLOT__
    #define __FORPLOT__
#elif !defined __SIXPLOT__
    #define __SIXPLOT__
#elif !defined __TENPLOT__
    #define __TENPLOT__
#endif

const QString strName = "性能测试";

LDrawSpectrum::LDrawSpectrum(QWidget *parent)
    : QWidget(parent)
{
    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowMinMaxButtonsHint;
    flags |= Qt::WindowCloseButtonHint;
    setWindowFlags(flags);
    setWindowTitle("QCustomplot " + strName);

    m_pCustomPlot = new LXCustomPlot();
    m_pCustomPlot->showTracer(false);

    // add title layout element:
    m_pCustomPlot->plotLayout()->insertRow(0);
    m_pCustomPlot->plotLayout()->addElement(0, 0, new QCPTextElement(m_pCustomPlot, strName + " (多条动态曲线)", QFont("微软雅黑", 12, QFont::Bold)));

    m_pCustomPlot->legend->setVisible(true);
    QFont legendFont = font();  // start out with MainWindow's font..
    legendFont.setPointSize(9); // and make a bit smaller for legend
    m_pCustomPlot->legend->setFont(legendFont);
    m_pCustomPlot->legend->setBrush(QBrush(QColor(255, 255, 255, 230)));
    // by default, the legend is in the inset layout of the main axis rect. So this is how we access it to change legend placement:
    m_pCustomPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop | Qt::AlignRight);

    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(m_pCustomPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), m_pCustomPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(m_pCustomPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), m_pCustomPlot->yAxis2, SLOT(setRange(QCPRange)));

    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    m_pCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    QList<QColor> colors;
#ifdef __ONEPLOT__
    colors << QColor(255, 255, 0);
#elif defined __TWOPLOT__
    colors << QColor(29, 255, 227) << QColor(255, 255, 0);
#elif defined __FORPLOT__
    colors << QColor(29, 0, 255) << QColor(100, 255, 0)
           << QColor(255, 106, 227) << QColor(29, 255, 227);
#elif defined __SIXPLOT__
    colors << QColor(29, 0, 255) << QColor(100, 255, 0)
           << QColor(255, 106, 227) << QColor(29, 255, 227)
           << QColor(255, 255, 0) << QColor(200, 106, 20);
#elif defined __TENPLOT__
    colors << QColor(29, 0, 255) << QColor(100, 255, 0) << QColor(255, 106, 227) << QColor(29, 255, 227) << QColor(255, 255, 0)
            << QColor(200, 106, 20) << QColor(255, 255, 255) << QColor(29, 255, 255) << QColor(255, 255, 0) << QColor(29, 106, 255);
#endif

    for (auto index = 0; index < colors.size(); ++index) {
        QCPGraph *pGraph = m_pCustomPlot->addGraph();
        pGraph->setName(QString("曲线%1").arg(index + 1));
        pGraph->setPen(QPen(colors[index]));
    }

    // give the axes some labels:
    m_pCustomPlot->xAxis->setLabel("x");
    m_pCustomPlot->yAxis->setLabel("y");

    // set axes ranges, so we see all data:
    m_pCustomPlot->xAxis->setRange(0, 40000);
    m_pCustomPlot->yAxis->setRange(-150, 150);
//    m_pCustomPlot->rescaleAxes(true);

    m_pCustomPlot->replot();

    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->addWidget(m_pCustomPlot);
    setLayout(pLayout);
//    showMaximized();
    resize(QSize(1000, 600));

    connect(&m_pUpdateTimer, SIGNAL(timeout()), this, SLOT(update()));
    m_pUpdateTimer.start(30);
}

LDrawSpectrum::~LDrawSpectrum()
{

}

void LDrawSpectrum::update()
{
    int nCount = 10000;
    QList<QVector<double>> yAlis;

#ifdef __ONEPLOT__
    QVector<double> x(nCount), y1(nCount);
    yAlis << y1;
#elif defined __TWOPLOT__
    QVector<double> x(nCount), y1(nCount), y2(nCount);
    yAlis << y1 << y2;
#elif defined __FORPLOT__
    QVector<double> x(nCount), y1(nCount), y2(nCount), y3(nCount), y4(nCount);
    yAlis << y1 << y2 << y3 << y4;
#elif defined __SIXPLOT__
    QVector<double> x(nCount), y1(nCount), y2(nCount), y3(nCount), y4(nCount), y5(nCount), y6(nCount);
    yAlis << y1 << y2 << y3 << y4 << y5 << y6;
#elif defined __TENPLOT__
    QVector<double> x(nCount), y1(nCount), y2(nCount), y3(nCount), y4(nCount), y5(nCount),
            y6(nCount), y7(nCount), y8(nCount), y9(nCount), y10(nCount); // initialize with entries 0..100
    yAlis << y1 << y2 << y3 << y4 << y5 << y6 << y7 << y8 << y9 << y10;
#endif

    for (auto index = 0; index < yAlis.size(); ++index) {
        for (int i = 0; i < nCount; ++i)
        {
            x[i] = i*4; // X轴

            double data = 0.0;
            if (index % 2 == 0) {
                 data = cos(i);
            } else {
                data = sin(i);
            }
            yAlis[index][i] = (qrand() % (100 - index * 10) + 1) * data; // Y轴
        }
    }

    for (auto index = 0; index < m_pCustomPlot->graphCount(); ++index) {
        if (index >= yAlis.size()) {
            continue;
        }
        m_pCustomPlot->graph(index)->data().data()->clear();
        m_pCustomPlot->graph(index)->addData(x, yAlis[index]);
    }

//    m_pCustomPlot->replot();
    m_pCustomPlot->replot(QCustomPlot::rpQueuedReplot);
}
