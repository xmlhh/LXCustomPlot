#ifndef XCUSTOMPLOT_H
#define XCUSTOMPLOT_H

#include "LXTracer.h"
#include "qcustomplot.h"
#include <QObject>
#include <QList>


class LXCustomPlot: public QCustomPlot
{
    Q_OBJECT

public:
    LXCustomPlot(QWidget *parent = 0);

protected:
    virtual void mouseMoveEvent(QMouseEvent *event);

public:
    ///
    /// \brief 设置是否显示鼠标追踪器
    /// \param show:是否显示
    ///
    void showTracer(bool show)
    {
        m_isShowTracer = show;
        if(m_xTracer)
        {
            m_xTracer->setVisible(m_isShowTracer);
        }
        foreach (LXTracer *tracer, m_dataTracers)
        {
            if(tracer)
            {
                tracer->setVisible(m_isShowTracer);
            }
        }
        if(m_lineTracer)
        {
            m_lineTracer->setVisible(m_isShowTracer);
        }
    }

    ///
    /// \brief 是否显示鼠标追踪器
    /// \return
    ///
    bool isShowTracer()
    {
        return m_isShowTracer;
    };

private:
    bool m_isShowTracer;//是否显示追踪器（鼠标在图中移动，显示对应的值）
    LXTracer *m_xTracer;//x轴
    LXTracer *m_yTracer;//y轴
    QList<LXTracer *> m_dataTracers;//
    LXTraceLine  *m_lineTracer;//直线
};

#endif // XCUSTOMPLOT_H
