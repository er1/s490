#include "util.h"

void hexDump(void * data, size_t byteLen)
{
  unsigned int line, col;
  char hex[49];
  char ascii[17];

  memset(hex, 0, 48);
  memset(ascii, 0, 16);

  if(byteLen == 0) 
    return;
 
  printf("0x  00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F \n");
  for(line=0; line<(byteLen/16)+1; line++)
    {
      for(col=0; col<16; col++)
	{
	  unsigned int pos = 16*line + col;
	  unsigned char curByte;
	  
	  if(pos>=byteLen)
	    break;

	  curByte = *((unsigned char *)(data+pos));
	  sprintf(hex, "%s%02X ", hex, curByte);
	  
	  if( curByte>=32 && curByte<127 )
	    sprintf(ascii, "%s%c", ascii, curByte);
	  else
	    sprintf(ascii, "%s%s", ascii, ".");
	}
      printf("%02X  %-48s %-16s\n", line, hex, ascii);
      memset(hex, 0, 48);
      memset(ascii, 0, 16);
    }
}
