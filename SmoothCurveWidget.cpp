#include "SmoothCurveWidget.h"
#include "mywidget.h"
//#include "SmoothCurveGenerator1.h"
#include "SmoothCurveGenerator2.h"

#include <QPainter>
#include <QtGlobal>
#include <QDateTime>

SmoothCurveWidget::SmoothCurveWidget(QWidget *parent) :
    QWidget(parent), ui(new Ui::SmoothCurveWidget) {
    ui->setupUi(this);

    connect(ui->generateCurveButton, SIGNAL(clicked(bool)), this, SLOT(generateCurves()));
    connect(ui->showKnotsCheckBox, SIGNAL(clicked(bool)), this, SLOT(update()));
    connect(ui->showSmoothCurveCheckBox, SIGNAL(clicked(bool)), this, SLOT(update()));
    connect(ui->smoothCurveGeneratorComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(update()));

    ui->generateCurveButton->click();
}

SmoothCurveWidget::~SmoothCurveWidget() {
    delete ui;
}

void SmoothCurveWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2 , height() / 2);
    painter.scale(1, -1);

    // 画坐标轴
    painter.setPen(QColor(180, 180, 180));
    painter.drawLine(-500, 0, 500, 0);
    painter.drawLine(0, 500, 0, -500);

    // showSmoothCurveCheckBox 被选中时显示平滑曲线，否则显示非平滑曲线
    painter.setPen(QPen(QColor(80, 80, 80), 2));
    if (ui->showSmoothCurveCheckBox->isChecked() && ui->smoothCurveGeneratorComboBox->currentIndex() == 0) {
        painter.drawPath(smoothCurve1);
    } else if (ui->showSmoothCurveCheckBox->isChecked() && ui->smoothCurveGeneratorComboBox->currentIndex() == 1) {
        painter.drawPath(smoothCurve2);
    } else {
        painter.drawPath(nonSmoothCurve);
    }

    // 如果曲线上的点可见，则显示出来
    if (ui->showKnotsCheckBox->isChecked()) {
        painter.setPen(Qt::black);
        painter.setBrush(Qt::gray);
        foreach(QPointF p, knots) {
            painter.drawEllipse(p, 3, 3);
        }
    }
}

void SmoothCurveWidget::generateCurves() {
    qsrand(QDateTime::currentDateTime().toMSecsSinceEpoch());

    // 随机生成曲线上的点: 横坐标为 [-200, 200]，纵坐标为 [-100, 100]
    int x = -200;
    knots.clear();
    while (x < 200) {
        knots << QPointF(x, qrand() % 200 - 100);
        x += qMin(qrand() % 30 + 5, 200);
    }

    // 根据曲线上的点创建平滑曲线
    smoothCurve1 = SmoothCurveGenerator1::generateSmoothCurve(knots);
    smoothCurve2 = SmoothCurveGenerator2::generateSmoothCurve(knots);

    // 连接点创建非平滑曲线曲线
    nonSmoothCurve = QPainterPath();
    nonSmoothCurve.moveTo(knots[0]);
    for (int i = 1; i < knots.size(); ++i) {
        nonSmoothCurve.lineTo(knots[i]);
    }

    update();
}

class SmoothCurveGenerator  // 这段代码是根据狗哥的代码  修改来的  已经验证了
{
protected:
    static QPainterPath generateSmoothCurveImp(const QVector<QPointF> &points) {
        QPainterPath path;
        int len = points.size();

        if (len < 2) {
            return path;
        }

        QVector<QPointF> firstControlPoints;
        QVector<QPointF> secondControlPoints;
        calculateControlPoints(points, &firstControlPoints, &secondControlPoints);

        path.moveTo(points[0].x(), points[0].y());

        // Using bezier curve to generate a smooth curve.
        for (int i = 0; i < len - 1; ++i) {
            path.cubicTo(firstControlPoints[i], secondControlPoints[i], points[i+1]);
        }

        return path;
    }
public:
    static QPainterPath generateSmoothCurve(const QVector<QPointF> &points) {
        QPainterPath result;

        int segmentStart = 0;
        int i = 0;
        int pointSize = points.size();
        while (i < pointSize) {
            if (qIsNaN(points.at(i).y()) || qIsNaN(points.at(i).x()) || qIsInf(points.at(i).y())) {
              //   QVector<QPointF> lineData(QVector<QPointF>(points.constBegin() + segmentStart, points.constBegin() + i - segmentStart));
               QVector<QPointF> lineData(i - segmentStart); std::copy(points.constBegin() + segmentStart, points.constBegin() + i - segmentStart, lineData.begin()); // 报错的地方 修改成上面的代码 。
                result.addPath(generateSmoothCurveImp(lineData));
                segmentStart = i + 1;
            }
            ++i;
        }
   //     QVector<QPointF> lineData(QVector<QPointF>(points.constBegin() + segmentStart, points.constEnd()));
    QVector<QPointF> lineData(i - segmentStart); std::copy(points.constBegin() + segmentStart, points.constBegin() + i - segmentStart, lineData.begin());
        result.addPath(generateSmoothCurveImp(lineData));
        return result;
    }

