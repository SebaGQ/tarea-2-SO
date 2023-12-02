#include <opencv2/opencv.hpp>
#include <omp.h>
#include <iostream>
#include <chrono>

using namespace std;
using namespace cv;
using namespace chrono;

//TODO: Comentar
void aplicarFiltroGrises(const Mat& src, Mat& dst) {
    #pragma omp parallel for
    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            Vec3b color = src.at<Vec3b>(y, x);
            dst.at<uchar>(y, x) = uchar(0.299 * color[2] + 0.587 * color[1] + 0.114 * color[0]);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Modo de Uso: " << argv[0] << " [Imagen Origen] [Imagen Destino] [Hilos]" << endl;
        return -1;
    }

    Mat imagenOriginal = imread(argv[1], IMREAD_COLOR);
    if (imagenOriginal.empty()) {
        cerr << "No se pudo cargar la imagen: " << argv[1] << endl;
        return -1;
    }

    int hilos = stoi(argv[3]);
    omp_set_num_threads(hilos);

    Mat imagenEnGris(imagenOriginal.size(), CV_8UC1);

    auto inicio = high_resolution_clock::now();

    aplicarFiltroGrises(imagenOriginal, imagenEnGris);

    auto fin = high_resolution_clock::now();

    auto duracion = duration_cast<microseconds>(fin - inicio);
    cout << "Tiempo de procesamiento: " << duracion.count() << " microsegundos" << endl;

    if (!imwrite(argv[2], imagenEnGris)) {
        cerr << "Error al guardar la imagen." << endl;
        return -1;
    }

    return 0;
}