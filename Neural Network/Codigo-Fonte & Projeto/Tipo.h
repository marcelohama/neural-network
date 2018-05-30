#ifndef TIPO_H
#define TIPO_H

typedef struct NeuronioExt tNeuronioExt;
typedef struct NeuronioOcu tNeuronioOcu;
typedef struct ListaNeuronioExt tListaNeuronioExt;
typedef struct ListaNeuronioOcu tListaNeuronioOcu;
typedef struct fLista tListaFloat;

// lista de valores
typedef struct Linha {
   int reg;
   struct Linha *prox;
} tLinha;

// lista de floats
struct fLista {
    float v;
    struct fLista *prox;
};

// neuronios de entrada e saida
struct NeuronioExt {
    // net e vies
    float net;
    float saida;
    float vies;
    // erro
    float erro;
    // lista de neuronios da camada oculta
    tListaFloat *listPesoNeuroOcul;
};
// neuronios ocultos
struct NeuronioOcu {
    // net
    float net;
    float saida;
    // erro
    float erro;
    // vies
    float vies;
};

// lista de neuronios
struct ListaNeuronioExt {
    tNeuronioExt *reg;
    struct ListaNeuronioExt *prox;
};
struct ListaNeuronioOcu {
    tNeuronioOcu *reg;
    struct ListaNeuronioOcu *prox;
};

#endif
