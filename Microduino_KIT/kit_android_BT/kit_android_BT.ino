#include "U8glib.h"

String comdata = "";  //显示的字符串
String onedata = "";  //判断clean缓存字符串

static  unsigned long k,m;

int pinRx = 0;
int pinTx = 1;

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);	
// HW SPI Com: CS = 10, A0 = 9 (Hardware Pins are  SCK = 13 and MOSI = 11)
static unsigned char u8g_logo_bits[] U8G_PROGMEM = {
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x01,0xE0,
  0x03,0x00,0x00,0x00,0x00,0x7E,0x00,0xF0,0x01,0x00,0x00,0x00,
  0x00,0xFE,0xF9,0xF7,0x07,0x00,0x00,0x00,0x00,0x3C,0x00,0xF8,
  0x03,0x00,0x00,0x00,0x00,0xFC,0xF9,0xE1,0x03,0x00,0x00,0x00,
  0x00,0x38,0x00,0xF0,0x01,0x00,0x00,0x00,0x00,0xFC,0xFF,0x01,
  0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0xFC,0xEF,0xF9,0x8F,0xD7,0x73,0xF1,0xC1,0x3B,0x9F,0xFF,
  0xFF,0x1E,0x3E,0x00,0x00,0xBC,0xEF,0xC1,0xE1,0x9F,0xFF,0xDD,
  0xE3,0x3F,0xCC,0xE1,0xF0,0xBF,0x7B,0x00,0x00,0x3C,0xF7,0xE1,
  0xE1,0x9F,0xFF,0xC6,0xF7,0x3E,0x8E,0xF3,0xF0,0xFF,0xF8,0x00,
  0x00,0x3C,0xF3,0xE1,0xF1,0x93,0xFF,0xE6,0xF7,0x3C,0x8F,0xF7,
  0xF0,0xFF,0xFC,0x00,0x00,0x7C,0xF2,0xE1,0xF1,0x83,0x87,0xFE,
  0xF7,0x39,0xFF,0xF7,0xF0,0xFF,0xFF,0x00,0x00,0x7C,0xF0,0xE3,
  0xF3,0xA3,0x03,0xFE,0xF7,0x3F,0xFF,0xF7,0x71,0xFC,0xFF,0x00,
  0x00,0x7C,0xF8,0xE3,0xF3,0xBF,0x03,0xFE,0xE3,0x3F,0xFF,0xF3,
  0x71,0xDC,0x7F,0x00,0x00,0x7E,0xFC,0xE7,0xE3,0xBF,0x03,0xFC,
  0xE3,0x3F,0xFE,0xF3,0x71,0x9C,0x7F,0x00,0x00,0xC1,0x03,0xF8,
  0xCF,0xE7,0x0F,0xF0,0x00,0x7F,0xFC,0xFC,0xFF,0x3E,0x1E,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };//Microduino

static unsigned char u8g_logo_bits1[] U8G_PROGMEM = { 

  0x00,0x40,0x00,0x00,0x00,0xC0,0x00,0x00,0x00,0xC0,0x03,0x00,0x00,0xC0,0x07,0x00,
  0x00,0xC0,0x0F,0x00,0x00,0xC0,0x1F,0x00,0x00,0xC0,0x3F,0x00,0x00,0xC0,0x7F,0x00,
  0xC0,0xC1,0xFB,0x00,0xE0,0xC3,0xE3,0x03,0xC0,0xC7,0xF3,0x03,0x80,0xCF,0xFB,0x01,
  0x00,0xDF,0x7F,0x00,0x00,0xFE,0x3F,0x00,0x00,0xF8,0x1F,0x00,0x00,0xF0,0x0F,0x00,
  0x00,0xE0,0x03,0x00,0x00,0xF0,0x07,0x00,0x00,0xFC,0x1F,0x00,0x00,0xFE,0x3F,0x00,
  0x00,0xDF,0x7F,0x00,0x80,0xCF,0xFB,0x00,0xE0,0xC7,0xF3,0x01,0xE0,0xC1,0xE3,0x03,
  0xC0,0xC0,0xF3,0x03,0x00,0xC0,0xFF,0x00,0x00,0xC0,0x7F,0x00,0x00,0xC0,0x1F,0x00,
  0x00,0xC0,0x0F,0x00,0x00,0xC0,0x03,0x00,0x00,0xC0,0x01,0x00,0x00,0x40,0x00,0x00,/*"C:\Users\ylb\Desktop\bluetooth1.bmp",0*/
};//Microduino
static unsigned char u8g_logo_bits2[] U8G_PROGMEM = { 
  0x00,0x04,0x60,0x00,0x00,0x0C,0x20,0x00,0x00,0xEC,0x37,0x00,0x00,0xF8,0x1F,0x00,
  0x00,0xFE,0x7F,0x00,0x00,0xFF,0xFF,0x00,0x80,0xF7,0xEF,0x01,0x80,0xFF,0xFF,0x01,
  0x80,0xFF,0xFF,0x03,0x80,0xFF,0xFF,0x03,0x98,0xFF,0xFF,0x3B,0xBC,0xFF,0xFF,0x7B,
  0xBE,0xFF,0xFF,0x7B,0xBE,0xFF,0xFF,0x7B,0xBE,0xFF,0xFF,0x7B,0xBE,0xFF,0xFF,0x7B,
  0xBE,0xFF,0xFF,0x7B,0xBE,0xFF,0xFF,0x7B,0xBE,0xFF,0xFF,0x7B,0xBE,0xFF,0xFF,0x7B,
  0xBE,0xFF,0xFF,0x7B,0xBC,0xFF,0xFF,0x3B,0x98,0xFF,0xFF,0x13,0x80,0xFF,0xFF,0x03,
  0x80,0xFF,0xFF,0x01,0x00,0xFF,0xFF,0x00,0x00,0x7C,0x3E,0x00,0x00,0x7C,0x3E,0x00,
  0x00,0x7C,0x3E,0x00,0x00,0x7C,0x3E,0x00,0x00,0x78,0x3E,0x00,0x00,0x10,0x08,0x00,/*"C:\Users\ylb\Desktop\android.bmp",0*/};//Microduino 

void setup()
{  
  Serial.begin(9600);
  pinMode(pinTx,OUTPUT);
  pinMode(pinRx,INPUT);
  while(!Serial)
  {
  }
}

void draw(void) {  
  u8g.setFont(u8g_font_7x14);

  u8g.drawXBMP( 0, 0, 128, 18, u8g_logo_bits);//Microdiuno
  u8g.drawXBMP( 96,20, 32, 32, u8g_logo_bits2);//Android 
  u8g.drawXBMP( 0,20, 32, 32, u8g_logo_bits1);//Bluetooth
  u8g.setPrintPos(0, 64); 
  u8g.print(comdata);
}
void loop()
{

  while (Serial.available() > 0)  //判断串口是否有输入
  {

    comdata = "";                     //清空显示字符
    onedata += char(Serial.read()); //读取字符
    comdata += onedata;               //同上
    delay(2);                         //等待串口缓存

  }

  //Serial.println(comdata);
 // Serial.println(onedata);

  if(onedata=="clean")           //清屏
    comdata = "";
    onedata = "";  //缓存字符串清空

  u8g.firstPage();  
  do {
    draw();
  } 
  while( u8g.nextPage() );
  delay(100);
}



