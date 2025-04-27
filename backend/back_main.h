#ifndef BACK_MAIN_H
#define BACK_MAIN_H

#include "mediaclass.h"
#include "../global.h"
#include <vector>

class Backend {
private:
    std::vector<Playlist*> playlist;
public:
    Backend();
    ~Backend();
    Playlist* getPlaylist(int list);
    void addNewPlaylist(std::string name);
    void remPlaylist(int playlist);
    int hash(std::string path);
};

#endif // BACK_MAIN_H
