#include "ECCAPP.h"



const BYTE baEASYCARDLogo[] = {//Width=382, Height=61
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
    0x80, 0x80, 0xC0, 0xC0, 0xE0, 0xE0, 0xF0, 0xF0, 0xF0, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x0F, 0x0F, 0x0F,
    0x8F, 0xEF, 0xE7, 0xE7, 0xC7, 0x87, 0x03, 0x03, 0xFF, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0x70, 0xF8,
    0xFE, 0x03, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x20, 0x30, 0x18, 0x8E, 0x8F, 0x8D, 0x0C, 0x0C, 0x8C,
    0xEC, 0x3C, 0x0C, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x70, 0x71, 0x73, 0xF3, 0x70, 0x00,
    0x00, 0x06, 0xFE, 0xFE, 0x87, 0x86, 0x86, 0x86, 0x00, 0x30, 0x1C, 0xC6, 0xC7, 0xC6, 0xC6, 0xC6,
    0xC6, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x47, 0x47, 0xC7, 0x07, 0x07, 0xFF, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0x3F, 0x07, 0x07, 0x07, 0x07, 0x07, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x80, 0xC0, 0xF0, 0x1E, 0x07, 0x01, 0x80, 0xC0, 0x70, 0x38, 0x0F, 0x02, 0x00, 0x00,
    0x07, 0x07, 0x07, 0x0F, 0x38, 0x60, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x1C,
    0x1C, 0x1C, 0x1C, 0x1C, 0x9C, 0xFC, 0xBC, 0x9E, 0x9F, 0x9C, 0x9C, 0x9C, 0x9C, 0x9C, 0x9C, 0x9C,
    0x9C, 0x9C, 0x9C, 0x9C, 0x1C, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x07, 0x07, 0x87,
    0xE7, 0x3F, 0x07, 0x00, 0x00, 0xFF, 0xFF, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
    0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0x70, 0x38, 0x0E,
    0x02, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x1E, 0x78, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x67, 0x67, 0x67, 0x67, 0x67, 0x67, 0x67, 0x67, 0x67, 0x67, 0x67,
    0x67, 0x67, 0x67, 0x67, 0x67, 0x67, 0x67, 0x07, 0x07, 0x07, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
    0xE0, 0xE0, 0xF0, 0xF0, 0xF8, 0xF8, 0xFC, 0xFE, 0x7E, 0x3E, 0x3E, 0x1E, 0x0C, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xF8, 0xFC, 0xFF,
    0xFF, 0xFF, 0xFF, 0x7F, 0x1F, 0x07, 0x00, 0x00, 0x00, 0x07, 0x03, 0x00, 0x00, 0x00, 0x80, 0xC0,
    0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F,
    0x7F, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x10, 0x30, 0x18, 0x18, 0x09, 0x0D, 0x07, 0x07, 0x07,
    0x0C, 0x0C, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x7C, 0x77, 0x71, 0xF0, 0x00,
    0x00, 0xE0, 0x7F, 0x01, 0x01, 0x01, 0xFF, 0x1F, 0x00, 0x00, 0x30, 0x30, 0x30, 0xFC, 0x36, 0x33,
    0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E,
    0xFF, 0xFF, 0xCE, 0x8E, 0x8E, 0x8E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xC0, 0xC0, 0xC1, 0x73, 0x7B, 0xFF, 0x00, 0x00, 0xE4, 0xE7,
    0xE3, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE7, 0xE7, 0xE7, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x0E, 0x03, 0x03, 0xFF, 0x00, 0x00, 0x01, 0x03, 0x02, 0x0E, 0x0E, 0x0E, 0x0E, 0xFE, 0x1E,
    0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0xFE, 0x3E, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x20, 0x30, 0x30,
    0x18, 0x1C, 0x1E, 0xFF, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33,
    0x33, 0x33, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x01,
    0x07, 0xBC, 0xF0, 0x00, 0x00, 0xFF, 0xFF, 0x0C, 0x0C, 0x0C, 0x0C, 0xEC, 0x8C, 0x0C, 0x0C, 0x8C,
    0xCF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0E, 0x07, 0x03, 0x01, 0x00, 0x00, 0x80,
    0xE0, 0x38, 0x1E, 0x06, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x01, 0x07, 0x06, 0x0C, 0x0C,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E,
    0x0E, 0x0E, 0x0E, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
    0x3F, 0x7F, 0xFF, 0xE7, 0xC1, 0x81, 0x00, 0x08, 0x1E, 0x1E, 0x1F, 0x3F, 0x1F, 0x1F, 0x1F, 0x3F,
    0x3F, 0x3F, 0x3F, 0x7E, 0x7E, 0x7C, 0xF8, 0xF0, 0xC0, 0x00, 0x00, 0x1F, 0x7F, 0x1F, 0x0F, 0xC3,
    0xE3, 0xF1, 0xF8, 0xF8, 0xFC, 0xFE, 0xFE, 0xFE, 0xFC, 0xFC, 0xFC, 0xFC, 0xF8, 0xF0, 0xE0, 0xC3,
    0x87, 0x0F, 0x1F, 0x3E, 0x7C, 0xF8, 0xF0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x38, 0x0E,
    0x02, 0x00, 0x00, 0x7F, 0xFF, 0xC0, 0xC0, 0xC0, 0xC1, 0xC3, 0xC6, 0xC4, 0xC0, 0xE0, 0x70, 0x00,
    0x01, 0x07, 0x1C, 0x70, 0x40, 0x00, 0x00, 0x00, 0x00, 0x40, 0x60, 0x30, 0x1C, 0x1F, 0x19, 0x30,
    0x73, 0x61, 0x60, 0xE0, 0xE6, 0xE6, 0xE3, 0xE0, 0xE0, 0xE0, 0xE2, 0xE6, 0xE6, 0xE7, 0xE0, 0xE0,
    0xE0, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x06, 0x06, 0x0E, 0x0C, 0x08, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F, 0x01, 0x01, 0x40, 0xC0, 0xC0, 0xFF, 0x00, 0x00, 0x80, 0x80,
    0xC3, 0xC6, 0x6C, 0x78, 0x78, 0x78, 0x6C, 0xC6, 0xC3, 0x81, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x40, 0x60, 0x30, 0x38, 0x1C, 0x07, 0x01, 0x00,
    0x60, 0xE0, 0xE0, 0xE0, 0xF0, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x40, 0xE0, 0x38, 0x1F, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x67, 0xE7, 0xE7,
    0xE7, 0xE7, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x07,
    0x07, 0x03, 0x01, 0x00, 0x00, 0x7F, 0xFF, 0x60, 0x70, 0x30, 0x30, 0x01, 0x03, 0x0F, 0x1B, 0x31,
    0x61, 0x60, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xE0, 0xF0, 0xFC, 0xE6, 0x63,
    0x60, 0x60, 0x60, 0x60, 0x60, 0x70, 0x30, 0x30, 0x31, 0x37, 0x3E, 0x38, 0xE0, 0xC0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
    0x07, 0x07, 0x07, 0x07, 0x07, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xFF, 0x3F, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0xF0, 0xFC, 0xFC, 0xFE, 0xFE, 0xFE, 0xF8, 0x60,
    0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xC0, 0xE0, 0xE1,
    0xF1, 0x78, 0x78, 0x3E, 0x3F, 0x1F, 0x0F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x3C, 0xF8, 0xE0, 0xC0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xF8, 0xFE, 0x7F, 0x7F, 0x3F, 0x3F, 0x1F, 0x0F, 0x07, 0x03, 0x01, 0x00,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x01, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xFF, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xF0, 0x1C, 0x03,
    0x03, 0x1C, 0xF0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x66, 0xC3, 0xC3, 0x83, 0x83, 0x02,
    0x00, 0x00, 0x00, 0x03, 0x0E, 0x38, 0xE0, 0x80, 0x80, 0x60, 0x30, 0x0C, 0x03, 0x00, 0x00, 0x00,
    0xF8, 0x0C, 0x06, 0x02, 0x03, 0x03, 0x03, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xF0,
    0x1C, 0x03, 0x03, 0x1C, 0xF0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xC3, 0xC3, 0xC3, 0xC3,
    0xC3, 0x43, 0x36, 0x1C, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x02,
    0x06, 0x0C, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x0C, 0x06, 0x02,
    0x03, 0x03, 0x03, 0x03, 0x02, 0x00, 0x00, 0x00, 0xC0, 0xF8, 0x0C, 0x06, 0x02, 0x03, 0x03, 0x03,
    0x03, 0x02, 0x06, 0x0C, 0xF8, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0x43,
    0x36, 0x1C, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x83, 0x83, 0x83, 0x83, 0x83, 0x82, 0x6E, 0x38, 0x00,
    0x00, 0xC0, 0xF8, 0x0C, 0x06, 0x02, 0x03, 0x03, 0x03, 0x03, 0x02, 0x06, 0x0C, 0xF8, 0x00, 0x00,
    0x00, 0x00, 0xFF, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0x43, 0x36, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0xF0, 0x1C, 0x03, 0x03, 0x1C, 0xF0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03,
    0xFF, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x03, 0xFF, 0x03, 0x03, 0x00, 0x00, 0xC0, 0xF8, 0x0C,
    0x06, 0x02, 0x03, 0x03, 0x03, 0x03, 0x02, 0x06, 0x0C, 0xF8, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x07,
    0x06, 0x0C, 0x30, 0x60, 0x80, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x1F, 0x3E,
    0xFC, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xFC, 0xFC, 0xFC, 0xFE, 0xFE, 0xFF, 0x7F, 0x3F,
    0x3F, 0x1F, 0x0F, 0x0F, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x3F, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x30, 0x1E, 0x07, 0x06, 0x06, 0x06,
    0x06, 0x06, 0x06, 0x07, 0x1E, 0x30, 0x00, 0x00, 0x00, 0x10, 0x30, 0x30, 0x30, 0x31, 0x11, 0x1F,
    0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x07, 0x0C, 0x18, 0x10, 0x30, 0x30, 0x30, 0x30, 0x10, 0x00, 0x00, 0x00, 0x30, 0x1E, 0x07, 0x06,
    0x06, 0x06, 0x06, 0x06, 0x06, 0x07, 0x1E, 0x30, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x03, 0x06, 0x18, 0x30, 0x20, 0x00, 0x00, 0x3F, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x18,
    0x18, 0x0C, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0C, 0x18, 0x10,
    0x30, 0x30, 0x30, 0x30, 0x10, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0C, 0x18, 0x10, 0x30, 0x30, 0x30,
    0x30, 0x10, 0x18, 0x0C, 0x07, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03,
    0x06, 0x18, 0x30, 0x20, 0x00, 0x00, 0x3F, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x07, 0x0C, 0x18, 0x10, 0x30, 0x30, 0x30, 0x30, 0x10, 0x18, 0x0C, 0x07, 0x00, 0x00,
    0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x06, 0x18, 0x30, 0x20, 0x20, 0x30, 0x1E,
    0x07, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x07, 0x1E, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x3F, 0x30, 0x30, 0x00, 0x00, 0x00, 0x07, 0x0C,
    0x18, 0x10, 0x30, 0x30, 0x30, 0x30, 0x10, 0x18, 0x0C, 0x07, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x0C, 0x18, 0x38, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};


