/*******************************************************************************
 * main.c                                                                      *
 * Propósito:                                                                  *
 *                                                                             *
 * @author Jéssica Taís C. Rodrigues                                           *
 * @version 1.0 13/06/2017                                                     *
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "arquivo.h"
#include "resolucao.h"

int main(void){
    int D, M;
    char E[256], S[256];

    scanf("%d%d%s%s", &D, &M, E, S);

    resolve(D, M, E, S);

    return 0;
}