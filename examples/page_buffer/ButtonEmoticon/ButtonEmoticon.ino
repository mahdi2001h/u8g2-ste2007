/*

  ButtonEmoticon.ino

  Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)

  Copyright (c) 2021, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  
     
*/

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif


/*
  U8g2lib Example Overview:
    Frame Buffer Examples: clearBuffer/sendBuffer. Fast, but may not work with all Arduino boards because of RAM consumption
    Page Buffer Examples: firstPage/nextPage. Less RAM usage, should work with all Arduino boards.
    U8x8 Text Only Example: No RAM usage, direct communication with display controller. No graphics, 8x8 Text only.
    
  This is a page buffer example.    
*/

U8G2_STE2007_96X68_F_3W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* reset=*/ 8);


void setup(void) {

  u8g2.begin();  
}

uint8_t width = 5;
uint8_t width_state = 1;
uint8_t border = 0;
uint8_t border_state = 1;
uint8_t emoticons = 0;
uint8_t emoticons_state = 1;
uint8_t offset = 0;
uint8_t offset_state = 1;

void wave(uint8_t min, uint8_t max, uint8_t &v, uint8_t &state) {
  if ( state ) {
    v++;
    if ( v >= max )
      state = 0;
  } else {
    v--;
    if ( v <= min )
      state = 1;
  }
}

void loop(void) {
  u8g2_uint_t x = u8g2.getDisplayWidth()/2;
  u8g2_uint_t y = u8g2.getDisplayHeight()/2;
  char text[2] = " ";
  y += offset>>4;
  text[0] = (emoticons>>2)+32;
  u8g2.setFont(u8g2_font_emoticons21_tr);
  u8g2.firstPage();
  do {
    u8g2.drawButtonUTF8(x, y, U8G2_BTN_HCENTER | (border>>2), width, 1, 1, text);
  } while ( u8g2.nextPage() );
  delay(30);
  wave(7, u8g2.getDisplayWidth()/2, width, width_state);
  wave(0, 3<<2, border, border_state);
  wave(0, 7<<2, emoticons, emoticons_state);
  wave(0, 11<<4, offset, offset_state);
}

