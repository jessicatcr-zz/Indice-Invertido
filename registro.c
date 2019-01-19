/*******************************************************************************
 * registro.c                                                                  *
 * Propósito:                                                                  *
 *                                                                             *
 * @author Jéssica Taís C. Rodrigues                                           *
 * @version 1.0 13/06/2017                                                     *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registro.h"

int comparaRegistro(Registro *reg1, Registro *reg2){
    
    int cmp = strcmp(reg1->palavra, reg2->palavra);
    if(cmp == 0){
        if(reg1->conversa < reg2->conversa){
            cmp = -1;
        }else if(reg1->conversa > reg2->conversa){
            cmp = 1;
        }else{
            if(reg1->posicao < reg2->posicao){
                cmp = -1;
            }else if(reg1->posicao > reg2->posicao){
                cmp = 1;
            }
        }
    }

    return cmp;
}

void imprimeRegistro(Registro *reg){
    printf("%s,%d,%d,%ld\n", reg->palavra, reg->conversa, reg->frequencia, reg->posicao);
}

BufferOrdenado *criaBufferOrdenado(void){
    BufferOrdenado *b = malloc(sizeof(BufferOrdenado));
    b->primeiro = NULL;
    b->ultimo = NULL;
    b->tamBuffer = 0;
    return b;
}

int bufferVazio(BufferOrdenado *b){
    return (b->primeiro == NULL);
}

void insereBuffer(BufferOrdenado *b, Registro *reg){
    Celula *novaCelula = malloc(sizeof(Celula));
    novaCelula->registro = *reg;
    novaCelula->ant = NULL;
    novaCelula->prox = NULL;

    if(bufferVazio(b)){
        b->primeiro = novaCelula;
        b->ultimo = novaCelula; 
    }else{
        Celula *aux = b->primeiro;
        while(aux != NULL && comparaRegistro(reg, &(aux->registro)) > 0){
            aux = aux->prox;
        }
        if(aux == NULL){
            b->ultimo->prox = novaCelula;
            novaCelula->ant = b->ultimo;
            b->ultimo = novaCelula;
        } else {
            if(b->primeiro == aux) {
                b->primeiro = novaCelula;
            }else{
                aux->ant->prox = novaCelula;
            }
            novaCelula->ant = aux->ant;
            novaCelula->prox = aux;
            aux->ant = novaCelula;
        }
    }
    b->tamBuffer++;
}

void removeMaxBuffer(BufferOrdenado *b, Registro *reg){
    Celula *aux = b->ultimo;
    b->ultimo = b->ultimo->ant;
    if(b->ultimo != NULL){
        b->ultimo->prox = NULL;
    }
    b->tamBuffer--;

    *reg = aux->registro;
    free(aux);
}

void removeMinBuffer(BufferOrdenado *b, Registro *reg){
    Celula *aux = b->primeiro;
    b->primeiro = b->primeiro->prox;
    if(b->primeiro != NULL){
        b->primeiro->ant = NULL;
    }
    b->tamBuffer--;

    *reg = aux->registro;
    free(aux);
}

void imprimeBuffer(BufferOrdenado *b){
    printf("-----[Buffer]\n");
    printf("tamBuffer: %d\n", b->tamBuffer);
    Celula *aux = b->primeiro;
    while(aux != NULL){
        imprimeRegistro(&(aux->registro));
        aux = aux->prox;
    }
    printf("-----[Buffer]\n");
}

void liberaBuffer(BufferOrdenado *b){
    Celula *aux;
    while(!bufferVazio(b)){
        aux = b->primeiro->prox;
        free(b->primeiro);
        b->primeiro = aux;
    }
    free(b);
}