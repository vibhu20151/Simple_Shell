#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

// Name - Vibhu Jain
// Roll No - 2020151

int compare_string(char* a1,char* a2)
{
	if(strcmp(a1,a2)==0)
		return 0;
	else return 1;
}
void printing_invalid()
{
	puts("invalid command");
}
int main(int argc, char **argv)
{
	struct tm * ptm; 
	char *options[] = {
	  "-u",
	  "-I"
	};
	char* a1=argv[1];
	time_t rawtime;
	char* a2=argv[2];

	char buf[256];
	memset(buf, 0, sizeof(buf));


	if(a1!=NULL)
	{
			if(compare_string(a1,options[0])==0){
					if(a2!=NULL){
						printing_invalid();
						exit(EXIT_FAILURE);
					}
					time_t now = time(&now);
					ptm = gmtime(&now);
					printf("UTC time: %s", asctime(ptm));
					exit(EXIT_SUCCESS);	
				}
				if(compare_string(a1,options[1])==0){
					if(a2!=NULL){
						printing_invalid();
						exit(EXIT_FAILURE);
					}
					time (&rawtime); 
					strftime(buf, 256, "Date in ISO format : %F", gmtime(&rawtime)); 
					puts(buf);
					exit(EXIT_SUCCESS);
				}
				printing_invalid();
				exit(EXIT_FAILURE);	
	}
	else{
			time ( &rawtime );
			ptm = localtime ( &rawtime );
			printf ( "Current local time and date: %s", asctime (ptm) );

		  exit(EXIT_SUCCESS);	
	}
}
