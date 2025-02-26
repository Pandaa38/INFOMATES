// gcc -Og bomba_jr.c -o bomba -no-pie -fno-guess-branch-probability


#include <stdio.h>	// para printf(), fgets(), scanf()
#include <stdlib.h>	// para exit()
#include <string.h>	// para strncmp()
#include <sys/time.h>	// para gettimeofday(), struct timeval

#define SIZE 100
#define TLIM 20



void boom(void){
	printf(	"\n"
		"***************\n"
		"*** BOOM!!! ***\n"
		"***************\n"
		"\n");
	exit(-1);
}

void defused(void){
	printf(	"\n"
		"·························\n"
		"··· bomba desactivada ···\n"
		"·························\n"
		"\n");
	exit(0);
}

///////////////////////////////////////////////////

int main(){

    char PASSWORD[]="lemadelsandwich\n";	// contraseña
    int  PIN  = 5008;			// pin

	char pw[SIZE];
	int  pc, n;

//////////////////////////////
	struct timeval tv1,tv2;	// gettimeofday() secs-usecs
	gettimeofday(&tv1,NULL);
//////////////////////////////

    do	printf("\nIntroduce la contraseña: ");
	while (	fgets(pw, SIZE, stdin) == NULL );


    //"ENCRIPTACION" SUMAMOS 20 A CADA CHAR DE MODO QUE CUANDO SE HAGA X/S LA CONTRASENIA MOSTRADA SEA ERRONEA
    for (size_t i = 0; i < sizeof(PASSWORD)-1; i++)
    {
        PASSWORD[i] += 2;
        pw[i] += 2;
    }

    
	
	if    (	strncmp(pw,PASSWORD,sizeof(PASSWORD)) )
	    boom();


//////////////////////////////
	gettimeofday(&tv2,NULL);
	if    ( tv2.tv_sec - tv1.tv_sec > TLIM )
	    boom();
//////////////////////////////


	do  {	printf("\nIntroduce el pin: ");
	 if ((n=scanf("%i",&pc))==0)
		scanf("%*s")    ==1;         }
	while (	n!=1 );

	PIN += 5;
	pc += 5;

	if    (	pc != PIN )
	    boom();


//////////////////////////////
	gettimeofday(&tv1,NULL);
	if    ( tv1.tv_sec - tv2.tv_sec > TLIM )
	    boom();
//////////////////////////////

    defused();
}
