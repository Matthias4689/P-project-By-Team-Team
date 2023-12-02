// ============================================================================
// ============================= LIBRERIAS ====================================
// ============================================================================

#include "hashmap.h"
#include "list.h"
#include "treemap.h"
#include <ctype.h>
#include <dirent.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// ============================================================================
// ============================= ESTRUCTURAS ==================================
// ============================================================================

// Estructura de un integrante.
typedef struct {
  int id;
  char nombre[101];
  int numTask;
} Integrante;

// Estructura de el estado del progreso de una tarea.
typedef struct {
  char fecha[11];
  char estado[50];
} Progreso;

// Estructura de una tareas
typedef struct {
  int id;
  char nombre[101];
  char descripcion[200];
  int prioridad;
  List *progreso; // Lista enlazada para el historial de progreso
  int idIntegrante;
} Tarea;


// ============================================================================
// ======================== PROTOTIPO DE FUNCIONES ============================
// ============================================================================

// ======================== Auxiliares ============================
void imprimirMenu();
void leerDato(char dato[101]);
int generarID_Integrante(HashMap *integrantes);
int generarID_Tarea(TreeMap *tareas);
int lower_than_int(void *key1, void *key2);
void obtenerFechaActual(char *fecha);
const char *obtenerNombreIntegrante(HashMap *integrantes, int idIntegrante);

// ======================== Funcionalidades Menu ============================
void agregarNewIntegrante(HashMap *integrantes, char *nombre);
void eliminarIntegrante(HashMap *integrantes, char *nombre);
void crearTarea(TreeMap *tree, const char *nombre, const char *descripcion, int prioridad);
void eliminarTarea(TreeMap *tree, int idTarea);
void agregarPrioridad(TreeMap *tree, int tareaId, int nuevaPrioridad);
void consultarID_Integrante_tarea(HashMap *integrantes, TreeMap *tareas);
void asignarIntegrante(HashMap *integrantes, TreeMap *tareas);
void verProgreso(TreeMap *tree, int tareaId);
void actualizarProgreso(TreeMap *tree, int tareaId);
void importarDesdeCSV(HashMap* integrantes, TreeMap* tareas);
void exportarA_CSV(TreeMap* tareas, HashMap* integrantes);
void mostrarTareasSinAsignar(HashMap *integrantes, TreeMap *tareas);
void mostrarTareasAsignadas(TreeMap *tareas, HashMap *integrantes);
void mostrarEquipo(HashMap *integrantes);
void limpiarConsola();
void dibujo();


