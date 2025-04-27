#include "mainwindow.h"

#include "../global.h"
#include <QFileDialog>
#include <QTime>
#include <QtMultimedia/QMediaMetaData>

#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/id3v2frame.h>

#include <QFileInfo>
#include <QInputDialog>
#include <QVector>
#include <QMessageBox>

void MainWindow::checkState() {
    if (global::player->qplayer.state() == QMediaPlayer::PlayingState)
        this->playButton.setIcon(QIcon::fromTheme("kt-pause"));
    else {
        if (global::player->qplayer.state() == QMediaPlayer::StoppedState &&
            global::player->qplayer.position() >= global::player->qplayer.duration()) {
            if (global::window->loopButton.isChecked()) global::player->qplayer.play();
            else if (global::player->qplayer.duration() != 0) global::player->next();
        }
        else this->playButton.setIcon(QIcon::fromTheme("kt-start"));
    }
}

void MainWindow::changeState() {
    if (global::player->qplayer.state() == QMediaPlayer::PlayingState)
        global::player->qplayer.pause();
    else
        global::player->play();
}

void MainWindow::setPosition() {
    global::player->qplayer.setPosition(this->positionSlider.value() * 1000);
}

void MainWindow::updatePosition() {
    this->positionSlider.setValue(global::player->qplayer.position() / 1000);
    QTime time(0,0,0);
    time = time.addMSecs(int(global::player->qplayer.position()));
    QString text = time.toString("mm:ss");
    this->currentTime.display(text);
}

void MainWindow::updateInfo() {
    this->positionSlider.setRange(0, global::player->qplayer.duration() / 1000);
    this->positionSlider.setDisabled(false);
    QTime time(0,0,0);
    time = time.addMSecs(int(global::player->qplayer.duration()));
    QString text = time.toString("mm:ss");
    this->durationTime.display(text);

    QLabel* track_label = &this->trackLabel;
    TagLib::FileRef f(global::player->getPath().c_str());
    QFileInfo fInfo(global::player->getPath().c_str());
    if (fInfo.suffix().toStdString().compare("mid") && (!f.tag()->title().isEmpty() ||
                                                        !f.tag()->album().isEmpty() ||
                                                        !f.tag()->artist().isEmpty())) {
        track_label->setText(f.tag()->title().toCString(true));
        track_label->setText(track_label->text().append("\n"));
        track_label->setText(track_label->text().append(f.tag()->album().toCString(true)));
        track_label->setText(track_label->text().append("\n"));
        track_label->setText(track_label->text().append(f.tag()->artist().toCString(true)));
    }
    else {
        track_label->setText("\n");
        track_label->setText(track_label->text().append(
            QFileInfo(global::player->getPath().c_str()).fileName()));
        track_label->setText(track_label->text().append("\n"));
    }
    QImage coverImage = global::player->qplayer.metaData(QMediaMetaData::CoverArtImage).value<QImage>();
    if (coverImage.isNull()) this->coverLabel.reset();
    else this->coverLabel.set_new_cover(QPixmap::fromImage(coverImage));
}

void MainWindow::open() {
    QString choosed_file = QFileDialog::getOpenFileName(this, "Открыть", nullptr, "Аудио файлы (*.mp3 *.ogg *.wav *.mid)");
    global::player->play(choosed_file.toStdString());
}

void MainWindow::itemActivatedHandler() {
    int playlist = global::window->playlistTab.currentIndex();
    QListWidget* widget = global::window->playlistWidget[playlist];
    qWarning() << global::backend->getPlaylist(playlist)->getPath(widget->currentRow()).c_str();
    global::player->set(playlist, widget->currentRow());
    global::player->play();
}

void MainWindow::addPlaylist() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Создать плейлист"),
                                         tr("Имя нового плейлиста:"), QLineEdit::Normal, nullptr, &ok);
    if (ok && !text.isEmpty()) global::backend->addNewPlaylist(text.toStdString());
}

void MainWindow::remPlaylist() {
    int playlist = global::window->playlistTab.currentIndex();
    int ret = QMessageBox::warning(this, "Удалить плейлист",
                               "Удалить " + global::window->playlistTab.tabText(playlist) + "?",
                               QMessageBox::Yes | QMessageBox::Cancel, QMessageBox::Cancel);
    if (ret == QMessageBox::Yes) {
        if (playlist == global::player->getPlaylist()) {
            global::player->stop();
            global::player->isPlaylist = false;
        }
        std::remove(global::backend->getPlaylist(playlist)->getPath().c_str());
        global::backend->remPlaylist(playlist);
        global::window->playlistWidget.erase(global::window->playlistWidget.begin() + playlist);
        global::window->playlistTab.removeTab(playlist);

    }
}

