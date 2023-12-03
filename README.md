# tarea-2-SO
Trabajo en parejas Sistemas Operativos 2023-2

## Descripcion 
Este repositorio contiene los codigos fuente para el desarrollo de la tarea 2 de Sistemas Operativos, de la Universidad del Bio Bio

## Estructura del repositorio
Este repositorio contiene tres implicaciones para convertir imagenes a escala de grises:
- 'CodigoSecuencial.cpp': Es la version secuencial del procesamiento de imagenes.
- 'CodigoHilos.cpp': Es la version que utiliza 'std:thread' 🧵 para el procesamiento paralelo.
- 'CodigoOpenMP.cpp': Es la version que emplea OpenMP para el procesamiento paralelo.

Cada version tiene su propio 'Makefile' para facilitar su compilacion:
- 'Makefile.secuencial': Compila 'CodigoSecuencial.cpp'.
- 'Makefile.hilos': Compila 'CodigoHilos.cpp'.
- 'Makefile.open': Compila 'CodigoOpenMP.cpp'.

## Requisitos
- Alguna distribucion de Linux (para el desarrollo de este trabajo se utilizo Ubuntu 22.04.3).
- Compilador 'g++' compatible con c++11 o superior.
- OpenCV 4.x instalado y accesible mediante 'pkg-config'.
- Soporte para OpenMP (Usualmente lo incluye 'g++').

## Compilacion
Para compilar cada programa, navegue al directorio del repositorio y ejecute el siguiente comando en la terminal(Recuerde que para navegar en la terminal de Linux, se necesita de los comandos 'cd' y 'ls'):
```
sh de linux
make -f Makefile.secuencial #para compilar la version secuencial
make -f Makefile.hilos  #para compilar la version con hilos
make -f Makefile.open  #para compilar la version con OpenMP
```

## Ejecucion 
Despues de la compilacion, puede ejecutar cada programa con el sigueinte formato:
```
./CodigoSecuencial <ImagenEntrada> <ImagenSalida>
./CodigoHilos <ImagenEntrada> <ImagenSalida> <NumeroDeHilos>
./CodigoOpenMP <ImagenEntrada> <ImagenSalida> <NumeroDeHilos>
```
En donde:
- '<ImagenEntrada>' es el nombre del archivo de la imagen a color.
- '<ImagenSalida>' es el nombre del archivo de la imagen en escala de grises resultante.
- '<NumeroDeHilos>' es el número de hilos a utilizar (solo para las versiones paralelas).

## Limpieza
Para eliminar los archivos compilados, ejecute:
```
sh:
make -f Makefile.secuencial clean
make -f Makefile.hilos clean
make -f Makefile.open clean
```


## Autores
- Sebastian Gutierrez
- Cristobal Rivas