BYTE pPtr[384 * 24 * 30];
//BYTE pPtrReceipt[384*30*30];
CTOS_FONT_ATTRIB stFONT_ATTRIB;
USHORT offsetX = 0;
USHORT offsetY = 0;
BYTE FONT_Height;
BYTE FONT_Width;

void PrintEASYCARDLOGO() {


    CTOS_PrinterLogo((BYTE *) baEASYCARDLogo, 0, 382, 7);
    //    CTOS_PrinterBufferLogo (offsetX, offsetY, 382,61, (BYTE *)baEASYCARDLogo );

    //   offsetY+=64;
    //    USHORT  usRtn= CTOS_PrinterBufferOutput(baEASYCARDLogo,offsetY/8);
    //      CTOS_PrinterFline(16);
    return;
}

void PrintDateTime(STR *Date, STR * Time) {

    BYTE DateTimeStr[64];
    TRANS_DATA2 TransData;
    STR yy[4 + 1], mm[2 + 1], dd[2 + 1], hh[2 + 1], min[2 + 1], ss[2 + 1];
    yy[4] = 0;
    mm[2] = 0;
    dd[2] = 0;
    hh[2] = 0;
    min[2] = 0;
    ss[2] = 0;
    memcpy(yy, &Date[0], 4);
    memcpy(mm, &Date[4], 2);
    memcpy(dd, &Date[6], 2);
    memcpy(hh, &Time[0], 2);
    memcpy(min, &Time[2], 2);
    memcpy(ss, &Time[4], 2);
    memset(DateTimeStr, 0x00, sizeof (DateTimeStr));
    sprintf(DateTimeStr, "交易時間:%4s/%2s/%2s  %2s:%2s:%2s", yy, mm, dd, hh, min, ss);

    BYTE height = d_FONT_12x24 & 0x00ff;
    BYTE width = d_FONT_12x24 >> 8;
    PrintStr(1, offsetY, DateTimeStr, d_FONT_12x24, FALSE);
    offsetY = offsetY + height + 2;

    //CTOS_PrinterPutString(DateTimeStr);    
}

void PrintDateTime2(STR *Date, STR * Time, USHORT FontSize) {

    BYTE DateTimeStr[64];
    TRANS_DATA2 TransData;
    STR yy[4 + 1], mm[2 + 1], dd[2 + 1], hh[2 + 1], min[2 + 1], ss[2 + 1];
    yy[4] = 0;
    mm[2] = 0;
    dd[2] = 0;
    hh[2] = 0;
    min[2] = 0;
    ss[2] = 0;
    memcpy(yy, &Date[0], 4);
    memcpy(mm, &Date[4], 2);
    memcpy(dd, &Date[6], 2);
    memcpy(hh, &Time[0], 2);
    memcpy(min, &Time[2], 2);
    memcpy(ss, &Time[4], 2);
    memset(DateTimeStr, 0x00, sizeof (DateTimeStr));
    sprintf(DateTimeStr, "交易時間:%4s/%2s/%2s  %2s:%2s:%2s", yy, mm, dd, hh, min, ss);

    BYTE height = FontSize & 0x00ff;
    BYTE width = FontSize >> 8;
    PrintStr(1, offsetY, DateTimeStr, FontSize, FALSE);
    offsetY = offsetY + height + 2;

    //CTOS_PrinterPutString(DateTimeStr);    
}

void GetDateTimeStr(STR *Date, STR * Time, STR *DateTimeStr) {

    STR yy[4 + 1], mm[2 + 1], dd[2 + 1], hh[2 + 1], min[2 + 1], ss[2 + 1];
    yy[4] = 0;
    mm[2] = 0;
    dd[2] = 0;
    hh[2] = 0;
    min[2] = 0;
    ss[2] = 0;
    memcpy(yy, &Date[0], 4);
    memcpy(mm, &Date[4], 2);
    memcpy(dd, &Date[6], 2);
    memcpy(hh, &Time[0], 2);
    memcpy(min, &Time[2], 2);
    memcpy(ss, &Time[4], 2);
    memset(DateTimeStr, 0x00, sizeof (DateTimeStr));
    sprintf(DateTimeStr, "%2s/%2s  %2s:%2s:%2s", mm, dd, hh, min, ss);

}

USHORT CheckPrintStatus() {

    USHORT usRet = CTOS_PrinterStatus();
    switch (usRet) {
        case d_OK:

            break;
        case d_PRINTER_HEAD_OVERHEAT:
            usRet = ErrorMessageBox(gTransTitle, "", "印表機過熱", "請稍候", "", d_MB_CHECK);
            while (1) {
                usRet = CTOS_PrinterStatus();
                if (usRet != d_PRINTER_HEAD_OVERHEAT)
                    break;
            };
            break;
        case d_PRINTER_PAPER_OUT:

            usRet = ErrorMessageBox(gTransTitle, "", "印表機缺紙", "請更換紙卷", "", d_MB_CHECK);
            break;
        case d_PRINTER_BARCODE_GENERATE_ERR:


            break;
        case d_PRINTER_BARCODE_CONTENT_ERR:

            break;
        case d_PRINTER_BARCODE_CONTENT_LEN_ERR:

            break;
        case d_PRINTER_BARCODE_OUTSIDE_PAPER:
            break;
    }
    return usRet;
}

void SetPrintConfig() {
    USHORT usRtn;
    // pPtr= malloc(64*1024);

    usRtn = CTOS_PrinterFontSelectMode(d_FONT_TTF_MODE);
    usRtn = CTOS_PrinterTTFSelect(d_FONT_TTF, 0);

    CTOS_PrinterBufferEnable();
    usRtn = CTOS_PrinterBufferInit(pPtr, PB_CANVAS_Y_SIZE * 30);
    usRtn = CTOS_PrinterBufferSelectActiveAddress(pPtr);
    memset(pPtr, 0x00, sizeof (64 * 1024));
    // usRtn =CTOS_LanguagePrinterFontSize ( d_FONT_12x24,  0,d_FONT_NO_SET_TYPE );//9*18CTOS_LanguagePrinterGetFontInfo ( USHORT *usASCIIFontID,

    return;
}

void SystemCheck(STR *RS232STR) {
    USHORT usRtn;
    BYTE tmpbuf[64];
    // BYTE pPtr[384*24*15];
    SetPrintConfig();

    CTOS_FONT_ATTRIB stFONT_ATTRIB;
    stFONT_ATTRIB.FontSize = Med_Font_Size; // Font Size = 12x24
    stFONT_ATTRIB.X_Zoom = 1; // The width magnifies X_Zoom diameters
    stFONT_ATTRIB.Y_Zoom = 1; // The height magnifies Y_Zoom diameters
    stFONT_ATTRIB.X_Space = 0; // The width of the space between the font with next
    stFONT_ATTRIB.Y_Space = 0; // The  0, 0, 384,1 );

    usRtn = CheckPrintStatus();
    if (usRtn != d_OK) return;
    PrintTitle();
    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    sprintf(tmpbuf, "======================================");
    PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
    FONT_Height = d_FONT_12x24 & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;
    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    sprintf(tmpbuf, "印表機測試:正常");
    PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
    FONT_Height = d_FONT_12x24 & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;

    PrintStr(1, offsetY, RS232STR, d_FONT_12x24, FALSE);
    FONT_Height = d_FONT_12x24 & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;
    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    sprintf(tmpbuf, "======================================");
    PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
    FONT_Height = d_FONT_12x24 & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;
    CTOS_PrinterBufferOutput(pPtr, (offsetY / 8));
    CTOS_PrinterFline(64);
    //free(pPtr);
    return;
}

void PrintStr(int XPos, int YPOS, STR * field, USHORT usFontSize, BYTE bframe) {
    USHORT usRtn;


    stFONT_ATTRIB.FontSize = usFontSize; // Font Size = 12x24
    stFONT_ATTRIB.X_Zoom = 1; // The width magnifies X_Zoom diameters
    stFONT_ATTRIB.Y_Zoom = 1; // The height magnifies Y_Zoom diameters
    stFONT_ATTRIB.X_Space = 0; // The width of the space between the font with next
    stFONT_ATTRIB.Y_Space = 0; // The  0, 0, 384,1 );
    BYTE height = usFontSize & 0x00ff;
    BYTE width = usFontSize >> 8;
    /*
      if(bframe)
      {
          usRtn= CTOS_PrinterBufferHLine ( offsetX, offsetY, 383,1 );
          usRtn= CTOS_PrinterBufferHLine ( offsetX, offsetY+Y+3, 383,1 );
          usRtn=CTOS_PrinterBufferVLine(offsetX,offsetY,Y+2,1);
          usRtn=CTOS_PrinterBufferVLine(383,offsetY,Y+2,1);
      } 
     */
    usRtn = CTOS_PrinterBufferPutString(pPtr, XPos + 1, YPOS, field, &stFONT_ATTRIB);
    //usRtn= CTOS_PrinterBufferPutString(pPtr, 192,offsetY,field2, &stFONT_ATTRIB );
    // offsetX=0;
    // offsetY=offsetY+height+2;
    //usRtn= CTOS_PrinterBufferOutput(pPtr,Y/8);

}

