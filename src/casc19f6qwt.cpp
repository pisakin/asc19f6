#include "cascemqwt.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "aPKC/utils.c"
#include "aPKC/kalman.c"
#include "aPKC/pump.c"
#include "aPKC/gdrive.c"
#include "aPKC/mnk.c"

extern float procQMU(const float uprI);
extern float kalman(const float in, const float WD, float *P, float *Xp, float *Zp, float *Xe);

extern float procKMNK(float *array, const int N);
extern void  procArrayMNK(const float in, float *arrayIN, float *arrayOUT, const int N, const float Tik);

static short VnN=29;
static short VMsTSk[31];

float VnTSk (short Vx)
{
  int i,N;
  float S=0;

  N=VnN;
  S=(short)(Vx-VMsTSk[N])*N;

  for (i=1; i<=(int)((N-1)/2); i++)
    S=S+(short)(VMsTSk[i]-VMsTSk[N-i])*(N-2*i);

  for (i=1; i<=N; i++)
    VMsTSk[N-i+1]=VMsTSk[N-i];

  VMsTSk[1]=Vx;

  return TKR(S)*6/(0.001*N*(N+1)*(N+2));
}

float KZv(float Vx, float Tik, float K, float T1, float G, float *W)

{
  float O;
  if (fabs(*W)<0.00001) *W=0;

  O=(Vx*K-*W);
  *W=O*Tik/T1+*W;
  O=O*G+*W;
  return O;
}

#ifdef __cplusplus
}
#endif

/*
 *  Конструктор класса
 */
CASCEMQWT::CASCEMQWT(QWidget *parent) : QFrame(parent)
{
//
  setAttribute(Qt::WA_DeleteOnClose);
  setWindowTitle(QString::fromUtf8("ascEMQWT"));
  QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  if (objectName().isEmpty()) setObjectName(QString::fromUtf8("ascEMQWT"));
  if (accessibleName().isEmpty()) setAccessibleName("ascEMQWT");
  if (accessibleDescription().isEmpty()) setAccessibleDescription("ascEMQWT");
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);
  sizePolicy.setHeightForWidth(true);
  setSizePolicy(sizePolicy);
  setFrameShape(QFrame::StyledPanel);
  setFrameShadow(QFrame::Raised);
//  Инициализация интерфейса
  initInterface();
//  Создание интерфейса
  createInterface();
//
  QTimer::singleShot(500, this, SLOT(procRefresh()));
}

/*
 *  Деструктор класса
 */
CASCEMQWT::~CASCEMQWT()
{

}

/*
 *  Переопределение метода отображения
 */
void CASCEMQWT::showEvent(QShowEvent *e)
{
  if (!e->spontaneous() && !init)
  {
    timerId = startTimer(100); init = true;
  }
}

/*
 *  Переопределение метода таймера обновления
 */
void CASCEMQWT::timerEvent(QTimerEvent *e)
{
  if (e->timerId() == timerId) {
    ++countTimer;
    refreshView();
  } else {
    QWidget::timerEvent(e);
  }

}

/*
 *  Создание графика
 */
