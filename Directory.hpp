#pragma once
#include <dirent.h>
#include <vector>
#include <string>
#include "Atributos.hpp"
using namespace std;

class Directory {
    private:
        vector<dirent*> files;
        Atributos &atributo;
        vector<string> deleted;
        void clearVect();
    public:
    Directory(Atributos &Atributo) : atributo(Atributo) {leerDel();}
    //~Directory();
    void ls(short);
    void getPrePath();
    void mDir(string);
    void cdBack();
    void cd(string);
    void del(string);
    bool isDeleted(string);
    void leerDel();
};