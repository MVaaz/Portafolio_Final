#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 101
#define FILENAME "symbol_table.csv"

typedef struct Symbol {
    char name[50];
    char type[30];
    char value[50];
    char scope[30];
    struct Symbol *next;
} Symbol;

Symbol *hashTable[TABLE_SIZE];

unsigned int hash(const char *key) {
    unsigned int h = 0;
    while (*key)
        h = (h * 31) + *key++;
    return h % TABLE_SIZE;
}

void insertSymbol(char *name, char *type, char *value, char *scope) {
    unsigned int index = hash(name);

    Symbol *newSymbol = (Symbol *)malloc(sizeof(Symbol));
    strcpy(newSymbol->name, name);
    strcpy(newSymbol->type, type);
    strcpy(newSymbol->value, value);
    strcpy(newSymbol->scope, scope);
    newSymbol->next = hashTable[index];

    hashTable[index] = newSymbol;

    printf("✔ Identificador '%s' agregado.\n", name);
}

Symbol* searchSymbol(char *name) {
    unsigned int index = hash(name);
    Symbol *curr = hashTable[index];

    while (curr) {
        if (strcmp(curr->name, name) == 0)
            return curr;
        curr = curr->next;
    }
    return NULL;
}

void deleteSymbol(char *name) {
    unsigned int index = hash(name);
    Symbol *curr = hashTable[index];
    Symbol *prev = NULL;

    while (curr) {
        if (strcmp(curr->name, name) == 0) {
            if (prev)
                prev->next = curr->next;
            else
                hashTable[index] = curr->next;

            free(curr);
            printf("✔ Identificador '%s' eliminado.\n", name);
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    printf("⚠ No se encontró el identificador '%s'.\n", name);
}

void saveToCSV() {
    FILE *f = fopen(FILENAME, "w");
    if (!f) {
        printf("❌ Error guardando archivo.\n");
        return;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        Symbol *curr = hashTable[i];
        while (curr) {
            fprintf(f, "%s,%s,%s,%s\n", curr->name, curr->type, curr->value, curr->scope);
            curr = curr->next;
        }
    }

    fclose(f);
}

void loadFromCSV() {
    FILE *f = fopen(FILENAME, "r");
    if (!f) {
        printf("⚠ Archivo '%s' no encontrado. Será creado al guardar.\n", FILENAME);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        char name[50], type[30], value[50], scope[30];

        sscanf(line, "%49[^,],%29[^,],%49[^,],%29[^\n]",
               name, type, value, scope);

        insertSymbol(name, type, value, scope);
    }

    fclose(f);
    printf("✔ Datos cargados desde '%s'.\n", FILENAME);
}

void menu() {
    printf("\n--- TABLA DE SÍMBOLOS ---\n");
    printf("1. Agregar identificador\n");
    printf("2. Buscar identificador\n");
    printf("3. Eliminar identificador\n");
    printf("4. Guardar y salir\n");
    printf("Selecciona una opción: ");
}

int main() {
    int option;
    char name[50], type[30], value[50], scope[30];

    loadFromCSV();

    do {
        menu();
        scanf("%d", &option);
        getchar();

        switch(option) {
            case 1:
                printf("Nombre: ");
                fgets(name, sizeof(name), stdin); name[strcspn(name, "\n")] = 0;

                printf("Tipo: ");
                fgets(type, sizeof(type), stdin); type[strcspn(type, "\n")] = 0;

                printf("Valor: ");
                fgets(value, sizeof(value), stdin); value[strcspn(value, "\n")] = 0;

                printf("Ámbito: ");
                fgets(scope, sizeof(scope), stdin); scope[strcspn(scope, "\n")] = 0;

                insertSymbol(name, type, value, scope);
                break;

            case 2:
                printf("Buscar nombre: ");
                fgets(name, sizeof(name), stdin); name[strcspn(name, "\n")] = 0;

                Symbol *s = searchSymbol(name);
                if (s) {
                    printf("✔ Encontrado: %s | Tipo: %s | Valor: %s | Ámbito: %s\n",
                           s->name, s->type, s->value, s->scope);
                } else {
                    printf("⚠ No encontrado.\n");
                }
                break;

            case 3:
                printf("Eliminar nombre: ");
                fgets(name, sizeof(name), stdin); name[strcspn(name, "\n")] = 0;
                deleteSymbol(name);
                break;

            case 4:
                saveToCSV();
                printf("✔ Datos guardados. Saliendo...\n");
                break;

            default:
                printf("Opción inválida.\n");
        }

    } while(option != 4);

    return 0;
}