QwtPlot *CASCEMQWT::createPlot()
{
  qwtPlotCurveA = new QwtPlotCurve;
  qwtPlotCurveA->setTitle( "Curve A" );
  penCurveA.setWidth(1);
  penCurveA.setColor(Qt::red);
  qwtPlotCurveA->setPen(penCurveA);
//  qwtPlotCurveA->setRenderHint( QwtPlotItem::RenderAntialiased, true ); // сглаживание
  qwtPlotCurveA->setStyle(QwtPlotCurve::Steps);
  idCurveA = 0;

  qwtPlotCurveB = new QwtPlotCurve;
  qwtPlotCurveB->setTitle( "Curve B" );
  penCurveB.setWidth(1);
  penCurveB.setColor(Qt::blue);
  qwtPlotCurveB->setPen(penCurveB);
  qwtPlotCurveB->setStyle(QwtPlotCurve::Steps);
//  qwtPlotCurveB->setRenderHint( QwtPlotItem::RenderAntialiased, true ); // сглаживание
  idCurveB = 1;

  qwtPlotCurveC = new QwtPlotCurve;
  qwtPlotCurveC->setTitle( "Curve C" );
  penCurveC.setWidth(1);
  penCurveC.setColor(Qt::green);
  qwtPlotCurveC->setPen(penCurveC);
  qwtPlotCurveC->setStyle(QwtPlotCurve::Steps);
//  qwtPlotCurveB->setRenderHint( QwtPlotItem::RenderAntialiased, true ); // сглаживание
  idCurveC = 2;

  qwtPlotCurveD = new QwtPlotCurve;
  qwtPlotCurveD->setTitle( "Curve D" );
  penCurveD.setWidth(1);
  penCurveD.setColor(Qt::yellow);
  qwtPlotCurveD->setPen(penCurveD);
  qwtPlotCurveD->setStyle(QwtPlotCurve::Steps);
//  qwtPlotCurveB->setRenderHint( QwtPlotItem::RenderAntialiased, true ); // сглаживание
  idCurveD = 3;

  qwtPlot = new QwtPlot(this);
  qwtPlot->setContentsMargins(0, 0, 0, 0);
  qwtPlot->setAutoFillBackground(true);
  qwtPlot->setTitle( "Qwt" ); // заголовок
  qwtPlot->setCanvasBackground( Qt::white ); // цвет фона
  // Параметры осей координат
  qwtPlot->setAxisTitle(QwtPlot::yLeft, "Y");
  qwtPlot->setAxisTitle(QwtPlot::xBottom, "time");
//    qwtPlot->insertLegend( new QwtLegend() );
  qwtPlot->setAxisScale(idCurveA, -10, 10);

//    qwtPlotScaleItem = new QwtPlotScaleItem( QwtScaleDraw::LeftScale, 0.0 );
//    qwtPlotScaleItem->setFont( qwtPlot->axisWidget( QwtAxis::YLeft )->font() );
//    qwtPlotScaleItem->attach(qwtPlot);
//    qwtPlot->axisScaleEngine(1);
///    qwtPlot->setAxisVisible( QwtAxis::YLeft, false );

  qwtPlotGrid = new QwtPlotGrid(); //
  penGrid.setWidth(1);
  penGrid.setColor(Qt::gray);
  qwtPlotGrid->setMajorPen(penGrid); // цвет линий и толщина
  qwtPlotGrid->attach(qwtPlot); // добавить сетку к полю графика
  vBoxLayout->addWidget(qwtPlot);

// make a plot curve from the data and attach it to the plot
  for( int index=0; index < plotDataSize; ++index ) {
    xData.append(index*Tik);
    aData.append(0); bData.append(0); cData.append(0); dData.append(0);
  }
//
  qwtPlotCurveA->setSamples(xData, aData);
  qwtPlotCurveA->attach(qwtPlot);

  qwtPlotCurveB->setSamples(xData, bData);
  qwtPlotCurveB->attach(qwtPlot);

  qwtPlotCurveC->setSamples(xData, cData);
  qwtPlotCurveC->attach(qwtPlot);

  qwtPlotCurveD->setSamples(xData, dData);
  qwtPlotCurveD->attach(qwtPlot);

  qwtPlot->replot();

  return qwtPlot;
}

/*
 *  Инициализация интерфейса
 */
void CASCEMQWT::initInterface()
{
  doubleValidator.setNotation(QDoubleValidator::StandardNotation);
  init = false;
  freqIN = 0.8; ampIN = 1.0; phaseIN = 90.0; noiseIN = 10; timeIN = 10.0;
  Tik = 1e-3;
//
  ampINdeg = 3.2f;
  ampINrad = TGR(ampINdeg);
  ampINcod = TGD(ampINdeg);;
//
  freqINHz = 0.2f;
//
  phaseINdeg = -90.0f;
  phaseINrad = TGR(phaseINdeg);
//    phaseINcod = TGR(phaseINdeg);
//
  timeRegSec = 25.0f;
  noiseINmrad = 1.0; noiseINrad = noiseINmrad *1e-3;
//
  offsetINdeg = 3.2;
  offsetINrad = TGR(offsetINdeg);
}

