//Name: GUO, Yuzhou
//ID: 260715042

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setWholeYear (int DAYSIZE, int FIRSTDAY);
void month (int k, int FIRSTDAY, char s[], int l);
void setDates (int DAYSIZE, int FIRSTDAY);
void separateLine(int k);
void monthTitle(int k, char month[], int l);
void dayTitle (int k);
int oneDay (char s[], int k);    //we need to put all functions ahead. 

int main (int argc, char *argv[])
{
        int DAYSIZE = atoi(argv[1]);
        int FIRSTDAY = atoi(argv[2]);

        _Bool rightNumber1 = (DAYSIZE>=2);
        if (!rightNumber1)
        {
                printf("Error: Cannot print days smaller than size 2.\n");
                return -1;
        }

        _Bool rightNumber2 = (FIRSTDAY>=1)&&(FIRSTDAY<=7);
        if (!rightNumber2)
        {
                printf("Error: The first day of the week must be between 1 and 7.\n");
                return -1;
        }

        setWholeYear(DAYSIZE, FIRSTDAY);     //this is the method that combines all the month method together, the only thing we need to call from main.

        return 0;
}
 
void setWholeYear (int DAYSIZE, int FIRSTDAY)
{
        char m[12][10] = {{"January"}, {"February"},{"March"}, {"April"}, {"May"}, {"June"}, {"July"}, {"August"}, {"September"}, {"October"}, {"November"    }, {"December"}};
        int length[13] = {7, 8, 5, 5, 3, 4, 4, 6, 9, 7, 8, 8};
        int firstDayPlace = FIRSTDAY;                            //set two char lists so that we can loop months instead of manually call each one.

        for (int i=0; i<12; i++)
        {
                month(DAYSIZE, FIRSTDAY, m[i], length[i]);
        if (firstDayPlace>7)
        {
                firstDayPlace = firstDayPlace-7;
        }
                setDates(DAYSIZE, firstDayPlace);
                firstDayPlace +=2;                  //the first day of the second month, see it in calendar, should shift two positions to right.
        }
        separateLine(DAYSIZE);
}

void month (int k, int FIRSTDAY, char s[], int l)
{
        separateLine(k);
        monthTitle(k, s, l);
        separateLine(k);
        dayTitle(k);
        separateLine(k);
}


void setDates (int DAYSIZE, int FIRSTDAY)
{
        int k = DAYSIZE-1;
        int length = (k+3)*7+1;
        int pattern = (k+3);
        int place = pattern*(FIRSTDAY-1)+2;
        int n =1;
        int row = 5;


        if (place==(6*pattern+2))
        {
                row =6;              //there is only one condition that makes 6 rows: when the first day is Saturday.
        }
        for (int a=0; a<row; a++)
        {
                for (int i=0; i<length; i++)
                {
                        _Bool separate = (i%pattern==0);
                        _Bool writeNumber = ((i-2)%pattern)==0;
                        _Bool space = (a==0)&&(i<(pattern*(FIRSTDAY-1)+2));

                        if (separate)
                        {
                                printf("|");
                        }
                        else if (writeNumber)
                        {
                                if ((a==0)&&(i<(pattern*(FIRSTDAY-1)+2)))  //the idea here is that, the current month receives a signal from last
                                {                                          //month, then use it to set its own first day.  
                                        printf("  ");
                                        continue;
                                }
                                if (n<10)
                                {
                                        printf("%i ", n);      //here for one sigal number(not two digits), we need to give an extra zero.
                                }
                                else if ((n>=10)&&(n<=30))
                                {
                                        printf("%i", n);
                                }
                                else if (n>30)
                                {
                                        printf("  ");
                                }
                                n++;
                        }
                        else
                        {
                                printf(" ");
                        }
                 }
        printf("\n");
        }
}

void separateLine(int k)
{
        int symbol = (k+3)*7+1;

        for (int i=0; i<symbol; i++)
        {
                if ((i==0)||(i==(symbol-1)))
                {
                        printf("|");
                }
                else
                {
                        printf("-");
                }
        }
        printf("\n");
}


void monthTitle(int k, char month[], int l)
{
        int symbol = (k+3)*7+1;
        int startpoint = ((symbol-2-l)/2)+1;   //the startpoint here is exactly the space before the position where the title should be printed.

        for (int i=0; i<symbol; i++)
        {       
                if ((i==0)||(i==(symbol-1)))
                {       
                        printf("|");
                }       
                else if (i==startpoint)
                {       
                        for (int j=0; j<l; j++)
                        {       
                                printf("%c", month[j]);
                        } 
                        i +=(l-1);
                }   
                else
                {       
                        printf(" ");
                }
        }
        printf("\n");
}

void dayTitle (int k)
{       
        char days[7][20] = {{"Sunday"}, {"Monday"}, {"Tuesday"}, {"Wednesday"}, {"Thursday"}, {"Friday"}, {"Saturday"}};
        
        int symbol = (k+3)*7+1;
        int pattern = (k+3);                  
                                              //the idea here is that we have a little loop inside the outside loop
        for (int i=0; i<symbol; i++)               //in this way, we can control how many characters should be printed this time.
        {       
                _Bool separate = (i%pattern==0);
                _Bool writeDay = (i-2)%pattern==0;
                
                if (separate)
                {       
                        printf("|");
                }
                else if (writeDay)
                {       
                        for (int j=0; j<7; j++)
                        {       
                                if (i==2+(pattern*j))
                                {       
                                        int move = oneDay(days[j], k);
                                        i += (move-1);
                                }
                        }
                }
                else
                {
                        printf(" ");
                }
        }
        printf("\n");
}
 
int oneDay (char s[], int k)
{
        int counter = 0;
        if (k<=strlen(s))  //this if condition lets the situation when "the space user asks for is larger than the length of the word" to handle.
        {
                 for (int j=0; j<k; j++)
                 {
                        printf("%c", s[j]);
                        counter++;
                 }
        }
        else
        {
                 for (int j=0; j<strlen(s); j++)
                 {
                        printf("%c", s[j]);
                        counter++;
                 }
        }
                 return counter;
}

