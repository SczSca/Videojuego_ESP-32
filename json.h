/**
 * @file json.h
 * @brief Declaración de la clase JSON para el manejo de objetos JSON en el contexto de puntajes de jugadores.
 */

#ifndef JSON_H
#define JSON_H

#include <ArduinoJson.h>

/**
 * @class JSON
 * @brief Clase para la creación y lectura de objetos JSON relacionados con puntajes de jugadores.
 *
 * La clase JSON proporciona métodos para crear un objeto JSON a partir del nombre de un jugador
 * y su puntaje, así como para leer dichos datos desde un objeto JSON.
 */
class JSON
{
public:
  /**
   * @brief Constructor por defecto.
   *
   * Inicializa una instancia de la clase JSON.
   */
  JSON() {}

  /**
   * @brief Crea un objeto JSON con el nombre del jugador y su puntaje.
   *
   * @param playerName Un puntero a un arreglo de caracteres que contiene el nombre del jugador.
   * @param score El puntaje del jugador.
   * @return String La representación del objeto JSON en formato de cadena de texto.
   */
  String createScoreJson(String playerName, int score);

  /**
   * @brief Lee un objeto JSON y extrae el nombre del jugador y su puntaje.
   *
   * @param jsonStr La cadena de texto en formato JSON que contiene el nombre del jugador y su puntaje.
   * @param score Referencia a una variable entera donde se almacenará el puntaje del jugador.
   * @param playerName Referencia a una variable String donde se almacenará el nombre del jugador.
   */
  void readScoreFromJson(const String &jsonStr, int &score, String &playerName);
};

#endif