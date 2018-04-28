#include <stdint.h>

#define F_CPU     2000000UL

#define _ADDR_(a) *(volatile uint8_t *)(a)
// GPIO Registers.
#define GPIOB_ODR _ADDR_(0x5005)
#define GPIOB_DDR _ADDR_(0x5007)
#define GPIOB_CR1 _ADDR_(0x5008)
#define GPIOC_ODR _ADDR_(0x500A)
#define GPIOC_IDR _ADDR_(0x500B)
#define GPIOC_DDR _ADDR_(0x500C)
#define GPIOC_CR1 _ADDR_(0x500D)
#define GPIOC_CR2 _ADDR_(0x500E)
#define GPIOD_ODR _ADDR_(0x500F)
#define GPIOD_DDR _ADDR_(0x5011)
#define GPIOD_CR1 _ADDR_(0x5012)

// Define pin mappings.
// (On-board LED, Port B)
#define TEST_PIN  5
// (SPI, Port C)
#define SPI_CS_PIN   4
#define SPI_SCK_PIN  5
#define SPI_MOSI_PIN 6
#define SPI_MISO_PIN 7
// ('4-wire' interface, Port D)
#define ILI_DC_PIN   3
#define ILI_RST_PIN  2

// OLED logo colors.
#define OLED_BLK  (0x0000)
#define OLED_LGRN (0x8628)
#define OLED_MGRN (0x5488)
#define OLED_DGRN (0x2E47)
// Color palette.
static uint16_t oled_colors[16] = {
  OLED_BLK, OLED_LGRN, OLED_MGRN, OLED_DGRN,
  0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000
};
// SSD1331 screen size.
#define SSD1331_SIZE     ((uint16_t)6144)
#define SSD1331_BUF_SIZE ((uint16_t)3072)
static const uint8_t oled_buffer[SSD1331_BUF_SIZE] = {
  // Rows 0-7.
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x02, 0x22, 0x22, 0x22, 0x22, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x33, 0x33,
  0x30, 0x11, 0x11, 0x11, 0x10, 0x22, 0x22, 0x22,
  0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x02, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
  0x00, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x33, 0x33,
  0x00, 0x11, 0x11, 0x11, 0x00, 0x22, 0x22, 0x22,
  0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x02, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
  0x22, 0x00, 0x00, 0x02, 0x20, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x33, 0x33,
  0x01, 0x11, 0x11, 0x10, 0x02, 0x22, 0x22, 0x22,
  0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x02, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
  0x22, 0x20, 0x00, 0x22, 0x20, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x33, 0x33,
  0x01, 0x11, 0x11, 0x00, 0x22, 0x22, 0x22, 0x22,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
  0x22, 0x22, 0x02, 0x22, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x33, 0x33,
  0x01, 0x11, 0x11, 0x02, 0x22, 0x22, 0x22, 0x20,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
  0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x02, 0x22,
  0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x33,
  0x01, 0x11, 0x11, 0x02, 0x22, 0x22, 0x20, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
  0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
  0x22, 0x22, 0x22, 0x20, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33,
  0x01, 0x11, 0x10, 0x02, 0x22, 0x20, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22,
  0x22, 0x20, 0x00, 0x22, 0x22, 0x20, 0x01, 0x00,
  0x22, 0x22, 0x22, 0x20, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33,
  0x01, 0x11, 0x10, 0x02, 0x22, 0x20, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  // Rows 8-15.
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22,
  0x22, 0x20, 0x02, 0x22, 0x22, 0x22, 0x00, 0x10,
  0x02, 0x22, 0x22, 0x20, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33,
  0x01, 0x11, 0x10, 0x02, 0x22, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22,
  0x22, 0x20, 0x02, 0x22, 0x22, 0x22, 0x20, 0x01,
  0x02, 0x22, 0x22, 0x20, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x33,
  0x00, 0x11, 0x10, 0x22, 0x22, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22,
  0x22, 0x20, 0x02, 0x22, 0x02, 0x22, 0x22, 0x01,
  0x02, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x33,
  0x30, 0x11, 0x10, 0x22, 0x22, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22,
  0x22, 0x20, 0x02, 0x20, 0x02, 0x22, 0x22, 0x01,
  0x02, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x33,
  0x30, 0x11, 0x10, 0x02, 0x20, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22,
  0x22, 0x22, 0x00, 0x00, 0x02, 0x22, 0x22, 0x01,
  0x00, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x33,
  0x30, 0x01, 0x10, 0x02, 0x20, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22,
  0x22, 0x22, 0x20, 0x00, 0x02, 0x22, 0x22, 0x01,
  0x00, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x33,
  0x33, 0x01, 0x10, 0x02, 0x20, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22,
  0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x01,
  0x00, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x33,
  0x33, 0x01, 0x11, 0x02, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
  0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x01,
  0x02, 0x22, 0x22, 0x00, 0x30, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x33,
  0x33, 0x00, 0x11, 0x02, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  // Rows 16-23.
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
  0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x20, 0x01,
  0x02, 0x22, 0x22, 0x00, 0x30, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x33,
  0x33, 0x30, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x20, 0x11,
  0x02, 0x22, 0x22, 0x03, 0x30, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x33, 0x33,
  0x33, 0x30, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x02, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00, 0x11,
  0x02, 0x22, 0x22, 0x03, 0x33, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x33, 0x33,
  0x33, 0x30, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x22, 0x22, 0x22, 0x22, 0x20, 0x01, 0x11,
  0x02, 0x22, 0x22, 0x03, 0x33, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x33, 0x33,
  0x33, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x11,
  0x02, 0x22, 0x22, 0x03, 0x33, 0x30, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x33, 0x33,
  0x33, 0x33, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10,
  0x02, 0x22, 0x22, 0x03, 0x33, 0x30, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x33, 0x33,
  0x33, 0x33, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10,
  0x22, 0x22, 0x22, 0x03, 0x33, 0x33, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x33, 0x33,
  0x33, 0x33, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,
  0x22, 0x22, 0x22, 0x03, 0x33, 0x33, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x03, 0x33, 0x33, 0x33,
  0x33, 0x33, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  // Rows 24-31.
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,
  0x22, 0x22, 0x22, 0x03, 0x33, 0x33, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x03, 0x33, 0x33, 0x33,
  0x33, 0x33, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x22, 0x22, 0x22, 0x03, 0x33, 0x33, 0x30, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x03, 0x33, 0x33, 0x33,
  0x33, 0x33, 0x30, 0x20, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x22, 0x22, 0x20, 0x03, 0x33, 0x33, 0x30, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x33, 0x33, 0x33, 0x33,
  0x33, 0x33, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
  0x22, 0x22, 0x20, 0x03, 0x33, 0x33, 0x33, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x33, 0x33, 0x33, 0x33,
  0x33, 0x30, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x22, 0x22, 0x20, 0x03, 0x30, 0x03, 0x33, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x33, 0x33, 0x33, 0x33,
  0x33, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x22, 0x22, 0x20, 0x00, 0x00, 0x33, 0x33, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x33, 0x33, 0x33, 0x33,
  0x33, 0x02, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x02, 0x22, 0x20, 0x22, 0x03, 0x33, 0x33, 0x30,
  0x00, 0x00, 0x00, 0x03, 0x33, 0x33, 0x33, 0x33,
  0x30, 0x02, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x02, 0x22, 0x22, 0x20, 0x03, 0x33, 0x33, 0x30,
  0x00, 0x00, 0x00, 0x00, 0x33, 0x33, 0x33, 0x33,
  0x00, 0x22, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  // Rows 32-39.
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x02, 0x22, 0x22, 0x00, 0x33, 0x33, 0x33, 0x33,
  0x00, 0x00, 0x00, 0x10, 0x33, 0x33, 0x33, 0x30,
  0x02, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x22, 0x22, 0x00, 0x33, 0x33, 0x33, 0x33,
  0x00, 0x00, 0x00, 0x10, 0x03, 0x33, 0x33, 0x00,
  0x22, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x22, 0x22, 0x03, 0x33, 0x33, 0x33, 0x33,
  0x00, 0x00, 0x00, 0x22, 0x03, 0x33, 0x00, 0x02,
  0x22, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x02, 0x22, 0x03, 0x33, 0x33, 0x33, 0x33,
  0x30, 0x00, 0x02, 0x22, 0x03, 0x30, 0x02, 0x22,
  0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x02, 0x20, 0x03, 0x33, 0x33, 0x33, 0x33,
  0x30, 0x00, 0x02, 0x22, 0x00, 0x00, 0x22, 0x22,
  0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x02, 0x00, 0x33, 0x33, 0x33, 0x33, 0x33,
  0x33, 0x00, 0x02, 0x22, 0x00, 0x02, 0x22, 0x22,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x03, 0x33, 0x33, 0x33, 0x33, 0x33,
  0x33, 0x00, 0x02, 0x22, 0x02, 0x22, 0x22, 0x20,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33,
  0x33, 0x00, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  // Rows 40-47.
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x03, 0x33, 0x33, 0x33, 0x33, 0x33,
  0x33, 0x00, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x33, 0x33, 0x33, 0x33, 0x33,
  0x30, 0x02, 0x22, 0x22, 0x22, 0x20, 0x01, 0x10,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x33, 0x33, 0x33, 0x33, 0x33,
  0x00, 0x22, 0x22, 0x22, 0x20, 0x00, 0x11, 0x10,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0x33, 0x33, 0x33, 0x30,
  0x02, 0x22, 0x22, 0x22, 0x00, 0x11, 0x11, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0x33, 0x33, 0x33, 0x30,
  0x22, 0x22, 0x22, 0x20, 0x01, 0x11, 0x11, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0x33, 0x33, 0x33, 0x00,
  0x22, 0x22, 0x20, 0x00, 0x11, 0x11, 0x11, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0x33, 0x33, 0x30, 0x02,
  0x22, 0x22, 0x00, 0x11, 0x11, 0x11, 0x10, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0x33, 0x33, 0x30, 0x22,
  0x22, 0x20, 0x01, 0x11, 0x11, 0x11, 0x10, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  // Rows 48-55.
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x33, 0x33, 0x00, 0x22,
  0x22, 0x20, 0x11, 0x11, 0x11, 0x11, 0x10, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x33, 0x33, 0x02, 0x22,
  0x22, 0x00, 0x11, 0x11, 0x11, 0x11, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x03, 0x30, 0x02, 0x22,
  0x20, 0x01, 0x11, 0x11, 0x11, 0x11, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x03, 0x30, 0x22, 0x22,
  0x20, 0x11, 0x11, 0x11, 0x11, 0x11, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x22, 0x22,
  0x00, 0x00, 0x00, 0x01, 0x11, 0x10, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22,
  0x00, 0x02, 0x22, 0x00, 0x11, 0x10, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22,
  0x02, 0x22, 0x22, 0x20, 0x01, 0x10, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x20,
  0x02, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  // Rows 56-63.
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x20,
  0x22, 0x00, 0x00, 0x22, 0x20, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x20,
  0x22, 0x22, 0x20, 0x22, 0x20, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x20,
  0x02, 0x22, 0x20, 0x22, 0x20, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22,
  0x00, 0x22, 0x00, 0x22, 0x20, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x22,
  0x20, 0x00, 0x02, 0x22, 0x20, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x22,
  0x22, 0x00, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22,
  0x22, 0x22, 0x22, 0x20, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

// The timing values are from a tutorial by 'lujji'.
// Presumably they scoped the output, but this method
// is not for precise timing; there are peripherals for that.
static inline void delay_ms(uint16_t ms) {
  uint32_t i;
  for (i=0; i<((F_CPU / 18000UL) * ms); ++i) {
    __asm__("nop");
  }
}

// Software SPI write method.
void sspi_write(uint8_t dat) {
  uint8_t i = 0x80;
  // MSB-first.
  for (i = 0x80; i != 0; i = i >> 1) {
    // Pull SCK low.
    GPIOC_ODR &= ~(1 << SPI_SCK_PIN);
    // Pull MOSI high or low, depending on data.
    if (dat & i) {
      GPIOC_ODR |=  (1 << SPI_MOSI_PIN);
    }
    else {
      GPIOC_ODR &= ~(1 << SPI_MOSI_PIN);
    }
    // Pull SCK high.
    GPIOC_ODR |=  (1 << SPI_SCK_PIN);
  }
}

void sspi_cmd(uint8_t dat) {
  // Pull DC low.
  GPIOD_ODR &= ~(1 << ILI_DC_PIN);
  // Send data.
  sspi_write(dat);
  // Pull DC high.
  GPIOD_ODR |=  (1 << ILI_DC_PIN);
}

void main() {
  // 'Fill Screen' variables.
  uint16_t di = 0;
  uint8_t px_col = 0;
  uint16_t px_val = 0;

  // Set the test LED pin on port B to open-drain output.
  GPIOB_DDR |= (1 << TEST_PIN);
  GPIOB_CR1 &= ~(1 << TEST_PIN);
  // Set the 'test' LED on to start.
  GPIOB_ODR &= ~(1 << TEST_PIN);

  // Setup the SPI pins. This is a test software SPI
  // implementation, so the peripheral will not be used.
  // Instead, SCK/MOSI/CS are push-pull 10MHz output while
  // MISO is not used.
  // CS/SCK/MOSI.
  GPIOC_DDR |=  ((1 << SPI_CS_PIN)  |
                 (1 << SPI_SCK_PIN) |
                 (1 << SPI_MOSI_PIN));
  GPIOC_CR1 |=  ((1 << SPI_CS_PIN)  |
                 (1 << SPI_SCK_PIN) |
                 (1 << SPI_MOSI_PIN));
  GPIOC_CR2 |=  ((1 << SPI_CS_PIN)  |
                 (1 << SPI_SCK_PIN) |
                 (1 << SPI_MOSI_PIN));
  // MISO.
  //GPIOC_DDR &=  ~(1 << SPI_MISO_PIN);
  //GPIOC_CR1 &=  ~(1 << SPI_MISO_PIN);

  // DC and Reset pins can be configured as push-pull output.
  GPIOD_DDR |=  ((1 << ILI_DC_PIN) |
                 (1 << ILI_RST_PIN));
  GPIOD_CR1 |=  ((1 << ILI_DC_PIN) |
                 (1 << ILI_RST_PIN));

  // SSD1331 initialization.
  // Pin starting states:
  // - DC: 1, CS: 1, MOSI: 0, SCK: 1, MISO: [N/A]
  GPIOD_ODR |=  (1 << ILI_DC_PIN);
  GPIOC_ODR |=  (1 << SPI_CS_PIN);
  GPIOC_ODR &= ~(1 << SPI_MOSI_PIN);
  GPIOC_ODR |=  (1 << SPI_SCK_PIN);
  // Reset the display by pulling the reset pin high/low/high.
  GPIOD_ODR |=  (1 << ILI_RST_PIN);
  delay_ms(250);
  GPIOD_ODR &= ~(1 << ILI_RST_PIN);
  delay_ms(250);
  GPIOD_ODR |=  (1 << ILI_RST_PIN);
  delay_ms(250);
  // Pull CS low.
  GPIOC_ODR &= ~(1 << SPI_CS_PIN);

  // Initialization sequence.
  // For testing, just send the raw hex values.
  // ('Unlock display')
  sspi_cmd(0xFD);
  sspi_cmd(0x12);
  // (Turn the display off.)
  sspi_cmd(0xAE);

  sspi_cmd(0x15);
  sspi_cmd(0x00);
  sspi_cmd(0x5F);
  sspi_cmd(0x75);
  sspi_cmd(0x00);
  sspi_cmd(0x3F);
  sspi_cmd(0x81);
  sspi_cmd(0x80);
  sspi_cmd(0x82);
  sspi_cmd(0x60);
  sspi_cmd(0x83);
  sspi_cmd(0x80);
  sspi_cmd(0x87);
  sspi_cmd(0x08);
  sspi_cmd(0x8A);
  sspi_cmd(0x80);
  sspi_cmd(0x8B);
  sspi_cmd(0x60);
  sspi_cmd(0x8C);
  sspi_cmd(0x80);
  sspi_cmd(0xA0);
  sspi_cmd(0x60);
  sspi_cmd(0xA1);
  sspi_cmd(0x00);
  sspi_cmd(0xA2);
  sspi_cmd(0x00);
  sspi_cmd(0xA4);
  sspi_cmd(0xA8);
  sspi_cmd(0x3F);
  sspi_cmd(0xAB);
  sspi_cmd(0x8E);
  sspi_cmd(0xB0);
  sspi_cmd(0x0B);
  sspi_cmd(0xB1);
  sspi_cmd(0x74);
  sspi_cmd(0xB3);
  sspi_cmd(0xD0);
  sspi_cmd(0xB9);
  sspi_cmd(0xBB);
  sspi_cmd(0x3E);
  sspi_cmd(0xBE);
  sspi_cmd(0x3E);
  sspi_cmd(0xAF);

  // Toggle the test LED to indicate completion of screen setup.
  GPIOB_ODR ^= (1 << TEST_PIN);

  // Main loop.
  while (1) {
    // Toggle the LED each step.
    GPIOB_ODR ^= (1 << TEST_PIN);
    // Fill the screen and increment the color.
    for (di = 0; di < SSD1331_BUF_SIZE; ++di) {
      px_col = oled_buffer[di] >> 4;
      px_val = oled_colors[px_col];
      sspi_write(px_val >> 8);
      sspi_write(px_val & 0x00FF);
      px_col = oled_buffer[di] & 0x0F;
      px_val = oled_colors[px_col];
      sspi_write(px_val >> 8);
      sspi_write(px_val & 0x00FF);
    }
  }
}
