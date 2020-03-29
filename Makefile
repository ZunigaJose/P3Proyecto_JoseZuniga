all:
		g++ main.cpp  Atributos.cpp Directory.cpp -lncurses -o Terminal

cleanup: 
		rm Terminal