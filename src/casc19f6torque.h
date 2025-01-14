#ifndef CASC19F6TORQUE_H
#define CASC19F6TORQUE_H

#include <QFrame>
#include <QVBoxLayout>
#include <QShowEvent>
#include <QTimerEvent>
#include <QKeyEvent>
#include <QLabel>
#include <QPushButton>
#include <QSplitter>
#include <QScrollArea>

#ifdef __linux__
#include <qcustomplot.h>
#else
#include "../../qcustomplot/qcustomplot.h"
#endif

class CASC19F6Torque : public QFrame
{
    Q_OBJECT
public:
    explicit CASC19F6Torque(QWidget *parent = nullptr);
    ~CASC19F6Torque();


signals:
    void home       (void);
    void back       (void);
    void closePage  (void);
    //

protected:
    virtual QSize sizeHint() const {return QSize(800, 600);}
    virtual void showEvent      (QShowEvent *e);
    virtual void timerEvent     (QTimerEvent *e);

private:
    bool init;
    int timerId;
    short countTimer; int countPlot;
    const float maxX = 10.0f;
    QVector<double> xData, yData;
    QVector<double> xData2, yData2;

    QVBoxLayout   *vBoxLayout;
    QHBoxLayout   *hBoxLayout;
    QSplitter     *splitter;
    //
    QScrollArea   *scrollArea;
    QWidget       *widgetScrollArea;
    QVBoxLayout   *layoutScrollArea;
    QSpacerItem   *spacerItem;
    //
    QGroupBox     *groupHeader;
    QHBoxLayout   *layoutHeader;
    //  CASCEMInput   *ascEMInput;
    QLabel        *lblTitel;
    QPushButton   *btnCalc;
    QPushButton   *btnOK;
    QPushButton   *btnCancel;
    QPushButton   *btnAccept;
    QPushButton   *btnReject;
    QSpacerItem   *spacerItemHeader;
    //
    QGroupBox     *groupFooter;
    QHBoxLayout   *layoutFooter;
    QLabel        *lblScaleX;
    QDoubleSpinBox*edtScaleX;
    QComboBox     *cmbScaleX;
    QLabel        *lblScaleXMax;
    QDoubleSpinBox*edtScaleXMax;
    QComboBox     *cmbScaleXMax;
    QLabel        *lblScaleY;
    QDoubleSpinBox*edtScaleY;
    QComboBox     *cmbScaleY;
    QLabel        *lblScaleYMin;
    QDoubleSpinBox*edtScaleYMin;
    QComboBox     *cmbScaleYMin;
    QLabel        *lblScaleYMax;
    QDoubleSpinBox*edtScaleYMax;
    QComboBox     *cmbScaleYMax;
    //
    QGroupBox     *groupInput;
    QVBoxLayout   *layoutInput;

    QGroupBox     *groupGeneral;
    QVBoxLayout   *layoutGeneral;
    //
    QCustomPlot   *customPlot;
    QCPLegend     *legend;
    QCPGraph      *graph;
    QPen          penGraph;
    QCPAxis       *xAxis, *yAxis;
    QCPGrid       *xGrid, *yGrid;
    QCPGraph      *graph2;
    QCPAxis       *xAxis2, *yAxis2;
    QCPGrid       *xGrid2, *yGrid2;
    QPen          penGraph2;
    QCustomPlot *createPlot (void);

    QPushButton *btnRefresh;
    //
    void initInterface            (void);
    void createInterface          (void);
    QScrollArea *createScrollArea (void);
    QGroupBox *createBoxHeader    (void);
    QGroupBox *createBoxGeneral   (void);
    QGroupBox *createBoxFooter    (void);

private slots:
    void refreshView              (void);
    void refreshData              (void);
    void refreshPlot              (void);
    void procRefresh              (void);
    void procCalc                 (void);
    void changeFreq               (const QString &str);
    void changePhase              (const QString &str);
    void changeAmp                (const QString &str);
    void changeTime               (const QString &str);
    void changeNoise              (const QString &str);
    void changeScaleXPlot         (const QString &str);
    void changeScaleYPlot         (const QString &str);
    void procMousePress           (QMouseEvent *e);
    void procMouseMove            (QMouseEvent *e);
};

#endif // CASC19F6TORQUE_H
