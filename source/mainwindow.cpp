#include "headers/mainwindow.h"
#include "headers/snake.h"
#include <QAction>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QToolBar>
#include <QWidget>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), count(1), thescore(0), Level("lowest"),
      FOOD("NoFood"), scene(new Scene(this)), score(new QLabel()),
      thefood(new QLabel()), thelevel(new QLabel()), Labels(new QVBoxLayout()),
      thewindow(new QHBoxLayout(scene)), game(new QGridLayout()),
      hasfood(false), isrun(false),
      changelevel(new QAction(tr("changelevel"), this)) {
  setFixedSize(600, 500);
  timer = new QTimer(this);
  timer->start(1000 / 3);
  changelevel->setShortcut(QKeySequence::Open);
  changelevel->setStatusTip(tr("change the level"));
  connect(this->changelevel, SIGNAL(triggered()), this, SLOT(changethelevel()));
  QToolBar *toolBar = addToolBar(tr("&File"));
  toolBar->addAction(changelevel);
  Labels->addWidget(score);
  Labels->addWidget(thefood);
  Labels->addWidget(thelevel);
  thewindow->addLayout(game);
  thewindow->addLayout(Labels);
  setCentralWidget(scene);
  statusBar();
  // game->setHorizontalSpacing(100);
  //  设置垂直间距
  // game->setVerticalSpacing(100);
  //  设置外间距
  // game->setContentsMargins(10, 10, 10, 10);

  start();

  this->installEventFilter(this);
  // asnake[1][1]->setStyleSheet("QLabel{background-color:rgb(20,101,102);}");
}

MainWindow::~MainWindow() {
  scene->deleteLater();
  delete score;
  delete thefood;
  delete thelevel;
  // delete Labels;
  delete thewindow;
  game->deleteLater();
  delete timer;
  delete mysnake;
  delete changelevel;
  qDebug() << "it is end";
  // as shown, the scene will be deleted after the window is deleted.
}

void MainWindow::start() {
  score->setText(QString::number(thescore));
  score->setFixedWidth(100);
  thefood->setText(FOOD);
  thefood->setFixedWidth(100);
  thelevel->setText(Level);
  thelevel->setFixedWidth(100);
  QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);
  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 16; ++j) {
      asnake[i][j] = new QLabel(this);
      asnake[i][j]->setStyleSheet("QLabel{background-color:rgb(200,101,102);}");
      asnake[i][j]->setSizePolicy(sizePolicy);
      snakes[i][j] = background;
      game->addWidget(asnake[i][j], j, i, 1, 1);
    }
  }
  game->setSpacing(0);
  mysnake = new Snake();
  asnake[mysnake->asnake.front().first][mysnake->asnake.front().second]
      ->setStyleSheet("QLabel{background-color:rgb(20,101,102);}");
  snakes[mysnake->asnake.front().first][mysnake->asnake.front().second] = snake;
  asnake[mysnake->asnake.back().first][mysnake->asnake.back().second]
      ->setStyleSheet("QLabel{background-color:rgb(20,101,102);}");

  snakes[mysnake->asnake.back().first][mysnake->asnake.back().second] = snake;
  createfood();
  connect(this->timer, SIGNAL(timeout()), this, SLOT(control()));
}
void MainWindow::control() {
  if (mysnake->currentDirection() != Snake::NoMove) {
    asnake[mysnake->asnake.back().first][mysnake->asnake.back().second]
        ->setStyleSheet("QLabel{background-color:rgb(200,101,102);}");
    snakes[mysnake->asnake.back().first][mysnake->asnake.back().second] =
        background;
    mysnake->run();
    asnake[mysnake->asnake.front().first][mysnake->asnake.front().second]
        ->setStyleSheet("QLabel{background-color:rgb(20,101,102);}");
    if (snakes[mysnake->asnake.front().first][mysnake->asnake.front().second] ==
        snake) {
      thescore = 0;
      score->setText("Gameover");
      QTimer::singleShot(0, this, SLOT(gameover()));
    }
    if (snakes[mysnake->asnake.front().first][mysnake->asnake.front().second] ==
        food) {
      hasfood = false;
      snakes[mysnake->asnake.front().first][mysnake->asnake.front().second] =
          snake;
      mysnake->longer();
      createfood();
      asnake[mysnake->asnake.front().first][mysnake->asnake.front().second]
          ->setStyleSheet("QLabel{background-color:rgb(20,101,102);}");
      thescore += 50;
      score->setText(QString::number(thescore));
    }
    // qDebug()<<asnake[mysnake->asnake.front().first][mysnake->asnake.front().second]->styleSheet();
    snakes[mysnake->asnake.front().first][mysnake->asnake.front().second] =
        snake;
    repaint();
  }
  isrun = false;
}
void MainWindow::gameover() {
  disconnect(this->timer, SIGNAL(timeout()), this, SLOT(control()));
  if (QMessageBox::Yes ==
      QMessageBox::information(NULL, tr("Game Over"), tr("Again?"),
                               QMessageBox::Yes | QMessageBox::No,
                               QMessageBox::Yes)) {
    std::cout << "test" << std::endl;
    isrun = false;
    hasfood = false;
    start();
  } else {
    std::cout << "test" << std::endl;
    exit(0);
  }
}
bool MainWindow::eventFilter(QObject *object, QEvent *event) {
  if (event->type() == QEvent::KeyPress) {
    handleKeyPress((QKeyEvent *)event);
    return true;
  } else {
    return QObject::eventFilter(object, event);
  }
}

void MainWindow::handleKeyPress(QKeyEvent *event) {
  if (isrun) {
    qDebug() << "is still run";
    return;
  }
  isrun = true;
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
void MainWindow::createfood() {
  if (!hasfood) {
    int x, y;
    do {
      x = (int)(QRandomGenerator::global()->bounded(16));
      y = (int)(QRandomGenerator::global()->bounded(16));
    } while (snakes[x][y] == snake);
    FOOD = QString::number(x) + "," + QString::number(y);
    thefood->setText(FOOD);
    asnake[x][y]->setStyleSheet("QLabel{background-color:rgb(20,10,10);}");
    snakes[x][y] = food;
    hasfood = true;
    repaint();
  }
}
void MainWindow::changethelevel() {
  switch (count) {
  case 1:
    timer->start(100 / 3);
    count = 2;
    Level = "hightest";
    thelevel->setText(Level);
    break;
  case 2:
    timer->start(300 / 3);
    count = 3;
    Level = "medium";
    thelevel->setText(Level);
    break;
  case 3:
    timer->start(1000 / 3);
    count = 1;
    Level = "lowest";
    thelevel->setText(Level);

    break;
  }
}
