#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void clrscr()			//clears the terminal screen
{
	system("clear");
}

void prompt()			
{
	printf("What happened on this delivery?\n");
	printf("1. Wd for WideBall\n2. W for wicket\n3. Nb for NoBall\n4. WdW for WideBall+Wicket\n");
	printf("5. NbW for NoBall+Wicket\n6. Wd(Runs) for Wideball+Runs\n7. Nb(Runs) for Noball+Runs\n8. Number of runs scored in current ball\n");
}

void printScore(char a[], char b[], int scoreteam1, int scoreteam2, int wickets1, int wickets2, int curball, int flag, int overs, int *f)
{
	clrscr();
	printf("\t\t\t##########################################################\n");
	printf("\t\t\t###########    Overs- %d.%d       ########################\n\n", curball/6, curball%6);
	printf("\t\t\t%s %d/%d", a, scoreteam1, 10-wickets1);
	if (!flag && curball!=0)
		printf("\t\tCur RR:%.1f", (float)(scoreteam1*6)/(float)curball );
	printf("\n");
	printf("\t\t\t%s %d/%d", b, scoreteam2, 10-wickets2);
	if (!flag)
		printf("\tYet to bat\n");
	else if (curball!=0 && curball!=6*overs)
		printf("\t\tCur RR:%.1f\tReq RR:%.1f", (float)(scoreteam2*6)/(float)curball, (float)((scoreteam1-scoreteam2+1)*6)/(float)(6*overs-curball));
	printf("\n\n");
	printf("\t\t\t##########################################################\n");
	printf("\t\t\t##########################################################\n\n");
	if (*f)
	{
		printf("Invalid input. Please enter again.\n");
		*f=0;
	}
	prompt();
}

void printResult(char a[], char b[], int team1score, int team2score)		//prints match result when match is over
{
	printf("Match over\n");
	if (team1score > team2score)
		printf("\t\t\t\t\t%s wins\n\n\n\n\n", a);
	else if ( team1score == team2score )
		printf("\t\t\t\t%s tied with %s\n\n\n\n", a, b);
	else
		printf("\t\t\t\t\t%s wins\n\n\n\n\n", b);
}

void toss(char name1[], char name2[])					//toss between the two teams
{
	srand(time(0));
	int x = rand() % 2;
	if (x == 0)
		printf("%s won the toss. Enter 1 for batting first and 2 for bowling first\n", name1);
	else
		printf("%s won the toss. Enter 1 for bowling first and 2 for batting first\n", name2);
}

void inputnames(char name1[], char name2[])			//inputs team names
{
	printf("Enter name of first team.\n");
	scanf(" %[^\n]", name1);
	printf("Enter name of second team.\n");
	scanf(" %[^\n]", name2);
}

void printpreviousrecord()							//prints result of last match
{
	clrscr();
	FILE* fi=fopen("data.txt", "r");
	char t[100];
	if (fi!=NULL)
	{
		while ( fscanf(fi," %[^\n]",t) != EOF )
			printf("%s\n", t);
		fclose(fi);
	}
	else
		printf("You need to create a match first.\n");
}

void savecurrentrecord(char name1[], char name2[], int scoreteam1, int scoreteam2)		//saves current match result
{
	FILE* fi = fopen("data.txt", "w");
	fprintf(fi, "%s\t%d\n", name1, scoreteam1);
	fprintf(fi, "%s\t%d\n", name2, scoreteam2);
	if ( scoreteam1 > scoreteam2 )
		fprintf(fi, "%s wins\n", name1);
	else if ( scoreteam2 > scoreteam1 )
		fprintf(fi, "%s wins\n", name2);
	else
		fprintf(fi, "%s tied with %s", name1, name2);
	fclose(fi);
}

void execball(char act[], int *curteamscore, int *curwickets, int *balls, int *curball, int *f) 	//changes the variables acc to current ball input
{
	if (strcmp(act, "Wd") == 0)
	{
		*curteamscore = *curteamscore+1;
	}
	else if (strcmp(act, "Nb") == 0)
	{
		*curteamscore = *curteamscore+1;
	}
	else if (strcmp(act, "W") == 0)
	{
		*curwickets = *curwickets-1;
		*balls = *balls-1;
		*curball = *curball+1;
	}
	else if (strcmp(act, "WdW") == 0)
	{
		*curwickets = *curwickets-1;
		*curteamscore = *curteamscore+1;
	}
	else if (strcmp(act, "NbW") == 0)
	{
		*curwickets = *curwickets-1;
		*curteamscore = *curteamscore+1;
	}
	else if (act[0]=='W' && act[1]=='d' && act[2]>='0' && act[2]<='6' && strlen(act)==3)
	{
		*curteamscore = *curteamscore+1;
		*curteamscore = *curteamscore + ((int)act[2]-'0');
	}
	else if (act[0]=='N' && act[1]=='b' && act[2]>='0' && act[2]<='6' && strlen(act)==3)
	{
		*curteamscore = *curteamscore+1;
		*curteamscore = *curteamscore + ((int)act[2]-'0');
	}
	else if (act[0]>='0' && act[0]<='6'  && strlen(act)==1)
	{
		*curteamscore = *curteamscore + ((int)act[0]-'0');
		*balls = *balls-1;
		*curball = *curball +1;
	}
	else
	{
		*f = 1;
	}
}

