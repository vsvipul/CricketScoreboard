#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct 
{
	char name[50];
	char player[11][50];
	int pruns[11];
	int runs;
	int wickets;
} team;

void init(team a, team b)
{
	int i;
	char num[11][3];
	for (i=0;i<11;i++)
		sprintf(num[i],"%d",i+1);
	for (i=0;i<11;i++)
	{
		strcpy(a.player[i],"Player ");
		strcpy(b.player[i],"Player ");
		strcat(a.player[i],num[i]);
		strcat(b.player[i],num[i]);
	}
	a.runs=0;
	b.runs=0;
	a.wickets=0;
	b.wickets=0;
}

void inputnames(team a, team b)
{
	char choice;
	int i;
	printf("Enter name of Team A: ");
	scanf(" %[^\n]s",a.name);
	printf("Enter name of Team B: ");
	scanf(" %[^\n]s",b.name);
	printf("Do you wish to enter player names now? Enter y for yes and n for no. You can enter names later.\n");
	scanf(" %c",&choice);
	if (choice=='y')
	{
		for (i=0;i<11;i++)
		{
			printf("Enter name of player %d for team %s\n",i+1,a.name);
			scanf(" %[^\n]s ",a.player[i]);
		}
		for (i=0;i<11;i++)
		{
			printf("Enter name of player %d for team %s\n",i+1,b.name);
			scanf(" %[^\n]s ",b.player[i]);
		}
	}
}

void printscoreboard(team a, team b)
{
	printf("+----------------------+----------+---------------------+\n");
	printf("| %s \t\tvs\t\t %s |\n",a.name,b.name);
	printf("+----------------------+----------+---------------------+\n");
}

int main()
{
	team a,b;
	init(a,b);
	inputnames(a,b);
//	printscoreboard(a,b);
	return 0;
}