/*
 *  Создание интерфейса
 */
void CASCEMQWT::createInterface()
{
  QFont font = this->font();
  font.setPixelSize(12);
  setFont(font);
//  Создание компановщика
  vBoxLayout = new QVBoxLayout();
  vBoxLayout->setContentsMargins(0, 0, 0, 0);
  vBoxLayout->setSpacing(0);
  setLayout(vBoxLayout);
//
  vBoxLayout->addWidget(createBoxHeader());
  vBoxLayout->addWidget(createBoxGeneral());
  vBoxLayout->addWidget(createBoxFooter());
}

/*
 *  Создание области прокрутки
 */
QScrollArea *CASCEMQWT::createScrollArea()
{
  scrollArea = new QScrollArea(this);
  scrollArea->setAutoFillBackground(true);
  scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  scrollArea->setWidgetResizable(true);

  layoutScrollArea = new QVBoxLayout();
  layoutScrollArea->setContentsMargins(0, 0, 0, 0);
  layoutScrollArea->setSpacing(0);

  widgetScrollArea = new QWidget();
  widgetScrollArea->setLayout(layoutScrollArea);
  scrollArea->setWidget(widgetScrollArea);

  spacerItem = new QSpacerItem(0, 100, QSizePolicy::Expanding, QSizePolicy::Expanding);
  layoutScrollArea->addItem(spacerItem);

  return scrollArea;

}

/*
 *  Создание группы заголовком
 */
