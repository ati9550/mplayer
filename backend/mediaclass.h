#ifndef MEDIACLASS_H
#define MEDIACLASS_H

#include <string>
#include <vector>
#include <QMediaPlayer>

struct Song {
    std::string path;
    int size;
    int hash;
};

class Playlist {
private:
    std::string path;
    std::string name;
    std::vector<Song> songs;
public:
    Playlist(std::string path);
    Playlist();
    void add(std::vector<std::string> path);
    void remove(int index);

    void update();
    void generate(std::string path);
    int save();
    void setPlaylist(std::string name);

    int getLength();
    std::string getPath();
    std::string getPath(int index);
};

class Player : public QObject {
    Q_OBJECT
public slots:
    void stop();
    int next();
    int prev();
private:
    std::string path;
    int playlist;
    int current;
    bool isChanged = false;
public:
    void play(std::string path);
    void play();

    QMediaPlayer qplayer;

    bool isPlaylist = false;
    std::string getPath();
    void set(int playlist, int index);
    int getPlaylist();
};

#endif // MEDIACLASS_H
