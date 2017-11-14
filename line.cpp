#include "line.h"
#include <math.h>
#include <QDebug>
#include <cmath>
#define PI 3.14159265

Line::Line()
{

}

double** Line::init(int n, double* _p[2]){
    this->n = n;
    qDebug() << "p";
    p = new double*[n];
    for(int i = 0; i < n; i++){
        p[i] = new double[2];
        p[i][0] = _p[i][0];
        p[i][1] = _p[i][1];
        qDebug() << p[i][0] << p[i][1];
    }

    // расчет tk (находим хорды между двумя точками)
    qDebug() << "tk";
    double _x;
    double _y;
    double chord;
    t = new double[n-1];
    for(int i = 0; i < n-1;i++){
        _x = pow((p[i+1][0] - p[i][0]),2);
        _y = pow((p[i+1][1] - p[i][1]),2);
        chord = _x+_y;
        chord = pow(chord,0.5);
        t[i] = chord;
        qDebug() << t[i];
    }

    // формируем матрицу M
    qDebug() << "M";
    M = new double*[n];
    for(int i = 0; i < n; i++){
        M[i] = new double[n];
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            M[i][j] = 0;
        }
    }
    M[0][0] = 1;
    M[n-1][n-1] = 1;

    int indent = 0; // отступ. Значение, с которого начинается заполнение числами
    for(int i = 1; i < n-1; i++){
        for(int j = 0; j < n; j++){
            if(j == indent){
                M[i][j] = t[i];
                M[i][j+1] = 2*(t[i-1] + t[i]);
                M[i][j+2] = t[i-1];
                break;
            }
        }
        indent++;
    }
    for(int i = 0; i < n; i++){
            qDebug() << M[i][0] << " " << M[i][1] << " " << M[i][2] << " "
                     << M[i][3]; //<< " " << M[i][4] << " " << M[i][5];

    }
    //qDebug() << "Здесь3";
    // формируем матрицу R
    qDebug() << "R";
    R = new double*[n];
    for(int i = 0; i < n; i++){
        R[i] = new double[2];
    }
    R[0][0] = dP1[0];
    R[0][1] = dP1[1];
    R[n-1][0] = dPn[0];
    R[n-1][1] = dPn[1];

    double firstCoeff;
    double secondCoeef;
    for(int i = 1; i < n-1; i++){
        firstCoeff  = (3*t[i-1])/ t[i];
        secondCoeef = (3*t[i])/(t[i-1]);
        /*qDebug() << firstCoeff << " * (" << p[i+1][0] << " - " << p[i][0] << ")" << " + "
                 << secondCoeef << " * (" << p[i][0]  << " - "  << p[i-1][0] << ")";*/
        R[i][0] = firstCoeff*(p[i+1][0] - p[i][0]) +
                  secondCoeef*(p[i][0] - p[i-1][0]);

        R[i][1] = firstCoeff*(p[i+1][1] - p[i][1]) +
                  secondCoeef*(p[i][1] - p[i-1][1]);
        qDebug() << R[i][0] << " " << R[i][1];
    }

    // находим инвертированную матрицу М
    invM = calcInvertMatrix(n,M);

    // находим значения dP
    qDebug() << "dP";
    dP = new double*[n];
    for(int i = 0; i < n; i++){
        dP[i] = new double[2];
    }
    double value = 0;
    for(int i = 0; i < n; i++){
        for(int k = 0; k < 2; k++){
            for(int j = 0; j < n; j++){
                value += invM[i][j]*R[j][k];
            }
            dP[i][k] = value;
            //dP[i][k] /= 10;
            /*if(i != 0 && i < n-1){
                dP[i][k] /= 10;
            }*/
            value = 0;
        }
        qDebug() << dP[i][0] << " " << dP[i][1];
    }

    return getDots();
}

