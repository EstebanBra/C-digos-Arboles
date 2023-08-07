#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct reservasVueloDeDragon
{
    int numReserva;
    char nombre[100];
    char destino[100];
    struct reservasVueloDeDragon *izquierda;
    struct reservasVueloDeDragon *derecha;
} RESERVA;

void limpiarPantalla();
void limpiarBuffer();
void esperarEnter();
void bienvenida();
void menu();
int validarNumeroReserva();
RESERVA *crearReserva(int numReserva, char nombre[], char destino[]);
RESERVA *insertarVueloDeDragon(RESERVA *raizReservas, int numReservaIngresado, char nombre[], char destino[]);
RESERVA *cancelarReserva(RESERVA *raizReservas, int numReserva);
void buscarReserva(RESERVA *raizReservas, int numReservaBuscado);
int buscarMostrarReservasPorDestino(RESERVA *raizReservas, char destinoBuscado[]);
void mostrarReservasInOrden(RESERVA *raizReservas);
void liberarArbol(RESERVA *raiz);

//Main con el switch, con casos para cada funcion
int main()
{
    srand(time(NULL));
    bienvenida();
    int opcion, cantidadReservas, i, numReserva, numReservaBuscado, numReservaCancelar;
    char nombre[100], destino[100];
    RESERVA *raizReservas = NULL;

    do
    {
        limpiarPantalla();
        menu();
        scanf("%d", &opcion);
        limpiarBuffer();

        switch (opcion)
        {
        case 1:
            limpiarPantalla();
            printf("\t\tReservas de vuelos\n\n");
            printf("Cuantas Reservas Desea hacer?\n->");
            scanf("%d", &cantidadReservas);
            limpiarBuffer();
            for (i = 0; i < cantidadReservas; i++)
            {

                numReserva = validarNumeroReserva();

                printf("Ingrese Su Nombre:\n->");
                fgets(nombre, sizeof(nombre), stdin);

                printf("Ingrese el Destino de su Vuelo:\n->");
                fgets(destino, sizeof(destino), stdin);

                raizReservas = insertarVueloDeDragon(raizReservas, numReserva, nombre, destino);

                printf("\n¡Reserva %d ingresada exitosamente!\n", i + 1);

                esperarEnter();

                limpiarPantalla();
            }
            break;
        case 2:
            limpiarPantalla();
            printf("Reservas En Orden\n\n");
            mostrarReservasInOrden(raizReservas);
            printf("\t\tCancelar Reserva\n\nIngrese el numero de Reserva que desea cancelar\n->");
            scanf("%d", &numReservaCancelar);
            limpiarBuffer();
            raizReservas = cancelarReserva(raizReservas, numReservaCancelar);
            esperarEnter();
            break;
        case 3:
            limpiarPantalla();
            printf("Ingrese el Numero de Reserva que busca:\n->");
            scanf("%d", &numReservaBuscado);
            limpiarBuffer();
            buscarReserva(raizReservas, numReservaBuscado);
            esperarEnter();
            break;
        case 4:
            limpiarPantalla();
            printf("Ingrese el Destino para mostrar las reservas:\n->");
            fgets(destino, sizeof(destino), stdin);

            printf("Reservas para el destino %s: \n", destino);

            // Llamamos a la función y obtenemos el valor de reservas encontradas
            int reservasEncontradas = buscarMostrarReservasPorDestino(raizReservas, destino);

            // Si no se encontraron reservas con el destino buscado, mostramos el mensaje
            if (reservasEncontradas == 0)
            {
                printf("No se encontraron reservas al destino %s\n", destino);
            }

            esperarEnter();
            break;
        case 5:
            printf("Reservas En Orden\n\n");
            mostrarReservasInOrden(raizReservas);
            esperarEnter();
            break;
        case 0:
            printf("\nHasta Pronto!. Buenas Suerte Aventurero\n");
            liberarArbol(raizReservas);
            break;
        default:
            printf("Opcion no Valida. Intente Nuevamente. \n");
        }

    } while (opcion != 0);
    return 0;
}

//Funcion para limpiar pantalla, es para mac y pc
void limpiarPantalla()
{
#ifdef _WIN32
    system("cls"); // Comando para limpiar pantalla en Windows
#else
    system("clear"); // Comando para limpiar pantalla en macOS y sistemas basados en Unix/Linux
#endif
}

