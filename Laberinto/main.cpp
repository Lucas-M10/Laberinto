#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <random>
#include <chrono>

//iostream es una libreria estandar de c++ sirve para leer datos en pantalla con cout o leer datos del usuario cin

using namespace std;

//esta linea nos permite usar todo lo que hay dentro del espacio de memoria std sin que estar teniendo que hacer std::cout<<"hola"<<endl
//que es un espacio de memoria
/*
- Muro              ->  0
- camino vacio      ->  1
- camino recorrido  ->  2
- entrada           ->  3
- salida            ->  4
*/

//Se encarga de inicializar la semilla
random_device rd;
mt19937 g(rd());

//Funcion que se encarga de crear el camino vacio
void algoritmo_DFS (vector<vector<int>> &matriz, int actual_fila, int actual_columna){

    //Saco los limites de la matriz
    int max_filas = matriz.size();
    int max_columnas = matriz[0].size();

    //en la posicion actual hago que sea un camino
    matriz[actual_fila][actual_columna]=1;

    //vector de tipo pair que nos guardara los movimientos que podemos hacer
    vector <pair<int, int>> direcciones = {{2, 0}, {-2, 0},{0, -2},{0, 2}};

    //se encarga de mezclar las direcciones
    shuffle(direcciones.begin(), direcciones.end(), g);

    //Se encarga de iterar en las posibilidades de movimientos
    for (int i=0; i<4; i++){

        //inicializamos las nuevas posiciones.
        int nueva_fila= actual_fila + direcciones[i].first;
        int nueva_columna = actual_columna + direcciones[i].second;

        //Verificamos si esta dentro del tablero y si es una pared.
        if (nueva_fila>=0 && nueva_fila<max_filas && nueva_columna>=0 && nueva_columna<max_columnas &&
            matriz[nueva_fila][nueva_columna]==0){
                //Rompemos la celda que se encuentra en el medio y llamamos a la recursividad
                matriz[actual_fila + direcciones[i].first/2][actual_columna + direcciones[i].second/2]=1;
                algoritmo_DFS(matriz, nueva_fila, nueva_columna);
            }
    }
}
//Funcion que genera el tablero
vector<vector<int>> generar_laberinto (int &filas, int &columnas){

    //Verificamos si es un impar y sino forzamos a que sea
    if (filas%2==0){
        filas++;
    }
    if (columnas%2==0){
        columnas++;
    }

    //Creamos una matriz de fila x columnas que se inicialice todo con muros
    vector<vector<int>> matriz (filas, vector<int>(columnas, 0));

    //Llamamos a la funcion para que genere el camino
    algoritmo_DFS(matriz, 1, 1);

    //posicion de la entrada y salida
    matriz[1][0]= 3;
    matriz[filas-2][columnas-1]= 4;

    return matriz;
}

//Esta funcion se encarga de resolver el laberinto
void resolver_laberintoBFS (vector <vector<int>> &matriz, int pos_fila, int pos_columna){

    //Sacamos las dimensiones de la matriz
    int max_filas = matriz.size();
    int max_columnas = matriz[0].size();

    //creamos un vector que se utilizara para los movimientos
    vector <pair <int, int>> mov = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};

    //creamos una cola donde guardara las posiciones a procesar
    queue<pair<int, int>> cola;

    //Matriz que nos dira si la posicion fue visitado
    vector<vector<bool>> visitado (max_filas, vector<bool>(max_columnas, false));

    //Matriz que nos dice de donde se llego a la celda
    vector<vector<pair<int, int>>> recorrido (max_filas, vector<pair<int, int>>(max_columnas, {-1, -1}));


    visitado [pos_fila][pos_columna]= true;
    cola.push({pos_fila, pos_columna});

    pair<int, int> salida = {max_filas-2, max_columnas-2};

    //loop principal que se encarga de procesar los elementos de la cola
    while (!cola.empty()){


        pair<int, int> actual = cola.front();
        cola.pop();

        //Verificamos si se llego a la salida
        if (actual.first == salida.first && actual.second == salida.second){

            while (actual.first != -1 && actual.second != -1){
                matriz[actual.first][actual.second]= 2;
                actual = recorrido[actual.first][actual.second];
            }
        }

        //Vsisitamos los nodos adyacentes o vecinos
        for (int i=0; i<4; i++){

            int nueva_fila = actual.first + mov[i].first;
            int nueva_columna = actual.second + mov[i].second;

            //Validamos si la posicion es valida, si todavia no se visito y si es un camino vacio
            if (nueva_fila>0 && nueva_fila<max_filas && nueva_columna>0 && nueva_columna<max_columnas &&
                visitado[nueva_fila][nueva_columna]==false && matriz[nueva_fila][nueva_columna]==1){
                    visitado [nueva_fila][nueva_columna] = true;
                    recorrido[nueva_fila][nueva_columna] = {actual.first, actual.second};
                    cola.push({nueva_fila, nueva_columna});
                }
        }
    }
}
/*
- Muro              ->  0
- camino vacio      ->  1
- camino recorrido  ->  2
- entrada           ->  3
- salida            ->  4
*/
//Fucnion Imprimir matriz
void imprimir_matriz (vector<vector<int>> matriz){

    int max_filas = matriz.size();
    int max_columnas = matriz[0].size();

    for (int i=0; i< max_filas; i++){
        for (int j=0; j<max_columnas; j++){

            if (matriz[i][j]==0){
                cout<<" # ";
            }
            else if (matriz[i][j]==1){
                cout<<"   ";
            }
            else if (matriz[i][j]==2){
                cout<<" . ";
            }
            else if (matriz[i][j]==3){
                cout<<" E ";
            }
            else{
                cout<<" S ";
            }
        }
        cout<<endl;
    }
}

int main()
{
    //Se ingresa los datos de las filas y columnas
    //y se realiza las verificaciones de un fila y columna minima.
    int filas, columnas;
    cout<<"Ingrese la cantidad de filas: ";
    cin>>filas;
    if (filas<6){
        filas=11;
    }
    cout<<endl;
    cout<<"Ingrese la cantidad de columnas: ";
    cin>>columnas;
    if (columnas<6){
        columnas=11;
    }
    cout<<endl;

    //Creo la matriz
    vector<vector<int>> matriz;

    //genero la matriz y tambien mido el tiempo de ejecucion
    auto inicio_1 = chrono::high_resolution_clock :: now ();
    matriz = generar_laberinto(filas, columnas);
    auto fin_1 = chrono::high_resolution_clock :: now ();
    auto tiempo_1 = chrono::duration_cast<chrono::microseconds> (fin_1- inicio_1);

    imprimir_matriz(matriz);
    cout<<endl;

    //Se resuelve el laberinto y se mide el tiempo de ejecucion
    auto inicio = chrono::high_resolution_clock :: now ();
    resolver_laberintoBFS(matriz, 1, 1);
    auto fin = chrono::high_resolution_clock :: now ();
    auto tiempo = chrono::duration_cast<chrono::microseconds> (fin- inicio);

    imprimir_matriz(matriz);
    cout<<endl;
    cout<<"El tiempo en generar el laberinto: "<< tiempo_1.count()<< " ms"<<endl;
    cout<<"El tiempo de resolucion por bfs: "<< tiempo.count() <<" ms"<<endl;
    return 0;
}