double** Line::getDots(){
    int count = 100*(n-1);
    double tau;
    double tk;
    double f1;
    double f2;
    double f3;
    double f4;
    double** dots = new double*[count];
    for(int i = 0; i < count; i++){
        dots[i] = new double[2];
    }

    F[0][0] = 2;
    F[0][1] = -3;
    F[0][2] = 1;
    F[1][0] = -2;
    F[1][1] = 3;
    F[1][2] = 0;
    F[2][0] = 1;
    F[2][1] = -2;
    F[2][2] = 1;
    F[3][0] = 1;
    F[3][1] = -1;
    F[3][2] = 0;
    for(int k = 0; k < n-1; k++){
        tk = t[k];
        G[0][0] = p[k][0];
        G[0][1] = p[k][1];
        G[1][0] = p[k+1][0];
        G[1][1] = p[k+1][1];
        G[2][0] = dP[k][0];
        G[2][1] = dP[k][1];
        G[3][0] = dP[k+1][0];
        G[3][1] = dP[k+1][1];
        qDebug() << "tk" << tk;
        qDebug() << "G" << k;
        qDebug() << G[0][0] << " " << G[0][1];
        qDebug() << G[1][0] << " " << G[1][1];
        qDebug() << G[2][0] << " " << G[2][1];
        qDebug() << G[3][0] << " " << G[3][1];

        for(int i = 0; i < 100; i++){
            tau = ((double)i)/100;
            f1 = pow(tau,3)*F[0][0] + pow(tau,2)*F[0][1] +
                    F[0][2];
            f2 = pow(tau,3)*F[1][0] + pow(tau,2)*F[1][1];
            f3 = (pow(tau,3)*F[2][0] + pow(tau,2)*F[2][1] +
                    tau*F[2][2])*tk;
            f4 = (pow(tau,3)*F[3][0] + pow(tau,2)*F[3][1])*tk;

            dots[k*100 + i][0] = f1*G[0][0] + f2*G[1][0] +
                                 f3*G[2][0] + f4*G[3][0];
            dots[k*100 + i][1] = f1*G[0][1] + f2*G[1][1] +
                                 f3*G[2][1] + f4*G[3][1];
            if(i == 33){
                qDebug() << "F1 = " << f1 << "F2 = " << f2 << "F3 = " << f3 << "F4 = " << f4;
                qDebug() << "i = 1/3" << dots[k*100 + i][0] << " " << dots[k*100 + i][1];
            }
            if(i == 66){
                qDebug() << "F1 = " << f1 << "F2 = " << f2 << "F3 = " << f3 << "F4 = " << f4;
                qDebug() << "i = 2/3" << dots[k*100 + i][0] << " " << dots[k*100 + i][1];
            }
    }
    }
    return dots;
}

void Line::createTurnMatrixX(double alphaX){
    turnMatrixX[0][0] = 1;
    turnMatrixX[0][1] = 0;
    turnMatrixX[0][2] = 0;
    turnMatrixX[1][0] = 0;
    turnMatrixX[1][1] = cos(alphaX*PI/180);
    turnMatrixX[1][2] = -sin(alphaX*PI/180);
    turnMatrixX[2][0] = 0;
    turnMatrixX[2][1] = sin(alphaX*PI/180);
    turnMatrixX[2][2] = cos(alphaX*PI/180);
}
void Line::createTurnMatrixY(double alphaY){
    turnMatrixY[0][0] = cos(alphaY*PI/180);
    turnMatrixY[0][1] = 0;
    turnMatrixY[0][2] = sin(alphaY*PI/180);
    turnMatrixY[1][0] = 0;
    turnMatrixY[1][1] = 1;
    turnMatrixY[1][2] = 0;
    turnMatrixY[2][0] = -sin(alphaY*PI/180);
    turnMatrixY[2][1] = 0;
    turnMatrixY[2][2] = cos(alphaY*PI/180);
}

void Line::turnX(double* dot){
    coord[0] = dot[0];
    coord[1] = dot[1];
    coord[2] = 0;
    dot[0] = coord[0]*turnMatrixX[0][0] +
             coord[1]*turnMatrixX[0][1] +
             coord[2]*turnMatrixX[0][2];
    dot[1] = coord[0]*turnMatrixX[1][0] +
             coord[1]*turnMatrixX[1][1] +
             coord[2]*turnMatrixX[1][2];
}

void Line::turnY(double* dot){
    coord[0] = dot[0];
    coord[1] = dot[1];
    coord[2] = 0;
    dot[0] = coord[0]*turnMatrixY[0][0] +
             coord[1]*turnMatrixY[0][1] +
             coord[2]*turnMatrixY[0][2];
    dot[1] = coord[0]*turnMatrixY[1][0] +
             coord[1]*turnMatrixY[1][1] +
             coord[2]*turnMatrixY[1][2];
}

