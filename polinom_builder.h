#ifndef POLINOM_BUILDER_H
#define POLINOM_BUILDER_H

#include "ui_polinom_builder.h"
#include <QChart>
#include <QLineSeries>
#include <QMainWindow>
#include <QValueAxis>
#include <QComboBox>
#include <QLocalServer>
#include <QVector>
#include <QTableWidgetItem>
#include <QLocalSocket>

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

    struct Data
    {
        QVector<double> coff; // Используем вектор для хранения значений
    };

protected slots:
    void applybutton();
    void closebutton();
    void plotGraph();
    void clearButton();
    void resultButton();
    void saveButton();
    bool savePointsToXml(const QString &fileName);
    bool saveKoeffsToXml(const QString &fileName);
    void loadButton();
    bool loadPointsFromXml();
    void polinomButtons();

    void onComboBoxChanged(int index);
    void updateButtonState();
    void clearButton_approx();
    void polinomButton_approx();
    void saveApproxButton();
    void sendData();

    void onLineEditTextChanged(const QString &text);
private:
    Ui::Polinom_builder *ui;
    QChart *chart, *chart_approx;
    QLineSeries *series, *series_approx;
    QLineSeries *splineSeries;
    QValueAxis *axisX, *axisX_approx;
    QValueAxis *axisY, *axisY_approx;
    void addRows();
    void clearTableExceptFirstRow();
    void save_vent_identf();
    QString QRegExp(const char *);
    QLocalServer *server;
    QLocalSocket *socket;
};
#endif // POLINOM_BUILDER_H
