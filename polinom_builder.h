#ifndef POLINOM_BUILDER_H
#define POLINOM_BUILDER_H

#include <QChart>
#include <QLineSeries>
#include <QMainWindow>
#include <QValueAxis>
#include <QComboBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class Polinom_builder;
}
QT_END_NAMESPACE

class Polinom_builder : public QMainWindow
{
    Q_OBJECT

public:
    Polinom_builder(QWidget *parent = nullptr);
    ~Polinom_builder();

    double computeError(const QVector<double> &x, const QVector<double> &y, const QVector<double> &coeffs);
    QVector<double> approximate(const QVector<double> &x, const QVector<double> &y, size_t degree);
    int bestDegree(const QVector<double> &x, const QVector<double> &y);
protected slots:
    void applybutton();
    void closebutton();
    void plotGraph();
    void clearButton();
    void resultButton();
    void saveButton();
    bool savePointsToXml(const QString &fileName);
    void loadButton();
    bool loadPointsFromXml();
    void polinomButtons();

    void onComboBoxChanged(int index);
private:
    Ui::Polinom_builder *ui;
    QChart *chart;
    QLineSeries *series;
    QValueAxis *axisX;
    QValueAxis *axisY;
    void addRows();
    void clearTableExceptFirstRow();
    void save_vent_identf();
};
#endif // POLINOM_BUILDER_H