void Printline(STR *field1, STR * field2, USHORT usFontSize, BYTE bframe) {
    USHORT usRtn;


    stFONT_ATTRIB.FontSize = usFontSize; // Font Size = 12x24
    stFONT_ATTRIB.X_Zoom = 1; // The width magnifies X_Zoom diameters
    stFONT_ATTRIB.Y_Zoom = 1; // The height magnifies Y_Zoom diameters
    stFONT_ATTRIB.X_Space = 0; // The width of the space between the font with next
    stFONT_ATTRIB.Y_Space = 0; // The  0, 0, 384,1 );
    BYTE Y = usFontSize & 0x00ff;
    BYTE X = usFontSize >> 8;

    if (bframe) {
        usRtn = CTOS_PrinterBufferHLine(offsetX, offsetY, 383, 1);
        usRtn = CTOS_PrinterBufferHLine(offsetX, offsetY + Y + 3, 383, 1);
        usRtn = CTOS_PrinterBufferVLine(offsetX, offsetY, Y + 2, 1);
        usRtn = CTOS_PrinterBufferVLine(383, offsetY, Y + 2, 1);
    }

    usRtn = CTOS_PrinterBufferPutString(pPtr, 1, offsetY, field1, &stFONT_ATTRIB);
    usRtn = CTOS_PrinterBufferPutString(pPtr, 192, offsetY, field2, &stFONT_ATTRIB);
    offsetX = 0;
    offsetY = offsetY + Y + 2;
    //usRtn= CTOS_PrinterBufferOutput(pPtr,Y/8);

}

void Drawline(int height) {
    int i = 0;
    for (i = 0; i < height; i++) {
        CTOS_PrinterBufferHLine(0, offsetY + height, 383, 1);
    }
    offsetY = offsetY + height + 2;
}

void PrintTitle() {
    ezxml_t TAG;
    USHORT usRtn;
    BYTE tmpbuf[64], tmpbuf2[64];
    BYTE TerminalID[64 + 1];

    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    memset(tmpbuf2, 0x00, sizeof (tmpbuf2));
    sprintf(tmpbuf, "特店名稱:%s", gConfig.TM.TITLE);
    PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
    FONT_Height = d_FONT_12x24 & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;

    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    memset(tmpbuf2, 0x00, sizeof (tmpbuf2));
    sprintf(tmpbuf, "分店名稱:%s", gConfig.TM.SUBTITLE);
    PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
    FONT_Height = d_FONT_12x24 & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;

    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    memset(tmpbuf2, 0x00, sizeof (tmpbuf2));
    int MERCHANTID = atoi(gConfig.MERCHANT.MERCHANTID);
    int NewLocationID = atoi(gConfig.MERCHANT.NewLocationID);
    int STCODE = atoi(gConfig.MERCHANT.STCODE);
    sprintf(tmpbuf, "特店代號:%08d-%03d-%010d", MERCHANTID, NewLocationID, STCODE);
    PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
    FONT_Height = d_FONT_12x24 & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;

    //GetBatchTotal_DevID((BYTE *) gTransData.ucCPUDeviceID);//kobe removed it for V2
    memset(TerminalID, 0x00, sizeof (TerminalID));

    fnBINTODEVASC((char *) gBatchTotal.DEVICEID, TerminalID, 16, LEVEL2);
    sprintf(tmpbuf, "設備編號:%s", TerminalID);
    PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
    FONT_Height = d_FONT_12x24 & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;

}

