#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Cliente {
    int id;
    int transacciones;  
    int llegada;        
    int inicio;         
    int salida;         
    struct Cliente *sig;
} Cliente;

typedef struct {
    Cliente *frente, *final;
    int totalClientes;
    int tiempoTotalEspera;
} Cola;


void inicializarCola(Cola *q) {
    q->frente = q->final = NULL;
    q->totalClientes = 0;
    q->tiempoTotalEspera = 0;
}

int colaVacia(Cola *q) {
    return (q->frente == NULL);
}

void encolar(Cola *q, Cliente *c) {
    c->sig = NULL;
    if (colaVacia(q)) {
        q->frente = q->final = c;
    } else {
        q->final->sig = c;
        q->final = c;
    }
    q->totalClientes++;
}

Cliente* desencolar(Cola *q) {
    if (colaVacia(q)) return NULL;
    Cliente *aux = q->frente;
    q->frente = aux->sig;
    if (q->frente == NULL) q->final = NULL;
    return aux;
}


void simularBanco(int numClientes) {
    Cola colas[3];
    for (int i = 0; i < 3; i++) inicializarCola(&colas[i]);

    int tiempo = 0;
    for (int i = 0; i < numClientes; i++) {
        Cliente *nuevo = (Cliente*)malloc(sizeof(Cliente));
        nuevo->id = i + 1;
        nuevo->transacciones = (rand() % 5) + 1; // 1 a 5
        nuevo->llegada = tiempo;
        nuevo->sig = NULL;

        
        int colaAsignada = rand() % 3;
        encolar(&colas[colaAsignada], nuevo);

        printf("Cliente %d llega en t=%d y va a la cola %d con %d transacciones.\n",
               nuevo->id, nuevo->llegada, colaAsignada + 1, nuevo->transacciones);

        tiempo += (rand() % 3); 
    }

    printf("\n--- Atendiendo clientes ---\n");
    for (int i = 0; i < 3; i++) {
        int tiempoCaja = 0;
        printf("\nCola %d:\n", i + 1);
        while (!colaVacia(&colas[i])) {
            Cliente *c = desencolar(&colas[i]);
            if (tiempoCaja < c->llegada) tiempoCaja = c->llegada;
            c->inicio = tiempoCaja;
            c->salida = c->inicio + c->transacciones;

            int espera = c->inicio - c->llegada;
            colas[i].tiempoTotalEspera += espera;

            printf("Cliente %d: llegó=%d, inicio=%d, salida=%d, espera=%d\n",
                   c->id, c->llegada, c->inicio, c->salida, espera);

            tiempoCaja = c->salida;
            free(c);
        }

        if (colas[i].totalClientes > 0) {
            float promedio = (float)colas[i].tiempoTotalEspera / colas[i].totalClientes;
            printf("Clientes atendidos: %d | Espera promedio: %.2f\n",
                   colas[i].totalClientes, promedio);
        } else {
            printf("Sin clientes.\n");
        }
    }
}

int main() {
    srand(time(NULL));
    int numClientes;
    printf("Ingresa el numero de clientes a simular: ");
    scanf("%d", &numClientes);
    simularBanco(numClientes);
    system("pause"); 
    return 0;
}
