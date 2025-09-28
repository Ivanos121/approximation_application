#include "polinom_builder.h"
#include "ui_polinom_builder.h"
#include "Poly_parametr.h"
#include "polynomial.h"
#include "plot.h"

#include <QGraphicsLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QXmlStreamWriter>
#include <iostream>
#include <QVector>
#include <stdio.h>
#include <gsl/gsl_multifit.h>
#include <gsl/gsl_blas.h>
#include <QFileInfo>
#include <QMessageBox>
#include <QSettings>
#include <algorithm>

Poly_parameters poly_parameters;

Polinom_builder::Polinom_builder(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Polinom_builder)
{
    ui->setupUi(this);

    ui->label_5->setWordWrap(true);
    ui->label_5->setText("<html><head/><body><p><span style=\" font-size:12pt; font-weight:700;\">Рассчитанные коэффициенты<br>аппроксимации</span></p></body></html>");
    ui->saveButton->setText("Сохранить график");
    ui->lineEdit->setText("2");
    ui->label_6->setText("<html>Степень<br>аппроксимации</html>");
    ui->label_8->setText("<html>Выбор ввода<br>степени аппроксимации</html>");
    ui->statusbar->setVisible(false);


    ui->plot->t_max = 10.0;
    ui->plot->U_max = 10.0;
    ui->plot->margin_bottom = 40;
    ui->plot->margin_left = 100;
    ui->plot->reset();

    dataLineColors_vent_identf.append(Qt::red);

    connect(ui->applyButton, &QPushButton::clicked, this, &Polinom_builder::applybutton);
    connect(ui->closeButton, &QPushButton::clicked, this, &Polinom_builder::closebutton);
    connect(ui->plotGraph, &QPushButton::clicked, this, &Polinom_builder::plotGraph);
    connect(ui->clearButton, &QPushButton::clicked, this, &Polinom_builder::clearButton);
    connect(ui->resultButton, &QPushButton::clicked, this, &Polinom_builder::resultButton);
    connect(ui->saveButton, &QPushButton::clicked, this, &Polinom_builder::saveButton);
    connect(ui->loadButton, &QPushButton::clicked, this, &Polinom_builder::loadButton);
    connect(ui->polinomButton, &QPushButton::clicked, this, &Polinom_builder::polinomButtons);
    connect(ui->comboBox, &QComboBox::currentIndexChanged, this, &Polinom_builder::onComboBoxChanged);

    chart = new QChart();
    chart->layout()->setContentsMargins(0,0,0,0);
    chart->setTitle(" ");

    // Создаем серию данных
    series = new QLineSeries();
    chart->addSeries(series);

    // Удаляем легенду из графика
    chart->legend()->hide();

    // Создаем оси
    axisX = new QValueAxis();
    axisX->setTitleText("Ось X (Время)");
    axisX->setRange(0, 3); // Устанавливаем диапазон оси X

    axisY = new QValueAxis();
    axisY->setTitleText("Ось Y (Уровень)");
    axisY->setRange(0, 10); // Устанавливаем диапазон оси Y

    // Добавляем оси к графику
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    // Устанавливаем график в QChartView
    ui->chartView->setChart(chart);

   // Заполняем QComboBox отдельными элементами
    ui->comboBox->addItem("Ввести вручную");
    ui->comboBox->addItem("Расчитать автоматически");


    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(3);
    QStringList name_6;
    name_6 << " № " << "Сигнал" << "Величина";
    ui->tableWidget->setHorizontalHeaderLabels(name_6);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget->setColumnWidth(0, 100);
    ui->tableWidget->setColumnWidth(1, 400);

    for(int row = 0; row<ui->tableWidget->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget->columnCount(); column++)
        {
            ui->tableWidget->setItem(row, column, new QTableWidgetItem());

        }
    }

    for (int i=0; i<8; i++)
    {
        if (ui->tableWidget->item(i, 0) != 0)
        {
            ui->tableWidget->item(i, 0)->setText(QString("%1").arg(i+1));
            ui->tableWidget->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        }
    }

    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(" "));
}

Polinom_builder::~Polinom_builder()
{
    delete ui;
}

void Polinom_builder::applybutton()
{
    close();
}

void Polinom_builder::closebutton()
{
    close();
}