void PrintRemark() {
    USHORT FontSize = 0x0C18;
    FONT_Height = FontSize & 0x00ff;
    BYTE tmpbuf[64];
    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    sprintf(tmpbuf, "%s", gConfig.TM.RECEIPTREMARK.STRING1);
    PrintStr(1, offsetY, tmpbuf, 0x0C18, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    memset(tmpbuf, 0x00, sizeof (tmpbuf));

    sprintf(tmpbuf, "%s", gConfig.TM.RECEIPTREMARK.STRING2);
    PrintStr(1, offsetY, tmpbuf, 0x0C18, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    memset(tmpbuf, 0x00, sizeof (tmpbuf));

    sprintf(tmpbuf, "%s", gConfig.TM.RECEIPTREMARK.STRING3);
    PrintStr(1, offsetY, tmpbuf, 0x0C18, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    memset(tmpbuf, 0x00, sizeof (tmpbuf));

    sprintf(tmpbuf, "%s", gConfig.TM.RECEIPTREMARK.STRING4);
    PrintStr(1, offsetY, tmpbuf, 0x0C18, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    memset(tmpbuf, 0x00, sizeof (tmpbuf));

    sprintf(tmpbuf, "%s", gConfig.TM.RECEIPTREMARK.STRING5);
    PrintStr(1, offsetY, tmpbuf, 0x0C18, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    return;
}

void PrintReceipt() {
    int i = 0;
    int ReceiptNum;
    int result;

    if ((gScrpitTesting == 1)) {
        STR * printflag = (STR*) ezxml_attr(gTestAction, "PRINT");
        if ((printflag != NULL) && (strcmp(printflag, "0") == 0))
            return;
    }

    //2014.04.07, kobe added for ECR, response to POS first
    if (ecrObj.gData.isEcrTxn) {
        //if process come to "print receipt" means that txn was success 
        sprintf(ecrObj.ngData->responseCode, "0000");
        if ((result = ecrObj.successResponse(&ecrObj)) != d_OK && !ecrObj.ngData->response2Pos) {
            ecrObj.errorResponse(&ecrObj, result);
        }

        if (memcmp(ecrObj.ngData->doesNeedToPrintReceipt, "NO", 2) == 0)
            return;
    }

    BYTE key;
    BYTE buf[2 + 1];
    memset(buf, 0x00, sizeof (buf));
    ReceiptNum = atoi(gConfig.TM.RECEIPTNUM);

    CTOS_KBDBufFlush();
    for (i = 0; i < ReceiptNum; i++) {

        Receipt(i, 0);

        if (i < ReceiptNum - 1) {
            ShowMessage3line(gTransTitle, "請撕下收據", "並按下任意鍵", "列印下一張收據", TYPE_ECR_FORCE_TO_CONFIRM_ANY_KEY);
        }

    }
    return;

}

void RePrintReceipt() {

    USHORT ret;
    int ReceiptNum;
    sprintf(gTransTitle, "重印帳單");

    do {
        ret = GetLastTransData(&gTransData);
        if (ret != d_OK) {
            ShowMessage(gTransTitle, "目前無交易!!", TYPE_ECR_FORCE_TO_CONFIRM_ANY_KEY);
            return;
        }
    } while (gTransData.ucTXTYPE == TXTYPE_LOCKCARD);

    BYTE buf[2 + 1];
    memset(buf, 0x00, sizeof (buf));

    ReceiptNum = atoi(gConfig.TM.RECEIPTNUM);

    int i;
    for (i = 0; i < ReceiptNum; i++) {
        Receipt(i, 1);
        if (i < ReceiptNum - 1)
            ShowMessage3line(gTransTitle, "請撕下收據", "並按下任意鍵", "列印下一張收據", TYPE_ECR_FORCE_TO_CONFIRM_ANY_KEY);
    }

}

void thread_PrintLastReceipt() {
    Receipt(1, 0);
    pthread_exit(NULL);
}

void Receipt(int ReceiptType, BYTE Reprint) {

    USHORT usRtn;


    BYTE tmpbuf[64], tmpbuf2[64];
    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    memset(tmpbuf2, 0x00, sizeof (tmpbuf2));
    CTOS_RTC SetRTC;
    BYTE CardID[17 + 1];
    BYTE Title[24];

    SetPrintConfig();


    // memset(pPtr,0x00,sizeof(pPtr));

    offsetY = 0;
    offsetX = 0;
    BYTE FONT_Height = Med_Font_Size & 0x00ff;
    BYTE FONT_Width = Med_Font_Size >> 8;
    stFONT_ATTRIB.FontSize = Med_Font_Size; // Font Size = 12x24
    stFONT_ATTRIB.X_Zoom = 1; // The width magnifies X_Zoom diameters
    stFONT_ATTRIB.Y_Zoom = 1; // The height magnifies Y_Zoom diameters
    stFONT_ATTRIB.X_Space = 0; // The width of the space between the font with next
    stFONT_ATTRIB.Y_Space = 0; // The  0, 0, 384,1 );
    //   CTOS_PrinterSetHeatLevel(5);


    if ((strcmp(gConfig.TX.OPERATIONMODE, "AUTO_BYTYPE") != 0) && (strcmp(gConfig.TX.OPERATIONMODE, "AUTO_FIX") != 0))
        usRtn = CheckPrintStatus();

    PrintEASYCARDLOGO();

    PrintTitle();


    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    sprintf(tmpbuf, "===========================");
    PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
    FONT_Height = d_FONT_12x24 & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;
    if (strcmp(gConfig.TX.OPERATIONMODE, "BARCODESCANNER") == 0) {
        sprintf(tmpbuf, "收銀機交易編號:%s", gTransData.ucTMINVOICENO);
        PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
        offsetY = offsetY + FONT_Height + 2;
    }
    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    memset(tmpbuf2, 0x00, sizeof (tmpbuf2));
    sprintf(tmpbuf, "批次號碼       :%s", gTransData.ucBatchNo);
    sprintf(tmpbuf2, "交易序號:%06ld", gTransData.usTXSN);
    PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
    PrintStr(228, offsetY, tmpbuf2, d_FONT_12x24, FALSE);
    FONT_Height = d_FONT_12x24 & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;
    // Printline(tmpbuf,tmpbuf2,d_FONT_12x24,FALSE);

    /*
    if(ecrObj.gData.isEcrTxn)
    {
        sprintf(tmpbuf,"收銀機交易序號: %ld",ecrObj.ngData->tmTxnSn);
        PrintStr(1,offsetY,tmpbuf,d_FONT_12x24,FALSE);
        offsetY=offsetY+FONT_Height+2;
    }
     */

    vGetTxTitleStr(gTransData.ucTXTYPE, Title);
    sprintf(tmpbuf, "交易類別       :%s", Title);

    if (strlen(gTransData.ucTxnAuthNum) <= 0)
        sprintf(tmpbuf2, "授權碼:000000");
    else
        sprintf(tmpbuf2, "授權碼:%s", gTransData.ucTxnAuthNum);
    PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
    PrintStr(228, offsetY, tmpbuf2, d_FONT_12x24, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    memset(tmpbuf2, 0x00, sizeof (tmpbuf2));
    sprintf(tmpbuf, "設備交易序號:%s", gTransData.ucRRN);

    PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);

    offsetY = offsetY + FONT_Height + 2;

    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    memset(tmpbuf2, 0x00, sizeof (tmpbuf2));
    memset(CardID, 0x00, sizeof (CardID));


    vdUIntToAsc2(gTransData.ucCardID, sizeof (gTransData.ucCardID), CardID, 10); //n_Card Physical ID
    if (ReceiptType == 0) {
        int i = 0;
        int offset1 = strlen(CardID) - 3 - 4 - 1;
        for (i = 0; i < 3; i++) {
            CardID[offset1 + i] = '*';
        }
    }
    sprintf(tmpbuf, "悠遊卡晶片號:%s", CardID);
    PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    if (strcmp(gConfig.TX.OPERATIONMODE, "AUTO_BYTYPE") == 0) {
        BYTE strPersonalProfileName[32];
        // int CardProfile=atoi(gTransData.ucBasicData_CardProfile);
        // int CardType=atoi(gTransData.ucBasicData_CardType);
        memset(strPersonalProfileName, 0x00, sizeof (strPersonalProfileName));
        GetCard_PersonalProfile(strPersonalProfileName);
        sprintf(tmpbuf, "卡片種類      :%s", strPersonalProfileName);
        PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
        offsetY = offsetY + FONT_Height + 2;
    }

    sprintf(tmpbuf, "卡片交易序號:%ld", gTransData.ulCardTxnSN);
    PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    memset(tmpbuf2, 0x00, sizeof (tmpbuf2));

    if (gAutoloadAMT > 0) {

        sprintf(tmpbuf, "交易前餘額   :%4ld", gEVBeforeAutoload);
        PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
        offsetY = offsetY + FONT_Height + 2;

        memset(tmpbuf, 0x00, sizeof (tmpbuf));
        memset(tmpbuf2, 0x00, sizeof (tmpbuf2));

        sprintf(tmpbuf, "自動加值   :%4ld", gAutoloadAMT);
        sprintf(tmpbuf2, "交易金額:%4ld", gTransData.lTxnAmt);
        PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
        PrintStr(192, offsetY, tmpbuf2, d_FONT_16x30, FALSE);
        FONT_Height = d_FONT_16x30 & 0x00ff;
        offsetY = offsetY + FONT_Height + 2;
    } else {
        sprintf(tmpbuf, "交易前餘額   :%4ld", gTransData.lEVBeforeTxn);
        sprintf(tmpbuf2, "交易金額:%4ld", gTransData.lTxnAmt);
        PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
        PrintStr(192, offsetY, tmpbuf2, d_FONT_16x30, FALSE);
        FONT_Height = d_FONT_16x30 & 0x00ff;
        offsetY = offsetY + FONT_Height + 2;
    }


    sprintf(tmpbuf, "交易後餘額   :%4ld", gTransData.lEVafterTxn);
    PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
    FONT_Height = d_FONT_12x24 & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;
    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    memset(tmpbuf2, 0x00, sizeof (tmpbuf2));

    PrintDateTime(gTransData.ucTxnData, gTransData.ucTxnTime);
    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    sprintf(tmpbuf, "===========================");
    PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    STR ReceiptTypeStr[36];

    memset(ReceiptTypeStr, 0x00, sizeof (36));
    BYTE buf[2 + 1];
    memset(buf, 0x00, sizeof (buf));
    USHORT ret;
    if (ReceiptType == 0) {
        sprintf(ReceiptTypeStr, "%s", gConfig.TM.RECEIPTTYPE1);
    } else if (ReceiptType == 1) {
        sprintf(ReceiptTypeStr, "%s", gConfig.TM.RECEIPTTYPE2);
    }

    if (Reprint) {
        sprintf(tmpbuf, "                        <%s><重印>", ReceiptTypeStr);
        PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
        offsetY = offsetY + FONT_Height + 2;
    } else {
        sprintf(tmpbuf, "                        <%s>", ReceiptTypeStr);
        PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
        offsetY = offsetY + FONT_Height + 2;
    }

    PrintRemark();
    //   FONT_Height=d_FONT_12x24 & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;
    CTOS_PrinterBufferOutput(pPtr, (offsetY / 8));
    CTOS_PrinterFline(64);
    // free(pPtr);
    // Set the font attribute
    // free(tmpbuf);free(tmpbuf2);
}

void Receipt2(int ReceiptType, BYTE Reprint) {

    USHORT usRtn;


    BYTE tmpbuf[64], tmpbuf2[64];
    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    memset(tmpbuf2, 0x00, sizeof (tmpbuf2));
    CTOS_RTC SetRTC;
    BYTE CardID[17 + 1];
    BYTE Title[24];

    SetPrintConfig();


    // memset(pPtr,0x00,sizeof(pPtr));

    offsetY = 0;
    offsetX = 0;
    BYTE FONT_Height = Med_Font_Size & 0x00ff;
    BYTE FONT_Width = Med_Font_Size >> 8;
    stFONT_ATTRIB.FontSize = Med_Font_Size; // Font Size = 12x24
    stFONT_ATTRIB.X_Zoom = 1; // The width magnifies X_Zoom diameters
    stFONT_ATTRIB.Y_Zoom = 1; // The height magnifies Y_Zoom diameters
    stFONT_ATTRIB.X_Space = 0; // The width of the space between the font with next
    stFONT_ATTRIB.Y_Space = 0; // The  0, 0, 384,1 );
    //   CTOS_PrinterSetHeatLevel(5);



    usRtn = CheckPrintStatus();


    PrintEASYCARDLOGO();

    PrintTitle();


    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    sprintf(tmpbuf, "===========================");
    PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
    FONT_Height = d_FONT_12x24 & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;
    if (strcmp(gConfig.TX.OPERATIONMODE, "BARCODESCANNER") == 0) {
        sprintf(tmpbuf, "收銀機交易編號:%s", gTransData.ucTMINVOICENO);
        PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
        offsetY = offsetY + FONT_Height + 2;
    }
    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    memset(tmpbuf2, 0x00, sizeof (tmpbuf2));
    sprintf(tmpbuf, "批次號碼       :%s", gTransData.ucBatchNo);
    sprintf(tmpbuf2, "交易序號:%06ld", gTransData.usTXSN);
    PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
    PrintStr(228, offsetY, tmpbuf2, d_FONT_12x24, FALSE);
    FONT_Height = d_FONT_12x24 & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;
    // Printline(tmpbuf,tmpbuf2,d_FONT_12x24,FALSE);

    /*
    if(ecrObj.gData.isEcrTxn)
    {
        sprintf(tmpbuf,"收銀機交易序號: %ld",ecrObj.ngData->tmTxnSn);
        PrintStr(1,offsetY,tmpbuf,d_FONT_12x24,FALSE);
        offsetY=offsetY+FONT_Height+2;
    }
     */

    vGetTxTitleStr(gTransData.ucTXTYPE, Title);
    sprintf(tmpbuf, "交易類別       :%s", Title);

    if (strlen(gTransData.ucTxnAuthNum) <= 0)
        sprintf(tmpbuf2, "授權碼:000000");
    else
        sprintf(tmpbuf2, "授權碼:%s", gTransData.ucTxnAuthNum);
    PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
    PrintStr(228, offsetY, tmpbuf2, d_FONT_12x24, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    memset(tmpbuf2, 0x00, sizeof (tmpbuf2));
    sprintf(tmpbuf, "設備交易序號:%s", gTransData.ucRRN);

    PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);

    offsetY = offsetY + FONT_Height + 2;

    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    memset(tmpbuf2, 0x00, sizeof (tmpbuf2));
    memset(CardID, 0x00, sizeof (CardID));


    vdUIntToAsc2(gTransData.ucCardID, sizeof (gTransData.ucCardID), CardID, 10); //n_Card Physical ID
    if (ReceiptType == 0) {
        int i = 0;
        int offset1 = strlen(CardID) - 3 - 4 - 1;
        for (i = 0; i < 3; i++) {
            CardID[offset1 + i] = '*';
        }
    }
    sprintf(tmpbuf, "悠遊卡晶片號:%s", CardID);
    PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    if (strcmp(gConfig.TX.OPERATIONMODE, "AUTO_BYTYPE") == 0) {
        BYTE strPersonalProfileName[32];
        // int CardProfile=atoi(gTransData.ucBasicData_CardProfile);
        // int CardType=atoi(gTransData.ucBasicData_CardType);
        memset(strPersonalProfileName, 0x00, sizeof (strPersonalProfileName));
        GetCard_PersonalProfile(strPersonalProfileName);
        sprintf(tmpbuf, "卡片種類      :%s", strPersonalProfileName);
        PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
        offsetY = offsetY + FONT_Height + 2;
    }

    sprintf(tmpbuf, "卡片交易序號:%ld", gTransData.ulCardTxnSN);
    PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    memset(tmpbuf2, 0x00, sizeof (tmpbuf2));

    if (gAutoloadAMT > 0) {

        sprintf(tmpbuf, "交易前餘額   :%4ld", gEVBeforeAutoload);
        PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
        offsetY = offsetY + FONT_Height + 2;

        memset(tmpbuf, 0x00, sizeof (tmpbuf));
        memset(tmpbuf2, 0x00, sizeof (tmpbuf2));

        sprintf(tmpbuf, "自動加值   :%4ld", gAutoloadAMT);
        sprintf(tmpbuf2, "交易金額:%4ld", gTransData.lTxnAmt);
        PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
        PrintStr(192, offsetY, tmpbuf2, d_FONT_16x30, FALSE);
        FONT_Height = d_FONT_16x30 & 0x00ff;
        offsetY = offsetY + FONT_Height + 2;
    } else {
        sprintf(tmpbuf, "交易前餘額   :%4ld", gTransData.lEVBeforeTxn);
        sprintf(tmpbuf2, "交易金額:%4ld", gTransData.lTxnAmt);
        PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
        PrintStr(192, offsetY, tmpbuf2, d_FONT_16x30, FALSE);
        FONT_Height = d_FONT_16x30 & 0x00ff;
        offsetY = offsetY + FONT_Height + 2;
    }


    sprintf(tmpbuf, "交易後餘額   :%4ld", gTransData.lEVafterTxn);
    PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
    FONT_Height = d_FONT_12x24 & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;
    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    memset(tmpbuf2, 0x00, sizeof (tmpbuf2));

    PrintDateTime(gTransData.ucTxnData, gTransData.ucTxnTime);
    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    sprintf(tmpbuf, "===========================");
    PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    STR ReceiptTypeStr[36];

    memset(ReceiptTypeStr, 0x00, sizeof (36));
    BYTE buf[2 + 1];
    memset(buf, 0x00, sizeof (buf));
    USHORT ret;
    if (ReceiptType == 0) {
        sprintf(ReceiptTypeStr, "%s", gConfig.TM.RECEIPTTYPE1);
    } else if (ReceiptType == 1) {
        sprintf(ReceiptTypeStr, "%s", gConfig.TM.RECEIPTTYPE2);
    }

    if (Reprint) {
        sprintf(tmpbuf, "                        <%s><重印>", ReceiptTypeStr);
        PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
        offsetY = offsetY + FONT_Height + 2;
    } else {
        sprintf(tmpbuf, "                        <%s>", ReceiptTypeStr);
        PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
        offsetY = offsetY + FONT_Height + 2;
    }

    PrintRemark();
    //   FONT_Height=d_FONT_12x24 & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;
    CTOS_PrinterBufferOutput(pPtr, (offsetY / 8));
    CTOS_PrinterFline(64);
    // free(pPtr);
    // Set the font attribute
    // free(tmpbuf);free(tmpbuf2);
}

USHORT PrintDetail(TRANS_DATA2 *TransData) {

    USHORT usRet;
    BYTE Title[24];
    BYTE CardID[17 + 1];
    BYTE tmpbuf[20];
    SetPrintConfig();

    // memset(pPtr,0x00,sizeof(pPtr));
    offsetY = 0;
    offsetX = 0;
    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    FONT_Height = d_FONT_12x24 & 0x00ff;
    vGetTxTitleStr(TransData->ucTXTYPE, Title);


    sprintf(tmpbuf, "交易類別:%s 交易序號:%ld ", Title, TransData->usTXSN);
    PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
    offsetY = offsetY + FONT_Height + 2;
    vdIntToAsc(TransData->ucCardID, sizeof (TransData->ucCardID), CardID, sizeof (CardID) - 1, ' ', 10); //n_Card Physical ID
    sprintf(tmpbuf, "悠遊卡晶片號:%s ", CardID);
    PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    PrintDateTime((STR *) & TransData->ucTxnData, (STR *) & TransData->ucTxnTime);

    sprintf(tmpbuf, "交易金額:%ld 卡片餘額:%ld", TransData->lTxnAmt, TransData->lEVafterTxn);
    PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
    offsetY = offsetY + FONT_Height + 2;


    /* if(TransData->ucTXSTATUS==TransStatus_VOIDED)
     {
        sprintf(tmpbuf,"<已取消>");
         PrintStr(1,offsetY,tmpbuf,d_FONT_12x24,FALSE);
         offsetY=offsetY+FONT_Height+2;
     }*/
    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    sprintf(tmpbuf, "===========================");
    PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
    FONT_Height = d_FONT_12x24 & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;
    CTOS_PrinterBufferOutput(pPtr, (offsetY / 8));
    // free(pPtr);
}

USHORT GetCardTYPEPrintStr(BYTE PersonalProfile, BYTE CardType, BYTE *strPersonalProfileName) {

    switch (PersonalProfile) {
        case 0:
            sprintf(strPersonalProfileName, "普");
            break;
        case 1:
            sprintf(strPersonalProfileName, "敬一");
            break;
        case 2:
            sprintf(strPersonalProfileName, "敬二");
            break;
        case 3:
            sprintf(strPersonalProfileName, "愛");
            break;
        case 4:
            sprintf(strPersonalProfileName, "愛陪");
            break;
        case 5:
            sprintf(strPersonalProfileName, "學");
            break;

        case 8:
            sprintf(strPersonalProfileName, "優");
            break;

        default:
            sprintf(strPersonalProfileName, "普");
            break;
    }
    return d_OK;
}

USHORT PrintDetail2(TRANS_DATA2 *TransData) {

    USHORT usRet;
    BYTE Title[24];
    BYTE CardID[17 + 1];
    BYTE tmpbuf[256];
    SetPrintConfig();
    USHORT FontSize = d_FONT_9x18;
    //  memset(pPtr,0x00,sizeof(pPtr));
    offsetY = 0;
    offsetX = 0;

    if (strcmp(gConfig.TX.OPERATIONMODE, "BARCODESCANNER") == 0) {
        sprintf(tmpbuf, "%s", TransData->ucTMINVOICENO);
        PrintStr(1, offsetY, tmpbuf, FontSize, FALSE);
        offsetY = offsetY + FONT_Height + 2;
    }

    memset(Title, 0x00, sizeof (Title));
    FONT_Height = FontSize & 0x00ff;
    vGetTxTitleStr(TransData->ucTXTYPE, Title);
    memset(CardID, 0x00, sizeof (CardID));
    vdIntToAsc(TransData->ucCardID, sizeof (TransData->ucCardID), CardID, sizeof (CardID) - 1, ' ', 10); //n_Card Physical ID
    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    BYTE DataTimeStr[32];
    memset(DataTimeStr, 0x00, sizeof (DataTimeStr));
    GetDateTimeStr(TransData->ucTxnData, TransData->ucTxnTime, DataTimeStr);
    if (strcmp(gConfig.TX.OPERATIONMODE, "AUTO_BYTYPE") == 0) {
        BYTE CardProfileStr[10 + 1];
        memset(CardProfileStr, 0x00, sizeof (CardProfileStr));
        GetCardTYPEPrintStr(TransData->ucBasicData_CardProfile, TransData->ucBasicData_CardType, CardProfileStr);
        sprintf(tmpbuf, "%s  %06ld  %8s  %17s(%s)  $%ld", DataTimeStr, TransData->usTXSN, Title, CardID, CardProfileStr, TransData->lTxnAmt);
    } else {
        sprintf(tmpbuf, "%s  %06ld  %8s  %17s     $%ld", DataTimeStr, TransData->usTXSN, Title, CardID, TransData->lTxnAmt);
    }

    PrintStr(1, offsetY, tmpbuf, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;



    // PrintDateTime2(TransData->ucTxnData,TransData->ucTxnTime,FontSize);

    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    sprintf(tmpbuf, "===========================");
    PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
    FONT_Height = d_FONT_12x24 & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;
    CTOS_PrinterBufferOutput(pPtr, (offsetY / 8));
    //free(pPtr);
}

USHORT CheckPrintTXDetail() {

    int iret;

    if (gScrpitTesting != 1) {
        iret = ShowMessage2line("交易明細", "是否列印交易明細", "", TYPE_ECR_FORCE_TO_CONFIRM_OK);
    } else {
        iret = d_OK;
    }
    if (iret == d_OK) PrintTXDetail2();
}

USHORT PrintTXDetail2() {
    USHORT usRtn;
    ULONG offset;
    int iSize;
    int inRetVal;

    SetPrintConfig();

    // memset(pPtr,0x00,sizeof(pPtr));
    offsetY = 0;
    offsetX = 0;
    BYTE FONT_Height = Med_Font_Size & 0x00ff;
    BYTE FONT_Width = Med_Font_Size >> 8;
    stFONT_ATTRIB.FontSize = Med_Font_Size; // Font Size = 12x24
    stFONT_ATTRIB.X_Zoom = 1; // The width magnifies X_Zoom diameters
    stFONT_ATTRIB.Y_Zoom = 1; // The height magnifies Y_Zoom diameters
    stFONT_ATTRIB.X_Space = 0; // The width of the space between the font with next
    stFONT_ATTRIB.Y_Space = 0; // The  0, 0, 384,1 );
    //   CTOS_PrinterSetHeatLevel(5);

    BYTE tmpbuf[256];
    memset(tmpbuf, 0x00, sizeof (tmpbuf));

    usRtn = CheckPrintStatus();


    PrintEASYCARDLOGO();

    PrintTitle();

    FONT_Height = d_FONT_12x24 & 0x00ff;

    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    sprintf(tmpbuf, "===========================");
    PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    if (strcmp(gConfig.TX.OPERATIONMODE, "BARCODESCANNER") == 0) {
        sprintf(tmpbuf, "收銀機交易序號");
        PrintStr(1, offsetY, tmpbuf, d_FONT_9x18, FALSE);
        offsetY = offsetY + FONT_Height + 2;
    }


    // sprintf(tmpbuf,"序號     類別                   卡號             金額 ");
    if (strcmp(gConfig.TX.OPERATIONMODE, "AUTO_BYTYPE") == 0) {
        sprintf(tmpbuf, "交易時間           序號     類別          卡號(卡別)          金額");
    } else {
        sprintf(tmpbuf, "交易時間           序號     類別           卡號            金額");
    }
    PrintStr(1, offsetY, tmpbuf, d_FONT_9x18, FALSE);
    offsetY = offsetY + FONT_Height + 2;


    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    sprintf(tmpbuf, "===========================");
    PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    CTOS_PrinterBufferOutput(pPtr, (offsetY / 8));
    TRANS_DATA2 TransData;

    FILE *fp = fopen(TransDataFile, "rb+");
    if (fp == NULL)
        return d_ERR_FILE_OPEN;

    fseek(fp, 0L, SEEK_END);
    ULONG ulFileSize;
    ulFileSize = ftell(fp);
    if (ulFileSize <= 0) return d_ERR_FILE_NOTEXIST;
    if (ulFileSize % sizeof (TRANS_DATA2) != 0) return d_ERR_FILE_SIZE_ERR;
    offset = 0;
    BYTE str[64];
    memset(str, 0x00, sizeof (str));
    int totalcnt = ulFileSize / sizeof (TRANS_DATA2);
    BYTE key;
    USHORT usRet;
    int iret, i;
    int iCount = 0;
    for (i = 0; i < totalcnt; i++) {

        usRet = CheckPrintStatus();
        if (usRet != d_OK) {
            if (usRet == d_ERR_USERCANCEL)
                return usRet;
            else
                continue;
        }
        sprintf(str, "%d/%d", iCount, totalcnt);
        ShowMessage3line("交易明細", "列印中...", str, "欲暫停請按(X)", Type_ComformNONE);
        CTOS_KBDHit(&key);
        if (key == d_KBD_CANCEL) {
            iret = ShowMessage3line("交易明細", "暫停?", "繼續列印請按<OK>", "", Type_ComformOK);
            if (iret == d_FAIL) {
                i = totalcnt;
                break;
            }
        }
        fseek(fp, offset, SEEK_SET);
        iSize = fread((BYTE *) & TransData, sizeof (TRANS_DATA2), 1, fp);
        if (TransData.ucTXTYPE != TXTYPE_LOCKCARD)
            usRet = PrintDetail2(&TransData);
        iCount++;


        offset += sizeof (TRANS_DATA2);
        if (offset >= ulFileSize) break;
    }
    fclose(fp);
    //  memset(pPtr,0x00,sizeof(pPtr));
    offsetY = 0;
    offsetX = 0;
    memset(tmpbuf, 0x00, sizeof (tmpbuf));
    sprintf(tmpbuf, "                           <報表結束>                              ");
    PrintStr(1, offsetY, tmpbuf, d_FONT_12x24, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    CTOS_PrinterBufferOutput(pPtr, (offsetY / 8));
    CTOS_PrinterFline(64);

    /************************************************************************************/
    //free(pPtr);
    return;

}

USHORT PrintTXDetail() {
    USHORT usRtn;
    ULONG offset;
    int iSize;
    int inRetVal;
    int iCount = 0;
    SetPrintConfig();

    //  memset(pPtr,0x00,sizeof(pPtr));
    offsetY = 0;
    offsetX = 0;
    BYTE FONT_Height = Med_Font_Size & 0x00ff;
    BYTE FONT_Width = Med_Font_Size >> 8;
    stFONT_ATTRIB.FontSize = Med_Font_Size; // Font Size = 12x24
    stFONT_ATTRIB.X_Zoom = 1; // The width magnifies X_Zoom diameters
    stFONT_ATTRIB.Y_Zoom = 1; // The height magnifies Y_Zoom diameters
    stFONT_ATTRIB.X_Space = 0; // The width of the space between the font with next
    stFONT_ATTRIB.Y_Space = 0; // The  0, 0, 384,1 );
    //   CTOS_PrinterSetHeatLevel(5);


    usRtn = CheckPrintStatus();


    PrintEASYCARDLOGO();

    //usRtn=CTOS_PrinterBufferInit(pPtr,PB_CANVAS_Y_SIZE);
    //  usRtn= CTOS_PrinterBufferSelectActiveAddress ( pPtr );
    PrintTitle();


    PrintStr(1, offsetY, "===========================", d_FONT_12x24, FALSE);
    FONT_Height = d_FONT_12x24 & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;
    CTOS_PrinterBufferOutput(pPtr, (offsetY / 8));

    TRANS_DATA2 TransData;

    FILE *fp = fopen(TransDataFile, "r");
    if (fp == NULL)
        return d_ERR_FILE_OPEN;

    fseek(fp, 0L, SEEK_END);
    ULONG ulFileSize;
    ulFileSize = ftell(fp);
    if (ulFileSize <= 0) return d_ERR_FILE_NOTEXIST;
    if (ulFileSize % sizeof (TRANS_DATA2) != 0) return d_ERR_FILE_SIZE_ERR;
    offset = 0;
    BYTE str[64];
    memset(str, 0x00, sizeof (str));
    USHORT usRet;
    BYTE key;
    int totalcnt = ulFileSize / sizeof (TRANS_DATA2);
    int iret;
    while (1) {
        usRet = CheckPrintStatus();
        if (usRet != d_OK) {
            if (usRet == d_ERR_USERCANCEL)
                return usRet;
            else
                continue;
        }

        fseek(fp, offset, SEEK_SET);
        iSize = fread((BYTE *) & TransData, sizeof (TRANS_DATA2), 1, fp);

        usRet = PrintDetail(&TransData);
        iCount++;
        offset += sizeof (TRANS_DATA2);
        sprintf(str, "%d/%d", iCount, totalcnt);
        ShowMessage3line("交易明細", "列印中...", str, "欲中斷請按(X)", Type_ComformNONE);
        CTOS_KBDHit(&key);
        if (key == d_KBD_CANCEL) {
            iret = MessageBox("交易明細", "是否確定中斷列印?", "", "繼續列印請按<OK>", "欲中斷請按(X)", d_MB_CONFIRM);
            if (iret == d_ERR_USERCANCEL) return;
        }
        if (offset >= ulFileSize) break;
    }
    fclose(fp);

    CTOS_PrinterFline(64);
    //free(pPtr);
    /************************************************************************************/



}

USHORT PrintSettlementReceipt(Batch_Totle_STRUCT *BatchTotal) {
    USHORT usRtn;
    CTOS_RTC SetRTC;
    BYTE Date[32];


    //2014.04.07, kobe added for ECR, response to POS first
    int result;
    if (ecrObj.gData.isEcrTxn) {
        //if process come to "print receipt" means that txn was success 
        sprintf(ecrObj.ngData->responseCode, "0000");
        snprintf(ecrObj.ngData->tipMsg, sizeof (ecrObj.ngData->tipMsg), "CMAS設備即將自動重新開機，請等待30秒");
        if ((result = ecrObj.successResponse(&ecrObj)) != d_OK && !ecrObj.ngData->response2Pos) {
            ecrObj.errorResponse(&ecrObj, result);
        }
    }

    //  USHORT FontSize=Med_Font_Size;
    USHORT FontSize = d_FONT_12x24;
    SetPrintConfig();

    // memset(pPtr,0x00,sizeof(pPtr));
    offsetY = 0;
    offsetX = 0;
    BYTE FONT_Height = Med_Font_Size & 0x00ff;
    BYTE FONT_Width = Med_Font_Size >> 8;
    stFONT_ATTRIB.FontSize = Med_Font_Size; // Font Size = 12x24
    stFONT_ATTRIB.X_Zoom = 1; // The width magnifies X_Zoom diameters
    stFONT_ATTRIB.Y_Zoom = 1; // The height magnifies Y_Zoom diameters
    stFONT_ATTRIB.X_Space = 0; // The width of the space between the font with next
    stFONT_ATTRIB.Y_Space = 0; // The  0, 0, 384,1 );
    //   CTOS_PrinterSetHeatLevel(5);



    usRtn = CheckPrintStatus();


    PrintEASYCARDLOGO();

    //  usRtn=CTOS_PrinterBufferInit(pPtr,PB_CANVAS_Y_SIZE);
    //  usRtn= CTOS_PrinterBufferSelectActiveAddress ( pPtr );
    PrintTitle();

    STR Line[64];

    sprintf(Line, "                         結帳報表");
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;
    memset(Line, 0x00, sizeof (Line));
    sprintf(Line, "===========================");
    PrintStr(1, offsetY, Line, FontSize, FALSE);

    FONT_Height = FontSize & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;



    ezxml_t FUNCTION, TYPE;


    sprintf(Line, "批次號碼:%s\n", BatchTotal->ucBatchSN);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;
    sprintf(Line, "交易總筆數:%-15ld交易總額:%6ld\n", BatchTotal->TotleCnt, BatchTotal->TotleAMT);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    memset(Line, 0x00, sizeof (Line));
    sprintf(Line, "===========================");
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    sprintf(Line, "購貨總筆數:%-15ld總額:%-6ld\n", BatchTotal->DEDUCTCnt, BatchTotal->DEDUCTAMT);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;
    sprintf(Line, "取消總筆數:%-15ld總額:%-6ld\n", BatchTotal->DEDUCTVOIDCnt, BatchTotal->DEDUCTVOIDAMT);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;
    sprintf(Line, "退貨總筆數:%-15ld總額:%-6ld\n", BatchTotal->REFUNDCnt, BatchTotal->REFUNDAMT);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    sprintf(Line, "購貨類交易總筆數:%-17ld總淨額:%-6ld\n", BatchTotal->DEDUCTNETCnt, BatchTotal->DEDUCTNETAMT);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;
    memset(Line, 0x00, sizeof (Line));
    if (strcmp(gConfig.TX.OPERATIONMODE, "AUTO_BYTYPE") == 0) {

        memset(Line, 0x00, sizeof (Line));
        sprintf(Line, "===========================");
        PrintStr(1, offsetY, Line, FontSize, FALSE);
        offsetY = offsetY + FONT_Height + 2;

        sprintf(Line, "普通卡:%-30ld總額:%-6ld\n", BatchTotal->AMTByProfile[0], BatchTotal->CntByProfile[0]);
        PrintStr(1, offsetY, Line, FontSize, FALSE);
        offsetY = offsetY + FONT_Height + 2;

        sprintf(Line, "敬老卡(一):%-30ld總額:%-6ld\n", BatchTotal->AMTByProfile[1], BatchTotal->CntByProfile[1]);
        PrintStr(1, offsetY, Line, FontSize, FALSE);
        offsetY = offsetY + FONT_Height + 2;

        sprintf(Line, "敬老卡(二):%-30ld總額:%-6ld\n", BatchTotal->AMTByProfile[2], BatchTotal->CntByProfile[2]);
        PrintStr(1, offsetY, Line, FontSize, FALSE);
        offsetY = offsetY + FONT_Height + 2;

        sprintf(Line, "愛心卡:%-30ld總額:%-6ld\n", BatchTotal->AMTByProfile[3], BatchTotal->CntByProfile[3]);
        PrintStr(1, offsetY, Line, FontSize, FALSE);
        offsetY = offsetY + FONT_Height + 2;

        sprintf(Line, "愛陪卡:%-30ld總額:%-6ld\n", BatchTotal->AMTByProfile[4], BatchTotal->CntByProfile[4]);
        PrintStr(1, offsetY, Line, FontSize, FALSE);
        offsetY = offsetY + FONT_Height + 2;

        sprintf(Line, "學生卡:%-30ld總額:%-6ld\n", BatchTotal->AMTByProfile[5], BatchTotal->CntByProfile[5]);
        PrintStr(1, offsetY, Line, FontSize, FALSE);
        offsetY = offsetY + FONT_Height + 2;

        sprintf(Line, "優待卡:%-30ld總額:%-6ld\n", BatchTotal->AMTByProfile[8], BatchTotal->CntByProfile[8]);
        PrintStr(1, offsetY, Line, FontSize, FALSE);
        offsetY = offsetY + FONT_Height + 2;
    }


    sprintf(Line, "===========================");
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    sprintf(Line, "加值總筆數:%-30ld總額:%-6ld\n", BatchTotal->ADDCnt, BatchTotal->ADDAMT);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;
    sprintf(Line, "取消總筆數:%-30ld總額:%-6ld\n", BatchTotal->ADDVOIDCnt, BatchTotal->ADDVOIDAMT);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;
    sprintf(Line, "加值類交易總筆數%-18ld總淨額:%-6ld\n", BatchTotal->ADDVALUENETCnt, BatchTotal->ADDVALUENETAMT);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;
    memset(Line, 0x00, sizeof (Line));
    sprintf(Line, "===========================");
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    sprintf(Line, "自動加值總筆數:%-20ld 總額:%-6ld\n", BatchTotal->AUTOLOADCnt, BatchTotal->AUTOLOADAMT);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    sprintf(Line, "===========================");
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    sprintf(Line, "鎖卡總筆數%-12ld\n", BatchTotal->BLACKCARDCNT);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;
    memset(Line, 0x00, sizeof (Line));
    sprintf(Line, "===========================");
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    FONT_Height = FontSize & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;
    PrintDateTime(gTransData.ucTxnData, gTransData.ucTxnTime);

    CTOS_PrinterBufferOutput(pPtr, (offsetY / 8));
    CTOS_PrinterFline(64);
    //free(pPtr);
}

void DebugPrint_hex(unsigned char* i_pc_buffer, long len, char* i_pc_title, int DebugMode) {
    if ((gDebugPrintFlag != DebugMode) && (gDebugPrintFlag != DebugMode_ALL))
        return;

    char buffer[100];
    char buffer2[50];
    char l_pc_temp[10];
    int i;
    long curLen;
    long tempLen;
    unsigned char ch;

    BYTE debugbuf[265];

    memset(debugbuf, 0x00, sizeof (debugbuf));
    CTOS_PrinterFontSelectMode(d_FONT_TTF_MODE);
    CTOS_PrinterTTFSelect(d_FONT_TTF, 0);
    CTOS_LanguagePrinterFontSize(d_FONT_12x24, 1, 0);
    sprintf(debugbuf, "%s lenght=%ld\n", i_pc_title, len);
    CTOS_PrinterPutString(debugbuf);
    memset(debugbuf, 0x00, sizeof (debugbuf));
    curLen = len;

    while (curLen > 10) {
        buffer[0] = 0;
        buffer2[0] = 0;
        for (i = 0; i < 8; i++) {
            ch = i_pc_buffer[len - curLen];
            sprintf(l_pc_temp, "%.2x^", ch);
            strcat(buffer, l_pc_temp);
            if (ch >= 0x20 && ch < 0x7f)
                sprintf(l_pc_temp, "%c", ch);
            else
                sprintf(l_pc_temp, "*");
            strcat(buffer2, l_pc_temp);
            curLen--;
        }
        strcat(buffer, buffer2);
        strcat(buffer, "\n");
        //fprintf(fPrinter, buffer);
        CTOS_PrinterPutString(buffer);
    }
    tempLen = curLen;
    if (curLen != 0) {
        buffer[0] = 0;
        buffer2[0] = 0;
        for (i = 0; i < tempLen; i++) {
            ch = i_pc_buffer[len - curLen];
            sprintf(l_pc_temp, "%.2x^", i_pc_buffer[len - curLen]);
            strcat(buffer, l_pc_temp);
            if (ch >= 0x20 && ch < 0x7f)
                sprintf(l_pc_temp, "%c", ch);
            else
                sprintf(l_pc_temp, "*");
            strcat(buffer2, l_pc_temp);
            curLen--;
        }
        for (i = tempLen; i < 8; i++) {
            ch = i_pc_buffer[len - curLen];
            sprintf(l_pc_temp, "  ^");
            strcat(buffer, l_pc_temp);
            strcat(buffer2, " ");
            curLen--;
        }
        strcat(buffer, buffer2);
        strcat(buffer, "\n");
        CTOS_PrinterPutString(buffer);
    }
    //fprintf(fPrinter, "-----\n");
    CTOS_PrinterPutString("-----\n");

    sprintf(buffer, "\x12LENGTH=%ld\n", len);
    //fprintf(fPrinter, buffer);
    CTOS_PrinterPutString(buffer);


}

USHORT PrintParameter() {
    USHORT usRtn;
    CTOS_RTC SetRTC;
    BYTE Date[32];
    USHORT FontSize = Med_Font_Size;

    memset(pPtr, 0x00, sizeof (pPtr)); //20141107, kobe added it, clear buffer
    SetPrintConfig();

    // memset(pPtr,0x00,sizeof(pPtr));
    offsetY = 0;
    offsetX = 0;
    BYTE FONT_Height = Med_Font_Size & 0x00ff;
    BYTE FONT_Width = Med_Font_Size >> 8;
    stFONT_ATTRIB.FontSize = Med_Font_Size; // Font Size = 12x24
    stFONT_ATTRIB.X_Zoom = 1; // The width magnifies X_Zoom diameters
    stFONT_ATTRIB.Y_Zoom = 1; // The height magnifies Y_Zoom diameters
    stFONT_ATTRIB.X_Space = 0; // The width of the space between the font with next
    stFONT_ATTRIB.Y_Space = 0; // The  0, 0, 384,1 );
    //   CTOS_PrinterSetHeatLevel(5);

    usRtn = CheckPrintStatus();
    if (usRtn != d_OK) return usRtn;



    //PrintEASYCARDLOGO();
    offsetY = 0;
    offsetX = 0;
    //usRtn=CTOS_PrinterBufferInit(pPtr,PB_CANVAS_Y_SIZE);
    //usRtn= CTOS_PrinterBufferSelectActiveAddress ( pPtr );
    PrintTitle();

    STR Line[64];

    sprintf(Line, "                    參數列表");
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;
    memset(Line, 0x00, sizeof (Line));
    sprintf(Line, "===========================");
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    FONT_Height = FontSize & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;

    sprintf(Line, "                    版本資訊");
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;


    sprintf(Line, "參數版號:%s\n", gConfig.CURRVERSION.PARAMETER);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;


    sprintf(Line, "AP版號:%s\n", gConfig.CURRVERSION.AP.VERSION);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;


    sprintf(Line, "鎖卡名單版號:%s\n", gConfig.CURRVERSION.BLC.VERSION);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;


    sprintf(Line, "SSL憑證版號:%s\n", gConfig.CURRVERSION.SSL.VERSION);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;


    memset(Line, 0x00, sizeof (Line));
    sprintf(Line, "===========================");
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    FONT_Height = FontSize & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;

    sprintf(Line, "                    特店資訊");
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;


    sprintf(Line, "特店代號:%s", gConfig.MERCHANT.MERCHANTID);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;


    sprintf(Line, "分公司代號:%s", gConfig.MERCHANT.NewLocationID);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;


    sprintf(Line, "分店代號:%s", gConfig.MERCHANT.STCODE);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    memset(Line, 0x00, sizeof (Line));
    sprintf(Line, "===========================");
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    FONT_Height = FontSize & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;



    sprintf(Line, "                    交易設定");
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    sprintf(Line, "SIGNON時間間隔:%s", gConfig.TX.SIGNONMAXTIME);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    sprintf(Line, "離線交易筆數容許:%s", gConfig.TX.OFFLINETXLIMIT);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;


    sprintf(Line, "離線交易必須上傳筆數上限:%s", gConfig.TX.FORCEONLINELIMIT);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    sprintf(Line, "加值最小單位:%s", gConfig.TX.MiniunitsADDVALUE);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    sprintf(Line, "自動加值金額上限:%s", gConfig.TX.AUTOLOADLIMITAMT);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;
    memset(Line, 0x00, sizeof (Line));
    sprintf(Line, "===========================");
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    FONT_Height = FontSize & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;



    sprintf(Line, "                    設備資訊");
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    sprintf(Line, "機器序號:%s", gConfig.DEVICE.EDC.MechineID);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    sprintf(Line, "讀卡機埠號:%s", gConfig.DEVICE.READER.bPORT);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;


    sprintf(Line, "二代設備編號:%s", gConfig.DEVICE.READER.CPU.CPUDEVICEID);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    sprintf(Line, "一代設備編號:%s", gConfig.DEVICE.READER.MIFARE_DEVICEID);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;


    sprintf(Line, "二代 SAM ID:%s", gConfig.DEVICE.READER.CPU.SAMID);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;


    sprintf(Line, "一代 SAM ID:%s", gConfig.DEVICE.READER.MIFARE_SAMID);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;



    sprintf(Line, "讀卡機序號:%s", gConfig.DEVICE.READER.bREADERID);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    sprintf(Line, "讀卡機韌體版本:%s", gConfig.DEVICE.READER.bREADERFWVER);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    memset(Line, 0x00, sizeof (Line));
    sprintf(Line, "===========================");
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    FONT_Height = FontSize & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;



    sprintf(Line, "                    商店資訊");
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;


    sprintf(Line, "特店名稱:%s", gConfig.TM.TITLE);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;


    sprintf(Line, "分店名稱:%s", gConfig.TM.SUBTITLE);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    sprintf(Line, "收據列印張數:%s", gConfig.TM.RECEIPTNUM);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;


    sprintf(Line, "收據第一聯:%s", gConfig.TM.RECEIPTTYPE1);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;


    sprintf(Line, "收據第二聯:%s", gConfig.TM.RECEIPTTYPE2);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;



    sprintf(Line, "%s", gConfig.TM.RECEIPTREMARK.STRING1);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;


    sprintf(Line, "%s", gConfig.TM.RECEIPTREMARK.STRING2);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;


    sprintf(Line, "%s", gConfig.TM.RECEIPTREMARK.STRING3);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;


    sprintf(Line, "%s", gConfig.TM.RECEIPTREMARK.STRING4);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;


    sprintf(Line, "%s", gConfig.TM.RECEIPTREMARK.STRING5);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    memset(Line, 0x00, sizeof (Line));
    sprintf(Line, "===========================");
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    FONT_Height = FontSize & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;


    BYTE buff[64 + 1];
    BYTE len = sizeof (buff);
    sprintf(Line, "                    本機網路設定");
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;
    memset(buff, 0x00, sizeof (buff));
    USHORT ret = CTOS_EthernetConfigGet((BYTE) d_ETHERNET_CONFIG_IP, (BYTE *) buff, &len);
    sprintf(Line, "本機IP:%s", buff);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;
    len = sizeof (buff);
    memset(buff, 0x00, sizeof (buff));
    ret = CTOS_EthernetConfigGet(d_ETHERNET_CONFIG_MASK, buff, &len);
    sprintf(Line, "MASK:%s", buff);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;
    len = sizeof (buff);
    memset(buff, 0x00, sizeof (buff));
    ret = CTOS_EthernetConfigGet(d_ETHERNET_CONFIG_GATEWAY, buff, &len);
    sprintf(Line, "GATEWAY:%s", buff);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;
    memset(buff, 0x00, sizeof (buff));
    len = sizeof (buff);
    ret = CTOS_EthernetConfigGet(d_ETHERNET_CONFIG_DNSIP, buff, &len);
    sprintf(Line, "DNS:%s", buff);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;
    memset(buff, 0x00, sizeof (buff));
    len = sizeof (buff);
    ret = CTOS_EthernetConfigGet(d_ETHERNET_CONFIG_MAC, buff, &len);
    sprintf(Line, "MAC:%s", buff);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;
    memset(buff, 0x00, sizeof (buff));
    len = sizeof (buff);
    ret = CTOS_EthernetConfigGet(d_ETHERNET_CONFIG_DHCP, buff, &len);
    sprintf(Line, "DHCP:%s", buff);
    memset(buff, 0x00, sizeof (buff));
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;


    CTOS_RTC RTC;
    ret = CTOS_RTCGet(&RTC);
    if (ret != 0) {
        return d_ERR_GETRTC;
    }


    memset(Line, 0x00, sizeof (Line));
    sprintf(Line, "===========================");
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    FONT_Height = FontSize & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;



    sprintf(Line, "                    通訊設定");
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;
    sprintf(Line, "網路訊號來源:%s", gConfig.ETHERNET.EthernetCHANNEL);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    sprintf(Line, "URL:%s", gConfig.ETHERNET.HOST_PRODUCTION.HOST.URL);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;


    sprintf(Line, "VIP IP:%s", gConfig.ETHERNET.HOST_PRODUCTION.HOST.VIPIP);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;


    sprintf(Line, "IP:%s", gConfig.ETHERNET.HOST_PRODUCTION.HOST.IP);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    sprintf(Line, "PORT:%s", gConfig.ETHERNET.HOST_PRODUCTION.HOST.PORT);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;


    sprintf(Line, "FTP URL:%s", gConfig.ETHERNET.HOST_PRODUCTION.FTP.URL);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;


    sprintf(Line, "FTP IP:%s", gConfig.ETHERNET.HOST_PRODUCTION.FTP.IP);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;


    memset(Line, 0x00, sizeof (Line));
    sprintf(Line, "===========================");
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    FONT_Height = FontSize & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;

    sprintf(Line, "                    交易功能開關");
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    if (GetFunctionSwitch("ADDVALUE") == TRUE)
        sprintf(Line, "現金加值:開啟");
    else
        sprintf(Line, "現金加值:關閉");

    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;
    if (GetFunctionSwitch("AUTOLOAD") == TRUE)
        sprintf(Line, "AUTOLOAD:開啟");
    else
        sprintf(Line, "AUTOLOAD:關閉");

    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    if (GetFunctionSwitch("DEDUCT") == TRUE)
        sprintf(Line, "購貨:開啟");
    else
        sprintf(Line, "購貨:關閉");

    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    if (GetFunctionSwitch("CANCELTXN") == TRUE)
        sprintf(Line, "取消:開啟");
    else
        sprintf(Line, "取消:關閉");

    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    if (GetFunctionSwitch("RETURN") == TRUE)
        sprintf(Line, "退貨:開啟");
    else
        sprintf(Line, "退貨:關閉");

    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    if (GetFunctionSwitch("SETVALUE") == TRUE)
        sprintf(Line, "展期:開啟");
    else
        sprintf(Line, "展期:關閉");

    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    if (GetFunctionSwitch("AUTOLOADENABLE") == TRUE)
        sprintf(Line, "AUTOLOAD ENABLE:開啟");
    else
        sprintf(Line, "AUTOLOAD ENABLE:關閉");

    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;



    memset(Line, 0x00, sizeof (Line));
    sprintf(Line, "===========================");
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    FONT_Height = FontSize & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;

    sprintf(Line, "                    交易密碼開關");
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    if (CheckFunctionpPasswordflag("ADDVALUE") == TRUE)
        sprintf(Line, "現金加值:開啟");
    else
        sprintf(Line, "現金加值:關閉");

    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    if (CheckFunctionpPasswordflag("DEDUCT") == TRUE)
        sprintf(Line, "購貨:開啟");
    else
        sprintf(Line, "購貨:關閉");

    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    if (CheckFunctionpPasswordflag("CANCELTXN") == TRUE)
        sprintf(Line, "取消:開啟");
    else
        sprintf(Line, "取消:關閉");

    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    if (CheckFunctionpPasswordflag("RETURN") == TRUE)
        sprintf(Line, "退貨:開啟");
    else
        sprintf(Line, "退貨:關閉");

    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;



    if (CheckFunctionpPasswordflag("SETTLE") == TRUE)
        sprintf(Line, "結帳:開啟");
    else
        sprintf(Line, "結帳:關閉");

    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;



    //2014.04.18, kobe added for ECR Parameters
    memset(Line, 0x00, sizeof (Line));
    sprintf(Line, "===========================");
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    FONT_Height = FontSize & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;

    sprintf(Line, "                   收銀機連線");
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    sprintf(Line, "開關:%s", (ecrObj.ecrOn) ? "ON" : "OFF");
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;


    sprintf(Line, "連線模式:%s", (ecrObj.interface == RS232) ? "RS232" : "USB");
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    if (ecrObj.interface == RS232) {
        sprintf(Line, " comport:%d", ecrObj.rs232.protocal.comport + 1);
        PrintStr(1, offsetY, Line, FontSize, FALSE);
        offsetY = offsetY + FONT_Height + 2;

        sprintf(Line, " baudRate:%ld", ecrObj.rs232.protocal.baudRate);
        PrintStr(1, offsetY, Line, FontSize, FALSE);
        offsetY = offsetY + FONT_Height + 2;

        sprintf(Line, " dataBits:%d", ecrObj.rs232.protocal.dataBits);
        PrintStr(1, offsetY, Line, FontSize, FALSE);
        offsetY = offsetY + FONT_Height + 2;


        sprintf(Line, " parity:%c", ecrObj.rs232.protocal.parity);
        PrintStr(1, offsetY, Line, FontSize, FALSE);
        offsetY = offsetY + FONT_Height + 2;

        sprintf(Line, " stopBits:%d", ecrObj.rs232.protocal.stopBits);
        PrintStr(1, offsetY, Line, FontSize, FALSE);
        offsetY = offsetY + FONT_Height + 2;
    }

    sprintf(Line, "收銀機版本:VER%d", ecrObj.version);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;

    //end

    int i;
    memset(Line, 0x00, sizeof (Line));
    sprintf(Line, "===========================");
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    FONT_Height = FontSize & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;

    if (strcmp(gConfig.TX.OPERATIONMODE, "AUTO_BYTYPE") == 0) {
        sprintf(Line, "扣款操作模式:依票種自動扣款");
        PrintStr(1, offsetY, Line, FontSize, FALSE);
        offsetY = offsetY + FONT_Height + 2;
        sprintf(Line, "票價表:");
        PrintStr(1, offsetY, Line, FontSize, FALSE);
        offsetY = offsetY + FONT_Height + 2;
        for (i = 0; i < 15; i++) {
            if (strlen(gConfig.TX.AMTTABLE[i].NAME) > 0) {
                sprintf(Line, "%s", gConfig.TX.AMTTABLE[i].NAME);
                PrintStr(1, offsetY, Line, FontSize, FALSE);
                offsetY = offsetY + FONT_Height + 2;
                sprintf(Line, "(%d) %3d-%3d-%3d-%3d-%3d-%3d-%3d-%3d-%3d-%3d", i,
                        gConfig.TX.AMTTABLE[i].AMT[0], gConfig.TX.AMTTABLE[i].AMT[1], gConfig.TX.AMTTABLE[i].AMT[2], gConfig.TX.AMTTABLE[i].AMT[3], gConfig.TX.AMTTABLE[i].AMT[4],
                        gConfig.TX.AMTTABLE[i].AMT[5], gConfig.TX.AMTTABLE[i].AMT[6], gConfig.TX.AMTTABLE[i].AMT[7], gConfig.TX.AMTTABLE[i].AMT[8], gConfig.TX.AMTTABLE[i].AMT[9]);
                PrintStr(1, offsetY, Line, d_FONT_9x18, FALSE);
                offsetY = offsetY + FONT_Height + 2;
            }
        }


    } else if (strcmp(gConfig.TX.OPERATIONMODE, "AUTO_FIX") == 0) {
        sprintf(Line, "扣款操作模式:固定金額自動扣款");
        PrintStr(1, offsetY, Line, FontSize, FALSE);
        offsetY = offsetY + FONT_Height + 2;
        sprintf(Line, "預設票價 %3d-%3d-%3d-%3d-%3d-%3d-%3d-%3d-%3d-%3d",
                gConfig.TX.AMTTABLE[0].AMT[0], gConfig.TX.AMTTABLE[0].AMT[1], gConfig.TX.AMTTABLE[0].AMT[2], gConfig.TX.AMTTABLE[0].AMT[3], gConfig.TX.AMTTABLE[0].AMT[4],
                gConfig.TX.AMTTABLE[0].AMT[5], gConfig.TX.AMTTABLE[0].AMT[6], gConfig.TX.AMTTABLE[0].AMT[7], gConfig.TX.AMTTABLE[0].AMT[8], gConfig.TX.AMTTABLE[0].AMT[9]);
        PrintStr(1, offsetY, Line, d_FONT_9x18, FALSE);
        offsetY = offsetY + FONT_Height + 2;

    } else if (strcmp(gConfig.TX.OPERATIONMODE, "BARCODESCANNER") == 0) {
        sprintf(Line, "扣款操作模式:連接條碼掃描器");
        PrintStr(1, offsetY, Line, FontSize, FALSE);
        offsetY = offsetY + FONT_Height + 2;
    } else {
        sprintf(Line, "扣款操作模式:手動操作");
        PrintStr(1, offsetY, Line, FontSize, FALSE);
        offsetY = offsetY + FONT_Height + 2;
    }


    memset(Line, 0x00, sizeof (Line));
    sprintf(Line, "===========================");
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    FONT_Height = FontSize & 0x00ff;
    offsetY = offsetY + FONT_Height + 2;

    sprintf(Line, "目前時間:%04d/%02d/%02d %02d:%02d:%02d", RTC.bYear + 2000, RTC.bMonth, RTC.bDay, RTC.bHour, RTC.bMinute, RTC.bSecond);
    PrintStr(1, offsetY, Line, FontSize, FALSE);
    offsetY = offsetY + FONT_Height + 2;



    CTOS_PrinterBufferOutput(pPtr, (offsetY / 8));
    CTOS_PrinterFline(64);
    //free(pPtr);
}

void PrintMemoarystatus(int flag) {
    BYTE buf[64];
    ULONG ulUsedDiskSize, ulTotalDiskSize, ulUsedRamSize, ulTotalRamSize;
    CTOS_SystemMemoryStatus(&ulUsedDiskSize, &ulTotalDiskSize, &ulUsedRamSize, &ulTotalRamSize);
    sprintf(buf, "F%d. UsedRamSize =%ld\n", flag, ulUsedRamSize);
    CTOS_PrinterPutString(buf);
    return;
}
