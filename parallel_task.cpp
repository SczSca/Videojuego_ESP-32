/**
 * @file parallel_task.cpp
 * @brief Implementación optimizada de la clase ParallelTask para manejar tareas paralelas en el videojuego.
 *
 * Esta clase utiliza FreeRTOS para crear y gestionar tareas en núcleos específicos del ESP32.
 * Las tareas incluyen el movimiento de obstáculos, manejo de menús, movimiento del jugador y gestión de pausa.
 */

#include "parallel_task.h"

#define NUCLEO_PRINCIPAL 1
#define NUCLEO_SECUNDARIO 0

// Declaración de los manejadores de tareas
TaskHandle_t HiloMenu;
TaskHandle_t HiloMenu2;
TaskHandle_t HiloObstaculo1;
TaskHandle_t HiloObstaculo2;
TaskHandle_t HiloPlayerMov;
TaskHandle_t HiloPausa;
TaskHandle_t HiloMusicaGame;

void ParallelTask::createGameTasks()
{
  // Creación de tareas para los obstáculos y el movimiento del jugador
  xTaskCreatePinnedToCore(obstacle1Task, "obstacle1Mov", 20000, NULL, 2, &HiloObstaculo1, NUCLEO_PRINCIPAL);
  xTaskCreatePinnedToCore(obstacle2Task, "obstacle2Mov", 20000, NULL, 3, &HiloObstaculo2, NUCLEO_PRINCIPAL);
  xTaskCreatePinnedToCore(playerMov, "playerMov", 20000, NULL, 4, &HiloPlayerMov, NUCLEO_PRINCIPAL);

  xTaskCreatePinnedToCore(gameMusic, "gameMusic", 20000, NULL, 4, &HiloMusicaGame, NUCLEO_SECUNDARIO);
  // Creación de la tarea para manejar la pausa en el núcleo secundario
  xTaskCreatePinnedToCore(checkingPause, "checkPause", 15000, NULL, 1, &HiloPausa, NUCLEO_SECUNDARIO);
}

void ParallelTask::resumeGame()
{
  // Reanuda las tareas suspendidas
  vTaskResume(HiloPlayerMov);
  vTaskResume(HiloObstaculo1);
  vTaskResume(HiloObstaculo2);
  vTaskResume(HiloMusicaGame);
  myJuego.startPlayer();

  // Reinicia la tarea de pausa
  xTaskCreatePinnedToCore(checkingPause, "checkPause", 15000, NULL, 1, &HiloPausa, NUCLEO_SECUNDARIO);
}

/**
  @param type es 1 en el caso de que sea salir de medio juego
*/
void ParallelTask::goMenu(int8_t type)
{
  if(type == 1)
  {
    vTaskDelete(HiloPlayerMov);
    vTaskDelete(HiloObstaculo1);
    vTaskDelete(HiloObstaculo2);
  }
  // Crea la tarea para gestionar el menú principal
  xTaskCreatePinnedToCore(menuTask, "MenuTask", 20000, NULL, 1, &HiloMenu, NUCLEO_PRINCIPAL);
}

void ParallelTask::gameOver()
{
  // Elimina las tareas de obstáculos y muestra el menú de fin de juego
  vTaskDelete(HiloObstaculo1);
  vTaskDelete(HiloObstaculo2);
  vTaskDelete(HiloPausa);
  vTaskDelete(HiloMusicaGame);
  xTaskCreatePinnedToCore(deathSound, "deathSound", 5000, NULL, 4, &HiloMusicaGame, NUCLEO_SECUNDARIO);
  currentState = ENTER_NAME;
  display.lcd_clear_display();
  goMenu(0);
}

