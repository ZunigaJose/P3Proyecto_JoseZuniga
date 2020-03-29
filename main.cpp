#include <ncurses.h>
#include "Atributos.hpp"
#include <iostream>
#include <dirent.h>
#include "Directory.hpp"
using namespace std;
string comandos[13];
Atributos atributos;
short backdground = COLOR_BLACK;
Directory dir(atributos);

void llenarComandos();
void terminal();

string getInput (string line, int parametro = 0) {
    int espacios = 0;
    string input;
    for (int i = 0; i < line.size(); i++) {
        if (line.at(i) == ' ') {
            espacios++;
        } else if (espacios == parametro) {
            input += line.at(i);
        }
    }
    return input;
}

int getCommand(string input) {
    for (int i = 0; i < 13; i++) {
        if (comandos[i] == input) {
            return i;
        }        
    }
    return -1;
}

bool validarParametro(string linea) {
    string str = getInput(linea, 1);
    if (str != "") {
        return true;
    } else {
        printw("Debe de ingresar un parametro para este comando!\n");
        return false;
    }
}

void changeColor(string para) {
    init_pair(69, COLOR_WHITE, COLOR_BLACK);
    init_pair(68, COLOR_BLACK, COLOR_WHITE);
    init_pair(67, COLOR_WHITE, COLOR_RED);
    if (para == "black") {
        bkgd(COLOR_PAIR(69));
        backdground = COLOR_BLACK;
    } else if (para == "white") {
        bkgd(COLOR_PAIR(68));
        backdground = COLOR_WHITE;
    } else if (para == "red") {
        bkgd(COLOR_PAIR(67));
        backdground = COLOR_RED;
    } else {
        printw("Parametro no valido\n");
    }
}



int main() {
    start_color();
    initscr();
    scrollok(stdscr, true);
    keypad(stdscr, TRUE);
    llenarComandos();
    atributos.leerAtributos();
    //bkgd()
    char str[80];
    terminal();
    endwin();
}

void terminal() {
    int op;
    atributos.print(backdground);
    char line[80];
    string input2;
    do {
        getstr(line);
        op = getCommand(getInput(line));
        switch (op)
        {
        case -1:
            printw("Comando no encontrado\n");
        break;
        case 1:
            clear();
        break;
        case 2:
            //ls
            dir.ls(backdground);
        break;
        case 3:
            //cd
            if (validarParametro(line)) {
                input2 = getInput(line, 1);
                dir.cd(input2);
            }
        break;
        case 4:
            //cd/
            
        break;
        case 5:
            //del
        break;
        case 6:
            //mkdir
        break;
        case 7:
            //file
        break;
        case 8:
            //write
        break;

        case 9:
            //read
        break;
        case 10:
            if (validarParametro(line)) {
                input2 = getInput(line, 1);
                changeColor(input2);
            }
        break;
        case 11:
            if (validarParametro(line)) {
                input2 = getInput(line, 1);
                atributos.setUser(input2);
                atributos.guardarAtributos();
            }
        break;
        case 12:
            //changeMachine
            if (validarParametro(line)) {
                input2 = getInput(line, 1);
                atributos.setMachine(input2);
                atributos.guardarAtributos();
            }
            break;
        default:
            break;
        }
        atributos.print(backdground);
    } while (op);
    
}

void llenarComandos() {
    comandos[0] = "exit";
    comandos[1] = "clear";
    comandos[2] = "ls";
    comandos[3] = "cd";
    comandos[4] = "cd/";
    comandos[5] = "del";
    comandos[6] = "mkdir";
    comandos[7] = "file";
    comandos[8] = "write";
    comandos[9] = "read";
    comandos[10] = "changeColor";
    comandos[11] = "changeUser";
    comandos[12] = "changeMachine";
}