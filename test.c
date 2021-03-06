#include <stdio.h>    // Standard input/output definitions
#include <stdlib.h>
#include <string.h>   // String function definitions
#include <unistd.h>   // para usleep()
#include <getopt.h>
#include <math.h>

#include "arduino-serial-lib.h"

float calculateSD(float data[]);

void error(char* msg)
{
    fprintf(stderr, "%s\n",msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	int fd = -1;
	int baudrate = 9600;  // default

	fd = serialport_init("/dev/ttyACM0", baudrate);

	if( fd==-1 )
	{
		error("couldn't open port");
		return -1;
	}
	char buff =*argv[1];
	if (buff =='1'||buff=='0'){
		while(1){
			write(fd,&buff,1);	
		}
	}else if(buff=='i'){
		int i;		
		char cad[5];		
		for(i = 0; i<5; i++){
		write(fd,&buff,1);
		cad[i] = read (fd,&buff,sizeof(char));
		usleep(100000);
		}
		printf("mod: %s\n",cad);
	}
	else if(buff=='t'){
		long int num[20]={};
		int i;
		for(i = 0; i<20; i++){
		write(fd,&buff,1);
		long int num[i] = read (fd,&buff,sizeof(long int));
		usleep(100000);
		}
		float prom;
		float suma;
		for(int j=0;j<20;j++){
			suma += num[i];
		}
		prom = suma / 20;
		printf("promedio: %f\n",prom);
	}
	
	close( fd );
	return 0;	
}

/* Ejemplo para calcular desviacion estandar y media */
float calculateSD(float data[])
{
    float sum = 0.0, mean, standardDeviation = 0.0;

    int i;

    for(i = 0; i < 10; ++i)
    {
        sum += data[i];
    }

    mean = sum/10;

    for(i = 0; i < 10; ++i)
        standardDeviation += pow(data[i] - mean, 2);

    return sqrt(standardDeviation / 10);
}

