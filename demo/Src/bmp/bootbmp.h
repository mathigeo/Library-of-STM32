#ifndef __BOOT_BMP_H
#define __BOOT_BMP_H



/*--  调入了一幅图像：.\otsu.bmp  --*/
/*--  宽度x高度=128x64  --*/
unsigned char bootbmp[]={
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0x7F,0x7F,0x7F,0x7F,0x3F,0x3F,0xBF,0xBF,0xBF,0xBF,0xBF,0xBF,0xBF,0xBF,
0x3F,0x7F,0x7F,0x7F,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x3F,0x3F,
0x3F,0x1F,0x1F,0x1F,0x1F,0x1F,0x3F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x1F,0x07,0x03,0x01,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC1,0xE3,0xF3,0xFB,0xFB,0xFD,0xFD,
0xFC,0xFE,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,0xFE,0xFE,0xFE,0xFC,0xFD,0xF9,0xF0,0xC0,0x80,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x07,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC0,0x80,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xC0,0xF0,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,
0x5F,0x1F,0x1F,0x1F,0x3F,0x3F,0x7F,0x7F,0xFF,0xFF,0xFF,0x7F,0x3F,0x7F,0x7F,0x3F,
0x1F,0x1F,0x1F,0x1F,0x5F,0x5F,0x5F,0xDF,0xDF,0xDF,0xFF,0xBF,0xFF,0xFF,0xFF,0xFF,
0xFE,0xF8,0xE0,0x80,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xFC,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
0xFE,0x3C,0x00,0xF8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,
0xFF,0xFB,0xF3,0x73,0xF8,0xFC,0xFC,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,0xFE,
0xF8,0xFB,0xF3,0xF3,0xF7,0xF7,0xFE,0xFC,0xFC,0xFC,0xFC,0xFC,0xFE,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFC,0xF2,0x9F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x7F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,
0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,
0x1F,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF9,0x0D,
0xC5,0xE4,0xF2,0xFB,0xFB,0xFB,0xF7,0xF7,0xF7,0xE7,0xE7,0x87,0xD7,0xF7,0xF7,0xFF,
0xFF,0x7F,0x7F,0x7E,0x7C,0x79,0x73,0xA7,0xC7,0xE7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x03,0x1F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFE,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xF8,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,
0x03,0x03,0x07,0x07,0x0F,0x0F,0x1F,0x3F,0x3F,0x3F,0x3F,0x3F,0x07,0x03,0x00,0x00,
0x00,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE3,
0xE0,0xFF,0xFF,0xFE,0xE6,0xCE,0xCC,0xDE,0xDE,0x9E,0x9E,0xDE,0xDE,0xEE,0xFE,0xF7,
0xF6,0xFB,0xFF,0xFE,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x3F,0x0F,0x01,0x00,0x00,0x00,0x00,0x01,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xF8,0xF0,
0xE0,0xE0,0xE0,0xE0,0xC0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x03,0x07,0x0F,0x0F,0x1F,0x3F,0x3F,0x3F,0x7F,0x7F,0x7F,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x3F,0x3F,0x1F,0x0F,
0x0F,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,0xFE,0xFC,0xFC,0xF8,0xF8,
0xF0,0xF0,0xF0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,
0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,
0xE0,0xE0,0xE1,0xE1,0xE1,0xE1,0xE1,0xE1,0xE1,0xE1,0xE3,0xE3,0xE3,0xE3,0xE3,0xE3,
0xE3,0xE3,0xE1,0xE1,0xE1,0xE1,0xE1,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,
0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
};


/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=16x16   --*/
unsigned char mateName[][32]={
/*阳*/
0x00,0xFE,0x02,0x22,0xDA,0x06,0x00,0xFC,0x04,0x04,0x04,0x04,0x04,0xFC,0x00,0x00,
0x00,0xFF,0x08,0x10,0x08,0x07,0x00,0xFF,0x41,0x41,0x41,0x41,0x41,0xFF,0x00,0x00,
/*海*/
0x10,0x60,0x02,0x0C,0xC0,0x10,0x08,0xF7,0x14,0x54,0x94,0x14,0xF4,0x04,0x00,0x00,
0x04,0x04,0x7C,0x03,0x00,0x01,0x1D,0x13,0x11,0x55,0x99,0x51,0x3F,0x11,0x01,0x00,
/*峰*/
0x00,0xF0,0x00,0xFF,0x00,0xF0,0x80,0x90,0x4C,0x57,0xA4,0x54,0x4C,0x84,0x80,0x00,
0x00,0x1F,0x10,0x0F,0x08,0x1F,0x10,0x10,0x15,0x15,0xFF,0x15,0x15,0x10,0x10,0x00
};

#endif /*__BOOT_BMP_H*/



