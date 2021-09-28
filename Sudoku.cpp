/**
 * @file Sudoku.cpp
 * @brief Juego Sudoku
 * @author Jesús Martín
 * @date 04/06/2019
*/
#include "Sudoku.h"
#include <fstream>
#include <iostream>

using namespace std;

//static sf::Color cell_bg(203, 239, 241);

static sf::Color cell_bg(0, 0, 0);

Board::Board(int nrows, int ncols, int size) {

  const int tam = nrows * ncols;
  const int thickness = 2.0;
  int total = 0;
  this->nrows = nrows;
  this->ncols = ncols;
  this->size = size;

  this->current = nullptr;
  cells = new sf::RectangleShape *[tam];

  for (int x = 0; x < ncols; x++) {
    for (int y = 0; y < nrows; y++) {
      cells[total] = new sf::RectangleShape(
        sf::Vector2f(size - thickness, size - thickness));
      cells[total]->setPosition(x * size, (y+1) * size);
      cells[total]->setFillColor(cell_bg);
      cells[total]->setOutlineColor(sf::Color::White);
      cells[total]->setOutlineThickness(thickness);
      total += 1;
    }
  }
  action(pixelx,pixely);
  cargarPhases();
}

void Board::draw(sf::RenderWindow &windows) {
  int total = nrows * ncols;

  for (int i = 0; i < total; i++) {
    windows.draw(*cells[i]);
  }

  //Fuente
  
  if(!font.loadFromFile("./fonts/GoodDog.otf")){
    string msg = "Fuente no encontrada";
    throw string(msg);
  }

  //Phase
  string Fase = "Phase: "+ to_string(fase);
  sf::Text Phase(Fase, font);
  Phase.setPosition(0,-5);
  Phase.setCharacterSize(40);
  windows.draw(Phase);

  //Pending
  string Casillas = "Pending: " + to_string(casillas);
  sf::Text Pending(Casillas, font);
  Pending.setPosition(150,-5);
  Pending.setCharacterSize(40);
  windows.draw(Pending);
  
  //Lifes
  string life="Lifes: "+ to_string(vidas);
  sf::Text Lifes(life, font);
  Lifes.setPosition(350,-5);
  Lifes.setCharacterSize(40);
  windows.draw(Lifes);

  //Rectangulos para separar el sudoku en 9

  sf::RectangleShape rectangle1(sf::Vector2f(450, 5));
  sf::RectangleShape rectangle2(sf::Vector2f(450, 5));
  sf::RectangleShape rectangle3(sf::Vector2f(450, 5));
  sf::RectangleShape rectangle4(sf::Vector2f(450, 5));
  rectangle1.setFillColor(sf::Color(255,255,255));
  rectangle2.setFillColor(sf::Color(255,255,255));
  rectangle3.setFillColor(sf::Color(255,255,255));
  rectangle4.setFillColor(sf::Color(255,255,255));
  rectangle1.rotate(90);
  rectangle1.move(150,50);
  rectangle2.rotate(90);
  rectangle2.move(300,50);
  rectangle3.move(0,198);
  rectangle4.move(0,348);
  windows.draw(rectangle1);
  windows.draw(rectangle2);
  windows.draw(rectangle3);
  windows.draw(rectangle4);

  escribir(x,y);

  //Mostrar las fases

  for(int i=0; i<filas; i++)
  {
    for(int j=0; j<columnas; j++)
    {
      if(valores[i][j]>0)
      {
        sf::Text numeros(to_string(valores[i][j]), font);
        if(validez[i][j]==true){
        if(valores[i][j]==valores_iniciales[i][j]){
          numeros.setFillColor(sf::Color::White);
        }else{
          numeros.setFillColor(sf::Color(192,192,192));
        }
        numeros.setPosition(i * size + 15 , (j+1) * size - 11);
        numeros.setCharacterSize(50);
        windows.draw(numeros);
        }else{
	        pause=true;
          numeros.setFillColor(sf::Color::Red);
          numeros.setPosition(i * size + 15 , (j+1) * size - 11);
          numeros.setCharacterSize(50);
          windows.draw(numeros);
	        if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)){
	          valores[x][y]=0;
		        casillas++;
		        vidas--;
		        pause=false;
	        }
        }
        if(valores[x][y]!=valores_iniciales[x][y] && validez[x][y]){
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)){
        	  valores[x][y]=0;
        	  casillas++;
    	    }
        }
      }
    }
  }

  //Recargar fases

  if(casillas==0 && fase<4 && !pause){
    sf::sleep(sf::seconds(1));
    fase++;
    cargarPhases();
  }

  //Fin de juego

  if(vidas<=0){
    sf::Text FinDeJuego("Has Perdido\n'Q' para salir",font);
    FinDeJuego.setCharacterSize(90);
    FinDeJuego.setPosition(65,140);
    sf::RectangleShape FindeJuego(sf::Vector2f(450,500));
    FindeJuego.setFillColor(sf::Color::Black);
    FinDeJuego.setFillColor(sf::Color::White);
    windows.draw(FindeJuego);
    windows.draw(FinDeJuego);
  }

  if(fase==4 && casillas<=0 && !pause){
    sf::Text FinDeJuego("Has Ganado\n'Q' para salir",font);
    FinDeJuego.setCharacterSize(90);
    FinDeJuego.setPosition(65,140);
    sf::RectangleShape FindeJuego(sf::Vector2f(450,500));
    FindeJuego.setFillColor(sf::Color::Black);
    FinDeJuego.setFillColor(sf::Color::White);
    windows.draw(FindeJuego);
    windows.draw(FinDeJuego);
  }
}