int main()
{
	char x;
	int i, team1score = 0, team2score = 0, overs, flag = 0; //flag=0 means first innings and flag=1 means second innings
	printf("Do you want to start a new match? Enter y for yes and n for no\n");
	scanf(" %c", &x);
	if (x=='y' || x=='Y')
	{
		char name1[50], name2[50], act[10];
		int f=0, choice, balls, wickets1, wickets2, curball;				//f=1 means invalid input
		inputnames(name1, name2);
		printf("Enter number of overs in each innings.\n");
		scanf(" %d", &overs);
		toss(name1, name2);
		scanf(" %d",&choice);

		double yvals1[overs*6];								//For GNUplot
		double yvals2[overs*6];
		memset(yvals1,0,sizeof(yvals1));
		memset(yvals2,0,sizeof(yvals2));

		if (choice == 1)									//team 1 batting team 2 bowling
		{
			balls = 6*overs;
			wickets1 = 10;
			wickets2 = 10;
			curball = 0;
			while (wickets1 && balls)
			{
				printScore(name1, name2, team1score, team2score, wickets1, wickets2, curball, flag, overs, &f);
				scanf(" %s", act);
				execball(act, &team1score, &wickets1, &balls, &curball, &f);
				if (curball && !yvals1[curball])
					yvals1[curball]=(double)(team1score*6)/(double)curball;
			}
			printf("First Innings over\n");
			flag = 1;
			balls = 6*overs;
			curball = 0;
			while (balls && wickets2)
			{
				printScore(name1, name2, team1score, team2score, wickets1, wickets2, curball, flag, overs, &f);
				scanf(" %s", act);
				execball(act, &team2score, &wickets2, &balls, &curball, &f);
				if (curball && !yvals2[curball])
					yvals2[curball]=(double)(team2score*6)/(double)curball;
				if(team2score > team1score)
				{
					printScore(name2, name1, team2score, team1score, wickets2, wickets1, curball, flag, overs, &f);
			    	printResult(name1, name2, team1score, team2score);
			    	break;
				}
			}
			printScore(name2, name1, team2score, team1score, wickets2, wickets1, curball, flag, overs, &f);
			printResult(name1, name2, team1score, team2score);
		}
        else if (choice == 2)						//team 2 batting team 1 bowling
		{
			wickets2 = 10;
			wickets1 = 10;
			curball = 0;
			balls = 6*overs;
			while (wickets2 && balls)
			{
				printScore(name2, name1, team2score, team1score, wickets2, wickets1, curball, flag, overs, &f);
				scanf(" %s", act);
				execball(act, &team2score, &wickets2, &balls, &curball, &f);
				if (curball && !yvals2[curball])
					yvals2[curball]=(double)(team2score*6)/(double)curball;
			}
			printf("First Innings over\n");
			flag = 1;
			balls = 6*overs;
			curball = 0;
			while (balls && wickets1)
			{
				printScore(name2, name1, team2score, team1score, wickets2, wickets1, curball, flag, overs, &f);
				scanf(" %s",act);
				execball(act, &team1score, &wickets1, &balls, &curball, &f);
				if (curball && !yvals1[curball])
					yvals1[curball]=(double)(team1score*6)/(double)curball;
				if (team1score > team2score)
				{
					printScore(name2, name1, team2score, team1score, wickets2, wickets1, curball, flag, overs, &f);
					printResult(name1, name2, team1score, team2score);
					break;
				}
			}
		}
		else
		{
			printf("Invalid choice. Please try again\n");
			exit(0);
		}
		printScore(name2, name1, team2score, team1score, wickets2, wickets1, curball, flag, overs, &f);
		printResult(name1, name2, team1score, team2score);
		savecurrentrecord(name1, name2, team1score, team2score);

		//GNUplot part begins
		char* commandsForGnuplot1[] = {"set title \"Run Rate vs balls for team 1\"", "plot 'data1.temp'"};
		char* commandsForGnuplot2[] = {"set title \"Run Rate vs balls for team 2\"", "plot 'data2.temp'"};
	    double xvals[overs*6];
	    for (i=0;i<overs*6;i++)
	    	xvals[i]=i;
	    FILE* temp1 = fopen("data1.temp", "w");
	    FILE* temp2 = fopen("data2.temp", "w");
	    FILE* gnuplotPipe1 = popen ("gnuplot -persistent", "w");
	    FILE* gnuplotPipe2 = popen ("gnuplot -persistent", "w");
	    for (i=0; i < 6*overs; i++)
	    	fprintf(temp1, "%lf %lf \n", xvals[i], yvals1[i]); //Write the data to a temporary file
	    for (i=0; i < 6*overs; i++)
	    	fprintf(temp2, "%lf %lf \n", xvals[i], yvals2[i]); //Write the data to a temporary file
	    for (i=0; i < 2; i++)
	    	fprintf(gnuplotPipe1, "%s \n", commandsForGnuplot1[i]); //Send commands to gnuplot one by one.
	    for (i=0; i < 2; i++)
	    	fprintf(gnuplotPipe2, "%s \n", commandsForGnuplot2[i]); //Send commands to gnuplot one by one.
	    //GNUplot part ends
    	
	}
	else
	{
		printf("Would you like to know result of previous match? Enter y for yes and n for no.\n");
		char ch;
		scanf(" %c", &ch);
		if (ch=='y' || ch=='Y')
			printpreviousrecord();
		else
			printf("Thanks for using!\n");
	}
	return 0;
}
