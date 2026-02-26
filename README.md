#  ESP32: Blink con Logs y Control de Errores

Este proyecto es una práctica avanzada del clásico "Blink" (parpadeo de LED) utilizando el **ESP-IDF v5.5.3** para el microcontrolador ESP32. A diferencia de un blink básico, este código implementa niveles de diagnóstico (Logs) y gestión de errores de hardware.

## Descripción
El programa hace parpadear el LED integrado (GPIO 2) cada segundo, utilizando funciones modulares para inicializar el hardware y cambiar el estado del pin. Además, envía mensajes detallados a la terminal para monitorear el comportamiento del sistema en tiempo real.

### Características Principales:
* **Gestión de Logs:** Uso de `ESP_LOG` con diferentes niveles (INFO, DEBUG, WARN, ERROR).
* **Control de Retardo:** Implementación de `vTaskDelay` con conversión de milisegundos a Ticks.
* **Seguridad:** Uso de `ESP_ERROR_CHECK` para asegurar que el hardware responda correctamente.

##  Requisitos cumplidos
1.  **Configuración de Niveles de Log:** Se habilitó el nivel `ESP_LOG_DEBUG` localmente y se configuró el filtro en `app_main` mediante `esp_log_level_set`.
2.  **Modularidad:** Funciones separadas para inicialización (`init_led`) y lógica de parpadeo (`blink_led`).
3.  **Manejo de Tiempos:** Uso de `pdMS_TO_TICKS(1000)` para un retardo exacto de 1 segundo.

##  Estructura del Código
El archivo principal se encuentra en: `main/blink_example_main.c`

| Función | Descripción |
| :--- | :--- |
| `init_led()` | Configura el pin GPIO 2 como salida digital. |
| `blink_led()` | Alterna el estado del LED y reporta el cambio mediante logs. |
| `app_main()` | Punto de entrada que establece el nivel de log y ejecuta el bucle principal. |

##  Cómo ejecutarlo
1.  **Abrir en VS Code:** Asegúrate de tener instalada la extensión ESP-IDF.
2.  **Compilar:** Presiona el icono de la **V** (Build) en la barra inferior.
3.  **Subir al ESP32:** Presiona el icono del **rayo** (Flash).
4.  **Monitorear:** Presiona el icono del **monitor** para ver los mensajes:
    * *Ejemplo de salida:* `I (1000) Hernan_Project: El LED ahora esta ENCENDIDO`

---
**Autor:** [2030339-arch](https://github.com/2030339-arch)
**Fecha:** Febrero 2026