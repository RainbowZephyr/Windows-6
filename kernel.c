void printString(char*);
void readString(char[]);
void readSector(char*, int);
void handleInterrupt21(int, int, int, int);
int divide(int, int);
int mod(int, int);
void readFile(char[], char[]);
void executeProgram(char* , int);
void terminate();
void writeSector(char*, int);
void deleteFile(char*);
void writeFile(char* , char*, int);


int main(){

  makeInterrupt21();
  interrupt(0x21,4, "shell\0", 0x2000, 0); //write file testW//
  // interrupt(0x21, 4, "tstpr2\0", 0x2000, 0);
  // interrupt(0x21, 7,"messag\0", 0, 0);
  // interrupt(0x21, 3, "messag\0", buffer, 0); // try to read messag
  // interrupt(0x21, 0, buffer, 0, 0);

  //   int i=0;
  //   char buffer1[13312];
  //   char buffer2[13312];
  //   buffer2[0]='h'; buffer2[1]='e'; buffer2[2]='l'; buffer2[3]='l';
  //   buffer2[4]='o';
  //   for(i=5; i<13312; i++) buffer2[i]=0x0;
  //   makeInterrupt21();
  //   interrupt(0x21,8, "testW\0", buffer2, 1); //write file testW
  //   interrupt(0x21,3, "testW\0", buffer1, 0); //read file testW
  //   interrupt(0x21,0, buffer1, 0, 0); // print out contents of testW


  while(1);

}

void printString(char* x){
  int i =0 ;
  char letter;
  while(x[i] != '\0'){
    letter = x[i];
    interrupt(0x10, 0xE*256+letter, 0, 0, 0);
    i++;
  }
}

void readString(char string[]){
  int j=0;
  char x;
  while(1){
    x = interrupt(0x16, string[j], 0, 0, 0);
    switch(x){ //enter
      case 0xD: string[j] = 0xD; string[++j] = 0xA; string[++j] = 0x0; interrupt(0x10, 0xE*256+' ', 0, 0, 0); interrupt(0x10, 0xE*256+x, 0, 0, 0); interrupt(0x10, 0xE*256+0xA, 0, 0, 0); return;
      break; //delete
      case 0x8: if(j>0){//     i=0;
	//     while(i<7){
	//       if(line[i] != exec[i]){
	// 	ce = 0;
	// 	break;
	//       }
	//       i++;
	//     }

	//     i=0;
	//     while(i<6){
	//       if(line[i] != delete[i]){
	// 	cd = 0;
	// 	break;
	//       }
	//       i++;
	//     }
	interrupt(0x10, 0xE*256+0x8, 0, 0, 0);
	interrupt(0x10, 0xE*256+0x0, 0, 0, 0);
	interrupt(0x10, 0xE*256+0x8, 0, 0, 0);
	j--;
      } else {
	string[j] = x;
	interrupt(0x10, 0xE*256+string[j], 0, 0, 0);
      }break;
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
      number = number- divisor;
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
  switch(ax){
    case 0: printString(bx); break;
    case 1: readString(bx); break;
    case 2: readSector(bx,cx); break;
    case 3: readFile(bx,cx); break;
    case 4: executeProgram(bx,cx); break;
    case 5: terminate(); break;
    case 6: writeSector(bx,cx); break;
    case 7: deleteFile(bx); break;
    case 8: writeFile(bx,cx,dx);  break;
    default: printString("Unknown Interrupt"); break;
  }

}


void readFile(char name[], char buffer[]){
  char directorySector[512];
  char tmpBuffer[512];
  int i =-1;
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


void executeProgram(char* name, int segment){
  int i = 0;
  char buffer[13312];

  readFile(name, buffer);

  while(i < 13312){
    putInMemory(segment, i ,buffer[i]);
    i++;
  }
  launchProgram(segment);

}
void terminate(){
  //while(1);
  interrupt(0x21, 4, "shell\0", 0x2000, 0);

}

void writeSector(char* buffer, int sector){
  int relSector = mod(sector, 18) +1;
  int head = mod(divide(sector,18), 2);
  int track = divide(sector,36);
  interrupt(0x13,769, buffer, track*256+relSector, head*256);
}

void deleteFile(char* name){
  char directorySector[512];
  char map[512];
  char file[32];
  int i =-1;
  int sectors[26];
  int c=6;
  int tmp=0;
  int bufferCounter =0 ;

  readSector(directorySector, 2);
  readSector(map, 1);

  while(i < 16 ){
    if(checkName(name, directorySector, i) == 0){
      i++;
    } else {
      break;
    }
  }

  directorySector[32*i] = 0x0;
  writeSector(directorySector,2);

  if(i == -1){
    return;
  }
  while(c<32){
    map[directorySector[32*i + c]+1] = 0x0;
    c++;
  }
  writeSector(map , 1);
}

void writeFile(char* name, char* buffer, int secNum){
  char directorySector[512];
  char tmpBuffer[512];
  char map[512];
  int dirCounter =0;
  int bufferCounter =0 ;
  int fileCounter=0;
  int sectorCounter =6;
  int mapCounter;
  int freeDir =0;
  int freeSector = 0;
  int bufferSize =0;
  int tmp;
  int globalCounter = 0;
  int bufferWrites;


  readSector(directorySector, 2); //load directory
  readSector(map, 1); //load map

  while(buffer[bufferSize] != '\0'){  //check file size
    bufferSize++;
  }

  bufferWrites = divide(bufferSize ,512);

  if(mod(bufferSize, 512) != 0){
    bufferWrites++;
  }

  while(dirCounter < 16){ // check for empty directory
    if(directorySector[dirCounter*32] == 0x0){
      freeDir =1;
      break;
    } else{
      dirCounter++;
    }
  }

  if(freeDir == 0){
    return;
  }

  while(name[fileCounter] != '\0'){ // copy name of file
    directorySector[dirCounter*32 + fileCounter] = name[fileCounter];
    fileCounter++;
  }

  if(fileCounter != 5){ //fill rest of name with 0s
    while(fileCounter < 6){
      directorySector[dirCounter*32 + fileCounter] = 0x0;
      fileCounter++;
    }
  }

  while(globalCounter < bufferWrites){

    mapCounter=0;
    while(mapCounter < 512){ //find free sector in map
      if(map[mapCounter] == 0x0){
	map[mapCounter] = 0xFF;
	freeSector =1;
	break;
      }else{
	mapCounter++;
      }
    }

    if(freeSector ==0){
      return;
    }

    tmp=0;
    while(tmp < 512){ //write 512 byte in tmp array
      tmpBuffer[tmp] = buffer[bufferCounter];
      tmp++;
      bufferCounter++; //counter to hold position of data from buffer
    }

    directorySector[32 * dirCounter + sectorCounter]  = mapCounter +1;
    writeSector(tmpBuffer , mapCounter + 1);
    writeSector(map ,1);
    writeSector(directorySector ,2);

    globalCounter++;
  }

}














