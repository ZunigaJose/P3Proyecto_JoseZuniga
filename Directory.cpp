#include "Directory.hpp"
#include "Atributos.hpp"
#include <ncurses.h>
#include <sys/stat.h>
#include <fstream>
#include <iostream>
using namespace std;

bool Directory::isDeleted(string folder) {
    for (int i = 0; i < deleted.size(); i++) {
        if (deleted[i] == folder) {
            return true;
        }
    }
    return false;
}

void Directory::ls(short color) {
    DIR *dir;
    struct dirent *file;
    files.clear();
    string name;
    if ((dir = opendir(atributo.path.c_str())) != NULL) {
        while ((file = readdir(dir)) != NULL) {
            name = file->d_name;
            if (name.at(0) != '.' && !isDeleted(name)) {
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
    if ((dir = opendir((atributo.path + '/' +line).c_str())) != NULL && !isDeleted(line)) {
        atributo.path = atributo.path + '/' + line;
    } else {
        printw("Carpeta ingresada no existe!!\n");
    }
}

void Directory::cdBack() {
    if (atributo.path != getenv("HOME")) {
        getPrePath();
    } else {
        printw("No se puede regresar mas!\n");
    }
}

void Directory::getPrePath() {
    string newPath = "";
    newPath = atributo.path;
    newPath = newPath.substr(0, newPath.find_last_of("/\\"));
    atributo.path = newPath;
}

void Directory::mDir(string folder) {
    DIR *dir;
    const int dir_err = mkdir((atributo.path + "/" + folder).c_str(), S_IRUSR | S_IWUSR);
    if (dir_err == - 1) {
    printw("Error creando el directorio!\n");
    }
}

/*Directory::~Directory() {
    clearVect();
}*/

void Directory::del(string line) {
    DIR *dir;
    if ((dir = opendir((atributo.path + '/' + line).c_str())) != NULL) {
        fstream archivo;
        archivo.open("Deleted.txt", ios::app);
        if (!archivo) {
            archivo.open("Deleted.txt", ios::trunc | ios::out);
            archivo.close();
            archivo.open("Atributos.txt", ios::app);
        }
        archivo << line << ';';
        deleted.push_back(line);
    }
}

int count(string line) {
    int count = 0;
    for (int i = 0; i < line.size(); i++) {
        if (line.at(i) == ';') {
            count++;
        }
    }
    return count;
}

void Directory::leerDel() {
    fstream archivo;
    archivo.open("Deleted.txt", ios::in);
    string line;
    if (archivo) {
        getline(archivo, line);
        int n = 0;
        int tot = count(line);
        string token[tot];
        for (int i = 0; i < line.size(); i++) {
            if (line.at(i) == ';') {
                n++;
            } else {
                token[n] += line.at(i);
            }
        }
        for (int i = 0; i < tot; i++) {
            deleted.push_back(token[i]);
        }
    }
}

void Directory::clearVect() {
    for (dirent *p : files) {
        delete p;
    }
    files.clear();
}