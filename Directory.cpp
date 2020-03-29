#include "Directory.hpp"
#include "Atributos.hpp"
#include <ncurses.h>
using namespace std;

void Directory::ls(short color) {
    DIR *dir;
    struct dirent *file;
    files.clear();
    string name;
    if ((dir = opendir(atributo.path.c_str())) != NULL) {
        while ((file = readdir(dir)) != NULL) {
            name = file->d_name;
            if (name.at(0) != '.') {
                files.push_back(file);
            }
        }
        int size = 0, x, y;
        int pair;
        string filename, file2;
        init_pair(90, COLOR_WHITE, color);
        init_pair(91, COLOR_BLUE, color);
        init_pair(92, COLOR_BLACK, color);
        for (int i = 0; i < files.size(); i++) {
            filename = files[i]->d_name;
            if (files[i]->d_type == DT_DIR) {
                pair = 91;
            } else {
                if (color == COLOR_WHITE) {
                    pair = 92;
                } else {
                    pair = 90;
                }
            }
            attron(COLOR_PAIR(pair));
            printw((filename + ' ').c_str());
            attroff(COLOR_PAIR(pair));
        }
        printw("\n");
        closedir(dir);
    }
}

void Directory::cd(string line) {
    DIR *dir;
    if ((dir = opendir((atributo.path + '/' +line).c_str())) != NULL) {
        atributo.path = atributo.path + '/' + line;
    } else {
        printw("Carpeta ingresada no existe!!\n");
    }
}

void Directory::getPrePath() {
    string temp = "";
    string newPath;
    int slashes = 0;
    for (int i = 0; i < atributo.path.size(); i++) {
        if(atributo.path.at(i) == '/'){
            slashes++;
        }
    }
    for (int i = 0; i < atributo.path.size(); i++) {
        if (atributo.path.at(i) !=  '/') {
            temp += atributo.path.at(i);
        } else {
            temp = "";
        }
    }
}

/*Directory::~Directory() {
    clearVect();
}*/

void Directory::clearVect() {
    for (dirent *p : files) {
        delete p;
    }
    files.clear();
}