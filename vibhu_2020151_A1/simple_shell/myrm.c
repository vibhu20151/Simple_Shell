#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include<string.h>

// Name - Vibhu Jain
// Roll No - 2020151


int compare_string(char* a1,char* a2)
{
	if(strcmp(a1,a2)==0)
		return 0;
	else return 1;
}

int removing(char* a1)
{
	if(remove(a1)==0)
		return 0;
	else return 1;
}

void helllo()
{
	printf("remove regular file ");
}

void printing_error(int i)
{
	if(i==0)
	{
		puts("Argument Missing..!");
	}
	else{
		puts("file doesnt exist");
	}
	return;
}

int main(int argc, char **argv) 
{  
	
	if(argv[1]==NULL){
		printing_error(0);
		return 0;
	}
	char *options[] = {
		  "-v",
		  "-i"
		};
	char hell='-';
	if(argv[1][0]!=hell){
		if(opendir(argv[1]) != NULL) { 
			printing_error(1);
			return 0;
		}
	    if(removing(argv[1])==0);
	    else printf("Error\n"); 
	    return 0;   
	   }
	else{
	   if(!compare_string(argv[1],options[0])){
	   	if(argv[2]==NULL){
			printing_error(0);
			return 0;
		}
		if(opendir(argv[2]) != NULL) { 
			printing_error(1);
			return 0;
		}
	   	if(removing(argv[2])==0) {
	   		printf("removed ");
	   		printf("%s\n",argv[2]);
	   	}
	    	else printf("Error\n");
	    	return 0; 
	    }
	    if(!compare_string(argv[1],options[1])){
	    	if(argv[2]==NULL){
				printing_error(0);
			return 0;
		}
		if(opendir(argv[2]) != NULL) {
			printing_error(1); 
			return 0;
		}
	   	helllo();
	   	char test;
		printf("%s",argv[2]);
	   	printf(" y/N?\n");
	   	scanf("%c", &test);
	   	if(test=='y'){
			if(removing(argv[2])!=0){
				printf("Error\n"); 
			} 
	    	}
	   	else if(test=='N') return 0;
		else{
	    		printf("invalid option\n");
	    	}
	    	return 0;
	    }
	    puts("invalid options");
	    return 0;
	}
} 
