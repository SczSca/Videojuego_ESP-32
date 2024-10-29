// #include <Arduino.h>
#include "menu_handler.h"

extern MenuHandler menuHandler;

// Índice de la letra que el jugador está seleccionando
int currentLetterIndex = 0;

/**
 * @brief Configura el menú inicial del juego.
 *
 * Este método inicializa el puerto serie, configura la pantalla LCD,
 * y el pin del botón. También muestra la pantalla de bienvenida
 * y realiza la inicialización de la tarjeta microSD.
 */
void MenuHandler::setup()
{
  Serial.begin(115200);
  display.lcd_init_display();
  display.createCharacters();
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  pinMode(PIN_X, INPUT_PULLUP);
  pinMode(PIN_Y, INPUT_PULLUP);
  display.showWelcomeScreen();
  microSD.init();
}

/**
 * @brief Verifica si el botón ha sido presionado.
 * @return true Si el botón ha sido presionado.
 * @return false Si el botón no ha sido presionado.
 *
 * Este método incluye un retardo de rebote para evitar múltiples
 * lecturas de un solo evento de presión de botón.
 */
bool MenuHandler::isButtonPressed()
{
  if (digitalRead(PIN_BUTTON) == LOW)
  {
    // Serial.println("Button was pressed");
    unsigned long currentMillis = millis();
    if (currentMillis - lastButtonPress > debounceDelay)
    {
      myOST.move();
      // Serial.println("Button works");
      lastButtonPress = currentMillis;
      return true;
    }
  }
  return false;
}

/**
 * @brief Maneja la transición desde la pantalla de bienvenida al menú principal.
 * @param buttonPressed Indica si el botón ha sido presionado.
 *
 * Cambia el estado actual a MAIN_MENU si el botón es presionado.
 */
void welcomeHandler(bool buttonPressed)
{
  if (buttonPressed)
  {
    currentState = MAIN_MENU;
    // Serial.println("Welcome btn pressed");
    display.showMainMenu(mainMenuIndex);
    // Serial.println("printin in lcd menuItems done");
  }
}

/**
 * @brief Maneja la navegación en el menú principal.
 * @param yValue Valor analógico del joystick en el eje Y.
 * @param joystickMoved Indica si el joystick ha sido movido.
 * @param buttonPressed Indica si el botón ha sido presionado.
 *
 * Actualiza el índice del menú según el movimiento del joystick y
 * verifica si el botón ha sido presionado para entrar en diferentes
 * estados del juego.
 */
void mainMenuHandler(int yValue, bool joystickMoved, bool buttonPressed)
{
  // int xValue = analogRead(PIN_X);
  // Serial.print("Y value: ");
  // Serial.println(yValue);

  // Serial.print("X value: ");
  // Serial.println(xValue);
  if (DECREMENTO(yValue) && !joystickMoved)
  {
    // Función para sonido
    myOST.move();
    mainMenuIndex++;
    if (mainMenuIndex >= mainMenuItems)
      mainMenuIndex = 0;
    joystickMoved = true;
    display.showMainMenu(mainMenuIndex);
  }

  if (INCREMENTO(yValue) && !joystickMoved)
  {
    // Función para sonido
    myOST.move();
    mainMenuIndex--;
    if (mainMenuIndex < 0)
      mainMenuIndex = mainMenuItems - 1;
    joystickMoved = true;
    display.showMainMenu(mainMenuIndex);
  }

  if (!INCREMENTO(yValue) && !DECREMENTO(yValue))
  {
    joystickMoved = false;
  }

  if (buttonPressed)
  {
    if (mainMenuIndex == 0)
    {
      currentState = IN_GAME;
      display.lcd_clear_display();
      // gameStartTime = millis();
    }
    else if (mainMenuIndex == 1)
    {
      currentState = HIGH_SCORES;
      display.showHighScores();
    }
    else if (mainMenuIndex == 2)
    {
      display.lcd_clear_display();
      mainMenuIndex = 0;
      currentState = WELCOME;
      display.showWelcomeScreen();
    }
  }
}

/**
 * @brief Maneja la navegación en la pantalla de puntajes altos.
 * @param buttonPressed Indica si el botón ha sido presionado.
 *
 * Regresa al menú principal si el botón es presionado.
 */
void highScoresHandler(bool buttonPressed)
{
  if (buttonPressed)
  {
    currentState = MAIN_MENU;
    display.showMainMenu(mainMenuIndex);
  }
}

/**
 * @brief Maneja la lógica del juego en curso.
 * @param buttonPressed Indica si el botón ha sido presionado.
 *
 * Cambia al estado de IN_GAME_MENU si se presiona el botón,
 * y controla el tiempo de juego para transitar a ENTER_NAME.
 */
