#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static int team1score=0;
static int team2score=0;
static int overs;
int flag=0;

void clrscr()
{
	system("clear");
}

void printScore(char a[], char b[], int scoreteam1, int scoreteam2, int wickets1, int wickets2, int curball)
{
    printf("\t\t\t##########################################################\n");
    printf("\t\t\t###########    Overs- %d.%d       ########################\n\n", curball/6, curball%6);
    printf("\t\t\t%s %d/%d",a,scoreteam1,10-wickets1);
    if (!flag && curball!=0)
    	printf("\t\tCur RR:%.1f", (float)(scoreteam1*6)/(float)curball);
    printf("\n");
    printf("\t\t\t%s %d/%d",b,scoreteam2,10-wickets2);
    if (!flag)
    	printf("\tYet to bat\n");
    else if (curball!=0)
    	printf("\t\tCur RR:%.1f\tReq RR:%.1f", (float)(scoreteam2*6)/(float)curball, (float)((scoreteam1-scoreteam2+1)*6)/(float)(6*overs-curball));
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
    else if (team1score==team2score)
    	printf("\t\t\t\t%s tied with %s\n\n\n\n",a,b);
    else
        printf("\t\t\t\t\t%s wins\n\n\n\n\n",b);;
}

int toss()
{
	srand(time(0));
    int x = rand() % 2;
    return x;
}

int main()
{
	char x;
	printf("Do you want to start a new match? Enter y for yes and n for no.\n");
	scanf(" %c",&x);
	if (x=='y' || x=='Y')
	{
		char name1[50], name2[50], tmp[50], act[10];
		int f=0;
		printf("Enter name of first team.\n");
		scanf(" %[^\n]", name1);
		printf("Enter name of second team.\n");
		scanf(" %[^\n]", name2);
		printf("Enter number of overs in each innings.\n");
		scanf(" %d", &overs);
		int tosschoice=toss();
		int choice;
		if (tosschoice==0)
			printf("%s won the toss. Enter 1 for batting first and 2 for bowling first\n", name1);
		else
			printf("%s won the toss. Enter 1 for bowling first and 2 for batting first\n", name2);
		scanf(" %d",&choice);
		if (choice==1)		//team 1 batting team 2 bowling
		{
			int balls=6*overs;
			int wickets1=10;
			int wickets2=10;
			char tmp2[50];
			int curball=0;
			while (wickets1 && balls)
			{
				printScore(name1, name2, team1score, team2score, wickets1, wickets2, curball);
				if (f)
				{
					printf("Invalid input. Please enter again.\n");
					f=0;
				}
				printf("What happened on this delivery?\n");
				printf("1. Wd for WideBall\n2. W for wicket\n3. Nb for NoBall\n4. WdW for WideBall+Wicket\n");
				printf("5. NbW for NoBall+Wicket\n6. Wd(Runs) for Wideball+Runs\n7. Nb(Runs) for Noball+Runs\n8. Number of runs scored in current ball\n");
				scanf(" %s",act);
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
                    curball++;
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
                else if (act[0]>='0' && act[0]<='6')
                {
                    team1score+=((int)act[0]-'0');
                    balls--;
                    curball++;
                }
                else
                {
                	f=1;
                }
            }
            printf("First Innings over\a\n");
            flag=1;
            balls=6*overs;
            curball=0;
            while (balls && wickets2)
            {
                printScore(name1, name2, team1score, team2score, wickets1, wickets2, curball);
                if (f)
				{
					printf("Invalid input. Please enter again.\n");
					f=0;
				}
                printf("What happened on this delivery?\n");
				printf("1. Wd for WideBall\n2. W for wicket\n3. Nb for NoBall\n4. WdW for WideBall+Wicket\n");
				printf("5. NbW for NoBall+Wicket\n6. Wd(Runs) for Wideball+Runs\n7. Nb(Runs) for Noball+Runs\n8. Number of runs scored in current ball\n");
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
                    curball++;
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
                else if (act[0]>='0' && act[0]<='6')
                {
                    team2score+=((int)act[0]-'0');
                    balls--;
                    curball++;
                }
                else
                {
                	f=1;
                }
                if(team2score>team1score)
                {
                    printResult(name1,name2);
                    break;
                }
            }
            printResult(name1,name2);
        }
        else if (choice==2)						//team 2 batting team 1 bowling
        {
            int wickets2=10;
			int wickets1=10;
			char tmp2[50];
			int curball=0;
			int balls=6*overs;
			while (wickets2 && balls)
			{
				printScore(name2, name1, team2score, team1score, wickets2, wickets1, curball);
				if (f)
				{
					printf("Invalid input. Please enter again.\n");
					f=0;
				}
				printf("What happened on this delivery?\n");
				printf("1. Wd for WideBall\n2. W for wicket\n3. Nb for NoBall\n4. WdW for WideBall+Wicket\n");
				printf("5. NbW for NoBall+Wicket\n6. Wd(Runs) for Wideball+Runs\n7. Nb(Runs) for Noball+Runs\n8. Number of runs scored in current ball\n");
				scanf(" %s", act);
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
                    curball++;
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
                else if (act[0]>='0' && act[0]<='6')
                {
                    team2score+=((int)act[0]-'0');
                    balls--;
                    curball++;
                }
                else
                {
                	f=1;
                }
            }
            printf("First Innings over\a\n");
            flag=1;
            balls=6*overs;
            curball=0;
            while (balls && wickets1)
            {
                printScore(name2, name1, team2score, team1score, wickets2, wickets1, curball);
                if (f)
				{
					printf("Invalid input. Please enter again.\n");
					f=0;
				}
                printf("What happened on this delivery?\n");
				printf("1. Wd for WideBall\n2. W for wicket\n3. Nb for NoBall\n4. WdW for WideBall+Wicket\n");
				printf("5. NbW for NoBall+Wicket\n6. Wd(Runs) for Wideball+Runs\n7. Nb(Runs) for Noball+Runs\n8. Number of runs scored in current ball\n");
				scanf(" %s",act);
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
                    curball++;
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
                else if (act[0]>='0' && act[0]<='6')
                {
                    team1score+=((int)act[0]-'0');
                    balls--;
                    curball++;
                }
                else
                {
                	f=1;
                }
                if (team1score>team2score)
                {
                    printResult(name1,name2);
                    break;
                }
            }
        }
        else
        {
        	printf("Invalid choice. Please try again\n");
        	exit(0);
        }
        printResult(name1,name2);

        FILE* fi = fopen("data.txt","w");
    	fprintf(fi,"%s\t%d\n",name1,team1score);
    	fprintf(fi,"%s\t%d\n",name2,team2score);
    	if (team1score>team2score)
    		fprintf(fi,"%s wins\n",name1);
    	else if (team2score>team1score)
    		fprintf(fi,"%s wins\n",name2);
    	else
    		fprintf(fi,"%s tied with %s",name1, name2);
    	fclose(fi);

    }
    else
    {
    	printf("Would you like to know result of previous match? Enter y for yes and n for no.\n");
    	char ch;
    	scanf(" %c",&ch);
    	if (ch=='y' || ch=='Y')
    	{
    		clrscr();
    		FILE* fi=fopen("data.txt","r");
    		char t[100];
    		while (fscanf(fi," %[^\n]",t)!=EOF)
    		{
    			printf("%s\n",t);
    		}
    		fclose(fi);
    	}
    	else
    		printf("Thanks for using!\n");
    }
	return 0;
}
