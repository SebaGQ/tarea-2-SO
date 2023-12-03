    #include <opencv2/opencv.hpp>
    #include <chrono>
    #include <iostream>

    using namespace cv;
    using namespace std;

    // Función para convertir una imagen a escala de grises.
    Mat convertirAGrises(const Mat& imagenOriginal) {
        Mat imagenGris(imagenOriginal.rows, imagenOriginal.cols, CV_8UC1);

        // Recorre cada pixel de la imagen original.
        for (int y = 0; y < imagenOriginal.rows; ++y) {
            for (int x = 0; x < imagenOriginal.cols; ++x) {
                Vec3b colorPixel = imagenOriginal.at<Vec3b>(y, x);
                // Convierte el pixel a escala de grises usando el método de luminosidad.
                uchar pixelGris = uchar(0.299 * colorPixel[2] + 0.587 * colorPixel[1] + 0.114 * colorPixel[0]);
                // Asigna el valor gris al pixel correspondiente en la imagen en grises.
                imagenGris.at<uchar>(y, x) = pixelGris;
            }
        }

        return imagenGris;
    }

    int main(int argc, char** argv) {
        // Verifica que se hayan pasado los argumentos
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

        // Guarda el tiempo de inicio, ejecuta la función y marca el guarda de finalizacion
        auto inicio = chrono::high_resolution_clock::now();

        Mat imagenGris = convertirAGrises(imagen);

        auto fin = chrono::high_resolution_clock::now();

        // Calcula la duración y la muestra en pantalla
        auto duracion = chrono::duration_cast<chrono::microseconds>(fin - inicio).count();
        cout << "Tiempo de procesamiento: " << duracion << " microsegundos." << endl;

        if (!imwrite(archivoSalida, imagenGris)) {
            cerr << "No se pudo guardar la imagen: " << archivoSalida << endl;
            return 1;
        }

        return 0;
    }
