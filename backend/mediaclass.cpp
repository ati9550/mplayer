#include "mediaclass.h"
#include "../global.h"

#include <fstream>
#include <QFileInfo>
#include <QDir>

Playlist::Playlist(std::string path) {
    this->path.assign(path);
    std::ifstream playlistFile(path);

    if (playlistFile.is_open()) {
        std::getline(playlistFile, this->name);
        QListWidget* newWidget = new QListWidget();
        newWidget->setAlternatingRowColors(true);
        QObject::connect(newWidget, &QListWidget::itemActivated,
                         global::window, &MainWindow::itemActivatedHandler);
        global::window->playlistWidget.push_back(newWidget);
        global::window->playlistTab.addTab(newWidget, this->name.c_str());

        std::string line;
        while (std::getline(playlistFile, line)) {
            if (!line.compare("\n")) break;
            this->songs.push_back(Song());
            this->songs[this->songs.size() - 1].path.assign(line);
            global::window->playlistWidget[global::window->playlistWidget.size() - 1]->addItem(QFileInfo(line.c_str()).fileName());
            std::getline(playlistFile, line);
            this->songs[this->songs.size() - 1].size = atoi(line.c_str());
            std::getline(playlistFile, line);
            this->songs[this->songs.size() - 1].hash = atoi(line.c_str());
        }
        playlistFile.close();
    }
    else qWarning("Не удалось открыть плейлист.");
}

Playlist::Playlist() {

}


int Playlist::getLength() {
    return this->songs.size();
}

std::string Playlist::getPath() {
    return this->path;
}

std::string Playlist::getPath(int index) {
    return this->songs[index].path;
}

void Player::play(std::string path) {
    if (path.compare("")) {
        this->path.assign(path);
        QUrl url = QUrl::fromLocalFile(QFileInfo(this->path.c_str()).absoluteFilePath());
        this->qplayer.setMedia(url);
        global::window->positionSlider.setDisabled(true);
        global::window->positionSlider.setValue(0);
        global::window->trackLabel.setText(QString("\nЗагрузка...\n"));
        if (global::player->qplayer.isAvailable())
            global::player->qplayer.play();
        else qWarning("Не удалось открыть песню.");
    }
    this->isChanged = false;
}

void Player::play() {
    if (this->isChanged) {
        if (this->path.compare("")) {
            QUrl url = QUrl::fromLocalFile(QFileInfo(this->path.c_str()).absoluteFilePath());
            this->qplayer.setMedia(url);
            global::window->positionSlider.setDisabled(true);
            global::window->positionSlider.setValue(0);
            global::window->trackLabel.setText(QString("\nЗагрузка...\n"));
            if (global::player->qplayer.isAvailable())
                global::player->qplayer.play();
            else qWarning("Не удалось открыть песню.");
        }
        this->isChanged = false;
    }
    else {
        if (this->qplayer.isAudioAvailable()) this->qplayer.play();
    }
}

int Playlist::save() {
    std::ofstream file;
    file.open(this->path, std::ios::out);

    if (file.is_open()) {
        file << this->name << "\n";
        for(int i = 0; i < this->songs.size(); i++) {
            file <<  this->songs[i].path << "\n";
            file <<  this->songs[i].size << "\n";
            file <<  this->songs[i].hash << "\n";
        }
        file.close();
        return 0;
    }
    else {
        qWarning("Не удалось сохранить плейлист.");
        return 1;
    }
}

void Playlist::setPlaylist(std::string name) {
    this->name.assign(name);
    QString default_dir_name = "Плейлисты";
    if (!QDir(default_dir_name).exists())
        QDir().mkdir(default_dir_name);
    this->path.assign(default_dir_name.toStdString() + "/" + name + ".m3ut");
}

void Playlist::add(std::vector<std::string> path) {
    for (int i = 0; i < path.size(); i++) {
        this->songs.push_back(Song());
        this->songs[this->songs.size() - 1].path.assign(path[i]);
    }
}

void Playlist::remove(int index) {
    this->songs.erase(this->songs.begin() + index);
}

std::string Player::getPath() {
    return this->path;
}

void Player::set(int list, int index) {
    this->isPlaylist = true;
    this->playlist = list;
    this->current = index;
    this->path.assign(global::backend->getPlaylist(list)->getPath(this->current));
    this->isChanged = true;
    if (this->qplayer.state() == QMediaPlayer::PlayingState) this->play();
}

void Player::stop() {
    this->qplayer.stop();
    global::window->positionSlider.setDisabled(true);
    global::window->positionSlider.setValue(0);
    global::window->trackLabel.setText(QString("\nГотов.\n"));
    global::window->coverLabel.reset();
    global::window->durationTime.display("00:00");
}

int Player::next() {
    if (!this->isPlaylist) return 1;
    if (global::backend->getPlaylist(this->playlist)->getLength() - 1 > this->current) {
        this->current++;
        qWarning() << this->current;
        global::window->playlistWidget[playlist]->setCurrentRow(current);
        this->set(this->playlist, this->current);
        if (global::player->qplayer.state() == QMediaPlayer::PlayingState) {
            this->qplayer.stop();
            this->play();
        }
        return 0;
    }
    else return 1;
}

int Player::prev() {
    if (!this->isPlaylist) return 1;
    if (global::backend->getPlaylist(this->playlist)->getLength() > 0 && this->current != 0) {
        this->current--;
        qWarning() << this->current;
        global::window->playlistWidget[playlist]->setCurrentRow(current);
        this->set(this->playlist, this->current);
        if (global::player->qplayer.state() == QMediaPlayer::PlayingState) {
            this->qplayer.stop();
            this->play();
        }
        return 0;
    }
    else return 1;
}

int Player::getPlaylist() {
    return this->playlist;
}

