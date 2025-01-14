#include "casc19f6torque.h"

CASC19F6Torque::CASC19F6Torque(QWidget *parent) : QFrame(parent)
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

CASC19F6Torque::~CASC19F6Torque()
{

}

void CASC19F6Torque::showEvent(QShowEvent *e)
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

void CASC19F6Torque::timerEvent(QTimerEvent *e)
{
    if (e->timerId() == timerId) {
        ++countTimer;
        refreshView();
    } else {
        QObject::timerEvent(e);
    }
}

QCustomPlot *CASC19F6Torque::createPlot()
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

    graph2 = customPlot->addGraph(xAxis2, yAxis2);
    penGraph2.setColor(QColor(Qt::red));
    graph2->setPen(penGraph2);
    //
    customPlot->replot();
    return customPlot;
}

void CASC19F6Torque::initInterface()
{
    init = false;
}

void CASC19F6Torque::createInterface()
{
    vBoxLayout = new QVBoxLayout();
    vBoxLayout->setContentsMargins(0, 0, 0, 0);
    vBoxLayout->setSpacing(0);
    setLayout(vBoxLayout);

    vBoxLayout->addWidget(createBoxHeader());
    vBoxLayout->addWidget(createBoxGeneral());
    vBoxLayout->addWidget(createBoxFooter());
}

QScrollArea *CASC19F6Torque::createScrollArea()
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

QGroupBox *CASC19F6Torque::createBoxHeader()
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

    btnRefresh = new QPushButton("btnRefresh", this);
    btnRefresh->setText("Refresh");
    connect(btnRefresh, SIGNAL(clicked()), SLOT(procRefresh()));
    //  connect(btnRefresh, SIGNAL(clicked()), SLOT(refreshPlot()));
    layoutHeader->addWidget(btnRefresh);


    return groupHeader;
}

QGroupBox *CASC19F6Torque::createBoxGeneral()
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

QGroupBox *CASC19F6Torque::createBoxFooter()
{
    groupFooter = new QGroupBox("groupFooter",this);
    groupFooter->setTitle("");
    groupFooter->setMaximumHeight(100);

    layoutFooter = new QHBoxLayout();
    layoutFooter->setContentsMargins(0, 0, 0, 0);
    layoutFooter->setSpacing(0);
    groupFooter->setLayout(layoutFooter);

    return groupFooter;
}

void CASC19F6Torque::refreshView()
{

}

void CASC19F6Torque::refreshData()
{

}

void CASC19F6Torque::refreshPlot()
{
    bool rPlot = false;
    // Луч 1
    if ((!xData.isEmpty())&&(!yData.isEmpty())) {
        graph->setData(xData, yData);
        xAxis->setRange(xData.first(), xData.last());
        double min = yData.first(), max = yData.first();
        for (int i = 0; i<yData.count(); ++i )
        {
            if (yData.at(i) < min) min = yData.at(i);
            if (yData.at(i) > max) max = yData.at(i);
        }
        yAxis->setRange(min*1.1, max*1.1);
        rPlot = true;
    }
    // Луч 2
    if ((!xData2.isEmpty())&&(!yData2.isEmpty())) {
        graph2->setData(xData2, yData2);
        xAxis2->setRange(xData2.first(), xData2.last());
        double min = yData2.first(), max = yData2.first();
        for (int i = 0; i<yData2.count(); ++i )
        {
            if (yData2.at(i) < min) min = yData2.at(i);
            if (yData2.at(i) > max) max = yData2.at(i);
        }
        yAxis2->setVisible(true);
        yAxis2->setRange(yAxis->range());
        rPlot = true;
    }
    //
    if (rPlot) customPlot->replot();

}

void CASC19F6Torque::procRefresh()
{

}

void CASC19F6Torque::procCalc()
{

}

void CASC19F6Torque::changeFreq(const QString &str)
{

}

void CASC19F6Torque::changePhase(const QString &str)
{

}

void CASC19F6Torque::changeAmp(const QString &str)
{

}

void CASC19F6Torque::changeTime(const QString &str)
{

}

void CASC19F6Torque::changeNoise(const QString &str)
{

}

void CASC19F6Torque::changeScaleXPlot(const QString &str)
{

}

void CASC19F6Torque::changeScaleYPlot(const QString &str)
{

}

void CASC19F6Torque::procMousePress(QMouseEvent *e)
{

}

void CASC19F6Torque::procMouseMove(QMouseEvent *e)
{

}
