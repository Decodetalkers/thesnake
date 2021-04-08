#include "mainwindow.h"
#include "qdebug.h"
#include "qevent.h"
#include "qgridlayout.h"
#include "qlabel.h"
#include "qmainwindow.h"
#include "qnamespace.h"
#include "qobject.h"
#include "qrandom.h"
#include "qsizepolicy.h"
#include "qwidget.h"
#include "snake.h"
#include <QWidget>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    scene(new QWidget(this)),
    game(new QGridLayout(scene)),
    hasfood(false),
    isrun(false)
{
    setFixedSize(500,500);
    timer = new QTimer(this);
    timer->start(1000/3);
    setCentralWidget(scene);

    //game->setHorizontalSpacing(100);
    // 设置垂直间距
    //game->setVerticalSpacing(100);
    // 设置外间距
    //game->setContentsMargins(10, 10, 10, 10);

    start();

    this->installEventFilter(this);
        //asnake[1][1]->setStyleSheet("QLabel{background-color:rgb(20,101,102);}");

}

MainWindow::~MainWindow()
{
}

void MainWindow::start(){
    QSizePolicy sizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    for(int i=0;i<16;++i){
        for(int j=0;j<16;++j){
            asnake[i][j]=new QLabel(this);
            asnake[i][j]->setStyleSheet("QLabel{background-color:rgb(200,101,102);}");
            asnake[i][j]->setSizePolicy(sizePolicy);
            snakes[i][j]=background; 
            game->addWidget(asnake[i][j],j,i,1,1);
        }
   
    }
    game->setSpacing(0);
    mysnake = new Snake();
    asnake[mysnake->asnake.front().first][mysnake->asnake.front().second]->setStyleSheet("QLabel{background-color:rgb(20,101,102);}");
    snakes[mysnake->asnake.front().first][mysnake->asnake.front().second]=snake;
    asnake[mysnake->asnake.back().first][mysnake->asnake.back().second]->setStyleSheet("QLabel{background-color:rgb(20,101,102);}");

    snakes[mysnake->asnake.back().first][mysnake->asnake.back().second]=snake;
    createfood();
    connect(this->timer, SIGNAL(timeout()),
            this, SLOT(control()));

}
void MainWindow::control(){
    if(mysnake->currentDirection()!=Snake::NoMove){
        asnake[mysnake->asnake.back().first][mysnake->asnake.back().second]->setStyleSheet("QLabel{background-color:rgb(200,101,102);}");
        snakes[mysnake->asnake.back().first][mysnake->asnake.back().second]=background;
        mysnake->run(); 
        asnake[mysnake->asnake.front().first][mysnake->asnake.front().second]->setStyleSheet("QLabel{background-color:rgb(20,101,102);}");
        if(snakes[mysnake->asnake.front().first][mysnake->asnake.front().second]==snake)
        {
            std::cout<<"gameover"<<std::endl;
            QTimer::singleShot(0,this,SLOT(gameover()));
        }
        if(snakes[mysnake->asnake.front().first][mysnake->asnake.front().second]==food)
        {
            hasfood=false;
            snakes[mysnake->asnake.front().first][mysnake->asnake.front().second]=snake;
            mysnake->longer();
            createfood();
            asnake[mysnake->asnake.front().first][mysnake->asnake.front().second]->setStyleSheet("QLabel{background-color:rgb(20,101,102);}");
        }
        //qDebug()<<asnake[mysnake->asnake.front().first][mysnake->asnake.front().second]->styleSheet();
        snakes[mysnake->asnake.front().first][mysnake->asnake.front().second]=snake;
        repaint();
    }
    isrun=false;
}
void MainWindow::gameover(){
    disconnect(this->timer, SIGNAL(timeout()),
            this, SLOT(control()));
    if (QMessageBox::Yes == QMessageBox::information(NULL,
                            tr("Game Over"), tr("Again?"),
                            QMessageBox::Yes | QMessageBox::No,
                            QMessageBox::Yes)) {
        std::cout<<"test"<<std::endl;
        isrun=false;
        hasfood=false;
        start();
    } else {
        std::cout<<"test"<<std::endl;
        exit(0);
    }
}
bool MainWindow::eventFilter(QObject *object, QEvent *event) {
    if (event->type() ==QEvent::KeyPress){
        handleKeyPress((QKeyEvent *) event);
        return true;
    } else {
        return QObject::eventFilter(object, event);
    }
}

void MainWindow::handleKeyPress(QKeyEvent *event) {
    if(isrun)
    {
        qDebug()<<"is still run";
        return;
    }
    isrun=true;
    switch (event->key()) {
        case Qt::Key_Left:
            mysnake->setMoveDirection(Snake::MoveLeft);
            break;
        case Qt::Key_Space:
            mysnake->setMoveDirection(Snake::NoMove);
            break;
        case Qt::Key_Right:
            mysnake->setMoveDirection(Snake::MoveRight);
            break;
        case Qt::Key_Up:
            mysnake->setMoveDirection(Snake::MoveUp);
            break;
        case Qt::Key_Down:
            mysnake->setMoveDirection(Snake::MoveDown);
            break;
    }
}
void MainWindow::createfood(){
    if(!hasfood){
        int x,y;
        do{
            x=(int)(QRandomGenerator::global()->bounded(16));
            y=(int)(QRandomGenerator::global()->bounded(16));
        }while(snakes[x][y]==snake);
        asnake[x][y]->setStyleSheet("QLabel{background-color:rgb(20,10,10);}");
        snakes[x][y]=food;
        hasfood=true;
        repaint();
    }
}