// ============================================================================
// ================================= MAIN =====================================
// ============================================================================
int main(int argc, char *argv[]) {

  int limpiadorBuffer;
  int menu;
  HashMap *integrantes = createMap(100);
  TreeMap *tareas = createTreeMap(lower_than_int);

  // Ciclo menu.
  do {
    imprimirMenu();
    printf("\nIngrese una opción: ");
    scanf("%i", &menu);
    getchar();
    if (menu > 16 || menu < 0) {
      printf("\n==============================\n");
      printf("  Escriba un número válido\n");
      printf("==============================\n");

    } else {
      switch (menu) {
      // Primera Función: Agregar un integrante.
      case 1: {
        printf("\n==============================\n");
        printf("  Agregar Nuevo Integrante\n");
        printf("==============================\n\n");
        printf("Ingrese el nombre del nuevo integrante: ");
        char nombreNuevoIntegrante[101];
        leerDato(nombreNuevoIntegrante);

        // Llamar a la función para agregar un nuevo integrante
        agregarNewIntegrante(integrantes, nombreNuevoIntegrante);
        break;
      }
      // Segunda función: Eliminar un integrante.
      case 2: {
        printf("\n==============================\n");
        printf("    Eliminar Integrante\n");
        printf("==============================\n\n");
        printf("Ingrese el nombre del integrante a eliminar: ");
        char nombreEliminarIntegrante[101];
        leerDato(nombreEliminarIntegrante);

        // Llamar a la función para eliminar un integrante
        eliminarIntegrante(integrantes, nombreEliminarIntegrante);
        break;
      }
      // Tercera función: Crear una tarea.
      case 3: {
        printf("\n==============================\n");
        printf("        Crear Tarea\n");
        printf("==============================\n\n");

        printf("Ingrese el nombre de la tarea: ");
        char nombreTarea[101];
        leerDato(nombreTarea);

        printf("Ingrese la descripcion de la tarea (Máximo 200 caracteres): ");
        char descripcionTarea[200];
        leerDato(descripcionTarea);

        printf("Ingrese la prioridad de la tarea: \n1.Alta\n2.Media\n3.Baja\n");
        int prioridadTarea;
        printf("Prioridad: ");
        scanf("%d", &prioridadTarea);

        while ((limpiadorBuffer = getchar()) != '\n' && limpiadorBuffer != EOF);

        crearTarea(tareas, nombreTarea, descripcionTarea, prioridadTarea);

        break;
      }
      // Cuarta función: Asignar Prioridad a una tarea.
      case 4: {
        printf("\n==============================\n");
        printf("      Eliminar Tarea\n");
        printf("==============================\n\n");

        char opcion;
        int idTarea;
        
        printf("¿Conoce el ID de la tarea? (S/N): ");
        scanf(" %c", &opcion);

        if (opcion == 'N' || opcion == 'n') {
            consultarID_Integrante_tarea(integrantes, tareas);
            printf("Ingrese el ID de la tarea: ");
            scanf("%d", &idTarea);
        } else {
            printf("Ingrese el ID de la tarea: ");
            scanf("%d", &idTarea);
        }

        eliminarTarea(tareas, idTarea);
        

        while ((limpiadorBuffer = getchar()) != '\n' && limpiadorBuffer != EOF);
        break;
      }
      // Quinta función: Asignar Prioridad a una tarea.
      case 5: {
        printf("\n==============================\n");
        printf("      Agregar Prioridad\n");
        printf("==============================\n\n");
        
        char opcion;
        int idTarea;

        printf("¿Conoce el ID de la tarea? (S/N): ");
        scanf(" %c", &opcion);

        if (opcion == 'N' || opcion == 'n') {
            consultarID_Integrante_tarea(integrantes, tareas);
            printf("Ingrese el ID de la tarea: ");
            scanf("%d", &idTarea);
        } else {
            printf("Ingrese el ID de la tarea: ");
            scanf("%d", &idTarea);
        }


        while ((limpiadorBuffer = getchar()) != '\n' && limpiadorBuffer != EOF);

        printf("Ingrese la prioridad de la tarea: \n1.Alta\n2.Media\n3.Baja\n");
        int nuevaPrioridad;
        printf("Prioridad:");
        scanf("%d", &nuevaPrioridad);

        
        while ((limpiadorBuffer = getchar()) != '\n' && limpiadorBuffer != EOF);

        agregarPrioridad(tareas, idTarea, nuevaPrioridad);

        break;
      }
      // Sexta función: Consultar ID de Tarea o Integrante.
      case 6: {
        printf("\n==============================\n");
        printf("        Consultar ID\n");
        printf("==============================\n\n");
        consultarID_Integrante_tarea(integrantes, tareas);
        break;
      }
      // Septima función: Asignar Tarea a un integrante.
      case 7: {
        printf("\n==============================\n");
        printf("  Asignar Tarea a Integrantes\n");
        printf("==============================\n\n");
        asignarIntegrante(integrantes, tareas);
        break;
      }
      // Octava función: Actualizar Progreso de la Tarea.
      case 8: {
        printf("\n==============================\n");
        printf("    Actualizar Progreso\n");
        printf("==============================\n\n");
        
        char opcion;
        int idTarea;
        
        printf("¿Conoce el ID de la tarea? (S/N): ");
        scanf(" %c", &opcion);

        if (opcion == 'N' || opcion == 'n') {
            consultarID_Integrante_tarea(integrantes, tareas);
            printf("Ingrese el ID de la tarea: ");
            scanf("%d", &idTarea);
        } else {
            printf("Ingrese el ID de la tarea: ");
            scanf("%d", &idTarea);
        }

        while ((limpiadorBuffer = getchar()) != '\n' && limpiadorBuffer != EOF);

        actualizarProgreso(tareas, idTarea);
        break;
      }
      // Novena función: Ver Progreso Actual de la Tarea.
      case 9: {
        printf("\n==============================\n");
        printf("        Ver Progreso\n");
        printf("==============================\n\n");

        char opcion;
        int idTarea;

        printf("¿Conoce el ID de la tarea? (S/N): ");
        scanf(" %c", &opcion);

        if (opcion == 'N' || opcion == 'n') {
            consultarID_Integrante_tarea(integrantes, tareas);
            printf("Ingrese el ID de la tarea: ");
            scanf("%d", &idTarea);
        } else {
            printf("Ingrese el ID de la tarea: ");
            scanf("%d", &idTarea);
        }

        while ((limpiadorBuffer = getchar()) != '\n' && limpiadorBuffer != EOF);

        verProgreso(tareas, idTarea);
        break;
      }
      // Decima función: Importar desde CSV.
      case 10: {
        printf("\n==============================\n");
        printf("     Importar desde CSV\n");
        printf("==============================\n\n");

        importarDesdeCSV(integrantes, tareas);
        break;
      }
      // Decima primer función: Exportar a CSV.
      case 11: {
        printf("\n==============================\n");
        printf(" Exportar a CSV\n");
        printf("==============================\n\n");

        exportarA_CSV(tareas, integrantes);
        break;
      }
      // Decima segunda función: Mostrar Tareas Sin Asignar
      case 12: {
        mostrarTareasSinAsignar(integrantes, tareas);
        break;
      }
      // Decima tercera función: Mostrar Tareas Asignadas.
      case 13: {
        mostrarTareasAsignadas(tareas, integrantes);
        break;
      }
      // Decima cuarta función: Mostrar Integrantes Equipo
      case 14: {
        mostrarEquipo(integrantes);
        break;
      }
      // Decima quinta función: Limpiar Consola.
      case 15: {
        limpiarConsola();
        break;
      }
      }
    }
    // Fin del ciclo pata el menu
  } while (menu != 16);

  clearMap(integrantes);
  limpiarConsola();
  dibujo();

  return 0;
  // FIN MAIN
}