QGroupBox *CASCEMQWT::createBoxHeader()
{
  groupHeader = new QGroupBox("Header",this);
  groupHeader->setTitle("");
  groupHeader->setMaximumHeight(50);

  layoutHeader = new QHBoxLayout();
  layoutHeader->setContentsMargins(0, 0, 0, 0);
  layoutHeader->setSpacing(0);
  groupHeader->setLayout(layoutHeader);

  lblTitel = new QLabel("Titel", this);
  lblTitel->setText("");
  QFont font = this->font();
  font.setPixelSize(14);
  font.setBold(true);
  lblTitel->setFont(font);
  layoutHeader->addWidget(lblTitel);

  lblFreqHz = new QLabel("Freq", this);
  lblFreqHz->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  lblFreqHz->setText("Freq, Hz");
  layoutHeader->addWidget(lblFreqHz);

  edtFreqHz = new QDoubleSpinBox(this);
  edtFreqHz->setRange(0.01f, 10.0f);
  edtFreqHz->setSingleStep(0.1);
  edtFreqHz->setValue(freqINHz);
//    edtFreq->setFocusPolicy(Qt::NoFocus);
  connect(edtFreqHz, SIGNAL(textChanged(QString)), this, SLOT(changeFreqHz(QString)));
  layoutHeader->addWidget(edtFreqHz);

  lblPhaseDeg = new QLabel("Phase", this);
  lblPhaseDeg->setText("Phase, deg");
  lblPhaseDeg->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  layoutHeader->addWidget(lblPhaseDeg);

  edtPhaseDeg = new QDoubleSpinBox(this);
  edtPhaseDeg->setRange(-90.0f, 90.0f);
  edtPhaseDeg->setSingleStep(10.0);
  edtPhaseDeg->setValue(phaseINdeg);
//    edtPhase->setFocusPolicy(Qt::NoFocus);
  connect(edtPhaseDeg, SIGNAL(textChanged(QString)), this, SLOT(changePhaseDeg(QString)));
  layoutHeader->addWidget(edtPhaseDeg);

  lblAmpDeg = new QLabel("Amp:", this);
  lblAmpDeg->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  lblAmpDeg->setText("Amp[deg]");
  layoutHeader->addWidget(lblAmpDeg);

  edtAmpDeg = new QDoubleSpinBox(this);
  edtAmpDeg->setRange(0.0, 180.0);
  edtAmpDeg->setSingleStep(0.1);
  edtAmpDeg->setValue(ampINdeg);
//    edtAmp->setFocusPolicy(Qt::NoFocus);
  connect(edtAmpDeg, SIGNAL(textChanged(QString)), this, SLOT(changeAmpDeg(QString)));
  layoutHeader->addWidget(edtAmpDeg);

  lblOffsetDeg = new QLabel("Offset:", this);
  lblOffsetDeg->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  lblOffsetDeg->setText("Offset[deg]");
  layoutHeader->addWidget(lblOffsetDeg);

  edtOffsetDeg = new QDoubleSpinBox(this);
  edtOffsetDeg->setRange(0.0, 180.0);
  edtOffsetDeg->setSingleStep(0.1);
  edtOffsetDeg->setValue(offsetINdeg);
//    edtAmp->setFocusPolicy(Qt::NoFocus);
  connect(edtOffsetDeg, SIGNAL(textChanged(QString)), this, SLOT(changeOffsetDeg(QString)));
  layoutHeader->addWidget(edtOffsetDeg);

  lblNoiseMRad = new QLabel("Noise", this);
  lblNoiseMRad->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  lblNoiseMRad->setText("Noise[mrad]");
  layoutHeader->addWidget(lblNoiseMRad);

  edtNoiseMRad = new QDoubleSpinBox(this);
  edtNoiseMRad->setRange(0, 50);
  edtNoiseMRad->setSingleStep(0.1);
  edtNoiseMRad->setValue(noiseINmrad);
//    edtFreq->setFocusPolicy(Qt::NoFocus);
  connect(edtNoiseMRad, SIGNAL(textChanged(QString)), this, SLOT(changeNoiseMRad(QString)));
  layoutHeader->addWidget(edtNoiseMRad);


  lblTimeRegSec = new QLabel("Time", this);
  lblTimeRegSec->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  lblTimeRegSec->setText("Time, sec");
  layoutHeader->addWidget(lblTimeRegSec);

  edtTimeRegSec = new QDoubleSpinBox(this);
  edtTimeRegSec->setRange(0.01, 60.0);
  edtTimeRegSec->setSingleStep(0.01);
  edtTimeRegSec->setValue(timeRegSec);
//    edtTime.set
//    edtTime->setFocusPolicy(Qt::NoFocus);
  connect(edtTimeRegSec, SIGNAL(textChanged(QString)), this, SLOT(changeTimeRegSec(QString)));
  layoutHeader->addWidget(edtTimeRegSec);

  btnRefresh = new QPushButton("Refresh", this);
  btnRefresh->setFocusPolicy(Qt::NoFocus);
  connect(btnRefresh, SIGNAL(clicked()), this, SLOT(procRefresh()));
  layoutHeader->addWidget(btnRefresh);


  return groupHeader;
}

/*
 *  Создание основной группыы
 */
QGroupBox *CASCEMQWT::createBoxGeneral()
{
  groupGeneral = new QGroupBox("General", this);
  groupGeneral->setTitle("");
//    groupGeneral->setMaximumHeight(40);

  layoutGeneral = new QHBoxLayout();
  layoutGeneral->setContentsMargins(0, 0, 0, 0);
  layoutGeneral->setSpacing(0);
  groupGeneral->setLayout(layoutGeneral);

//    layoutGeneral->addWidget(createScrollArea());
  layoutGeneral->addWidget(createPlot());

  return groupGeneral;

}

/*
 *  Создание группы подвала
 */