void inGameHandler(bool buttonPressed)
{
  // if (buttonPressed)
  // {
  //   currentState = IN_GAME_MENU;
  //   inGameMenuIndex = 0;
  //   display.showInGameMenu(inGameMenuIndex);
  // }

  // // Suponiendo que el juego termina después de 15 segundos
  // if (millis() - gameStartTime > 15000)
  // {
  //   // Antes de ir a GAME_OVER, se activa el ingreso del nombre
  //   currentState = ENTER_NAME;
  //   currentLetterIndex = 0;                // Reiniciamos el índice de letras
  //   display.displayPlayerName(playerName); // Mostramos el nombre inicial
  // }
}

/**
 * @brief Maneja la navegación en el menú del juego.
 * @param yValue Valor analógico del joystick en el eje Y.
 * @param joystickMoved Indica si el joystick ha sido movido.
 * @param buttonPressed Indica si el botón ha sido presionado.
 * @param gameStartTime Tiempo de inicio del juego.
 *
 * Actualiza el índice del menú del juego y verifica las acciones del botón.
 */
void inGameMenuHandler(int yValue, bool joystickMoved, bool buttonPressed)
{
  if (DECREMENTO(yValue) && !joystickMoved)
  {
    // Función para sonido
    myOST.move();
    inGameMenuIndex++;
    if (inGameMenuIndex >= inGameMenuItems)
      inGameMenuIndex = 0;
    joystickMoved = true;
    display.showInGameMenu(inGameMenuIndex);
  }

  if (INCREMENTO(yValue) && !joystickMoved)
  {
    // Función para sonido
    myOST.move();
    inGameMenuIndex--;
    if (inGameMenuIndex < 0)
      inGameMenuIndex = inGameMenuItems - 1;
    joystickMoved = true;
    display.showInGameMenu(inGameMenuIndex);
  }

  if (!INCREMENTO(yValue) && !DECREMENTO(yValue))
  {
    joystickMoved = false;
  }

  if (buttonPressed)
  {
    if (inGameMenuIndex == 0)
    {
      currentState = IN_GAME;
      display.lcd_clear_display();
      // gameStartTime = millis();
    }
    else if (inGameMenuIndex == 1)
    {
      currentState = MAIN_MENU;
      display.showMainMenu(mainMenuIndex);
    }
  }
}

/**
 * @brief Maneja la lógica del menú de "Game Over".
 * @param yValue Valor analógico del joystick en el eje Y.
 * @param joystickMoved Indica si el joystick ha sido movido.
 * @param buttonPressed Indica si el botón ha sido presionado.
 *
 * Actualiza el índice del menú de "Game Over" y maneja la
 * transición a otros estados del juego según la entrada del botón.
 */
void gameOverHandler(int yValue, bool joystickMoved, bool buttonPressed)
{
  if (DECREMENTO(yValue) && !joystickMoved)
  {
    // Función para sonido
    myOST.move();
    gameOverMenuIndex++;
    if (gameOverMenuIndex >= gameOverMenuItems)
      gameOverMenuIndex = 0;
    joystickMoved = true;
    display.showGameOverMenu(gameOverMenuIndex);
  }

  if (INCREMENTO(yValue) && !joystickMoved)
  {
    // Función para sonido
    myOST.move();
    gameOverMenuIndex--;
    if (gameOverMenuIndex < 0)
      gameOverMenuIndex = gameOverMenuItems - 1;
    joystickMoved = true;
    display.showGameOverMenu(gameOverMenuIndex);
  }

  if (!INCREMENTO(yValue) && !DECREMENTO(yValue))
  {
    joystickMoved = false;
  }

  if (buttonPressed)
  {
    if (gameOverMenuIndex == 0)
    {
      currentState = IN_GAME;
      display.lcd_clear_display();
      // gameStartTime = millis();
    }
    else if (gameOverMenuIndex == 1)
    {
      currentState = MAIN_MENU;
      display.showMainMenu(mainMenuIndex);
    }
  }
}

/**
 * @brief Maneja la entrada del nombre del jugador.
 * @param yValue Valor analógico del joystick en el eje Y.
 * @param joystickMoved Referencia que indica si el joystick ha sido movido.
 * @param buttonPressed Indica si el botón ha sido presionado.
 *
 * Cambia las letras del nombre del jugador y maneja la
 * transición al estado GAME_OVER cuando se ingresa el nombre completo.
 */
