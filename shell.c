#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>



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
	size_t len = 256;
	size_t i = 0;
	if (!(prompt = malloc(256 * sizeof(char)))) {
		return 1;
	}
	strcpy(prompt, "$");

	if (argc == 3 && (strcmp(argv[1],"-p") !=0)) {
		prompt = argv[2];
	}
	else {
		prompt = "257sh";
	}

	printf("\n");

	//infinite loop to get commands 
	while (1) {
		printf("[[%s]] ", prompt);
		i = getline(&prompt, &len, stdin);
		prompt[i - 1] = '\0';
		fgets(command, 50, stdin);
		//trim the string 
		if (strcmp(command, cd) != 0) {
			// do the cd stuff
			//if(cd has extra follow the path)
		}
		if (strcmp(command, pid) != 0) {
			// do the pid stuff
		}
		if (strcmp(command, ppid) != 0) {
			//do the ppid stuff
		}
		if (strcmp(command, exit) != 0) {
			//do the exit stuff
		}
		//add a command to catch the ^C
		else {
			fflush();
			pid = fork();
			//checks to see if fork worked
			if (pid < 0) {
				//	printf("fork failed at %d\n", c);
				//closes the program 
				exit(0);
			}
			else if (pid > 0) {
				//printf("parent: new child is %d\n", pid);
			}
			else {
				//might not work takes an array and number
				execvp(command);
			}
			//close children
			exit(0);
		}
		//waits for children to close 
		//printf("who waits");
		while (wait(NULL) > 0) {
			//printf("Waiting");
		}


	}


	return 0;
}
