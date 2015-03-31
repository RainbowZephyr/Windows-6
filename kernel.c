void printString(char*);
void readString(char[]);
void readSector(char*, int);
void handleInterrupt21(int, int, int, int);
int divide(int, int);
int mod(int, int);
char* readFile(char[], char*);

int main(){
//  int i=0;
// char buffer[512];
 //readSector(buffer, 30);
 //printString(buffer);
// while(i<512)
// {
//   interrupt(0x10, 0xE*256+buffer[i], 0, 0, 0);
//   i++;
// }

// makeInterrupt21();
// interrupt(0x21,0,0,0,0);


makeInterrupt21();
interrupt(0x21,1,line,0,0);
interrupt(0x21,0,line,0,0);

 char line[80];
 readString(line);
 printString(line);
 //makeInterrupt21();
// interrupt(0x21,1,line,0,0);
// interrupt(0x21,0,line,0,0);

//while(1);
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
  } else if (ax == 1) {
    readString(bx);
  } else if (ax == 2) {
    readSector(bx);
  } else {
    printString("Error");
  }

}

char* readFile(char[] name){
  char directorySector[512];
  readSector(directorySector, );

}

void executeProgram(char* name, int segment){

}


