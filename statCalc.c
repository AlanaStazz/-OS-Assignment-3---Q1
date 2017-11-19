//Threaded Stats Calculator
//Alana Staszczyszyn & Elijah Tavenor
//OS Design - Assignment 3 Pt 1

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>


//Function Declarations
void inputCheck(int n, char **input);
int calc_min(void *input_ints);
int calc_max(void *input_ints);
int calc_avg(void *input_ints);



int main(int argc, char *argv[]){

	//Variables
	int x, y;
	int numOfInts = (argc - 1);
	int argArr[numOfInts];
	void *min;
	void *max;
	void *avg;

	//Input sanitization
	inputCheck(argc, argv);

	//Populate array with cmd line args
	for(x = 1; x <=numOfInts; x++){
		argArr[x - 1] = atoi(argv[x]);
	}
	
	//TODO ADDED
	//Make threads
	pthread_t thr[3];


	y = pthread_create(&thr[0], NULL, (void *)calc_min, (void *) argArr);

	if (y != 0){
		printf("\n\nThread creation error: failed @ calc_min thread");		//TODO: handle errors better (for join + make)
	}


	y = pthread_create(&thr[1], NULL, (void *)calc_max, (void *) argArr);

	if (y != 0){

		printf("\n\nThread creation error: failed @ calc_max thread");
	}


	y = pthread_create(&thr[2], NULL, (void *)calc_avg, (void *) argArr);

	if (y != 0){
		printf("\n\nThread creation error: failed @ calc_avg thread");

	}


	//Joins
	y = pthread_join(thr[0], &min);

	if (y != 0){

		printf("\n\nThread join error: failed @ calc_max thread - error code %d", y);

	}
	
	y = pthread_join(thr[1], &max);

	if (y != 0){

		printf("\n\nThread join error: failed @ calc_max thread - error code %d", y);

	}

	y = pthread_join(thr[2], &avg);

	if (y != 0){

		printf("\n\nThread join error: failed @ calc_max thread - error code %d", y);

	}

	//TODO: Create the actual functions
	
	printf("\n\nTesting: end of main... %d %d %d", (uintptr_t)min, (uintptr_t)max, (uintptr_t)avg);

	return(0);

}

//Input Validation & Sanitization
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



//TODO: Functions for min, max, avg
int calc_min(void *input_ints){

/*	int i;
	int min = INT_MAX;
	int *ptr = (int *)input_ints;*/

	printf("\n\nTesting: calc_min");

	return 123;

}

int calc_max(void *input_ints){

	printf("\n\nTesting: calc_max");

	return 123;

}

int calc_avg(void *input_ints){

	printf("\n\nTesting: calc_avg");

	return 123;

}
