#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "Rede.h"

int randSeed = time(NULL);

/****************************************************
| criação e destruicao de neuronios e links da rede |
****************************************************/
// retorna um valor randomico entre -1 e 1
float Rede::randomico() {
    srand(randSeed);
    randSeed = rand();
    return (float)(randSeed%200)/100-1;
}
// criacao de um registro de lista float
tListaFloat *Rede::criaPeso() {
    tListaFloat *ptNovo = (tListaFloat*)malloc(sizeof(tListaFloat));
    ptNovo->v = randomico();
    ptNovo->prox = NULL;
    return ptNovo;
}
// criacao de novas instancias de neuronios extremos
tNeuronioExt *Rede::novoNeuroExt() {
    tNeuronioExt *ptNovo = (tNeuronioExt*)malloc(sizeof(tNeuronioExt));
    ptNovo->net = 0;
    ptNovo->erro = 0;
    ptNovo->saida = 0;
    if(vies == true) ptNovo->vies = randomico();
    else ptNovo->vies = 0;
    return ptNovo;
}
// criacao de novas instancias de neuronios ocultos
tNeuronioOcu *Rede::novoNeuroOcu() {
    tNeuronioOcu *ptNovo = (tNeuronioOcu*)malloc(sizeof(tNeuronioOcu));
    ptNovo->net = 0;
    ptNovo->erro = 0;
    ptNovo->saida = 0;
    if(vies == true) ptNovo->vies = randomico();
    else ptNovo->vies = 0;
    // cria as conexoes das entradas com os pesos
    tListaNeuronioExt *ptPercorreE = ent;
    while(ptPercorreE != NULL) {
        if(pesoEntOcu == NULL) pesoEntOcu = criaPeso();
        else {
            tListaFloat *ptPercorreP = pesoEntOcu;
            while(ptPercorreP->prox != NULL) {
                ptPercorreP = ptPercorreP->prox;
            }
            ptPercorreP->prox = criaPeso();
        }
        ptPercorreE = ptPercorreE->prox;
    }
    // cria as conexoes das saidas com os pesos
    tListaNeuronioExt *ptPercorreS = sai;
    while(ptPercorreS != NULL) {
        if(pesoOcuSai == NULL) pesoOcuSai = criaPeso();
        else {
            tListaFloat *ptPercorreP = pesoOcuSai;
            while(ptPercorreP->prox != NULL) {
                ptPercorreP = ptPercorreP->prox;
            }
            ptPercorreP->prox = criaPeso();
        }
        ptPercorreS = ptPercorreS->prox;
    }
    return ptNovo;
}
// dada uma camada, cria um neuronio e conecta-o com os neuronios das camadas adjacentes
void Rede::criaNeuronio(unsigned char tipoCamada) {
    // caso seja um neuronio de entrada
    if(tipoCamada == 0) {
        // criando neuronio...
        tListaNeuronioExt *ptNovoExt = (tListaNeuronioExt*)malloc(sizeof(tListaNeuronioExt));
        ptNovoExt->reg = novoNeuroExt();
        ptNovoExt->prox = NULL;
        if(ent == NULL) ent = ptNovoExt;
        else {
            tListaNeuronioExt *ptPercorre = ent;
            while(ptPercorre->prox != NULL) ptPercorre = ptPercorre->prox;
            ptPercorre->prox = ptNovoExt;
        }
    }
    // caso seja um neuronio oculto
    else if(tipoCamada == 1) {
        // criando neuronio...
        tListaNeuronioOcu *ptNovoOcu = (tListaNeuronioOcu*)malloc(sizeof(tListaNeuronioOcu));
        ptNovoOcu->reg = novoNeuroOcu();
        ptNovoOcu->prox = NULL;
        if(ocu == NULL) ocu = ptNovoOcu;
        else {
            tListaNeuronioOcu *ptPercorre = ocu;
            while(ptPercorre->prox != NULL) ptPercorre = ptPercorre->prox;
            ptPercorre->prox = ptNovoOcu;
        }
    }
    // caso seja um neuronio de saida
    else if(tipoCamada == 2) {
        // criando neuronio...
        tListaNeuronioExt *ptNovoExt = (tListaNeuronioExt*)malloc(sizeof(tListaNeuronioExt));
        ptNovoExt->reg = novoNeuroExt();
        ptNovoExt->prox = NULL;
        if(sai == NULL) sai = ptNovoExt;
        else {
            tListaNeuronioExt *ptPercorre = sai;
            while(ptPercorre->prox != NULL) ptPercorre = ptPercorre->prox;
            ptPercorre->prox = ptNovoExt;
        }
    }
}
void Rede::reiniciaRede() {
    ent = NULL;
    pesoEntOcu = NULL;
    ocu = NULL;
    pesoOcuSai = NULL;
    sai = NULL;
}

