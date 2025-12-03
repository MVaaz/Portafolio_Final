
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_STR 128
#define DATAFILE "students.csv"

typedef struct {
    int matricula;        
    char *nombre;
    char *apellido;
    int ncal;             
    double *calificaciones;
} Student;

typedef struct Node {
    Student data;
    struct Node *left;
    struct Node *right;
} Node;


char* strdupa(const char *s) {
    if (!s) return NULL;
    char *d = malloc(strlen(s)+1);
    if (!d) { perror("malloc"); exit(EXIT_FAILURE); }
    strcpy(d, s);
    return d;
}

double promedio_student(const Student *s) {
    if (!s || s->ncal == 0) return 0.0;
    double sum = 0.0;
    for (int i=0;i<s->ncal;i++) sum += s->calificaciones[i];
    return sum / s->ncal;
}

void print_student(const Student *s) {
    if (!s) return;
    printf("Mat: %08d | %s %s | nCal: %d | Prom: %.2f | Califs: ",
           s->matricula, s->nombre, s->apellido, s->ncal, promedio_student(s));
    for (int i=0;i<s->ncal;i++) {
        printf("%.2f", s->calificaciones[i]);
        if (i+1 < s->ncal) printf(", ");
    }
    printf("\n");
}

Node* create_node(const Student *s) {
    Node *n = malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(EXIT_FAILURE); }
    n->data.matricula = s->matricula;
    n->data.nombre = strdupa(s->nombre);
    n->data.apellido = strdupa(s->apellido);
    n->data.ncal = s->ncal;
    n->data.calificaciones = malloc(sizeof(double) * s->ncal);
    if (s->ncal > 0 && !n->data.calificaciones) { perror("malloc"); exit(EXIT_FAILURE); }
    for (int i=0;i<s->ncal;i++) n->data.calificaciones[i] = s->calificaciones[i];
    n->left = n->right = NULL;
    return n;
}

Node* insert_node(Node *root, const Student *s) {
    if (!root) return create_node(s);
    if (s->matricula < root->data.matricula)
        root->left = insert_node(root->left, s);
    else if (s->matricula > root->data.matricula)
        root->right = insert_node(root->right, s);
    else
        printf("Ya existe un alumno con matrícula %08d (ignorado).\n", s->matricula);
    return root;
}

Node* find_min(Node *root) {
    if (!root) return NULL;
    while (root->left) root = root->left;
    return root;
}

Node* delete_node(Node *root, int matricula) {
    if (!root) return NULL;
    if (matricula < root->data.matricula)
        root->left = delete_node(root->left, matricula);
    else if (matricula > root->data.matricula)
        root->right = delete_node(root->right, matricula);
    else {
        // encontrado
        if (!root->left && !root->right) {
            // hoja
            free(root->data.nombre);
            free(root->data.apellido);
            free(root->data.calificaciones);
            free(root);
            return NULL;
        } else if (!root->left || !root->right) {
            Node *child = root->left ? root->left : root->right;
            free(root->data.nombre);
            free(root->data.apellido);
            free(root->data.calificaciones);
            *root = *child; 
            free(child);
            return root;
        } else {
            Node *succ = find_min(root->right);
            free(root->data.nombre);
            free(root->data.apellido);
            free(root->data.calificaciones);
            root->data.matricula = succ->data.matricula;
            root->data.nombre = strdupa(succ->data.nombre);
            root->data.apellido = strdupa(succ->data.apellido);
            root->data.ncal = succ->data.ncal;
            root->data.calificaciones = malloc(sizeof(double) * succ->data.ncal);
            for (int i=0;i<succ->data.ncal;i++) root->data.calificaciones[i] = succ->data.calificaciones[i];
            root->right = delete_node(root->right, succ->data.matricula);
        }
    }
    return root;
}

Node* search_node(Node *root, int matricula) {
    if (!root) return NULL;
    if (matricula == root->data.matricula) return root;
    if (matricula < root->data.matricula) return search_node(root->left, matricula);
    return search_node(root->right, matricula);
}

void inorder_print(Node *root) {
    if (!root) return;
    inorder_print(root->left);
    print_student(&root->data);
    inorder_print(root->right);
}

