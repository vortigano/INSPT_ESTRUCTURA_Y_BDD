#ifndef ANALIZADOR_H
#define ANALIZADOR_H
typedef struct{
    int code;
    int pos;
} t_error;

typedef struct ctx ctx;

ctx     *analizador_init();
void    analizador_finalize (ctx**);
t_error analizador_get_error(ctx*contexto);
/**
 * @brief Analiza una expresión y actualiza el contexto con el resultado.
 * @param ctx* Contexto del analizador
 * @param char* Puntero a cadena de expresion
*/
void    analizar_expresion  (ctx*, char*);

#endif