#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include<string.h>

// Name- Vibhu Jain
// Roll No - 2020151


void findExt(char *t, char *s) {
    int i = 0;
    int j = 0;
	int len = (int)strlen(s);

    while(i < len && s[i]!= '.') {
        i=i+1;
    } 
    i=i+1;
    t[j] = '.';
	j++;

	for(;i<len;i++){
        t[j] = s[i];
		j++;
    }
    t[j] = '\0';
	j++;
}
void extSort(char **names, int n) {
	int i =0;
	while(i<=n-2){
        for(int j = i + 1; j <=n-1; j++) {  
            char *t2 = (char *) calloc(1000, sizeof(char));
            findExt(t2, names[j]);      
            char *t1 = (char *) calloc(1000, sizeof(char));
            findExt(t1, names[i]);
            if(strcmp(t2, t1) <=-1) {
                char *t = (char *) malloc(1000 * sizeof(char));
                char *t1 = (char *) malloc(1000 * sizeof(char));

                strcpy(t, names[i]);
				strcpy(t1,names[i]);
                strcpy(names[i], names[j]);
				strcpy(t1,names[j]);
                strcpy(names[j], t);
            }
        }
		i++;
    }
}
int main(int argc, char* argv[])
{	
    char buf[512];

	char *options[] = {
	  "-a",
	  "-s"
	};	
	int two =2;

    struct dirent *myfile;
	DIR *mydir;
	int one = 1;

	int showHidden,sort=0;
	int zeros = 0 ;

	
	if(argv[one]==NULL){
		mydir=opendir(".");
		while((myfile = readdir(mydir)) != NULL)
		    {
		    	if(myfile->d_name[zeros]=='.') continue;
			sprintf(buf, "%s/%s", argv[one], myfile->d_name);
			printf(" %s", myfile->d_name);
		    }
		    closedir(mydir);
		    printf("\n");
		    return 0;
	}
	if(strcmp(argv[one],options[one])==zeros){
		sort=one;
	}
	if(strcmp(argv[one],options[zeros])==zeros){
		showHidden=one;
	}

	if(showHidden==0 && sort==0){
			printf("");
		mydir=opendir(argv[one]);
		if(mydir==NULL){
			perror("");
			return 0;
		}
		char check ='.';
		while((myfile = readdir(mydir)) != NULL)
		    {
		    	if(myfile->d_name[0]==check) continue;
			sprintf(buf, "%s/%s", argv[one], myfile->d_name);
            printf(" ");

			printf(" %s\n", myfile->d_name);
		    }
		closedir(mydir);
	}else if(showHidden==1){
		if(argv[two]!=NULL)
			mydir=opendir(argv[two]);
		else
			mydir=opendir(".");

		if(mydir==NULL){
			perror("");
			return 0;
		}
            printf(" ");
		while((myfile = readdir(mydir)) != NULL)
		    {
				int file =0;

			sprintf(buf, "%s/%s", argv[1], myfile->d_name);
			file++;
			printf(" %s", myfile->d_name);
		    }
		closedir(mydir);
		printf("\n");
	}
	else if(sort==1){
		if(argv[two]!=NULL)
			{mydir=opendir(argv[two]);
            printf(" ");}

		else
			mydir=opendir(".");		

		int i=0;
		if(mydir==NULL){
			perror("");
			return 0;
		}

		char *names[1000];
		char check ='.';
		printf(" ");
		while((myfile = readdir(mydir)) != NULL)
		    {
		    	if(myfile->d_name[0]==check) continue;
			int sp=0;
			names[i]=(char*)malloc(1000*sizeof(char));
			sp++;
			sprintf(buf, "%s/%s", argv[one], myfile->d_name);
			strcpy(names[i], myfile->d_name); 
			i=i+1;
		    }
		extSort(names, i);
		for(int j = 0; j< i; ++ j) {
            		printf("%s", names[j]);
            		printf(" ");
        	}
		closedir(mydir);
       	printf("\n");

	}else{
		perror("invalid command");
	}
}