void collect_nodes(Node *root, Node ***arr, int *count, int *cap) {
    if (!root) return;
    collect_nodes(root->left, arr, count, cap);
    if (*count >= *cap) {
        *cap *= 2;
        *arr = realloc(*arr, sizeof(Node*) * (*cap));
        if (!*arr) { perror("realloc"); exit(EXIT_FAILURE); }
    }
    (*arr)[(*count)++] = root;
    collect_nodes(root->right, arr, count, cap);
}

int cmp_prom_desc(const void *a, const void *b) {
    const Node *A = *(const Node**)a;
    const Node *B = *(const Node**)b;
    double pa = promedio_student(&A->data);
    double pb = promedio_student(&B->data);
    if (pa < pb) return 1;
    if (pa > pb) return -1;
    return 0;
}

void report_promedio_threshold(Node *root, double threshold, bool less_than) {
    if (!root) return;
    report_promedio_threshold(root->left, threshold, less_than);
    double p = promedio_student(&root->data);
    if ((less_than && p < threshold) || (!less_than && p >= threshold)) {
        print_student(&root->data);
    }
    report_promedio_threshold(root->right, threshold, less_than);
}

int count_lower_than_matricula(Node *root, int matricula) {
    Node *target = search_node(root, matricula);
    if (!target) return -1;
    double ptarget = promedio_student(&target->data);
    // recorrer y contar
    if (!root) return 0;
    int count = 0;
    Node **arr = malloc(sizeof(Node*) * 16);
    int cap = 16, n = 0;
    collect_nodes(root, &arr, &n, &cap);
    for (int i=0;i<n;i++) {
        if (arr[i]->data.matricula == matricula) continue;
        if (promedio_student(&arr[i]->data) < ptarget) count++;
    }
    free(arr);
    return count;
}

void print_level(Node *root, int level) {
    if (!root) return;
    if (level == 0) {
        print_student(&root->data);
    } else {
        print_level(root->left, level-1);
        print_level(root->right, level-1);
    }
}

/* Imprimir árbol en ASCII (lado derecho arriba) */
void print_ascii_tree(Node *root, int space) {
    if (!root) return;
    const int GAP = 6;
    space += GAP;
    print_ascii_tree(root->right, space);
    for (int i=GAP;i<space;i++) putchar(' ');
    printf("%08d\n", root->data.matricula);
    print_ascii_tree(root->left, space);
}

/* Liberar todo el árbol */
void free_tree(Node *root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root->data.nombre);
    free(root->data.apellido);
    free(root->data.calificaciones);
    free(root);
}

/* ---------- I/O a archivo (CSV simple) ----------
Format por línea:
matricula;nombre;apellido;ncal;g1,g2,g3,...
ejemplo:
12345678;Juan;Perez;3;80.5,90,70
*/
bool save_tree_to_file(Node *root, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) { perror("fopen"); return false; }
    // recopilamos en inorder para orden por matrícula
    Node **arr = malloc(sizeof(Node*)*16);
    int cap=16, n=0;
    collect_nodes(root, &arr, &n, &cap);
    for (int i=0;i<n;i++) {
        Student *s = &arr[i]->data;
        fprintf(f, "%08d;%s;%s;%d;", s->matricula, s->nombre, s->apellido, s->ncal);
        for (int j=0;j<s->ncal;j++) {
            fprintf(f, "%.2f", s->calificaciones[j]);
            if (j+1 < s->ncal) fprintf(f, ",");
        }
        fprintf(f, "\n");
    }
    free(arr);
    fclose(f);
    return true;
}

