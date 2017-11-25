#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"
#include <QMouseEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    dots = new double*[MAX_N];
    turnDots = new double*[MAX_N];
    for(int i = 0; i < MAX_N; i++){
        dots[i] = new double[2];
        turnDots[i] = new double[2];
        lineBool[i] = false;
    }
    graph = new double*[(MAX_N-1)*100];
    turnGraph = new double*[(MAX_N -1)*100];
    for(int i = 0; i < (MAX_N-1)*100; i++){
        graph[i] = new double[2];
        turnGraph[i] = new double[2];
    }
    ui->setupUi(this);
    setWindowTitle("Lab2");
    showMaximized();
    setMouseTracking(true);

    connect(ui->p1x, SIGNAL(textChanged(QString)),this,SLOT(setP1()));
    connect(ui->p1y, SIGNAL(textChanged(QString)),this,SLOT(setP1()));
    connect(ui->p2x, SIGNAL(textChanged(QString)),this,SLOT(setP2()));
    connect(ui->p2y, SIGNAL(textChanged(QString)),this,SLOT(setP2()));
    connect(ui->p3x, SIGNAL(textChanged(QString)),this,SLOT(setP3()));
    connect(ui->p3y, SIGNAL(textChanged(QString)),this,SLOT(setP3()));
    connect(ui->p4x, SIGNAL(textChanged(QString)),this,SLOT(setP4()));
    connect(ui->p4y, SIGNAL(textChanged(QString)),this,SLOT(setP4()));
    connect(ui->p5x, SIGNAL(textChanged(QString)),this,SLOT(setP5()));
    connect(ui->p5y, SIGNAL(textChanged(QString)),this,SLOT(setP5()));
    connect(ui->p6x, SIGNAL(textChanged(QString)),this,SLOT(setP6()));
    connect(ui->p6y, SIGNAL(textChanged(QString)),this,SLOT(setP6()));
    connect(ui->p7x, SIGNAL(textChanged(QString)),this,SLOT(setP7()));
    connect(ui->p7y, SIGNAL(textChanged(QString)),this,SLOT(setP7()));
    connect(ui->p8x, SIGNAL(textChanged(QString)),this,SLOT(setP8()));
    connect(ui->p8y, SIGNAL(textChanged(QString)),this,SLOT(setP8()));
    connect(ui->p9x, SIGNAL(textChanged(QString)),this,SLOT(setP9()));
    connect(ui->p9y, SIGNAL(textChanged(QString)),this,SLOT(setP9()));
    connect(ui->p10x, SIGNAL(textChanged(QString)),this,SLOT(setP10()));
    connect(ui->p10y, SIGNAL(textChanged(QString)),this,SLOT(setP10()));
    connect(ui->n,SIGNAL(textChanged(QString)),this,SLOT(setN()));
    connect(ui->reset, SIGNAL(clicked(bool)),this,SLOT(reset()));
    connect(ui->createGraph, SIGNAL(clicked(bool)),this,SLOT(createSpline()));
    connect(ui->editDots, SIGNAL(clicked(bool)),this,SLOT(editDots()));
    connect(ui->btnTurnX, SIGNAL(clicked(bool)),this,SLOT(turnX()));
    connect(ui->btnTurnY, SIGNAL(clicked(bool)),this,SLOT(turnY()));
}

