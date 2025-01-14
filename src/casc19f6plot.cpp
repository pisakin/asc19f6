#include "casc19f6plot.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "aPKF/gc.c"
#include "aPKF/pu.c"
//#include "aPKF/pump.c"
//#include "aPKF/gdrive.c"
//#include "aPKF/laphx.c"
//#include "aPKF/mnk.c"
#include "aPKF/utils.c"
//#include "aPKF/integ.c"
#include "aPKF/zvsin.c"
#include "aPKF/zvstep.c"

//extern float procPumpQFromIMU(const float uprI);
//extern float procPumpIFromA(const float uprI);
extern float procPUPl(const float alpha);


#ifdef __cplusplus
}
#endif

/*
 *  Конструктор класса
 */
CASC19F6Plot::CASC19F6Plot(QWidget *parent) : QFrame(parent)
{
//  Установка параметров окна
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle(QString::fromUtf8("asc19F6Plot"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    if (objectName().isEmpty()) setObjectName(QString::fromUtf8("asc19F6Plot"));
    if (accessibleName().isEmpty()) setAccessibleName("asc19F6Plot");
    if (accessibleDescription().isEmpty()) setAccessibleDescription("asc19F6Plot");
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
 *  Деструктор класса
 */
CASC19F6Plot::~CASC19F6Plot()
{

}

/*
 *  Переопределение метода отображения
 */
void CASC19F6Plot::showEvent(QShowEvent *e)
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

/*
 *  Переопределение метода таймера
 */
void CASC19F6Plot::timerEvent(QTimerEvent *e)
{
  if (e->timerId() == timerId) {
      ++countTimer;
      refreshView();
  } else {
      QObject::timerEvent(e);
  }
}

/*
 *  Создание графика
 */
QCustomPlot *CASC19F6Plot::createPlot()
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

/*
 *  Инициализация интерфейса
 */
void CASC19F6Plot::initInterface()
{
    init = false;
}

/*
 *  Создание интерфейса
 */
void CASC19F6Plot::createInterface()
{
  vBoxLayout = new QVBoxLayout();
  vBoxLayout->setContentsMargins(0, 0, 0, 0);
  vBoxLayout->setSpacing(0);
  setLayout(vBoxLayout);

  vBoxLayout->addWidget(createBoxHeader());
  vBoxLayout->addWidget(createBoxGeneral());
  vBoxLayout->addWidget(createBoxFooter());
}


/*
 *  Создание области прокрутки
 */
QScrollArea *CASC19F6Plot::createScrollArea()
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

/*
 *  Создание группы заголовков
 */
QGroupBox *CASC19F6Plot::createBoxHeader()
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
//  lblTitel->setText("Насос");
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

/*
 *  Создание группы ввода
 */
QGroupBox *CASC19F6Plot::createBoxInput()
{
  groupInput = new QGroupBox(this);

  layoutInput = new QVBoxLayout();
  layoutInput->setContentsMargins(0, 0, 0, 0);
  layoutInput->setSpacing(0);
  groupInput->setLayout(layoutInput);

  return groupInput;
}

/*
 *  Создание основной группы
 */
QGroupBox *CASC19F6Plot::createBoxGeneral()
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

/*
 *  Создание группы подвала
 */
QGroupBox *CASC19F6Plot::createBoxFooter()
{
  groupFooter = new QGroupBox("groupFooter",this);
  groupFooter->setTitle("");
  groupFooter->setMaximumHeight(50);

  layoutFooter = new QHBoxLayout();
  layoutFooter->setContentsMargins(0, 0, 0, 0);
  layoutFooter->setSpacing(0);
  groupFooter->setLayout(layoutFooter);

  return groupFooter;
}

/*
 *  Построение графика насоса
 *  Расход от тока механизма управления
 */
void CASC19F6Plot::procPlotPumpQI()
{
    tData.clear(); yData.clear();
//  Расход от тока управления
  for (int i = -100; i < 100; i+=1) {
    float in = i / 10.0;
    tData.append(in);
//    yData.append(procPumpQFromIMU(in));
//    yData.append(procPumpIFromA(in));
  }
}

/*
 *  Построение графика насоса
 *  Расход от тока механизма управления
 */
void CASC19F6Plot::procPlotPumpIA()
{
    tData.clear(); yData.clear();
//  Расход от тока управления
  for (int i = -100; i < 100; i+=1) {
    float in = i / 10.0;
    tData.append(in);
//    yData.append(procPumpIFromA(in));
  }
}

/*
 *
 */
void CASC19F6Plot::procPlotPl()
{
    tData.clear(); yData.clear();
    const float Tik = 1e-3;

    const float Amp = 10e-3;
    const float freqHz = 0.2;
    const float phase0 = 90.0;
    const float TimeReg = 7.0;
    float a_rad = 0.0, a_deg = 0;

    for (int i = 0; i < (TimeReg/Tik); ++i)
    {
        a_deg += 1e-2;
        a_rad = a_deg * M_PI / 180.0;
        tData.append(a_deg);
        yData.append(funcGcMn(a_rad));
    }
}

void CASC19F6Plot::procPlotMn()
{
    tData.clear(); yData.clear();
    const float Tik = 1e-3;

    const float Amp = 10e-3;
    const float freqHz = 0.2;
    const float phase0 = 90.0;
    const float TimeReg = 7.0;
    float a_rad = 0.0, a_deg = 0;

    for (int i = 0; i < (TimeReg/Tik); ++i)
    {
        a_deg += 1e-2;
        a_rad = a_deg * M_PI / 180.0;
        tData.append(a_deg);
        yData.append(funcPUMn(a_rad));
    }
}

/*
 *
 */
void CASC19F6Plot::refreshView()
{

}

/*
 *
 */
void CASC19F6Plot::refreshData()
{
    procPlotMn();
//
    refreshPlot();
}

/*
 *  Обновление графика
 */
void CASC19F6Plot::refreshPlot()
{
//
  bool rPlot = false;
// Луч 1
  if ((!tData.isEmpty())&&(!yData.isEmpty())) {
    graph->setData(tData, yData);
    xAxis->setRange(tData.first(), tData.last());
    double min = yData.first(), max = yData.first();
    for (int i = 0; i<yData.count(); ++i ) {
      if (yData.at(i) < min) min = yData.at(i);
      if (yData.at(i) > max) max = yData.at(i);
    }
    yAxis->setRange(min*1.1, max*1.1);
//    yAxis->setRange(0.0, max*1.1);
    rPlot = true;
  }
// Луч 2
  if ((!tData.isEmpty())&&(!yData2.isEmpty())) {
    graph2->setData(tData, yData2);
    xAxis2->setRange(tData.first(), tData.last());
    double min = yData2.first(), max = yData2.first();
    for (int i = 0; i<yData2.count(); ++i ) {
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

/*
 *
 */
void CASC19F6Plot::procRefresh()
{
    refreshPlot();
}

/*
 *
 */
void CASC19F6Plot::procCalc()
{

}

/*
 *
 */
void CASC19F6Plot::changeFreq(const QString &str)
{

}

/*
 *
 */
void CASC19F6Plot::changePhase(const QString &str)
{

}

/*
 *
 */
void CASC19F6Plot::changeAmp(const QString &str)
{

}

/*
 *
 */
void CASC19F6Plot::changeTime(const QString &str)
{

}

/*
 *
 */
void CASC19F6Plot::changeNoise(const QString &str)
{

}

/*
 *
 */
void CASC19F6Plot::changeScaleXPlot(const QString &str)
{

}

/*
 *
 */
void CASC19F6Plot::changeScaleYPlot(const QString &str)
{

}

/*
 *
 */
void CASC19F6Plot::procMousePress(QMouseEvent *e)
{

}

/*
 *
 */
void CASC19F6Plot::procMouseMove(QMouseEvent *e)
{

}