// Mover el cursor entre letras
char playerName[4] = {'A', 'A', 'A', '\0'};
void enterNameHandler(int yValue, bool joystickMoved, bool buttonPressed)
{
  // Mover el cursor entre letras, asegurándonos de que el índice esté dentro de los límites
  if (!joystickMoved && (DECREMENTO(yValue) || INCREMENTO(yValue)))
  {
    // Serial.println("Me moví?");
    // Validar que currentLetterIndex esté dentro de los límites correctos
    if (currentLetterIndex >= 0 && currentLetterIndex < 3)
    {
      // Serial.println(currentLetterIndex);
      if (DECREMENTO(yValue))
      {
        myOST.move();
        playerName[currentLetterIndex]++;
        if (playerName[currentLetterIndex] > 'Z')
        {
          playerName[currentLetterIndex] = 'A';
        }
      }
      else if (INCREMENTO(yValue))
      {
        myOST.move();
        playerName[currentLetterIndex]--;
        if (playerName[currentLetterIndex] < 'A')
        {
          playerName[currentLetterIndex] = 'Z';
        }
      }
      joystickMoved = true; // Joystick se movió
    }
  }
  else
  {
    joystickMoved = false; // Joystick no se movió
  }

  // Actualizar solo cuando el botón sea presionado
  if (buttonPressed)
  {
    currentLetterIndex++;

    // Si hemos ingresado todas las letras, pasar al estado GAME_OVER
    if (currentLetterIndex >= 3)
    {
      currentState = GAME_OVER;
      currentLetterIndex = 0; // Reiniciar índice
      display.lcd_clear_display(); // Limpiar pantalla

      // Guardar el nombre ingresado
      display.saveValue(playerName, score);

      // Reiniciar playerName para futuras entradas
      playerName[0] = 'A';
      playerName[1] = 'A';
      playerName[2] = 'A';
      playerName[3] = '\0'; // Asegurar terminación con '\0'
      display.showGameOverMenu(gameOverMenuIndex); // Mostrar Game Over
    }
    else
    {
      // Solo actualizar la pantalla cuando el botón sea presionado
      display.lcd_set_cursor(0, 0);
      display.lcd_print("Nombre: ");
      display.lcd_set_cursor(0, 1);
      display.lcd_print(playerName);
    }
  }
  else
  {
    // No actualizar la pantalla hasta que se presione el botón
    display.lcd_set_cursor(0, 0);
    display.lcd_print("Nombre: ");
    display.lcd_set_cursor(0, 1);
    display.lcd_print(playerName);
  }
}

/**
 * @brief Maneja la navegación del menú en el videojuego.
 *
 * Esta función se encarga de gestionar la lógica de navegación del menú en función del estado actual del juego.
 * Se utilizan entradas del joystick y botones para navegar a través de diferentes estados del menú.
 *
 * @param startGameFlag Bandera que indica si se debe iniciar un nuevo juego.
 *                      Esta variable puede ser modificada en la función según la lógica del menú.
 *
 * La función realiza lo siguiente:
 * - Lee el valor analógico del eje Y del joystick.
 * - Verifica si un botón ha sido presionado.
 * - Dependiendo del estado actual del menú (`currentState`), llama a la función de manejo correspondiente para ese estado.
 *
 * Los estados posibles son:
 * - WELCOME: Muestra la pantalla de bienvenida.
 * - MAIN_MENU: Maneja la navegación en el menú principal del juego.
 * - HIGH_SCORES: Muestra las puntuaciones más altas.
 * - IN_GAME: Maneja la lógica durante el juego.
 * - IN_GAME_MENU: Maneja la navegación en el menú del juego en curso.
 * - GAME_OVER: Muestra la lógica cuando el juego ha terminado.
 * - ENTER_NAME: Maneja la entrada del nombre del jugador.
 *
 * Ejemplo de uso:
 * ```cpp
 * MenuHandler menuHandler;
 * menuHandler.handleMenuNavigation(startGameFlag);
 * ```
 */
void MenuHandler::handleMenuNavigation()
{
  int yValue = analogRead(PIN_Y);    // Lee el valor del eje Y del joystick
  bool joystickMoved = false;        // Bandera para indicar si el joystick se ha movido
  buttonPressed = isButtonPressed(); // Verifica si el botón ha sido presionado

  // Manejo del menú basado en el estado actual
  switch (currentState)
  {
  case WELCOME:
    // Serial.println("Welcome");
    welcomeHandler(buttonPressed); // Maneja la pantalla de bienvenida
    break;

  case MAIN_MENU:
    // Serial.println("Main Menu");
    mainMenuHandler(yValue, joystickMoved, buttonPressed); // Maneja el menú principal
    break;

  case HIGH_SCORES:
    // Serial.println("High scores");
    highScoresHandler(buttonPressed); // Maneja la visualización de las puntuaciones más altas
    break;

  case IN_GAME:
    // Serial.println("In game");
    inGameHandler(buttonPressed); // Maneja la lógica del juego
    break;

  case IN_GAME_MENU:
    // Serial.println("Pause");
    inGameMenuHandler(yValue, joystickMoved, buttonPressed); // Maneja el menú en el juego
    break;

  case GAME_OVER:
    // Serial.println("over");
    gameOverHandler(yValue, joystickMoved, buttonPressed); // Maneja la lógica de fin de juego
    break;

  case ENTER_NAME:
    enterNameHandler(yValue, joystickMoved, buttonPressed); // Maneja la entrada del nombre
    break;
  }
}
