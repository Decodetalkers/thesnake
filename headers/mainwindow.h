#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "snake.h"
#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QString>
#include <QTimer>
#include <QDebug>
class Scene : public QWidget {
	Q_OBJECT
public:
	Scene(QWidget *parent=nullptr):QWidget(parent){};
	~Scene() { qDebug()<< "deleted";}
};
class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  enum type { snake, food, background };
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
  Scene *scene;
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