// ============================================================================
// ======================= IMPLEMENTACIÓN DE FUNCIONES ========================
// ============================================================================

// ========================== FUNCIONES PRINCIPALES ===========================

// Función para agregar un nuevo integrante al mapa de integrantes
void agregarNewIntegrante(HashMap *integrantes, char *nombre) {
  // Generar un ID único para el nuevo integrante
  int id = generarID_Integrante(integrantes);
  // Crear una estructura para el nuevo integrante
  Integrante *nuevoIntegrante = (Integrante *)malloc(sizeof(Integrante));
  nuevoIntegrante->id = id;
  strcpy(nuevoIntegrante->nombre, nombre);
  // Insertar el nuevo integrante en la tabla hash
  char strID[20]; // Convertir el ID a cadena para usarlo como clave en la tabla hash
  sprintf(strID, "%d", id);
  insertMap(integrantes, strID, nuevoIntegrante);

  printf("\nSe agregó correctamente el nuevo integrante:\n\n");
  printf("Nombre: %s\n", nombre);
  printf("ID: %d\n\n", id);
}

// Función para eliminar un integrante
void eliminarIntegrante(HashMap *integrantes, char *nombre) {

  // Buscar el integrante por su nombre
  Integrante *integrante = NULL;
  for (Pair *current = firstMap(integrantes); current != NULL;
       current = nextMap(integrantes)) {
    Integrante *datosIntegrante = (Integrante *)current->value;
    if (strcmp(datosIntegrante->nombre, nombre) == 0) {
      integrante = datosIntegrante;
      break;
    }
  }

  // Eliminar el integrante si se encontró
  if (integrante != NULL) {

    char strID[20];
    sprintf(strID, "%d", integrante->id);

    eraseMap(integrantes, strID);

    printf("\nSe eliminó correctamente el integrante:\n\n");
    printf("Nombre: %s\n", nombre);
    printf("ID: %d\n\n", integrante->id);

    free(integrante);
  }
}

void crearTarea(TreeMap *tree, const char *nombre, const char *descripcion,
                int prioridad) {
  // Crear una nueva Tarea
  Tarea *nuevaTarea = (Tarea *)malloc(sizeof(Tarea));

  if (nuevaTarea == NULL) {
    // Manejar el fallo de asignación de memoria, si es necesario
    printf("Error al asignar memoria para la nueva tarea.\n");
    return;
  }

  // Asignar valores a los campos de la nueva tarea
  int id = generarID_Tarea(tree);
  nuevaTarea->id = id;

  strncpy(nuevaTarea->nombre, nombre, sizeof(nuevaTarea->nombre) - 1);
  strncpy(nuevaTarea->descripcion, descripcion,
          sizeof(nuevaTarea->descripcion) - 1);
  nuevaTarea->prioridad = prioridad;

  // Crear una lista para el historial de progreso de la tarea
  nuevaTarea->progreso = createList();

  // Crear un nuevo objeto Progreso y agregarlo a la lista de progreso
  Progreso *progreso = (Progreso *)malloc(sizeof(Progreso));
  if (progreso == NULL) {
    // Manejar el fallo de asignación de memoria, si es necesario
    printf("Error al asignar memoria para el progreso de la nueva tarea.\n");
    free(nuevaTarea); // Liberar la memoria de la nueva tarea antes de salir
    return;
  }

  // Asignar valores iniciales al objeto Progreso
  strncpy(progreso->estado, "Sin Iniciar", sizeof(progreso->estado) - 1);
  obtenerFechaActual(progreso->fecha);

  // Agregar el objeto Progreso a la lista de progreso de la tarea
  pushBack(nuevaTarea->progreso, progreso);

  // Asignar ID de integrante predeterminado
  nuevaTarea->idIntegrante = 0;

  // Utilizar el puntero a la tarea como clave en lugar de la prioridad
  insertTreeMap(tree, &nuevaTarea->id, nuevaTarea);

  printf("\nSe agregó correctamente la tarea con ID: %d\n\n", nuevaTarea->id);
}

// Función para eliminar una tarea segun el ID
void eliminarTarea(TreeMap *tree, int tareaId) {
    Pair *resultPair = searchTreeMap(tree, &tareaId);

    if (resultPair != NULL) {
        Tarea *tarea = (Tarea *)resultPair->value;
        eraseTreeMap(tree, &tareaId);
        printf("\nSe eliminó la tarea con ID %d correctamente.\n\n", tareaId);

        // Liberar memoria de la tarea y su progreso
        if (tarea->progreso != NULL) {
            cleanList(tarea->progreso);
            free(tarea->progreso);
        }
        free(tarea);
    } else {
        printf("\nNo se encontró la tarea con ID %d.\n\n", tareaId);
    }
}


