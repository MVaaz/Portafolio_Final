#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h> 

#define MAX_EXPR 256
#define MAX_STACK 128

// Pila para caracteres
typedef struct {
    char data[MAX_STACK];
    int top;
} CharStack;

void cs_init(CharStack *s) { s->top = -1; }
int cs_empty(CharStack *s) { return s->top == -1; }
char cs_top(CharStack *s) { return s->data[s->top]; }
void cs_push(CharStack *s, char c) { s->data[++s->top] = c; }
char cs_pop(CharStack *s) { return s->data[s->top--]; }

// Pila para valores enteros
typedef struct {
    int data[MAX_STACK];
    int top;
} IntStack;

void is_init(IntStack *s) { s->top = -1; }
int is_empty(IntStack *s) { return s->top == -1; }
void is_push(IntStack *s, int v) { s->data[++s->top] = v; }
int is_pop(IntStack *s) { return s->data[s->top--]; }

// Precedencia de operadores
int precedence(char op) {
    switch(op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3; 
        case '(': return 0;
        default: return -1;
    }
}

// Verificar si un operador es asociativo por la derecha
int is_right_associative(char op) {
    return (op == '^'); 
}

// Convertir infijo a postfijo
void infix_to_postfix(const char *infix, char *postfix) {
    CharStack ops;
    cs_init(&ops);
    int i = 0, j = 0;
    while (infix[i]) {
        if (isspace(infix[i])) { i++; continue; }
        if (isdigit(infix[i])) {
            // Copia el número completo
            while (isdigit(infix[i])) postfix[j++] = infix[i++];
            postfix[j++] = ' ';
        } else if (infix[i] == '(') {
            cs_push(&ops, '(');
            i++;
        } else if (infix[i] == ')') {
            while (!cs_empty(&ops) && cs_top(&ops) != '(')
                postfix[j++] = cs_pop(&ops), postfix[j++] = ' ';
            if (!cs_empty(&ops) && cs_top(&ops) == '(') cs_pop(&ops);
            i++;
        } else if (strchr("+-*/^", infix[i])) {
            while (!cs_empty(&ops) &&
                   ((is_right_associative(infix[i]) && precedence(cs_top(&ops)) > precedence(infix[i])) ||
                   (!is_right_associative(infix[i]) && precedence(cs_top(&ops)) >= precedence(infix[i])))) {
                postfix[j++] = cs_pop(&ops), postfix[j++] = ' ';
            }
            cs_push(&ops, infix[i]);
            i++;
        } else {
            i++; // Ignora caracteres desconocidos
        }
    }
    while (!cs_empty(&ops))
        postfix[j++] = cs_pop(&ops), postfix[j++] = ' ';
    postfix[j] = '\0';
}

// Evaluar expresión postfija
int eval_postfix(const char *postfix) {
    IntStack vals;
    is_init(&vals);
    int i = 0;
    while (postfix[i]) {
        if (isspace(postfix[i])) { i++; continue; }
        if (isdigit(postfix[i])) {
            int num = 0;
            while (isdigit(postfix[i])) num = num * 10 + (postfix[i++] - '0');
            is_push(&vals, num);
        } else if (strchr("+-*/^", postfix[i])) {
            int b = is_pop(&vals), a = is_pop(&vals), res = 0;
            switch(postfix[i]) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/': res = a / b; break;
                case '^': res = (int)pow(a, b); break;
            }
            is_push(&vals, res);
            i++;
        } else {
            i++; // Ignora caracteres desconocidos
        }
    }
    return is_pop(&vals);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <archivo_entrada>\n", argv[0]);
        return 1;
    }
    FILE *fin = fopen(argv[1], "r");
    if (!fin) {
        printf("No se pudo abrir el archivo de entrada.\n");
        return 1;
    }
    FILE *fout = fopen("exp_postfijas.txt", "w");
    if (!fout) {
        printf("No se pudo crear el archivo de salida.\n");
        fclose(fin);
        return 1;
    }
    char line[MAX_EXPR];
    while (fgets(line, sizeof(line), fin)) {
        char *expr = strtok(line, ";");
        while (expr) {
            char postfix[MAX_EXPR] = {0};
            infix_to_postfix(expr, postfix);
            int result = eval_postfix(postfix);
            fprintf(fout, "Expresión: %s; Resultado: %d\n", postfix, result);
            expr = strtok(NULL, ";");
        }
    }
    fclose(fin);
    fclose(fout);
    return 0;
}