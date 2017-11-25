#ifndef LINE_H
#define LINE_H


class Line
{
private:
    int n;
    double dP1[2] = {0.1,0.1};
    double dPn[2] = {0.1,0.1};
    double **p;
    double *t;
    double **dP;   //nx1
    // матрицы для расчета dP
    double **M;  //nxn
    double **invM;
    double **R;  //nx2
    // матрица для расчета весовых коэффициентов
    double F[4][3];
    // Gt = Pk, Pk+1, P'k, P'k+1
    double G[4][2];
    double ** dots;
    double calcDeterminant(int, double**);
    double** calcInvertMatrix(int,double**);
    double coord[3]; // координаты для поворота вокруг осей
    double turnMatrixX[3][3]; // матрица поворота для оси X
    double turnMatrixY[3][3]; // матрица поворота для оси Y

public:
    Line();
    double** init(int, double**);
    double** getDots();
    void createTurnMatrixX(double);
    void createTurnMatrixY(double);
    void turnX(double*);
    void turnY(double*);
    void reset();

};

#endif // LINE_H