MainWindow::~MainWindow()
{
    for(int i = 0; i < MAX_N; i++){
        delete [] dots[i];
        delete [] turnDots[i];
    }
    for(int i = 0; i < (MAX_N-1)*100; i++){
        delete [] graph[i];
        delete [] turnGraph[i];
    }
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    int x = event->x();
    int y = event->y();
    double px = x;
    double py = y;
    if(x >= (2*planeAbscissaX1 - planeAbscissaX2) && x <= planeAbscissaX2 &&
       y >= planeOrdinateY2 && y <= (2*planeOrdinateY1 - planeOrdinateY2)){
        for(int i = 0; i < n; i++){
            if(!lineBool[i]){
                px -= planeAbscissaX1;
                px /= 10;
                py =  planeAbscissaY1 - y;
                py /= 10;
                switch(i){
                case 0:
                    ui->p1x->setText(QString::number(px));
                    ui->p1y->setText(QString::number(py));
                    break;
                case 1:
                    ui->p2x->setText(QString::number(px));
                    ui->p2y->setText(QString::number(py));
                    break;
                case 2:
                    ui->p3x->setText(QString::number(px));
                    ui->p3y->setText(QString::number(py));
                    break;
                case 3:
                    ui->p4x->setText(QString::number(px));
                    ui->p4y->setText(QString::number(py));
                    break;
                case 4:
                    ui->p5x->setText(QString::number(px));
                    ui->p5y->setText(QString::number(py));
                    break;
                case 5:
                    ui->p6x->setText(QString::number(px));
                    ui->p6y->setText(QString::number(py));
                    break;
                case 6:
                    ui->p7x->setText(QString::number(px));
                    ui->p7y->setText(QString::number(py));
                    break;
                case 7:
                    ui->p8x->setText(QString::number(px));
                    ui->p8y->setText(QString::number(py));
                    break;
                case 8:
                    ui->p9x->setText(QString::number(px));
                    ui->p9y->setText(QString::number(py));
                    break;
                case 9:
                    ui->p10x->setText(QString::number(px));
                    ui->p10y->setText(QString::number(py));
                    break;
                }
            break;
            }
        }
    }
}


