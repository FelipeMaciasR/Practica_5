#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fruta.h>
#include <QDebug>
#include <vector>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    char Lab[31][29] = {
        "############################",
        "#............##............#",
        "#.####.#####.##.#####.####.#",
        "#F####.#####.##.#####.####F#",//
        "#.####.#####.##.#####.####.#",
        "#..........................#",
        "#.####.##.########.##.####.#",
        "#.####.##.########.##.####.#",
        "#......##....##....##......#",
        "######.##### ## #####.######",
        "     #.##### ## #####.#     ",
        "     #.##          ##.#     ",
        "     #.## ######## ##.#     ",
        "######.## #      # ##.######",
        "T     .   #      #   .     T",
        "######.## #      # ##.######",
        "     #.## ######## ##.#     ",
        "     #.##          ##.#     ",
        "     #.## ######## ##.#     ",
        "######.## ######## ##.######",
        "#............##............#",
        "#.####.#####.##.#####.####.#",
        "#.####.#####.##.#####.####.#",
        "#F..##.......  .......##..F#",
        "###.##.##.########.##.##.###",
        "###.##.##.########.##.##.###",
        "#......##....##....##......#",
        "#.##########.##.##########.#",
        "#.##########.##.##########.#",
        "#..........................#",
        "############################"
    };



    scene=new QGraphicsScene(0,0,500,400);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFocus();

    int matrizx=500/28;
    int matrizy=500/31;

    for (int i=0;i<31;i++){

        for (int j=0;j<29;j++){

            if (Lab[i][j]=='#'){

                int x = j*matrizx;

                int y = i*matrizy;

                QGraphicsRectItem *rectItem = new QGraphicsRectItem(x, y, matrizx, matrizy);
                rectItem->setBrush (Qt::black);
                scene->addItem(rectItem);
                paredes.push_back(rectItem);

            }

            else if(Lab[i][j]=='.'){
                int x = j*matrizx;
                int y = i*matrizy;

                Fruta* fruta = new Fruta();
                fruta->setPos(x+10, y+10);
                scene->addItem(fruta);
                frutas.push_back(fruta);
            }

            else if(Lab[i][j]=='F'){
                int x = j*matrizx;
                int y = i*matrizy;

                Bola* bola = new Bola();
                bola->setPos(x+10, y+10);
                scene->addItem(bola);
                Bolas.push_back(bola);
            }
            else if(Lab[i][j]=='T'){
                int x = j*matrizx;
                int y = i*matrizy;

                QGraphicsRectItem *rectItem = new QGraphicsRectItem(x, y, matrizx, matrizy);
                rectItem->setBrush (Qt::blue);
                scene->addItem(rectItem);
                Telep.push_back(rectItem);
            }

        }
    }


    pacman = new QGraphicsEllipseItem(20, 20, 10, 10);
    pacman->setBrush(QBrush(Qt::yellow));
    scene->addItem(pacman);



    moverIx1=false;
    moverDx1=false;
    moverUy1=false;
    moverDy1=false;

    timer=new QTimer();

    connect(timer,SIGNAL(timeout()),this,SLOT(animar()));
    connect(this,SIGNAL(aviso()),this,SLOT(aumentarPunt()));
    connect(this,SIGNAL(aviso2()),this,SLOT(aumentarPunt2()));


    timer->start(30);

}


void MainWindow::animar()
{
    if(moverIx1)
    {
        pacman->setPos(pacman->x()-2,pacman->y());

    }
    if(moverDx1)
    {
        pacman->setPos(pacman->x()+2,pacman->y());

    }
    if(moverUy1)
    {
        pacman->setPos(pacman->x(),pacman->y()-2);

    }
    if(moverDy1)
    {
        pacman->setPos(pacman->x(),pacman->y()+2);

    }
    for (auto it = frutas.begin(); it != frutas.end(); ++it) {
        Fruta* frutaActual = *it;

        if (pacman->collidesWithItem(frutaActual) && frutaActual->isVisible()) {
            frutaActual->hide();

            frutas.erase(it);

            scene->removeItem(frutaActual);
            delete frutaActual;
            frutaActual = nullptr;

            emit aviso();

            break;
        }
    }
    for (auto it = Bolas.begin(); it != Bolas.end(); ++it) {
        Bola* bolaActual = *it;

        if (pacman->collidesWithItem(bolaActual) && bolaActual->isVisible()) {
            bolaActual->hide();

            Bolas.erase(it);

            scene->removeItem(bolaActual);
            delete bolaActual;
            bolaActual = nullptr;

            emit aviso2();

            break;
        }
    }
    if (pacman->collidesWithItem(Telep[0])) {
        moverIx1 = true;
        pacman->setPos(Telep[1]->x() , Telep[1]->y() );
    }

    if (pacman->collidesWithItem(Telep[1])) {
        moverDx1 = true;
        pacman->setPos(Telep[0]->x() , Telep[0]->y() );
    }

    bool colision = false;

    for (auto pared : paredes) {
        if (pacman->collidesWithItem(pared)) {
            colision = true;
            break;
        }
    }


    if (colision) {
        if (moverIx1) {
            pacman->setPos(pacman->x() + 2, pacman->y());
        }
        if (moverDx1) {
            pacman->setPos(pacman->x() - 2, pacman->y());
        }
        if (moverUy1) {
            pacman->setPos(pacman->x(), pacman->y() + 2);
        }
        if (moverDy1) {
            pacman->setPos(pacman->x(), pacman->y() - 2);
        }
    }


}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    moverIx1=false;
    moverDx1=false;
    moverUy1=false;
    moverDy1=false;
    if(ev->key()==Qt::Key_A)
    {
        moverIx1=true;
    }
    else if(ev->key()==Qt::Key_S)
    {
        moverDx1=true;
    }
    else if(ev->key()==Qt::Key_W)
    {
        moverUy1=true;
    }
    else if(ev->key()==Qt::Key_Z)
    {
        moverDy1=true;
    }

}

void MainWindow::aumentarPunt()
{
    puntuacion += 1;
    ui->lcdNumber->display(puntuacion);
    std::cout<<puntuacion<<std::endl;
}

void MainWindow::aumentarPunt2()
{
    puntuacion += 5;
    ui->lcdNumber->display(puntuacion);
    std::cout<<puntuacion<<std::endl;
}


MainWindow::~MainWindow()
{
    delete scene;
    delete ui;
}

