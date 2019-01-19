/*******************************************************************************
 * resolucao.c                                                                 *
 * Propósito:                                                                  *
 *                                                                             *
 * @author Jéssica Taís C. Rodrigues                                           *
 * @version 1.0 13/06/2017                                                     *
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registro.h"
#include "arquivo.h"
#include "resolucao.h"


void resolve(int D, int M, char E[MAX_CAMINHO], char S[MAX_CAMINHO]){
    int i, numRegistros, tamMemoria;
    char nomeArquivo[MAX_CAMINHO+24], nomeArquivo2[MAX_CAMINHO+24], nomeArquivoRes[MAX_CAMINHO+24];
    
    tamMemoria = M/sizeof(Registro);
    S = S;
    
    for(i = 1; i <= D; i++) {
        numRegistros = estruturaArquivo(i, E);
        sprintf(nomeArquivo, "%s%d.bin", TMP, i);
        ordenaArquivo(nomeArquivo, numRegistros, tamMemoria);
        computaFrequencia(nomeArquivo);
    }

    int nivel = 0, contProxNivel = 0, contNivel = D;

    while(contNivel != 1){
        for(i = 1; i < contNivel; i += 2){
            if(nivel == 0){
                sprintf(nomeArquivo, "%s%d.bin", TMP, i);
                sprintf(nomeArquivo2, "%s%d.bin", TMP, i+1);
            }else{
                sprintf(nomeArquivo, "%sN%d.%d.bin", TMP, nivel, i);
                sprintf(nomeArquivo2, "%sN%d.%d.bin", TMP, nivel, i+1);   
            }
            contProxNivel++;
            sprintf(nomeArquivoRes, "%sN%d.%d.bin", TMP, nivel+1, contProxNivel);
            uneArquivos(nomeArquivo, nomeArquivo2, nomeArquivoRes);   
        }
        if(contNivel % 2 == 1){
            if(nivel == 0){
                sprintf(nomeArquivo, "%s%d.bin", TMP, contNivel);
            }else{
                sprintf(nomeArquivo, "%sN%d.%d.bin", TMP, nivel, contNivel);  
            }

            contProxNivel++;
            sprintf(nomeArquivoRes, "%sN%d.%d.bin", TMP, nivel+1, contProxNivel);
            rename(nomeArquivo, nomeArquivoRes);  
        }
        nivel++;
        contNivel = contProxNivel;
        contProxNivel = 0;
    }
    sprintf(nomeArquivo, "%sN%d.1.bin", TMP, nivel);
    sprintf(nomeArquivoRes, "%s%s", S, NOMEINDEX);
    transformaArquivo(nomeArquivo, nomeArquivoRes);
}