void agregarPrioridad(TreeMap *tree, int tareaId, int nuevaPrioridad) {
  // Utilizando searchTreeMap para encontrar la Tarea con el ID dado en el TreeMap
  Pair *resultPair = searchTreeMap(tree, &tareaId);

  if (resultPair != NULL) {
    // Encontrada la Tarea, actualizar su prioridad
    Tarea *foundTarea = (Tarea *)resultPair->key;
    foundTarea->prioridad = nuevaPrioridad;
    printf("\nPrioridad de Tarea con ID %d fue actualizada a ", tareaId);
    switch (nuevaPrioridad) {
      case 1: {
        printf("Alta\n\n");
        break;
      }
      case 2: {
        printf("Media\n\n");
        break;
      }
      case 3: {
        printf("Baja\n\n");
        break;
      }
    }
  } else {
    // Tarea con el ID dado no encontrada en el TreeMap
    printf("Tarea con ID %d no fue encontrada.\n\n", tareaId);
  }
}

void consultarID_Integrante_tarea(HashMap *integrantes, TreeMap *tareas) {
    char opcion;
    do {
        printf("¿Desea consultar el ID de un integrante (I) o tarea (T)? (I/T): ");
        scanf(" %c", &opcion);

        if (opcion == 'I' || opcion == 'i') {
            char nombreIntegrante[101];
            printf("Ingrese el nombre del integrante: ");
            scanf("%s", nombreIntegrante);

            // Buscar el ID del integrante en el Mapa 'integrantes'
            int idIntegrante = -1;
            for (Pair *current = firstMap(integrantes); current != NULL; current = nextMap(integrantes)) {
                Integrante *integrante = (Integrante *)current->value;
                if (strcmp(integrante->nombre, nombreIntegrante) == 0) {
                    idIntegrante = integrante->id;
                    break;
                }
            }

            if (idIntegrante != -1) {
                printf("\nEl ID del integrante '%s' es: %d\n", nombreIntegrante, idIntegrante);
            } else {
                printf("\nNo se encontró el integrante '%s'.\n", nombreIntegrante);
            }
        } else if (opcion == 'T' || opcion == 't') {
            char nombreTarea[101];
            printf("Ingrese el nombre de la tarea: ");
            scanf("%s", nombreTarea);

            // Buscar el ID de la tarea en el TreeMap 'tareas'
            int idTarea = -1; 
            for (Pair *current = firstTreeMap(tareas); current != NULL; current = nextTreeMap(tareas)) {
                Tarea *tarea = (Tarea *)current->value;
                if (strcmp(tarea->nombre, nombreTarea) == 0) {
                    idTarea = tarea->id;
                    break;
                }
            }

            if (idTarea != -1) {
                printf("\nEl ID de la tarea '%s' es: %d\n\n", nombreTarea, idTarea);
            } else {
                printf("\nNo se encontró la tarea '%s'.\n\n", nombreTarea);
            }
        } else {
            printf("Opción no válida.\n");
        }

        printf("¿Desea buscar otro Integrante o Tarea? (S/N): ");
        scanf(" %c", &opcion);
    } while (opcion == 'S' || opcion == 's');
  printf("\n");
}

void asignarIntegrante(HashMap *integrantes, TreeMap *tareas) {
    int idIntegrante;
    int idTarea;
    char opcion;

    do {
        printf("¿Conoce el ID del integrante? (S/N): ");
        scanf(" %c", &opcion);

        if (opcion == 'N' || opcion == 'n') {
            consultarID_Integrante_tarea(integrantes, tareas);
            printf("Ingrese el ID del integrante: ");
            scanf("%d", &idIntegrante);
        } else {
            printf("Ingrese el ID del integrante: ");
            scanf("%d", &idIntegrante);
        }

        printf("¿Conoce el ID de la tarea? (S/N): ");
        scanf(" %c", &opcion);

        if (opcion == 'N' || opcion == 'n') {
            consultarID_Integrante_tarea(integrantes, tareas);
            printf("Ingrese el ID de la tarea: ");
            scanf("%d", &idTarea);
        } else {
            printf("Ingrese el ID de la tarea: ");
            scanf("%d", &idTarea);
        }

        // Buscar el integrante y la tarea en los HashMaps y TreeMaps
        char strIDIntegrante[20];
        sprintf(strIDIntegrante, "%d", idIntegrante);
        Pair *integrantePair = searchMap(integrantes, strIDIntegrante);
        Integrante *integrante = (Integrante *)integrantePair->value;
      
        Pair *resultPair = searchTreeMap(tareas, &idTarea);
        Tarea *tarea = (resultPair != NULL) ? (Tarea *)resultPair->value : NULL;

        if (integrante != NULL && tarea != NULL) {
            tarea->idIntegrante = idIntegrante;
            printf("Se asignó la tarea al integrante correctamente.\n");
        } else {
            printf("No se pudo realizar la asignación.\n");
        }

        printf("¿Desea asignar otra tarea al mismo integrante? (S/N): \n\n");
        scanf(" %c", &opcion);
    } while (opcion == 'S' || opcion == 's');
}

