#include<stdio.h>
#include <stdio.h>
#include <string.h>

// Name - Vibhu Jain
// Roll No - 2020151


int compare_string(char* a1,char* a2)
{
	if(strcmp(a1,a2)==0)
		return 0;
	else return 1;
}

void print_line(char* line)
{
	printf("%s\n", line);
}

void lets_print(int cnt)
{
	printf("%d",cnt);
	printf(")");
}

void main(int argc , char **argv)
{
		char line[10000];
        char *options[] = {
		  "-n",
		  "-E"
		};
		
		char* a1 =argv[1];


		if(a1==NULL){
			printf("Please also give arguments...!!\n");
			return ;
		}
		char check ='-';
        FILE *file;
		
		if(a1[0]!=check){
		       file = fopen(a1,"r");
		       if(file==NULL){
		       	perror("Error");
				return ;
		       }
		       while(fscanf(file,"%[^\n]\n",line)!=EOF)
		       {		
		                      printf("%s\n", line);
		       }
		       fclose(file);
		       return;
		  }
		char* a2 =argv[2];

		 if(compare_string(a1,options[0])==0){
			file = fopen(a2,"r"); int cnt=1;
			if(file==NULL){
		       	perror("Error");
				return ;
		       }
		       while(fscanf(file,"%[^\n]\n",line)!=EOF)
		       {		
		       		lets_print(cnt);
		       		cnt++;
		            print_line(line);
		       }
		       fclose(file);
		       return;
		}
		if(compare_string(a1,options[1])==0){
			file = fopen(a2,"r");
			if(file==NULL){
		       	perror("Error");
				return ;
		       }
			int filee = 1;
		       while(fscanf(file,"%[^\n]\n",line)!=EOF)
		      {
						filee++;
		      			char c='$';
		      			strncat(line,&c,1);
						print_line(line);
		       }
		       fclose(file);
		       return;
		}
		puts("invalid command");
		return;
}
