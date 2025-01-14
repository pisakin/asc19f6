#include "casc19f6gc.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "aPKF/gc.c"
#include "aPKF/rocket.c"
#include "aPKF/torque.c"
#include "aPKF/utils.c"

#ifdef __cplusplus
}
#endif

/*
 *
 */
CASC19F6GC::CASC19F6GC(QWidget *parent) : QFrame(parent)
{
//  Установка параметров окна
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle(QString::fromUtf8("ascEMPlot"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    if (objectName().isEmpty()) setObjectName(QString::fromUtf8("ascEMPlot"));
    if (accessibleName().isEmpty()) setAccessibleName("ascEMPlot");
    if (accessibleDescription().isEmpty()) setAccessibleDescription("ascEMPlot");
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(true);
    setSizePolicy(sizePolicy);
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Raised);
//
    initInterface();
//
    createInterface();
//
    QTimer::singleShot(500, this, SLOT(refreshData()));
}

/*
 *
 */
CASC19F6GC::~CASC19F6GC()
{

}

/*
 *
 */
void CASC19F6GC::showEvent(QShowEvent *e)
{
    if (!e->spontaneous() && !init)
    {
        //  Отображение первоначальных параметров
        refreshView();
        //
        timerId = startTimer(500);
        init = true;
        countTimer = 0;
    }

}

void CASC19F6GC::timerEvent(QTimerEvent *e)
{
    if (e->timerId() == timerId) {
        ++countTimer;
        refreshView();
    } else {
        QObject::timerEvent(e);
    }
}

QCustomPlot *CASC19F6GC::createPlot()
{
    customPlot = new QCustomPlot();
    //
    customPlot->setAutoFillBackground(true);
    customPlot->setObjectName("customPlot");
    customPlot->setAccessibleName("customPlot");
    customPlot->setAccessibleDescription("customPlot");
    //  connect(customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(procMousePress(QMouseEvent*)));
    //  connect(customPlot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(procMouseMove(QMouseEvent*)));
    //  Луч 1
    xAxis = customPlot->xAxis;
    xGrid = xAxis->grid();
    xAxis->setLabel("x");
    xAxis->setRange(0, 100);

    yAxis = customPlot->yAxis;
    yGrid = yAxis->grid();
    yAxis->setLabel("y");
    yAxis->setRange(-1, 1);

    graph = customPlot->addGraph(xAxis, yAxis);
    //  graph->setLineStyle(QCPGraph::LineStyle::lsStepCenter);
    penGraph.setColor(QColor(Qt::blue));
    graph->setPen(penGraph);
    //  Луч 2
    xAxis2 = customPlot->xAxis2;
    xGrid2 = xAxis2->grid();
    xAxis2->setLabel("x");
    xAxis2->setRange(0, 100);

    yAxis2 = customPlot->yAxis2;
    yGrid2 = yAxis2->grid();
    yAxis2->setLabel("y");
    yAxis2->setRange(-1, 1);

    graph2 = customPlot->addGraph(xAxis, yAxis2);
    penGraph2.setColor(QColor(Qt::red));
    graph2->setPen(penGraph2);
    //
    customPlot->replot();
    return customPlot;
}

void CASC19F6GC::initInterface()
{
    init = false;
}

void CASC19F6GC::createInterface()
{
    vBoxLayout = new QVBoxLayout();
    vBoxLayout->setContentsMargins(0, 0, 0, 0);
    vBoxLayout->setSpacing(0);
    setLayout(vBoxLayout);

    vBoxLayout->addWidget(createBoxHeader());
    vBoxLayout->addWidget(createBoxGeneral());
    vBoxLayout->addWidget(createBoxFooter());
}

QScrollArea *CASC19F6GC::createScrollArea()
{
    scrollArea = new QScrollArea(this);
    scrollArea->setAutoFillBackground(true);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setWidgetResizable(true);

    layoutScrollArea = new QVBoxLayout();
    layoutScrollArea->setContentsMargins(10, 10, 10, 10);
    layoutScrollArea->setSpacing(10);
    //    layoutScrollArea.a
    //
    widgetScrollArea = new QWidget();
    widgetScrollArea->setLayout(layoutScrollArea);
    scrollArea->setWidget(widgetScrollArea);
    //unsigned short row = 0;
    customPlot = new QCustomPlot();
    customPlot->setAutoFillBackground(true);
    customPlot->addGraph();
    //  customPlot->graph(0)->setData(x, y);
    //
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    //
    countPlot = 10;
    customPlot->xAxis->setRange(0, maxX);
    customPlot->yAxis->setRange(-1, 1);
    customPlot->replot();

    layoutScrollArea->addWidget(customPlot);

    spacerItem = new QSpacerItem(0, 100, QSizePolicy::Expanding, QSizePolicy::Expanding);
    layoutScrollArea->addItem(spacerItem);

    return scrollArea;
}

QGroupBox *CASC19F6GC::createBoxHeader()
{
    groupHeader = new QGroupBox("groupHeader", this);
    groupHeader->setTitle("");
    groupHeader->setMaximumHeight(50);

    layoutHeader = new QHBoxLayout();
    layoutHeader->setContentsMargins(0, 0, 0, 0);
    layoutHeader->setSpacing(0);
    groupHeader->setLayout(layoutHeader);

    lblTitel = new QLabel("Titel", this);
    lblTitel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    lblTitel->setText("Насос");
    QFont font = this->font();
    font.setPixelSize(14);
    font.setBold(true);
    lblTitel->setFont(font);
    layoutHeader->addWidget(lblTitel);

    spacerItemHeader = new QSpacerItem(100, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    layoutHeader->addItem(spacerItemHeader);

    btnSavePNG = new QPushButton("btnSavePNG", this);
    btnSavePNG->setText("Save PNG");
    connect(btnSavePNG, SIGNAL(clicked()), SLOT(procSaveToPNG()));
    layoutHeader->addWidget(btnSavePNG);

    btnSaveCSV = new QPushButton("btnSaveCSV", this);
    btnSaveCSV->setText("Save CSV");
    connect(btnSaveCSV, SIGNAL(clicked()), SLOT(procSaveToCSV()));
    layoutHeader->addWidget(btnSaveCSV);

    btnRefresh = new QPushButton("btnRefresh", this);
    btnRefresh->setText("Refresh");
    connect(btnRefresh, SIGNAL(clicked()), SLOT(procRefresh()));
    //  connect(btnRefresh, SIGNAL(clicked()), SLOT(refreshPlot()));
    layoutHeader->addWidget(btnRefresh);


    return groupHeader;
}

QGroupBox *CASC19F6GC::createBoxGeneral()
{
    groupGeneral = new QGroupBox("groupGeneral",this);
    groupGeneral->setTitle("");
    groupGeneral->setAutoFillBackground(true);

    layoutGeneral = new QVBoxLayout();
    layoutGeneral->setContentsMargins(0, 0, 0, 0);
    layoutGeneral->setSpacing(0);
    groupGeneral->setLayout(layoutGeneral);

    //  layoutGeneral->addWidget(createScrollArea());
    layoutGeneral->addWidget(createPlot());

    return groupGeneral;
}

QGroupBox *CASC19F6GC::createBoxFooter()
{
    groupFooter = new QGroupBox("groupFooter",this);
    groupFooter->setTitle("");
    groupFooter->setMaximumHeight(75);

    layoutFooter = new QHBoxLayout();
    layoutFooter->setContentsMargins(0, 0, 0, 0);
    layoutFooter->setSpacing(0);
    groupFooter->setLayout(layoutFooter);

    return groupFooter;
}

void CASC19F6GC::refreshView()
{

}

void CASC19F6GC::refreshData()
{
    const float Tik = 1e-3;


    const float ampDeg = 1.0;
    const float ampRad = TGR(ampDeg);
    const float freqHz = 0.8;
    const float phase0_rad = 0.0;
    const float TimeReg = 10.0 / freqHz;

    int N = 10;
    float *array = (float*) malloc((N) * sizeof(float));
    for (short i = 0; i<N; ++i) array[i] = 0.0;

    xData.clear(); yData.clear(); yData2.clear();
    for (int i = 1; i< (TimeReg / Tik); ++i) {
        xData.append(i * Tik);
        yData.append(i * Tik);
    }
    free(array);
    //
    refreshPlot();
}

void CASC19F6GC::refreshPlot()
{
    bool rPlot = false;
    double min1 = 0.0, max1 = 0.0;
    double min2 = 0.0, max2 = 0.0;
    // Луч 1
    if ((!xData.isEmpty())&&(!yData.isEmpty())) {
        graph->setData(xData, yData);
        xAxis->setRange(xData.first(), xData.last());
        xAxis2->setRange(xData.first(), xData.last());
        min1 = yData.first(), max1 = yData.first();
        for (int i = 0; i<yData.count(); ++i )
        {
            if (yData.at(i) < min1) min1 = yData.at(i);
            if (yData.at(i) > max1) max1 = yData.at(i);
        }
        yAxis->setRange(min1, max1);
        rPlot = true;
    }
    // Луч 2
    if ((!xData.isEmpty())&&(!yData2.isEmpty())) {
        graph2->setData(xData, yData2);
        xAxis->setRange(xData.first(), xData.last());
        xAxis2->setRange(xData.first(), xData.last());
        min2 = yData2.first(); max2 = yData2.first();
        for (int i = 0; i<yData2.count(); ++i )
        {
            if (yData2.at(i) < min2) min2 = yData2.at(i);
            if (yData2.at(i) > max2) max2 = yData2.at(i);
        }
        yAxis2->setVisible(true);

        yAxis->setRange(-min2, max2);
        yAxis2->setRange(-min2, max2);

        //    yAxis2->setRange(yAxis->range());
        rPlot = true;
    }
    //
    if (rPlot) customPlot->replot();
}

void CASC19F6GC::procRefresh()
{
    refreshPlot();
}

void CASC19F6GC::procCalc()
{

}

void CASC19F6GC::changeFreq(const QString &str)
{
    bool ok = false;
    float value = 0.0f;
    QString s = str;
    s.replace(QStringLiteral(","), QStringLiteral("."));
    value = s.toFloat(&ok);
    if (ok) freq = value;
}

void CASC19F6GC::changePhase(const QString &str)
{
    bool ok = false;
    float value = 0.0f;
    QString s = str;
    s.replace(QStringLiteral(","), QStringLiteral("."));
    value = s.toFloat(&ok);
    if (ok) phase = value;
}

void CASC19F6GC::changeAmp(const QString &str)
{
    bool ok = false;
    float value = 0.0f;
    QString s = str;
    s.replace(QStringLiteral(","), QStringLiteral("."));
    value = s.toFloat(&ok);
    if (ok) amp = value;
}

void CASC19F6GC::changeTime(const QString &str)
{
    bool ok = false;
    float value = 0.0f;
    QString s = str;
    s.replace(QStringLiteral(","), QStringLiteral("."));
    value = s.toFloat(&ok);
    if (ok) timeReg = value;
}

void CASC19F6GC::changeNoise(const QString &str)
{
    bool ok = false;
    float value = 0.0f;
    QString s = str;
    s.replace(QStringLiteral(","), QStringLiteral("."));
    value = s.toFloat(&ok);
    if (ok) noise = value;
}

void CASC19F6GC::changeScaleXPlot(const QString &str)
{
    bool ok = false;
    float value = 0.0f;
    QString s = str;
    s.replace(QStringLiteral(","), QStringLiteral("."));
    value = s.toFloat(&ok);
    if (ok) scaleX = value;
}

void CASC19F6GC::changeScaleYPlot(const QString &str)
{
    bool ok = false;
    float value = 0.0f;
    QString s = str;
    s.replace(QStringLiteral(","), QStringLiteral("."));
    value = s.toFloat(&ok);
    if (ok) scaleY = value;
}

void CASC19F6GC::procMousePress(QMouseEvent *e)
{

}

void CASC19F6GC::procMouseMove(QMouseEvent *e)
{

}

void CASC19F6GC::procSaveToCSV()
{

}

void CASC19F6GC::procSaveToPNG()
{

}