/********************************************************
| atribuicao e retorno de valores dos neuronios e links |
********************************************************/
// atribui valores a um neuronio de extremidade, dado seu indice e sua camada
void Rede::setNeuroExt(unsigned char tipoCamada, float n, float e, float s, float v, unsigned int ind) {
    tListaNeuronioExt *ptPercorre = NULL;
    if(tipoCamada == 0) ptPercorre = ent;
    else if(tipoCamada == 2) ptPercorre = sai;
    for(unsigned int i=0;i<ind&&ptPercorre != NULL;i++) {
        ptPercorre = ptPercorre->prox;
    }
    ptPercorre->reg->net = n;
    ptPercorre->reg->erro = e;
    ptPercorre->reg->vies = v;
    ptPercorre->reg->saida = s;
}
// retorna um neuronio de extremidade, dado seu indice e sua camada
tNeuronioExt Rede::getNeuroExt(unsigned char tipoCamada, unsigned int ind) {
    tListaNeuronioExt *ptPercorre = NULL;
    if(tipoCamada == 0) ptPercorre = ent;
    else if(tipoCamada == 2) ptPercorre = sai;
    for(unsigned int i=0;i<ind&&ptPercorre != NULL;i++) {
        ptPercorre = ptPercorre->prox;
    }
    return *(ptPercorre->reg);
}
// atribui valores a um neuronio oculto, dado seu indice e sua camada
void Rede::setNeuroOcu(float n, float e, float v, float s, unsigned int ind) {
    tListaNeuronioOcu *ptPercorre = ocu;
    for(unsigned int i=0;i<ind&&ptPercorre != NULL;i++) {
        ptPercorre = ptPercorre->prox;
    }
    ptPercorre->reg->vies = v;
    ptPercorre->reg->net = n;
    ptPercorre->reg->erro = e;
    ptPercorre->reg->saida = s;
}
// retorna um neuronio oculto, dado seu indice e sua camada
tNeuronioOcu Rede::getNeuroOcu(unsigned int ind) {
    tListaNeuronioOcu *ptPercorre = ocu;
    for(unsigned int i=0;i<ind&&ptPercorre != NULL;i++) {
        ptPercorre = ptPercorre->prox;
    }
    return *(ptPercorre->reg);
}
// atribui valores a um link, dado seu tipo, seu peso e seu indice
void Rede::setLink(unsigned char tipo, float p, unsigned int ind) {
    tListaFloat *ptPercorre = NULL;
    if(tipo == 0) ptPercorre = pesoEntOcu;
    else if(tipo == 1) ptPercorre = pesoOcuSai;
    for(unsigned int i=0;i<ind&&ptPercorre != NULL;i++) {
        ptPercorre = ptPercorre->prox;
    }
    ptPercorre->v = p;
}
// retorna um link, dado seu tipo e seu indice
float Rede::getLink(unsigned char tipo, unsigned int ind) {
    tListaFloat *ptPercorre = NULL;
    if(tipo == 0) ptPercorre = pesoEntOcu;
    else if(tipo == 1) ptPercorre = pesoOcuSai;
    for(unsigned int i=0;i<ind&&ptPercorre != NULL;i++) {
        ptPercorre = ptPercorre->prox;
    }
    return ptPercorre->v;
}