QGroupBox *CASCEMQWT::createBoxFooter()
{
  groupFooter = new QGroupBox("Footer",this);
  groupFooter->setTitle("");
  groupFooter->setMaximumHeight(50);

  layoutFooter = new QHBoxLayout();
  layoutFooter->setContentsMargins(0, 0, 0, 0);
  layoutFooter->setSpacing(0);
  groupFooter->setLayout(layoutFooter);

  lblScaleXMax = new QLabel("ScaleXMax: ", this);
  layoutFooter->addWidget(lblScaleXMax);

  edtScaleXMax = new QDoubleSpinBox(this);
  edtScaleXMax->setFocusPolicy(Qt::NoFocus);
  edtScaleXMax->setRange(1.0, 100.0);
  edtScaleXMax->setSingleStep(0.1);
  connect(edtScaleXMax, SIGNAL(textChanged(QString)), SLOT(changeScaleXPlot(QString)));
  layoutFooter->addWidget(edtScaleXMax);

  lblScaleY = new QLabel("scaleY: ", this);
  layoutFooter->addWidget(lblScaleY);
/*
  edtScaleY = new QDoubleSpinBox(this);
  edtScaleY->setFocusPolicy(Qt::NoFocus);
  edtScaleY->setRange(0.1, 100.0);
  connect(edtScaleY, SIGNAL(textChanged(QString)), SLOT(changeScaleYPlot(QString)));
  layoutFooter->addWidget(edtScaleY);
*/
  cmbScaleY = new QComboBox(this);
  cmbScaleY->setEditable(true);
  cmbScaleY->setValidator(&doubleValidator);
  cmbScaleY->setFocusPolicy(Qt::NoFocus);
  QStringList lstScaleY;
  lstScaleY.clear();
  lstScaleY.append("0.001");
  lstScaleY.append("0.01");
  lstScaleY.append("0.1");
  lstScaleY.append("1");
  lstScaleY.append("10");
  lstScaleY.append("100");
  lstScaleY.append("1000");
  cmbScaleY->addItems(lstScaleY);
  connect(cmbScaleY, SIGNAL(currentTextChanged(QString)), SLOT(changeScaleYPlot(QString)));
  layoutFooter->addWidget(cmbScaleY);

  return groupFooter;

}

/*
 *  Обновление вида
 */
void CASCEMQWT::refreshView()
{
/*
  if ((!xData.isEmpty())&&(!xData.isEmpty())) {
    qwtPlotCurveA->setSamples(xData, yData);
    qwtPlot->replot();
  }
*/
}

/*
 *  Обновление графика
 */
void CASCEMQWT::refreshPlot()
{

//
  bool bRePlot = false;
  if ((!xData.isEmpty())&&(!aData.isEmpty()))
  {
    qwtPlotCurveA->setSamples(xData, aData);
//
    double minY = aData.first(), maxY = aData.last();
    for (int i = 0; i<aData.count(); ++i )
    {
      if (aData.at(i) < minY) minY = aData.at(i);
      if (aData.at(i) > maxY) maxY = aData.at(i);
    }
    //qwtPlot->setAxisScale(0, xData.first(), xData.last());
    float max = ampINdeg*2*M_PI*freqINHz;
    qwtPlot->setAxisScale(0, -max, max);
//    qwtPlotGrid->set
    bRePlot = true;
  } else {
    if (xData.isEmpty()) qDebug() << "xData empty";
    if (aData.isEmpty()) qDebug() << "aData empty";
  }
//
  if ((!xData.isEmpty())&&(!bData.isEmpty()))
  {
    qwtPlotCurveB->setSamples(xData, bData);
//
    double minY = bData.first(), maxY = bData.last();
    for (int i = 0; i<bData.count(); ++i )
    {
      if (bData.at(i) < minY) minY = bData.at(i);
      if (bData.at(i) > maxY) maxY = bData.at(i);
    }
//    qwtPlot->setAxisScale(0, minY, maxY);
    bRePlot = true;
   } else {
      if (xData.isEmpty()) qDebug() << "xData empty";
      if (bData.isEmpty()) qDebug() << "bData empty";
   }
//
  if ((!xData.isEmpty())&&(!cData.isEmpty()))
  {
    qwtPlotCurveC->setSamples(xData, cData);
//
    double minY = cData.first(), maxY = cData.last();
    for (int i = 0; i<cData.count(); ++i )
    {
      if (cData.at(i) < minY) minY = cData.at(i);
      if (cData.at(i) > maxY) maxY = cData.at(i);
    }
//    qwtPlot->setAxisScale(0, minY, maxY);
    bRePlot = true;
   } else {
      if (xData.isEmpty()) qDebug() << "xData empty";
      if (cData.isEmpty()) qDebug() << "cData empty";
   }
//
  if ((!xData.isEmpty())&&(!dData.isEmpty()))
  {
    qwtPlotCurveB->setSamples(xData, dData);
//
    double minY = dData.first(), maxY = dData.last();
    for (int i = 0; i<dData.count(); ++i )
    {
      if (dData.at(i) < minY) minY = dData.at(i);
      if (dData.at(i) > maxY) maxY = dData.at(i);
    }
//    qwtPlot->setAxisScale(0, minY, maxY);
    bRePlot = true;
   } else {
      if (xData.isEmpty()) qDebug() << "xData empty";
      if (dData.isEmpty()) qDebug() << "dData empty";
   }

//
  if (bRePlot) qwtPlot->replot();
}

