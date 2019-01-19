/*******************************************************************************
 * resolucao.h                                                                 *
 * Propósito:                                                                  *
 *                                                                             *
 * @author Jéssica Taís C. Rodrigues                                           *
 * @version 1.0 13/06/2017                                                     *
 ******************************************************************************/

#ifndef __RESOLUCAO_H__
#define __RESOLUCAO_H__

/**
 * Constrói um índice invertido.
 *
 * @param  int       D    quantidade de conversas
 * @param  int       M    quantidade máxima de memória primária a ser utilizada
 * @param  char[]    E    caminho onde se encontram as conversas   
 * @param  char[]    S    caminho onde será armazenado o índice invertido
 * @return void
 */
void resolve(int D, int M, char E[MAX_CAMINHO], char S[MAX_CAMINHO]);

#endif