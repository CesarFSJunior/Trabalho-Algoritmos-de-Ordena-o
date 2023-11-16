#include <time.h>
#include <stdio.h>
void testTime() {

        time_t hora_atual;
        struct tm *informacao_hora;
        char string_hora[9]; // Espaço para "HH:MM:SS\0"

        time(&hora_atual);
        informacao_hora = localtime(&hora_atual);

        strftime(string_hora, sizeof(string_hora), "%H:%M:%S", informacao_hora);

        printf("Hora atual: %s\n", string_hora);
}
