/*******************************************************************************
 * arquivo.h                                                                   *
 * Propósito:                                                                  *
 *                                                                             *
 * @author Jéssica Taís C. Rodrigues                                           *
 * @version 1.0 13/06/2017                                                     *
 ******************************************************************************/

#ifndef __ARQUIVO_H__
#define __ARQUIVO_H__

#define MAX_CAMINHO 256
#define TMP "./tmp/"
#define NOMEINDEX "index"
//#define NOMEINDEX "meuindex"


/**
 * Estrutura o arquivo no formato binário composto por registros
 *
 * @param  int       conversa    número da conversas
 * @param  char[]    E           caminho onde se encontram as conversas   
 * @return int                   quantidade de registros no arquivo
 */
int estruturaArquivo(int conversa, char E[MAX_CAMINHO]);

/**
 * Calcula as frenquecias das palavras do arquivo
 *
 * @param  char[]   nomeArquivo  Nome do arquivo onde estão as palavras 
 * @return void
 */
void computaFrequencia(char nomeArquivo[MAX_CAMINHO+24]);

/**
 * Imprime o arquivo no formato binário composto por registros
 *
 * @param  char[]    nomeArquivo    caminho onde se encontra o arquivo   
 * @return void
 */
void imprimeArquivo(char nomeArquivo[MAX_CAMINHO+24]);

/**
 * Ordena arquivos no formato binário composto por registros
 *
 * @param  char[]    nomeArquivo    caminho onde se encontra o arquivo 
 * @param  int       n              quantidade de registros no arquivo
 * @param  int       tamMemoria     tamanho da memória disponível em número de registros
 * @return void
 */
void ordenaArquivo(char nomeArquivo[MAX_CAMINHO+24], int n, int tamMemoria);

/**
 * Une arquivos dois arquivos, armazenando o conteúdo ordenado num terceiro
 *
 * @param  char[]    nomeArquivo1             caminho onde se encontra o primeiro arquivo 
 * @param  char[]    nomeArquivo2             caminho onde se encontra o segundo arquivo 
 * @param  char[]    nomeArquivo2Resultado    caminho onde se encontra o arquivo onde o resultado será colocado 
 * @return void
 */
void uneArquivos(char nomeArquivo1[MAX_CAMINHO+24], char nomeArquivo2[MAX_CAMINHO+24],
                 char nomeArquivoResultado[MAX_CAMINHO+24]);

/**
 * Transforma um arquivo em formato binário para formato de caractere
 *
 * @param  char[]    nomeArquivoBin           caminho onde se encontra o arquivo binário
 * @param  char[]    nomeArquivo2Resultado    caminho onde se encontra o arquivo onde o resultado será colocado 
 * @return void
 */
void transformaArquivo(char nomeArquivoBin[MAX_CAMINHO+24], char nomeArquivoResultado[MAX_CAMINHO+24]);

#endif