void Polinom_builder::plotGraph()
{
    // Проверяем, есть ли данные в серии
    if (series->count() == 0)
    {
        QMessageBox::warning(this, "Внимание!", "Нет данных для построения");
        return; // Выход из функции, если данных нет
    }

    // Считываем значения из QLineEdit
    QString timeText = ui->lineEditX->text();
    QString levelText = ui->lineEditY->text();

    // Отладочные сообщения
    qDebug() << "Введенные значения для времени:" << timeText;
    qDebug() << "Введенные значения для уровня:" << levelText;

    // Разделяем строки на массивы чисел
    QStringList timeValues = timeText.split(' ', Qt::SkipEmptyParts);
    QStringList levelValues = levelText.split(' ', Qt::SkipEmptyParts);

    // Преобразуем строки в числа для времени
    for (const QString &value : std::as_const(timeValues))
    {
        QString cleanedValue = value;
        cleanedValue.remove('[').remove(']'); // Удаляем квадратные скобки
        cleanedValue = cleanedValue.trimmed(); // Удаляем пробелы

        bool ok;
        double timeValue = cleanedValue.toDouble(&ok);
        if (ok)
        {
            poly_parameters.timeArray.append(timeValue);
        }
        else
        {
            qDebug() << "Ошибка преобразования строки:" << cleanedValue;
        }
    }

    // Преобразуем строки в числа для уровня
    for (const QString &value : std::as_const(levelValues))
    {
        QString cleanedValue = value; // Создаем копию строки
        cleanedValue.remove('[').remove(']'); // Удаляем квадратные скобки
        cleanedValue = cleanedValue.trimmed(); // Удаляем пробелы

        bool ok;
        double levelValue = cleanedValue.toDouble(&ok);
        if (ok)
        {
            poly_parameters.levelArray.append(levelValue);
        }
        else
        {
            qDebug() << "Ошибка преобразования строки уровня:" << cleanedValue;
        }
    }

    // Отладочные сообщения
    qDebug() << "Time Array:" << poly_parameters.timeArray;
    qDebug() << "Level Array:" << poly_parameters.levelArray;

    // Проверяем, что массивы имеют одинаковый размер
    if (poly_parameters.timeArray.size() != poly_parameters.levelArray.size()) {
        // Проверяем, есть ли возможность исправить размерности
        if (poly_parameters.timeArray.size() == 0 || poly_parameters.levelArray.size() == 0)
        {
            QMessageBox::warning(this, "Внимание!", "Ошибка: Один из массивов пуст.");
        } else
        {
            QMessageBox::warning(this, "Внимание!", "Ошибка: Массивы не совпадают по размеру.");
        }
        return; // Обработка ошибки: массивы не совпадают по размеру
    }

    // Удаляем предыдущую серию, если она существует
    if (ui->chartView->chart()->series().size() > 0)
    {
        ui->chartView->chart()->removeAllSeries();
    }

    // Создаем серию для графика
    series = new QLineSeries();

    for (int i = 0; i < poly_parameters.timeArray.size(); ++i)
    {
        series->append(poly_parameters.timeArray[i], poly_parameters.levelArray[i]);
        //series->append(poly_parameters.timeArray[i], poly_parameters.levelArray[i]);
    }


    // Добавляем серию к графику
    ui->chartView->chart()->addSeries(series);
    ui->chartView->chart()->createDefaultAxes();

    // Проверяем, что массивы не пустые перед установкой диапазонов осей
    if (poly_parameters.timeArray.isEmpty() || poly_parameters.levelArray.isEmpty())
    {
        QMessageBox::warning(this, "Внимание!", "Ошибка: Один из массивов пуст. Диапазоны осей не будут установлены.");
    }
    else
    {
        ui->chartView->chart()->axes(Qt::Horizontal).first()->setRange(*std::min_element(poly_parameters.timeArray.begin(), poly_parameters.timeArray.end()),
                                                                       *std::max_element(poly_parameters.timeArray.begin(), poly_parameters.timeArray.end()));
        ui->chartView->chart()->axes(Qt::Vertical).first()->setRange(*std::min_element(poly_parameters.levelArray.begin(), poly_parameters.levelArray.end()),
                                                                     *std::max_element(poly_parameters.levelArray.begin(), poly_parameters.levelArray.end()));
    }

    // Подписываем оси
    auto xAxis = qobject_cast<QValueAxis *>(ui->chartView->chart()->axes(Qt::Horizontal).first());
    if (xAxis)
    {
        xAxis->setTitleText("Ось X (Время)"); // Подпись для оси X
    }

    auto yAxis = qobject_cast<QValueAxis *>(ui->chartView->chart()->axes(Qt::Vertical).first());
    if (yAxis)
    {
        yAxis->setTitleText("Ось Y (Уровень)"); // Подпись для оси Y
    }

    // Отладочное сообщение о завершении
    qDebug() << "График обновлен.";
}

