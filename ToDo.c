#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//TP5

#define MAX 150

typedef struct Tarea
{
    
    int TareaID;
    char *Descripcion;
    int Duracion;

}sTAREA;

typedef struct sNodo{
    sTAREA T;
    struct sNodo* Siguiente;
}sNodo;

sNodo* crearListaVacio();

sNodo* crearNodo(int id, char descipcion[], int duracion);

void insertarNodo(sNodo** cabecera,int id, char descipcion[], int duracion);

void mostrarTarea(sTAREA t);

sNodo* BuscarTareaID(sNodo * tareasPend, sNodo * tareasReal,int id);

sNodo* BuscarTareaClave(sNodo * tareasPend, sNodo * tareasReal,char clave[]);

void mostrarTodasLasTareas(sNodo* t);
int main (){
    char buffer[MAX],*clave;
    int cantTareas,duracion,respuesta,id = 0, bandera,idAux;

    sNodo* tareasRealizadas,* tareaPendientes,*tareasEnProceso; 
    sNodo* busqueda; 
    tareasRealizadas = crearListaVacio();
    tareaPendientes = crearListaVacio();
    do
    {
        printf("\n1- Agregar una tarea pendiente: ");
        printf("\n2- Ver y Marcar como realizadas las tareas pendientes: ");
        printf("\n3- Mostrar Tareas Pendientes");
        printf("\n4- Mostrar Tareas Realizadas");
        printf("\n5- Buscar por ID");
        printf("\n6- Buscar por clave");
        printf("\n10- Salir");
        fflush(stdin);
        printf("\nIngrese una opcion: ");
        scanf("%d",&respuesta);
        
        switch (respuesta)
        {
        case 1 :
            printf("\nIngrese una descripción para la tarea: ");
            fflush(stdin);
            gets(buffer);
            printf("\nIngrese una duracion(en minutos): ");
            fflush(stdin);
            scanf("%d",&duracion);
            insertarNodo(&tareaPendientes, id, buffer, duracion);
            id ++;
            break;
        case 2 :
            printf("\n=== Tareas Pendienetes ===");
            mostrarTodasLasTareas(tareaPendientes);
            printf("\n==========================");
            printf("\n=== Tareas Realizadas ===");
            mostrarTodasLasTareas(tareasRealizadas);
            printf("\n==========================");
            printf("\n=== Tareas EnProceso ===");
            mostrarTodasLasTareas(tareasEnProceso);
            printf("\n==========================");
            printf("\nIngrese el ID de la tarea a seleccionar: ");
            scanf("%d",&idAux);

            break;
        case 3:
            printf("\n=== Tareas Pendienetes ===");
            mostrarTodasLasTareas(tareaPendientes);
            printf("\n==========================");
            break;
        case 4:
            printf("\n=== Tareas Realizadas ===");
            mostrarTodasLasTareas(tareasRealizadas);
            printf("\n==========================");
            break;
        case 5:
            printf("\nIngrese el id: ");
            fflush(stdin);
            scanf("%d",&idAux);
            busqueda = BuscarTareaID(tareaPendientes,tareasRealizadas,idAux);
            break;
        case 6:
            printf("\nIngrese la clave: ");
            fflush(stdin);
            gets(buffer);
            clave = (char *) malloc(sizeof(char) * strlen(buffer) + 1);
            strcpy(clave,buffer);
            busqueda = BuscarTareaClave(tareaPendientes,tareasRealizadas,clave);        
        
        }
        if (respuesta == 5 || respuesta == 6)
        {
            if (busqueda != NULL){
                printf("\n=== LA TAREA BUSCADA ES: ===");
                mostrarTarea(busqueda->T);
                printf("\n================");
            }
            else
            {
                printf("\n===NO HUBO RESULTADOS===");
            }
        }
        
    } while (respuesta != 10);
    
    free(tareasRealizadas);
    free(tareaPendientes);
    return 0;
}

void Eliminar(sNodo ** t, int id){
    sNodo* aux, *auxAnterior;
    aux = *t;
    auxAnterior = *t;

    while (aux && aux->T.TareaID != id)
    {
        auxAnterior = aux;
        aux = aux->Siguiente;
    }
    if (aux == *t)
    {
        *t = aux->Siguiente;
        free(aux->T.Descripcion);
        free(aux);    
    }else{
        if (aux)
        {
            auxAnterior->Siguiente = aux->Siguiente;
            free(aux->T.Descripcion);
            free(aux);
        }
    }

}

void mostrarTodasLasTareas(sNodo* t){
    sNodo* aux = t;
    while (aux != NULL)
    {
        printf("\n---------------------");
        mostrarTarea(aux->T);
        printf("\n---------------------");
        aux = aux->Siguiente;
    }
    
}

sNodo* BuscarTareaClave(sNodo * tareasPend, sNodo * tareasReal,char clave[]){
    // HACER QUE SOLO RECIBA UNA LISTA Y LO BUSQUE DE AHI RECIEN EN EL PROGRAMA
    //PRINCIPAL HACES EL TRAMUYO DE SI ESTABA O NO
    sNodo* aux = tareasPend;
    while (aux && strstr(aux->T.Descripcion, clave) == NULL)
    {
        aux =aux->Siguiente;
    }
    if (aux == NULL)
    {
        aux = tareasReal;
        while (aux && strstr(aux->T.Descripcion, clave) == NULL)
        {
            aux =aux->Siguiente;
        }
    }
    return aux;
}

sNodo* BuscarTareaID(sNodo * tareasPend, sNodo * tareasReal,int id){

        sNodo* aux = tareasPend;
        while (aux != NULL && aux->T.TareaID != id)
        {
            aux = aux->Siguiente;
        }
        if (aux == NULL)
        {
            aux = tareasReal;
            while (aux!= NULL && aux->T.TareaID != id)
            {
                aux = aux->Siguiente;
            }
        }
        return aux;

}

void insertarNodo(sNodo** cabecera,int id, char* descipcion, int duracion){
    sNodo* nuevoNodo = crearNodo(id,descipcion,duracion);
    nuevoNodo->Siguiente = *cabecera;
    *cabecera = nuevoNodo;
}

sNodo* crearNodo(int id, char descipcion[], int duracion){
    sNodo* nuevoNodo= (sNodo *) malloc(sizeof(sNodo));
    nuevoNodo->T.Descripcion = (char *) malloc(sizeof(char) * strlen(descipcion) + 1);
    strcpy(nuevoNodo->T.Descripcion, descipcion);
    nuevoNodo->T.Duracion = duracion;
    nuevoNodo->T.TareaID = id;
    return nuevoNodo;
}

sNodo* crearListaVacio(){
    return NULL;
}

void mostrarTarea(sTAREA t){

    printf("\nID : %d", t.TareaID);
    printf("\nDescripción: ");
    puts(t.Descripcion);
    printf("Duracion: %d",t.Duracion);

}