/*************************
| funcoes de rede neural |
*************************/
// obtem o net, dada a soma e a funcao
float Rede::obtemSaida(float net, unsigned char tipo, bool derivada) {
    if(derivada == false) {
        if(tipo == 0) return net/2;
        else if(tipo == 1) {
            if(net < -9) return 0;
            if(net > 14) return 1;
            return 1/(1+exp(-net));
        }
        else if(tipo == 2) {
            if(net < -6) return -1;
            if(net > 7) return 1;
            return (1-exp(-2*net))/(1+exp(-2*net));
        }
    }
    else {
        if(tipo == 0) return 0.5;
        else if(tipo == 1) {
            if(net > 9) return 0;
            if(net < -9) return 0;
            return (1/(1+exp(-net)))*(1-(1/(1+exp(-net))));
        }
        else if(tipo == 2) {
            if(net > 5) return 0;
            if(net < -5) return 0;
            return 1-(1-exp(-2*net))/(1+exp(-2*net))*(1-exp(-2*net))/(1+exp(-2*net));
        }
    }
    return 0;
}
// retorna um link, dado seu tipo e seu indice
float Rede::getErro(tListaFloat *l, unsigned int ind) {
    tListaFloat *ptPercorre = l;
    for(unsigned int i=0;i<ind&&ptPercorre != NULL;i++) {
        ptPercorre = ptPercorre->prox;
    }
    return ptPercorre->v;
}
// mapeia a entrada/saida da rede
unsigned int Rede::valorDesejado(unsigned int indClasse, unsigned int indNeuronio) {
    if(indClasse == indNeuronio) return 1;
    else return 0;
}
// retorna o indice do neuronio de maior saida
unsigned int Rede::obtemIndice(int nNeuronioSaida) {
    float val = -1;
    unsigned int index = 0;
    for(int i=0;i<nNeuronioSaida;i++) {
        if(getNeuroExt(2,i).saida > val) {
            index = i;
            val = getNeuroExt(2,i).saida;
        }
    }
    return index+1;
}
// executa o treinamento
void Rede::executaTreino(Matriz dados, unsigned int nNeuroOcu) {
    float erroGeral;
    bool erroOk;
    // para todos os vetores de entradas...
    FILE *arqLog = fopen("logTreino.txt","w");
    for(unsigned int iteracoesGerais=0;iteracoesGerais<iteracoes;iteracoesGerais++) {
        erroOk = true;
        for(unsigned int entVet=0;entVet<(dados.nElementos)/(dados.nAtributos+1);entVet++) {
            tListaNeuronioExt *ptPercorreE = ent;
            // passo 1 - para entrada de vetor, atribui-o nos neuronios de entrada -> OK!
            for(unsigned int ind=0;ind<dados.nAtributos;ind++) {
                setNeuroExt(0,0,0,dados.getVal(entVet,ind),getNeuroExt(0,ind).vies,ind);
                //printf("[%f]\n",getNeuroExt(0,ind).saida); system("pause");
                ptPercorreE = ptPercorreE->prox;
            }
            // passo 2 - calculo dos nets dos neuronios ocultos -> OK!
            for(unsigned int indOcu=0;indOcu<nNeuroOcu;indOcu++) {
                float net = getNeuroOcu(indOcu).vies;
                for(unsigned int indEnt=0;indEnt<dados.nAtributos;indEnt++) {
                    net += getLink(0,indEnt*nNeuroOcu+indOcu)*getNeuroExt(0,indEnt).saida;
                }
                // passo 3 - aplicam-se as funcoes de transferencia para obter as saidas da camada oculta -> OK!
                float saida = obtemSaida(net,funcaoT,false);
                setNeuroOcu(net,getNeuroOcu(indOcu).erro,getNeuroOcu(indOcu).vies,saida,indOcu);
            }
            // passo 4 - saidas dos neuronios da camada oculta enviadas para as entradas dos neuronios da camada de saida -> OK!
            for(unsigned int indSai=0;indSai<dados.nClasses;indSai++) {
                float net = getNeuroExt(2,indSai).vies;
                for(unsigned int indOcu=0;indOcu<nNeuroOcu;indOcu++) {
                    net += getLink(1,indOcu*dados.nClasses+indSai)*getNeuroOcu(indOcu).saida;
                }
                // passo 5 - calculam-se as saídas dos neurônios da camada de saída - OK!
                float saida = obtemSaida(net,funcaoT,false);
                setNeuroExt(2,net,getNeuroExt(2,indSai).erro,saida,getNeuroExt(2,indSai).vies,indSai);
            }
            // passo 6 -  para cada neuronio da saida, calculam-se o erro e salva-os - OK!
            for(unsigned int indSai=0;indSai<dados.nClasses;indSai++) {
                int desejado;
                if(indSai+1 == dados.getIndex((int)dados.getVal(entVet,dados.nAtributos))) desejado = 1;
                else desejado = 0;
                float obtido = getNeuroExt(2,indSai).saida;
                float erroSai = (desejado-obtido)*obtemSaida(getNeuroExt(2,indSai).net,funcaoT,true);
                setNeuroExt(2,getNeuroExt(2,indSai).net,erroSai,getNeuroExt(2,indSai).saida,getNeuroExt(2,indSai).vies,indSai);
                //printf("[c%d - des: %d --- obt: %f --- erro: %f]\n",dados.getVal(entVet,dados.nAtributos), desejado, obtido, getNeuroExt(2,indSai).erro);
            }
            // passo 7 -  para cada neuronio oculto, calculam-se o erro e salva-os - OK!
            for(unsigned int indOcu=0;indOcu<nNeuroOcu;indOcu++) {
                float erroOcu = 0;
                for(unsigned int indSai=0;indSai<dados.nClasses;indSai++) {
                    erroOcu += getNeuroExt(2,indSai).erro*getLink(1,indSai+indOcu*dados.nClasses);
                }
                erroOcu *= obtemSaida(getNeuroOcu(indOcu).net,funcaoT,true);
                setNeuroOcu(getNeuroOcu(indOcu).net,erroOcu,getNeuroOcu(indOcu).vies,getNeuroOcu(indOcu).saida,indOcu);
                //printf("erro: %f]\n",getNeuroOcu(indOcu).erro);
            }
            // passo 8 - atualizam-se os pesos dos neuronios da camada de saida - OK!
            for(unsigned int indOcu=0;indOcu<nNeuroOcu;indOcu++) {
                for(unsigned int indSai=0;indSai<dados.nClasses;indSai++) {
                    float novoPeso = getLink(1,indOcu*dados.nClasses+indSai)+aprendTaxa*getNeuroExt(2,indSai).erro*getNeuroOcu(indOcu).saida;
                    setLink(1,novoPeso,indOcu*dados.nClasses+indSai);
                    //printf("[%f]\n",novoPeso);
                }
            }
            // passo 9 - atualizam-se os pesos da camada oculta - OK!
            for(unsigned int indEnt=0;indEnt<dados.nAtributos;indEnt++) {
                for(unsigned int indOcu=0;indOcu<nNeuroOcu;indOcu++) {
                    float novoPeso = getLink(0,indEnt*nNeuroOcu+indOcu)+aprendTaxa*getNeuroOcu(indOcu).erro*getNeuroExt(0,indEnt).net;
                    setLink(0,novoPeso,indEnt*nNeuroOcu+indOcu);
                    //printf("[%f]\n",novoPeso);
                }
            }
            // atualizam-se os vieses
            for(unsigned int indOcu=0;indOcu<nNeuroOcu;indOcu++) {
                setNeuroOcu(getNeuroOcu(indOcu).net,getNeuroOcu(indOcu).erro,getNeuroOcu(indOcu).vies+aprendTaxa*getNeuroOcu(indOcu).erro,getNeuroOcu(indOcu).saida,indOcu);
            }
            for(unsigned int indSai=0;indSai<dados.nClasses;indSai++) {
                float n = getNeuroOcu(indSai).net;
                float e = getNeuroExt(2,indSai).erro;
                float v = getNeuroExt(2,indSai).vies+aprendTaxa*getNeuroExt(2,indSai).erro;
                float s = getNeuroExt(2,indSai).saida;
                setNeuroExt(2,n,e,s,v,indSai);
            }
            // passo 10 - calcula-se o erro da rede
            erroGeral = 0;
            for(unsigned int indSai=0;indSai<dados.nClasses;indSai++) {
                erroGeral += getNeuroExt(2,indSai).erro*getNeuroExt(2,indSai).erro;
            }
            erroGeral /= 2;
            printf("iteracao %4.0d --- linha %4.0d --- erro: %f\n",iteracoesGerais+1,entVet+1,erroGeral); //system("pause");
            exibeDados(arqLog,nNeuroOcu,dados.nClasses);
            // se o erro for menor que o erro minimo, para o treinamento
            if(erroGeral > erroMin) erroOk = false;
        }
        if(erroOk == true) break;
    }
    fclose(arqLog);
}
// executa o teste
void Rede::executaTeste(Matriz dados, unsigned int nNeuroOcu, unsigned int nSaida) {
    FILE *arqLog = fopen("logTeste.txt","w");
    unsigned int matrizConfusao[nSaida][nSaida];
    for(unsigned int i=0;i<nSaida;i++) {
        for(unsigned int j=0;j<nSaida;j++) {
            matrizConfusao[i][j] = 0;
        }
    }
    for(unsigned int entVet=0;entVet<(dados.nElementos)/(dados.nAtributos+1);entVet++) {
        tListaNeuronioExt *ptPercorreE = ent;
        // passo 1 - para entrada de vetor, atribui-o nos neuronios de entrada -> OK!
        for(unsigned int ind=0;ind<dados.nAtributos;ind++) {
            setNeuroExt(0,0,0,dados.getVal(entVet,ind),getNeuroExt(0,ind).vies,ind);
            ptPercorreE = ptPercorreE->prox;
        }
        // passo 2 - calculo dos nets dos neuronios ocultos -> OK!
        for(unsigned int indOcu=0;indOcu<nNeuroOcu;indOcu++) {
            float net = getNeuroOcu(indOcu).vies;
            for(unsigned int indEnt=0;indEnt<dados.nAtributos;indEnt++) {
                net += getLink(0,indEnt*nNeuroOcu+indOcu)*getNeuroExt(0,indEnt).saida;
            }
            // passo 3 - aplicam-se as funcoes de transferencia para obter as saidas da camada oculta -> OK!
            float saida = obtemSaida(net,funcaoT,false);
            setNeuroOcu(net,getNeuroOcu(indOcu).erro,getNeuroOcu(indOcu).vies,saida,indOcu);
            //printf("%f %f\n",getNeuroOcu(indOcu).net,getNeuroOcu(indOcu).saida); system("pause");
        }
        // passo 4 - saidas dos neuronios da camada oculta enviadas para as entradas dos neuronios da camada de saida -> OK!
        for(unsigned int indSai=0;indSai<dados.nClasses;indSai++) {
            float net = 0;
            for(unsigned int indOcu=0;indOcu<nNeuroOcu;indOcu++) {
                net += getLink(1,indOcu*dados.nClasses+indSai)*getNeuroOcu(indOcu).saida;
            }
            // passo 5 - calculam-se as saídas dos neurônios da camada de saída - OK!
            float saida = obtemSaida(net,funcaoT,false);
            setNeuroExt(2,net,getNeuroExt(2,indSai).erro,saida,getNeuroExt(2,indSai).vies,indSai);
        }
        exibeDados(arqLog,nNeuroOcu,dados.nClasses);
        // passo 6 -  para cada neuronio da saida, confronta o resuoltado real com a classificacao da rede
        int desejado = dados.getVal(entVet,dados.nAtributos);
        int obtido = dados.getClasse(obtemIndice(dados.nClasses));
        desejado = dados.getIndex((int)desejado);
        obtido = dados.getIndex((int)obtido);
        //printf("Ent:%d -> Ind_Desejado: %d, Ind_Obtido: %d\n", entVet, (int)desejado, (int)obtido); system("pause");
        matrizConfusao[(int)obtido-1][(int)desejado-1]++;
    }
    FILE *arqMatriz = fopen("MatrizConf.csv","w");
    if(arqMatriz == NULL) return;
    fprintf(arqMatriz,"Horizontal=Valor_Obtido x Vertical=Valor_Real\n");
    fprintf(arqMatriz,"x,");
    for(unsigned int i=0;i<nSaida;i++) {
        fprintf(arqMatriz,"%d",dados.getClasse(i+1));
        if(i+1<nSaida) fputc(',',arqMatriz);
    }
    fputc(10,arqMatriz);

    for(unsigned int i=0;i<nSaida;i++) {
        fprintf(arqMatriz,"%d,",dados.getClasse(i+1));
        for(unsigned int j=0;j<nSaida;j++) {
            fprintf(arqMatriz,"%d",matrizConfusao[i][j]);
            if(j+1<nSaida) fprintf(arqMatriz,",");
        }
        fputc(10,arqMatriz);
    }
    fclose(arqMatriz);
}
// exibe em console os dados
void Rede::exibeDados(FILE *arqLog, int o, int s) {
    // criacao do arquivo de dados
    int cont = 0;
    tListaFloat *LEO = pesoEntOcu;
    tListaFloat *LOS = pesoOcuSai;
    tListaNeuronioExt *NE = ent;
    tListaNeuronioExt *NS = sai;
    tListaNeuronioOcu *NO = ocu;
    fprintf(arqLog,"\n================================================================");
    fprintf(arqLog,"\nneuronios de entrada:\n");
    while(NE != NULL) {
        fprintf(arqLog,"[saida = %f]\n",NE->reg->saida);
        NE = NE->prox;
    }
    fprintf(arqLog,"\n\npesos dos links Entrada<->Oculto:\n");
    while(LEO != NULL) {
        fprintf(arqLog,"[%.2f] ",LEO->v);
        LEO = LEO->prox;
        if(++cont == o) {
            cont = 0;
            fprintf(arqLog,"\n");
        }
    }
    fprintf(arqLog,"\nneuronios ocultos:\n");
    while(NO != NULL) {
        fprintf(arqLog,"[net = %.2f][saida = %.2f][vies = %.2f]\n",NO->reg->net,NO->reg->saida,NO->reg->vies);
        NO = NO->prox;
    }
    cont = 0;
    fprintf(arqLog,"\n\npesos dos links Oculto<->Saida:\n");
    while(LOS != NULL) {
        fprintf(arqLog,"[%.2f] ",LOS->v);
        LOS = LOS->prox;
        if(++cont == s) {
            cont = 0;
            fprintf(arqLog,"\n");
        }
    }
    fprintf(arqLog,"\nneuronios de saida:\n");
    while(NS != NULL) {
        fprintf(arqLog,"[net = %.2f][saida = %.2f][vies = %.2f]\n",NS->reg->net,NS->reg->saida,NS->reg->vies);
        NS = NS->prox;
    }
    fprintf(arqLog,"\n================================================================");
}
