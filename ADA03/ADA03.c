#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 4096

// ----- ESTRUCTURA DE PELÍCULA -----
typedef struct Movie {
    int id;
    char title[200];
    float vote_average;
    char release_date[20];
    char genres[200];
    char keywords[400];
    struct Movie *next;
    struct Movie *prev;
} Movie;

// ----- CABEZA DE LA LISTA -----
typedef struct {
    Movie *head;
    Movie *tail;
} MovieList;

// ===== FUNCIONES DE UTILIDAD =====
void initList(MovieList *list) {
    list->head = NULL;
    list->tail = NULL;
}

Movie *createMovie(int id, char *title, float vote, char *date, char *genres, char *keywords) {
    Movie *newNode = (Movie*)malloc(sizeof(Movie));
    if (!newNode) {
        printf("Error: no se pudo asignar memoria.\n");
        exit(1);
    }
    newNode->id = id;
    strcpy(newNode->title, title);
    newNode->vote_average = vote;
    strcpy(newNode->release_date, date);
    strcpy(newNode->genres, genres);
    strcpy(newNode->keywords, keywords);
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void appendMovie(MovieList *list, Movie *movie) {
    if (list->head == NULL) {
        list->head = list->tail = movie;
    } else {
        list->tail->next = movie;
        movie->prev = list->tail;
        list->tail = movie;
    }
}

void printMovie(Movie *m) {
    printf("\nID: %d\nTítulo: %s\nPuntuación: %.2f\nFecha: %s\nGéneros: %s\nPalabras clave: %s\n",
           m->id, m->title, m->vote_average, m->release_date, m->genres, m->keywords);
}

// ===== FUNCIÓN AUXILIAR: strcasestr personalizada =====
char *strcasestr_custom(const char *haystack, const char *needle) {
    if (!*needle) return (char *)haystack;
    for (; *haystack; haystack++) {
        const char *h = haystack;
        const char *n = needle;
        while (*h && *n && tolower((unsigned char)*h) == tolower((unsigned char)*n)) {
            h++; n++;
        }
        if (!*n) return (char *)haystack;
    }
    return NULL;
}

// ===== FUNCIÓN PARA LEER CAMPOS ENTRE COMILLAS =====
char *parse_csv_field(char **line_ptr) {
    char *line = *line_ptr;
    static char field[256];
    int i = 0;

    // Saltar espacios o comas iniciales
    while (*line == ' ' || *line == ',') line++;

    if (*line == '"') {
        line++; // saltar la comilla inicial
        while (*line && *line != '"') {
            field[i++] = *line++;
        }
        field[i] = '\0';
        if (*line == '"') line++; // saltar comilla final
        if (*line == ',') line++; // saltar coma después de comillas
    } else {
        while (*line && *line != ',') {
            field[i++] = *line++;
        }
        field[i] = '\0';
        if (*line == ',') line++;
    }

    *line_ptr = line;
    return field;
}

// ===== CARGAR DESDE CSV =====
void loadFromCSV(MovieList *list, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("No se pudo abrir el archivo %s\n", filename);
        exit(1);
    }

    char line[MAX_LINE];
    fgets(line, sizeof(line), fp); // saltar encabezado

    while (fgets(line, sizeof(line), fp)) {
        char *p = line;
        int id;
        float vote;
        char title[100], date[20], genres[100], keywords[200];

        id = atoi(parse_csv_field(&p));
        strcpy(title, parse_csv_field(&p));
        vote = atof(parse_csv_field(&p));
        strcpy(date, parse_csv_field(&p));
        strcpy(genres, parse_csv_field(&p));
        strcpy(keywords, parse_csv_field(&p));

        appendMovie(list, createMovie(id, title, vote, date, genres, keywords));
    }

    fclose(fp);
    printf("\nDatos cargados correctamente desde %s\n", filename);
}

// ===== BUSCAR =====
Movie* searchByTitle(MovieList *list, const char *title) {
    Movie *temp = list->head;
    while (temp) {
        if (strcasestr_custom(temp->title, title))
            return temp;
        temp = temp->next;
    }
    return NULL;
}

Movie* searchById(MovieList *list, int id) {
    Movie *temp = list->head;
    while (temp) {
        if (temp->id == id) return temp;
        temp = temp->next;
    }
    return NULL;
}