void Polinom_builder::clearButton()
{
    // Проверяем, есть ли данные в серии
    if (series->count() == 0)
    {
        QMessageBox::warning(this, "Внимание!", "Нет данных для очистки");
        return; // Выход из функции, если данных нет
    }

    // Удаляем все серии из графика
    if (ui->chartView->chart())
    {
        ui->chartView->chart()->removeAllSeries();
    }

    // Удаляем оси (если необходимо)
    auto axes = ui->chartView->chart()->axes();

    for (auto axis : std::as_const(axes))
    {
        ui->chartView->chart()->removeAxis(axis);// Удаляем все серии из графика
    }

    // Очистка QLineEdit (если необходимо)
    ui->lineEditX->clear();
    ui->lineEditY->clear();

    // Восстанавливаем квадратные скобки в QLineEdit
    ui->lineEditX->setText("[]"); // Восстанавливаем квадратные скобки для времени
    ui->lineEditY->setText("[]"); // Восстанавливаем квадратные скобки для уровня

    // Создаем новую серию
    series = new QLineSeries();

    // Создаем новые оси
    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;

    // Устанавливаем диапазоны для осей (можно настроить по вашему усмотрению)
    axisX->setRange(0, 10); // Пример диапазона для оси X
    axisY->setRange(0, 10); // Пример диапазона для оси Y

    // Добавляем оси в график
    ui->chartView->chart()->addAxis(axisX, Qt::AlignBottom);
    ui->chartView->chart()->addAxis(axisY, Qt::AlignLeft);

    // Настройка сетки
    axisX->setGridLineVisible(true);
    axisY->setGridLineVisible(true);

    // Привязываем оси к серии (если серия уже существует)
    if (series)
    {
        series->attachAxis(axisX);
        series->attachAxis(axisY);
    }

    // Подписываем оси
    auto xAxis = qobject_cast<QValueAxis *>(ui->chartView->chart()->axes(Qt::Horizontal).first());
    if (xAxis) {
        xAxis->setTitleText("Ось X (Время)"); // Подпись для оси X
    }

    auto yAxis = qobject_cast<QValueAxis *>(ui->chartView->chart()->axes(Qt::Vertical).first());
    if (yAxis) {
        yAxis->setTitleText("Ось Y (Уровень)"); // Подпись для оси Y
    }

    // Отладочное сообщение
    qDebug() << "График очищен и поля ввода восстановлены.";
    clearTableExceptFirstRow();
}

