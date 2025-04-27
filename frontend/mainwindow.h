#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLCDNumber>

#include <QTabWidget>
#include <QListWidget>

#include "coverlabel.h"
#include "mediaslider.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public slots:
    void checkState();
    void changeState();
    void setPosition();
    void updatePosition();
    void updateInfo();
    void open();
    void itemActivatedHandler();
    void addPlaylist();
    void remPlaylist();
    void addSongs();
    void delSongs();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QWidget centralWidget;
    QHBoxLayout layout;
    QVBoxLayout playerLayout;
    QVBoxLayout playlistLayout;

    QFrame playFrame;
    QVBoxLayout playLayout;
    QHBoxLayout positionLayout;
    QHBoxLayout playbackLayout;
    QHBoxLayout effectsLayout;

    CoverLabel coverLabel;
    QLabel trackLabel;

    MediaSlider positionSlider;
    QLCDNumber currentTime;
    QLCDNumber durationTime;

    QPushButton openButton;
    QPushButton prevButton;
    QPushButton playButton;
    QPushButton nextButton;
    QPushButton loopButton;

    QSlider volumeSlider;

    QFrame managementFrame;
    QHBoxLayout managementLayout;

    QPushButton addButton;
    QPushButton delButton;
    QPushButton refreshButton;
    QPushButton newButton;
    QPushButton remButton;

    QTabWidget playlistTab;
    std::vector<QListWidget*> playlistWidget;
};

#endif // MAINWINDOW_H
