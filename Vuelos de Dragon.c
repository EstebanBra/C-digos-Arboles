#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void esperarTecla();
void bienvenida();
void menu();
RESERVA *crearReserva(int numReserva, char nombre[], char destino[]);
RESERVA *insertarVueloDeDragon(RESERVA *raizReservas, int numReservaIngresado, char nombre[], char destino[]);
RESERVA *cancelarReserva(RESERVA *raizReservas, int numReserva);
void buscarReserva(RESERVA *raizReservas, int numReservaBuscado);
void mostrarReservasPorDestino(RESERVA *raizReservas, char destino[]);
void mostrarReservasInOrden(RESERVA *raizReservas);
void liberarArbol(RESERVA *raiz);

int main()
{
    bienvenida();
    int opcion, cantidadReservas, i, numReserva, numReservaBuscado;
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

                printf("Ingrese el Numero de su Reserva:\n->");
                scanf("%d", &numReserva);
                limpiarBuffer();

                printf("Ingrese Su Nombre:\n->");
                fgets(nombre, sizeof(nombre), stdin);

                printf("Ingrese el Destino de su Vuelo:\n->");
                fgets(destino, sizeof(destino), stdin);

                raizReservas = insertarVueloDeDragon(raizReservas, numReserva, nombre, destino);

                printf("\n¡Reserva %d ingresada exitosamente!\n\n", i + 1);

                esperarTecla();

                limpiarPantalla();
            }
            break;
        case 2:

            break;
        case 3:
            limpiarPantalla();
            printf("Ingrese el Numero de Reserva que busca:\n->");
            scanf("%d", &numReservaBuscado);
            limpiarBuffer();
            buscarReserva(raizReservas, numReservaBuscado);
            esperarTecla();
            break;
        case 4:

            break;
        case 5:
            printf("Reservas En Orden\n");
            mostrarReservasInOrden(raizReservas);
            esperarTecla();
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
void limpiarPantalla()
{
#ifdef _WIN32
    system("cls"); // Comando para limpiar pantalla en Windows
#else
    system("clear"); // Comando para limpiar pantalla en macOS y sistemas basados en Unix/Linux
#endif
}
void limpiarBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
void esperarTecla()
{
    printf("Presione Enter para continuar...");
    fflush(stdout); // Limpia el búfer de salida para asegurarse de que el mensaje se muestre antes de esperar la entrada
    getchar();      // Espera a que el usuario presione una tecla
}
void bienvenida()
{
    printf("\n\t\tBIENVENIDO A LOS VUELOS DE DRAGON\n");

    printf("\n\tAqui podras realizar reservas de vuelos en DRAGONES!, puedes ir a cualquier parte del mundo.\n\n");
    esperarTecla();
    limpiarPantalla();
}
void menu()
{

    int opcion;

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

    printf("\nIngrese numero de la opcion:\n->");
}
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
RESERVA *cancelarReserva(RESERVA *raizReservas, int numReserva)
{
    if (raizReservas == NULL)
    {
        printf("No se econtro la reserva %d en los registros, por lo tanto no se puede eliminar", numReserva);
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
            return auxReserva;
        }
        else if (raizReservas->derecha == NULL)
        {
            RESERVA *auxReserva = raizReservas->izquierda;
            free(raizReservas);
            return auxReserva;
        }
        // Nodo Con dos hijos, encontrar sucesor inOrden
        RESERVA *sucesor = raizReservas->derecha;
        while(sucesor->izquierda != NULL)
        {
            sucesor = sucesor->izquierda;
        }
        
        0
    }
}
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
void liberarArbol(RESERVA *raiz)
{
    if (raiz != NULL)
    {
        liberarArbol(raiz->izquierda);
        liberarArbol(raiz->derecha);
        free(raiz);
    }
}