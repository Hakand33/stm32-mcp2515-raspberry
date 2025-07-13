#ifndef MCP2515_H
#define MCP2515_H

#include "stm32f4xx_hal.h"
#include "main.h"

// SPI CS Pin tanımı
#define MCP2515_CS_PORT GPIOA
#define MCP2515_CS_PIN  GPIO_PIN_4

// MCP2515 SPI komutları
#define MCP2515_RESET     0xC0
#define MCP2515_READ      0x03
#define MCP2515_WRITE     0x02
#define MCP2515_RTS       0x80
#define MCP2515_READ_STATUS 0xA0
#define MCP2515_BIT_MODIFY  0x05
// Fonksiyon Prototipleri
void MCP2515_Reset(void);
void MCP2515_WriteRegister(uint8_t address, uint8_t data);
uint8_t MCP2515_ReadRegister(uint8_t address);
void MCP2515_BitModify(uint8_t address, uint8_t mask, uint8_t data);
uint8_t MCP2515_ReadStatus(void);
void MCP2515_Init(void);
void MCP2515_SendMessage(uint16_t can_id, uint8_t *data);

#endif
