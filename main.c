#include <stdio.h>
#include <string.h>
#include <stdlib.h>

double
average(char year[], char age[], char geo[])
{
  FILE *in;
  in =fopen("statscan_diabetes.csv", "r");
  double sum=0, average, temp;
  int i=0, m, j, k, l=0, length, geocondition, yearcondition, agecondition, conditions;
  char t[200], s[200], c, a[]="null";
  
  while(fscanf(in, "%c", &c)==1)
    {
      geocondition = 0; agecondition = 0; yearcondition = 0;
      for(j=1;j<=18;++j)
        {
            for(k=0;k<=200;++k)
            {
                t[k]=0;
                s[k]=0;
            }
            i=1;
            t[0]=c;
            do
            {
                fscanf(in, "%c", &t[i]);
                ++i;
            } while(t[i-1] != 44 && t[i-1] != 10);

          
            m=0;
            length = strlen(t);
            for(k=0;k<=length;++k)
            {
                if(t[k]!=44 && t[k]!= 34)
                {
                    s[m]=t[k];
                    ++m;
                }
            }
            
            if (strcmp(s,geo)==0 || strcmp (a,geo)==0)
            {
              geocondition = 1;
            }
            if (strcmp(s,year)==0 || strcmp (a,year)==0)
            {
              yearcondition = 1;
            }
            if (strcmp(s,age)==0 || strcmp (a,age)==0)
            {
              agecondition = 1;
            }
          conditions = agecondition + geocondition + yearcondition;
            if (conditions==3 && j==14)
            {
              temp = atof(s);
              if(temp != 0)
              {
                sum = sum + temp;
                ++l;
              }
            }
        }
    }
    average = sum/l;
    fclose(in);
  return(average);
}

