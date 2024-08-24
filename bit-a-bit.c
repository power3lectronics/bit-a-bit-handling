#include<stdio.h>

/*unsigned int convertToUtf16(unsigned int auxInt){
	unsigned int codeUnit[2];
	unsigned int utf16 = 0x0;

	if(auxInt >= 0x0000 || auxInt <= 0xFFFF){
		auxInt = auxInt; 
	}
	else if(auxInt >= 0x10000 || auxInt <= 0x10FFFF){
		auxInt = auxInt - 0x10000;
		if(ordem == 0){
			codeUnit[0] = (auxInt >> 10) + 0xD800;
			codeUnit[1] = (auxInt & 0x03FF) + 0xDC00;	 	
		}
		else if(ordem == 1){
			codeUnit[0] = (auxInt & 0x03FF) + 0xDC00;
			codeUnit[1] = (auxInt >> 10) + 0xD800;	 	
		}
		uft16 = ((utf16 | codeUnit[0]) << 10) | codeUnit[1]; 
	}
	fputc(utf16, arq_saida);
	
}*/

// int utf8to16(FILE* arq_entrada, FILE* arq_saida, int ordem)

int utf8to16(FILE* arq){
	int _char = 0; // character from file reading
	int shiftFirstByte = 0;
	int shiftInternalByte = 0;
	int auxCounter = 0;
	int countBitOne = 0;
	int remainingBytes = 0;
	int byteIndex = 0;
	unsigned int auxInt = 0x0;
	int verifyChar = 0x0;  	
	
	/*int bigEndian = 0xFEFF;
	int littleEndian  =  0xFFFE;
	
	if(ordem == 0){
		fputc(littleEndian, arq_saida);
	}
	else if(ordem == 1){
		fputc(bigEndian, arq_saida);
	}	
	*/	
	
	while((_char = fgetc(arq))!= EOF){		
		//printf("%x", _char);		
		byteIndex = byteIndex;	// indicates the byte position	
		
		verifyChar = _char & 0xF0; printf("%x\n", verifyChar);

		//if(verifyChar != 0x00 && verifyChar != 0xC0 && verifyChar != 0xE0 && verifyChar != 0xF0 && verifyChar != 0x80){
			//printf("BYTE ERROR!!");	
			//return (-1);
		//} 

		while(((_char << shiftFirstByte) & 0x80) == 0x80){ 					
			countBitOne += 1;
			shiftFirstByte += 1;
		}	
		
		if(((countBitOne == 0 || countBitOne >= 2) && 
  		   ((verifyChar != 0x00) && 
   			(verifyChar != 0xC0) && 
   			(verifyChar != 0xE0) && 
   			(verifyChar != 0xF0))) ||
   			((countBitOne == 1) && (verifyChar != 0x80))){ printf("INVALID BYTE\n"); }
				
		//else if(countBitOne == 1 && ver){
	
		if(countBitOne == 4){
			auxInt = (auxInt | (_char & 0x07)) << 18;
			remainingBytes = 3;
			auxCounter = remainingBytes;
			shiftInternalByte = 12;
		}
		
		//else if(countBitOne == 3){
		if(countBitOne == 3){
			auxInt = auxInt & 0x0;			
			auxInt = (auxInt | (_char & 0x0F)) << 12;
			remainingBytes = 2;
			auxCounter = remainingBytes;
			shiftInternalByte = 6;
		}
		else if(countBitOne == 2){
			auxInt = auxInt & 0x0;
			auxInt = (auxInt | (_char & 0x1F)) << 6;
			remainingBytes = 1;
			auxCounter = remainingBytes;
			shiftInternalByte = 0;
		}
		else if(countBitOne  == 1){
			if(remainingBytes == 3 && auxCounter != 0){
				auxInt = auxInt | (((auxInt & 0x0) | (_char & 0x3F)) << shiftInternalByte);
			}
			else if(remainingBytes == 2 && auxCounter != 0){
				auxInt = auxInt | (((auxInt & 0x0) | (_char & 0x3F)) << shiftInternalByte);
			}
			else if(remainingBytes == 1 && auxCounter != 0){
				auxInt = auxInt | (((auxInt & 0x0) | (_char & 0x3F)) << shiftInternalByte);
			}
			
			//if((shiftInternalByte != 0) && (auxCounter != 0)){
			if(shiftInternalByte != 0){
				shiftInternalByte -= 6;
			}
			if(auxCounter != 0){
				auxCounter -= 1;
			}
			
			if(auxCounter == 0){
				shiftInternalByte = 0;
				remainingBytes = 0;	
				byteIndex += 1;
				printf("%x\n", auxInt);
			} 
		}
		else if(countBitOne == 0){
			auxInt = auxInt & 0x7F;
		}
		
	countBitOne = 0;
	shiftFirstByte = 0;	
	}
		
	return 0;
}

int main(void){
	FILE* arq;
	arq = fopen("arqentrada.txt", "rb");
	utf8to16(arq);
	return 0;
}
