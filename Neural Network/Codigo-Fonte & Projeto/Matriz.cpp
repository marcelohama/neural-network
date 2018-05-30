#include "Matriz.h"

Matriz::Matriz() {
    aberto = false;
    tupla = NULL;
    nAtributos = 0;
    nClasses = 0;
    nElementos = 0;
}

void Matriz::loadFile(char *fileName) {
    // tentativa de abertura de arquivo
    FILE *arqTreino = fopen(fileName,"r");
    if(fileName == NULL || arqTreino == NULL) {
        return;
    }
    aberto = true;

    bool neg;
    bool flag = false;
    char caracter = 'x';
    float cla = -1;
    tLinha *novaTupla = NULL;

    while(caracter != EOF) {
        // alocagem de uma nova linha
        nElementos++;
        novaTupla = (tLinha*)malloc(sizeof(tLinha));
        novaTupla->prox = NULL;
        novaTupla->reg = 0;
        // leitura de um valor
        neg = false;
        caracter = fgetc(arqTreino);
        while(caracter != ',' && caracter != 10 && caracter != EOF) {
            if(caracter == '-') neg = true;
            else {
                novaTupla->reg *= 10;
                novaTupla->reg += caracter-48;
            }
            caracter = fgetc(arqTreino);
        }
        if(neg == true) novaTupla->reg *= -1;

        if(caracter == 10) {
            flag = true;
            if(cla != novaTupla->reg) {
                nClasses++;
                cla = novaTupla->reg;
            }
        }
        if(flag == false) nAtributos++;
        // insercao na lista
        if(tupla == NULL) {
            tupla = novaTupla;
        } else {
            tLinha *pt = tupla;
            while(pt->prox != NULL) pt = pt->prox;
            pt->prox = novaTupla;
        }
    }
    nElementos = nElementos-nElementos%(nAtributos+1);
}

unsigned int Matriz::getIndClasse(int classe) {
    if(aberto == false) return 0;
    unsigned int indC = 0;
    int classAnt = -1;
    for(unsigned int i=0;i<nElementos/(nAtributos+1);i++) {
        if(classAnt != getVal(i,nAtributos)) {
            indC++;
            classAnt = (int)getVal(i,nAtributos);
        }
        if(getVal(i,nAtributos) == classe) {
            return indC;
        }
    }
    return 0;
}

void Matriz::showTuplas() {
    if(aberto == false) return;
    tLinha *pt = tupla;
    int lCont = 0;
    printf("\n");
    for(unsigned int i=0;i<nElementos;i++) {
        printf("%d   ",pt->reg);
        lCont++;
        if(lCont%(nAtributos+1) == 0) {
            lCont = 0;
            printf("\n");
        }
        pt = pt->prox;
    }
}

void Matriz::showDados() {
    if(aberto == false) return;
    printf("\nnClasses = %d\nnAtributos = %d\nnElementos = %d",nClasses,nAtributos,nElementos);
}

void Matriz::setVal(unsigned int linha, unsigned int coluna, int valor) {
    if(aberto == false) return;
    if(linha*(nAtributos+1)+coluna > nElementos || coluna > nAtributos+1) {
        printf("\nfora de range...");
        return;
    }
    tLinha *pt = tupla;
    for(unsigned int i=0;i<linha*(nAtributos+1)+coluna;i++) {
        pt = pt->prox;
    }
    pt->reg = valor;
}

int Matriz::getVal(unsigned int linha, unsigned int coluna) {
    if(aberto == false) return 0;
    if(linha*(nAtributos+1)+coluna > nElementos || coluna > nAtributos+1) {
        printf("\nfora de range...");
        return 0;
    }
    tLinha *pt = tupla;
    for(unsigned int i=0;i<linha*(nAtributos+1)+coluna;i++) {
        pt = pt->prox;
    }
    return pt->reg;
}

unsigned int Matriz::getClasse(unsigned int ind) {
    if(aberto == false) return 0;
    int classeAnt = -1;
    for(unsigned int i=0;i<nElementos/(nAtributos+1);i++) {
        if(getVal(i,nAtributos) != classeAnt) {
            classeAnt = getVal(i,nAtributos);
            ind--;
        }
        if(ind == 0) return classeAnt;
    }
    return 0;
}

unsigned int Matriz::getIndex(int classe) {
    if(aberto == false) return 0;
    int classeAnt = -1, ind = 0;
    for(unsigned int i=0;i<nElementos/(nAtributos+1);i++) {
        if(getVal(i,nAtributos) != classeAnt) {
            classeAnt = getVal(i,nAtributos);
            ind++;
        }
        if(classeAnt == classe) return ind;
    }
    return 0;
}