void Polinom_builder::resultButton()
{
    // Проверяем, есть ли данные в серии
    if (series->count() == 0)
    {
        QMessageBox::warning(this, "Внимание!", "Нет данных для расчета");
        return; // Выход из функции, если данных нет
    }

    clearTableExceptFirstRow();
    QString selectedText = ui->comboBox->currentText(); // Получаем текст текущего элемента
    poly_parameters.x_y_inv_optimalDegree = -1;

    if(selectedText == "Ввести вручную")
    {
        poly_parameters.x_y_inv_optimalDegree = ui->lineEdit->text().toInt();

    }
    else if(selectedText == "Расчитать автоматически")
    {
        poly_parameters.x_y_inv_optimalDegree = bestDegree(poly_parameters.timeArray, poly_parameters.levelArray);

    }

    int k = poly_parameters.levelArray.size();


    poly_parameters.levelArrayAppr.resize(k);


    poly_parameters.x_y_inv_koeffss = approximate(poly_parameters.timeArray, poly_parameters.levelArray, poly_parameters.x_y_inv_optimalDegree);

    for (int i = 0; i < poly_parameters.x_y_inv_koeffss.size(); ++i)
    {
        qDebug() << "koefficient[" << i << "] =" << poly_parameters.x_y_inv_koeffss[i];
    }

    Polynomial x_y_inv_poly(poly_parameters.x_y_inv_koeffss);

    for(int i = 0; i < poly_parameters.timeArray.size(); ++i)
    {
        poly_parameters.levelArrayAppr[i] = x_y_inv_poly.evaluate(poly_parameters.timeArray[i]);
    }

    // Создаем новую серию
    QLineSeries *newSeries = new QLineSeries();

    for (int i = 0; i < poly_parameters.timeArray.size(); ++i)
    {
        newSeries->append(poly_parameters.timeArray[i], poly_parameters.levelArray[i]);
    }

    // Добавляем новую серию в график
    chart->addSeries(newSeries);

    // Устанавливаем стиль для новой серии (например, цвет)
    newSeries->setName("Новая серия"); // Устанавливаем имя для новой серии
    newSeries->setPen(QPen(Qt::blue)); // Устанавливаем цвет линии

    // Обновляем оси, если необходимо
    chart->createDefaultAxes(); // Создает оси для новой серии, если они еще не созданы

    // Подписываем оси
    auto xAxis = qobject_cast<QValueAxis *>(ui->chartView->chart()->axes(Qt::Horizontal).first());
    if (xAxis)
    {
        xAxis->setTitleText("Ось X (Время)"); // Подпись для оси X
    }

    auto yAxis = qobject_cast<QValueAxis *>(ui->chartView->chart()->axes(Qt::Vertical).first());
    if (yAxis)
    {
        yAxis->setTitleText("Ось Y (Уровень)"); // Подпись для оси Y
    }


    // Принудительно обновляем график
    ui->chartView->setChart(chart);

    addRows();
    save_vent_identf();
    ui->plot->clear();
}

void Polinom_builder::saveButton()
{
    // Проверяем, есть ли данные в серии
    if (series->count() == 0)
    {
        QMessageBox::warning(this, "Внимание!", "Нет данных для сохранения");
        return; // Выход из функции, если данных нет
    }

    QString str;
    QString filter = "Данные сигнала скорости (*.xml);;Все файлы (*.*)";
    QString selectedFilter;  // Переменная для хранения выбранного фильтра
    QString initialPath = "/home/elf/ImView2_Qt6/Reference materials"; // Замените на нужный путь


    str = QFileDialog::getSaveFileName(this, "Выбрать имя, под которым сохранить данные", initialPath
                                       , filter, &selectedFilter);
    if (!str.isEmpty())
    {
        if (selectedFilter == "Данные сигнала скорости (*.xml)" && !str.endsWith(".xml"))
        {
            str += ".xml";
        }
    }

    bool saved = savePointsToXml(str);
    if (saved)
    {
        qDebug() << "Данные успешно сохранены в XML";
    }
    else
    {
        qDebug() << "Ошибка сохранения XML";
    }
}

bool Polinom_builder::savePointsToXml(const QString &fileName)
{
    QString str = fileName;

    QFile file(str);
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();
    xml.writeStartElement("Points");  // Корневой элемент

    // Получаем точки из серии
    const auto points = series->points();

    for (const QPointF &pt : points)
    {
        xml.writeStartElement("Point");
        xml.writeAttribute("x", QString::number(pt.x()));
        xml.writeAttribute("y", QString::number(pt.y()));
        xml.writeEndElement(); // Point
    }

    xml.writeEndElement(); // Points
    xml.writeEndDocument();

    file.close();
    qDebug() << "Сохранено точек:" << points.size();
    return true;
}

void Polinom_builder::loadButton()
{
    QVector<QPointF> loadedData;
    bool loaded = loadPointsFromXml();
    if (loaded)
    {
        qDebug() << "Данные успешно загружены из XML, точек:" << loadedData.size();
        // Можно обновить график: series->replace(loadedData); или аналогично
    }
    else
    {
        qDebug() << "Ошибка загрузки XML";
    }
}

