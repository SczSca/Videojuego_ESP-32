/**
 * @file MicroSD.h
 * @brief Declaración de la clase MicroSD para gestionar la lectura y escritura de datos en una tarjeta microSD.
 */

#ifndef MICROSD_H
#define MICROSD_H

#include <SD.h>
#include <SPI.h>

#define MICROSD_PIN 5 ///< Definición del pin utilizado para la comunicación con la tarjeta microSD

/**
 * @class MicroSD
 * @brief Clase para la gestión de operaciones en una tarjeta microSD.
 *
 * La clase MicroSD permite inicializar la tarjeta, guardar puntajes de jugadores,
 * obtener los puntajes más altos y verificar el contenido de los archivos.
 */
class MicroSD
{
public:
  /**
   * @brief Nombre del archivo donde se guardan los puntajes.
   *
   * El nombre del archivo por defecto es `/scores.txt`.
   */
  //String folderName = "/Scores/";
  String fileName = "/scores.txt";

  /**
   * @brief Inicializa la tarjeta microSD.
   *
   * Este método debe ser llamado antes de realizar cualquier operación de lectura o escritura.
   * Inicializa la comunicación SPI y verifica que la tarjeta microSD esté disponible.
   */
  void init();

  /**
   * @brief Guarda el nombre del jugador y su puntaje en la tarjeta microSD.
   *
   * El puntaje y el nombre del jugador se guardan en el archivo especificado por `filename`.
   * Si el archivo no existe, será creado.
   *
   * @param playerName Un puntero a un arreglo de caracteres que contiene el nombre del jugador.
   * @param score El puntaje del jugador.
   */
  void saveScore(char *playerName, int score);

  /**
   * @brief Obtiene los puntajes más altos almacenados en la tarjeta microSD.
   *
   * Lee los puntajes del archivo y guarda los N puntajes más altos en el arreglo `topScores`.
   *
   * @param topScores Un arreglo de cadenas donde se almacenarán los puntajes más altos.
   * @param topN El número de puntajes más altos a obtener.
   */
  void getTopScores(String topScores[], int topN);

  /**
   * @brief Verifica el contenido del archivo de puntajes.
   *
   * Este método imprime el contenido del archivo de puntajes en la consola serial.
   */
  void checkFileContent();
};

#endif