//Funcion para limpiar el enter que queda en el buffer despues de ingresar un entero
void limpiarBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

//Funcion para esperar
void esperarEnter()
{
    printf("Presione Enter para continuar...");
    fflush(stdout); // Limpia el búfer de salida para asegurarse de que el mensaje se muestre antes de esperar la entrada
    getchar();      // Espera a que el usuario presione una tecla
}

void bienvenida()
{
    printf("\n\t\tBIENVENIDO A LOS VUELOS DE DRAGON\n\n");

    printf("Este es un sistema para realizar, buscar, mostar, y cancelar reservas de vuelo.\n\n");
    esperarEnter();
    limpiarPantalla();
}

void menu()
{
    printf("|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|\n\n"
           "|/////////////////// MENU ////////////////////|\n"
           "|                                             |\n"
           "|      1. Realizar Reserva de Vuelo.          |\n"
           "|      2. Cancelar Reserva de Vuelo.          |\n"
           "|      3. Buscar Reserva en los Registros.    |\n"
           "|      4. Mostrar Reservas Por Destino.       |\n"
           "|      5. Mostrar Reservas Ordenadas.         |\n"
           "|      0. Salir del Programa.                 |\n"
           "|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|\n");

    printf("\nIngrese una opcion:\n->");
}

//Funcion para validar el numero de reserva, debe ser de 3 digitos obligatoriamente
int validarNumeroReserva()
{
    int numero;

    while (1)
    {
        printf("Ingrese un numero de tres digitos: \n->");
        scanf("%d", &numero);
        limpiarBuffer(numero);

        if (numero >= 100 && numero <= 999)
        {
            int valido = 1; // Bandera para verificar unicidad

            // Verificar unicidad
            for (int i = 100; i <= 999; i++)
            {
                if (i != numero && i == numero)
                {
                    valido = 0;
                    break;
                }
            }

            if (valido)
            {
                printf("Numero ingresado correctamente.\n");
                return numero;
            }
            else
            {
                printf("El numero ya fue ingresado. Ingrese otro.\n");
            }
        }
        else
        {
            printf("Numero no valido. Ingrese un numero de tres digitos.\n");
        }
    }
}

//Funcion para mostrar las reservas ordenadas
void mostrarReservasInOrden(RESERVA *raizReservas)
{
    if (raizReservas != NULL)
    {
        mostrarReservasInOrden(raizReservas->izquierda);
        printf("Numero de reserva: %d\n", raizReservas->numReserva);
        printf("Nombre: %s", raizReservas->nombre);
        printf("Destino: %s\n\n", raizReservas->destino);
        mostrarReservasInOrden(raizReservas->derecha);
    }
}

//Funcion para crear una reserva
RESERVA *crearReserva(int numReserva, char nombre[], char destino[])
{
    RESERVA *nuevaReserva = (RESERVA *)malloc(sizeof(RESERVA));
    nuevaReserva->numReserva = numReserva;
    strcpy(nuevaReserva->nombre, nombre);
    strcpy(nuevaReserva->destino, destino);
    nuevaReserva->izquierda = NULL;
    nuevaReserva->derecha = NULL;
    return nuevaReserva;
}

//Funcion para Insertar una Reserva en el ABB
RESERVA *insertarVueloDeDragon(RESERVA *raizReservas, int numReservaIngresado, char nombre[], char destino[])
{
    // Si No Existen reservas se crea una y se asigna a la raiz.
    if (raizReservas == NULL)
    {
        raizReservas = crearReserva(numReservaIngresado, nombre, destino);
    }

    // Si el numero de reserva ingresado es menor al de la raiz se asigan en el hijo Izquierdo.
    if (numReservaIngresado < raizReservas->numReserva)
    {
        raizReservas->izquierda = insertarVueloDeDragon(raizReservas->izquierda, numReservaIngresado, nombre, destino);

    } // Si el numero de Reserva ingresado es mayor que el de la raiz se asigan al hijo derexho
    else if (numReservaIngresado > raizReservas->numReserva)
    {
        raizReservas->derecha = insertarVueloDeDragon(raizReservas->derecha, numReservaIngresado, nombre, destino);
    }
    return raizReservas;
}

