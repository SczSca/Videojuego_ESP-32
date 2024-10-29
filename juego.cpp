#include "juego.h"
#include "global_variables.h"

void Juego :: movimiento()
{

// Leer los valores del joystick
  int xValue = analogRead(PIN_X);
  int yValue = analogRead(PIN_Y);

  if(xValue == 4095 || xValue == 0)
  {
    xMoved = true;
    if(xValue > 1900){
      playerMovX = 1;
    }else{
      playerMovX = -1;
    }

  }
  
  if(yValue == 4095 || yValue == 0)
  {
    yMoved = true;
    if(yValue > 1900){
      playerMovY = -1;
    }else{
      playerMovY = 1;
    }
  }

  if(xMoved && (xValue > 1800 && xValue < 2000))
  {
    joystickXReleased = true;
    xMoved = false;
  }

  if(yMoved && (yValue > 1800 && yValue < 2000))
  {
    joystickYReleased = true;
    yMoved = false;
  }

  // Movimiento en el eje X
  if (joystickXReleased) {
    if (player[0] < 16 && player[0] > -1) {  // Mover a la derecha
      int futureMov = player[0] + playerMovX;
      if(futureMov > 15 || futureMov < 0)
      {
        return;
      }
      movePoint(player[0] + playerMovX, player[1]);
      joystickXReleased = false;  // Joystick no está en el centro
      playerMovX = 0;
    } 
  }

  // Movimiento en el eje Y
  if (joystickYReleased) {
    if (player[1] < 2 && player[1] > -1) {  // Mover hacia abajo
      int futureMov = player[1] + playerMovY;
      if(futureMov > 1 || futureMov < 0)
      {
        return;
      }
      movePoint(player[0], futureMov);
      joystickYReleased = false;  // Joystick no está en el centro
      playerMovY = 0;
    } 
  }

};


// Función para mover
void Juego :: movePoint(int newX, int newY) 
{
  // Borrar el punto anterior
  display.print(32,player[0],player[1]);

  // Actualizar las coordenadas
  player[0] = newX;
  player[1] = newY;

  // Dibujar el nuevo punto
  
  display.print(5,player[0],player[1]);

  // Mostrar en el monitor serial
  // Serial.print("X Pos: ");
  // Serial.print(player[0]);
  // Serial.print(" Y Pos: ");
  // Serial.println(player[1]);
}
  
bool Juego :: hasCrashed(){
  bool returnVal = false;

  if(
    (player[0] == obstacle1[0] && player[1] == obstacle1[1]) 
    || 
    (player[0] == obstacle2[0] && player[1] == obstacle2[1])
    )
  {
    returnVal = true;
    // Serial.print("choco");
    // my_soundtrack.death_sound();
  }

  return returnVal;
}

void Juego :: startPlayer(){
  display.print(5,player[0],player[1]);
}
