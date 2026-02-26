#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Para usar logs de nivel DEBUG, esta definición debe ir ANTES de incluir esp_log.h
#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG
#include "esp_log.h"
#include "esp_err.h"

#define LED_PIN 2
static uint8_t led_level = 0;
static const char *TAG = "Charly";

// 1. FUNCIÓN DE CONFIGURACIÓN
esp_err_t init_led(void) {
    gpio_reset_pin(LED_PIN);
    esp_err_t err = gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    if (err == ESP_OK) {
        ESP_LOGI(TAG, "El LED se inicializó correctamente en el pin %d", LED_PIN);
        ESP_LOGD(TAG, "Debug: init_led() regresó ESP_OK");
    } else {
        ESP_LOGE(TAG, "FALLO crítico: No se pudo inicializar el LED");
    }
    return err;
}

// 2. FUNCIÓN DE CONTROL (PARPADEO)
esp_err_t blink_led(void) {
    led_level = !led_level;
    
    // Corregido: %u para unsigned int (estado)
    ESP_LOGD(TAG, "Debug: Siguiente estado del LED = %u", led_level);
    
    esp_err_t err = gpio_set_level(LED_PIN, led_level);
    
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "Advertencia: No se pudo cambiar el nivel físico del pin");
    } else {
        ESP_LOGI(TAG, "Estado del LED cambiado a: %s", led_level ? "ENCENDIDO" : "APAGADO");
    }
    
    return err;
}

// 3. PUNTO DE ENTRADA PRINCIPAL
void app_main(void) {
    /* Configuración del nivel de Log:
       ESP_LOG_ERROR, ESP_LOG_WARN, ESP_LOG_INFO, ESP_LOG_DEBUG, ESP_LOG_VERBOSE
    */
    esp_log_level_set(TAG, ESP_LOG_INFO); // Cambia a ESP_LOG_DEBUG para ver todo

    // Inicializamos y verificamos errores inmediatamente
    if (init_led() != ESP_OK) {
        ESP_LOGE(TAG, "Error al iniciar el hardware. Deteniendo...");
        return; 
    }

    ESP_LOGI(TAG, "Iniciando bucle de parpadeo...");

    while (1) {
        // Retardo de 1000ms usando el conversor de ticks de FreeRTOS
        vTaskDelay(pdMS_TO_TICKS(1000));
        
        // Ejecuta el parpadeo y verifica si hubo error
        ESP_ERROR_CHECK(blink_led());
    }
}