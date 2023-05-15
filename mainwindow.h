#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QFrame>
#include <fruta.h>
#include <iostream>
#include <QVector>
#include <bola.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QGraphicsEllipseItem *pacman;
    Fruta* fruta;
    QTimer *timer;
    bool moverIx1;
    bool moverDx1;
    bool moverUy1;
    bool moverDy1;
    void keyPressEvent(QKeyEvent *ev);
    QVector<Fruta*> frutas;
    QVector<QGraphicsRectItem*> paredes;
    QVector<Bola*> Bolas;
    QVector<QGraphicsRectItem*> Telep;
    int puntuacion=0;



signals:
    void aviso();
    void aviso2();


public slots:
    void animar();
    void aumentarPunt();
    void aumentarPunt2();

};
#endif // MAINWINDOW_H
