#include <stdio.h>

//Program implements MODES: 1
//#define MODE 1


int riffcheck(void){           //function used to check if 'RIFF' is found
   int ch1,ch2,ch3,ch4;        //by reading 4 bytes and examining if they match with the letters 
   ch1=getchar();              
   ch2=getchar();
   ch3=getchar();
   ch4=getchar();
   if (ch1=='R' && ch2=='I' && ch3=='F' && ch4=='F'){
      return 0;                //if correct return 0
   }  
}

 
int wavecheck(void){           //function used to check if 'WAVE' is found
   int x,ch1,ch2,ch3,ch4;      //by reading 4 bytes and examining if they match with the letters 
   ch1=getchar();             
   ch2=getchar();
   ch3=getchar();
   ch4=getchar();
   if (ch1=='W' && ch2=='A' && ch3=='V' && ch4=='E'){
      return 0;               
   }
}

int format(void){                   //function used to check is 'fmt ' is found
   int x,ch1,ch2,ch3,ch4;           //by reading 4 bytes and examining if they match with the letters and space
   ch1=getchar();
   ch2=getchar();
   ch3=getchar();
   ch4=getchar();
   if (ch1=='f' && ch2=='m' && ch3=='t' && ch4==' '){
      return 0;                    
   }
}


int datacheck(void){              //function that is used to check if 'data' is found
   int ch1,ch2,ch3,ch4,res;       //by reading 4 bytes and examining if they match with the letters 
   ch1=getchar();
   ch2=getchar();
   ch3=getchar();
   ch4=getchar();
   if (ch1=='d' && ch2=='a' && ch3=='t' && ch4=='a'){
      return 0;                  
   }
}

int calculate4(void){            //function that calculates little endian style numbers with 4 bytes
   int ch1,ch2,ch3,ch4,res;      //by reading 4 bytes 
   ch1=getchar();                //and editing the most significant bytes as if they were stored before the least significant bytes
   ch2=getchar();
   ch3=getchar();
   ch4=getchar();
   res=ch1+ch2*16*16+ch3*16*16*16*16+ch4*16*16*16*16*16*16;
   return res;                   
}

int calculate2(void){          //fuction that calculates little endian style numbers with 2 bytes
   int ch1,ch2,res;            //by reading 2 bytes and editing them as if the most significant byte was stored
   ch1=getchar();              //before the least significant one
   ch2=getchar();
   res=ch1+16*16*ch2;
   return res;                
}

int main(void){
   int ch,sizeoffile,monost,samplerate,bytespersec,blockal,bitspers,sizedata;
   int indata=0,size=0;
    
if (MODE==1){   
   ch=riffcheck();                 //check for "RIFF"
   if (ch != 0){                   //if function result is not 0 -> invalid file, print error and terminate program  
      fprintf(stderr, "Error! \"RIFF\" not found\n");
      return 1;
   }
        
   ch=calculate4();               //calculating size of file 
   sizeoffile=ch;                 //saving it in a variable to check later for bad file size
   fprintf(stderr, "size of file: %d\n",sizeoffile);
        
   ch=wavecheck();                //check for "WAVE"
   size += 4;                     //variable "size" is used to check if we have bad file size in the end
                                  //increasing size by 4 because we read 4 bytes
   if (ch != 0){                  //check for invalid file
      fprintf(stderr, "Error! \"WAVE\" not found\n");
      return 1;
   }
        
   ch=format();                   //check for "fmt " 
   size += 4;                     //increasing by 4 because we read 4 bytes. Same in the following checks
   if (ch != 0){                  //check for invalid file
      fprintf(stderr, "Error! \"fmt \" not found\n");       
      return 1;
   }
                
   ch=calculate4();              //calculating size of format chunck
   size += 4;                   
   fprintf(stderr, "size of format chunck: %d\n",ch);
   if (ch != 16){                //size of format chunck must be 16 
      fprintf(stderr, "Error! size of format chunck should be 16\n");
      return 1;
   }
        
   ch=calculate2();             //calculate "WAVE" type format
   size += 2;                   //adding 2 because we read 2 bytes
   fprintf(stderr, "WAVE type format: %d\n",ch);   
   if (ch!= 1){                 //"WAVE" type format must be 1
      fprintf(stderr, "Error! WAVE type format should be 1\n");
      return 1;
   }
        
   ch=calculate2();              //calculating mono/stereo
   size += 2;
   monost=ch;                    //saving result in variable to check later if file is valid
   fprintf(stderr, "mono/stereo: %d\n",monost);
   if (ch != 1 && ch != 2){      //mono/stereo must be 1 or 2 
      fprintf(stderr, "Error! mono/stereo should be 1 or 2\n");
      return 1;
   }
        
   ch=calculate4();              //calculating sample rate size
   samplerate=ch;                //saving result in variable to check for validation between bytes per sec and block alignment
   size += 4;
   fprintf(stderr, "sample rate: %d\n",samplerate);
    
   ch=calculate4();              //calculating bytes per second
   bytespersec=ch;
   size += 4;
   fprintf(stderr, "bytes/sec: %d\n",bytespersec);
        
   ch=calculate2();             //calculating block alignment 
   blockal=ch;
   size += 2;
   fprintf(stderr, "block alignment: %d\n", blockal);
   if (bytespersec != blockal * samplerate){     //bytes per sec must be the product of sample rate and block aligment
      fprintf(stderr, "Error! bytes/second should be sample rate x block alignment\n");
      return 1;
   }
          
   ch=calculate2();             //calculating bits per second
   bitspers=ch;
   size += 2;
   fprintf(stderr, "bits/sample: %d\n",bitspers);
   if (bitspers != 8 && bitspers != 16){    //bits per second must be 8 or 16
      fprintf(stderr, "Error! bits/sample should be 8 or 16\n");
      return 1;
   }
   if (blockal != bitspers/8*monost){      //if this equation is true, file is not valid
      fprintf(stderr, "Error! block alignment should be bits per sample / 8 x mono/stereo\n");
      return 1;
   }
    
   ch=datacheck();             //check if "data" is found
   size += 4;
   if (ch != 0){               //check if "data" was found
      fprintf(stderr, "Error! \"data\" not found\n");
      return 1;
   }
        
   ch=calculate4();           //calculating size of data 
   sizedata=ch;
   size += 4;                      
   fprintf(stderr, "size of data chunck: %d\n",sizedata); 

   do{         //reading bytes until end of sound file
      ch=getchar();
      indata += 1;           //variable "indata" is used to check if we have isufficient data - increasing by 1 because we read 1 byte
      size += 1;             //increasing size variable by 1 beacause we read 1 byte
   }while(ch != EOF);
   
   if (indata < sizedata){   //if the data we read are not equal to the size of data we calculated with function, print error
                             //and terminate program
      fprintf(stderr, "Error! insufficient data\n");
      return 1;
   } 
        
   if (size-1 != sizeoffile){    //if the bytes we read after calculating size of file are different than what we expected, 
                                 //print error and terminate program
      fprintf(stderr, "Error! bad file size\n");
      return 1;
   }
}   
   return 0;
}