void MainWindow::paintEvent(QPaintEvent*){
    QPainter p(this); // Создаём новый объект рисовальщика
    p.setPen(QPen(Qt::black,1,Qt::SolidLine)); // Настройки рисования
    // рисуем X+ Y+
    p.drawLine(planeAbscissaX1,planeAbscissaY1,planeAbscissaX2,planeAbscissaY2); // Рисование линии
    p.drawLine(planeOrdinateX1,planeOrdinateY1,planeOrdinateX2,planeOrdinateY2);
    // рисуем метрику
    int countX = 1;
    QString str;
    for(int i = planeAbscissaX1 + 10; i < planeAbscissaX2; i+=10){
        p.drawLine(i, planeAbscissaY1-2, i, planeAbscissaY2+2);
        str = QString::number(countX);
        if((i % 50) == 0)
            if(str.length() > 1){
                p.drawText(i-6,  planeAbscissaY1+14, str);
            }else{
                p.drawText(i-3,  planeAbscissaY1+14, str);
            }
        countX++;
    }

    int countY = 1;
    for(int i = planeOrdinateY1 - 10; i > planeOrdinateY2; i-=10){
        p.drawLine(planeOrdinateX1-2, i, planeOrdinateX2+2, i);
        str = QString::number(countY);
        if((i % 50) == 0)
            if(str.length() > 1){
                p.drawText(planeOrdinateX1-18, i+5, str);
            }else{
                p.drawText(planeOrdinateX1-12, i+5, str);
            }
        countY++;
    }
    // рисуем X- Y-
    int newPlaneAbscissaX2 = planeAbscissaX1 - (planeAbscissaX2 - planeAbscissaX1);
    int newPlaneOrdinateY2 =  planeOrdinateY1 + (planeOrdinateY1 - planeOrdinateY2);
    p.drawLine(planeAbscissaX1,planeAbscissaY1,newPlaneAbscissaX2,planeAbscissaY2); // Рисование линии
    p.drawLine(planeOrdinateX1,planeOrdinateY1,planeOrdinateX2,newPlaneOrdinateY2);
    // рисуем метрику
    countX = -1;
    str;
    for(int i = planeAbscissaX1 - 10; i > newPlaneAbscissaX2; i-=10){
        p.drawLine(i, planeAbscissaY1-2, i, planeAbscissaY2+2);
        str = QString::number(countX);
        if((i % 50) == 0)
            if(str.length() > 2){
                p.drawText(i-11,  planeAbscissaY1+14, str);
            }else{
                p.drawText(i-8,  planeAbscissaY1+14, str);
            }
        countX--;
    }

    countY = -1;
    for(int i = planeOrdinateY1 + 10; i < newPlaneOrdinateY2; i+=10){
        p.drawLine(planeOrdinateX1-2, i, planeOrdinateX2+2, i);
        str = QString::number(countY);
        if((i % 50) == 0)
            if(str.length() > 2){
                p.drawText(planeOrdinateX1-23, i+5, str);
            }else{
                p.drawText(planeOrdinateX1-17, i+5, str);
            }
        countY--;
    }

    if(!turnDotsISReady){
        // рисуем отмеченные точки
        for(int i = 0; i < n; i++){
            int number;
            if(lineBool[i]){
                number = i + 1;
                str.clear();
                str = "P";
                str += QString::number(number);
                p.setPen(QPen(Qt::black,4,Qt::SolidLine));
                p.drawPoint(dots[i][0]*10 +planeAbscissaX1, - dots[i][1]*10 + planeAbscissaY1);
                p.setPen(QPen(Qt::black,1,Qt::SolidLine));
                p.drawText(dots[i][0]*10 +planeAbscissaX1, - dots[i][1]*10 + planeAbscissaY1 - 10, str);

            }
        }
        // рисуем линии между соседними точками
        for(int i = 1; i < n; i++){
            if(lineBool[i-1] && lineBool[i]){
                        p.setPen(QPen(Qt::green,1.5,Qt::DashLine));
                p.drawLine(dots[i-1][0]*10 +planeAbscissaX1, - dots[i-1][1]*10 + planeAbscissaY1,
                            dots[i][0]*10 +planeAbscissaX1, - dots[i][1]*10 + planeAbscissaY1);
            }
        }
    }else{
        // рисуем отмеченные точки
        for(int i = 0; i < n; i++){
            int number;
            if(lineBool[i]){
                number = i + 1;
                str.clear();
                str = "P";
                str += QString::number(number);
                p.setPen(QPen(Qt::black,4,Qt::SolidLine));
                p.drawPoint(turnDots[i][0]*10 +planeAbscissaX1, - turnDots[i][1]*10 + planeAbscissaY1);
                p.setPen(QPen(Qt::black,1,Qt::SolidLine));
                p.drawText(turnDots[i][0]*10 +planeAbscissaX1, - turnDots[i][1]*10 + planeAbscissaY1 - 10, str);

            }
        }
        // рисуем линии между соседними точками
        for(int i = 1; i < n; i++){
            if(lineBool[i-1] && lineBool[i]){
                        p.setPen(QPen(Qt::green,1.5,Qt::DashLine));
                p.drawLine(turnDots[i-1][0]*10 +planeAbscissaX1, - turnDots[i-1][1]*10 + planeAbscissaY1,
                            turnDots[i][0]*10 +planeAbscissaX1, - turnDots[i][1]*10 + planeAbscissaY1);
            }
        }
    }

    // рисуем сплайн
    if(graphIsReady){
            if(!turnGraphIsReady){
                p.setPen(QPen(Qt::blue,2,Qt::SolidLine));
                for(int i = 0; i < (n-1)*100 -1; i++){
                    p.drawLine(graph[i][0]*10 +planeAbscissaX1, - graph[i][1]*10 + planeAbscissaY1,
                            graph[i+1][0]*10 +planeAbscissaX1, - graph[i+1][1]*10 + planeAbscissaY1);
                            //p.drawPoint(graph[i][0]*10 +planeAbscissaX1, - graph[i][1]*10 + planeAbscissaY1);
                }
            }else{     // рисуем повернутый сплайн
                p.setPen(QPen(Qt::blue,2,Qt::SolidLine));
                for(int i = 0; i < (n-1)*100 -1; i++){
                    p.drawLine(turnGraph[i][0]*10 +planeAbscissaX1, - turnGraph[i][1]*10 + planeAbscissaY1,
                            turnGraph[i+1][0]*10 +planeAbscissaX1, - turnGraph[i+1][1]*10 + planeAbscissaY1);
                        //p.drawPoint(graph[i][0]*10 +planeAbscissaX1, - graph[i][1]*10 + planeAbscissaY1);
                }
            }
    }


}