void Board::action(int posx, int posy) {

  if(posy>=50 && !pause){

    pixelx=posx;
    pixely=posy;

    x = (posx / this->size);
 	  y = (posy / this->size)-1;
    
    if (current != nullptr){
      current->setFillColor(cell_bg);
    }
    current = cells[x * nrows + y];
    current->setFillColor(sf::Color(128,128,128));
  }
}

void Board::derecha(){
  if(!pause){
    pixelx+=50;
		  if(pixelx>=450){
		  pixelx=0;
	    }
	    action(pixelx,pixely);
  }
}
void  Board::izquierda(){
  if(!pause){
    pixelx-=50;
		if(pixelx<0){
		  pixelx=400;
		}
	  action(pixelx,pixely);
  }
}

void Board::arriba(){
  if(!pause){
    pixely-=50;
		  if(pixely<50){
		  pixely=450;		
		  }
		  action(pixelx,pixely);
  }
}

void Board::abajo(){
  if(!pause){
    pixely+=50;
		if(pixely>=500){
		  pixely=50;		
		}
	  action(pixelx,pixely);
	}
}

Board::~Board(void) {
  int total = nrows * ncols;

  if (cells == nullptr) {
    return;
  }

  for (int i = 0; i < total; i++) {
    delete cells[i];
  }

  delete[] cells;
  cells = nullptr;

  //Liberar memoria de valores

  for(int i=0;i<filas;++i){
    delete[] valores[i];
  }
  delete[] valores;

  //Liberar memoria de valores_iniciales

  for(int i=0;i<filas;++i){
    delete[] valores_iniciales[i];
  }
  delete[] valores_iniciales;

  //Liberar memoria de validez

  for(int i=0;i<filas;++i){
    delete[] validez[i];
  }
  delete[] validez;

}

void Board::cargarPhases()
{ 
  string name = "phases/phase" +to_string(fase) + ".txt";
  ifstream file;
  file.open(name);

  if (file.fail())
  {
      string msg = "Error al abrir el fichero '" +name +"'";
      cerr <<msg <<endl;
      throw msg;
  }

  file >> filas;
  file >> columnas;
  
  valores = new int*[filas];
  for(int i=0;i<filas;++i){
    valores[i]=new int [columnas];
  }

  valores_iniciales = new int*[filas];
  for(int i=0;i<filas;++i){
    valores_iniciales[i]=new int [columnas];
  }

  validez = new bool*[filas];
  for(int i=0;i<filas;++i){
    validez[i]=new bool [columnas];
  }

  for(int i=0; i<filas; i++)
  {
    for(int j=0; j<columnas; j++)
    {
      file >> valores[j][i];

      validez[j][i]=true;

      valores_iniciales[j][i]=valores[j][i];

      if(valores[j][i]==0){
        casillas++;
      }
          
    }
  }
}

void Board::escribir(int posx,int posy){
  
  if(valores[posx][posy]==0 && pause==false){
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
      valores[posx][posy]=1;
      casillas--;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
      valores[posx][posy]=2;
      casillas--;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
      valores[posx][posy]=3;
      casillas--;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)){
      valores[posx][posy]=4;
      casillas--;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)){
      valores[posx][posy]=5;
      casillas--;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)){
      valores[posx][posy]=6;
      casillas--;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)){
      valores[posx][y]=7;
      casillas--;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)){
      valores[posx][posy]=8;
      casillas--;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)){
      valores[posx][posy]=9;
      casillas--;
    }
    
    validez[posx][posy]=comprobarValor(posx,posy);

  }
}

bool Board::comprobarValor(int posx,int posy){
  
  int contador=0;

  //Comprobacion en la fila

  for(int i=0;i<columnas;i++){
    if(valores[i][posy]==valores[posx][posy] && i!=posx && valores[posx][posy]!=0){
      contador++;
    }
  }

  //Comprobacion en la columna

  for(int j=0;j<filas;j++){
    if(valores[posx][j]==valores[posx][posy] && j!=y && valores[posx][posy]!=0){
      contador++;
    }
  }

  //Comprobacion en el cuadrado

  int cuadradox=(posx/3)*3,cuadradoy=(posy/3)*3;

  for(;cuadradox<=((posx/3)*3)+2;cuadradox++){
    if(valores[posx][posy]==valores[cuadradox][cuadradoy] && valores[posx][posy]!=0 && posx!=cuadradox && posy!=cuadradoy){
      contador++;
    }
  }
  cuadradox--;

  cuadradoy++;
  if(valores[posx][posy]==valores[cuadradox][cuadradoy] && valores[posx][posy]!=0 && posx!=cuadradox && posy!=cuadradoy){
      contador++;
  }
  cuadradoy++;
  for(;cuadradox>=(x/3)*3;cuadradox--){
    if(valores[posx][posy]==valores[cuadradox][cuadradoy] && valores[posx][posy]!=0 && posx!=cuadradox && posy!=cuadradoy){
      contador++;
    }
  }
  cuadradox++;
  cuadradoy--;
  if(valores[posx][posy]==valores[cuadradox][cuadradoy] && valores[posx][posy]!=0 && posx!=cuadradox && posy!=cuadradoy){
      contador++;
  }
  cuadradox++;
  if(valores[posx][posy]==valores[cuadradox][cuadradoy] && valores[posx][posy]!=0 && posx!=cuadradox && posy!=cuadradoy){
      contador++;
  }

  if(contador==0){
    return true;
  }else{
    return false;
  }
}
