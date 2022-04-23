/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_spi_flash.h"

void task_code(void *parameter) {

   printf("Hello world! running on core %d\n", xPortGetCoreID());
   // required loop on core 1 only, otherwise
   // E (20) FreeRTOS: FreeRTOS Task "task1" should not return, Aborting now!
   if (xPortGetCoreID()) {
      for (;;) {
         printf("Hello world! running on core %d\n", xPortGetCoreID());
         vTaskDelay(1000 / portTICK_PERIOD_MS);
      }
   }
}

void app_main(void)
{
   TaskHandle_t task1;

   task_code(NULL);
   xTaskCreatePinnedToCore(
         task_code,  // task function
         "task1",    // task name
         10000,      // stack size in words
         NULL,       // task input param
         0,          // task priority
         &task1,     // handle
         1);         // core id

    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU core(s), WiFi%s%s, ",
            CONFIG_IDF_TARGET,
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    printf("Minimum free heap size: %d bytes\n", esp_get_minimum_free_heap_size());

    for (int i = 100; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    printf("Restarting now.\n");

    vTaskDelete(task1);

    fflush(stdout);
    //esp_restart();
}