void MainWindow::setP1(){
    dots[0][0] = ui->p1x->text().toDouble(&p1xBool);
    dots[0][1] = ui->p1y->text().toDouble(&p1yBool);
    if(p1xBool && p1yBool){
        lineBool[0] = true;
    }else{
        lineBool[0] = false;
    }
    this->update();
}
void MainWindow::setP2(){
    dots[1][0] = ui->p2x->text().toDouble(&p2xBool);
    dots[1][1] = ui->p2y->text().toDouble(&p2yBool);
    if(p2xBool && p2yBool){
        lineBool[1] = true;
    }else{
        lineBool[1] = false;
    }
    this->update();
}
void MainWindow::setP3(){
    dots[2][0] = ui->p3x->text().toDouble(&p3xBool);
    dots[2][1] = ui->p3y->text().toDouble(&p3yBool);
    if(p3xBool && p3yBool){
        lineBool[2] = true;
    }else{
        lineBool[2] = false;
    }
    this->update();
}
void MainWindow::setP4(){
    dots[3][0] = ui->p4x->text().toDouble(&p4xBool);
    dots[3][1] = ui->p4y->text().toDouble(&p4yBool);
    if(p4xBool && p4yBool){
        lineBool[3] = true;
    }else{
        lineBool[3] = false;
    }
    this->update();
}
void MainWindow::setP5(){
    dots[4][0] = ui->p5x->text().toDouble(&p5xBool);
    dots[4][1] = ui->p5y->text().toDouble(&p5yBool);
    if(p5xBool && p5yBool){
        lineBool[4] = true;
    }else{
        lineBool[4] = false;
    }
    this->update();
}
void MainWindow::setP6(){
    dots[5][0] = ui->p6x->text().toDouble(&p6xBool);
    dots[5][1] = ui->p6y->text().toDouble(&p6yBool);
    if(p6xBool && p6yBool){
        lineBool[5] = true;
    }else{
        lineBool[5] = false;
    }
    this->update();
}
void MainWindow::setP7(){
    dots[6][0] = ui->p7x->text().toDouble(&p7xBool);
    dots[6][1] = ui->p7y->text().toDouble(&p7yBool);
    if(p7xBool && p7yBool){
        lineBool[6] = true;
    }else{
        lineBool[6] = false;
    }
    this->update();
}
void MainWindow::setP8(){
    dots[7][0] = ui->p8x->text().toDouble(&p8xBool);
    dots[7][1] = ui->p8y->text().toDouble(&p8yBool);
    if(p8xBool && p8yBool){
        lineBool[7] = true;
    }else{
        lineBool[7] = false;
    }
    this->update();
}
void MainWindow::setP9(){
    dots[8][0] = ui->p9x->text().toDouble(&p9xBool);
    dots[8][1] = ui->p9y->text().toDouble(&p9yBool);
    if(p9xBool && p9yBool){
        lineBool[8] = true;
    }else{
        lineBool[8] = false;
    }
    this->update();
}
void MainWindow::setP10(){
    dots[9][0] = ui->p10x->text().toDouble(&p10xBool);
    dots[9][1] = ui->p10y->text().toDouble(&p10yBool);
    if(p10xBool && p10yBool){
        lineBool[9] = true;
    }else{
        lineBool[9] = false;
    }
    this->update();
}
void MainWindow::createSpline(){

    graph = line.init(n,dots);
    turnGraphIsReady = false;
    turnDotsISReady = false;
    graphIsReady = true;
    this->update();
}

void MainWindow::editDots(){
    graphIsReady = false;
    turnGraphIsReady = false;
    turnDotsISReady = false;
    this->update();
}

