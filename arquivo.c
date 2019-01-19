/*******************************************************************************
 * arquivo.c                                                                   *
 * Propósito:                                                                  *
 *                                                                             *
 * @author Jéssica Taís C. Rodrigues                                           *
 * @version 1.0 13/06/2017                                                     *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "registro.h"
#include "arquivo.h"

int estruturaArquivo(int conversa, char E[MAX_CAMINHO]){
    FILE *arq, *arqResultado;
    int qtdRegistros = 0;
    Registro reg;
    memset(&reg, 0, sizeof(Registro));

    char nomeArquivo[MAX_CAMINHO+24], nomeArquivoResultado[MAX_CAMINHO+24];
    sprintf(nomeArquivo, "%s%d", E, conversa);
    sprintf(nomeArquivoResultado, "%s%d.bin", TMP, conversa);

    arq = fopen(nomeArquivo, "r");
    arqResultado = fopen(nomeArquivoResultado, "wb");

    reg.conversa = conversa;
    reg.frequencia = 0;

    while(fscanf(arq, "%20s", reg.palavra) != EOF){
        reg.posicao = ftell(arq) - strlen(reg.palavra);
        fwrite(&reg, sizeof(Registro), 1, arqResultado);
        qtdRegistros++;
    }
    fclose(arq);
    fclose(arqResultado);

    return qtdRegistros;
}

void computaFrequencia(char nomeArquivo[MAX_CAMINHO+24]){
    FILE *leituraCont, *leitura, *escrita;
    int i, frequencia;
    Registro reg, ultLido, aux;

    leituraCont = fopen(nomeArquivo, "r+b");
    leitura = fopen(nomeArquivo, "r+b");
    escrita = fopen(nomeArquivo, "r+b");

    fread(&reg, sizeof(Registro), 1, leituraCont);
    while(!feof(leituraCont)){
        frequencia = 1;
        while(fread(&ultLido, sizeof(Registro), 1, leituraCont)
              && !feof(leituraCont) && strcmp(reg.palavra, ultLido.palavra) == 0){
            frequencia++;
        }

        for(i = 0; i < frequencia; i++) {
            fread(&aux, sizeof(Registro), 1, leitura);
            aux.frequencia = frequencia;
            fwrite(&aux, sizeof(Registro), 1, escrita);
        }

        strncpy(reg.palavra, ultLido.palavra, 20);
        reg.conversa = ultLido.conversa;
        reg.frequencia = ultLido.frequencia;
        reg.posicao = ultLido.posicao;
    }

    fclose(leituraCont);
    fclose(leitura);
    fclose(escrita);
}

void imprimeArquivo(char nomeArquivo[MAX_CAMINHO+24]){
    FILE *arq;
    Registro reg;

    arq = fopen(nomeArquivo, "rb");

    printf("-----%s\n", nomeArquivo);
    while(fread(&reg, sizeof(Registro), 1, arq) && !feof(arq)){
        imprimeRegistro(&reg);
    }
    printf("-----%s\n", nomeArquivo);
    fclose(arq);
}

void particiona(FILE *arqLI, FILE *arqEI, FILE *arqLS, FILE* arqES, int esq, int dir, int *novaEsq, int *novaDir, int tamMemoria){
    int lI = esq, eI = esq, lS = dir, eS = dir;
    bool ondeLer = true; // se verdadeira lê no começo, senão lê no final
    Registro ultLido, auxR;

    fseek(arqLI, (lI -1)*sizeof(Registro), SEEK_SET);
    fseek(arqEI, (eI -1)*sizeof(Registro), SEEK_SET);
    fseek(arqLS, (lS -1)*sizeof(Registro), SEEK_SET);
    fseek(arqES, (eS -1)*sizeof(Registro), SEEK_SET);

    BufferOrdenado *buffer;
    buffer = criaBufferOrdenado();

    while(lS >= lI){
        if(buffer->tamBuffer < tamMemoria - 1){
            if(ondeLer){
                // printf("[DEBUG-PARTICIONA] LER-INICIO lI: %d\n", lI);
                fread(&ultLido, sizeof(Registro), 1, arqLI);
                lI++;
                ondeLer = false;
            } else {
                // printf("[DEBUG-PARTICIONA] LER-FIM lS: %d\n", lS);
                fseek(arqLS, (lS - 1)*sizeof(Registro), SEEK_SET);
                fread(&ultLido, sizeof(Registro), 1, arqLS);
                lS--;
                ondeLer = true;
            }
            insereBuffer(buffer, &ultLido);
        }else{ //Quando buffer está cheio
            if(lS == eS) {
                // printf("[DEBUG-PARTICIONA] LER-FIM lS: %d\n", lS);
                fseek(arqLS, (lS - 1)*sizeof(Registro), SEEK_SET);
                fread(&ultLido, sizeof(Registro), 1, arqLS);
                lS--;
                ondeLer = true;    
            } else if(lI == eI) {
                // printf("[DEBUG-PARTICIONA] LER-INICIO lI: %d\n", lI);
                fread(&ultLido, sizeof(Registro), 1, arqLI);
                lI++;
                ondeLer = false;                
            } else if(ondeLer) {
                // printf("[DEBUG-PARTICIONA] LER-INICIO lI: %d\n", lI);                
                fread(&ultLido, sizeof(Registro), 1, arqLI);
                lI++;
                ondeLer = false;
            } else {
                // printf("[DEBUG-PARTICIONA] LER-FIM lS: %d\n", lS);                
                fseek(arqLS, (lS - 1)*sizeof(Registro), SEEK_SET);
                fread(&ultLido, sizeof(Registro), 1, arqLS);
                lS--;
                ondeLer = true;
            }

            //imprimeBuffer(buffer);
            //imprimeRegistro(&ultLido);

            if(comparaRegistro(&ultLido, &(buffer->ultimo->registro)) > 0){
                // printf("[DEBUG-PARTICIONA] INSERE-FIM eS: %d\n", eS);
                fseek(arqES, (eS - 1)*sizeof(Registro), SEEK_SET);
                fwrite(&ultLido, sizeof(Registro), 1, arqES);
                eS--;
            } else if(comparaRegistro(&ultLido, &(buffer->primeiro->registro)) < 0){
                // printf("[DEBUG-PARTICIONA] INSERE-INICIO eI: %d\n", eI);
                fwrite(&ultLido, sizeof(Registro), 1, arqEI);
                eI++;
            } else {
                if(eI - esq < dir - eS) {
                    // printf("[DEBUG-PARTICIONA] INSERE-MIN-INICIO eI: %d\n", eI);
                    removeMinBuffer(buffer, &auxR);
                    fwrite(&auxR, sizeof(Registro), 1, arqEI);
                    eI++;
                } else {
                    // printf("[DEBUG-PARTICIONA] INSERE-MAX-FIM eS: %d\n", eS);
                    fseek(arqES, (eS - 1)*sizeof(Registro), SEEK_SET);
                    removeMaxBuffer(buffer, &auxR);
                    fwrite(&auxR, sizeof(Registro), 1, arqES);
                    eS--;
                }
                insereBuffer(buffer, &ultLido);
            }
        }
    }

    *novaDir = eI;
    *novaEsq = eS;

    while(eI <= eS) {
        removeMinBuffer(buffer, &auxR);
        fwrite(&auxR, sizeof(Registro), 1, arqEI);
        eI++;
    }

    liberaBuffer(buffer);
}

void quickSortExterno(char nomeArquivo[MAX_CAMINHO+24], int esq, int dir, int tamMemoria){
    if(dir-esq < 1){
        return;
    }else{
        int novaEsq, novaDir;

        FILE *leituraI, *escritaI, *leituraS, *escritaS;
        
        leituraI = fopen(nomeArquivo, "r+b"), escritaI = fopen(nomeArquivo, "r+b");
        leituraS = fopen(nomeArquivo, "r+b"), escritaS = fopen(nomeArquivo, "r+b");
        
        particiona(leituraI, escritaI, leituraS, escritaS, esq, dir, &novaEsq, &novaDir, tamMemoria);
        
        fclose(leituraI); fclose(escritaI); fclose(leituraS); fclose(escritaS);

        quickSortExterno(nomeArquivo, esq, novaDir, tamMemoria);
        quickSortExterno(nomeArquivo, novaEsq, dir, tamMemoria);
    }
}

void ordenaArquivo(char nomeArquivo[MAX_CAMINHO+24], int n, int tamMemoria){
    quickSortExterno(nomeArquivo, 1, n, tamMemoria);
}

void uneArquivos(char nomeArquivo1[MAX_CAMINHO+24], char nomeArquivo2[MAX_CAMINHO+24],
                 char nomeArquivoResultado[MAX_CAMINHO+24]){
    FILE *arq1, *arq2, *arqRes;
    Registro reg1, reg2;

    arq1 = fopen(nomeArquivo1, "rb");
    arq2 = fopen(nomeArquivo2, "rb");
    arqRes = fopen(nomeArquivoResultado, "wb");

    fread(&reg1, sizeof(Registro), 1, arq1);
    fread(&reg2, sizeof(Registro), 1, arq2);

    while(!feof(arq1) && !feof(arq2)){
        if(comparaRegistro(&reg1, &reg2) < 0){
            fwrite(&reg1, sizeof(Registro), 1, arqRes);
            fread(&reg1, sizeof(Registro), 1, arq1);
        }else{
            fwrite(&reg2, sizeof(Registro), 1, arqRes);
            fread(&reg2, sizeof(Registro), 1, arq2);            
        }
    }

    while(!feof(arq1)){
        fwrite(&reg1, sizeof(Registro), 1, arqRes);
        fread(&reg1, sizeof(Registro), 1, arq1);        
    }

    while(!feof(arq2)){
        fwrite(&reg2, sizeof(Registro), 1, arqRes);
        fread(&reg2, sizeof(Registro), 1, arq2);        
    }    

    fclose(arq1);
    fclose(arq2);
    fclose(arqRes);
}

void transformaArquivo(char nomeArquivoBin[MAX_CAMINHO+24], char nomeArquivoResultado[MAX_CAMINHO+24]){
    FILE *arqBin, *arqRes;
    Registro reg;

    arqBin = fopen(nomeArquivoBin, "rb");
    arqRes = fopen(nomeArquivoResultado, "w");

    fread(&reg, sizeof(Registro), 1, arqBin);
    while(!feof(arqBin)){
        fprintf(arqRes, "%s,%d,%d,%ld\n", reg.palavra, reg.conversa, reg.frequencia, reg.posicao);
        fread(&reg, sizeof(Registro), 1, arqBin);
    }

    fclose(arqBin);
    fclose(arqRes);
}