void actualizarProgreso(TreeMap *tree, int tareaId) {
  Pair *resultPair = searchTreeMap(tree, &tareaId);
  if (resultPair != NULL) {
    // Encontrada la Tarea, actualizar su progreso
    Tarea *tarea = (Tarea *)resultPair->value;

    int submenu;
    Progreso *progreso = (Progreso *)malloc(sizeof(Progreso));

    printf("Seleccione el nuevo estado de progreso:\n\n");
    printf("1. Iniciado\n");
    printf("2. Atrasado\n");
    printf("3. En Pausa\n");
    printf("4. Finalizado\n");
    printf("5. Cancelado\n\n");
    printf("Ingrese el número de la opción: ");

    scanf("%d", &submenu);
    printf("\n");

    char estadoAnterior[50];
    if (tarea->progreso != NULL) {
      Progreso *aux = lastList(tarea->progreso);
      strncpy(estadoAnterior, aux->estado, sizeof(estadoAnterior) - 1);
        estadoAnterior[sizeof(estadoAnterior) - 1] = '\0';
    } else {
      estadoAnterior[0] = '\0';
    }

    switch (submenu) {
    case 1:
      strncpy(progreso->estado, "Iniciado", sizeof(progreso->estado) - 1);
      break;
    case 2:
      strncpy(progreso->estado, "Atrasado", sizeof(progreso->estado) - 1);
      break;
    case 3:
      strncpy(progreso->estado, "En Pausa", sizeof(progreso->estado) - 1);
      break;
    case 4:
      strncpy(progreso->estado, "Finalizado", sizeof(progreso->estado) - 1);
      break;
    case 5:
      strncpy(progreso->estado, "Cancelado", sizeof(progreso->estado) - 1);
      break;
    default:
      printf("Opción no válida. No se actualizará el progreso.\n");
      free(progreso);
      return;
    }

    if (tarea->progreso == NULL) {
      tarea->progreso = createList();
    }

    if (strcmp(estadoAnterior, progreso->estado) == 0) {
      printf("El estado de progreso no ha cambiado. No se realizará la actualización.\n");
      free(progreso);
      return;
    }

    obtenerFechaActual(progreso->fecha);
    pushBack(tarea->progreso, progreso);

    printf("Progreso actualizado con éxito. Nuevo estado: %s\n", progreso->estado);
    
  } else {
    printf("Tarea con ID %d no se encontró.\n", tareaId);
  }
}

void verProgreso(TreeMap *tree, int tareaId) {
  Pair *resultPair = searchTreeMap(tree, &tareaId);
  if (resultPair != NULL) {
    Tarea *tarea = (Tarea *)resultPair->value;

    // Imprime el ID de la Tarea, nombre, descripcion, prioridad, progreso y ID del integrante asignado si corresponde.
    printf("Tarea ID: %d\n", tarea->id);
    printf("Nombre: %s\n", tarea->nombre);
    printf("Descripcion: %s\n", tarea->descripcion);
    printf("Prioridad: %d\n", tarea->prioridad);
    if(tarea->idIntegrante == 0){
      printf("ID Integrante: No hay integrante asignado\n");
    } else {
      printf("ID Integrante: %d\n", tarea->idIntegrante);
    }

    if (tarea->progreso != NULL) {
      Node *currentNode = tarea->progreso->head;
      printf("Historial Progreso:\n");
      while (currentNode != NULL) {
        Progreso *currProgreso = currentNode->data;
        printf("%s", currProgreso->fecha);
        printf(" %s\n", currProgreso->estado);

        free(currProgreso);
        currentNode = currentNode->next;
      }
    } else {
      printf("No hay progreso.\n");
    }
  }
  printf("\n");
}