    static QPainterPath generateSmoothCurve(const QPainterPath &basePath, const QVector<QPointF> &points) {
        if (points.isEmpty()) return basePath;

        QPainterPath path = basePath;
        int len = points.size();
        if (len == 1) {
            path.lineTo(points.at(0));
            return path;
        }

        QVector<QPointF> firstControlPoints;
        QVector<QPointF> secondControlPoints;
        calculateControlPoints(points, &firstControlPoints, &secondControlPoints);

        path.lineTo(points.at(0));
        for (int i = 0; i < len - 1; ++i)
            path.cubicTo(firstControlPoints[i], secondControlPoints[i], points[i+1]);

        return path;
    }

    static void calculateFirstControlPoints(double *&result, const double *rhs, int n) {
        result = new double[n];
        double *tmp = new double[n];
        double b = 2.0;
        result[0] = rhs[0] / b;

        // Decomposition and forward substitution.
        for (int i = 1; i < n; i++) {
            tmp[i] = 1 / b;
            b = (i < n - 1 ? 4.0 : 3.5) - tmp[i];
            result[i] = (rhs[i] - result[i - 1]) / b;
        }

        for (int i = 1; i < n; i++) {
            result[n - i - 1] -= tmp[n - i] * result[n - i]; // Backsubstitution.
        }

        delete[] tmp;
    }

    static void calculateControlPoints(const QVector<QPointF> &knots,
                                                       QVector<QPointF> *firstControlPoints,
                                                       QVector<QPointF> *secondControlPoints) {
        int n = knots.size() - 1;

        firstControlPoints->reserve(n);
        secondControlPoints->reserve(n);

        for (int i = 0; i < n; ++i) {
            firstControlPoints->append(QPointF());
            secondControlPoints->append(QPointF());
        }

        if (n == 1) {
            // Special case: Bezier curve should be a straight line.
            // P1 = (2P0 + P3) / 3
            (*firstControlPoints)[0].rx() = (2 * knots[0].x() + knots[1].x()) / 3;
            (*firstControlPoints)[0].ry() = (2 * knots[0].y() + knots[1].y()) / 3;

            // P2 = 2P1 – P0
            (*secondControlPoints)[0].rx() = 2 * (*firstControlPoints)[0].x() - knots[0].x();
            (*secondControlPoints)[0].ry() = 2 * (*firstControlPoints)[0].y() - knots[0].y();

            return;
        }

        // Calculate first Bezier control points
        double *xs = nullptr;
        double *ys = nullptr;
        double *rhsx = new double[n]; // Right hand side vector
        double *rhsy = new double[n]; // Right hand side vector

        // Set right hand side values
        for (int i = 1; i < n - 1; ++i) {
            rhsx[i] = 4 * knots[i].x() + 2 * knots[i + 1].x();
            rhsy[i] = 4 * knots[i].y() + 2 * knots[i + 1].y();
        }
        rhsx[0] = knots[0].x() + 2 * knots[1].x();
        rhsx[n - 1] = (8 * knots[n - 1].x() + knots[n].x()) / 2.0;
        rhsy[0] = knots[0].y() + 2 * knots[1].y();
        rhsy[n - 1] = (8 * knots[n - 1].y() + knots[n].y()) / 2.0;

        // Calculate first control points coordinates
        calculateFirstControlPoints(xs, rhsx, n);
        calculateFirstControlPoints(ys, rhsy, n);

        // Fill output control points.
        for (int i = 0; i < n; ++i) {
            (*firstControlPoints)[i].rx() = xs[i];
            (*firstControlPoints)[i].ry() = ys[i];

            if (i < n - 1) {
                (*secondControlPoints)[i].rx() = 2 * knots[i + 1].x() - xs[i + 1];
                (*secondControlPoints)[i].ry() = 2 * knots[i + 1].y() - ys[i + 1];
            } else {
                (*secondControlPoints)[i].rx() = (knots[n].x() + xs[n - 1]) / 2;
                (*secondControlPoints)[i].ry() = (knots[n].y() + ys[n - 1]) / 2;
            }
        }

        delete xs;
        delete ys;
        delete[] rhsx;
        delete[] rhsy;
    }
};
void QCPGraph::drawLinePlot(QCPPainter *painter, const QVector<QPointF> &lines) const
{
    if (painter->pen().style() != Qt::NoPen && painter->pen().color().alpha() != 0) {
        applyDefaultAntialiasingHint(painter);
        if (mSmooth && mLineStyle == lsLine) painter->drawPath(SmoothCurveGenerator::generateSmoothCurve(lines));
        else drawPolyline(painter, lines);
    }
}

class QCP_LIB_DECL QCPGraph : public QCPAbstractPlottable1D<QCPGraphData>
{
public:
    void setSmooth(bool smooth);             // 新增内容
protected:
    bool mSmooth;                            // 新增内容
};
// QCPGraph.cpp源文件
void QCPGraph::setSmooth(bool smooth)
{
    mSmooth = smooth;
}