Node* load_tree_from_file(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        // No existe archivo: es válido iniciar vacío
        return NULL;
    }
    Node *root = NULL;
    char line[1024];
    while (fgets(line, sizeof(line), f)) {
        // quitar newline
        char *p = line;
        while (*p && (*p == '\n' || *p == '\r')) *p++ = '\0';
        // parsear por ;
        char *tok = strtok(line, ";");
        if (!tok) continue;
        int matricula = atoi(tok);
        char *nombre = strtok(NULL, ";"); if (!nombre) nombre = "";
        char *apellido = strtok(NULL, ";"); if (!apellido) apellido = "";
        char *ncal_s = strtok(NULL, ";"); if (!ncal_s) ncal_s = "0";
        int ncal = atoi(ncal_s);
        char *calstr = strtok(NULL, ";");
        // preparar Student
        Student s;
        s.matricula = matricula;
        s.nombre = nombre;
        s.apellido = apellido;
        s.ncal = ncal;
        s.calificaciones = NULL;
        if (ncal > 0) {
            s.calificaciones = malloc(sizeof(double)*ncal);
            // parsear calstr por ,
            if (calstr) {
                char *c = strtok(calstr, ",");
                int idx = 0;
                while (c && idx < ncal) {
                    s.calificaciones[idx++] = atof(c);
                    c = strtok(NULL, ",");
                }
                // en caso de menos califs de las esperadas, completar con 0
                for (; idx<ncal; idx++) s.calificaciones[idx] = 0.0;
            } else {
                for (int i=0;i<ncal;i++) s.calificaciones[i] = 0.0;
            }
        }
        root = insert_node(root, &s);
        if (s.calificaciones) free(s.calificaciones);
    }
    fclose(f);
    return root;
}

/* ---------- Actualizar una calificación (reemplazar según índice) ---------- */
bool update_single_grade(Node *root, int matricula, int index0, double newgrade) {
    Node *n = search_node(root, matricula);
    if (!n) return false;
    if (index0 < 0 || index0 >= n->data.ncal) return false;
    n->data.calificaciones[index0] = newgrade;
    return true;
}

/* ---------- Menú de usuario ---------- */

void prompt_student_input(Student *s) {
    char buf[MAX_STR];
    printf("Ingrese matrícula (8 dígitos entero): ");
    fgets(buf, sizeof(buf), stdin);
    s->matricula = atoi(buf);
    printf("Nombre: ");
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = 0;
    s->nombre = buf[0] ? buf : "";
    printf("Apellido: ");
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = 0;
    s->apellido = buf[0] ? buf : "";
    printf("Numero de calificaciones: ");
    fgets(buf, sizeof(buf), stdin);
    s->ncal = atoi(buf);
    if (s->ncal > 0) {
        s->calificaciones = malloc(sizeof(double) * s->ncal);
        for (int i=0;i<s->ncal;i++) {
            printf("Calificación %d: ", i+1);
            fgets(buf, sizeof(buf), stdin);
            s->calificaciones[i] = atof(buf);
        }
    } else {
        s->calificaciones = NULL;
    }
}

