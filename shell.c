
int main (){
  while(1){
    char line[100];
    char buffer[13312];
    char programName[6];
    char fileName[6];
    interrupt(0x21, 0, "shell> \0 ", 0, 0);
    interrupt(0x21, 1, line, 0, 0);

/*    if(line[0] == 'v' && line[1] == 'i' && line[2] == 'e' && line[3] == 'w' ){
      programName[0] = line[5];
      programName[1] = line[6];
      programName[2] = line[7];
      programName[3] = line[8];
      programName[4] = line[9];
      programName[5] = line[10];

      interrupt(0x21, 3,programName, buffer, 0);
      interrupt(0x21, 0, buffer, 0, 0);
    } else {
      interrupt(0x21, 0, "Bad Command\0 ", 0, 0);
    } */

/*    if(line[0] == 'e' && line[1] == 'x' && line[2] == 'e' && line[3] == 'c' && line[4] == 'u' && line[5] == 't' && line[6] == 'e' ){

      programName[0] = line[8];
      programName[1] = line[9];
      programName[2] = line[10];
      programName[3] = line[11];
      programName[4] = line[12];
      programName[5] = line[13];

    } else {
      interrupt(0x21, 0, "Bad Command\0 ", 0, 0);
    } */

/*    if(line[0] == 'c' && line[1] == 'o' && line[2] == 'p' && line[3] == 'y'){

      programName[0] = line[5];
      programName[1] = line[6];
      programName[2] = line[7];
      programName[3] = line[8];
      programName[4] = line[9];
      programName[5] = line[10];

      fileName[0] =  line[12];
      fileName[1] =  line[13];
      fileName[2] =  line[14];
      fileName[3] =  line[15];
      fileName[4] =  line[16];
      fileName[5] =  line[17];

      interrupt(0x21, 3,programName, buffer, 0);
      interrupt(0x21, 8, fileName, buffer , 0);
      interrupt(0x21, 0,buffer, 0, 0);
    } else {
      interrupt(0x21, 0, "Bad Command\0 ", 0, 0);
    }
*/
 /*   if(line[0] == 'd' && line[1] == 'e' && line[2] == 'l' && line[3] == 'e' && line[4] == 't' && line[5] == 'e'){

      programName[0] = line[6];
      programName[1] = line[7];
      programName[2] = line[8];
      programName[3] = line[9];
      programName[4] = line[10];
      programName[5] = line[11];

      interrupt(0x21, 7, programName, 0, 0);
    } else {
      interrupt(0x21, 0, "Bad Command\0 ", 0, 0);
    }

*/
    if(line[0] == 'd' && line[1] == 'i' && line[2] == 'r'){

      char directory[512];
      int i = 0;
      int c = 6;
      int used = 1;

      char name[6];
      char size[5];
      interrupt(0x21, 2, directory, 2, 0);

      while(i<16){
	if(directory[i*32] != 0x0){

	  name[0] = directory[i*32+0];  //0
	  name[1] = directory[i*32+1];  //1
	  name[2] = directory[i*32+2];  //2
	  name[3] = directory[i*32+3];  //3
	  name[4] = directory[i*32+4];  //4
	  name[5] = directory[i*32+5]; //5
/*
	  while(directory[i*32 +c] != 0x0){
	    used++;
	    c++;
	  }*/

// 	 switch(used){
// 	   case 1: size[0] = '5'; size[1] = '1'; size[2] = '2'; break;
// 	   case 2: size[0] = '1'; size[1] = '0'; size[2] = '2'; size[3] = '4'; break;
// 	   case 3: size[0] = '1'; size[1] = '5'; size[2] = '3'; size[3] = '6'; break;
// 	   case 4: size[0] = '2'; size[1] = '0'; size[2] = '4'; size[3] = '8'; break;
// 	   case 5: size[0] = '2'; size[1] = '5'; size[2] = '6'; size[3] = '0'; break;
// 	   case 6: size[0] = '3'; size[1] = '0'; size[2] = '7'; size[3] = '2'; break;
// 	   case 7: size[0] = '3'; size[1] = '5'; size[2] = '8'; size[3] = '4'; break;
// 	   case 8: size[0] = '4'; size[1] = '0'; size[2] = '9'; size[3] = '6'; break;
// 	   case 9: size[0] = '4'; size[1] = '6'; size[2] = '0'; size[3] = '8'; break;
// 	   case 10: size[0] = '5'; size[1] = '1'; size[2] = '2'; size[3] = '0'; break;
// 	   case 11: size[0] = '5'; size[1] = '6'; size[2] = '3'; size[3] = '2'; break;
// 	   case 12: size[0] = '6'; size[1] = '1'; size[2] = '4'; size[3] = '4'; break;
// 	   case 13: size[0] = '6'; size[1] = '6'; size[2] = '5'; size[3] = '6'; break;
// 	   case 14: size[0] = '7'; size[1] = '1'; size[2] = '6'; size[3] = '8'; break;
// 	   case 15: size[0] = '7'; size[1] = '6'; size[2] = '8'; size[3] = '0'; break;
// 	   case 16: size[0] = '8'; size[1] = '1'; size[2] = '9'; size[3] = '2'; break;
// 	   case 17: size[0] = '8'; size[1] = '7'; size[2] = '0'; size[3] = '4'; break;
// 	   case 18: size[0] = '9'; size[1] = '2'; size[2] = '1'; size[3] = '6'; break;
// 	   case 19: size[0] = '9'; size[1] = '7'; size[2] = '2'; size[3] = '8'; break;
// 	   case 20: size[0] = '1'; size[1] = '0'; size[2] = '2'; size[3] = '4'; size[4] = '0'; break;
// 	   case 21: size[0] = '1'; size[1] = '0'; size[2] = '7'; size[3] = '5'; size[4] = '2'; break;
// 	   case 22: size[0] = '1'; size[1] = '1'; size[2] = '2'; size[3] = '6'; size[4] = '4'; break;
// 	   case 23: size[0] = '1'; size[1] = '1'; size[2] = '7'; size[3] = '7'; size[4] = '6'; break;
// 	   case 24: size[0] = '1'; size[1] = '2'; size[2] = '2'; size[3] = '8'; size[4] = '8'; break;
// 	   case 25: size[0] = '1'; size[1] = '2'; size[2] = '8'; size[3] = '0'; size[4] = '0'; break;
// 	   case 26: size[0] = '1'; size[1] = '3'; size[2] = '3'; size[3] = '1'; size[4] = '2'; break;
// 	   default: size[0] = 's'; size[1] = 'i'; size[2] = 'z'; size[3] = 'e'; size[4] = '!'; break;
//
//
// 	 }

	  interrupt(0x21, 0, name, 0, 0);
	//  interrupt(0x21, 0, size, 0, 0);
	  interrupt(0x21, 0, "\n", 0, 0);
	}

	   i++;



      }

    } else {
      interrupt(0x21, 0, "Bad Command\0 ", 0, 0);
    }


  }
}
