#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qboxlayout.h"
#include "qlabel.h"
#include "qobjectdefs.h"
#include "qwidget.h"
#include "qwindowdefs.h"
#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
#include <QTimer>
#include <QString>
#include "snake.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum type {
        snake,
        food,
        background
    };
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected slots: 
    void control();
    bool eventFilter(QObject *object, QEvent *event);
    void gameover();
    void changethelevel();
private:
    int count;
    int thescore;
    QString Level;
    QString FOOD;
    void handleKeyPress(QKeyEvent *event);
    QWidget *scene;
    QLabel *asnake[16][16];
    QLabel *score;
    QLabel *thefood;
    QLabel *thelevel;
    type snakes[16][16];
    QVBoxLayout *Labels;
    QHBoxLayout *thewindow;
    QGridLayout *game;
    void start();
    QTimer *timer;
    Snake *mysnake;
    bool hasfood;
    bool isrun;
    void createfood();
    QAction *changelevel;
};
#endif // MAINWINDOW_H
