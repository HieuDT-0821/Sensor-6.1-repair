#include "mq135.h"

extern ADC_HandleTypeDef hadc1;

float MQ135_Read(void)
{
    HAL_ADC_Start(&hadc1);
    if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
    {
        uint32_t value = HAL_ADC_GetValue(&hadc1);
        // Đổi giá trị ADC sang ppm (giả lập)
        return (float)value * 0.1f;
    }
    return 0.0f;
}