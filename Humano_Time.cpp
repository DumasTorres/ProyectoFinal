/*#include <mpi.h>
#include <omp.h>
#include <iostream>
#include <vector>
#include <windows.h> // Para semáforos y funciones específicas de Windows

// Semáforo para sincronización
HANDLE semaforo;

// Función que simula tareas paralelas del humano
void gestionar_tareas(int id_humano) {
#pragma omp parallel num_threads(4) // Simula 4 pensamientos/procesos paralelos
    {
        int id_hilo = omp_get_thread_num(); // Identificador del hilo
        for (int tarea = 0; tarea < 3; tarea++) { // Cada proceso realiza 3 iteraciones de tareas
            WaitForSingleObject(semaforo, INFINITE); // Adquirir semáforo
#pragma omp critical // Bloque crítico para evitar colisiones en la impresión
            {
                std::cout << "[Hilo " << id_hilo << "][Tiempo " << GetTickCount64() << "] "
                    << "Humano " << id_humano << ": procesando tarea " << tarea << std::endl;
            }
            Sleep(1000); // Simular trabajo (en milisegundos)
            ReleaseSemaphore(semaforo, 1, NULL); // Liberar semáforo
        }
    }
}

// Función que simula la interacción con el entorno
void manejar_entorno(int id_humano) {
    // Factores externos simulados
    std::vector<std::string> eventos = { "Caminar", "Cocinar", "Lavar ropa", "Planchar", "Entrenar" };
    for (const auto& evento : eventos) {
#pragma omp critical // Bloque crítico para evitar colisiones en la impresión
        {
            std::cout << "[Tiempo " << GetTickCount64() << "] "
                << "Humano " << id_humano << ": Manejo del entorno: " << evento << std::endl;
        }
        Sleep(1000); // Simular tiempo de respuesta (en milisegundos)
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    double tiempo_inicio, tiempo_fin;
    tiempo_inicio = MPI_Wtime(); // Inicio del cronómetro

    int rango, tamanio;
    MPI_Comm_rank(MPI_COMM_WORLD, &rango); // Identificador del proceso
    MPI_Comm_size(MPI_COMM_WORLD, &tamanio); // Número total de procesos

    // Inicializar semáforo (máximo 2 procesos pueden entrar a la sección crítica)
    semaforo = CreateSemaphore(NULL, 2, 2, NULL);
    if (semaforo == NULL) {
        std::cerr << "Error al crear el semáforo" << std::endl;
        MPI_Finalize();
        return 1;
    }

    if (rango == 0) {
        std::cout << "Inicio de la simulación con " << tamanio << " humanos en paralelo." << std::endl;
    }

    // Cada nodo simula un humano
    std::cout << "[Tiempo " << GetTickCount64() << "] Nodo " << rango << ": Simulando humano." << std::endl;
    gestionar_tareas(rango);
    manejar_entorno(rango);

    MPI_Barrier(MPI_COMM_WORLD); // Sincronización global

    if (rango == 0) {
        std::cout << "Finalización de la simulación." << std::endl;
    }

    tiempo_fin = MPI_Wtime(); // Fin del cronómetro

    if (rango == 0) {
        std::cout << "Tiempo total de ejecución: " << (tiempo_fin - tiempo_inicio) << " segundos." << std::endl;
    }

    CloseHandle(semaforo); // Liberar recursos del semáforo
    MPI_Finalize();
    return 0;
}
*/