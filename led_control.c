#include "led_control.h"

/* Khởi tạo các chức năng */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

/* Con trỏ hàm dùng để điều khiển LED */
void (*LED_Control)(void) = LED_Mode1; // Khởi tạo với chế độ LED_Mode1

/* Biến để theo dõi chế độ hiện tại */
static int current_mode = 1;

int main(void)
{
    /* Khởi tạo HAL Library */
    HAL_Init();

    /* Cấu hình xung hệ thống */
    SystemClock_Config();

    /* Khởi tạo tất cả các GPIO */
    MX_GPIO_Init();

    /* Vòng lặp vô tận */
    while (1)
    {
        /* Gọi hàm điều khiển LED thông qua con trỏ */
        LED_Control();
        HAL_Delay(2000); // Chờ 2 giây trước khi chuyển đổi chế độ

        /* Chuyển đổi chế độ LED */
        Change_LED_Mode();
    }
}

/* Hàm chế độ LED 1: Bật LED trong 100ms, tắt trong 100ms */
void LED_Mode1(void)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
    HAL_Delay(100);
}

/* Hàm chế độ LED 2: Bật LED trong 500ms, tắt trong 500ms */
void LED_Mode2(void)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
    HAL_Delay(500);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
    HAL_Delay(500);
}

/* Hàm chế độ LED 3: Bật LED trong 1000ms, tắt trong 1000ms */
void LED_Mode3(void)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
    HAL_Delay(1000);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
    HAL_Delay(1000);
}

/* Hàm chuyển đổi chế độ LED */
void Change_LED_Mode(void)
{
    current_mode++;
    if (current_mode > 3)
    {
        current_mode = 1;
    }

    /* Chuyển đổi con trỏ hàm dựa vào chế độ hiện tại */
    switch (current_mode)
    {
        case 1:
            LED_Control = LED_Mode1;
            break;
        case 2:
            LED_Control = LED_Mode2;
            break;
        case 3:
            LED_Control = LED_Mode3;
            break;
        default:
            LED_Control = LED_Mode1;
            break;
    }
}

/* Hàm cấu hình xung hệ thống */
void SystemClock_Config(void)
{
    // Cấu hình xung hệ thống (xem thêm tài liệu hoặc sử dụng STM32CubeMX để tự động sinh mã)
}

/* Hàm khởi tạo GPIO */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* Bật clock cho GPIOA */
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /* Cấu hình chân PA0 làm Output */
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
