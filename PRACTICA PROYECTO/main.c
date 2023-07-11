#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITAS 100
#define MAX_MEDICOS 10

struct Cita {
    char fecha[20];
    char hora[10];
    char descripcion[100];
    char medico[50];
    int identificacion;
    int ocupada;
};

struct Agenda {
    struct Cita citas[MAX_CITAS];
    int num_citas;
};

struct Medico {
    char nombre[50];
    int ocupado;
};

void guardarCitasEnArchivo(struct Agenda* agenda) {
    FILE* archivo = fopen("citasAgenda.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    for (int i = 0; i < agenda->num_citas; i++) {
        fprintf(archivo, "Cita %d:\n", i + 1);
        fprintf(archivo, "Fecha: %s\n", agenda->citas[i].fecha);
        fprintf(archivo, "Hora: %s\n", agenda->citas[i].hora);
        fprintf(archivo, "Descripcion: %s\n", agenda->citas[i].descripcion);
        fprintf(archivo, "Medico: %s\n", agenda->citas[i].medico);
        fprintf(archivo, "Estado: %s\n", agenda->citas[i].ocupada ? "Ocupada" : "Disponible");
        fprintf(archivo, "------------------------\n");
    }

    fclose(archivo);
    
}

void agendarCita(struct Agenda* agenda, struct Medico* medicos, int num_medicos) {
    int identificacion;
    if (agenda->num_citas < MAX_CITAS) {
        struct Cita nuevaCita;
        printf("Fecha: ");
        scanf("%s", nuevaCita.fecha);

        printf("Ingrese su numero de cedula: ");
        scanf("%d", &identificacion);

        printf("Horario disponible para la agendacion de citas:\n");
        printf("1) 9:00\n");
        printf("2) 10:00\n");
        printf("3) 11:00\n");
        printf("4) 15:00\n");
        printf("5) 19:00\n");
        printf("6) 21:00\n");
        printf("7) 16:00\n");
        printf("8) 17:00\n");
        printf("9) 23:00\n");
        // Agrega más opciones de hora según sea necesario

        int opcion;
        printf("Seleccione el numero de la hora: ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                strcpy(nuevaCita.hora, "9:00");
                break;
            case 2:
                strcpy(nuevaCita.hora, "10:00");
                break;
            case 3:
                strcpy(nuevaCita.hora, "11:00");
                break;
            case 4:
                strcpy(nuevaCita.hora, "15:00");
                break;
            case 5:
                strcpy(nuevaCita.hora, "19:00");
                break;
            case 6:
                strcpy(nuevaCita.hora, "21:00");
                break;
            case 7:
                strcpy(nuevaCita.hora, "16:00");
                break;
            case 8:
                strcpy(nuevaCita.hora, "17:00");
                break;
            case 9:
                strcpy(nuevaCita.hora, "23:00");
                break;
            default:
                printf("Usted ingreso una hora no establecida!!\nPor favor vuelva a intentarlo!!\n");
                return;
        }

        printf("Ingrese su nombre: ");
        scanf(" %[^\n]", nuevaCita.descripcion);

        printf("Medicos disponibles:\n");
        for (int i = 0; i < num_medicos; i++) {
            if (medicos[i].ocupado == 0) {
                printf("%d) %s\n", i + 1, medicos[i].nombre);
            }
        }
        printf("Seleccione el numero del medico: ");
        scanf("%d", &opcion);
        if (opcion >= 1 && opcion <= num_medicos && medicos[opcion - 1].ocupado == 0) {
            strcpy(nuevaCita.medico, medicos[opcion - 1].nombre);
            nuevaCita.ocupada = 1;
            medicos[opcion - 1].ocupado = 1;

            agenda->citas[agenda->num_citas] = nuevaCita;
            agenda->num_citas++;

            guardarCitasEnArchivo(agenda);

            printf("\n!!Cita agendada con exito!!\n");
            printf("IMPORTANTE: \nRecuerde llegar 10 minutos antes a su cita.");
        } else {
            printf("Opcion invalida o medico ocupado.\n");
        }
    } else {
        printf("La agenda esta llena!! \nNo es posible agendar mas citas.\n");
    }
}

void mostrarAgenda(struct Agenda* agenda) {
    printf("------------------------\n");
    printf("Agenda de citas:\n");
    for (int i = 0; i < agenda->num_citas; i++) {
        printf("Cita %d:\n", i + 1);
        printf("Fecha: %s\n", agenda->citas[i].fecha);
        printf("Hora: %s\n", agenda->citas[i].hora);
        printf("Nombre del paciente: %s\n", agenda->citas[i].descripcion);
        printf("Medico: %s\n", agenda->citas[i].medico);
        printf("Estado: %s\n", agenda->citas[i].ocupada ? "Ocupada" : "Disponible");
        printf("------------------------\n");
    }
}

int main() {
    struct Agenda miAgenda;
    miAgenda.num_citas = 0;

    struct Medico medicos[MAX_MEDICOS] = {
        {"Dr. Perez", 0},
        {"Dra. Gomez", 0},
        {"Dr. Lopez", 0},
        {"Dra. Rodriguez", 0},
        {"Dr. Martinez", 0},
        {"Dr. Fernandez", 0},
        {"Dra. Sanchez", 0},
        {"Dra. Sarmiento", 0},
        {"Dr. Mullo", 0},
        {"Dr. Valencia", 0}
    };
    int num_medicos = sizeof(medicos) / sizeof(medicos[0]);

    int opcion;
    do {
        printf("--BIENVENIDO A LA FUNDACION SALUD PARA TODOS--\n");
        printf("\n");
        printf("------Menu------\n");
        printf("1) Agendar cita\n");
        printf("2) Mostrar agenda\n");
        printf("3) Salir\n");
        printf("Ingrese su opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agendarCita(&miAgenda, medicos, num_medicos);
                break;
            case 2:
                mostrarAgenda(&miAgenda);
                break;
            case 3:
                printf("Tenga un bonito dia.\n");
                break;
            default:
                printf("Usted ingreso una opcion no valida!! Vuelva a intentarlo\n");
                break;
        }

        printf("\n");
    } while (opcion != 3);

    return 0;
}