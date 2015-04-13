int main (){
  
  while(1){
  interrupt(0x21, 0, "shell>  \0", 0, 0);
  interrupt(0x21, 1, 0, 0, 0);
  interrupt(0x21, 0, "\n", 0, 0);
  interrupt(0x21, 0, "Bad Command!\0", 0, 0);
  interrupt(0x21, 0, "\n", 0, 0);
  }
  
} 
