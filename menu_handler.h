#ifndef MENU_HANDLER_H
#define MENU_HANDLER_H

#include "lcd_handler.h"
#include "song.h"

// Instancia del controlador de LCD para la visualización
extern LCDHandler display;
extern soundtracks myOST;

/**
 * @class MenuHandler
 * @brief Clase para manejar el menú del juego.
 *
 * Esta clase se encarga de la navegación y la gestión de entradas del menú
 * del juego, incluyendo la detección de presiones de botones y el control
 * del estado del juego.
 */
class MenuHandler
{
private:
  // unsigned long gameStartTime = 0;         ///< Tiempo de inicio del juego.
  unsigned long lastButtonPress = 0;       ///< Marca de tiempo del último botón presionado.
  const unsigned long debounceDelay = 200; ///< Retardo para la rebote del botón.
  bool buttonPressed = false;              ///< Indica si un botón ha sido presionado.
  bool isResumed = false;

public:
  /**
   * @brief Configura el menú y su estado inicial.
   *
   * Este método debe ser llamado una vez para inicializar
   * el menú y establecer cualquier configuración necesaria.
   */
  void setup();

  /**
   * @brief Verifica si un botón ha sido presionado.
   * @return true Si un botón ha sido presionado.
   * @return false Si no se ha presionado ningún botón.
   */
  bool isButtonPressed();

  /**
   * @brief Maneja la navegación del menú.
   * @param startGameFlag Determina si el juego se ha iniciado.
   *
   * Este método se encarga de actualizar el estado del menú
   * basado en el estado actual de sistema.
   */
  void handleMenuNavigation();
};

#endif