/*
 *
 */
void CASCEMQWT::procRefresh()
{
  xData.clear();
  aData.clear(); bData.clear(); cData.clear(); dData.clear();

  const float TimeReg = timeRegSec;
  const float ampRad = ampINrad;
  const float freqHz = freqINHz;
  const float phase0 = phaseINrad;
  const float noiseIN = noiseINmrad;
  const float offset = offsetINrad;


  float arrayIN[30], arrayOUT[30];
  for (int i = 0; i < 30; i++) {
    arrayIN[i] = 0.0; arrayOUT[i] = 0.0;
  }

  float WOCTSk=0.0;

  QRandomGenerator generator;
  float  noise = static_cast<float>(generator.generateDouble() * 2.0*noiseIN - noiseIN)*1e-3;

  for (int i=0; i<(TimeReg / Tik); i++) {
    xData.append(i*Tik);
    float y = ampRad*sin(2*M_PI*freqHz*Tik*i + phase0) + offset;
    float wy = ampRad*2*M_PI*freqHz*cos(2*M_PI*freqHz*Tik*i + phase0);
    aData.append(wy * 180.0 / M_PI);
    float noise = static_cast<float>(generator.generateDouble()*2.0*noiseIN - noiseIN)*1e-3;
    if (noiseINmrad!=0.0) y += noise;
    float vnTSk = VnTSk(TRD(y));
    float ocTSk = KZv(vnTSk,1e-3, 1.0, 0.0032, 10.0, &WOCTSk);
    bData.append(ocTSk * 180.0 / M_PI);
//    yData.append(y * 180.0 / M_PI);
    float a = 0, b = 0, c =0;
    float org = procMNK1D(y, arrayIN, 10, 1e-3, &a, &b, &c);
    float wMNKL = procWMNKL(y, arrayIN,  10, 1e-3);
    float wMNKR = procWMNKR(y, arrayIN,  10, 1e-3);
    cData.append(wMNKL * 180.0 / M_PI);
    dData.append(wMNKR * 180.0 / M_PI);
//    yData2.append(WK);
  }
//
  refreshPlot();
}

/*
 *
 */
void CASCEMQWT::procCalc()
{

}

/*
 *
 */
void CASCEMQWT::changeFreq(const QString &str)
{
  bool ok = false;
  float value = 0.0f;
  QString s = str;
  s.replace(QStringLiteral(","), QStringLiteral("."));
  value = s.toFloat(&ok);
  if (ok) freqIN = value;

}

/*
 *
 */
void CASCEMQWT::changePhase(const QString &str)
{
  bool ok = false;
  float value = 0.0f;
  QString s = str;
  s.replace(QStringLiteral(","), QStringLiteral("."));
  value = s.toFloat(&ok);
  if (ok) phaseIN = value;

}

