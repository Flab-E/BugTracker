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
		{printf("Login Succesful!\n"); Admin();}			//enter user home section of user
	else									//enters the password 'admin123
	{
		printf("Incorrect password for admin.\n\n\n");
		AdminValidate();
	}
}

void Admin()
{	
	//This is the admin's home section
	printf("\n========== Admin Home ==========\n");
	
	//variables
	int ad_choice;
	
	//print admin choice
	printf("[1] Resolve a bug\n");
	printf("[2] View all Bug reports\n");
	printf("[3] Search for bug\n");
	printf("[4] Exit\n");
	printf("Enter your choice [1/2/3]: "); 
	
	//read and functionality to admin's choice
	scanf("%d", &ad_choice);
	switch(ad_choice)
	{
		case 1: Resolve(); break;
		case 2: View(); break;
		case 3: SearchBug(); break;
		case 4: exit(0); break;
	}
}

void UserValidate()
{
	//Very first page for all user:
	printf("\n========== User ==========\n");
	
	//variables:
	int choice;
	
	//options for User
	printf("\n[1] Login\n");
	printf("[2] SignUp\n");
	printf("[3] Exit\n");
	printf("Enter choice (1/2): ");
	
	//actions to user's choice
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
	//user's Login page
	printf("\n\n\n========== User Login ==========\n");
	
	//Variables:
	int found = 0;
	int fielc_count = 0;
	char us[128];
	char *pass;
	char ch[3096];
	FILE *fp = fopen("Users.csv", "r");

	//Validating login credentials
	printf("Enter Username:\t");
	scanf("%s", us);
	if(!fp)
	{
		printf("Users.csv file is inaccesible\n");
		UserValidate();
	}
	else
	{
		//Extracting user data from Users.csv
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
	printf("[3] Logout\n");
	printf("[4] Exit\n");
	
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
	
	//using current time as seed for rand()
	srand((unsigned) time(&t));
	for(int i =0; i<6; i++)
	{
		//generates a random number between 0 - 9 for a total of 6 times
		rand_num = (rand_num*10) + rand()%10;
	}

	//returning random number generated
	return rand_num;
}

void report(char us[])
{
	//User Report Page
	printf("\n\n\n========== Bug Report ==========\n");

	//variables
	time_t t;
	time(&t);
	FILE *fp = fopen("BugReport.csv", "a");
	char bugid[10];
	char user[128];
	char stat[128] = "Pending";
	char des[1024];
	char prio[10];
	char type[50];
	
	//Values to variables:
	*user = *us;
	sprintf(bugid, "%d", rand_gen());
	printf("Enter bug priority:\n");
	scanf("%s", prio);
	printf("Enter bug type:\n");
	scanf("%s", type);
	printf("Enter bug description:\n");
	scanf(" %[^\n]s\n",des);
	printf("%s\n", des);

	
	//Entering Values into BugReport.csv File
	fputs(bugid, fp);
        fputs(",",fp);
        fputs(us,fp);
	fputs(",", fp);
	fputs(des, fp);
        fputs(",",fp);
	fputs(type, fp);
	fputs(",", fp);
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
	//Users Bug report page:
	printf("\n\n\n========== %s's Bug Reports ==========\n", us);
	
	//variables:
	int found = 1;
	char *bugid, *user, *desc, *type, *stat, *prio, *curr;
	int row_count =0,  field_count=0;
	char ch[3096];
	FILE *fp = fopen("BugReport.csv", "r");


	if(!fp)
	{
		printf("Unable to read BugRetport.csv\n");
		return;
	}	

	/*
	Extracting from the Bugreport.csv file 
	where the Username matches the currently logged in user's name
	*/
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
				//checking if the user name validates to every value in Username field
				user = buf;
				if(( strcmp(us, buf)==0))
					found = 0;
				
			}			
			else if(field_count == 2)
				desc = buf;
			else if(field_count == 3)
				type = buf;	
			else if(field_count == 4)
				stat = buf;
			else if(field_count == 5)
				prio = buf;
			else if(field_count == 6)
				curr = buf;
			else
				printf("Unknown error\n");
			field_count++;	
				
				
			//Assigning null to buff, in order to terminate redundant loop
			buf = strtok(NULL, ",");
		}
		if(found == 0)
			printf("\nbugid:\t\t%s\nUsername:\t%s\nReport:\t\t%s\nType:\t\t%s\nStatus:\t\t%s\nPriority:\t%s\nTime:\t\t%s\n", bugid, user, desc, type, stat, prio, curr);
	}
	fclose(fp);
	User(us);
}


