#include "front_main.h"

#include "../global.h"

#include "mainwindow.h"

#include <string>
#include <vector>

#include <QApplication>
#include <QTime>
//#include <QIcon>
//#include <QUrl>
//include <QImage>
//#include <QPixmap>
#include <QMediaPlayer>

#include <QFileDialog>

#include <QObject>

void frontend::init(){
    QObject::connect(&global::player->qplayer, &QMediaPlayer::stateChanged,
                      global::window, &MainWindow::checkState);

    QObject::connect(&global::window->playButton, &QPushButton::clicked,
                      global::window, &MainWindow::changeState);

    QObject::connect(&global::window->nextButton, &QPushButton::clicked,
                      global::player, &Player::next);

    QObject::connect(&global::window->prevButton, &QPushButton::clicked,
                      global::player, &Player::prev);

    QObject::connect(&global::window->volumeSlider, &QSlider::valueChanged,
                     &global::player->qplayer, &QMediaPlayer::setVolume);

    QObject::connect(&global::window->positionSlider, &QSlider::sliderReleased,
                      global::window, &MainWindow::setPosition);

    QObject::connect(&global::player->qplayer, &QMediaPlayer::positionChanged,
                      global::window, &MainWindow::updatePosition);

    QObject::connect(&global::player->qplayer, &QMediaPlayer::durationChanged,
                      global::window, &MainWindow::updateInfo);

    QObject::connect(&global::window->openButton, &QPushButton::clicked,
                      global::window, &MainWindow::open);

    QObject::connect(&global::window->newButton, &QPushButton::clicked,
                      global::window, &MainWindow::addPlaylist);

    QObject::connect(&global::window->remButton, &QPushButton::clicked,
                      global::window, &MainWindow::remPlaylist);

    QObject::connect(&global::window->addButton, &QPushButton::clicked,
                      global::window, &MainWindow::addSongs);

    QObject::connect(&global::window->delButton, &QPushButton::clicked,
                      global::window, &MainWindow::delSongs);

    global::window->show();
}