int main()
{
  int year;
  double temp, lowest, highest, nationalaverage;
  double ontarioy[7], albertay[7], quebecy[7], britishcy[7], nationaly[7];
  double provincialaverage[4];
  
  char any[] = "null";
  char yr[][5] = {"2015", "2016", "2017", "2018", "2019", "2020", "2021"};
  char provinces[][30] = {"Ontario", "Alberta", "Quebec", "British Columbia", "Canada (excluding territories)"};
  char ageGroups[][20] = {"35 to 49 years", "50 to 64 years", "65 years and over"};
  
  
  
  //*Question 1a
  for(int i = 0; i < 4; i++)
    {
      //Filling array to be used in questions 2-3
      provincialaverage[i] = average(any, any, provinces[i]);
      printf("\nThe average percentage of diabetes in %s is %.2lf%%.", provinces[i], provincialaverage[i]);
    }

  //*Question 1b
  nationalaverage = average(any, any, provinces[4]);
  printf("\n\nThe average percentage of diabetes in %s is %.2lf%%.", provinces[4], nationalaverage);
  
  //*Question 1c
  printf("\n\nAverage by year for Ontario: ");
  for(int i = 0; i < 7; i++)
    {
      ontarioy[i] = average(yr[i], any, provinces[0]);
      printf("\n%s: %.2lf%%", yr[i], ontarioy[i]);
    }

  printf("\n\nAverage by year for Alberta: ");
  for(int i = 0; i < 7; i++)
    {
      albertay[i] = average(yr[i], any, provinces[1]);
      printf("\n%s: %.2lf%%", yr[i], albertay[i]);
    }

  printf("\n\nAverage by year for Quebec: ");
  for(int i = 0; i < 7; i++)
    {
      quebecy[i] = average(yr[i], any, provinces[2]);
      printf("\n%s: %.2lf%%", yr[i], quebecy[i]);
    }

  printf("\n\nAverage by year for British Columbia: ");
  for(int i = 0; i < 7; i++)
    {
      britishcy[i] = average(yr[i], any, provinces[3]);
      printf("\n%s: %.2lf%%", yr[i], britishcy[i]);
    }
  
  printf("\n\nAverage by year for Canada: ");
  for(int i = 0; i < 7; i++)
    {
      nationaly[i] = average(yr[i], any, provinces[4]);
      printf("\n%s: %.2lf%%", yr[i], nationaly[i]);
    }
  
  //*Question 1 d
  printf("\n\nAverage by age group for Ontario: ");
  for(int i = 0; i < 3; i++)
    {
      printf("\n%s: %.2lf%%", ageGroups[i], average(any, ageGroups[i], provinces[0]));
    }

  printf("\n\nAverage by age group for Alberta: ");
  for(int i = 0; i < 3; i++)
    {
      printf("\n%s: %.2lf%%", ageGroups[i], average(any, ageGroups[i], provinces[1]));
    }

  printf("\n\nAverage by age group for Quebec: ");
  for(int i = 0; i < 3; i++)
    {
      printf("\n%s: %.2lf%%", ageGroups[i], average(any, ageGroups[i], provinces[2]));
    }

  printf("\n\nAverage by age group for British Columbia: ");
  for(int i = 0; i < 3; i++)
    {
      printf("\n%s: %.2lf%%", ageGroups[i], average(any, ageGroups[i], provinces[3]));
    }

  printf("\n\nAverage by age group for Canada: ");
  for(int i = 0; i < 3; i++)
    {
      printf("\n%s: %.2lf%%", ageGroups[i], average(any, ageGroups[i], provinces[4]));
    }

  //*Question 2
  for(int i=0;i<=3;++i)
    {
      temp = provincialaverage[i];
      if(i==0)
      {
        lowest = temp;
        highest = temp;
      }
      if(temp > highest)
      {
        highest = temp;
      }
      if(temp < lowest)
      {
        lowest = temp;
      }
    }

  printf("\n\n");
  for(int i = 0; i < 4; i++)
    {
      if(provincialaverage[i] == lowest)
        {
          printf("\%s has the lowest percentage of diabetes with %.2lf%%\n", provinces[i], provincialaverage[i]);
        }
      else if(provincialaverage[i] == highest)
        {
          printf("\%s has the highest percentage of diabetes with %.2lf%%\n", provinces[i], provincialaverage[i]);
        }
    }

  //*Question 3
  printf("\n\nThe province(s) below the national average are");
  for(int i = 0; i < 4; i++)
    {
      if(provincialaverage[i] < nationalaverage)
        {
          printf(" %s", provinces[i]);
        }
    }

  printf("\nThe province(s) above the national average are");
  for(int i = 0; i < 4; i++)
    {
      if(provincialaverage[i] > nationalaverage)
        {
          printf(" %s", provinces[i]);
        }
    }

  //*Question 4
  for (int i=0; i<=6; ++i)
    {
      if(i==0)
      {
        lowest = ontarioy[i];
        highest = ontarioy[i];
      }
      if(ontarioy[i]<=lowest)
      {
        lowest = ontarioy[i];
      }
      if(ontarioy[i]>=highest)
      {
        highest = ontarioy[i];
      }
      if(albertay[i]<=lowest)
      {
        lowest = albertay[i];
      }
      if(albertay[i]>=highest)
      {
        highest = albertay[i];
      }
      if(quebecy[i]<=lowest)
      {
        lowest = quebecy[i];
      }
      if(quebecy[i]>=highest)
      {
        highest = quebecy[i];
      }
      if(britishcy[i]<=lowest)
      {
        lowest = britishcy[i];
      }
      if(britishcy[i]>=highest)
      {
        highest = britishcy[i];
      }
    }

  printf("\n");

  for(int i=0; i<=6; i++)
    {
      if(ontarioy[i]==lowest)
      {
        printf("\nOntario in the year %d had the lowest percentage of diabetes", i+2015);
      }
      if(ontarioy[i]==highest)
      {
        printf("\nOntario in the year %d had the highest percentage of diabetes", i+2015);
      }
      if(albertay[i]==lowest)
      {
        printf("\nAlberta in the year %d had the lowest percentage of diabetes", i+2015);
      }
      if(albertay[i]==highest)
      {
        printf("\nAlberta in the year %d had the highest percentage of diabetes", i+2015);
      }
      if(quebecy[i]==lowest)
      {
        printf("\nQuebec in the year %d had the lowest percentage of diabetes", i+2015);
      }
      if(quebecy[i]==highest)
      {
        printf("\nQuebec in the year %d had the highest percentage of diabetes", i+2015);
      }
      if(britishcy[i]==lowest)
      {
        printf("\nBritish Columbia in the year %d had the lowest percentage of diabetes", i+2015);
      }
      if(britishcy[i]==highest)
      {
        printf("\nBritish Columbia in the year %d had the highest percentage of diabetes", i+2015);
      }
    }

  return 0;
}
