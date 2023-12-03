#include <opencv2/opencv.hpp>
#include <omp.h>
#include <iostream>
#include <chrono>

using namespace std;
using namespace cv;
using namespace chrono;

// Función para aplicar un filtro de escala de grises a una imagen.
void aplicarFiltroGrises(const Mat& src, Mat& dst) {
    #pragma omp parallel for  // Directiva de OpenMP para paralelizar el bucle for.
    for (int y = 0; y < src.rows; y++) {  // Recorre las filas de la imagen.
        for (int x = 0; x < src.cols; x++) {  // Recorre las columnas de la imagen.
            Vec3b color = src.at<Vec3b>(y, x); // Obtiene el color del píxel en formato BGR.
            // Calcula el valor en escala de grises y lo asigna al píxel correspondiente.
            dst.at<uchar>(y, x) = uchar(0.299 * color[2] + 0.587 * color[1] + 0.114 * color[0]);
        }
    }
}

int main(int argc, char* argv[]) {
    // Verifica que se haya pasado el número correcto de argumentos.
    if (argc != 4) {
        cerr << "Modo de Uso: " << argv[0] << " [Imagen Origen] [Imagen Destino] [Hilos]" << endl;
        return -1;
    }
    // Cargar la imagen original
    Mat imagenOriginal = imread(argv[1], IMREAD_COLOR);
    if (imagenOriginal.empty()) { // comprueba si se cargo correctamente la imagen
        cerr << "No se pudo cargar la imagen: " << argv[1] << endl;
        return -1;
    }


    int hilos = stoi(argv[3]);  // Convierte el tercer argumento a entero para obtener el número de hilos.
    omp_set_num_threads(hilos); // Establece el número de hilos para OpenMP.

    // Crea una imagen en blanco para la salida en escala de grises.
    Mat imagenEnGris(imagenOriginal.size(), CV_8UC1);

    // Inicia el cronómetro.
    auto inicio = high_resolution_clock::now();

    // Aplica el filtro de escala de grises.
    aplicarFiltroGrises(imagenOriginal, imagenEnGris);

    // Detiene el cronómetro.
    auto fin = high_resolution_clock::now();

    // Calcula la duración de la operación.
    auto duracion = duration_cast<microseconds>(fin - inicio);
    cout << "Tiempo de procesamiento: " << duracion.count() << " microsegundos" << endl;

    // Guarda la imagen en escala de grises.
    if (!imwrite(argv[2], imagenEnGris)) {
        cerr << "Error al guardar la imagen." << endl;
        return -1;
    }

    return 0; // Finaliza el programa.
}