/*
 *
 */
void CASCEMQWT::changeAmp(const QString &str)
{
  bool ok = false;
  float value = 0.0f;
  QString s = str;
  s.replace(QStringLiteral(","), QStringLiteral("."));
  value = s.toFloat(&ok);
  if (ok) ampIN = value;

}

/*
 *
 */
void CASCEMQWT::changeTime(const QString &str)
{
  bool ok = false;
  float value = 0.0f;
  QString s = str;
  s.replace(QStringLiteral(","), QStringLiteral("."));
  value = s.toFloat(&ok);
  if (ok) timeIN = value;

}

/*
 *
 */
void CASCEMQWT::changeNoise(const QString &str)
{
  bool ok = false;
  float value = 0.0f;
  QString s = str;
  s.replace(QStringLiteral(","), QStringLiteral("."));
  value = s.toFloat(&ok);
  if (ok) noiseIN = value;

}

void CASCEMQWT::changeFreqHz(const QString &str)
{
  bool ok = false;
  float value = 0.0f;
  QString s = str;
  s.replace(QStringLiteral(","), QStringLiteral("."));
  value = s.toFloat(&ok);
  if (ok) freqINHz = value;
//
  procRefresh();

}

void CASCEMQWT::changePhaseDeg(const QString &str)
{
  bool ok = false;
  float value = 0.0f;
  QString s = str;
  s.replace(QStringLiteral(","), QStringLiteral("."));
  value = s.toFloat(&ok);
  if (ok) {
    phaseINdeg = value;
    phaseINrad = phaseINdeg*M_PI/180.0;
  }
//
  procRefresh();

}

void CASCEMQWT::changePhaseRad(const QString &str)
{
  bool ok = false;
  float value = 0.0f;
  QString s = str;
  s.replace(QStringLiteral(","), QStringLiteral("."));
  value = s.toFloat(&ok);
  if (ok) {
    phaseINrad = value;
    phaseINdeg = value * 180.0/M_PI;
  }
//
  procRefresh();

}

void CASCEMQWT::changeAmpCod(const QString &str)
{
  bool ok = false;
  short value = 0.0f;
  QString s = str;
  s.replace(QStringLiteral(","), QStringLiteral("."));
  value = s.toShort(&ok);
  if (ok) {
    ampINcod = value;
    ampINdeg = TDG(ampINcod);
    ampINrad = TDR(ampINcod);
  }
//
  procRefresh();

}

void CASCEMQWT::changeAmpDeg(const QString &str)
{
  bool ok = false;
  float value = 0.0f;
  QString s = str;
  s.replace(QStringLiteral(","), QStringLiteral("."));
  value = s.toFloat(&ok);
  if (ok) {
    ampINdeg = value;
    ampINrad = value * M_PI / 180.0;
    ampINcod = TGD(value);
    edtOffsetDeg->setValue(ampINdeg);
  }
//
  procRefresh();

}

void CASCEMQWT::changeAmpRad(const QString &str)
{
  bool ok = false;
  float value = 0.0f;
  QString s = str;
  s.replace(QStringLiteral(","), QStringLiteral("."));
  value = s.toFloat(&ok);
  if (ok) {
    ampINrad = value;
    ampINdeg = value * 180.0 / M_PI;
    ampINcod = TRD(value);
  }
//
  procRefresh();

}

void CASCEMQWT::changeTimeRegSec(const QString &str)
{
  bool ok = false;
  float value = 0.0f;
  QString s = str;
  s.replace(QStringLiteral(","), QStringLiteral("."));
  value = s.toFloat(&ok);
  if (ok) timeRegSec = value;
//
  procRefresh();

}