// Función para Importar desde un archivo Csv
void importarDesdeCSV(HashMap *integrantes, TreeMap *tareas) {
    char tipo_archivo[2];

    do {
      // Seleccionar un tipo de archivo a importar
        printf("¿Desea importar archivo con integrantes (I) o tareas (T)?: ");
        scanf("%1s", tipo_archivo);

        if (tipo_archivo[0] == 'I' || tipo_archivo[0] == 'i') {
            char nombre_archivo[101];
            char delimitador;

            printf("Ingrese nombre del archivo con integrantes: ");
            scanf("%s", nombre_archivo);

            int opcion;
          // Se pregunta si el archivo csv esta separado por ',' o ';'
            printf("Delimitador:\n1) ',' \n2) ';'\n");
            printf("Ingrese opcion: ");
            scanf("%d", &opcion);

            do{
              if (opcion == 1) {
                  delimitador = ',';
              } else if (opcion == 2) {
                  delimitador = ';';
              } else {
                  printf("Opción inválida\n");
                  continue;
              }
            }while (opcion == 1 || opcion == 2);
            
            FILE *archivo = fopen(nombre_archivo, "r");
            if (!archivo) {
                printf("No se pudo abrir el archivo\n");
                continue;
            }

            char linea[1024];

            while (fgets(linea, 1024, archivo)) {
                char *token = strtok(linea, &delimitador);
                int id = atoi(token);

                // Verificar si el id no tiene 5 dígitos y asignar uno nuevo si es necesario
                if (id < 10000 || id > 99999) {
                    id = generarID_Integrante(integrantes);
                }

                token = strtok(NULL, &delimitador);
                char nombre[101];
                strcpy(nombre, token);
                leerDato(nombre);

                // Crear un nuevo integrante y asignar su información
                Integrante *nuevoIntegrante = (Integrante *)malloc(sizeof(Integrante));
                nuevoIntegrante->id = id;
                strcpy(nuevoIntegrante->nombre, nombre);

                // Insertar el nuevo integrante en el mapa de integrantes
                char strID[20];
                sprintf(strID, "%d", id);
                insertMap(integrantes, strID, nuevoIntegrante);
            }

            fclose(archivo);
            printf("Se importaron integrantes desde %s\n", nombre_archivo);
        } else if (tipo_archivo[0] == 'T' || tipo_archivo[0] == 't') {
            char nombre_archivo[101];
            char delimitador;

            printf("Ingrese nombre del archivo con tareas: ");
            scanf("%s", nombre_archivo);

            int opcion;
            printf("Delimitador:\n1) ',' \n2) ';'\n");
            printf("Ingrese opcion: ");
            scanf("%d", &opcion);

            if (opcion == 1) {
                delimitador = ',';
            } else if (opcion == 2) {
                delimitador = ';';
            } else {
                printf("Opción inválida\n");
                return; 
            }

            FILE *archivo = fopen(nombre_archivo, "r");
            if (!archivo) {
                printf("No se pudo abrir el archivo\n");
                return; 
            }

            char linea[1024];

            while (fgets(linea, 1024, archivo)) {
                char *token = strtok(linea, &delimitador);

                int id = atoi(token);
                if (id < 1000000 || id > 9999999) {
                    id = generarID_Tarea(tareas);
                }

                token = strtok(NULL, &delimitador);
                char nombreTarea[101];
                strcpy(nombreTarea, token);

                token = strtok(NULL, &delimitador);
                char descripcionTarea[256];
                strcpy(descripcionTarea, token);

                token = strtok(NULL, &delimitador);
                int prioridadTarea = atoi(token);

                // Crear una nueva tarea
                Tarea *nuevaTarea = (Tarea *)malloc(sizeof(Tarea));
                nuevaTarea->id = id;
                // Asignar nombre, descripción y prioridad a la nueva tarea

                // Crear una lista para el historial de progreso de la tarea
                nuevaTarea->progreso = createList();
                insertTreeMap(tareas, &nuevaTarea->id, nuevaTarea);
            }
            fclose(archivo);
            printf("Se importaron tareas desde %s\n", nombre_archivo);
        } else {
            printf("Opción inválida\n");
        }

        char seguir;
        printf("¿Importar otro archivo (S/N)? ");
        scanf(" %c", &seguir);

        if (seguir == 'N' || seguir == 'n') {
            break;
        }
    } while (1);
}


// Función para Exportar archivos integrantes/tareas a csv
void exportarA_CSV(TreeMap* tareas, HashMap* integrantes) {

  char tipo_archivo[2];
  // Se pregunta el tipo de archivo que se desea exportar, Integrante o Tarea.
  printf("¿Desea exportar un archivo con integrantes (I) o tareas (T)?: ");
  scanf("%1s", tipo_archivo);

  if (tipo_archivo[0] == 'I' || tipo_archivo[0] == 'i') {
    // Se crea el archivo y se abre en modo de escritura
    FILE* archivo = fopen("IntegrantesExported.csv", "w");

    if(!archivo) {
      printf("No se pudo crear el archivo CSV");
      return;
    }

    fprintf(archivo, "ID,Nombre\n");
    // Se recorre el mapa de integrantes y se escriben los datos en el archivo CSV
    for(Pair* current = firstMap(integrantes); current != NULL; current = nextMap(integrantes)) {

      Integrante* integrante = current->value;

      fprintf(archivo, "%d,%s\n", 
        integrante->id,
        integrante->nombre);

    }

    fclose(archivo);

    printf("Se exportaron los integrantes al archivo IntegrantesExported.csv\n");

  } else if (tipo_archivo[0] == 'T' || tipo_archivo[0] == 't') {
    // Se crea el archivo y se abre en modo de escritura
    FILE* archivo = fopen("TareasExported.csv", "w");

    if(!archivo) {
      printf("No se pudo crear el archivo CSV");
      return;
    }

    fprintf(archivo, "ID,Nombre,Descripcion,Prioridad,Estado,ID Integrante\n");
    // Recorre el arbol de tarea y lo escribe en el archivo.
    for(Pair* current = firstTreeMap(tareas); current != NULL; current = nextTreeMap(tareas)) {

      Tarea* tarea = current->value;
      Progreso* progreso = lastList(tarea->progreso);
      char* nombreIntegrante = obtenerNombreIntegrante(integrantes, tarea->idIntegrante);

      fprintf(archivo, "%d,%s,%s,%d,%s,%d\n", 
        tarea->id,
        tarea->nombre,
        tarea->descripcion,
        tarea->prioridad,
        progreso->estado,  
        tarea->idIntegrante);

    }

    fclose(archivo);
    printf("Se exportaron las tareas al archivo TareasExported.csv\n");

  } else printf("Opción no válida");

  char seguir;
  printf("¿Desea exportar a otro archivo (S/N)?: ");
  scanf(" %c", &seguir);

  if (seguir == 'S' || seguir == 's') {
    exportarA_CSV(tareas, integrantes);
  }
}

