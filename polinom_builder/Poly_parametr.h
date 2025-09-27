#ifndef POLY_PARAMETR_H
#define POLY_PARAMETR_H

#include "qcolor.h"
#include <QVector>


struct Poly_parameters
{
    double x_y_inv_optimalDegree;
    QVector<double> timeArray;
    QVector<double> levelArray;
    QVector<double> x_y_inv_koeffss;
    QVector<double> timeArrayAppr;
    QVector<double> levelArrayAppr;
    QVector<int> newRow;

};

extern Poly_parameters poly_parameters;
QVector<QColor> dataLineColors_vent_identf;



#endif // POLY_PARAMETR_H
