#include "back_main.h"

#include <string>
#include <fstream>
#include <iostream>


Backend::Backend() {
    global::player = new Player();
    std::ifstream listFile("list.txt");

    if (listFile.is_open()) {
        std::string line;

        while (std::getline(listFile, line)) {
            if (!line.compare("\n")) break;
            this->playlist.push_back(new Playlist(line));
        }
        listFile.close();
    }
    else qWarning("Не удалось открыть список.");
}

Playlist* Backend::getPlaylist(int list) {
    return this->playlist[list];
}

void Backend::addNewPlaylist(std::string name) {
    Playlist* newPlaylist = new Playlist();
    this->playlist.push_back(newPlaylist);
    newPlaylist->setPlaylist(name);

    QListWidget* newWidget = new QListWidget();
    newWidget->setAlternatingRowColors(true);
    QObject::connect(newWidget, &QListWidget::itemActivated,
                     global::window, &MainWindow::itemActivatedHandler);
    global::window->playlistWidget.push_back(newWidget);
    global::window->playlistTab.addTab(newWidget, name.c_str());
}

void Backend::remPlaylist(int playlist) {
    this->playlist.erase(this->playlist.begin() + playlist);
}


Backend::~Backend() {
    std::ofstream file;
    file.open("list.txt", std::ios::out);

    for (int i = 0; i < this->playlist.size(); i++) {
        if (file.is_open() && !this->playlist[i]->save())
            file <<  this->playlist[i]->getPath() << "\n";
        else {
            qWarning("Не удалось сохранить список плейлистов.");
            break;
        }
    }
    file.close();
}

int Backend::hash(std::string path) {
    return 0;
}