bool Polinom_builder::loadPointsFromXml()
{
    QVector<QPointF> points;

    QString filter = "Данные сигнала скорости (*.xml);;Все файлы (*.*)";
    QString initialPath = "../ImView2_Qt6/Reference materials";

    QString str = QFileDialog::getOpenFileName(this, "Выбрать имя, под которым загрузить данные", initialPath
                                       , filter);

    // Открываем файл
    QFile file(str);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Не удалось открыть файл" << str;
        return false;
    }

    // Создаём XML-ридер
    QXmlStreamReader xml(&file);

    // Читаем XML
    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::StartElement && xml.name() == QStringLiteral("Point"))
        {
            // Извлекаем атрибуты x и y
            QString xStr = xml.attributes().value("x").toString();
            QString yStr = xml.attributes().value("y").toString();

            bool okX, okY;
            double x = xStr.toDouble(&okX);
            double y = yStr.toDouble(&okY);

            if (okX && okY)
            {
                points.append(QPointF(x, y));
            } else
            {
                qWarning() << "Неверный формат точки в XML:" << xStr << yStr;
            }
        }
    }

    // Проверяем на ошибки чтения
    if (xml.hasError())
    {
        qWarning() << "Ошибка чтения XML:" << xml.errorString();
        file.close();
        return false;
    }

    file.close();

    // Если точек нет, ничего не делаем
    if (points.isEmpty())
    {
        qWarning() << "В файле нет точек";
        return false;
    }

    // Создаем QStringList для хранения всех значений x и y
    QStringList xList;
    QStringList yList;

    for (const QPointF &point : points)
    {
        // Добавляем значения x и y в соответствующие списки
        xList.append(QString::number(point.x()));
        yList.append(QString::number(point.y()));
    }

    // Устанавливаем все значения x в первый QLineEdit с квадратными скобками
    QString xValues = QString("[%1]").arg(xList.join(" ")); // Добавляем квадратные скобки
    ui->lineEditX->setText(xValues); // Устанавливаем все значения X

    // Устанавливаем все значения y во второй QLineEdit с квадратными скобками
    QString yValues = QString("[%1]").arg(yList.join(" ")); // Добавляем квадратные скобки
    ui->lineEditY->setText(yValues); // Устанавливаем все значения Y


    // Убедитесь, что series инициализирован
    if (series)
    {
        series = new QLineSeries(); // Создаем новый экземпляр серии
        qDebug() << "Серия обновлена новыми точками.";
    }
    else
    {
        qWarning() << "Серия не инициализирована, не удалось обновить.";
        return false;
    }

    // Обновляем серию
    //series->clear();  // Очищаем старую серию
    series->replace(points);  // Добавляем новые точки

    poly_parameters.timeArray.clear();
    poly_parameters.levelArray.clear();
    for (const auto point : std::as_const(points))
    {
        poly_parameters.timeArray.append(point.x());
        poly_parameters.levelArray.append(point.y());
    }


    // Принудительно обновляем график
    if (chart->series().contains(series))
    {
        chart->removeSeries(series);  // Удаляем, чтобы пересоздать
    }

    // Удаляем старые оси
    const auto axes = chart->axes();
    for (QAbstractAxis *axis : axes)
    {
        chart->removeAxis(axis);
    }

    chart->addSeries(series);

    // Создаём и настраиваем оси
    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;

    double minX = points.first().x(), maxX = points.first().x();
    double minY = points.first().y(), maxY = points.first().y();

    for (const QPointF &p : std::as_const(points))
    {
        if (p.x() < minX) minX = p.x();
        if (p.x() > maxX) maxX = p.x();
        if (p.y() < minY) minY = p.y();
        if (p.y() > maxY) maxY = p.y();
    }

    axisX->setRange(minX, maxX);
    axisY->setRange(minY, maxY);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->legend()->hide();

    series->attachAxis(axisX);
    series->attachAxis(axisY);

    ui->chartView->setChart(chart);
    ui->chartView->repaint();

    // Подписываем оси
    auto xAxis = qobject_cast<QValueAxis *>(ui->chartView->chart()->axes(Qt::Horizontal).first());
    if (xAxis) {
        xAxis->setTitleText("Ось X (Время)"); // Подпись для оси X
    }

    auto yAxis = qobject_cast<QValueAxis *>(ui->chartView->chart()->axes(Qt::Vertical).first());
    if (yAxis) {
        yAxis->setTitleText("Ось Y (Уровень)"); // Подпись для оси Y
    }

    return true;
}

