#include "font.h"


uint8_t FontLib[] = {  

   /* 0x00 [   ] [ 0 ] */ 
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,
   /* 0x01 [ ! ] [ 1 ] */ 
      0x20,0x20,0x20,0x20,0x20,0x00,0x20,
   /* 0x02 [ " ] [ 2 ] */ 
      0x48,0x48,0x90,0x00,0x00,0x00,0x00,
   /* 0x03 [ # ] [ 3 ] */ 
      0x50,0x50,0xF8,0x50,0xF8,0x50,0x50,
   /* 0x04 [ $ ] [ 4 ] */ 
      0x20,0x78,0xA0,0x70,0x28,0xF0,0x20,
   /* 0x05 [ % ] [ 5 ] */ 
      0xC8,0xC8,0x10,0x20,0x40,0x98,0x98,
   /* 0x06 [ & ] [ 6 ] */ 
      0x20,0x50,0x50,0x50,0xA8,0x90,0x68,
   /* 0x07 [ ' ] [ 7 ] */ 
      0x20,0x20,0x40,0x00,0x00,0x00,0x00,
   /* 0x08 [ ( ] [ 8 ] */ 
      0x10,0x20,0x40,0x40,0x40,0x20,0x10,
   /* 0x09 [ ) ] [ 9 ] */ 
      0x40,0x20,0x10,0x10,0x10,0x20,0x40,
   /* 0x0A [ * ] [ 10 ] */ 
      0x20,0xA8,0x70,0xF8,0x70,0xA8,0x20,
   /* 0x0B [ + ] [ 11 ] */ 
      0x00,0x20,0x20,0xF8,0x20,0x20,0x00,
   /* 0x0C [ , ] [ 12 ] */ 
      0x00,0x00,0x00,0x00,0x20,0x20,0x40,
   /* 0x0D [ - ] [ 13 ] */ 
      0x00,0x00,0x00,0xF8,0x00,0x00,0x00,
   /* 0x0E [ . ] [ 14 ] */ 
      0x00,0x00,0x00,0x00,0x00,0x60,0x60,
   /* 0x0F [ / ] [ 15 ] */ 
      0x08,0x08,0x10,0x20,0x40,0x80,0x80,
   /* 0x10 [ 0 ] [ 16 ] */ 
      0x70,0x88,0x98,0xA8,0xC8,0x88,0x70,
   /* 0x11 [ 1 ] [ 17 ] */ 
      0x20,0x60,0x20,0x20,0x20,0x20,0x70,
   /* 0x12 [ 2 ] [ 18 ] */ 
      0x70,0x88,0x08,0x10,0x20,0x40,0xF8,
   /* 0x13 [ 3 ] [ 19 ] */ 
      0x70,0x88,0x08,0x30,0x08,0x88,0x70,
   /* 0x14 [ 4 ] [ 20 ] */ 
      0x10,0x30,0x50,0x90,0xF8,0x10,0x10,
   /* 0x15 [ 5 ] [ 21 ] */ 
      0xF8,0x80,0xF0,0x08,0x08,0x88,0x70,
   /* 0x16 [ 6 ] [ 22 ] */ 
      0x30,0x40,0x80,0xF0,0x88,0x88,0x70,
   /* 0x17 [ 7 ] [ 23 ] */ 
      0xF8,0x08,0x10,0x20,0x40,0x40,0x40,
   /* 0x18 [ 8 ] [ 24 ] */ 
      0x70,0x88,0x88,0x70,0x88,0x88,0x70,
   /* 0x19 [ 9 ] [ 25 ] */ 
      0x70,0x88,0x88,0x78,0x08,0x10,0x60,
   /* 0x1A [ : ] [ 26 ] */ 
      0x00,0x60,0x60,0x00,0x60,0x60,0x00,
   /* 0x1B [ ; ] [ 27 ] */ 
      0x00,0x60,0x60,0x00,0x60,0x20,0x40,
   /* 0x1C [ < ] [ 28 ] */ 
      0x10,0x20,0x40,0x80,0x40,0x20,0x10,
   /* 0x1D [ = ] [ 29 ] */ 
      0x00,0x00,0xF8,0x00,0xF8,0x00,0x00,
   /* 0x1E [ > ] [ 30 ] */ 
      0x40,0x20,0x10,0x08,0x10,0x20,0x40,
   /* 0x1F [ ? ] [ 31 ] */ 
      0x70,0x88,0x08,0x10,0x20,0x00,0x20,
   /* 0x20 [ @ ] [ 32 ] */ 
      0x70,0x88,0xB8,0xA8,0xB8,0x80,0x78,
   /* 0x21 [ A ] [ 33 ] */ 
      0x20,0x50,0x88,0x88,0xF8,0x88,0x88,
   /* 0x22 [ B ] [ 34 ] */ 
      0xF0,0x88,0x88,0xF0,0x88,0x88,0xF0,
   /* 0x23 [ C ] [ 35 ] */ 
      0x70,0x88,0x80,0x80,0x80,0x88,0x70,
   /* 0x24 [ D ] [ 36 ] */ 
      0xF0,0x48,0x48,0x48,0x48,0x48,0xF0,
   /* 0x25 [ E ] [ 37 ] */ 
      0xF8,0x80,0x80,0xE0,0x80,0x80,0xF8,
   /* 0x26 [ F ] [ 38 ] */ 
      0xF8,0x80,0x80,0xF8,0x80,0x80,0x80,
   /* 0x27 [ G ] [ 39 ] */ 
      0x70,0x88,0x80,0x80,0x98,0x88,0x78,
   /* 0x28 [ H ] [ 40 ] */ 
      0x88,0x88,0x88,0xF8,0x88,0x88,0x88,
   /* 0x29 [ I ] [ 41 ] */ 
      0x70,0x20,0x20,0x20,0x20,0x20,0x70,
   /* 0x2A [ J ] [ 42 ] */ 
      0xF8,0x10,0x10,0x10,0x10,0x90,0x60,
   /* 0x2B [ K ] [ 43 ] */ 
      0x88,0x90,0xA0,0xC0,0xA0,0x90,0x88,
   /* 0x2C [ L ] [ 44 ] */ 
      0x80,0x80,0x80,0x80,0x80,0x80,0xF8,
   /* 0x2D [ M ] [ 45 ] */ 
      0x88,0xD8,0xA8,0x88,0x88,0x88,0x88,
   /* 0x2E [ N ] [ 46 ] */ 
      0x88,0x88,0xC8,0xA8,0x98,0x88,0x88,
   /* 0x2F [ O ] [ 47 ] */ 
      0x70,0x88,0x88,0x88,0x88,0x88,0x70,
   /* 0x30 [ P ] [ 48 ] */ 
      0xF0,0x88,0x88,0xF0,0x80,0x80,0x80,
   /* 0x31 [ Q ] [ 49 ] */ 
      0x70,0x88,0x88,0x88,0xA8,0x90,0x68,
   /* 0x32 [ R ] [ 50 ] */ 
      0xF0,0x88,0x88,0xF0,0xA0,0x90,0x88,
   /* 0x33 [ S ] [ 51 ] */ 
      0x70,0x88,0x80,0x70,0x08,0x88,0x70,
   /* 0x34 [ T ] [ 52 ] */ 
      0xF8,0x20,0x20,0x20,0x20,0x20,0x20,
   /* 0x35 [ U ] [ 53 ] */ 
      0x88,0x88,0x88,0x88,0x88,0x88,0x70,
   /* 0x36 [ V ] [ 54 ] */ 
      0x88,0x88,0x88,0x88,0x88,0x50,0x20,
   /* 0x37 [ W ] [ 55 ] */ 
      0x88,0x88,0x88,0xA8,0xA8,0xD8,0x88,
   /* 0x38 [ X ] [ 56 ] */ 
      0x88,0x88,0x50,0x20,0x50,0x88,0x88,
   /* 0x39 [ Y ] [ 57 ] */ 
      0x88,0x88,0x50,0x20,0x20,0x20,0x20,
   /* 0x3A [ Z ] [ 58 ] */ 
      0xF8,0x08,0x10,0x20,0x40,0x80,0xF8,
   /* 0x3B [ [ ] [ 59 ] */ 
      0x70,0x40,0x40,0x40,0x40,0x40,0x70,
   /* 0x3C [ \ ] [ 60 ] */ 
      0x80,0x80,0x40,0x20,0x10,0x08,0x08,
   /* 0x3D [ ] ] [ 61 ] */ 
      0x70,0x10,0x10,0x10,0x10,0x10,0x70,
   /* 0x3E [ ^ ] [ 62 ] */ 
      0x20,0x50,0x88,0x00,0x00,0x00,0x00,
   /* 0x3F [ _ ] [ 63 ] */ 
      0x00,0x00,0x00,0x00,0x00,0x00,0xF8,
   /* 0x40 [ ` ] [ 64 ] */ 
      0x20,0x20,0x10,0x00,0x00,0x00,0x00,
   /* 0x41 [ a ] [ 65 ] */ 
      0x00,0x70,0x08,0x68,0x98,0x98,0x68,
   /* 0x42 [ b ] [ 66 ] */ 
      0x80,0x80,0x80,0xE0,0x90,0x90,0xE0,
   /* 0x43 [ c ] [ 67 ] */ 
      0x00,0x00,0x00,0x70,0x80,0x80,0x70,
   /* 0x44 [ d ] [ 68 ] */ 
      0x08,0x08,0x08,0x38,0x48,0x48,0x38,
   /* 0x45 [ e ] [ 69 ] */ 
      0x00,0x00,0x70,0x88,0xF8,0x80,0x78,
   /* 0x46 [ f ] [ 70 ] */ 
      0x30,0x48,0x40,0xE0,0x40,0x40,0x40,
   /* 0x47 [ g ] [ 71 ] */ 
      0x70,0x88,0x98,0x68,0x08,0x08,0x70,
   /* 0x48 [ h ] [ 72 ] */ 
      0x80,0x80,0x80,0xB0,0xC8,0x88,0x88,
   /* 0x49 [ i ] [ 73 ] */ 
      0x00,0x20,0x00,0x60,0x20,0x20,0x70,
   /* 0x4A [ j ] [ 74 ] */ 
      0x10,0x00,0x30,0x10,0x10,0x90,0x60,
   /* 0x4B [ k ] [ 75 ] */ 
      0x80,0x80,0x90,0xA0,0xC0,0xA0,0x90,
   /* 0x4C [ l ] [ 76 ] */ 
      0x60,0x20,0x20,0x20,0x20,0x20,0x20,
   /* 0x4D [ m ] [ 77 ] */ 
      0x00,0x00,0x50,0xA8,0xA8,0x88,0x88,
   /* 0x4E [ n ] [ 78 ] */ 
      0x00,0x00,0xB0,0xC8,0x88,0x88,0x88,
   /* 0x4F [ o ] [ 79 ] */ 
      0x00,0x00,0x70,0x88,0x88,0x88,0x70,
   /* 0x50 [ p ] [ 80 ] */ 
      0x00,0xE0,0x90,0x90,0xE0,0x80,0x80,
   /* 0x51 [ q ] [ 81 ] */ 
      0x00,0x38,0x48,0x48,0x38,0x08,0x08,
   /* 0x52 [ r ] [ 82 ] */ 
      0x00,0x00,0xB0,0xC8,0x80,0x80,0x80,
   /* 0x53 [ s ] [ 83 ] */ 
      0x00,0x00,0x78,0x80,0x70,0x08,0xF0,
   /* 0x54 [ t ] [ 84 ] */ 
      0x40,0x40,0xE0,0x40,0x40,0x48,0x30,
   /* 0x55 [ u ] [ 85 ] */ 
      0x00,0x00,0x88,0x88,0x88,0x98,0x68,
   /* 0x56 [ v ] [ 86 ] */ 
      0x00,0x00,0x88,0x88,0x88,0x50,0x20,
   /* 0x57 [ w ] [ 87 ] */ 
      0x00,0x00,0x88,0x88,0xA8,0xA8,0x50,
   /* 0x58 [ x ] [ 88 ] */ 
      0x00,0x00,0x88,0x50,0x20,0x50,0x88,
   /* 0x59 [ y ] [ 89 ] */ 
      0x00,0x88,0x88,0x78,0x08,0x88,0x70,
   /* 0x5A [ z ] [ 90 ] */ 
      0x00,0x00,0xF8,0x10,0x20,0x40,0xF8,
   /* 0x5B [ { ] [ 91 ] */ 
      0x30,0x40,0x40,0x80,0x40,0x40,0x30,
   /* 0x5C [ | ] [ 92 ] */ 
      0x20,0x20,0x20,0x00,0x20,0x20,0x20,
   /* 0x5D [ } ] [ 93 ] */ 
      0x60,0x10,0x10,0x08,0x10,0x10,0x60,
   /* 0x5E [ ~ ] [ 94 ] */ 
      0x40,0xA8,0x10,0x00,0x00,0x00,0x00,
 };