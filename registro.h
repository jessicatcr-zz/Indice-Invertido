/*******************************************************************************
 * registro.h                                                                  *
 * Propósito:                                                                  *
 *                                                                             *
 * @author Jéssica Taís C. Rodrigues                                           *
 * @version 1.0 13/06/2017                                                     *
 ******************************************************************************/

#ifndef __REGISTRO_H__
#define __REGISTRO_H__

/**
 * Estrutura que representa o formato do índice
 */
typedef struct registro{
    char palavra[20];
    int conversa;
    int frequencia;
    long int posicao;
} Registro;

typedef struct celula{
    Registro registro;
    struct celula *ant;    
    struct celula *prox;    
} Celula;

typedef struct bufferOrdenado{
    Celula *primeiro;
    Celula *ultimo;
    int tamBuffer;
} BufferOrdenado;

/**
 * Compara dois registros
 *
 * @param  Registro*    reg1    dados do primeiro registro
 * @param  Registro*    reg2    dados do segundo registro  
 * @return int          cmp     retorna -1 se o primeiro é menor, +1 se maior ou 0 se ĩgual
 */
int comparaRegistro(Registro *reg1, Registro *reg2);

/**
 * Imprime informações do registro
 *
 * @param  Registro*    reg    dados do registro
 * @return void
 */
void imprimeRegistro(Registro *reg);

/**
 * Cria buffer ordenado vazio.
 *
 * @return BufferOrdenado*   retorna buffer vazio
 */
BufferOrdenado *criaBufferOrdenado(void);

/**
 * Verifica se buffer está vazio.
 *
 * @param  BufferOrdenado*    b    buffer de registros
 * @return int                     0 se está vazio, 1 caso contrário
 */
int bufferVazio(BufferOrdenado *b);

/**
 * Insere registro no buffer de maneira ordenada.
 *
 * @param  BufferOrdenado*    b    buffer
 * @param  Registro*          reg  registro a ser inserido no buffer
 * @return void
 */
void insereBuffer(BufferOrdenado *b, Registro *reg);

/**
 * Remove maior registro do buffer.
 *
 * @param  BufferOrdenado*  b      buffer
 * @param  Registro*        reg    onde o registro será colocado
 * @return void
 */
void removeMaxBuffer(BufferOrdenado *b, Registro *reg);

/**
 * Remove menor registro do buffer.
 *
 * @param  BufferOrdenado*  b      buffer
 * @param  Registro*        reg    onde o registro será colocado
 * @return void
 */
void removeMinBuffer(BufferOrdenado *b, Registro *reg);

/**
 * Imprime dados do buffer.
 *
 * @param BufferOrdenado* b     buffer
 * @return void
 */
void imprimeBuffer(BufferOrdenado *b);

/**
 * Libera memoria do buffer
 *
 * @param  BufferOrdenado*    b    buffer
 * @return void
 */
void liberaBuffer(BufferOrdenado *b);

#endif