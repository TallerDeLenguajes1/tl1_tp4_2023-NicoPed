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

sNodo* crearNodo(sTAREA t);

sTAREA crearTarea(int id, char* descripcion, int duracion);

void insertarNodo(sNodo** cabecera,sNodo* nuevoNodo);

void mostrarTarea(sTAREA t);

sNodo* BuscarTareaID(sNodo * lista,int id);

sNodo* BuscarTareaClave(sNodo * lista, char clave[]);
void mostrarTodasLasTareas(sNodo* t);

void Eliminar(sNodo ** t, int id);

void mostrarDatos(sNodo* lista);
int cantidadTareas(sNodo* lista);
int sacarTiempoAsociado(sNodo *lista);


int main (){
    char buffer[MAX],*clave;
    int cantTareas,duracion,respuesta,id = 0, bandera,idAux,opcionLista;
    sTAREA nuevaTarea;
    sNodo* nuevoNodo;
    sNodo* tareasRealizadas,* tareaPendientes,*tareasEnProceso; 
    sNodo* busqueda; 
    tareasRealizadas = crearListaVacio();
    tareaPendientes = crearListaVacio();
    tareasEnProceso = crearListaVacio();
    do
    {
        printf("\n1- Agregar una tarea pendiente: ");
        printf("\n2- Ver y Marcar como realizadas las tareas pendientes: ");
        printf("\n3- Mostrar Tareas Pendientes");
        printf("\n4- Mostrar Tareas Realizadas");
        printf("\n5- Buscar por ID");
        printf("\n6- Buscar por clave");
        printf("\n7- Mostrar Datos de una lista");
        printf("\n10- Salir");
        fflush(stdin);
        printf("\nIngrese una opcion: ");
        scanf("%d",&respuesta);
        
        switch (respuesta)
        {
        case 1 :
            /*MODULALO OSEA HACE UN QUE TE CREE LA TAREA OTRO QUE TE CREE EL NODO Y DE AHI MANDARLO A INSERTAR OBVIAMENTE
            NECESITAS UNA VRBLE NODO Y OTRA TAREA*/
            printf("\n==========================");
            printf("\nIngrese una descripción para la tarea: ");
            fflush(stdin);
            gets(buffer);
            printf("\nIngrese una duracion(en minutos): ");
            fflush(stdin);
            scanf("%d",&duracion);
            printf("\n==========================");
            nuevaTarea = crearTarea(id,buffer,duracion);
            nuevoNodo= crearNodo(nuevaTarea);
            insertarNodo(&tareaPendientes,nuevoNodo);
            free(nuevaTarea.Descripcion);
            id ++;
            break;
        case 2 :
            printf("\n=== Tareas Pendienetes ===");
            mostrarTodasLasTareas(tareaPendientes);
            printf("\n==========================");
            printf("\n=== Tareas Realizadas ===");
            mostrarTodasLasTareas(tareasRealizadas);
            printf("\n==========================");
            printf("\n=== Tareas En Proceso ===");
            mostrarTodasLasTareas(tareasEnProceso);
            printf("\n==========================");
            printf("\nIngrese el ID de la tarea a seleccionar: ");
            scanf("%d",&idAux);
    /* para el pasaje hacer una funcion quitado que te da un nodo y ese
    nodo pasarlo a la otra lista*/
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
            busqueda = BuscarTareaID(tareaPendientes,idAux);
            if (busqueda == NULL)
            {
                busqueda = BuscarTareaID(tareasRealizadas,idAux);
                if (busqueda == NULL)
                {
                    busqueda = BuscarTareaID(tareasEnProceso,idAux);
                }
            }
            break;
        case 6:
            printf("\nIngrese la clave: ");
            fflush(stdin);
            gets(buffer);
            clave = (char *) malloc(sizeof(char) * strlen(buffer) + 1);
            strcpy(clave,buffer);
            busqueda = BuscarTareaClave(tareaPendientes,clave);        
            if (busqueda == NULL)
            {
                busqueda = BuscarTareaClave(tareasRealizadas,clave);
                if (busqueda == NULL)
                {
                    busqueda = BuscarTareaClave(tareasEnProceso,clave);
                }
            }
            
            break;
        case 7:
            do
            {
            printf("\n1- Tareas Pendientes: ");
            printf("\n2- Tareas Realizadas");
            printf("\n3- Tareas en proceso: ");
            printf("\nIngrese una opción: ");
            scanf("%d",&opcionLista);
            } while (opcionLista != 1 && opcionLista != 2 && opcionLista != 3);
            switch (opcionLista)
            {
            case 1:
                printf("==== PARA TAREAS PENDIENTES ====");
                mostrarDatos(tareaPendientes);
                break;
            case 2:
                printf("==== PARA TAREAS REALIZADAS ====");
                mostrarDatos(tareasRealizadas);
                break;
            case 3:
                printf("==== PARA TAREAS EN PROCESO ====");
                mostrarDatos(tareasEnProceso);
                break;            
            default:
                break;
            }
            break;
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

sTAREA crearTarea(int id, char* descripcion, int duracion){
    sTAREA t;
    t.Descripcion = (char *) malloc(sizeof(char)* strlen(descripcion) + 1);
    strcpy(t.Descripcion,descripcion);
    t.TareaID = id;
    t.Duracion = duracion;
    return t;
}

void mostrarDatos(sNodo* lista){
    int cantTareas = cantidadTareas(lista);
    int tiempoAsociado = sacarTiempoAsociado(lista);
    printf("\n=============================");
    printf("\nLa cantidad de tareas son: %d",cantTareas);
    printf("\nEl tiempo Asociado es: %d",tiempoAsociado);
    printf("\n=============================");

}
int cantidadTareas(sNodo* lista){
    if (lista == NULL)
    {
        return 0;
    }else
    {
        return(1 + cantidadTareas(lista->Siguiente));
    }  
}
int sacarTiempoAsociado(sNodo *lista){
    if (lista == NULL)
    {
        return 0;
    }else
    {
        return(lista->T.Duracion + sacarTiempoAsociado(lista->Siguiente));
    }  
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

sNodo* BuscarTareaClave(sNodo * lista, char clave[]){
    // HACER QUE SOLO RECIBA UNA LISTA Y LO BUSQUE DE AHI RECIEN EN EL PROGRAMA
    //PRINCIPAL HACES EL TRAMUYO DE SI ESTABA O NO
    sNodo* aux = lista;
    while (aux && strstr(aux->T.Descripcion, clave) == NULL)
    {
        aux =aux->Siguiente;
    }
    return aux;
}

sNodo* BuscarTareaID(sNodo * tareas, int id){

        sNodo* aux = tareas;
        while (aux != NULL && aux->T.TareaID != id)
        {
            aux = aux->Siguiente;
        }
        return aux;

}

void insertarNodo(sNodo** cabecera,sNodo* nuevoNodo){
    nuevoNodo->Siguiente = *cabecera;
    *cabecera = nuevoNodo;
}

sNodo* crearNodo(sTAREA t){
    sNodo* nuevoNodo= (sNodo *) malloc(sizeof(sNodo));
    nuevoNodo->T.Descripcion = (char *) malloc(sizeof(char) * strlen(t.Descripcion) + 1);
    strcpy(nuevoNodo->T.Descripcion, t.Descripcion);
    nuevoNodo->T.Duracion = t.Duracion;
    nuevoNodo->T.TareaID = t.TareaID;
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
