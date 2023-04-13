#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct Tarea
{
    
    int TareaID;
    char *Descripcion;
    int Duracion;

}sTAREA;


int main (){
    char buffer[MAX];
    int cantTareas;
    printf ("\nCuantas tareas va a cargar?");
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
    
    return 0;
}