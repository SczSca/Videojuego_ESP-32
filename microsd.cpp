#include "microsd.h"
#include "json.h"

JSON json;

/**
 * @brief Inicializa la tarjeta microSD.
 *
 * Verifica si la tarjeta microSD está correctamente conectada y lista para su uso.
 * Si la inicialización falla, se muestra un mensaje de error en la consola serial.
 */
void MicroSD::init()
{
  if (!SD.begin(MICROSD_PIN))
  {
    Serial.println("Error al inicializar la microSD");
  }
  else
  {
    Serial.println("MicroSD inicializada correctamente");
  }
}

/**
 * @brief Guarda el nombre del jugador y su puntaje en la tarjeta microSD.
 *
 * Utiliza el método `createScoreJson` de la clase JSON para convertir el nombre del jugador y su puntaje
 * en una cadena JSON y luego la guarda en el archivo especificado.
 *
 * @param playerName Un puntero a un arreglo de caracteres que contiene el nombre del jugador.
 * @param score El puntaje del jugador.
 */
void MicroSD::saveScore(char *playerName, int score)
{
  String jsonData = json.createScoreJson(playerName, score);
  File file = SD.open(fileName, FILE_APPEND);
  if (file)
  {
    file.println(jsonData);
    file.close();
  }
  else
  {
    Serial.println("Error al abrir el archivo para escribir");
  }
}

/**
 * @brief Obtiene los puntajes más altos almacenados en la tarjeta microSD.
 *
 * Lee el archivo de puntajes, deserializa cada entrada de JSON, y ordena los puntajes
 * en orden descendente. Luego guarda los primeros `topN` puntajes en el arreglo `topScores`.
 *
 * @param topScores Un arreglo de cadenas donde se almacenarán los puntajes más altos.
 * @param topN El número de puntajes más altos a obtener.
 */
void MicroSD::getTopScores(String topScores[], int topN)
{
  File file = SD.open(fileName, FILE_READ);

  if (!file)
  {
    topScores[0] = "No hay puntajes";
    return;
  }

  String allScores[100];   // Almacenar hasta 100 entradas de JSON
  int scoreValues[100];    // Para ordenar los puntajes
  String playerNames[100]; // Para almacenar los nombres de los jugadores
  int count = 0;

  // Leer cada línea (un JSON) y deserializarla
  while (file.available() && count < 100)
  {
    allScores[count] = file.readStringUntil('\n');
    json.readScoreFromJson(allScores[count], scoreValues[count], playerNames[count]);
    count++;
  }
  file.close();

  // Ordenar los puntajes en orden descendente (método burbuja)
  for (int i = 0; i < count - 1; i++)
  {
    for (int j = i + 1; j < count; j++)
    {
      if (scoreValues[i] < scoreValues[j])
      {
        // Intercambiar puntajes
        int tempScore = scoreValues[i];
        scoreValues[i] = scoreValues[j];
        scoreValues[j] = tempScore;

        // Intercambiar nombres de jugadores
        String tempName = playerNames[i];
        playerNames[i] = playerNames[j];
        playerNames[j] = tempName;
      }
    }
  }

  // Guardar los primeros `topN` puntajes en el array `topScores`
  for (int i = 0; i < topN && i < count; i++)
  {
    topScores[i] = playerNames[i] + ":" + String(scoreValues[i]);
  }
}

/**
 * @brief Verifica el contenido del archivo de puntajes y lo muestra en la consola serial.
 *
 * Lee el archivo línea por línea y muestra cada línea en la consola serial.
 * Si el archivo no puede abrirse, se imprime un mensaje de error.
 */
void MicroSD::checkFileContent()
{
  File file = SD.open(fileName, FILE_READ);

  if (file)
  {
    while (file.available())
    {
      String line = file.readStringUntil('\n');
      // Serial.println(line); // Mostrar el contenido del archivo línea por línea
    }
    file.close();
  }
  else
  {
    // Serial.println("Error al abrir el archivo");
  }
}