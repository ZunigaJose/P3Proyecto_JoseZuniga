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
        void clearVect();
    public:
    Directory(Atributos &Atributo) : atributo(Atributo) {}
    //~Directory();
    void ls(short);
    void getPrePath();
    void cd(string);
};