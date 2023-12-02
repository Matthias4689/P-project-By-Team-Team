# □ Task/Unity
##### Gestor de Tareas

## Descripción

🔲Task/Unity es una aplicación colaborativa de gestión de tareas enfocada en impulsar la colaboración y eficiencia en equipos comprometidos con los Objetivos de Desarrollo Sostenible (ODS) de la ONU. La plataforma se centra en organizar el trabajo en equipo de manera consciente a través de una serie de funciones clave. Permite agregar y eliminar integrantes, así como la creación, asignación y actualización detallada de tareas. Los usuarios pueden asignar prioridades, consultar información específica mediante identificadores únicos, asignar tareas a miembros del equipo y monitorear el progreso de cada tarea.

## Cómo compilar y ejecutar

1. Clonar el repositorio:

    ```
    git clone <https://github.com/Matthias4689/Task-Unity-App.git>
    ```

3. Navegar al directorio del proyecto:

    ```
    cd Task-Unity-App

    ```

4. Compilar el código:

    ```
    gcc gcc main.c hashmap.c list.c treemap.c -o TaskApp

    ```

5. Ejecutar la aplicación:

    ```
    ./TaskApp

    ```


## Funcionalidades

### Funcionando correctamente:

- generarID_Integrante
- generarID_Tarea
- obtenerFechaActual
- obtenerNombreIntegrante
- agregarNewIntegrante
- eliminarIntegrante
- mostrarEquipo
- crearTarea
- eliminarTarea
- agregarPrioridad
- consultarID_Integrante_tarea
- asignarIntegrante
- verProgreso
- actualizarProgreso
- exportarA_CSV
- mostrarTareasSinAsignar
- mostrarTareasAsignadas
- limpiarConsola


### Problemas conocidos:

- Algunas operaciones pueden tener problemas si se ingresan datos incorrectos o si se intenta realizar una acción inválida. Se recomienda seguir las instrucciones y restricciones proporcionadas en las funciones para evitar problemas. Aún estamos investigando algunas posibles soluciones.
- Se decidió cambiar la clave utilizada en el árbol de tareas, pasando de la prioridad a utilizar el ID asignado. Esta decisión surgió debido a la limitación de diferenciar entre tareas dentro del mismo nivel de prioridad, dado el uso de una escala restringida (1=alta, 2=media, 3=baja). En situaciones donde existen numerosas tareas en un mismo nivel de prioridad, la efectividad en su ordenamiento se ve comprometida. Sin embargo, este cambio conllevó a la pérdida del propósito inicial de emplear un árbol para almacenar las tareas, resultando en una carencia del ordenamiento originalmente buscado.
- Funcion importarDesdeCSV no funciona correctamente. Aún estamos investigando la posible causa.

### A mejorar:

- Mostrar calendario mensual con el historial de cambios marcado con las fechas indicadas
- Asignar un tiempo de cumplimiento en minutos/horas.
- Crear 2 o mas equimos de trabajo diferentes.
- restringir la cantidad de tareas asignadas a cada integrante.
- Poder editar tareas existentes.
- Agregar una opcion de volver o cancelar la opcion seleccionada en el menu.
- Que a mayor prioridad, mayor sea la cantidad de integrantes que se necesiten asignar.
- Agregar una opcion que muestre las tareas segun su prioridad o progreso.


## Contribuciones

### Héctor Aguilera:
- Aporte Nulo
- **Auto-evaluación**: -----.

### Javier Donetch:
- Desarrollo de funciones:
    - leerDato
    - asignarIntegrante
    - actualizarProgreso
    - verProgreso
    - mostrarTareasSinAsignar
    - mostrarTareasAsignadas
    - obtenerNombreIntegrante
    - limpiarConsola
    - dibujo
- Diseño inicial de la interfaz de usuario.
- Documentación y depuración del código.
- **Auto-evaluación**: 3 (Aporte excelente).

### Abram Lipson:
- Desarrollo de funciones:
    - generarID_Tarea
    - crearTarea
    - eliminarTarea
    - agregarPrioridad
    - importarDesdeCSV
    - obtenerFechaActual
- Documentación y depuración del código.
- **Auto-evaluación**: 3 (Aporte excelente).

### Matías Romero:
- Desarrollo de funciones:
    - agregarNewIntegrante
    - generarID_Integrante
    - eliminarIntegrante
    - mostrarEquipo
    - consultarID_Integrante_tarea
    - exportarA_CSV
- Documentación y depuración del código. 
- Diseño y redacción del README.
- **Auto-evaluación**: 3 (Aporte excelente).


###### Project-By-Team-Team
