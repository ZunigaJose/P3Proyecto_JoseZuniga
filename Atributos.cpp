#include "Atributos.hpp"
#include <string>
#include <ncurses.h>
#include <fstream>

Atributos::Atributos() {
    path = getenv("HOME");
}

void Atributos::leerAtributos() {
    fstream archivo;
    archivo.open("Atributos.txt", ios::in);
    if(!archivo) {
        archivo.open("Atributos.txt", ios::trunc | ios::out);
        archivo.close();
        archivo.open("Atributos.txt", ios::in);
        user = "home";
        machine = "vm-gauss";
        guardarAtributos();
    } else {
        string line;
        getline(archivo, line);
        int n = 0;
        string token [2];
        for (int i = 0; i < line.size(); i++) {
            if(line.at(i) == ';') {
                n++;
            } else {
                token[n] += line.at(i);
            }
        }
        user = token[0];
        machine = token[1];
        archivo.close();
    }
}

void Atributos::guardarAtributos() {
    fstream archivo;
    archivo.open("Atributos.txt", ios::out);
    if(archivo) {
        archivo << user << ';' << machine << ';';
    }
    archivo.close();
}

void Atributos::print(short color) {
    string out = "~";
    string det = user + '@' + machine;
    start_color();
    init_pair(11, COLOR_GREEN,color);
    attron(COLOR_PAIR(11));
    printw(det.c_str());
    attroff(COLOR_PAIR(11));
    printw(":");
    if (path != getenv("HOME")) {
        out += path;
    } /*else {
        out + '~';
    }*/
    init_pair(12, COLOR_BLUE, color);
    attron(COLOR_PAIR(12));
    printw(out.c_str());
    attroff(COLOR_PAIR(12));
    printw("$ ");
}