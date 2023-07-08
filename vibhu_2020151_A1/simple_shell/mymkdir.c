
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>


// Name - Vibhu Jain
// Roll No - 2020151


void printing_messgae()
{
	printf("Usage: mkdir [OPTION]... [DIRECTORY]...\n");
	printf("Create the DIRECTORY(ies), if they do not already exist.\n");
	printf("\n");
}

int compare_string(char* a1,char* a2)
{
	if(strcmp(a1,a2)==0)
		return 0;
	else return 1;
}

void printing_error(int i)
{
	if(i==0)
	{
		puts("invalid command");

	}
	else{
		printf("Error: file exists\n");
	}
	return;
}
  
int main(int argc, char** argv) 
{ 
	
	char *options[] = {
		  "--help",
		  "-v"
		};

	char* a1 = argv[1];

	if(a1==NULL){
		printing_error(0);
		return 0;
	}
	char* a2 = argv[2];
	if(a2==NULL && compare_string(a1,options[0])!=0 && compare_string(argv[1],options[1])!=0){
		if(a1[0]=='-'){
		 printing_error(0);
		 return 0;
		 }
	    if (mkdir(a1, 0777) == -1) 
		printing_error(1);
	       
	   }
	else{
	   if(compare_string(a1,options[1])==0){
	   	if (mkdir(a2, 0777) == -1) 
			printing_error(1);
		    else{
			printf("Directory created : "); 
			printf("%s\n",a2);  
		   }
		  return 0;
	    }
	    if(compare_string(a1,options[0])==0){

		printing_messgae();	   	
	   	printf("Mandatory arguments to long options are mandatory for short options too.\n");
	   	printf("   -v, --verbose     print a message for each created directory\n");	
	    return 0;
	    }
	    perror("invalid command");
	}
	return 0; 
    
} 
