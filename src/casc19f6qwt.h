#ifndef CASCEMQWT_H
#define CASCEMQWT_H

#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QShowEvent>
#include <QTimer>
#include <QTimerEvent>
#include <QKeyEvent>
#include <QGroupBox>
#include <QSplitter>
#include <QScrollArea>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QValidator>
#include <QDoubleValidator>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QRandomGenerator>

#include <qwt/qwt_plot.h>
#include <qwt/qwt_legend.h>
#include <qwt/qwt_plot_grid.h>
#include <qwt/qwt_plot_curve.h>
#include <qwt/qwt_plot_scaleitem.h>

#include "cascemdevice.h"

class CASCEMQWT : public QFrame
{
    Q_OBJECT
public:
    explicit CASCEMQWT(QWidget *parent = nullptr);
            ~CASCEMQWT();

signals:

protected:
  virtual QSize sizeHint() const { return QSize(800, 600); }
  virtual void showEvent  (QShowEvent  *e);
  virtual void timerEvent (QTimerEvent *e);

private:
  bool init;
  int timerId; unsigned int countTimer;
  float   ampIN, freqIN, phaseIN, timeIN , noiseIN;
  float   Tik;
  float   timeRegSec;
  float   ampINdeg, ampINrad;
  short   ampINcod;
  float   freqINHz;
  float   phaseINdeg, phaseINrad;
  float   noiseINdeg, noiseINrad, noiseINmrad;
  short   noiseINcod;
  float   offsetINdeg, offsetINrad;
  short   offsetINcod;
//
  static constexpr int plotDataSize = 800;
  static constexpr double gain = 7.5;
  QVector<double> xData;
  QVector<double> aData, bData, cData, dData;
//
  QVBoxLayout     *vBoxLayout;
  QHBoxLayout     *hBoxLayout;
  QSplitter       *splitter;
  QScrollArea     *scrollArea;
  QWidget         *widgetScrollArea;
  QVBoxLayout     *layoutScrollArea;
  QSpacerItem     *spacerItem;
  QDoubleValidator doubleValidator;
//
  QGroupBox       *groupHeader;
  QHBoxLayout     *layoutHeader;
  QLabel          *lblTitel;
  QLabel          *lblFreqHz;
  QDoubleSpinBox  *edtFreqHz;
  QLabel          *lblAmpDeg;
  QDoubleSpinBox  *edtAmpDeg;
  QLabel          *lblAmpCode;
  QSpinBox        *edtAmpCode;
  QLabel          *lblAmpRad;
  QDoubleSpinBox  *edtAmpRad;
  QLabel          *lblPhaseDeg;
  QDoubleSpinBox  *edtPhaseDeg;
  QLabel          *lblTimeRegSec;
  QDoubleSpinBox  *edtTimeRegSec;
  QLabel          *lblNoiseDeg;
  QDoubleSpinBox  *edtNoiseDeg;
  QLabel          *lblNoiseRad;
  QDoubleSpinBox  *edtNoiseRad;
  QLabel          *lblNoiseMRad;
  QDoubleSpinBox  *edtNoiseMRad;
  QLabel          *lblNoiseCod;
  QSpinBox        *edtNoiseCod;
//
  QLabel          *lblOffsetDeg;
  QDoubleSpinBox  *edtOffsetDeg;
  QLabel          *lblOffsetRad;
  QDoubleSpinBox  *edtOffsetRad;
  QLabel          *lblOffsetCod;
  QSpinBox        *edtOffsetCod;

  QPushButton     *btnCalc;
  QLabel          *lblFreq;
  QDoubleSpinBox  *edtFreq;
  QLabel          *lblAmp;
  QSpinBox        *edtAmp;
  QLabel          *lblPhase;
  QDoubleSpinBox  *edtPhase;
  QLabel          *lblTime;
  QDoubleSpinBox  *edtTime;
  QLabel          *lblStep;
  QDoubleSpinBox  *edtStep;
  QLabel          *lblNoise;
  QDoubleSpinBox  *edtNoise;
//
  QGroupBox       *groupFooter;
  QHBoxLayout     *layoutFooter;
  QLabel          *lblScaleX;
  QDoubleSpinBox  *edtScaleX;
  QComboBox       *cmbScaleX;
  QLabel          *lblScaleXMax;
  QDoubleSpinBox  *edtScaleXMax;
  QComboBox       *cmbScaleXMax;
  QLabel          *lblScaleY;
  QDoubleSpinBox  *edtScaleY;
  QComboBox       *cmbScaleY;
  QLabel          *lblScaleYMin;
  QDoubleSpinBox  *edtScaleYMin;
  QComboBox       *cmbScaleYMin;
  QLabel          *lblScaleYMax;
  QDoubleSpinBox  *edtScaleYMax;
  QComboBox       *cmbScaleYMax;
//
  QGroupBox       *groupInput;
  QHBoxLayout     *layoutInput;
//
  QGroupBox       *groupGeneral;
  QHBoxLayout     *layoutGeneral;
  QPushButton     *btnRefresh;
  QPushButton     *btnOK;
  QPushButton     *btnCancel;
  QPushButton     *btnAccept;
  QPushButton     *btnReject;

  QPushButton     *btnStart;
  QPushButton     *btnReset;
//
  QwtPlotCurve        *qwtPlotCurveA;
  int                 idCurveA;
  QPen                penCurveA;
//
  QwtPlotCurve        *qwtPlotCurveB;
  int                 idCurveB;
  QPen                penCurveB;
//
  QwtPlotCurve        *qwtPlotCurveC;
  int                 idCurveC;
  QPen                penCurveC;
//
  QwtPlotCurve        *qwtPlotCurveD;
  int                 idCurveD;
  QPen                penCurveD;
//
  QwtPlotGrid         *qwtPlotGrid;
  QPen                penGrid;
  QwtPlotScaleItem    *qwtPlotScaleItem;
  QwtPlot             *qwtPlot;
//    
  QwtPlot   *createPlot         (void);

//
  void initInterface            (void);
  void createInterface          (void);
  QScrollArea *createScrollArea (void);
  QGroupBox *createBoxHeader    (void);
  QGroupBox *createBoxGeneral   (void);
  QGroupBox *createBoxFooter    (void);

private slots:
  void refreshView            (void);
  void refreshPlot            (void);
  void procRefresh            (void);
  void procCalc               (void);
  void procStart              (void);
  void resetData              (void);
  void changeFreq             (const QString &str);  
  void changePhase            (const QString &str);
  void changeAmp              (const QString &str);
  void changeTime             (const QString &str);
  void changeNoise            (const QString &str);
  void changeFreqHz             (const QString &str);
  void changePhaseDeg           (const QString &str);
  void changePhaseRad           (const QString &str);
  void changeAmpCod             (const QString &str);
  void changeAmpDeg             (const QString &str);
  void changeAmpRad             (const QString &str);
  void changeTimeRegSec         (const QString &str);
  void changeNoiseRad           (const QString &str);
  void changeNoiseMRad          (const QString &str);
  void changeNoiseDeg           (const QString &str);
  void changeNoiseCod           (const QString &str);
  void changeOffsetCod          (const QString &str);
  void changeOffsetDeg          (const QString &str);
  void changeOffsetRad          (const QString &str);
  void changeScaleXPlot       (const QString &str);
  void changeScaleYPlot       (const QString &str);
  void procMousePress         (QMouseEvent *e);
  void procMouseMove          (QMouseEvent *e);

};

#endif // CASCEMQWT_H
