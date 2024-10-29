#ifndef JUEGO_H
#define JUEGO_H

// #include "videojuego.h"
// #include "Variables.h"
#include "lcd_handler.h"


// extern uint8_t VERT_PIN  = 32;
// extern VERT_PIN 32;
// extern HORZ_PIN 35
// extern SEL_PIN 34

extern LCDHandler display;

class Juego{
    
    public:
        void movimiento( void );
        bool hasCrashed( void );
        void startPlayer( void );

    private:
        int lastXValue = 2900;  // Valor inicial centrado
        int lastYValue = 2900;
        int centerVal = 2900;

        int playerMovX, playerMovY = 0;
        // Umbral de sensibilidad para detectar movimientos
        const int threshold = 800;
        bool xMoved = false;
        bool yMoved = false;

        // Variable global player para posicion de jugador
        // Columna (0 a 15)
        // Fila (0 a 1)
        // Variables para detectar si el joystick ya ha vuelto al centro
        bool joystickXReleased = true;
        bool joystickYReleased = true;
        void movePoint( int,  int );


};
#endif