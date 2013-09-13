#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include "urutil.h"


#define HOR 512
#define VER 512
#define SAMPLE (VER*HOR)



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
	int i, j, k, l, m, n, a,b, cnt, Q;  // index
	int l1, r1;
	char fname[10][100], dname[100], timage[100];
	int *LI, *OI;
	float *PM;

	int mean,sqsum, var, sigma;
	int tempL[7][7], tempLL[7][7], tempH[5][5], tempA[9] = {0};

	int temp;
	FILE *in;
	


	LI = (int *)malloc(SAMPLE*(BL2+9)*sizeof(int));
	OI = (int *)malloc(SAMPLE*BH2*sizeof(int));
	PM = (float *)malloc(SAMPLE*sizeof(float));

	sprintf(fname[0], "boat");
	sprintf(fname[0], "baboon");

	Q = 0;
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

		

		for(i=0; i<VER-6; i +=2)
		{
			for(j=0; j<HOR-6; j+=2)
			{
				PM[Q]=0;


				for(m=0; m <7; m++)   
				{
					for(n=0; n<7; n++)
					{
						tempL[m][n] = blur[i+m][j+n]; // temp LR-patch
					
					}
				}
				


				for(m = 0; m <5; m++)
				{
					for(n=0; n<5; n++)
					{
						tempH[m][n] = Org[i+m+1][j+n+1] - blur[i+m+1][j+n+1]; //temp HR-patch (High freq)[n
						OI[Q*BH2+m*BH+n] = tempH[m][n];
					}
				}


				for(m=0; m<7; m++)
				{
					for(n = 0; n<7; n++)
					{

						temp = 9*tempL[m][n];

						for(k=-1; k<=1; k++)
						{
							for(l=-1; l<=1; l++)
							{
								l1 = m+k;
								if(l1 < 0) l1 = 0;
								if(l1 == 7) l1 = 6;
								r1 = n+l;
								if(r1 < 0) r1 = 0;
								if(r1 == 7) r1 = 6;
								temp -= tempL[l1][r1];

							}
						}
					
						LI[Q*(BL2+9)+m*BL+n] =temp;
						PM[Q] += abs(temp);
					}
				}
				PM[Q] /= BL2;

				LI[Q*(BL2+9) + BL2 + 1] = tempH[0][0];
				LI[Q*(BL2+9) + BL2 + 2] = tempH[0][1];
				LI[Q*(BL2+9) + BL2 + 3] = tempH[0][2];
				LI[Q*(BL2+9) + BL2 + 4] = tempH[0][3];
				LI[Q*(BL2+9) + BL2 + 5] = tempH[0][4];
				LI[Q*(BL2+9) + BL2 + 6] = tempH[1][0];
				LI[Q*(BL2+9) + BL2 + 7] = tempH[2][0];
				LI[Q*(BL2+9) + BL2 + 8] = tempH[3][0];
				LI[Q*(BL2+9) + BL2 + 9] = tempH[4][0];

				for(b = 0; b<(BL2+9); b++)
				{
					LI[Q*(BL2+9) + b] = (int)(LI[Q*(BL2+9) + b]/PM[Q]+1); // nomalization 그  e값을 뭐로해야 되는지 잘 몰라서1로함
				}
				Q++;
			}
		}
	}

	// Establish database
	in = fopen("trainedDB_LI.img","wb");
	fwrite(LI,sizeof(int), SAMPLE*(BL2+9), in);
	fclose(in);

	in = fopen("trainedDB_OI.img", "wb");
	fwrite(OI,sizeof(int), SAMPLE*BH2, in);
	fclose(in);



}
