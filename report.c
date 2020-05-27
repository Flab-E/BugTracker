#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "VAR.h"
#include "manpage.h"


void Validate(char * flag[])
{
	//argv parsed from main function as *char[]
	if(strcmp(flag[1], "-h")==0 || strcmp(flag[1], "--help")==0)
		help();								//help section for '-h' option
	else if(strcmp(flag[1], "-u")==0 || strcmp(flag[1], "--user")==0)
		UserValidate();							//user section for '-u' option
	else if(strcmp(flag[1], "-a")==0 || strcmp(flag[1], "--admin")==0)
		AdminValidate();						//admin section for '-a' option
	else
		printf("\'-h\' or \'--help\' flag for help section\n");
}

void AdminValidate()
{
	char pass[128] = "";
	printf("\n========== Admin Login ==========\n");
	printf("Please enter password for admin:");
	scanf("%s", pass);
	if(strcmp(pass, "admin123")==0)
		{printf("Login Succesful!\n"); Admin();}							//enter user home section if user
	else									//enters the password 'admin123
	{
		printf("Incorrect password for admin.\n\n\n");
		AdminValidate();
	}
}

void Admin()
{
	printf("\n========== Admin Home ==========\n");
	int ad_choice;
	printf("[1] Resolve a bug\n");
	printf("[2] View all Bug reports\n");
	printf("[3] Exit\n");
	printf("Enter your choice [1/2/3]: "); 
	scanf("%d", &ad_choice);
	switch(ad_choice)
	{
		case 1: Resolve(); break;
		case 2: View(); break;
		case 3: exit(0); break;
	}
}

void UserValidate()
{
	printf("\n========== User ==========\n");
	int choice;
	printf("\n[1] Login\n");
	printf("[2] SignUp\n");
	printf("[3] Exit\n");
	printf("Enter choice (1/2): ");
	scanf("%d", &choice);
	switch(choice)
	{
		case 1: Login(); break;
		case 2: SignUp(); break;
		case 3: exit(0); break;
		default: printf("Enter a valid choice.\n\n"); UserValidate(); break;
	}
}

void Login()
{
	printf("\n\n\n========== User Login ==========\n");
	int found = 0;
	int fielc_count = 0;
	char us[128];
	char *pass;
	char ch[3096];
	FILE *fp = fopen("Users.csv", "r");

	printf("Enter Username:\t");
	scanf("%s", us);
	if(!fp)
	{
		printf("Users.csv file is inaccesible\n");
		UserValidate();
	}
	else
	{
		while(fgets(ch, 3096, fp))
		{
			found = 0;
			char * buf = strtok(ch, ",");
			for(buf; buf && *buf; buf = strtok(NULL, ","))
			{
				if(found==1)
					pass = buf;
				if(strcmp(buf, us)==0)
					found = 1;
			}
			if(found == 1)
				break;
		}
		if(found == 1)
		{
			found = 0;
			char pa[128];
			printf("Enter password:\t");
			scanf("%s", pa);
			if(strcmp(pa, strtok(pass, "\n"))==0)
			{
				printf("Login Succesful!\n");
				User(us);
			}
			else
			{
				printf("Incorrect Password!\n");
				Login();
			}
		}
		else
		{
			printf("Username not found~\n");
			Login();
		}
	}
	fclose(fp);
}

void SignUp()
{
	//variables:
	printf("\n\n\n========== User Sign Up ==========\n");
	char us[128];
	char pa[128];
        FILE * fp = fopen("Users.csv", "a");
	
	//username and password
	printf("Enter Username:\t");
	scanf("%s", us);
	printf("Enter password:\t");
	scanf("%s", pa);

	//Update Users.csv
        fputs(us, fp);
        fputs(",",fp);
        fputs(pa,fp);
        fputs("\n",fp);
        fclose(fp);
	printf("Registration Complete!\n");
	
	//Back to User Login
	Login();
}

void User(char us[])
{
	printf("\n\n\n========== User Home ==========\n");
	//variables:
	int user_choice;
	
	//print out user options
	printf("Would you like to:\n");
	printf("[1] Report a bug\n");
	printf("[2] View status of your bugs\n");
	printf("[4] Logout\n");
	printf("[3] Exit\n");
	
	//read user's choice and action
	scanf("%d", &user_choice);
	switch(user_choice)
	{
		case 1: report(us); break;
		case 2: UserExtract(us); break;
		case 3: UserValidate(); break;
		case 4: exit(0); break;
	}
}

int rand_gen()
{
	//variables
	time_t t;
	int rand_num = 0;
	
	
	srand((unsigned) time(&t));
	for(int i =0; i<6; i++)
	{
		rand_num = (rand_num*10) + rand()%10;
	}

	return rand_num;
}

void report(char us[])
{
	printf("\n\n\n========== Bug Report ==========\n");
	time_t t;
	time(&t);
	char bugid[10];
	char user[128];
	char stat[128] = "Pending";
	char desc[1024];
	char prio[10];
	FILE * fp = fopen("BugReport.csv", "a");

	*user = *us;
	sprintf(bugid, "%d", rand_gen());
	printf("\nEnter bug description:\n");
	fflush(stdin);
        scanf("%[^\n]%*c", desc);
        fflush(stdin);
	printf("Enter report priority [High/Medium/Low]:\n");
	scanf("%[^\n]%*c", desc);
	

	

	fputs(bugid, fp);
        fputs(",",fp);
        fputs(us,fp);
	fputs(",", fp);
	fputs(strtok(desc,"\n"), fp);
        fputs(",",fp);
        fputs(stat,fp);
        fputs(",",fp);
        fputs(prio,fp);
        fputs(",",fp);
        fputs(ctime(&t),fp);
        fputs("\n",fp);
        
        fclose(fp);

	printf("Bug successfully reported with id:%s\n", bugid);
	User(us);
}

