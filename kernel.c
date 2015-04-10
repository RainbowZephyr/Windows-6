void printString(char*);
void readString(char[]);
void readSector(char*, int);
void handleInterrupt21(int, int, int, int);
int divide(int, int);
int mod(int, int);
void readFile(char[], char[]);

int main(){


char buffer[13312]; /*this is the maximum size of a file*/

makeInterrupt21();
interrupt(0x21, 3, "messag\0", buffer, 0); /*read the file into buffer*/
interrupt(0x21, 0, buffer, 0, 0); /*print out the file*/
while(1);

}

void printString(char* x){
  int i =0 ;
  while(x[i] != '\0'){
    char letter = x[i];
    interrupt(0x10, 0xE*256+letter, 0, 0, 0);
    i++;
  }
}

void readString(char string[]){
  int j=0;
  char x;
  int deletedBefore =0;
  string[j] = 0xA;
  j++;
  while(1){
    x = interrupt(0x16, string[j], 0, 0, 0);
    switch(x){ //enter
      case 0xD: string[j] = ' '; string[++j] = '\0'; string[++j] = 0xA; string[++j] = 0x3;  interrupt(0x10, 0xE*256+x, 0, 0, 0); return;
      break; //delete
      case 0x8: if(j>=1){
	--j;
	string[j]=0x0 ;
	if(!deletedBefore){
	  interrupt(0x10, 0xE*256+x, 0, 0, 0);
	  interrupt(0x10, 0xE*256+'\0', 0, 0, 0);
	  deletedBefore =1;
	} else {
	  interrupt(0x10, 0xE*256+x, 0, 0, 0);
	  interrupt(0x10, 0xE*256+x, 0, 0, 0);
	  interrupt(0x10, 0xE*256+'\0', 0, 0, 0);
	}
      } else {
	if(j==0){string[j]=0x0;
	  interrupt(0x10, 0xE*256+x, 0, 0, 0);
	  interrupt(0x10, 0xE*256+' ', 0, 0, 0);
	}
      }
      break;
      default: string[j] = x; interrupt(0x10, 0xE*256+x, 0, 0, 0); j++;
      break;
    }
  }
}

int divide(int number, int divisor){
  int counter=0;
  if(divisor == 0 ){
    return -1;
  } else {
    while(number >= divisor){
      number =number- divisor;
      counter++;
    }
    return counter;
  }
}

int mod(int number, int divisor){
  int dividend=divide(number , divisor);
  int remainder =number - divisor * dividend;
  return remainder;
}

void readSector(char* buffer, int sector){
  int relSector = mod(sector, 18) +1;
  int head = mod(divide(sector,18), 2);
  int track = divide(sector,36);
  interrupt(0x13,513, buffer, track*256+relSector, head*256);
}


 void handleInterrupt21(int ax, int bx, int cx, int dx){
  if (ax == 0) {
    printString(bx);
  } else {
      if (ax == 1) {
    readString(bx);
    }
   else {
      if (ax == 2) {
    readSector(bx);
    }
   else {
      if(ax == 3) {
    readFile(bx,cx);
    }
   else {
    printString("Error");
  }
  }
  }
}
}


void readFile(char name[], char buffer[]){
  char directorySector[512];
 // char buffer[13312];
  char tmpBuffer[512];
  char file[32];
  int i =-1;
  int sectors[26];
  int c=6;
  int tmp=0;
  int bufferCounter =0 ;
  readSector(directorySector, 2);


  while(i < 16 ){
        if(checkName(name, directorySector, i) == 0){
            i++;
        } else {
            break;
        }
  }

  if(i == -1){
    return;
  }
	while(c<32){
	if(directorySector[32*i + c] == 0x0){
		break;
	}
		readSector(tmpBuffer,directorySector[32*i+c]);

		while(tmp < 512){
			buffer[bufferCounter]=tmpBuffer[tmp];
			tmp++;
			bufferCounter++;
		}
		c++;
	}

}

int checkName(char name[] , char directoryName[],  int i){
  int c = 0;
  while(c < 6){
    if(name[c] != directoryName[32*i+c]){
      return 0;
    }
    c++;
  }
  return 1;
}