QVector<double> Polinom_builder::approximate(const QVector<double>& x, const QVector<double>& y, size_t degree)
{
    degree++;
    QVector<double> koeffs(degree);

    // Проверка на корректность входных данных
    if (x.size() != y.size() || x.size() == 0)
    {
        printf("Ошибка: размеры векторов x и y должны совпадать и быть больше нуля.\n");
        return koeffs;
    }

    for (int i = 0; i < poly_parameters.timeArray.size(); ++i)
    {
        std::cout << x[i] << " " << y[i] << std::endl;
    }
    std::cout << std::endl;

    size_t n = x.size();

    // Создаем gsl матрицы и векторы
    gsl_matrix *X = gsl_matrix_alloc(n, degree);
    gsl_vector *Y = gsl_vector_alloc(n);
    gsl_vector *c = gsl_vector_alloc(degree); // параметры модели
    gsl_matrix *cov = gsl_matrix_alloc(degree, degree);

    // Заполняем X матрицу значениями
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < degree; j++)
        {
            gsl_matrix_set(X, i, j, pow(x[i], j));
        }
        gsl_vector_set(Y, i, y[i]);
    }

    qDebug() << X << " " << Y << Qt::endl;

    // Выполняем аппроксимацию методом наименьших квадратов
    gsl_multifit_linear_workspace *work = gsl_multifit_linear_alloc(n, degree);
    double chisq;

    int status = gsl_multifit_linear(X, Y, c, cov, &chisq, work);
    if (status != GSL_SUCCESS)
    {
        printf("Ошибка при вычислении аппроксимации\n");
        return koeffs;
    }

    // Вывод полученных коэффициентов
    //printf("Коэффициенты полинома:\n");
    for (size_t j=0; j<degree; j++)
    {
        koeffs[j] = gsl_vector_get(c,j);
        printf("a_%zu = %g\n", j, gsl_vector_get(c,j));
    }
    //printf("Отклонение (chisq): %g\n", chisq);

    // Используем модель для оценки новых значений
    double x_eval = x[0];
    double y_eval = 0;
    for (size_t j=0; j<degree; j++)
    {
        y_eval += gsl_vector_get(c,j) * pow(x_eval,j);
    }
    printf("Оценка в точке x=%.2f: y=%.2f\n", x_eval,y_eval);

    // Освобождение ресурсов
    gsl_multifit_linear_free(work);
    gsl_matrix_free(X);
    gsl_vector_free(Y);
    gsl_vector_free(c);
    gsl_matrix_free(cov);

    return koeffs;
}

double Polinom_builder::computeError(const QVector<double>& x,
                                 const QVector<double>& y,
                                 const QVector<double>& coeffs)
{
    double error_sum=0;
    int degree=coeffs.size()-1;

    for(int i=0;i<x.size();++i)
    {
        double y_pred=0;
        for(int j=0;j<=degree;++j)
            y_pred+=coeffs[j]*std::pow(x[i],j);
        double diff=y[i]-y_pred;
        error_sum+=diff*diff;
    }
    return std::sqrt(error_sum/x.size()); // среднеквадратичная ошибка
}

int Polinom_builder::bestDegree(const QVector<double>& x, const QVector<double>& y)
{
    int maxDegree=5;
    double bestError=std::numeric_limits<double>::max();
    int bestDegree=1;

    for(int degree=1;degree<=maxDegree;++degree)
    {
        auto coeffs = approximate(x, y, degree);
        double err=computeError(x, y, coeffs);
        std::cout<<"Степень "<<degree<<" ошибка "<<err<<std::endl;

        if (err < 1e-10)
        {
            bestError=err;
            bestDegree=degree;
            break;
        }

        if(err<bestError)
        {
            bestError=err;
            bestDegree=degree;
        }
    }

    std::cout<<"Оптимальная степень: "<<bestDegree<<", ошибка: "<<bestError<<std::endl;
    return bestDegree;
}

