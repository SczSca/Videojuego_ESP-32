#include <Arduino.h>
#include "song.h"

void soundtracks ::marcha_imperial(void)
{
  tone(buzzer, LA3, Q);
  delay(1 + Q);
  tone(buzzer, LA3, Q);
  delay(1 + Q);
  tone(buzzer, LA3, Q);
  delay(1 + Q);
  tone(buzzer, F3, E + S);
  delay(1 + E + S);
  tone(buzzer, C4, S);
  delay(1 + S);

  tone(buzzer, LA3, Q);
  delay(1 + Q);
  tone(buzzer, F3, E + S);
  delay(1 + E + S);
  tone(buzzer, C4, S);
  delay(1 + S);
  tone(buzzer, LA3, H);
  delay(1 + H);

  tone(buzzer, E4, Q);
  delay(1 + Q);
  tone(buzzer, E4, Q);
  delay(1 + Q);
  tone(buzzer, E4, Q);
  delay(1 + Q);
  tone(buzzer, F4, E + S);
  delay(1 + E + S);
  tone(buzzer, C4, S);
  delay(1 + S);

  tone(buzzer, Ab3, Q);
  delay(1 + Q);
  tone(buzzer, F3, E + S);
  delay(1 + E + S);
  tone(buzzer, C4, S);
  delay(1 + S);
  tone(buzzer, LA3, H);
  delay(1 + H);

  tone(buzzer, LA4, Q);
  delay(1 + Q);
  tone(buzzer, LA3, E + S);
  delay(1 + E + S);
  tone(buzzer, LA3, S);
  delay(1 + S);
  tone(buzzer, LA4, Q);
  delay(1 + Q);
  tone(buzzer, Ab4, E + S);
  delay(1 + E + S);
  tone(buzzer, G4, S);
  delay(1 + S);

  tone(buzzer, Gb4, S);
  delay(1 + S);
  tone(buzzer, E4, S);
  delay(1 + S);
  tone(buzzer, F4, E);
  delay(1 + E);
  delay(1 + E); // PAUSE
  tone(buzzer, Bb3, E);
  delay(1 + E);
  tone(buzzer, Eb4, Q);
  delay(1 + Q);
  tone(buzzer, D4, E + S);
  delay(1 + E + S);
  tone(buzzer, Db4, S);
  delay(1 + S);

  tone(buzzer, C4, S);
  delay(1 + S);
  tone(buzzer, B3, S);
  delay(1 + S);
  tone(buzzer, C4, E);
  delay(1 + E);
  delay(1 + E); // PAUSE QUASI FINE RIGA
  tone(buzzer, F3, E);
  delay(1 + E);
  tone(buzzer, Ab3, Q);
  delay(1 + Q);
  tone(buzzer, F3, E + S);
  delay(1 + E + S);
  tone(buzzer, LA3, S);
  delay(1 + S);

  tone(buzzer, C4, Q);
  delay(1 + Q);
  tone(buzzer, LA3, E + S);
  delay(1 + E + S);
  tone(buzzer, C4, S);
  delay(1 + S);
  tone(buzzer, E4, H);
  delay(1 + H);

  tone(buzzer, LA4, Q);
  delay(1 + Q);
  tone(buzzer, LA3, E + S);
  delay(1 + E + S);
  tone(buzzer, LA3, S);
  delay(1 + S);
  tone(buzzer, LA4, Q);
  delay(1 + Q);
  tone(buzzer, Ab4, E + S);
  delay(1 + E + S);
  tone(buzzer, G4, S);
  delay(1 + S);

  tone(buzzer, Gb4, S);
  delay(1 + S);
  tone(buzzer, E4, S);
  delay(1 + S);
  tone(buzzer, F4, E);
  delay(1 + E);
  delay(1 + E); // PAUSE
  tone(buzzer, Bb3, E);
  delay(1 + E);
  tone(buzzer, Eb4, Q);
  delay(1 + Q);
  tone(buzzer, D4, E + S);
  delay(1 + E + S);
  tone(buzzer, Db4, S);
  delay(1 + S);

  tone(buzzer, C4, S);
  delay(1 + S);
  tone(buzzer, B3, S);
  delay(1 + S);
  tone(buzzer, C4, E);
  delay(1 + E);
  delay(1 + E); // PAUSE QUASI FINE RIGA
  tone(buzzer, F3, E);
  delay(1 + E);
  tone(buzzer, Ab3, Q);
  delay(1 + Q);
  tone(buzzer, F3, E + S);
  delay(1 + E + S);
  tone(buzzer, C4, S);
  delay(1 + S);

  tone(buzzer, LA3, Q);
  delay(1 + Q);
  tone(buzzer, F3, E + S);
  delay(1 + E + S);
  tone(buzzer, C4, S);
  delay(1 + S);
  tone(buzzer, LA3, H);
  delay(1 + H);

  delay(2 * H);
}

void soundtracks ::move(void)
{
  tone(buzzer, 500, 80); // Frecuencia de 500 Hz, duración de 80 ms
}

void soundtracks ::death_sound(void)
{
  tone(buzzer, E5, 100); // Nota E5
  delay(100 + 50);
  tone(buzzer, E5, 100); // Nota E5 repetida
  delay(100 + 50);
  tone(buzzer, E5, 100); // Nota E5 repetida
  delay(100 + 50);

  tone(buzzer, C5, 100); // Cambio a C5
  delay(100 + 50);

  tone(buzzer, E5, 100); // Vuelta a E5
  delay(100 + 50);

  tone(buzzer, G5, 100); // Nota G5
  delay(100 + 50);
  tone(buzzer, G4, 100); // Nota G4, descenso en tono
  delay(100 + 50);

  // Sección final del sonido de muerte
  tone(buzzer, C5, 400); // Nota C5 larga
  delay(400 + 50);
  tone(buzzer, G4, 400); // Nota G4 larga
  delay(400 + 50);
  tone(buzzer, E4, 400); // Nota E4 larga
  delay(400 + 50);
  tone(buzzer, LA4, 300); // Nota A4
  delay(300 + 50);
  tone(buzzer, B4, 300); // Nota B4
  delay(300 + 50);
  tone(buzzer, Bb4, 200); // Nota Bb4
  delay(200 + 50);
  tone(buzzer, LA4, 300); // Nota A4
  delay(300 + 50);

  tone(buzzer, G4, 200); // Nota G4
  delay(200 + 50);
  tone(buzzer, F4, 200); // Nota F4
  delay(200 + 50);
  tone(buzzer, E4, 200); // Nota E4
  delay(200 + 50);
  tone(buzzer, G4, 200); // Nota G4
  delay(200 + 50);
  tone(buzzer, LA4, 200); // Nota A4
  delay(200 + 50);
  tone(buzzer, F4, 400); // Nota F4 larga
  delay(400 + 50);
}
