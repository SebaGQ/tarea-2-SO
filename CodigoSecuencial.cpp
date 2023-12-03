#include <opencv2/opencv.hpp>
#include <chrono>
#include <iostream>

using namespace cv;
using namespace std;

//TODO: Comentar
Mat convertirAGrises(const Mat& imagenOriginal) {
    Mat imagenGris(imagenOriginal.rows, imagenOriginal.cols, CV_8UC1);

    for (int y = 0; y < imagenOriginal.rows; ++y) {
        for (int x = 0; x < imagenOriginal.cols; ++x) {
            Vec3b colorPixel = imagenOriginal.at<Vec3b>(y, x);
            uchar pixelGris = uchar(0.299 * colorPixel[2] + 0.587 * colorPixel[1] + 0.114 * colorPixel[0]);
            imagenGris.at<uchar>(y, x) = pixelGris;
        }
    }

    return imagenGris;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Modo de uso: " << argv[0] << " [ImagenEntrada] [ImagenSalida]" << endl;
        return 1;
    }

    string archivoEntrada = argv[1];
    string archivoSalida = argv[2];

    Mat imagen = imread(archivoEntrada, IMREAD_COLOR);
    if (imagen.empty()) {
        cerr << "No se pudo cargar la imagen: " << archivoEntrada << endl;
        return 1;
    }

    auto inicio = chrono::high_resolution_clock::now();

    Mat imagenGris = convertirAGrises(imagen);

    auto fin = chrono::high_resolution_clock::now();

    auto duracion = chrono::duration_cast<chrono::microseconds>(fin - inicio).count();
    cout << "Tiempo de procesamiento: " << duracion << " microsegundos." << endl;

    if (!imwrite(archivoSalida, imagenGris)) {
        cerr << "No se pudo guardar la imagen: " << archivoSalida << endl;
        return 1;
    }

    return 0;
}
