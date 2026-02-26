#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"

static const char *TAG = "ejercicio_contador";

// Definimos el pin 2 que es el LED azul de tu placa
#define BLINK_GPIO 2

void app_main(void)
{
    /* 1. CONFIGURACIÓN DEL PIN */
    ESP_LOGI(TAG, "Configurando el GPIO %d como salida...", BLINK_GPIO);
    gpio_reset_pin(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    /* 2. INICIALIZACIÓN DEL CONTADOR */
    int contador = 0;
    uint8_t estado_led = 0;

    /* 3. BUCLE PRINCIPAL */
    while (1) {
        // Imprimir el estado actual en el monitor serial
        printf(">>> Ciclo actual: %d | LED: %s\n", 
                contador, 
                estado_led ? "ENCENDIDO" : "APAGADO");

        // Cambiar el estado del pin físico
        gpio_set_level(BLINK_GPIO, estado_led);

        // Cambiar la variable de estado para la siguiente vuelta (0 a 1, o 1 a 0)
        estado_led = !estado_led;

        // Si el LED se acaba de apagar (completó un parpadeo), sumamos al contador
        if (estado_led == 0) {
            contador++;
        }

        // Si el contador llega a 10, lo reiniciamos (opcional)
        if (contador > 10) {
            printf("--- Limite alcanzado, reiniciando contador ---\n");
            contador = 0;
        }

        // Espera de 500ms (puedes usar CONFIG_BLINK_PERIOD o un numero directo)
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}