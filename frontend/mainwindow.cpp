#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    trackLabel.setText("\nГотов.\n");
    trackLabel.setAlignment(Qt::AlignCenter);
    trackLabel.setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    trackLabel.setTextInteractionFlags(Qt::TextSelectableByMouse);
    trackLabel.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    currentTime.setFrameStyle(QLCDNumber::NoFrame);
    currentTime.setSegmentStyle(QLCDNumber::Flat);
    currentTime.setDigitCount(5);
    currentTime.display("00:00");
    currentTime.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    currentTime.setMinimumHeight(32);

    positionSlider.setOrientation(Qt::Horizontal);
    positionSlider.setPageStep(0);
    positionSlider.setRange(0, 1);
    positionSlider.setDisabled(true);

    durationTime.setFrameStyle(QLCDNumber::NoFrame);
    durationTime.setSegmentStyle(QLCDNumber::Flat);
    durationTime.setDigitCount(5);
    durationTime.display("00:00");
    durationTime.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    durationTime.setMinimumHeight(32);

    positionLayout.addWidget(&currentTime);
    positionLayout.addWidget(&positionSlider);
    positionLayout.addWidget(&durationTime);

    openButton.setText("Открыть");
    openButton.setIcon(QIcon::fromTheme("fileopen"));

    prevButton.setIcon(QIcon::fromTheme("media-skip-backward"));
    prevButton.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    playButton.setIcon(QIcon::fromTheme("media-playback-start"));
    playButton.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    nextButton.setIcon(QIcon::fromTheme("media-skip-forward"));
    nextButton.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    loopButton.setText("Зациклить");
    loopButton.setIcon(QIcon::fromTheme("media-playlist-repeat"));
    loopButton.setCheckable(true);

    playbackLayout.addWidget(&openButton);
    playbackLayout.addStretch();
    playbackLayout.addWidget(&prevButton);
    playbackLayout.addWidget(&playButton);
    playbackLayout.addWidget(&nextButton);
    playbackLayout.addStretch();
    playbackLayout.addWidget(&loopButton);

    playFrame.setLayout(&playLayout);
    playFrame.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    playFrame.setFrameStyle(QFrame::Panel | QFrame::Sunken);

    playLayout.addLayout(&positionLayout);
    playLayout.addLayout(&playbackLayout);

    volumeSlider.setOrientation(Qt::Horizontal);
    volumeSlider.setRange(0, 100);
    volumeSlider.setValue(100);

    effectsLayout.addWidget(new QLabel("Громкость: "));
    effectsLayout.addWidget(&volumeSlider);

    playerLayout.addWidget(&coverLabel);
    playerLayout.addWidget(&trackLabel);
    playerLayout.addWidget(&playFrame);
    playerLayout.addLayout(&effectsLayout);

    layout.addLayout(&playerLayout);

    playlistLayout.addWidget(&playlistTab);

    addButton.setIcon(QIcon::fromTheme("list-add"));
    delButton.setIcon(QIcon::fromTheme("list-remove"));
    refreshButton.setText("Проверить пути");
    refreshButton.setIcon(QIcon::fromTheme("view-refresh"));
    newButton.setIcon(QIcon::fromTheme("folder-new"));
    remButton.setIcon(QIcon::fromTheme("edit-delete"));

    managementLayout.addWidget(&addButton);
    managementLayout.addWidget(&delButton);
    managementLayout.addStretch();
    managementLayout.addWidget(&refreshButton);
    managementLayout.addStretch();
    managementLayout.addWidget(&newButton);
    managementLayout.addWidget(&remButton);

    managementFrame.setFrameStyle(QFrame::Panel | QFrame::Sunken);
    managementFrame.setLayout(&managementLayout);

    playlistLayout.addWidget(&managementFrame);

    layout.addLayout(&playlistLayout);

    centralWidget.setLayout(&layout);
    this->setCentralWidget(&centralWidget);
    this->setWindowTitle("Плеер");
}

MainWindow::~MainWindow()
{
}

