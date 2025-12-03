#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000
#define NAME_LEN 50
#define CAREER_LEN 50

typedef struct {
    int matricula;
    char nombre[NAME_LEN];
    char carrera[CAREER_LEN];
    int ocupado;
    int borrado;
} Estudiante;

Estudiante tabla[MAX];

int hash(int key) {
    return key % MAX;
}

void inicializarTabla() {
    for(int i=0;i<MAX;i++){
        tabla[i].ocupado = 0;
        tabla[i].borrado = 0;
    }
}

int insertar(int matricula, char *nombre, char *carrera) {
    int index = hash(matricula);
    int i = 0;
    while(i < MAX) {
        int pos = (index + i) % MAX;
        if(!tabla[pos].ocupado || tabla[pos].borrado) {
            tabla[pos].matricula = matricula;
            strcpy(tabla[pos].nombre, nombre);
            strcpy(tabla[pos].carrera, carrera);
            tabla[pos].ocupado = 1;
            tabla[pos].borrado = 0;
            return 1;
        }
        i++;
    }
    return 0;
}

Estudiante* buscar(int matricula) {
    int index = hash(matricula);
    int i = 0;
    while(i < MAX) {
        int pos = (index + i) % MAX;
        if(tabla[pos].ocupado && !tabla[pos].borrado && tabla[pos].matricula == matricula)
            return &tabla[pos];
        if(!tabla[pos].ocupado && !tabla[pos].borrado)
            return NULL;
        i++;
    }
    return NULL;
}

int eliminar(int matricula) {
    int index = hash(matricula);
    int i = 0;
    while(i < MAX) {
        int pos = (index + i) % MAX;
        if(tabla[pos].ocupado && !tabla[pos].borrado && tabla[pos].matricula == matricula) {
            tabla[pos].borrado = 1;
            return 1;
        }
        if(!tabla[pos].ocupado && !tabla[pos].borrado)
            return 0;
        i++;
    }
    return 0;
}

void cargarCSV() {
    FILE *f = fopen("estudiantes.csv", "r");
    if(!f) {
        f = fopen("estudiantes.csv", "w");
        fclose(f);
        return;
    }
    int matricula; char nombre[NAME_LEN]; char carrera[CAREER_LEN];
    while(fscanf(f, "%d,%49[^,],%49[^\n]\n", &matricula, nombre, carrera) == 3) {
        insertar(matricula, nombre, carrera);
    }
    fclose(f);
}

void guardarCSV() {
    FILE *f = fopen("estudiantes.csv", "w");
    for(int i=0;i<MAX;i++){
        if(tabla[i].ocupado && !tabla[i].borrado)
            fprintf(f, "%d,%s,%s\n", tabla[i].matricula, tabla[i].nombre, tabla[i].carrera);
    }
    fclose(f);
}

int main(){
    inicializarTabla();
    cargarCSV();

    int opcion;
    do {
        printf("\n--- MENU ---\n1. Agregar estudiante\n2. Buscar estudiante\n3. Eliminar estudiante\n4. Salir\nOpcion: ");
        scanf("%d", &opcion);

        if(opcion == 1) {
            int matricula; char nombre[NAME_LEN]; char carrera[CAREER_LEN];
            printf("Matricula: "); scanf("%d", &matricula);
            printf("Nombre: "); scanf("%s", nombre);
            printf("Carrera: "); scanf("%s", carrera);
            if(insertar(matricula, nombre, carrera)) printf("Agregado correctamente.\n");
            else printf("Tabla llena.\n");
        }
        else if(opcion == 2) {
            int matricula; printf("Matricula: "); scanf("%d", &matricula);
            Estudiante *e = buscar(matricula);
            if(e) printf("Encontrado: %s, %s\n", e->nombre, e->carrera);
            else printf("No encontrado.\n");
        }
        else if(opcion == 3) {
            int matricula; printf("Matricula: "); scanf("%d", &matricula);
            if(eliminar(matricula)) printf("Eliminado.\n");
            else printf("No existe.\n");
        }
    } while(opcion != 4);

    guardarCSV();
    return 0;
}