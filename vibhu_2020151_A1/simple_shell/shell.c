#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include<sys/wait.h>
#include<fcntl.h> 
#include<errno.h> 
#include <pthread.h>


// Name - Vibhu Jain
// Roll No - 2020151

char* path;
char cwd[1024];

void printing_starting_intro(char* uname)
{
	printf("Simple Shell : Made by -Vibhu Jain\n");
	printf("\n\nUSER is: @%s", uname);
}

void init_shell()
{
	char* uname= getenv("USER");
	printing_starting_intro(uname);
	printf("\n");
}
char **parse(char* str){
	char *token;
	token=strtok(str," \n");
	char **tokens = calloc(1024,sizeof(char*));
	int pos=0;
	while(token!=NULL){
		tokens[pos]=token;
		token=strtok(NULL," \n");
		pos=pos+1;
	}
	return tokens;
}
void print_buffer2()
{
    printf("%s","Options:-L  print the value of $PWD if it names the current working directory\n");
    printf("%s","By default, `pwd' behaves as if `-L' were specified.\n");
}
void print_buffer1()
{
	printf("%s","pwd: pwd [-L][--help]\n");
    printf("%s","Print the name of the current working directory.\n");
}

int compare_string(char* a1,char* a2)
{
	if(strcmp(a1,a2)==0)
		return 0;
	else return 1;
}

void add_to_history(char** arg){
	char *hispath;
	hispath = calloc(1024,sizeof(char));
	int j=0;
	strcpy(hispath,path);
	strcat(hispath,"/history.txt");
	int fp = open(hispath,O_WRONLY | O_APPEND);
	int pos=0;
	char *c ;
	c = (char *) calloc(1024, sizeof(char));  
	while(arg[pos]!=NULL){
		int len = strlen(arg[pos]);
		int i=0;
		while(i<len)
		{
			*(c+j)=*(arg[pos]+i);
			i++;
			j++;
		}
		*(c+j)=' ';
		pos++;
		j++;
	}
	int len1 = strlen(c);
  	write(fp, c, len1);
 	close(fp);
}

int my_pwd(char** args){
	char*a1 = args[1];
	if(a1==NULL){
   getcwd(cwd, sizeof(cwd));
   printf("Current working dir: %s\n", cwd);
  }

  else if(compare_string(a1,"--help")==0){
    print_buffer1();
	print_buffer2();
    printf("%s","--help :: Gives the information about the PWD..!!\n");
  }
  else if(compare_string(a1,"-L")!=0){
	fprintf(stderr,"Command not found\n");   
  }
  else{
	getcwd(cwd, sizeof(cwd));
	printf("Current working dir: %s\n", cwd);
  }
  return 1;	
}
void buffer_cd1()
{
		printf("This is the help command of CD ....!!!\n");
		printf("\n");
		printf("CD command is used to change our current directory Location...!!");
}
void buffer_cd2()
{
		printf("\n");
		printf("Below are the Flags used : \n      -L : Default state of cd \n     --help : Displays this help page \n");

		printf("      .. :  is used to go to the previous Directory ...!!\n");
		printf("       ~  : Used to go to the Home directory ..!!\n");
}
int my_cd(char **arg){
	char*a1 =arg[1];
	char*a2=arg[2];
	if(a1==NULL){
		printf("Please give the arguments..!!\n");
		return 1;
	}

	else if(compare_string(a1,"--help")==0){
		buffer_cd1();	
		buffer_cd2();
	}
	else if (compare_string(a1,"~")==0)
	{
		char s[1024];
		chdir(getenv("HOME"));
		printf("%s\n", getcwd(s, 100));
		return 1;
	}	
	else if(compare_string(a1,"-L")!=0)
	{
	chdir(a1);
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("dir: %s", cwd);
	printf("\n");
	return 1;
	}
	else{
		if(a2==NULL){
		printf("Please also give the dir name..!!\n");
	}
	else{
		chdir(a2);
		char cwd[1024];
		getcwd(cwd, sizeof(cwd));
		printf("dir: %s", cwd);
		printf("\n");
		return 1;
	}
	}
}

void my_exit(){
 	exit(0);
}

void print_history_buffer(char* c)
{
	printf("%s",c);
 	printf("\n");
}

int my_history(char **arg){

	char *hispath ;
	hispath=calloc(1024,sizeof(char));
	char* a2 =arg[2];
	strcpy(hispath,path);
	char* a1 =arg[1];
	strcat(hispath,"/history.txt");

	if(a1!=NULL){
		char *options[] = {
		  "-c",
		  "-s"
		};
		if (compare_string(a1,options[1])==0) {
			if(a2==NULL){
				return 1;
			}
			int pos=2;
			int fp = open(hispath,O_WRONLY | O_APPEND);
			int j=0;
			char *c =(char *) calloc(1024, sizeof(char));  
			while(arg[pos]!=NULL){
				int len = strlen(arg[pos]);
				int i=0;
				while(i<len)
				{
					*(c+j)=*(arg[pos]+i);
					i++;
					j++;
				}
				*(c+j)=' ';
				pos++;
				j++;
			}
		  	write(fp, c, strlen(c));
		 	close(fp);
		 	return 1;
		}
		if (compare_string(a1,options[0])==0) {
			if(a2!=NULL){
				perror("invalid command");
				return 1;
			}
			int fp = open(hispath,O_TRUNC);
			close(fp);
			return 1;
		}
		perror("invalid command");
		return 1;
		
	}
	add_to_history(arg);
	char *c;
	int fp;
	fp=open(hispath,O_RDONLY);
	c=(char *) calloc(1024, sizeof(char));
 	if(fp != -1)
 	{
  		read(fp, c, 1024);
 	}
 	close(fp);
	print_history_buffer(c);
 	return 1;
}



