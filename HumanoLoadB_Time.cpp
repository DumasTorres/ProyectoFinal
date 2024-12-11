#include <mpi.h>
#include <omp.h>
#include <iostream>
#include <vector>
#include <windows.h> // Para sem�foros y funciones espec�ficas de Windows

// Sem�foro para sincronizaci�n
HANDLE semaforo;

// Funci�n que simula tareas paralelas del humano
void gestionar_tareas(int id_humano, int total_tareas) {
    int tareas_por_hilo = total_tareas / 4; // Asignar una cantidad de tareas por hilo

    // Asignaci�n din�mica de tareas para balancear carga
#pragma omp parallel num_threads(4) // Simula 4 pensamientos/procesos paralelos
    {
        int id_hilo = omp_get_thread_num(); // Identificador del hilo
        for (int tarea = id_hilo * tareas_por_hilo; tarea < (id_hilo + 1) * tareas_por_hilo && tarea < total_tareas; tarea++) {
            WaitForSingleObject(semaforo, INFINITE); // Adquirir sem�foro
#pragma omp critical // Bloque cr�tico para evitar colisiones en la impresi�n
            {
                std::cout << "[Hilo " << id_hilo << "][Tiempo " << GetTickCount64() << "] "
                    << "Humano " << id_humano << ": procesando tarea " << tarea << std::endl;
            }
            Sleep(1000); // Simular trabajo (en milisegundos)
            ReleaseSemaphore(semaforo, 1, NULL); // Liberar sem�foro
        }
    }
}

// Funci�n que simula la interacci�n con el entorno
void manejar_entorno(int id_humano) {
    // Factores externos simulados
    std::vector<std::string> eventos = { "Caminar", "Cocinar", "Lavar ropa", "Planchar", "Entrenar", "Debo pagar factura", "No tengo dinero"};
    for (const auto& evento : eventos) {
#pragma omp critical // Bloque cr�tico para evitar colisiones en la impresi�n
        {
            std::cout << "[Tiempo " << GetTickCount64() << "] "
                << "Humano " << id_humano << ": Manejo del entorno: " << evento << std::endl;
        }
        Sleep(1000); // Simular tiempo de respuesta (en milisegundos)
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    double tiempo_inicio = MPI_Wtime(); // Inicia la medici�n del tiempo

    int rango, tamanio;
    MPI_Comm_rank(MPI_COMM_WORLD, &rango); // Identificador del proceso
    MPI_Comm_size(MPI_COMM_WORLD, &tamanio); // N�mero total de procesos

    // Inicializar sem�foro (m�ximo 2 procesos pueden entrar a la secci�n cr�tica)
    semaforo = CreateSemaphore(NULL, 2, 2, NULL);
    if (semaforo == NULL) {
        std::cerr << "Error al crear el sem�foro" << std::endl;
        MPI_Finalize();
        return 1;
    }

    if (rango == 0) {
        std::cout << "Inicio de la simulaci�n con " << tamanio << " humanos en paralelo." << std::endl;
    }

    // Cada nodo simula un humano
    std::cout << "[Tiempo " << GetTickCount64() << "] Nodo " << rango << ": Simulando humano." << std::endl;

    int tareas_totales = 12; // Total de tareas que se distribuyen entre los humanos (procesos)
    gestionar_tareas(rango, tareas_totales); // Cada humano realiza un n�mero equilibrado de tareas
    manejar_entorno(rango);

    MPI_Barrier(MPI_COMM_WORLD); // Sincronizaci�n global
    if (rango == 0) {
        std::cout << "Finalizacion de la simulacion." << std::endl;
    }

    CloseHandle(semaforo); // Liberar recursos del sem�foro

    double tiempo_fin = MPI_Wtime(); // Finaliza la medici�n del tiempo
    if (rango == 0) {
        std::cout << "Tiempo total de ejecuci�n: " << (tiempo_fin - tiempo_inicio) << " segundos." << std::endl;
    }

    MPI_Finalize();
    return 0;
}
