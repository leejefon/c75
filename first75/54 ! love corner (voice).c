/* 愛轉角 */

#include<stdio.h>
#include<windows.h>
#include<conio.h>

#define Do_l 262
#define Re_l 294
#define Mi_l 330
#define Fa_l 349
#define So_l 392
#define La_l 440
#define Si_l 494

#define Do_m 523
#define Re_m 587
#define Mi_m 659
#define Fa_m 698
#define So_m 784
#define La_m 880
#define Si_m 988

#define Do_h 1046
#define Re_h 1175
#define Mi_h 1318
#define Fa_h 1397
#define So_h 1568
#define La_h 1760
#define Si_h 1976

int main()
{
    printf("\n\n\n\tThis is \"Love Corner\"");
    
    int row,col;
    int voice[21][6] = {{Do_m,Si_l,Do_m,La_m,La_m,0},{So_m,Fa_m,So_m,Mi_m,Re_m,Do_m},{Do_m,Si_l,Do_m,La_m,La_m,0},{So_m,Fa_m,So_m,Do_m,Mi_m,0},
                        {Do_m,Si_l,Do_m,La_m,La_m,0},{So_m,Fa_m,So_m,Mi_m,Re_m,Do_m},
                        {La_l,Mi_m,Fa_m,Fa_m,0,0},{Mi_m,Do_m,Mi_m,Re_m,Do_m,0},{So_m,La_m,La_m,So_m,So_m,0},
                        
                        {Mi_m,Re_m,Do_m,Si_l,Do_m,So_m},{So_m,Mi_m,Re_m,Do_m,La_l,Do_m},{Mi_m,Re_m,0,0,0},
                        {Mi_m,Fa_m,So_m,So_m,So_m,Si_m},{Do_h,Mi_m,Mi_m,Fa_m,Mi_m,Do_m},{Mi_m,Re_m,0,0,0},
                        
                        {Mi_m,Fa_m,So_m,So_m,So_m,Si_l},{Do_m,0,0,0,0,0},{La_l,So_m,So_m,So_m,Si_l,Do_m},
                        {La_l,Mi_m,Fa_m,Fa_m,0,0},{Mi_m,Do_m,Mi_m,Re_m,0,0},{Mi_m,Re_m,Do_m,Si_l,Re_m,Do_m}};
                        
    int tempo[21][6]={{2,2,2,4,4,0},{2,2,4,2,2,4},{2,2,2,4,4,0},{2,2,2,2,8,0},
                      {2,2,2,4,4,0},{2,2,4,2,2,6},
                      {2,2,1,6,0,0},{2,2,4,2,6,0},{2,2,4,2,8,0},
                      
                      {2,2,2,2,2,2},{4,2,2,2,2,2},{2,4,0,0,0,0},
                      {2,2,2,2,2,2},{4,2,2,2,2,2},{2,4,0,0,0,0},
                      
                      {2,2,2,2,2,2},{6,0,0,0,0,0},{2,2,2,2,2,6},
                      {2,2,1,6,0,0},{2,2,2,6,0,0},{2,2,2,2,1,4}};
    
    for(row=0; row<21; row++) {
        for(col=0; col<6; col++) {
            Beep(voice[row][col], tempo[row][col]*150);           
        }
    }
/*
// 給愛麗絲
    printf("\n\n\n\tThis is \"Garbage Song\"");

    int row;
    int voice[51] = {Mi_m,(Re_m+30),Mi_m,(Re_m+30),Mi_m,Si_l,Re_m,Do_m,La_l,  //9
	 	  				   Do_l,Mi_l,La_l,Si_l, Mi_l,So_l+15,Si_l,Do_m,         //8
							Mi_l,Mi_m,(Re_m+30),Mi_m,(Re_m+30),Mi_m,Si_l,Re_m,Do_m,La_l,  //10
							Do_l,Mi_l,La_l,Si_l,Mi_l,Do_m,Si_l,La_l,  //8
							Si_l,Do_m,Re_m,Mi_m,So_l,Fa_m,Mi_m,Re_m,  //8
							Fa_l,Mi_m,Re_m,Do_m,Mi_l,Re_m,Do_m,Si_l};  //8

    int tempo[51]={1,1,1,1,1,1,1,1,4,
				       1,1,1,4,1,1,1,4,
						 1,1,1,1,1,1,1,1,1,4,
						 1,1,1,4,1,1,1,4,
						 1,1,1,4,1,1,1,4,
						 1,1,1,4,1,1,1,4};


    for(row=0; row<51; row++) {
	    Beep(voice[row], tempo[row]*200);
    }
*/
    getch();
}
