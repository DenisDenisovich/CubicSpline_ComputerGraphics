#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <line.h>
#include <QList>
/*struct dot{
    double x;
    double y;
};*/

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    virtual void 	mousePressEvent (QMouseEvent *event); 


private:
    Ui::MainWindow *ui;
    Line line;

    static const int MIN_N = 6;
    static const int MAX_N = 10;
    int n = MIN_N;
    //double dot[2];
    //QList<dot> dotList;
    double **dots; // first index - number of dot. second index (0 - x, 1 - y)
    double **graph;
    double **turnDots;
    double **turnGraph;
    int xAlpha;
    int yAlpha;
    // координаты OX+
    int planeAbscissaX1 = 750;
    int planeAbscissaX2 = 1350;
    int planeAbscissaY1 = 350;
    int planeAbscissaY2 = 350;
    // координаты OY+
    int planeOrdinateX1 = 750;
    int planeOrdinateX2 = 750;
    int planeOrdinateY1 = 350;
    int planeOrdinateY2 = 25;

    bool p1xBool, p1yBool, p2xBool, p2yBool, p3xBool, p3yBool,
         p4xBool, p4yBool, p5xBool, p5yBool, p6xBool, p6yBool,
         p7xBool, p7yBool, p8xBool, p8yBool, p9xBool, p9yBool,
         p10xBool, p10yBool,
         xAlphaBool, yAlphaBool;
    bool lineBool[MAX_N];
    bool graphIsReady = false;
    bool turnGraphIsReady = false;
    bool turnDotsISReady = false;
private slots:
    void createSpline();
    void editDots();
    void setN();
    void setP1();
    void setP2();
    void setP3();
    void setP4();
    void setP5();
    void setP6();
    void setP7();
    void setP8();
    void setP9();
    void setP10();

    void turnX();
    void turnY();
    void reset();
};

#endif // MAINWINDOW_H
