#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <fcntl.h>
//#include <sys/ioctl.h>

//#include <linux/gpio.h>
//FILE *fp;
#define pathExport "/sys/class/gpio/export"
#define PATH	"/sys/class/gpio/pio"
#define dir		"/direction"
#define val		"/value"

int transform(int num, char * name);
void IniOut(int num, char * pathName);

#if 0
int main(int argc, char**argv){
	char path[4];
	char Grp;
	int Num, i;
	int input = 152;

	for(i=0;i<4;i++) path[i] = 0x0;

	transform(input, path);

	for(i=0;i<4;i++)
	printf("%c", path[i]);
	
	
}
#endif
int main(int argc, char** argv){
	int i, example;
	char pathName[40];
	char keypath[4];
	
	for(i=0;i<40;i++) pathName[i] = 0x0;
	for(i=0;i<4;i++) keypath[i] = 0x0;
	//inital input; inital output; read;
	/*1transform num to string*/
	example = 153;
	strncpy(pathName, PATH, 19);
	IniOut(example, pathName);
	/* make a long path name string*/
}
void IniOut(int num, char * pathName){//"153" "E25" 153
	int pinNum, i, size, numbersize, index;
	char pin[3];
	char keypath[4];
	char set_val[4];
	FILE *fp;

/*	pinNum = num;*/
	
	if((fp = fopen(pathExport, "ab"))==NULL){
		printf("open Export file failed\n");
		exit(1);
	}
	rewind(fp);
	
	if(num/100){numbersize = 3;
	set_val[0]='1';
	set_val[1]=(num-100)/10 + '0';
	set_val[2]=num%10+'0';
	}
	else{
		if(num/10){
		numbersize = 2;
		set_val[0]=num/10+ '0';
		set_val[1]=num%10+ '0';
		}
		else{
			numbersize =1;
			set_val[0]=num/1 + '0';
			}
		
	}
	for(i=0;i<4;i++) printf("%c",set_val[i]);
	printf("%d\n", numbersize);
	fwrite(set_val, sizeof(char), numbersize, fp);
	fclose(fp);
	//direction
	size = transform(num,keypath);
	strncpy(&pathName[19], keypath, size);
	index = 19+size;
	strncpy(&pathName[index], dir, 10);

	for(i=0;i<40;i++) printf("%c", pathName[i]);

	if((fp=fopen(pathName, "rb+"))==NULL){
		printf("direction open failed\n");
		exit(1);
	}
	rewind(fp);
	
	strncpy(&pathName[index], val, 6);
	for(i=0;i<40;i++)	printf("%c", pathName[i]);
	i=0;
	while(pathName[index+6+i]){
		pathName[index+6+i++] = 0x0;
	}
	if((fp=fopen(pathName, "rb+"))==NULL){
		printf("cannot open vaule\n");
		exit(1);
	}

	strcpy(set_val, "1");
	fwrite(&set_val, sizeof(char), 1, fp);
	fclose(fp);
	
}
int transform(int num, char * path){
/*int main(int argc, char**argv){*/
	int input, i, tmp, size;
	char name[4];

	for(i=0;i<4;i++) name[i] = 0x0;//NULL

	//input = argc;//pinNum
	input = num;
	tmp = input % 32;

	name[0] = (input/32) + 'A';

	if(tmp /10) {
		name[1] = (tmp / 10) + '0';
		name[2] = (tmp % 10) + '0';
		size = 3;
	}
	else{
		name[1] = (tmp % 10) + '0';
		size = 2;
		}
	
	for(i=0;i<4;i++)
	printf("%c", name[i]);

	strncpy(path, name, 4);

	printf("copyed\n");
	return size;
//	return 1;
	//return name;
}