void MainWindow::setN(){
    bool flag;
    int _n = ui->n->text().toInt(&flag);
    if(flag){
        if(_n <= MAX_N && _n >= MIN_N){
            graphIsReady = false;
            n = _n;
            switch(n){
            case 6:
                ui->p7x->setEnabled(false);
                ui->p7y->setEnabled(false);
                ui->p8x->setEnabled(false);
                ui->p8y->setEnabled(false);
                ui->p9x->setEnabled(false);
                ui->p9y->setEnabled(false);
                ui->p10x->setEnabled(false);
                ui->p10y->setEnabled(false);
                break;
            case 7:
                ui->p7x->setEnabled(true);
                ui->p7y->setEnabled(true);
                ui->p8x->setEnabled(false);
                ui->p8y->setEnabled(false);
                ui->p9x->setEnabled(false);
                ui->p9y->setEnabled(false);
                ui->p10x->setEnabled(false);
                ui->p10y->setEnabled(false);
                break;
            case 8:
                ui->p7x->setEnabled(true);
                ui->p7y->setEnabled(true);
                ui->p8x->setEnabled(true);
                ui->p8y->setEnabled(true);
                ui->p9x->setEnabled(false);
                ui->p9y->setEnabled(false);
                ui->p10x->setEnabled(false);
                ui->p10y->setEnabled(false);
                break;
            case 9:
                ui->p7x->setEnabled(true);
                ui->p7y->setEnabled(true);
                ui->p8x->setEnabled(true);
                ui->p8y->setEnabled(true);
                ui->p9x->setEnabled(true);
                ui->p9y->setEnabled(true);
                ui->p10x->setEnabled(false);
                ui->p10y->setEnabled(false);
                break;
            case 10:
                ui->p7x->setEnabled(true);
                ui->p7y->setEnabled(true);
                ui->p8x->setEnabled(true);
                ui->p8y->setEnabled(true);
                ui->p9x->setEnabled(true);
                ui->p9y->setEnabled(true);
                ui->p10x->setEnabled(true);
                ui->p10y->setEnabled(true);
                break;
            }
        }
    }
}

void MainWindow::turnX(){
    bool flag;
    double alphaX;
    double swap[2];
    alphaX = ui->xalpha->text().toDouble(&flag);
    if(flag){
        line.createTurnMatrixX(alphaX);
        for(int i = 0; i < n; i++){
            swap[0] = dots[i][0];
            swap[1] = dots[i][1];
            turnDots[i][0] = swap[0];
            turnDots[i][1] = swap[1];
            line.turnX(turnDots[i]);
        }
        turnDotsISReady = true;
        if(graphIsReady){
            for(int i = 0; i < (n-1)*100; i++){
                swap[0] = graph[i][0];
                swap[1] = graph[i][1];
                turnGraph[i][0] = swap[0];
                turnGraph[i][1] = swap[1];
                line.turnX(turnGraph[i]);
            }
            turnGraphIsReady = true;
        }
    }
    this->update();
}

void MainWindow::turnY(){
    bool flag;
    double alphaY;
    double swap[2];
    alphaY = ui->yalpha->text().toDouble(&flag);
    if(flag){
        line.createTurnMatrixY(alphaY);
        for(int i = 0; i < n; i++){
            swap[0] = dots[i][0];
            swap[1] = dots[i][1];
            turnDots[i][0] = swap[0];
            turnDots[i][1] = swap[1];
            line.turnY(turnDots[i]);
        }
        turnDotsISReady = true;
        if(graphIsReady){
            for(int i = 0; i < (n-1)*100; i++){
                swap[0] = graph[i][0];
                swap[1] = graph[i][1];
                turnGraph[i][0] = swap[0];
                turnGraph[i][1] = swap[1];
                line.turnY(turnGraph[i]);
            }
            turnGraphIsReady = true;
        }
    }
    this->update();
}

void MainWindow::reset(){
    ui->p1x->clear();
    ui->p1y->clear();
    ui->p2x->clear();
    ui->p2y->clear();
    ui->p3x->clear();
    ui->p3y->clear();
    ui->p4x->clear();
    ui->p4y->clear();
    ui->p5x->clear();
    ui->p5y->clear();
    ui->p6x->clear();
    ui->p6y->clear();
    ui->p7x->clear();
    ui->p7y->clear();
    ui->p8x->clear();
    ui->p8y->clear();
    ui->p9x->clear();
    ui->p9y->clear();
    ui->p10x->clear();
    ui->p10y->clear();
    ui->xalpha->clear();
    ui->yalpha->clear();
    graphIsReady = false;
    turnGraphIsReady = false;
    turnDotsISReady = false;
}


