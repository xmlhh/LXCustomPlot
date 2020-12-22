#include "LDrawSpectrum.h"
#include <QVBoxLayout>

const QString strName = "性能测试";

LDrawSpectrum::LDrawSpectrum(QWidget *parent)
    : QWidget(parent)
{
    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowMinMaxButtonsHint;
    flags |= Qt::WindowCloseButtonHint;
    setWindowFlags(flags);
    setWindowTitle("QCustomplot " + strName);

    m_customPlot = new LXCustomPlot();
    m_customPlot->showTracer(false);

    // add title layout element:
    m_customPlot->plotLayout()->insertRow(0);
    m_customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(m_customPlot, strName + " (10条动态曲线)", QFont("微软雅黑", 12, QFont::Bold)));

    m_customPlot->legend->setVisible(true);
    QFont legendFont = font();  // start out with MainWindow's font..
    legendFont.setPointSize(9); // and make a bit smaller for legend
    m_customPlot->legend->setFont(legendFont);
    m_customPlot->legend->setBrush(QBrush(QColor(255, 255, 255, 230)));
    // by default, the legend is in the inset layout of the main axis rect. So this is how we access it to change legend placement:
    m_customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop | Qt::AlignRight);

    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(m_customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), m_customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(m_customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), m_customPlot->yAxis2, SLOT(setRange(QCPRange)));

    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    m_customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    QList<QColor> colors;
    colors << QColor(29, 0, 255) << QColor(100, 255, 0) << QColor(255, 106, 227) << QColor(29, 255, 227) << QColor(255, 255, 0)
            << QColor(200, 106, 20) << QColor(255, 255, 255) << QColor(29, 255, 255) << QColor(255, 255, 0) << QColor(29, 106, 255);

    for (auto index = 0; index < colors.size(); ++index) {
        QCPGraph *pGraph = m_customPlot->addGraph();
        pGraph->setName(QString("曲线%1").arg(index + 1));
        pGraph->setPen(QPen(colors[index]));
        m_pGraphs.append(pGraph);
    }

    // give the axes some labels:
    m_customPlot->xAxis->setLabel("x");
    m_customPlot->yAxis->setLabel("y");

    // set axes ranges, so we see all data:
    m_customPlot->xAxis->setRange(0, 40000);
    m_customPlot->yAxis->setRange(-150, 150);
//    m_customPlot->rescaleAxes(true);

    m_customPlot->replot();

    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->addWidget(m_customPlot);
    setLayout(pLayout);
//    showMaximized();
    resize(QSize(1000, 600));

    connect(&m_pUpdateTimer, SIGNAL(timeout()), this, SLOT(update()));
    m_pUpdateTimer.start(5);
}

LDrawSpectrum::~LDrawSpectrum()
{

}

void LDrawSpectrum::update()
{
    int nCount = 10000;
    QList<QVector<double>> yAlis;
    QVector<double> x(nCount), y1(nCount), y2(nCount), y3(nCount), y4(nCount), y5(nCount),
            y6(nCount), y7(nCount), y8(nCount), y9(nCount), y10(nCount); // initialize with entries 0..100
    yAlis << y1 << y2 << y3 << y4 << y5 << y6 << y7 << y8 << y9 << y10;

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

    for (auto index = 0; index < m_pGraphs.size(); ++index) {
        m_pGraphs[index]->data().data()->clear();
        m_pGraphs[index]->addData(x, yAlis[index]);
    }

//    m_customPlot->replot();
    m_customPlot->replot(QCustomPlot::rpQueuedReplot);
}
