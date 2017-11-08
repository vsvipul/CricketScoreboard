#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int team1score=0;
static int team2score=0;
static int overs;
int flag=0;

void clrscr()
{
	system("@cls||clear");
}

void printScore(char a[], char b[], int scoreteam1, int scoreteam2, int wickets1, int wickets2)
{
    printf("\t\t\t##########################################################\n");
    printf("\t\t\t##########################################################\n\n");
    printf("\t\t\t%s %d/%d\n",a,scoreteam1,10-wickets1);
    printf("\t\t\t%s %d/%d",b,scoreteam2,10-wickets2);
    if (!flag)
    	printf("\tYet to bat\n");
    printf("\n");
    printf("\t\t\t##########################################################\n");
    printf("\t\t\t##########################################################\n\n");
}

void printResult(char a[], char b[])
{
	clrscr();
    printf("Match over\a\n");
    if (team1score>team2score)
        printf("\t\t\t\t\t%s wins\n\n\n\n\n",a);
    else
        printf("\t\t\t\t\t%s wins\n\n\n\n\n",b);;
}

int main()
{
	char x;
	printf("Do you want to start a new match? Enter y for yes and n for no.\n");
	scanf(" %c",&x);
	if (x=='y' || x=='Y')
	{
		char name1[50],name2[50],tmp[50],act[10];
		printf("Enter name of first team.\n");
		scanf(" %s", name1);
		printf("Enter name of second team.\n");
		scanf("%s", name2);
		printf("Enter number of overs in each innings.\n");
		scanf(" %d", &overs);
		int balls=6*overs;
		printf("Which team is batting first, %s or %s ?\n",name1,name2);
		scanf(" %s", tmp);
		if (strcmp(tmp,name1)==0)
		{
			int wickets1=10;
			int wickets2=10;
			char tmp2[50];
			while (wickets1 && balls)
			{
				printScore(name1, name2, team1score, team2score, wickets1, wickets2);
				printf("What happened on this delivery?\n");
				printf("Wd for WideBall\nW for wicket\nNb for NO ball\nOr runs scored( <=0 )");
				printf("\nWdW for WideBall+Wicket\nNbW for NO ball+Wicket\nWd(Runs) for Wideball+Runs\nNb(Runs) for NOball+Runs\n");
				scanf(" %s", act);
				if (strcmp(act,"Wd")==0)
                {
                    team1score++;
                }
                else if (strcmp(act,"Nb")==0)
                {
                    team1score++;
                }
                else if (strcmp(act,"W")==0)
                {
                    wickets1--;
                    balls--;
                }
                else if (strcmp(act,"WdW")==0)
                {
                    wickets1--;
                    team1score++;
                }
                else if (strcmp(act,"NbW")==0)
                {
                    wickets1--;
                    team1score++;
                }
                else if (act[0]=='W' && act[1]=='d')
                {
                    team1score++;
                    team1score+=((int)act[2]-'0');
                }
                else if (act[0]=='N' && act[1]=='b')
                {
                    team1score++;
                    team1score+=((int)act[2]-'0');
                }
                else
                {
                    team1score+=((int)act[0]-'0');
                    balls--;
                }
            }
            printf("First Innings over\a\n");
            flag=1;
            balls=6*overs;

            while (balls && wickets2)
            {
                printScore(name1, name2, team1score, team2score, wickets1, wickets2);
                printf("What happened on this delivery?\n");
                printf("Wd for WideBall\nW for wicket\nNb for NO ball\nOr runs scored( <=0 )\n");
                printf("WdW for WideBall+Wicket\nNbW for NO ball+Wicket\nWd(Runs) for Wideball+Runs\nNb(Runs) for NOball+Runs\n");
                scanf(" %s",act);
                if (strcmp(act,"Wd")==0)
                {
                    team2score++;
                }
                else if (strcmp(act,"Wd")==0)
                {
                    team2score++;
                }
                else if (strcmp(act,"W")==0)
                {
                    wickets2--;
                    balls--;
                }
                else if (strcmp(act,"WdW")==0)
                {
                    wickets2--;
                    team2score++;
                }
                else if (strcmp(act,"NbW")==0)
                {
                    wickets2--;
                    team2score++;
                }
                else if (act[0]=='W' && act[1]=='d')
                {
                    team2score++;
                    team2score+=((int)act[2]-'0');
                }
                else if (act[0]=='N' && act[1]=='b')
                {
                    team2score++;
                    team2score+=((int)act[2]-'0');
                }
                else
                {
                    team2score+=((int)act[0]-'0');
                    balls--;
                }
                if(team2score>team1score)
                {
                    printResult(name1,name2);
                    break;
                }
            }

        }
        else
        {
            int wickets2=10;
			int wickets1=10;
			char tmp2[50];
			while (wickets2 && balls)
			{
				printScore(name2, name1, team2score, team1score, wickets2, wickets1);
				printf("What happened on this delivery?\n");
				printf("Wd for WideBall\nW for wicket\nNb for NO ball\nOr runs scored( <=0 )\n");
				printf("\nWdW for WideBall+Wicket\nNbW for NO ball+Wicket\nWd(Runs) for Wideball+Runs\nNb(Runs) for NOball+Runs\n");
				fgets(act,10,stdin);
				if (strcmp(act,"Wd")==0)
                {
                    team2score++;
                }
                else if (strcmp(act,"Nb")==0)
                {
                    team2score++;
                }
                else if (strcmp(act,"W")==0)
                {
                    wickets2--;
                    balls--;
                }
                else if (strcmp(act,"WdW")==0)
                {
                    wickets2--;
                    team1score++;
                }
                else if (strcmp(act,"NbW")==0)
                {
                    wickets2--;
                    team2score++;
                }
                else if (act[0]=='W' && act[1]=='d')
                {
                    team2score++;
                    team2score+=((int)act[2]-'0');
                }
                else if (act[0]=='N' && act[1]=='b')
                {
                    team2score++;
                    team2score+=((int)act[2]-'0');
                }
                else
                {
                    team2score+=((int)act[0]-'0');
                    balls--;
                }
            }
            printf("First Innings over\a\n");
            flag=1;
            balls=6*overs;

            while (balls && wickets1)
            {
                printScore(name2, name1, team2score, team1score, wickets2, wickets1);
                printf("What happened on this delivery?\n");
                printf("Wd for WideBall\nW for wicket\nNb for NO ball\nOr runs scored( <=0 )\n");
                printf("WdW for WideBall+Wicket\nNbW for NO ball+Wicket\nWd(Runs) for Wideball+Runs\nNb(Runs) for NOball+Runs\n");
                fgets(act,10,stdin);
                if (strcmp(act,"Wd")==0)
                {
                    team1score++;
                }
                else if (strcmp(act,"Wd")==0)
                {
                    team1score++;
                }
                else if (strcmp(act,"W")==0)
                {
                    wickets1--;
                    balls--;
                }
                else if (strcmp(act,"WdW")==0)
                {
                    wickets1--;
                    team1score++;
                }
                else if (strcmp(act,"NbW")==0)
                {
                    wickets1--;
                    team1score++;
                }
                else if (act[0]=='W' && act[1]=='d')
                {
                    team1score++;
                    team1score+=((int)act[2]-'0');
                }
                else if (act[0]=='N' && act[1]=='b')
                {
                    team1score++;
                    team1score+=((int)act[2]-'0');
                }
                else
                {
                    team1score+=((int)act[0]-'0');
                    balls--;
                }
                if(team2score>team1score)
                {
                    printResult(name1,name2);
                    break;
                }
            }
        }
        printResult(name1,name2);
    }
	return 0;
}
