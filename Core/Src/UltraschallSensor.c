#include "UltraschallSensor.h"
extern UART_HandleTypeDef huart2;
// Sends a command to the sensor and calculates the result out of the answer.
uint16_t Sensor_ReadData(const uint8_t* command) {
    HAL_StatusTypeDef status;
    uint8_t checksum;
    uint8_t rxBuffer[4];

    // 1. Send Command
    HAL_UART_Transmit(&huart2, (uint8_t*)command, 4, 100);

    // 2. Receive Answer (4 Bytes: Startbyte, Data_H, Data_L, Checksum)
    status = HAL_UART_Receive(&huart2, rxBuffer, 4, 100);

    // Calculate expected URM37 checksum
    checksum = rxBuffer[0] + rxBuffer[1] + rxBuffer[2];

    // 3. Evaluate Data Integrity
    if (status == HAL_OK && checksum == rxBuffer[3]) {
        // Reconstruct the 16-bit measurement (Cast to prevent integer promotion issues)
        return (uint16_t)(((uint16_t)rxBuffer[1] << 8) | rxBuffer[2]);
    }

    // 4. Error Handling (If we reached here, something went wrong)(Measurement-value too high results in 0xFFFF)
    if (status != HAL_OK) {
        return 0xFFFD; // HAL UART Timeout or Hardware Error
    }

    if (checksum != rxBuffer[3]) {
        return 0xFFFE; // Checksum Mismatch (Data Corrupted)
    }

    return 0xFFFC; // Global Fallback Error Value
}
