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

void mostrarTarea(sTAREA* t);

void mostrarTodasLasTareas(sTAREA** t, int cantidad);

sTAREA* BuscarTareaID(sTAREA ** tareasPend, sTAREA ** tareasReal,int id, int cantTareas);

sTAREA* BuscarTareaClave(sTAREA ** tareasPend, sTAREA ** tareasReal,char clave[], int cantTareas);

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
        printf("\n=== CARGAR TAREA %d ===",i);
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
        mostrarTarea (tareasPendientes[i]);
        printf("\n===============================");
        do
        {
        printf("\nRealizo esta tarea? 1 = SI 0 = NO: ");;    
        fflush(stdin);
        scanf("%d",&resp);
        } while (resp != 1 && resp != 0);
        if (resp)
        {
            tareasRealizadas[i] = tareasPendientes[i];
            tareasPendientes[i] = NULL;
        }

    }
    
    //MOSTRAR POR PANTALLA LAS TAREAS REALIZADAS Y LISTAR PENDIENTES

    printf("\n==== Tareas Realizadas ====");
    mostrarTodasLasTareas(tareasRealizadas,cantTareas);

    printf("\n==== Tareas Pendientes ====");
    mostrarTodasLasTareas(tareasPendientes,cantTareas);

    printf("\n==============================================");
    
    // BUSQUEDA
    sTAREA * busqueda = NULL;
    int id;
    char *clave; 
    
    do
    {
   
        printf("\n================================");
        printf("\n1-Buscar Por id ");
        printf("\n2-Buscar Por Clave");
        printf("\n3-Salir");
        printf("\nSeleccione una opcion: ");
        fflush(stdin);
        scanf("%d",&resp);
        switch (resp)
        {
        case 1:
            printf("\nIngrese el id: ");
            fflush(stdin);
            scanf("%d",&id);
            busqueda = BuscarTareaID(tareasPendientes,tareasRealizadas,id,cantTareas);
            break;
        case 2:
            printf("\nIngrese la clave: ");
            fflush(stdin);
            gets(buffer);
            clave = (char *) malloc(sizeof(char) * strlen(buffer) + 1);
            strcpy(clave,buffer);
            busqueda = BuscarTareaClave(tareasPendientes,tareasRealizadas,clave,cantTareas);        
            break;
        }
    if ( resp == 1 || resp == 2)
    {    
        if (busqueda != NULL)
        {
            printf("\n=== LA TAREA BUSCADA ES: ===");
            mostrarTarea(busqueda);
        }else
        {
            printf("\n===NO HUBO RESULTADOS===");
        }
    }
    
    } while (resp != 3);
    
    free(tareasPendientes);
    free(tareasRealizadas);
    return 0;
}
sTAREA* BuscarTareaClave(sTAREA ** tareasPend, sTAREA ** tareasReal,char clave[], int cantTareas){

    if (tareasPend != NULL && tareasReal != NULL)
    {
        for (int i = 0; i < cantTareas; i++)
        {
            if (tareasPend[i] != NULL && strstr(tareasPend[i]->Descripcion, clave) != NULL)
            {
                return(tareasPend[i]);
            }
            else if (tareasReal[i] != NULL && strstr(tareasReal[i]->Descripcion, clave) != NULL)
            {
                return(tareasReal[i]);
            }            
        }
    }
    return (NULL);
}
sTAREA* BuscarTareaID(sTAREA ** tareasPend, sTAREA ** tareasReal,int id, int cantTareas){

    if (tareasPend != NULL && tareasReal != NULL)
    {
        
        for (int i = 0; i < cantTareas; i++)
        {
            if (tareasPend[i] != NULL && tareasPend[i]->TareaID == id)
            {
                return (tareasPend[i]);
            }
            else if (tareasReal[i] != NULL && tareasReal[i]->TareaID == id)
            {
                return(tareasReal[i]);
            }
        }
    }
    return (NULL);
}

void mostrarTodasLasTareas(sTAREA** t, int cantidad){
    
    for (int i = 0; i < cantidad; i++)
    {
        if ( t[i] != NULL)
        {
            printf("\n=== TAREA %d ===",i);
            mostrarTarea(t[i]);
        }
        
    }
    

}

void mostrarTarea(sTAREA* t){

    printf("\nID : %d", t->TareaID);
    printf("\nDescripción: ");
    puts(t->Descripcion);
    printf("Duracion: %d",t->Duracion);

}