#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include "urutil.h"


#define HOR 512
#define VER 512
#define SAMPLE (VER*HOR*4)



#define BL 5
#define BH 7
#define BL2  (BL*BL)
#define BH2  (BH*BH)

#define OS 2
#define ITV 2
#define ITH 2


unsigned char Org[VER][HOR], blur[VER][HOR];


void main()
{
	int i, j, k, m, n, cnt;  // index
	char fname[10][100], dname[100], timage[100];
	int *LI, *OI;

	int mean,sqsum, var, sigma;

	FILE *in;
	


	LI = (int *)malloc(SAMPLE*BL2*sizeof(int));
	OI = (int *)malloc(SAMPLE*BH2*sizeof(int));


	sprintf(fname[0], "boat");
	sprintf(fname[0], "baboon");


	for(cnt = 0; cnt<2; cnt++)
	{
		sprintf(dname,"D:/traning/$_LQ.raw",fname[cnt]);
		in = fopen(dname, "rb");
		fread(blur,sizeof(unsigned char), HOR*VER,in);
		fclose(in);

		sprintf(dname, "D:/training/%S.raw",fname[cnt]);
		in = fopen(dname, "rb");
		fread(Org, sizeof(unsigned char), HOR*VER, in);
		fclose(in);

		