/* Menú principal */
void menu() {
    Node *root = load_tree_from_file(DATAFILE);
    int choice;
    do {
        printf("\n--- Sistema ABB Estudiantes ---\n");
        printf("1. Reporte: todos los estudiantes ordenados por matrícula (in-order)\n");
        printf("2. Reporte: todos los estudiantes ordenados por promedio (desc)\n");
        printf("3. Reporte: estudiantes con promedio < 70\n");
        printf("4. Reporte: estudiantes con promedio >= 70\n");
        printf("5. Insertar nuevo estudiante\n");
        printf("6. Eliminar estudiante por matrícula\n");
        printf("7. Actualizar UNA calificación (por matrícula)\n");
        printf("8. Dada matrícula, contar alumnos con promedio menor que el promedio de esa matrícula\n");
        printf("9. Mostrar valores de los nodos de un nivel (raíz = 0)\n");
        printf("10. Mostrar árbol (ASCII)\n");
        printf("11. Guardar en archivo y salir\n");
        printf("0. Salir sin guardar\n");
        printf("Elija opción: ");
        char buf[64];
        fgets(buf, sizeof(buf), stdin);
        choice = atoi(buf);
        switch(choice) {
            case 1:
                printf("\n--- Todos (orden por matrícula) ---\n");
                inorder_print(root);
                break;
            case 2: {
                // collect y ordenar por promedio
                Node **arr = malloc(sizeof(Node*)*16);
                int cap=16, n=0;
                collect_nodes(root, &arr, &n, &cap);
                qsort(arr, n, sizeof(Node*), cmp_prom_desc);
                printf("\n--- Todos (orden por promedio desc) ---\n");
                for (int i=0;i<n;i++) print_student(&arr[i]->data);
                free(arr);
                break;
            }
            case 3:
                printf("\n--- Promedio < 70 ---\n");
                report_promedio_threshold(root, 70.0, true);
                break;
            case 4:
                printf("\n--- Promedio >= 70 ---\n");
                report_promedio_threshold(root, 70.0, false);
                break;
            case 5: {
                Student s;
                // pedimos datos con buffers locales
                char tmp[MAX_STR];
                printf("Ingrese matrícula (8 dígitos entero): ");
                fgets(tmp, sizeof(tmp), stdin); s.matricula = atoi(tmp);
                printf("Nombre: ");
                fgets(tmp, sizeof(tmp), stdin); tmp[strcspn(tmp, "\n")] = 0;
                s.nombre = tmp;
                printf("Apellido: ");
                fgets(tmp, sizeof(tmp), stdin); tmp[strcspn(tmp, "\n")] = 0;
                s.apellido = tmp;
                printf("Numero de calificaciones: ");
                fgets(tmp, sizeof(tmp), stdin); s.ncal = atoi(tmp);
                s.calificaciones = NULL;
                if (s.ncal > 0) {
                    s.calificaciones = malloc(sizeof(double)*s.ncal);
                    for (int i=0;i<s.ncal;i++) {
                        printf("Calificación %d: ", i+1);
                        fgets(tmp, sizeof(tmp), stdin);
                        s.calificaciones[i] = atof(tmp);
                    }
                }
                root = insert_node(root, &s);
                if (s.calificaciones) free(s.calificaciones);
                break;
            }
            case 6: {
                printf("Matrícula a eliminar: ");
                fgets(buf, sizeof(buf), stdin);
                int m = atoi(buf);
                root = delete_node(root, m);
                printf("Si existía, se eliminó (o quedó información previa si no existía).\n");
                break;
            }
            case 7: {
                printf("Matrícula del alumno a actualizar: ");
                fgets(buf, sizeof(buf), stdin);
                int m = atoi(buf);
                Node *n = search_node(root, m);
                if (!n) {
                    printf("No existe alumno con matrícula %08d\n", m);
                    break;
                }
                printf("Alumno encontrado: "); print_student(&n->data);
                printf("Ingrese índice de calificación a actualizar (1 .. %d): ", n->data.ncal);
                fgets(buf, sizeof(buf), stdin);
                int idx = atoi(buf) - 1;
                if (idx < 0 || idx >= n->data.ncal) {
                    printf("Índice inválido.\n");
                    break;
                }
                printf("Nueva calificación: ");
                fgets(buf, sizeof(buf), stdin);
                double ng = atof(buf);
                update_single_grade(root, m, idx, ng);
                printf("Actualizado.\n");
                break;
            }
            case 8: {
                printf("Ingrese matrícula de referencia: ");
                fgets(buf, sizeof(buf), stdin);
                int m = atoi(buf);
                int c = count_lower_than_matricula(root, m);
                if (c < 0) printf("No existe matrícula %08d\n", m);
                else printf("Número de alumnos con promedio menor que el de %08d: %d\n", m, c);
                break;
            }
            case 9: {
                printf("Ingrese nivel (raíz = 0): ");
                fgets(buf, sizeof(buf), stdin);
                int lvl = atoi(buf);
                printf("--- Nodos en nivel %d ---\n", lvl);
                print_level(root, lvl);
                break;
            }
            case 10:
                printf("--- Árbol (ASCII, se muestra la matrícula) ---\n");
                print_ascii_tree(root, 0);
                break;
            case 11:
                if (save_tree_to_file(root, DATAFILE)) {
                    printf("Guardado en '%s'. Saliendo...\n", DATAFILE);
                } else {
                    printf("Error al guardar en '%s'.\n", DATAFILE);
                }
                free_tree(root);
                return;
            case 0:
                free_tree(root);
                printf("Saliendo sin guardar.\n");
                return;
            default:
                printf("Opción no válida.\n");
        }
    } while (1);
}

/* ---------- main ---------- */

int main(void) {
    printf("Sistema ABB - Gestor de estudiantes\n");
    printf("El archivo de datos por defecto es '%s'\n", DATAFILE);
    menu();
    return 0;
}
