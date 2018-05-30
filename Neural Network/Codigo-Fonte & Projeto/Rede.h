#ifndef REDE_H
#define REDE_H

#include "Matriz.h"
#include "Tipo.h"

class Rede {

    public:
        // construtor
        Rede(unsigned char f, unsigned int i, float a, float e) {
            vies = false;
            funcaoT = f;
            iteracoes = i;
            aprendTaxa = a;
            erroMin = e;
            ent = NULL;
            pesoEntOcu = NULL;
            ocu = NULL;
            pesoOcuSai = NULL;
            sai = NULL;
        }
        // dados
        bool vies;
        unsigned char funcaoT;
        unsigned int iteracoes;
        float aprendTaxa;
        float erroMin;
        Matriz dadosDeTreino;
        Matriz dadosDeTeste;
        // metodos
        void executaTreino(Matriz dados, unsigned int nNeuroOcu);
        void executaTeste(Matriz dados, unsigned int nNeuroOcu, unsigned int nSaida);
        void criaNeuronio(unsigned char tipoCamada);
        void exibeDados(FILE *arqLog, int o, int s);
        void reiniciaRede();

    protected:
        tNeuronioExt *novoNeuroExt();
        tNeuronioOcu *novoNeuroOcu();
        tListaFloat *criaPeso();
        float randomico();
        void setNeuroExt(unsigned char tipoCamada, float n, float e, float s, float v, unsigned int ind);
        tNeuronioExt getNeuroExt(unsigned char tipoCamada, unsigned int ind);
        void setNeuroOcu(float n, float e, float v, float s, unsigned int ind);
        tNeuronioOcu getNeuroOcu(unsigned int ind);
        float obtemSaida(float soma, unsigned char tipo, bool derivada);
        void setLink(unsigned char tipo, float p, unsigned int ind);
        float getLink(unsigned char tipo, unsigned int ind);
        float getErro(tListaFloat *l, unsigned int ind);
        unsigned int valorDesejado(unsigned int indClasse, unsigned int indNeuronio);
        unsigned int retornaClasse(Matriz dados);
        unsigned int obtemIndice(int nNeuronioSaida);

    private:
        tListaNeuronioExt *ent;
        tListaFloat *pesoEntOcu;
        tListaNeuronioOcu *ocu;
        tListaFloat *pesoOcuSai;
        tListaNeuronioExt *sai;

};

#endif