void Polinom_builder::addRows()
{
    int rowCount = poly_parameters.x_y_inv_koeffss.size();
    int currentRowCount = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(currentRowCount + rowCount); // Устанавливаем новое количество строк

    // Заполняем новые строки данными
    for (int i = 0; i < rowCount; ++i)
    {
        int newRow = currentRowCount + i; // Индекс новой строки

        // Устанавливаем элемент в первую колонку
        QTableWidgetItem *item0 = new QTableWidgetItem(QString::number(newRow + 1)); // +1 для отображения с 1
        ui->tableWidget->setItem(newRow, 0, item0);

        // Устанавливаем элемент во вторую колонку
        QTableWidgetItem *item1 = new QTableWidgetItem(QString("Коэффициент [ %1 ]").arg(newRow + 1));
        ui->tableWidget->setItem(newRow, 1, item1);

        // Устанавливаем элемент в третью колонку
        QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(poly_parameters.x_y_inv_koeffss[i]));
        ui->tableWidget->setItem(newRow, 2, item2);
    }
    for (int i = 0; i < currentRowCount + rowCount; i ++)
    {
        if (ui->tableWidget->item(i, 0) != 0)
        {
            ui->tableWidget->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget->item(i, 2) != 0)
        {
            ui->tableWidget->item(i, 2)->setTextAlignment(Qt::AlignCenter);
        }
    }
}

void Polinom_builder::clearTableExceptFirstRow()
{
    // // Очистка содержимого таблицы, кроме заголовков и первой строки
    // for (int row = 0; row < ui->tableWidget->rowCount(); ++row) // Начинаем с 1, чтобы пропустить первую строку
    // {
    //     for (int col = 0; col < ui->tableWidget->columnCount(); ++col)
    //     {
    //         QTableWidgetItem *item = ui->tableWidget->item(row, col);
    //         if (item)
    //         {
    //             delete item; // Удаляем элемент
    //         }
    //     }
    // }

    // // Устанавливаем количество строк в 1, чтобы оставить только заголовки и первую строку
    // // ui->tableWidget->setRowCount(1);

    // Удаляем все строки, кроме первой
    int rowCount = ui->tableWidget->rowCount();
    for (int row = rowCount - 1; row >= 0; --row) // Начинаем с последней строки и идем вверх
    {
        ui->tableWidget->removeRow(row); // Удаляем строку
    }
}

void Polinom_builder::save_vent_identf()
{
    QFile file(QString("/home/elf/wers/polinom_builder/build/Desktop-Debug/vent_identf.xml"));
    file.open(QIODevice::WriteOnly);

    //Создаем объект, с помощью которого осуществляется запись в файл
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);  // Устанавливаем автоформатирование текста
    xmlWriter.writeStartDocument();     // Запускаем запись в документ
    xmlWriter.writeStartElement("resources");   // Записываем первый элемент с его именем
    xmlWriter.writeStartElement("vent_identf");  // Записываем тег с именем для первого итема
    xmlWriter.writeStartElement("general_settings");

    for (int i = 0; i < poly_parameters.x_y_inv_koeffss.size(); ++i)
    {
        xmlWriter.writeStartElement("koefficient_1_" + QString::number(i));
        xmlWriter.writeAttribute("value", QString::number(poly_parameters.x_y_inv_koeffss[i]));
        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();
}

void Polinom_builder::polinomButtons()
{
    // Проверяем, есть ли данные в серии
    if (series->count() == 0)
    {
        QMessageBox::warning(this, "Внимание!", "Нет данных для построения графика");
        return; // Выход из функции, если данных нет
    }

    ui->plot->t_max = poly_parameters.timeArray[poly_parameters.timeArray.size()-1];
    ui->plot->U_max = poly_parameters.levelArray[poly_parameters.levelArray.size()-1];
    ui->plot->margin_bottom = 40;
    ui->plot->margin_left = 100;
    ui->plot->reset();

    ui->plot->clear();
    ui->plot->addDataLine(QColor(255,0,0), 0);

    Polynomial x_y_inv_poly(poly_parameters.x_y_inv_koeffss);

    for (int i = 0; i < 1000; i++)
    {
        double xx = poly_parameters.timeArray[poly_parameters.timeArray.size()-1] / (1000.0 - 1.0) * i;
        double z = x_y_inv_poly.evaluate(xx);
        ui->plot->addPoint(0,xx, z);
    }
}

void Polinom_builder::onComboBoxChanged(int index)
{
    // Предположим, что второй пункт имеет индекс 1
    if (index == 1)
    {
        ui->lineEdit->setDisabled(true);   // делаем недоступным
    }
    else
    {
        ui->lineEdit->setDisabled(false);  // делаем доступным
    }
}
