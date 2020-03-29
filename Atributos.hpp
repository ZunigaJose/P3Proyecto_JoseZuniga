#pragma once
#include <string>
using namespace std;

class Atributos {
    private:
        string user, machine, path;
    public:
        Atributos();
        string getUser() {return user;};
        string getMachine() {return machine;}
        string getPath() {return path;}
        void leerAtributos();
        void setUser(string usr){user = usr;}
        void setMachine(string mach){machine = mach;}
        void guardarAtributos();
        void print(short);
        friend class Directory;
};