void UserExtract(char us[])
{
	printf("\n\n\n========== %s's Bug Reports ==========\n", us);
	int found = 1;
	char *bugid, *user, *desc, *stat, *prio, *curr;
	int row_count =0,  field_count=0;
	char ch[3096];
	FILE *fp = fopen("BugReport.csv", "r");


	if(!fp)
	{
		printf("Unable to read BugRetport.csv\n");
		return;
	}	


	while(fgets(ch, 3096, fp))
	{
		found = 1;
		field_count = 0;
		char *buf = strtok(ch, ",");
		while(buf)
		{
			if(field_count == 0)
				bugid = buf;

			else if(field_count == 1) 
			{
				user = buf;
				if(( strcmp(us, buf)==0))
					found = 0;
				
			}			
			else if(field_count == 2)
				desc = buf;

			else if(field_count == 3)
				stat = buf;
			else if(field_count == 4)
				prio = buf;
			else if(field_count == 5)
				curr = buf;
			else
				printf("Unknown error\n");
			field_count++;	
				
				
				
			buf = strtok(NULL, ",");
		}
		if(found == 0)
			printf("\nbugid:\t\t%s\nUsername:\t%s\nRepors:\t\t%s\nStatus:\t\t%s\nPriority:\t%s\nTime:\t\t%s\n", bugid, user, desc, stat, prio, curr);
	}
	fclose(fp);
	User(us);
}


void Resolve()
{
	printf("\n========== Admin Resolve Update ==========\n");
	FILE *fp, *fp1, *fp2;
	char *bugid, *user, *desc, *stat, *prio, *curr;
	int field_count = 0, found = 1;
	char res_bugid[10], ch[3096], chre[3096];
        fp1 = fopen("BugReport.csv", "r");
        fp2 = fopen("temp.csv", "a");
        if(!fp1 || !fp2)
        {
                printf("Unable to access Report.csv\n");
                return;
        }
	
	printf("Enter bugid of resolved bug: ");
	scanf("%s", res_bugid);

	while(fgets(ch, 3096, fp1))
	{
		field_count = 0;
		char *buf = strtok(ch, ",");
		while(buf)
		{
			switch(field_count)
			{
				case 0: bugid = buf; break;
				case 1: user = buf; break;
				case 2: desc = buf; break;
				case 3: stat = buf; break;
			}
			field_count++;
			buf = strtok(NULL, ",");
		}
		if(strcmp(res_bugid, bugid)==0)
		{
			stat = "Resolved";
			fputs(bugid, fp2);
        		fputs(",",fp2);
        		fputs(user,fp2);
			fputs(",", fp2);
			fputs(desc, fp2);
        		fputs(",",fp2);
        		fputs(stat,fp2);
        		fputs(",",fp2);
        		fputs(prio,fp2);
        		fputs(",",fp2);
        		fputs(curr,fp2);
		}
		else
		{
			fputs(bugid, fp2);
        		fputs(",",fp2);
        		fputs(user,fp2);
			fputs(",", fp2);
			fputs(desc, fp2);
        		fputs(",",fp2);
        		fputs(stat,fp2);
        		fputs(prio,fp2);
        		fputs(",",fp2);
        		fputs(curr,fp2);
		}
	}
	fclose(fp1);
	fclose(fp2);
	
	//erasing redundant data in BugReport.csv
	fp = fopen("BugReport.csv", "w");
	fputs("", fp);
	fclose(fp);
	
	//rewriting BugReport.csv
	fp1 = fopen("BugReport.csv", "a");
        fp2 = fopen("temp.csv", "r");
        if(!fp1 || !fp2)
        {
                printf("Unable to access Report.csv\n");
                return;
        }
        
        while(fgets(chre, 3096, fp2))
	       	fputs(chre, fp1);

        fclose(fp1);
        fclose(fp2);
	
	//erasing data from temp.csv
	fp = fopen("temp.csv", "w");
	fputs("", fp);
	fclose(fp);
	
	View();
	Admin();
}

void View()
{
	printf("\n\n\n========== All Bug Reports ==========\n");
	int field_count=0;
	char ch[3096];
	FILE *fp = fopen("BugReport.csv", "r");

	if(!fp)
	{
		printf("Unable to read BugRetport.csv\n");
		return;
	}	


	while(fgets(ch, 3096, fp))
	{
		field_count = 0;
		char *buf = strtok(ch, ",");
		while(buf)
		{
			if(field_count == 0)
				printf("Bugid:\t\t%s\n", buf);
			else if(field_count == 1)
				printf("Username:\t%s\n", buf);			
			else if(field_count == 2)
				printf("Report:\t\t%s\n", buf);
			else if(field_count == 3)
				printf("Status:\t\t%s\n\n", buf);
			else if(field_count == 4)
				printf("Priority:\t%s\n", buf);
			else if(field_count == 5)
				printf("Time:\t\t%s\n\n", buf);
			else
				printf("Unknown error\n");
			field_count++;		
			buf = strtok(NULL, ",");
		}
	}
	fclose(fp);
	Admin();
}
