#include "json.h"

/**
 * @file json.h
 * @brief Definición de funciones para crear y leer datos JSON relacionados con puntajes de jugadores.
 */

/**
 * @brief Crea un objeto JSON con el nombre del jugador y su puntaje.
 *
 * Esta función recibe el nombre del jugador y su puntaje, y los inserta en un
 * objeto JSON, que luego se convierte en una cadena de texto JSON.
 *
 * @param playerName Un puntero a un arreglo de caracteres que contiene el nombre del jugador.
 * @param score El puntaje del jugador.
 * @return String La representación del objeto JSON en formato de cadena de texto.
 */
String JSON::createScoreJson(String playerName, int score)
{
  DynamicJsonDocument doc(1024);
  doc["playerName"] = playerName;
  doc["score"] = score;

  String output;
  serializeJson(doc, output);
  // Serial.println(output);
  return output;
}

/**
 * @brief Lee un objeto JSON y extrae el nombre del jugador y su puntaje.
 *
 * Esta función deserializa una cadena de texto en formato JSON y extrae el
 * nombre del jugador y su puntaje. Si la deserialización falla, imprime un
 * mensaje de error.
 *
 * @param jsonStr La cadena de texto en formato JSON que contiene el nombre del jugador y su puntaje.
 * @param score Referencia a una variable entera donde se almacenará el puntaje del jugador.
 * @param playerName Referencia a una variable String donde se almacenará el nombre del jugador.
 */
void JSON::readScoreFromJson(const String &jsonStr, int &score, String &playerName)
{
  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, jsonStr);

  if (!error)
  {
    // Leer el nombre del jugador y el puntaje desde el JSON
    playerName = doc["playerName"].as<String>();
    score = doc["score"].as<int>();

    // Seriales para depuración
    // Serial.print("Nombre del jugador: ");
    // Serial.println(playerName);
    // Serial.print("Puntaje: ");
    // Serial.println(score);
  }
  else
  {
    // Serial.println("Error en la deserialización");
  }
}