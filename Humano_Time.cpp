/*#include <mpi.h>
#include <omp.h>
#include <iostream>
#include <vector>
#include <windows.h> // Para sem�foros y funciones espec�ficas de Windows

// Sem�foro para sincronizaci�n
HANDLE semaforo;

// Funci�n que simula tareas paralelas del humano
void gestionar_tareas(int id_humano) {
#pragma omp parallel num_threads(4) // Simula 4 pensamientos/procesos paralelos
    {
        int id_hilo = omp_get_thread_num(); // Identificador del hilo
        for (int tarea = 0; tarea < 3; tarea++) { // Cada proceso realiza 3 iteraciones de tareas
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
    std::vector<std::string> eventos = { "Caminar", "Cocinar", "Lavar ropa", "Planchar", "Entrenar" };
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

    double tiempo_inicio, tiempo_fin;
    tiempo_inicio = MPI_Wtime(); // Inicio del cron�metro

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
    gestionar_tareas(rango);
    manejar_entorno(rango);

    MPI_Barrier(MPI_COMM_WORLD); // Sincronizaci�n global

    if (rango == 0) {
        std::cout << "Finalizaci�n de la simulaci�n." << std::endl;
    }

    tiempo_fin = MPI_Wtime(); // Fin del cron�metro

    if (rango == 0) {
        std::cout << "Tiempo total de ejecuci�n: " << (tiempo_fin - tiempo_inicio) << " segundos." << std::endl;
    }

    CloseHandle(semaforo); // Liberar recursos del sem�foro
    MPI_Finalize();
    return 0;
}
*/