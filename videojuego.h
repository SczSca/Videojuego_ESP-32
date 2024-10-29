/**
 * @file videojuego.h
 * @brief Declaración de las instancias globales utilizadas en el videojuego.
 *
 * Este archivo contiene las instancias de las clases encargadas del manejo de la microSD, la pantalla LCD,
 * el menú y las tareas paralelas en el videojuego.
 */

#ifndef VIDEOJUEGO_H
#define VIDEOJUEGO_H

#include "microsd.h"
#include "lcd_handler.h"
#include "menu_handler.h"
#include "parallel_task.h"
#include "song.h"

soundtracks myOST;

/**
 * @brief Instancia global de la clase MicroSD para gestionar la tarjeta microSD.
 *
 * Esta instancia se utiliza para leer y escribir puntajes en la tarjeta microSD.
 */
MicroSD microSD;

/**
 * @brief Instancia global de la clase LCDHandler para gestionar la pantalla LCD.
 *
 * Esta instancia se utiliza para manejar la salida visual en la pantalla del videojuego.
 */
LCDHandler display;

/**
 * @brief Instancia global de la clase MenuHandler para gestionar el menú del videojuego.
 *
 * Esta instancia se utiliza para manejar la navegación del menú del videojuego.
 */
MenuHandler menuHandler;

/**
 * @brief Instancia global de la clase ParallelTask para gestionar tareas paralelas.
 *
 * Esta instancia se utiliza para manejar las tareas que deben ejecutarse de manera concurrente en el videojuego.
 */
ParallelTask parallelTask;

Juego myJuego;

// soundtracks myOST;

#endif