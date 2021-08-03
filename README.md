## Proyecto final de Estructuras de Datos avanzados

### Integrantes

- Alessia Yi
- Maor Roizman
- Macarena Oyague

### Implementación

Se ha implementado un *RTree binario* para resolver las consultas solicitadas en el enunciado *Instrucciones.pdf*. Está compuesto por nodos de tipo *RNode*, que tendrán un *MBR* que corresponda a la región que abarcan sus hijos. En el caso de las hojas, se tendrá además un puntero a *Neighborhood*, que tendrá a su vez las coordenadas de tipo *Point* que delimitan la región poligonal del vecindario. Se mantienen listas además para llevar la cuenta de los viajes, de tipo *Trip* en función al punto de recojo -pickup- y al de destino -dropoff-.

### Documentos

Se adjunta *Presentacion.pdf*, que representa la presentación de referencia sobre el proyecto. Este tiene como finalidad tanto explicar los procedimientos del algoritmo implementado como dar ejemplos de la propuesta del *RTree binario*. Además, ejemplifica cómo se pueden testear los resultados.

### Compilación

Para ejecutar el codigo entregado se requieren los siguientes pasos:

Clonar el repositorio a local
```
git clone https://github.com/mrg2000/final-project-eda.git
```
Luego entrar a la carpeta ```final-project-eda```
```
cd final-project-eda
```
Finalemnete ejectuar el archivo main que se encuentra dentro de la carpeta ```scr```
```
g++ -std=c++11 src/main.cpp
./a.out
```