#include "Arduino.h"
#include "linky.h"

#include <SoftwareSerial.h>

Linky::Linky(int RXPin, int TXPin) {
	_pin_RX = RXPin;
	_pin_TX = TXPin;
}

void Linky::begin() {
	_serport = new SoftwareSerial(_pin_RX, _pin_TX); // RX, TX
	_serport->begin(LINKY_COM_RATE);
}

bool Linky::isValidNumber(String str){
   for(byte i=0;i<str.length();i++)  {
       if(!isDigit(str.charAt(i))) return false;
   }
   return true;
}

int Linky::getCommandValue_int(String CMD, int CMDlenght, int CMDResultLenght, String line, int lineLenght, int defaultIfError) {
  if(!line.startsWith(CMD)) { return defaultIfError; }
  if(CMDlenght+1+CMDResultLenght > lineLenght) { return defaultIfError; } // Invalid size line length too short
  
  String raw_value = line.substring(CMDlenght+1, CMDlenght+1+CMDResultLenght);
  if(!isValidNumber(raw_value)) { return defaultIfError; }
  
  return raw_value.toInt();
}

long Linky::getCommandValue_long(String CMD, int CMDlenght, int CMDResultLenght, String line, int lineLenght, long defaultIfError) {
  if(!line.startsWith(CMD)) { return defaultIfError; }
  if(CMDlenght+1+CMDResultLenght > lineLenght) { return defaultIfError; } // Invalid size line length too short
  
  String raw_value = line.substring(CMDlenght+1, CMDlenght+1+CMDResultLenght);
  if(!isValidNumber(raw_value)) { return defaultIfError; }
  
  return (long)raw_value.toInt();
}

bool Linky::getCommandValue_str(String CMD, int CMDlenght, int CMDResultLenght, String line, int lineLenght, char* value) {
  if(!line.startsWith(CMD)) { return false; }
  if(CMDlenght+1+CMDResultLenght > lineLenght) { return false; } // Invalid size line length too short
  
  line.substring(CMDlenght+1, CMDlenght+1+CMDResultLenght).toCharArray(value,CMDResultLenght+1);
  return true;
} 

void Linky::updateStruct(int len) {
						getCommandValue_str ("ADCO"    , 4,12,_buffer,len+1, _data.ADCO     );
						getCommandValue_str ("OPTARIF" , 7, 4,_buffer,len+1, _data.OPTARIF  );
	_data.ISOUSC 	=	getCommandValue_int ("ISOUSC"  , 6, 2,_buffer,len+1, _data.ISOUSC);
	_data.HCHC   	=	getCommandValue_long("HCHC"    , 4, 9,_buffer,len+1, _data.HCHC);
	_data.HCHP   	=	getCommandValue_long("HCHP"    , 4, 9,_buffer,len+1, _data.HCHP);
	_data.EJPHN  	=	getCommandValue_long("EJPHN"   , 5, 9,_buffer,len+1, _data.EJPHN);
	_data.EJPHPM 	=	getCommandValue_long("EJPHPM"  , 6, 9,_buffer,len+1, _data.EJPHPM);
	_data.BBRHCJB	=	getCommandValue_long("BBRHCJB" , 7, 9,_buffer,len+1, _data.BBRHCJB);
	_data.BBRHPJB	=	getCommandValue_long("BBRHPJB" , 7, 9,_buffer,len+1, _data.BBRHPJB);
	_data.BBRHCJW	=	getCommandValue_long("BBRHCJW" , 7, 9,_buffer,len+1, _data.BBRHCJW);
	_data.BBRHPJW	=	getCommandValue_long("BBRHPJW" , 7, 9,_buffer,len+1, _data.BBRHPJW);
	_data.BBRHCJR	=	getCommandValue_long("BBRHCJR" , 7, 9,_buffer,len+1, _data.BBRHCJR);
	_data.BBRHPJR	=	getCommandValue_long("BBRHPJR" , 7, 9,_buffer,len+1, _data.BBRHPJR);
	_data.PEJP   	=	getCommandValue_int ("PEJP"    , 4, 2,_buffer,len+1, _data.HCHP);
						getCommandValue_str ("PTEC"    , 4, 4,_buffer,len+1, _data.PTEC  );
						getCommandValue_str ("DEMAIN"  , 6, 4,_buffer,len+1, _data.DEMAIN  );
	_data.IINST     = 	getCommandValue_int ("IINST"   , 5, 3,_buffer,len+1, _data.IINST); 
	_data.IINST1    = 	getCommandValue_int ("IINST1"  , 6, 3,_buffer,len+1, _data.IINST1); 
	_data.IINST2    = 	getCommandValue_int ("IINST2"  , 6, 3,_buffer,len+1, _data.IINST2); 
	_data.IINST3    = 	getCommandValue_int ("IINST3"  , 6, 3,_buffer,len+1, _data.IINST3); 
	_data.ADPS      = 	getCommandValue_int ("ADPS"    , 4, 3,_buffer,len+1, _data.ADPS); 
	_data.ADIR1     = 	getCommandValue_int ("ADIR1"   , 5, 3,_buffer,len+1, _data.ADIR1); 
	_data.ADIR2     = 	getCommandValue_int ("ADIR2"   , 5, 3,_buffer,len+1, _data.ADIR2); 
	_data.ADIR3     = 	getCommandValue_int ("ADIR3"   , 5, 3,_buffer,len+1, _data.ADIR3);
	_data.IMAX      = 	getCommandValue_int ("IMAX"    , 4, 3,_buffer,len+1, _data.IMAX); 
	_data.IMAX1     = 	getCommandValue_int ("IMAX1"   , 5, 3,_buffer,len+1, _data.IMAX1); 
	_data.IMAX2     = 	getCommandValue_int ("IMAX2"   , 5, 3,_buffer,len+1, _data.IMAX2); 
	_data.IMAX3     = 	getCommandValue_int ("IMAX3"   , 5, 3,_buffer,len+1, _data.IMAX3); 
	_data.PMAX      = 	getCommandValue_long("PMAX"    , 4, 5,_buffer,len+1, _data.PMAX); 
	_data.PAPP      = 	getCommandValue_long("PAPP"    , 4, 5,_buffer,len+1, _data.PAPP); 
						getCommandValue_str ("MOTDETAT", 8, 6,_buffer,len+1, _data.MOTDETAT );
						getCommandValue_str ("PPOT"    , 4, 2,_buffer,len+1, _data.PPOT);
}

void Linky::update(int timeout) {
	char currentChar;
	bool readingLine = false;
	int bufferIterator = 0;

	_serport->flush();
	
	while (currentChar != LINKY_START_FRAME) {
		if (_serport->available()) {
			currentChar = _serport->read() & 0x7F;
		}
		yield();
	}


	while(true) {
		yield();
		if (_serport->available()) {
			currentChar = _serport->read() & 0x7F;
			
			if(currentChar == LINKY_END_FRAME) { return; }
			else if(currentChar == LINKY_START_LINE) { 
				memset(_buffer, 0, LINKY_BUFFER_TELEINFO_SIZE);
				readingLine = true;
			}
			else if(currentChar == LINKY_END_LINE) { 
				updateStruct(bufferIterator);
				readingLine = false;
				bufferIterator = 0;
			}
			else if(currentChar == LINKY_END_DATA) { return; } 
			else {
				if(readingLine) {
					_buffer[bufferIterator] = currentChar;
					bufferIterator++;
				}
			}
		}
	}
}

LinkyData Linky::grab() {
	return _data;
}