// Función para mostrar tareas sin asignar
void mostrarTareasSinAsignar(HashMap *integrantes, TreeMap *tareas) {
  printf("\n=============================\n");
  printf("  Tareas Sin Asignar\n");
  printf("=============================\n");

  // Recorrer la estructura de tareas (BST)
  for (Pair *current = firstTreeMap(tareas); current != NULL;
      current = nextTreeMap(tareas)) {
      Tarea *tarea = (Tarea *)current->value;
      char estado[50];
      Progreso *aux = lastList(tarea->progreso);
      strncpy(estado, aux->estado, sizeof(estado) - 1);
      estado[sizeof(estado) - 1] = '\0';
    // Verificar si la tarea está asignada
    if (tarea->idIntegrante == 0) {
      // Tarea no asignada
      printf("ID: %d\n", tarea->id);
      printf("Nombre: %s\n", tarea->nombre);
      printf("Descripción: %s\n", tarea->descripcion);
      printf("Prioridad: %d\n", tarea->prioridad);
      printf("Estado: %s\n", estado);
      printf("-----------------------------\n");
    }
  }

  printf("¿Desea asignar alguna de estas tareas a un integrante? (S/N): ");
  char respuesta;
  scanf(" %c", &respuesta);

  if (respuesta == 'S' || respuesta == 's') {
    // Llamado a la función asignar tarea
    char nombreNuevoIntegrante[101];
    leerDato(nombreNuevoIntegrante);

    asignarIntegrante(integrantes, tareas);
  }
}

// Función para mostrar tareas asignadas
void mostrarTareasAsignadas(TreeMap *tareas, HashMap *integrantes) {
  printf("\n=============================\n");
  printf("  Tareas Asignadas\n");
  printf("=============================\n");

  // Recorrer la estructura de tareas (BST)
  for (Pair *current = firstTreeMap(tareas); current != NULL;
       current = nextTreeMap(tareas)) {
    Tarea *tarea = (Tarea *)current->value;

    // Verificar si la tarea está asignada
    if (tarea->idIntegrante != 0) {
      // Tarea asignada

      // Obtener el estado de la tarea
      char estado[50];
      Progreso *aux = lastList(tarea->progreso);
      strncpy(estado, aux->estado, sizeof(estado) - 1);
      estado[sizeof(estado) - 1] = '\0';

      // Mostrar la información de la tarea asignada
      printf("ID: %d\n", tarea->id);
      printf("Nombre: %s\n", tarea->nombre);
      printf("Descripción: %s\n", tarea->descripcion);
      printf("Prioridad: %d\n", tarea->prioridad);
      printf("Estado: %s\n", estado);
      printf("Asignada a: %s (ID: %d)\n", obtenerNombreIntegrante(integrantes, tarea->idIntegrante), tarea->idIntegrante);
      printf("-----------------------------\n");
    }
  }
}


// Función para mostrar los datos de todos los integrantes
void mostrarEquipo(HashMap *integrantes) {

  printf("\n====================\n");
  printf("   Equipo Actual\n");
  printf("====================\n\n");

  // Recorrer el hashmap de integrantes
  for (Pair *current = firstMap(integrantes); current != NULL;
       current = nextMap(integrantes)) {

    // Obtener datos del integrante
    Integrante *integrante = (Integrante *)current->value;

    // Mostrar datos
    printf("Nombre: %s\n", integrante->nombre);
    printf("ID: %d\n\n", integrante->id);
  }

  printf("\n");
}


// ==========================================================================
// ========================== FUNCIONES AUXILIARES ==========================

// Función para imprimir menu.
void imprimirMenu() {
  printf("==============================\n");
  printf("        TaskUnity App\n");
  printf("==============================\n");
  printf("1.  Agregar Integrante\n");
  printf("2.  Eliminar Integrante\n");
  printf("3.  Crear Tarea Nueva\n");
  printf("4.  Eliminar Tarea\n");
  printf("5.  Agregar Prioridad a la Tarea\n");
  printf("6.  Consulta de ID\n");
  printf("7.  Asignar Tarea a un Integrante\n");
  printf("8.  Actualizar Progreso\n");
  printf("9.  Ver Progreso Actual\n");
  printf("10. Importar desde CSV\n");
  printf("11. Exportar a CSV\n");
  printf("12. Mostrar Tareas Sin Asignar\n");
  printf("13. Mostrar Tareas Asignadas\n");
  printf("14. Mostrar Integrantes Equipo\n");
  printf("15. Limpiar Consola \n");
  printf("16. Salir\n");
  printf("==============================\n");
  printf("Por favor ingrese el número de la función deseada\n");
}

// Función para leer datos
void leerDato(char cadena[101]) {
  scanf("%100[^\n]s", cadena);
  int largo = strlen(cadena);
  if (largo > 101) {
    printf("No se ha podido registrar\n");
  }
  getchar();
}

// Generar ID de 5 dígitos para el integrantye nuevo
int generarID_Integrante(HashMap *integrantes) {
  int nuevoID;
  do {
    nuevoID = 10000 + rand() % 90000;
    char strID[20];
    sprintf(strID, "%d", nuevoID);

    if (searchMap(integrantes, strID) == NULL) {
      break;
    }
  } while (1);

  return nuevoID;
}

