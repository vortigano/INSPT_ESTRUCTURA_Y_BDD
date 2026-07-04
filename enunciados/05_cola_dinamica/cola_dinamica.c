#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#define s scanf

typedef struct elemento
{
    int dato;
    struct elemento *sig;
} nodo;

void acolar(nodo, nodo **, nodo **);
nodo *nuevonodo(nodo);
nodo desacolar(nodo **);
void listar(nodo *);
void vaciar(nodo **);
nodo *verificar(nodo *);
nodo ingresar_dato(void);
void dato_eliminado(nodo);
int menu(void);

int main()
{
    nodo *p = NULL, *q, r;
    int op;
    system("cls");
    system("color 9f");
    do
    {
        op = menu();
        switch (op)
        {
        case 1:
        {
            r = ingresar_dato();
            acolar(r, &p, &q);
            break;
        }
        case 2:
        {
            if (verificar(p) != NULL)
                r = desacolar(&p);
            dato_eliminado(r);
            break;
        }
        case 3:
        {
            if (verificar(p) != NULL)
            {
                printf("\nContenido de la cola:\n\n");
                listar(p);
                getch();
            }
            break;
        }
        case 4:
        {
            if (verificar(p) != NULL)
                vaciar(&p);
            break;
        }
        }
    } while (op < 5);
    getch();
    if (verificar(p) != NULL)
        vaciar(&p);
    return 0;
} // CIERRA MAIN
//**********************************************************************
nodo *nuevonodo(nodo r)
{
    nodo *x;
    x = (nodo *)malloc(sizeof(nodo));
    x->dato = r.dato; //*x=r;
    x->sig = NULL;
    return (x);
}
//**********************************************************************
void acolar(nodo r, nodo **p, nodo **q)
{
    nodo *nuevo;
    nuevo = nuevonodo(r);
    if (*p == NULL)
        *p = nuevo;
    else
        (*q)->sig = nuevo;
    *q = nuevo;
} // CIERRA ACOLAR
//**********************************************************************
nodo desacolar(nodo **p)
{
    nodo r, *aux;
    r = **p;
    aux = *p;
    *p = (*p)->sig;
    free(aux);
    return (r);
} // CIERRA DESACOLAR
//**********************************************************************
void listar(nodo *p)
{
    if (p)
    {
        printf("\t\t%d\n", p->dato);
        listar(p->sig);
    }
} // CIERRA LISTAR
//**********************************************************************
void vaciar(nodo **p)
{
    nodo *aux;
    while (*p != NULL)
    {
        aux = *p;
        *p = (*p)->sig;
        free(aux);
    }
} // CIERRA VACIAR
//**********************************************************************
nodo *verificar(nodo *p)
{
    if (p == NULL)
    {
        system("cls"); // clrscr();
        printf("\nCola vacia!");
        printf("\n\n\n\nPulse una tecla para continuar...");
        getch();
    }
    return (p);
} // CIERRA VERIFICAR
//**********************************************************************
nodo ingresar_dato(void)
{
    nodo r;
    system("cls"); // clrscr();
    printf("\nIngrese un nro.: ");
    s("%d", &r.dato);
    return (r);
} // CIERRA INGRESAR_DATO
//**********************************************************************
void dato_eliminado(nodo r)
{
    system("cls"); // clrscr();
    printf("\nValor eliminado: %d", r.dato);
    printf("\n\n\nPulse una tecla para continuar...");
    getch();
} // CIERRA DATO_ELIMINADO
//**********************************************************************
int menu(void)
{
    int op;
    system("cls");
    printf("\n\t\t\t\tMenu principal");
    do
    {
        printf("\n\n\t\t\t\tAcolar    - 1");
        printf("\n\n\t\t\t\tDesacolar - 2");
        printf("\n\n\t\t\t\tListar    - 3");
        printf("\n\n\t\t\t\tVaciar    - 4");
        printf("\n\n\t\t\t\tSalir     - 5");
        printf("\n\n\nOpcion nro.: ");
        s("%d", &op);
    } while (op < 1 || op > 5);
    return (op);
} // CIERRA MENU