//Funcion para cancelar las reservas
RESERVA *cancelarReserva(RESERVA *raizReservas, int numReserva)
{
    if (raizReservas == NULL)
    {
        printf("No se encontro la reserva %d en los registros, por lo tanto no se puede cancelar\n", numReserva);
        return raizReservas;
    }

    if (numReserva < raizReservas->numReserva)
    {
        raizReservas->izquierda = cancelarReserva(raizReservas->izquierda, numReserva);
    }
    else if (numReserva > raizReservas->numReserva)
    {
        raizReservas->derecha = cancelarReserva(raizReservas->derecha, numReserva);
    }
    else
    {
        // Si los nodos tienen al menos un hijo
        if (raizReservas->izquierda == NULL)
        {
            RESERVA *auxReserva = raizReservas->derecha;
            free(raizReservas);
            printf("Reserva Cancelada Exitosamente!\n");
            return auxReserva;
        }
        else if (raizReservas->derecha == NULL)
        {
            RESERVA *auxReserva = raizReservas->izquierda;
            free(raizReservas);
            printf("Reserva Cancelada Exitosamente!\n");
            return auxReserva;
        }
        // Nodo Con dos hijos, encontrar sucesor inOrden
        RESERVA *sucesor = raizReservas->derecha;
        while (sucesor->izquierda != NULL)
        {
            sucesor = sucesor->izquierda;
        }

        // Verificar que el sucesor tenga un numReserva válido antes de copiar sus datos
        if (sucesor->numReserva != 0)
        {
            // Copiar datos del sucesor al nodo actual
            raizReservas->numReserva = sucesor->numReserva;
            strcpy(raizReservas->nombre, sucesor->nombre);
            strcpy(raizReservas->destino, sucesor->destino);

            // Eliminar el sucesor
            raizReservas->derecha = cancelarReserva(raizReservas->derecha, sucesor->numReserva);
        }
        else
        {
            // Si el sucesor tiene numReserva igual a cero, simplemente lo eliminamos
            raizReservas->derecha = cancelarReserva(raizReservas->derecha, 0);
        }
        printf("Reserva Cancelada Exitosamente!\n");
    }
    return raizReservas;
}

//Funcion para buscar una reserva por su numero
void buscarReserva(RESERVA *raizReservas, int numReservaBuscado)
{
    if (raizReservas == NULL)
    {
        printf("No se encontro la Reserva %d en los Registros.\n", numReservaBuscado);
        return;
    }
    if (raizReservas->numReserva == numReservaBuscado)
    {
        printf("Reserva Encontrada:\n");
        printf("Numero de reserva: %d\n", raizReservas->numReserva);
        printf("Nombre: %s", raizReservas->nombre);
        printf("Destino: %s\n", raizReservas->destino);
        return;
    }
    else if (numReservaBuscado < raizReservas->numReserva)
    {
        buscarReserva(raizReservas->izquierda, numReservaBuscado);
    }
    else
    {
        buscarReserva(raizReservas->derecha, numReservaBuscado);
    }
}

//Funcion para Buscar y mostrar reservas por destino
int buscarMostrarReservasPorDestino(RESERVA *raizReservas, char destinoBuscado[])
{
    int reservasEncontradas = 0;

    if (raizReservas != NULL)
    {
        reservasEncontradas += buscarMostrarReservasPorDestino(raizReservas->izquierda, destinoBuscado);

        if (strcasecmp(raizReservas->destino, destinoBuscado) == 0)
        {
            printf("Numero de reserva: %d\n", raizReservas->numReserva);
            printf("Nombre: %s", raizReservas->nombre);
            printf("Destino: %s\n\n", raizReservas->destino);
            reservasEncontradas++; // Incrementamos el contador cuando encontramos una reserva con el destino buscado
        }

        reservasEncontradas += buscarMostrarReservasPorDestino(raizReservas->derecha, destinoBuscado);
    }

    return reservasEncontradas;
}

//Funcion para liberar el arbol
void liberarArbol(RESERVA *raiz)
{
    if (raiz != NULL)
    {
        liberarArbol(raiz->izquierda);
        liberarArbol(raiz->derecha);
        free(raiz);
    }
}
