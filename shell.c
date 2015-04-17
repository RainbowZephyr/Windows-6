
int main (){
  char line[100];
  char buffer[13312];
  int cv,cd,cc,ce;
  int i,tmp;
  char* view= "view";
  char* exec="execute";
  char* delete="delete";
  char* copy = "copy";
  int clear;
  char* programName;
  char* fileName;

  while(1){
  cv=1;
  ce=1;
  cd=1;
    interrupt(0x21, 0, "shell> \0 ", 0, 0);
    interrupt(0x21, 1, line, 0, 0);
  //  interrupt(0x10, 0xE*256+line[0], 0, 0, 0);

    i=0;
    while(i < 4){
      if(line[i] != view[i]){
	cv = 0;
	break;
      }
      i++;
    }
	
    i=0;
    while(i<7){
      if(line[i] != exec[i]){
	ce = 0;
	break;
      }
      i++;
    }
    
    i=0;
    while(i<6){
      if(line[i] != delete[i]){
	cd = 0;
	break;
      }
      i++;
    }
    
     i=0;
    while(i<4){
      if(line[i] != delete[i]){
	cc = 0;
	break;
      }
      i++;
    }
    

    if((cv ==0 && ce == 0 && cd ==0 && cc == 0) ){
      interrupt(0x21, 0, "bad command", 0, 0);
    }


/*
      if(cv==1){
      i=5;
      while(line[i] != '\0'){
      programName[i-5] = line[i];
      i++;
      }
      interrupt(0x21, 3,programName, buffer, 0);
      interrupt(0x21, 0, buffer, 0, 0);
      } 
*/
//cannot have both if conditions at the same time, one must be commented for the other to work
  /*    if(ce==1){
	i=8;
	while(line[i] != '\0'){
	  programName[i-8] = line[i];
	  i++;
	}
	interrupt(0x21, 4, programName, 0x2000, 0);

      } */
 /*     
	if(cd == 1 ){
      	i=7;
      	while(line[i] != '\0'){
      		programName[i-7]=line[i];
      		i++;
      	} 
      	interrupt(0x21,7 , programName, 0 ,0);
        } */

	if(cc == 1 ){
      	i=4;
      	while(line[i] != 0x20){
      		programName[i-4]=line[i];
      		i++;
      	} 
      	i++;
      	tmp=0;
      	while(line[i] != '\0'){
      		fileName[tmp] = line[i];
      		i++;
      	}
      	
      	interrupt(0x21, 3,programName, buffer, 0);
      	interrupt(0x21, 8, fileName, buffer , 0);
      }


    clear = 0;
    while(clear < 100){
      line[clear]=0x0;
      clear++;
    }

  }
}