void printt_echo_buff(char*a1)
{
	printf("%s",a1);
	printf(" ");
}


int my_echo(char **arg){
	
	char *options[] = {
	  "-n",
	  "-e"
	};

	char*a1=arg[1];
	char check ='-';

	if(a1==NULL)
	{
		printf("Please also give arguments..!!\n");
		return 1;
	}

	if(a1[0]==check){
		if(compare_string(a1,options[1])==0){
			 int c=0;
			 char a ='\\';
			 int j=2;
			while(arg[j]!=NULL){
				int len = strlen(arg[j]);
				int i=0;
				while(i<len){
					if(i==0 && arg[j][i]==a){
						int pp = strlen(arg[j]);
						if(pp>=2){
							if(arg[j][i+1]=='c'){
								c=1;
								break;
							}
							else if(arg[j][i+1]!='n')
							{
								printf("%c",arg[j][i]);
								i++;
							}
							else {
								printf("\n");
								i=i+2;
							}
						}
					}else{
						i++;
						printf("%c",arg[j][i-1]);
					}
				}
				if(c==1){
					break;
					}
				j++;
			}
			c=0;
			printf("\n");
			return 1;
		}
	
		if(compare_string(a1,options[0])==0){
			int pos=2;
			if(arg[pos]==NULL){
				return 1;
			}
			while(arg[pos]!=NULL){
				printt_echo_buff(arg[pos]);
				pos++;
			}
			return 1;
		}
		perror("invalid command");
		return 1;
	}else{
		int pos=1;
		if(a1==NULL){
			printf("\n");
			return 1;
		}
		while(arg[pos]!=NULL){
			printt_echo_buff(arg[pos]);
			pos++;
		}
		printf("\n");
		return 1;
	}
}
	
int check(char	**arg){

	if (arg[0] == NULL) {
	    return 1;
	}
	char*a1 =arg[0];
	char *builtin_str[] = {
	  "cd",
	  "pwd",
	  "exit",
	  "echo",
	  "history"
	};

	    if (compare_string(a1,builtin_str[4])==0) {
	      return my_history(arg);
	    }

		if (compare_string(a1,builtin_str[1])==0) {
	    	add_to_history(arg);
	       return my_pwd(arg);
	    }

		if (compare_string(a1,builtin_str[3])==0) {
	  		add_to_history(arg);
	      return my_echo(arg);
	    }
		
		if (compare_string(a1,builtin_str[0])==0) {
	    	add_to_history(arg);
	      return my_cd(arg);
	    }

		if (compare_string(a1,builtin_str[2])==0) {
			add_to_history(arg);
			my_exit();
		}

	add_to_history(arg);
	   
	return 0;
}



void* callingsystem(char** arg)
{
	char * argument=arg[0];
	int i=1;
	while(arg[i]!=NULL)
	{
		strcat(argument," ");
		strcat(argument,arg[i]);
		i++;
	}

	system(argument);
	return ;
}

int exec_arg_fork(char** arg){
	int status;
	pid_t pid;
	pid = fork();
	char*a1=arg[0];

	if(pid<0)
	{
		perror("Forking Failed");
	}
	else if (pid == 0) {
	if (execvp(a1, arg) == -1) {
	      perror("");
	}
	exit(EXIT_FAILURE);
	}
	else {
	    wait(NULL);
  	}
  return 1;
}
int exec_arg_pthread(char** arg,char* inputtt){
	
	pthread_t pid;
	
	int len1=strlen(inputtt);
	
	inputtt[len1-2]='\0';

	int len=strlen(arg[0]);
	arg[0][len-2]='\0';

	int iret1;
	
	iret1 = pthread_create( &pid, NULL,callingsystem,(char**)arg);

	pthread_join(pid,NULL);

  return 1;
}


int main()
{
	init_shell();
	int flag=0;
	path=calloc(1024,sizeof(char));
	getcwd(path, 1024);

	while(1){
		char **par=calloc(1024,sizeof(char*));
		
		char * pathr=calloc(1024,sizeof(char));
		
		char* inputS=calloc(1024,sizeof(char));

		strcpy(pathr,path);
		strcat(pathr,"/");
		printf(">");

		ssize_t size = 0;
		char *line=NULL;
		if(getline(&line, &size, stdin) == -1){
			if(feof(stdin)==0)
			{
				perror("readline");
				exit(EXIT_FAILURE);
			}
			else{
				exit(EXIT_SUCCESS);
			}
		}

		inputS=line;
		par=parse(inputS);
		flag=check(par);

		char*inputttt=*par;
		int  length = strlen(inputttt);

		if(!flag){
			strcat(pathr,par[0]);
			par[0]=pathr;
			if(inputttt[length-1]=='t' && inputttt[length-2]=='&')
			{
				exec_arg_pthread(par,inputttt);
			}
			else{
				exec_arg_fork(par);
			}
			free(par);
			free(inputS);
	}
	}
}