void ParallelTask::pauseGame()
{
  // Suspende las tareas de movimiento del jugador y obstáculos
  vTaskSuspend(HiloPlayerMov);
  vTaskSuspend(HiloObstaculo1);
  vTaskSuspend(HiloObstaculo2);
  vTaskSuspend(HiloMusicaGame);

  // Muestra el menú de pausa
  currentState = IN_GAME_MENU;
  inGameMenuIndex = 0;
  display.showInGameMenu(inGameMenuIndex);
  
  // Crea la tarea de menú de pausa
  xTaskCreatePinnedToCore(menuTask2, "MenuTask-2", 20000, NULL, 5, &HiloMenu2, NUCLEO_PRINCIPAL);
}

void ParallelTask::restartPositions()
{
  obstacle1[0] = 0;
  obstacle1[1] = 0;

  obstacle2[0] = 15;
  obstacle2[1] = 1;

  player[0] = 7;
  player[1] = 0;
}

void ParallelTask::startTasks()
{
  // Configura y muestra el menú inicial del juego
  menuHandler.setup();
  goMenu(0);
}

void ParallelTask::menuTask(void *pvParameters)
{
  bool whileFlag = true;
  while (whileFlag)
  {
    menuHandler.handleMenuNavigation();

    // Control del estado del juego desde el menú
    if (currentState == IN_GAME)
    {
      score = 0;
      whileFlag = false;
      restartPositions();
    }

    vTaskDelay(120 / portTICK_PERIOD_MS);
  }

  createGameTasks(); // Al salir del menú, se crean las tareas del juego
  vTaskDelete(NULL);
}

void ParallelTask::menuTask2(void *pvParameters)
{
  bool whileFlag = true;
  bool isResumed = false;

  while (whileFlag)
  {
    menuHandler.handleMenuNavigation();

    if (currentState == IN_GAME)
    {
      isResumed = true;
      whileFlag = false;
    }
    else if (currentState == MAIN_MENU)
    {
      whileFlag = false;
    }

    vTaskDelay(120 / portTICK_PERIOD_MS);
  }

  // Reanudar juego o volver al menú principal
  if (isResumed) resumeGame();
  else goMenu(1);

  vTaskDelete(NULL);
}

void ParallelTask::obstacle1Task(void *pvParameters)
{
  int8_t counter = 3;
  for (;;)
  {
    display.moveObstacle(obstacle1, 1);
    obstacle1[0] = 0;
    obstacle1[1] = 0;
    score += 1;

    // if (--counter == 0) break;

    vTaskDelay(20 / portTICK_PERIOD_MS);
  }
  
  vTaskDelete(NULL);
}

void ParallelTask::obstacle2Task(void *pvParameters)
{
  int8_t counter = 3;
  for (;;)
  {
    display.moveObstacle(obstacle2, 2);
    obstacle2[0] = 15;
    obstacle2[1] = 1;
    score += 1;

    // if (--counter == 0) break;

    vTaskDelay(20 / portTICK_PERIOD_MS);
  }
  
  vTaskDelete(NULL);
}

void ParallelTask::playerMov(void *pvParameters)
{
  myJuego.startPlayer();
  bool whileFlag = true;

  while (whileFlag)
  {
    if (myJuego.hasCrashed())
    {
      whileFlag = false;
    }
    myJuego.movimiento();
    vTaskDelay(30 / portTICK_PERIOD_MS);
  }

  gameOver();
  vTaskDelete(NULL);
}

void ParallelTask::checkingPause(void *pvParameters)
{
  bool whileFlag = true;

  while (whileFlag)
  {
    if (menuHandler.isButtonPressed())
    {
      whileFlag = false;
    }

    vTaskDelay(100 / portTICK_PERIOD_MS);
  }

  pauseGame();
  vTaskDelete(NULL);
}

void ParallelTask::gameMusic(void *pvParameters)
{
  bool whileFlag = true;
  while(whileFlag)
  {
    myOST.marcha_imperial();
  }
}

void ParallelTask::deathSound(void *pvParameters)
{
  myOST.death_sound();
  vTaskDelete(NULL);
  
}