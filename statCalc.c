//Threaded Stats Calculator
//Alana Staszczyszyn & Elijah Tavenor
//OS Design - Assignment 3 Pt 1

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>


//Function Declarations
void inputCheck(int n, char **input);



int main(int argc, char *argv[]){

	//Variables
	int x, y;
	int numOfInts = (argc - 1);
	int argArr[numOfInts];

	//Input sanitization
	inputCheck(argc, argv);

	//Populate array with cmd line args
	for(x = 1; x <=numOfInts; x++){
		argArr[x - 1] = atoi(argv[x]);
	}

	//TODO: Create the threads, each calling a different function
	

}

//Input Validation
void inputCheck(int n, char **input){

	//If too few arguments, exit
	if (n <= 1){
	fprintf(stderr,"Format error; usage: statCalc <int1> <int2> . . . <intn>");

	exit(1);

	}

	//Make sure every argument is actually an int
	int i, j;

	for (i=1; i < n; i++){

		j=0;

		while(input[i][j] != '\0'){

			if(!isdigit(input[i][j])){

				fprintf(stderr, "Format error: all input must be integers.\n\n");
				exit(1);
			}

			j++;

			//Also make sure no overflow
			if(j > 9){

				fprintf(stderr, "Overflow error: Please only input ints less less than 10 digits.\n\n");
				exit(1);
			}
		}

	}

}

//TODO: Thread creation function

//TODO: Functions for min, max, avg