void MainWindow::addSongs() {
    int playlist = global::window->playlistTab.currentIndex();
    QStringList fileNames;
    fileNames = QFileDialog::getOpenFileNames(this, "Добавить песни", nullptr, "Аудио файлы (*.mp3 *.ogg *.wav *.mid)");
    QVector<QString> fileNamesVec = fileNames.toVector();
    std::vector<std::string> fileNamesStr;
    for (int i = 0; i < fileNames.size(); i++)
        fileNamesStr.push_back(fileNamesVec[i].toStdString());;
    if (!fileNames.isEmpty()) global::backend->getPlaylist(playlist)->add(fileNamesStr);
    for (int i = 0; i < fileNames.size(); i++)
        global::window->playlistWidget[playlist]->addItem(QFileInfo(fileNamesStr[i].c_str()).fileName());
}

void MainWindow::delSongs() {
    int playlist = global::window->playlistTab.currentIndex();
    int song = global::window->playlistWidget[playlist]->currentRow();
    std::string path(global::backend->getPlaylist(playlist)->getPath(song));
    global::window->playlistWidget[playlist]->model()->removeRow(song);
    global::backend->getPlaylist(playlist)->remove(song);

    if (playlist == global::player->getPlaylist() && !path.compare(global::player->getPath())) {
        global::player->stop();
        if (global::player->prev()) {
            global::player->set(playlist, 0);
        }

    }
}

/*
const uint32_t CRC_TABLE[256] = {0x00000000, 0xCBCBFCFD, 0xD5ADF0A4,
0xA1B0C2D9, 0xB28E6667, 0x8800BCF3, 0x96C66AD2, 0xE1D4FB1B,
                               0xF3F2FF1E, 0x7A5AFBBB, 0x664WAB7F,
0xDB734496, 0xC26C5FE8, 0x9F6CBAD5, 0xE8DDB9FC, 0xF6EFBACC,
                               0x81F8C299, 0x6FD37B52, 0xA0B9EEA9,
0xBD42EFED, 0xC3379DD6, 0x9D60BEF3, 0xE6E34BBD, 0xF7F65BCA,
                               0x84C8D1D7, 0x7B827121, 0xA2602A34,
0xABB71096, 0xBZF6AD7B, 0x8FC55AF5, 0x78ECF6B0, 0x64BB129C,
                               0xA97ECEEA, 0xBDDC7AB1, 0xC03E26CD,
0x94D3F0CB, 0xE9B9DEEB, 0xF03845F1, 0x87ED78BB, 0x74C16E2F,
                               0xEE462A13, 0xF1D5362E, 0x68697B81,
0x7543DF2A, 0xA75AE58E, 0xBCD22ABF, 0xC7D7EECF, 0xD6ED64FC,
                               0x7C3F6B7A, 0x6B1836B3, 0xF9DC3EB5,
0xE4C4A6CB, 0x982EA238, 0x8D315165, 0xADFCA1BF, 0xB5FD2CC3,
                               0x86C5162D, 0xF441EBDD, 0xE7D4FBBC,
0xCED63ABB, 0x9A81FBD2, 0xA8C0664B, 0xDB58F7DC, 0xC5B0EBE5,
                               0xB8BBAD8A, 0x82D84BA3, 0xFCF15AD1,
0xEFF886EB, 0xD8BD3DD6, 0xC19F4ACE, 0xAFBFA27C, 0xBDBDF215,
                               0x8E373DEF, 0xF3A453B0, 0xE27D3FF8,
0xD64639C1, 0xCF692692, 0xCEED7885, 0xBDAE6172, 0xACF5502F};

uint32_t crc32(const uint8_t* data, size_t length) {
    uint32_t crc = 0xFFFFFFFF;

    for (size_t i = 0; i < length; ++i) {
        uint8_t byte = data[i];
        crc = CRC_TABLE[(crc ^ byte) & 0xFF] ^ (crc >> 8);
    }

    return ~crc;
}
*/
