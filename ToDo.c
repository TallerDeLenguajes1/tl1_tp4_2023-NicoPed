#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 150

typedef struct Tarea
{
    
    int TareaID;
    char *Descripcion;
    int Duracion;

}sTAREA;



int main (){
    char buffer[MAX];
    int cantTareas,duracion;
    printf ("\nCuantas tareas va a cargar?\n");
    scanf("%d", &cantTareas);

    sTAREA ** tareasPendientes;
    sTAREA ** tareasRealizadas;

    tareasPendientes = (sTAREA ** ) malloc(sizeof(sTAREA *) * cantTareas);
    tareasRealizadas = (sTAREA ** ) malloc(sizeof(sTAREA *) * cantTareas);

    for (int i = 0; i < cantTareas; i++)
    {
        //ES una buena practica hacer esto
        tareasPendientes[i] = NULL;
        tareasRealizadas[i] = NULL;
    }
    int i = 0;
    printf("\n====A Continuacion va a cargar las Tareas Pendientes==== ");
    for (int i = 0; i < cantTareas; i++)
    {
        //sacarla en una función
        tareasPendientes[i] = (sTAREA *) malloc(sizeof(sTAREA) * 1);
        tareasPendientes[i]->TareaID = i;
        fflush(stdin);
        printf("\nIngerese una descrpicion de la tarea (MAX %d): ",MAX);
        gets(buffer);
        tareasPendientes[i]->Descripcion = (char *) malloc(sizeof(char) * strlen(buffer)+1);
        strcpy(tareasPendientes[i]->Descripcion, buffer);
        printf("\nIngrese lo que se va a tardar en realizar la tarea (duracion): ");
        fflush(stdin);
        scanf("%d", &tareasPendientes[i]->Duracion);
    }
    
    //LISTAR LAS TAREAS UNA A UNA 

    int resp;
    for (int i = 0; i < cantTareas; i++)
    {

        printf("\n===TAREA %d ===",i);
        //EN busxar fijarse si no esta en NULL si no se rompe
        puts (tareasPendientes[i]->Descripcion); 
        printf("\nRealizo esta tarea? 1 = SI 0 = NO");;    
        scanf("%d",&resp);
    }
    

    free(tareasPendientes);
    free(tareasRealizadas);
    return 0;
}