// ===== ELIMINAR =====
void deleteMovie(MovieList *list, const char *title) {
    Movie *m = searchByTitle(list, title);
    if (!m) {
        printf("Película no encontrada.\n");
        return;
    }

    printMovie(m);
    printf("\n¿Desea eliminar esta película? (s/n): ");
    char op;
    scanf(" %c", &op);
    if (tolower(op) != 's') return;

    if (m->prev) m->prev->next = m->next;
    else list->head = m->next;
    if (m->next) m->next->prev = m->prev;
    else list->tail = m->prev;

    free(m);
    printf("Película eliminada.\n");
}

// ===== ACTUALIZAR =====
void updateMovie(MovieList *list, const char *title) {
    Movie *m = searchByTitle(list, title);
    if (!m) {
        printf("Película no encontrada.\n");
        return;
    }

    printMovie(m);
    printf("\nSeleccione campo a modificar:\n");
    printf("1. Título\n2. Puntuación\n3. Fecha\n4. Géneros\n5. Palabras clave\n> ");
    int opt;
    scanf("%d", &opt);
    getchar();

    switch (opt) {
        case 1:
            printf("Nuevo título: ");
            fgets(m->title, 100, stdin);
            m->title[strcspn(m->title, "\n")] = 0;
            break;
        case 2:
            printf("Nueva puntuación: ");
            scanf("%f", &m->vote_average);
            break;
        case 3:
            printf("Nueva fecha: ");
            scanf("%s", m->release_date);
            break;
        case 4:
            printf("Nuevos géneros: ");
            getchar();
            fgets(m->genres, 100, stdin);
            m->genres[strcspn(m->genres, "\n")] = 0;
            break;
        case 5:
            printf("Nuevas palabras clave: ");
            getchar();
            fgets(m->keywords, 200, stdin);
            m->keywords[strcspn(m->keywords, "\n")] = 0;
            break;
        default:
            printf("Opción inválida.\n");
    }

    printf("Datos actualizados.\n");
}

// ===== INSERTAR =====
void insertMovie(MovieList *list) {
    int id;
    float vote;
    char title[100], date[20], genres[100], keywords[200];

    printf("ID: "); scanf("%d", &id);
    printf("Título: "); getchar(); fgets(title, 100, stdin);
    title[strcspn(title, "\n")] = 0;
    printf("Puntuación: "); scanf("%f", &vote);
    printf("Fecha: "); scanf("%s", date);
    printf("Géneros: "); getchar(); fgets(genres, 100, stdin);
    genres[strcspn(genres, "\n")] = 0;
    printf("Palabras clave: "); fgets(keywords, 200, stdin);
    keywords[strcspn(keywords, "\n")] = 0;

    appendMovie(list, createMovie(id, title, vote, date, genres, keywords));
    printf("Película insertada correctamente.\n");
}

// ===== MOSTRAR TODAS =====
void printAll(MovieList *list) {
    Movie *temp = list->head;
    while (temp) {
        printMovie(temp);
        temp = temp->next;
    }
}

// ===== MENÚ PRINCIPAL =====
int main() {
    MovieList list;
    initList(&list);
    char filename[] = "Movies.csv";

    printf("Cargando datos desde %s...\n", filename);
    loadFromCSV(&list, filename);

    int option;
    do {
        printf("\n===== MENÚ =====\n");
        printf("1. Buscar película por título\n");
        printf("2. Buscar película por ID\n");
        printf("3. Insertar nueva película\n");
        printf("4. Eliminar película\n");
        printf("5. Actualizar datos\n");
        printf("6. Mostrar todas las películas\n");
        printf("7. Salir\n> ");
        scanf("%d", &option);
        getchar();

        switch (option) {
            case 1: {
                char title[100];
                printf("Título a buscar: ");
                fgets(title, 100, stdin);
                title[strcspn(title, "\n")] = 0;
                Movie *m = searchByTitle(&list, title);
                if (m) printMovie(m);
                else printf("No encontrada.\n");
                break;
            }
            case 2: {
                int id;
                printf("ID a buscar: ");
                scanf("%d", &id);
                Movie *m = searchById(&list, id);
                if (m) printMovie(m);
                else printf("No encontrada.\n");
                break;
            }
            case 3: insertMovie(&list); break;
            case 4: {
                char title[100];
                printf("Título a eliminar: ");
                fgets(title, 100, stdin);
                title[strcspn(title, "\n")] = 0;
                deleteMovie(&list, title);
                break;
            }
            case 5: {
                char title[100];
                printf("Título a actualizar: ");
                fgets(title, 100, stdin);
                title[strcspn(title, "\n")] = 0;
                updateMovie(&list, title);
                break;
            }
            case 6: printAll(&list); break;
            case 7: printf("Saliendo...\n"); break;
            default: printf("Opción inválida.\n");
        }
    } while (option != 7);

    return 0;
}