void Line::reset(){
    delete [] t;
    for(int i = 0; i < n; i++){
        delete [] p[i];
        delete [] M[i];
        delete [] invM[i];
        delete [] R[i];
        delete [] dP[i];
    }
    int count = 100*(n-1);
    for(int i = 0; i < count; i++){
        delete [] dots[i];
    }
}

double Line::calcDeterminant(int n, double** matrix){
    // раскрываем определитель по первой строке
    double determinant = 0;
    double coeff;

    for(int i = 0; i < n; i++){
        coeff = matrix[0][i];
        if(coeff != 0){
            if(((i+1)+1)%2 != 0){
                coeff = -coeff;
            }
            if(n-1 >= 2){
                // создаем новую подматрицу
                double** subMatrix = new double*[n-1];
                for(int subi = 0; subi < n-1; subi++){
                    subMatrix[subi] = new double[n-1];
                }
                // заполняем значениями новую подматрицу
                int matrixIndexI = 1;
                int matrixIndexJ = 0;
                int subMatrixIndexI = 0;
                int subMatrixIndexJ = 0;
                double value;
                while(matrixIndexI < n){
                    while(matrixIndexJ < n){
                        if(matrixIndexJ == i){ //  пропускаем столбец
                            matrixIndexJ++;
                            continue;
                        }
                        value = matrix[matrixIndexI][matrixIndexJ];
                        subMatrix[subMatrixIndexI][subMatrixIndexJ] = value;

                        matrixIndexJ++;
                        subMatrixIndexJ++;
                    }
                    matrixIndexJ = 0;
                    subMatrixIndexJ = 0;
                    matrixIndexI++;
                    subMatrixIndexI++;
                }
                determinant+= coeff * calcDeterminant(n-1,subMatrix);
                // удаляем новую подматрицу
                for(int delIndex = 0; delIndex < n-1; delIndex++){
                    delete [] subMatrix[delIndex];
                }

            }else{
                determinant = matrix[0][0] * matrix[1][1] -
                              matrix[1][0] * matrix[0][1];
                break;
            }

        }
    }
    return determinant;
}
double** Line::calcInvertMatrix(int n, double** matrix){
    long double determinant = calcDeterminant(n,matrix);
    invM = new double*[n];
    double** algM = new double*[n];
    double** subMatrix = new double*[n-1];
    for(int i = 0; i < n; i++){
        algM[i] = new double[n];
        invM[i] = new double[n];
    }
    for(int i = 0; i < n-1; i++){
        subMatrix[i] = new double[n-1];
    }

    // находим матрицу алгебраических дополнений
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            // заполняем значениями новую подматрицу(матрицу миноров)
            int matrixIndexI = 0;
            int matrixIndexJ = 0;
            int subMatrixIndexI = 0;
            int subMatrixIndexJ = 0;
            double value;
            while(matrixIndexI < n){
                if(matrixIndexI == i){ // пропускаем строку
                    matrixIndexI++;
                    continue;
                }
                while(matrixIndexJ < n){
                    if(matrixIndexJ == j){ //  пропускаем столбец
                        matrixIndexJ++;
                        continue;
                    }
                    value = matrix[matrixIndexI][matrixIndexJ];
                    subMatrix[subMatrixIndexI][subMatrixIndexJ] = value;

                    matrixIndexJ++;
                    subMatrixIndexJ++;
                }
                matrixIndexJ = 0;
                subMatrixIndexJ = 0;
                matrixIndexI++;
                subMatrixIndexI++;
            }

            algM[i][j] = calcDeterminant(n-1,subMatrix);
            if((i+j+2)%2 != 0){
                algM[i][j] = -algM[i][j];
            }
        }
    }

    // транспонируем матрицу алгебраических дополнений
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            invM[j][i] = algM[i][j];
        }
    }

    // делим элементы конечной матрицы на определитель(находим обратную матрицу)
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            invM[j][i] /= determinant;
        }
    }
    for(int i = 0; i < n; i++){
        delete [] algM[i];
    }
    for(int i = 0; i < n-1; i++){
        delete[] subMatrix[i];
    }

    return invM;
}