void Resolve()
{
	//Admin resolve issue page
	printf("\n========== Admin Resolve Update ==========\n");
	
	//variables:
	FILE *fp, *fp1, *fp2;
	char *bugid, *user, *desc, *type, *stat, *prio, *curr;
	int field_count = 0, found = 1;
	char res_bugid[10], ch[3096], chre[3096];
        
        //BugReport.csv is readable only
        //temp.csv is in append mode
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
				case 3: type = buf; break;
				case 4: stat = buf; break;
				case 5: prio = buf; break;
				case 6: curr = buf; break;
			}
			field_count++;
			//Assigning null to buff, in order to terminate redundant loop
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
        		fputs(type, fp2);
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
        		fputs(type, fp2);
        		fputs(",",fp2);
        		fputs(stat,fp2);
        		fputs(",",fp2);
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
	//Admin Vie All Bugs page:
	printf("\n\n\n========== All Bug Reports ==========\n");
	
	//variables
	int field_count=0;
	char ch[3096];
	FILE *fp = fopen("BugReport.csv", "r");

	if(!fp)
	{
		printf("Unable to read BugRetport.csv\n");
		return;
	}	

	//Extracting all data frm BugReport.csv
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
				printf("Type:\t\t%s\n\n", buf);
			else if(field_count == 4)
				printf("Status:\t%s\n", buf);
			else if(field_count == 5)
				printf("Priority:\t\t%s\n\n", buf);
			else if(field_count == 6)
				printf("Time:\t\t%s\n\n", buf);
			else
				printf("Unknown error\n");
			field_count++;
			//Assigning null to buff, in order to terminate redundant loop
			buf = strtok(NULL, ",");
		}
	}
	fclose(fp);
	Admin();
}

void SearchBug()
{
	//Admin's Search for bug Section:
	printf("\n\n\n========== Search Bug Reports ==========\n");
	
	//Variables:
	int q_choice[100];
	char q[100];
	
	//Admin's options:
	printf("Search for bug report by:\n");
	printf("[1] bugid\n");
	printf("[2] Username\n");
	printf("[3] Type\n");
	printf("[4] Status\n");
	printf("[5] Priority\n");
	printf("Enter choice [1/2/3/4/5]:\t");
	scanf("%d", &q_choice);
	printf("Enter query: ");
	scanf("%s", q);	
	
	//Functionality
	int found = 1;
	char *bugid, *user, *desc, *type, *stat, *prio, *curr;
	int row_count =0,  field_count=0;
	char ch[3096];
	FILE *fp = fopen("BugReport.csv", "r");


	if(!fp)
	{
		printf("Unable to read BugRetport.csv\n");
		return;
	}	

	//Extracting data from BugReport.csv for the given query
	while(fgets(ch, 3096, fp))
	{
		found = 1;
		field_count = 0;
		char *buf = strtok(ch, ",");
		while(buf)
		{
			if(strcmp(buf, q)==0)
				found = 0;
			if(field_count == 0)
				bugid = buf;
			else if(field_count == 1)
				user = buf;
			else if(field_count == 2)
				desc = buf;
			else if(field_count == 3)
				type = buf;
			else if(field_count == 4)
				stat = buf;
			else if(field_count == 5)
				prio = buf;
			else if(field_count == 6)
				curr = buf;
			else
				printf("Unknown error\n");
			field_count++;
			//Assigning null to buff, in order to terminate redundant loop
			buf = strtok(NULL, ",");
		}
		if(found == 0)
			printf("\nbugid:\t\t%s\nUsername:\t%s\nReport:\t\t%s\nType:\t\t%s\nStatus:\t\t%s\nPriority:\t%s\nTime:\t\t%s\n", bugid, user, desc, type, stat, prio, curr);
		else
			printf("Quesry not found~\n");
	}
	fclose(fp);
	Admin();
	
	
	
	
}
































