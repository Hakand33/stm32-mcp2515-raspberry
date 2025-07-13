#include "mcp2515.h"

extern SPI_HandleTypeDef hspi1;  // SPI tanımı main.c içinde yapılmalı

static void MCP2515_Select(void) {
    HAL_GPIO_WritePin(MCP2515_CS_PORT, MCP2515_CS_PIN, GPIO_PIN_RESET);
}

static void MCP2515_Unselect(void) {
    HAL_GPIO_WritePin(MCP2515_CS_PORT, MCP2515_CS_PIN, GPIO_PIN_SET);
}

// CS kontrolü
#define MCP2515_CS_LOW()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)
#define MCP2515_CS_HIGH() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)

void MCP2515_Init(void) {
    // Reset komutu vs. buraya yazılır
    // MCP2515_CS_LOW(); ...
}

void MCP2515_SendMessage(uint16_t can_id, uint8_t *data) {
    // MCP2515’e veri gönderme işlemi
    // SPI protokolüne uygun veri gönder
}
void MCP2515_Reset(void) {
    uint8_t cmd = MCP2515_RESET;
    MCP2515_Select();
    HAL_SPI_Transmit(&hspi1, &cmd, 1, HAL_MAX_DELAY);
    MCP2515_Unselect();
    HAL_Delay(10); // reset sonrası kısa gecikme
}


void MCP2515_WriteRegister(uint8_t address, uint8_t data) {
    uint8_t txBuf[3] = {MCP2515_WRITE, address, data};
    MCP2515_Select();
    HAL_SPI_Transmit(&hspi1, txBuf, 3, HAL_MAX_DELAY);
    MCP2515_Unselect();
}

uint8_t MCP2515_ReadRegister(uint8_t address) {
    uint8_t txBuf[2] = {MCP2515_READ, address};
    uint8_t rxBuf = 0;
    MCP2515_Select();
    HAL_SPI_Transmit(&hspi1, txBuf, 2, HAL_MAX_DELAY);
    HAL_SPI_Receive(&hspi1, &rxBuf, 1, HAL_MAX_DELAY);
    MCP2515_Unselect();
    return rxBuf;
}

void MCP2515_BitModify(uint8_t address, uint8_t mask, uint8_t data) {
    uint8_t txBuf[4] = {MCP2515_BIT_MODIFY, address, mask, data};
    MCP2515_Select();
    HAL_SPI_Transmit(&hspi1, txBuf, 4, HAL_MAX_DELAY);
    MCP2515_Unselect();
}

uint8_t MCP2515_ReadStatus(void) {
    uint8_t cmd = MCP2515_READ_STATUS;
    uint8_t status = 0;
    MCP2515_Select();
    HAL_SPI_Transmit(&hspi1, &cmd, 1, HAL_MAX_DELAY);
    HAL_SPI_Receive(&hspi1, &status, 1, HAL_MAX_DELAY);
    MCP2515_Unselect();
    return status;
}
