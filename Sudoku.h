/**
 * @file Sudoku.h
 * @brief Clase Board
 * @author Jesús Martín
 * @date 04/06/2019
*/
#include <SFML/Graphics.hpp>
#include <string>

class Board {
  sf::RectangleShape **cells; /**<Puntero de punteros para realizar cada celda del tablero*/
  int nrows; /**<Numero de filas del tablero*/
  int ncols; /**<Numero de columnas del tablero*/
  int size; /**<Tamaño de la ventana*/
  sf::RectangleShape *current; /**<Puntero que apunta a la celda correspondiente para visualizar el cursor*/

  //Posicion
  int pixelx=200; /**<Posicion x de la ventana (pixel)*/
  int pixely=250; /**<Posicion y de la ventana (pixel)*/
  int x; /**Posicion x del tablero*/
  int y; /**Posicion y del tablero*/
  //Fuente
  sf::Font font; /**<Fuente*/
  //para las fases
  int filas; /**<Filas que lee desde el fichero*/ 
  int columnas; /**<Columnas que lee desde el fichero*/
  int **valores; /**<Valores de cada celda*/
  //para el texto
  int fase=1; /**<Fases del Sudoku*/
  int casillas=0; /**<Numero de casillas en blanco de cada Fase*/
  int vidas=3; /**<Numeor de vidas*/
  //copia de la matriz valores
  int **valores_iniciales; /**<Valores iniciales de cada Fase*/
  //comprobar valor
  bool **validez; /**<Para cada posicion del tablero:True si el numero es valido y False si no lo es*/

  bool pause=false; /**<True si el juego está pausado y False si no lo está*/

public:
/**
 * @brief Constructor de la clase que crea el tablero
 * @param nrows Numero de filas del tablero
 * @param ncols Numero de columnas del tablero
 * @param size Tamaño de la ventana
 * @post Tablero 9x9 creado correctamente
*/
  Board(int nrows, int ncols, int size);
/**
 * @brief Dibujar el tablero en pantalla
 * @param windows La ventana del juego
 * @post Toda la ventana dibujada
*/
  void draw(sf::RenderWindow &windows);
/**
 * @brief Mover el current
 * @param posx Posicion x en la ventana(pixel)
 * @param posy Posicion y en la ventana(pixel)
 * @post Mover el current al pixel que corresponde
*/
  void action(int posx, int posy);
/**
 * @brief Liberar de memoria celdas y punteros
 * @post Memoria liberada
*/
  ~Board(void);
/**
 * @brief Mover el current a la derecha con el teclado
 * @post Mover el current al pixel que corresponde
*/
  void derecha();
/**
 * @brief Mover el current a la izquierda con el teclado
 * @post Mover el current al pixel que corresponde
*/
  void izquierda();
/**
 * @brief Mover el current arriba con el teclado
 * @post Mover el current al pixel que corresponde
*/
  void arriba();
/**
* @brief Mover el current abajo con el teclado
* @post Mover el current al pixel que corresponde
*/
  void abajo();
/**
 * @brief Cargar las fases del Sudoku
 * @post Fases cargadas
 */
  void cargarPhases();
/**
 * @brief Escribir un numero del 1 al 9 en los cuadros libres
 * @param posx Posicion en x el tablero
 * @param posy Posicion en y el tablero
 * @post Numero introducido correctamente
*/  
  void escribir(int posx,int posy);
/**
 * @brief Comprobar si el numero es valido o no
 * @param posx Posicion x en el tablero
 * @param posy Posicion y en el tablero
 * @retval True si el numero es valido
 * @retval False si el numero no es valido
 * @pre posx debe ser mayor o igual a 0 y menor o igual a 9
 * @pre posy debe ser mayor o igual a 0 y menor o igual a 9
*/
  bool comprobarValor(int posx,int posy);
};
