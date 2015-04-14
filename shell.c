int checkView(char[]);
char* extractName(char[]);
int checkExec(char[]);
char* extractProg(char[]);

int main (){
 char line[100]; 
 char buffer[13312];
 int known =1; 
 
  while(1){
  interrupt(0x21, 0, "shell> \0 ", 0, 0);
  interrupt(0x21, 1, line, 0, 0);
  interrupt(0x21, 0, "\n", 0, 0);
  
  if((checkView(line) == 0) && (checkExec(line) == 0)){
  interrupt(0x21, 0, "bad command", 0, 0);
  } else  {
  
  if(checkView(line) == 1){
  interrupt(0x21, 3, extractName(line), buffer, 0);
  interrupt(0x21, 0, buffer, 0, 0);
  } 
  
  if(checkExec(line) == 1){
  interrupt(0x21, 4, extractProg(line), 0x2000, 0);
  }
  
  
  }
  
  }

}

int checkView(char string[]){
	int i =0;
	char* view= "view";
	while(i < 4){
		if(string[i] != view[i]){
		return 0;
		}
	i++;
    }
	
	return 1;

}

char* extractName(char string[]){
	int i = 5;
	int j = 0;
	char name[6];
	while(j<6){
	name[j] = string[j+5];
	i++;
	j++;
	}
	return name;
}

int checkExec(char string[]){
	int i =0;
	char* exec= "execute";
	while(i < 7){
	if(exec[i] != string[i]){
	return 0;
	}
	i++;
	}
	
	return 1;

}

char* extractProg(char string[]){
	int i = 5;
	int j = 0;
	char name[6];
	while(j<6){
	name[j] = string[j+5];
	i++;
	j++;
	}
	return name;
}