void CASCEMQWT::changeNoiseRad(const QString &str)
{
  bool ok = false;
  float value = 0.0f;
  QString s = str;
  s.replace(QStringLiteral(","), QStringLiteral("."));
  value = s.toFloat(&ok);
  if (ok) {
   noiseINrad = value;
   noiseINdeg = noiseINrad * 180.0 / M_PI;
   noiseINcod = TRD(value);
  }
//
  procRefresh();

}

void CASCEMQWT::changeNoiseMRad(const QString &str)
{
  bool ok = false;
  float value = 0.0f;
  QString s = str;
  s.replace(QStringLiteral(","), QStringLiteral("."));
  value = s.toFloat(&ok);
  if (ok) {
   noiseINmrad = value;
   noiseINrad = value / 1e3;
   noiseINdeg = noiseINrad * 180.0 / M_PI;
   noiseINcod = TRD(value);
  }
//
  procRefresh();

}

void CASCEMQWT::changeNoiseDeg(const QString &str)
{
  bool ok = false;
  float value = 0.0f;
  QString s = str;
  s.replace(QStringLiteral(","), QStringLiteral("."));
  value = s.toFloat(&ok);
  if (ok) {
    noiseINdeg = value;
    noiseINrad = noiseINdeg * M_PI / 180.0;
    noiseINcod = TGD(value);
  }
//
  procRefresh();

}

void CASCEMQWT::changeNoiseCod(const QString &str)
{
  bool ok = false;
  short value = 0;
  QString s = str;
  s.replace(QStringLiteral(","), QStringLiteral("."));
  value = s.toFloat(&ok);
  if (ok) {
    noiseINcod = value;
    noiseINrad = TDR(value);
    noiseINdeg = TDG(value);
  }
//
  procRefresh();

}

void CASCEMQWT::changeOffsetCod(const QString &str)
{
  bool ok = false;
  short value = 0;
  QString s = str;
  s.replace(QStringLiteral(","), QStringLiteral("."));
  value = s.toFloat(&ok);
  if (ok) {
    offsetINcod = value;
    offsetINrad = TDR(value);
    offsetINdeg = TDG(value);
  }
//
  procRefresh();

}

void CASCEMQWT::changeOffsetDeg(const QString &str)
{
  bool ok = false;
  float value = 0.0f;
  QString s = str;
  s.replace(QStringLiteral(","), QStringLiteral("."));
  value = s.toFloat(&ok);
  if (ok) {
    offsetINdeg = value;
    offsetINrad = value * M_PI / 180.0;
    offsetINcod = TGD(value);
  }
//
  procRefresh();

}

void CASCEMQWT::changeOffsetRad(const QString &str)
{
  bool ok = false;
  float value = 0.0f;
  QString s = str;
  s.replace(QStringLiteral(","), QStringLiteral("."));
  value = s.toFloat(&ok);
  if (ok) {
    offsetINrad = value;
    offsetINdeg = value * 180.0 / M_PI;
    offsetINcod = TRD(value);
  }
//
  procRefresh();

}

/*
 *
 */
void CASCEMQWT::changeScaleXPlot(const QString &str)
{
  bool ok = false;
  float value = 0.0f;
  QString s = str;
  s.replace(QStringLiteral(","), QStringLiteral("."));
  value = s.toFloat(&ok);

}

/*
 *
 */
void CASCEMQWT::changeScaleYPlot(const QString &str)
{
  bool ok = false;
  float value = 0.0f;
  QString s = str;
  s.replace(QStringLiteral(","), QStringLiteral("."));
  value = s.toFloat(&ok);

}

/*
 *
 */
void CASCEMQWT::procMousePress(QMouseEvent *e)
{

}

/*
 *
 */
void CASCEMQWT::procMouseMove(QMouseEvent *e)
{

}

/*
 *
 */
void CASCEMQWT::procStart()
{

}

/*
 *
 */
void CASCEMQWT::resetData()
{
    for( int index=0; index<plotDataSize; ++index )
    {
        xData[index] = index;
        aData[index] = 0; bData[index] = 0; cData[index] = 0; dData[index] = 0;
    }
}
