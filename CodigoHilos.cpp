#include <opencv2/opencv.hpp>
#include <chrono>
#include <thread>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;
using namespace std::chrono;

//TODO: Comentar
void procesarSegmento(Mat& src, Mat& dest, int inicio, int fin) {
    for (int fila = inicio; fila < fin; ++fila) {
        for (int col = 0; col < src.cols; ++col) {
            Vec3b color = src.at<Vec3b>(fila, col);
            dest.at<uchar>(fila, col) = uchar(0.299 * color[2] + 0.587 * color[1] + 0.114 * color[0]);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cout << "Formato: " << argv[0] << " <ImagenEntrada> <ImagenSalida> <Hilos>" << endl;
        return 1;
    }

    Mat imagenOriginal = imread(argv[1], IMREAD_COLOR);
    if (imagenOriginal.empty()) {
        cerr << "Error al abrir la imagen." << endl;
        return 1;
    }

    int numHilos = stoi(argv[3]);
    vector<thread> hilos;
    Mat imagenGris(imagenOriginal.rows, imagenOriginal.cols, CV_8UC1);

    auto inicioCrono = high_resolution_clock::now();

    int altoSegmento = imagenOriginal.rows / numHilos;
    for (int i = 0; i < numHilos; ++i) {
        int inicio = i * altoSegmento;
        int fin = (i == numHilos - 1) ? imagenOriginal.rows : inicio + altoSegmento;
        hilos.emplace_back(procesarSegmento, ref(imagenOriginal), ref(imagenGris), inicio, fin);
    }

    for (auto& h : hilos) {
        h.join();
    }

    auto finCrono = high_resolution_clock::now();
    auto duracion = duration_cast<microseconds>(finCrono - inicioCrono);
    cout << "Duracion: " << duracion.count() << " microsegundos." << endl;

    if (!imwrite(argv[2], imagenGris)) {
        cerr << "No se pudo guardar la imagen." << endl;
        return 1;
    }

    return 0;
}
