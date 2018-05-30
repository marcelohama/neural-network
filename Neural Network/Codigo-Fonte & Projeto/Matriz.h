#ifndef MATRIZ_H
#define MATRIZ_H

#include <stdio.h>
#include <stdlib.h>
#include "Tipo.h"

class Matriz {
    public:
        Matriz();
        void showTuplas();
        void showDados();
        void loadFile(char *fileName);
        void setVal(unsigned int linha, unsigned int coluna, int valor);
        int getVal(unsigned int linha, unsigned int coluna);
        unsigned int getClasse(unsigned int ind);
        unsigned int getIndClasse(int classe);
        unsigned int nAtributos;
        unsigned int nClasses;
        unsigned int nElementos;
        unsigned int getIndex(int classe);

    private:
        tLinha *tupla;
        bool aberto;
};

#endif
