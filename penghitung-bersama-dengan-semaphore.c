#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

SemaphoreHandle_t mocca;

int shared_counter = 0;

void
tambahin(void *arg)
{

	for(int i = 0; i < 23; i++)
	{
		if(xSemaphoreTake(mocca, portMAX_DELAY))
		{
			printf("void tambahin\n");
			shared_counter+=1;
			xSemaphoreGive(mocca);
		}
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void
baca(void *arg)
{

	for(int i = 0; i < 23; i++)
	{
		if(xSemaphoreTake(mocca, portMAX_DELAY))
		{
			
			printf("void baca\n");
			printf("berhitung = %d\n", shared_counter);
			xSemaphoreGive(mocca);
		}
		vTaskDelay(2000 / portTICK_PERIOD_MS);
	}
}

void app_main(void)
{
	mocca = xSemaphoreCreateMutex();

	xTaskCreate(tambahin, "tambahin", 2048, NULL, 1, NULL);
	xTaskCreate(baca, "baca", 2048, NULL, 1, NULL);
}