// Funcion para generar idtarea
int generarID_Tarea(TreeMap *tareas) {
  int nuevoID;
  do {
    nuevoID = 1000000 + rand() % 9000000;
    char strID[20];
    sprintf(strID, "%d", nuevoID);

    // Convertir el ID a cadena antes de buscarlo en el TreeMap
    if (searchTreeMap(tareas, strID) == NULL) {
      break;
    }
  } while (1);

  return nuevoID;
}

int lower_than_int(void *key1, void *key2) {
  int *k1 = (int *)key1;
  int *k2 = (int *)key2;
  if (*k1 < *k2)
    return 1;
  return 0;
}

// Función para obtener el nombre del integrante por ID
const char *obtenerNombreIntegrante(HashMap *integrantes, int idIntegrante) {
  char strIDIntegrante[20];
  sprintf(strIDIntegrante, "%d", idIntegrante);
  Pair *integrantePair = searchMap(integrantes, strIDIntegrante);

  if (integrantePair != NULL) {
    Integrante *integrante = (Integrante *)integrantePair->value;
    return integrante->nombre;
  } else {
    return "No encontrado";
  }
}

// Función para limpiar consola.
void limpiarConsola() {
#ifdef _WIN32
  system("cls"); // Comando para limpiar la consola en Windows
#else
  system("clear"); // Comando para limpiar la consola en sistemas Unix/Linux
#endif
}

void obtenerFechaActual(char *fecha) {
  time_t t;
  struct tm *tm_info;

  time(&t);
  tm_info = localtime(&t);

  strftime(fecha, 11, "%d/%m/%Y", tm_info);
}

// Función para dibujar figura creditos
void dibujo() {
  printf("\n                  ==============================\n");
  printf("                    Gracias por usar TaskUnity!\n");
  printf("                  ==============================\n");
  printf("\n                        ..-+#@@@@@@@#+-:.                      \n");
  printf("                    -#@@@@@##*+++++*##@@@@@#-                  \n");
  printf("                .*@@@@+:::::::::::::::::::=@@@@#.              \n");
  printf("             .+@@@*:::::::::::::::::::::::::::*@@@+.           \n");
  printf("           .#@@#:::::::::::::::::::::::::::::::::#@@@.         \n");
  printf("         .+@@*:::::::::::::::::::::::::::::::::::::*@@*.       \n");
  printf("        :@@#:::::::::::::::::::::::::::::::::::::::::#@@-      \n");
  printf("       +@@-:::::::::::::::::::::::::::::::::::::::::::-@@*     \n");
  printf("      #@@:::::::::::::::::::::::::::::::::::::::::::::::#@#    \n");
  printf("     #@#:::::::::::::::::::::::::::::::::::::::::::::::::#@#   \n");
  printf("    -@@-::::::::::::::::::::::::::::::::::::::::::::::::::@@=  \n");
  printf("   :@@-::::::::::::#@@+::::::::::#@@=:::::::::::::::::::::-@@: \n");
  printf("   *@#::::::::::::-@@@#:::::::::+@@@#::::::::::::::::::::::#@* \n");
  printf("  .@@-::::::::::::@@@@*:::::::::@@@@*:::::::::::::::::::::::@@.\n");
  printf("  -@@:::::::::::::#@@@::::::::::@@@#::::::::::::::::::::::::@@-\n");
  printf("  =@@::::::::::::::++::::::::::::+=:::::::::::::::::::::::::#@+\n");
  printf("  +@#:::::::::::::::::::::::::::::::::::::::::::::::::::::::#@+\n");
  printf("  =@@:::::::::::::::::::::::::::::::::::::::::::::::::::::::#@+\n");
  printf("  -@@:::::=@:::::::::::::::::::::::::::::::::::*@:::::::::::@@-\n");
  printf("  .@@-:::+@@:::::::::::::::::::::::::::::::::::#@#::::::::::@@.\n");
  printf("   *@#:::::=@-:::::::::::::::::::::::::::::::::@@#-::::::::#@* \n");
  printf("   :@@-::::::@+::::::::::::::::::::::::::::::-@-::::::::::-@@: \n");
  printf("    =@@-::::::+@=::::::::::::::::::::::::::-#*::::::::::::@@=  \n");
  printf("    .#@#::::::::+@::::::::::::::::::::::::%%:::::::::::::#@#.  \n");
  printf("      #@#:::::::::=@#-:::::::::::::::::=@#::::::::::::::#@#    \n");
  printf("       +@@-::::::::::=#@#-:::::::::+#@*-::::::::::::::-@@*     \n");
  printf("        -@@#::::::::::::::-+%%%%*=-:::::::::::::::::::#@@-      \n");
  printf("         .*@@*:::::::::::::::::::::::::::::::::::::+@@*.       \n");
  printf("           .@@@#:::::::::::::::::::::::::::::::::*@@@.         \n");
  printf("             .+@@@+:::::::::::::::::::::::::::+@@@+.           \n");
  printf("               ..#@@@@+:::::::::::::::::::=@@@@#..             \n");
  printf("                    -#@@@@@##++====+##@@@@@#=                  \n");
  printf("                        .:-+#@@@@@@@#+-:.                      \n");
  printf("\n                  ==============================\n");
  printf("                   CREATED BY TEAM-TEAM GROUP\n");
  printf("                  ==============================\n");
}
