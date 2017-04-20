#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

void intHandler(int sig) {

}



int main(int argc, char *argv[]) {
	

	

	/* First argument is executable name only 
	int i = 0;
	printf("\ncmdline args count=%d", argc);
	printf("\nexe name=%s", argv[0]);
	
	for (i = 1; i< argc; i++) {
		printf("\narg%d=%s", i, argv[i]);
	}
	*/
	char *prompt;
	size_t len = 50;
	size_t i = 0;
	if (!(prompt = malloc(50 * sizeof(char)))) {
		return 1;
	}
	strcpy(prompt, "$");

	if (argc == 3 && (strcmp(argv[1],"-p") == 0)) {
		prompt = argv[2];
	}
	else {
		prompt = "257sh";
	}

	printf("\n");

	//infinite loop to get commands 
	while (1) {
		int pid;
		char command[50];
		char cwd[1024];
		signal(SIGINT, intHandler);
		printf("%s> ", prompt);
		
		if (!fgets(command, 50, stdin)) {
			continue;
		}
		if (strlen(command) == 1) {
			continue;
		}
		command[strlen(command) - 1] = '\0';

		char* argv[20];
		int p = 1;
		argv[0] = strtok(command, " ");
		while (argv[p] = strtok(NULL, " ")) {
			p++;
		}
		argv[p] = '\0';
		if (strcmp(argv[0],"cd") == 0) {
			// do the cd stuff
			//if(cd has extra follow the path)
			if (argv[1] == NULL) {
				if (getcwd(cwd, sizeof(cwd)) != NULL) {
					printf("%s\n", cwd);
				}
			}
			else {
				
				if (chdir(argv[1]) == 0) {
					setenv("PWD", argv[1], 1);
				}
			}
		}
		else if (strcmp(argv[0],"pid") == 0) {
			//do pid stuff
			printf("Procces id is: %d\n", getpid());
		}
		else if (strcmp(argv[0],"ppid") == 0) {
			//do the ppid stuff
			printf("Parent id is: %d\n", getppid());
		}
		else if (strcmp(argv[0],"exit") == 0) {
			//do the exit stuff
			raise(SIGKILL);
		}
		//add a command to catch the ^C
		else {
			fflush(0);
			pid = fork();
			//checks to see if fork worked
			if (pid == -1) {
				printf("fork failed \n");
			}
			else if (pid == 0) {
				//might not work takes an array and number
				

				if (execvp(argv[0], argv)) {
					exit(1);
				}
				//close children
				exit(0);
			}
			else {
				int status;
				wait(&status);
				printf("Child exited with status: %d\n", status);
			}
		}
		
		
		
		//waits for children to close 
		//printf("who waits");
		


	}


	return 0;
}
