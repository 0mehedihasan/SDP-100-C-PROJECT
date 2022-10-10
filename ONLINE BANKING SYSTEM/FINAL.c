#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<math.h>
#include<dos.h>
#include<time.h>
#include<ctype.h>
#include<windows.h>
#include<time.h>
#define ENTER 13
#define BKSP 8
#define SPACE 32
#define TAB 9
#define CNN 15
#define CBN 4

struct user {
	char phone[50];
	char name[50];
	char password[50];
	float balance;
};

COORD coordinates = {0,0};
void gotocoordinate(int x,int y)
{
    coordinates.X=x;
    coordinates.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coordinates);
}
COORD coord = {0, 0};
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void setcolor(int ForgC)
{
    WORD wColor;
    HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if(GetConsoleScreenBufferInfo(hStdOut,&csbi))
    {
        wColor=(csbi.wAttributes & 0xF0)+(ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut,wColor);

    }
}
void welcomeMessage()
{
    system("cls");
    setcolor(1);
    printf("\n\n\n\n\n");
    printf("\n\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\t\t      =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t      =                  WELCOME                  =");
    printf("\n\t\t      =                    TO                     =");
    printf("\n\t\t      =                  ONLINE                   =");
    printf("\n\t\t      =                  BANKING                  =");
    printf("\n\t\t      =                  SYSTEM                   =");
    printf("\n\t\t      =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\n\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\n\n\t\t\t Enter any key to continue.....");
    getch();
}

void loading()
{
    system("cls");
    int r,q;

    gotoxy(36,14);
    setcolor(1);
    printf("LOADING...");
    gotoxy(30,15);
    for(r=1; r<=25; r++)
    {
        for(q=0; q<=100000000; q++);
        printf("%c",177);
    }
    system("cls");


}

int main(){
	struct user user,usr;
	char filename[50],phone[50],password[50],phone2[50];
	FILE *fp,*fptr;
	int opt,choice;
	int amount;
	char cont = 'y';
	/*color and font size start here*/
	system("COLOR F1");
     static CONSOLE_FONT_INFOEX  fontex;
     fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
     HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
     GetCurrentConsoleFontEx(hOut, 0, &fontex);
     fontex.FontWeight = 500;
     fontex.dwFontSize.X = 30;
     fontex.dwFontSize.Y = 30;
     SetCurrentConsoleFontEx(hOut, NULL, &fontex);
     /*color and font end here*/
    welcomeMessage();
    system("cls");
    loading();
    system("cls");
	printf("\nWhat do you want to do?");
	printf("\n\n1.Register your account");
	printf("\n2.Login to your account");

	printf("\n\nPlease enter your choice:\t");
	scanf("%d",&opt);
	if(opt == 1){
		system("cls");  //clearing the screen
		printf("\nEnter your name:\t");
		scanf("%s",user.name);
		printf("Enter your phone number:\t");
		scanf("%s",user.phone);
		printf("Enter your new password:\t");
		scanf("%s",user.password);
		user.balance=0;
		strcpy(filename,user.phone);
		fp=fopen(strcat(filename,".dat"),"w");
		fwrite(&user,sizeof(user),1,fp);
		if(fwrite != 0){
			printf("Successfully registered");
		}
	}
	else if(opt == 2){
		system("cls");
		printf("\nPhone No.:\t");
		scanf("%s",phone);
		printf("Password:\t");
		scanf("%s",password);
		fp = fopen(strcat(phone,".dat"),"r");
		if(fp == NULL) printf("Account number not registered");
		else {
			fread(&user,sizeof(struct user),1,fp);
			fclose(fp);
			if(!strcmp(password,user.password)){
				while(cont == 'y'){
				system("cls");
				printf("\n\tWelcome %s",user.name);
				printf("\nPress 1 for balance inquiry");
				printf("\nPress 2 for adding fund");
				printf("\nPress 3 for cash withdraw");
				printf("\nPress 4 for online transfer");
				printf("\nPress 5 for changing password");
				printf("\nPress 6 for changing phone number");
				printf("\nPress 7 for checking user info\n\n");
				scanf("%d",&choice);
				switch(choice){
					case 1:
						printf("Your current balance is TK. %.2f",user.balance);
						break;

					case 2:
						system("cls");
						printf("Enter amount to be added:\t");
						scanf("%d",&amount);
						user.balance += amount;
						fp = fopen(phone,"w");
						fwrite(&user,sizeof(struct user),1,fp);
						if(fwrite !=0) printf("\n\nYou have deposited TK.%d",amount);
						fclose(fp);
						break;

					case 3:
						system("cls");
						printf("Enter withdrawal amount:\t");
						scanf("%d",&amount);
						if(amount % 500 != 0) printf("\nSorry amount should be multiple of 500");
						else if(amount>user.balance) printf("\nSorry insufficient balance");
						else {
							user.balance -= amount;
						fp = fopen(phone,"w");
						fwrite(&user,sizeof(struct user),1,fp);
						if(fwrite !=0) printf("\n\nYou have withdrawn TK.%d",amount);
						fclose(fp);
						}
						break;

					case 4:
						printf("Please enter the phone number to transfer balance:\t");
						scanf("%s",phone);
						printf("Enter the amount to transfer:\t");
						scanf("%d",&amount);
						if(amount > user.balance) printf("\nSorry insufficient balance");
						else {
							fptr = fopen(strcat(phone,".dat"),"r");
							if(fptr==NULL) printf("Sorry number is not registered");
							else {
								fread(&usr,sizeof(struct user),1,fptr);
								fclose(fptr);

								usr.balance += amount;

								fptr = fopen(phone,"w");
								fwrite(&usr,sizeof(struct user),1,fptr);
								if(fwrite != 0){
								// 	printf("ACcount:%s",usr.ac);
								// printf("\npassword%s",usr.password);
								// printf("\nphone%s",usr.phone);
								// printf("\nbalance%f",usr.balance);
									printf("Your transfer is completed. You have transfered TK.%d to %s",amount,usr.phone);
									fclose(fptr);
									user.balance -= amount;
									strcpy(filename,user.phone);
									fp = fopen(strcat(filename,".dat"),"w");
									fwrite(&user,sizeof(struct user),1,fp);
									fclose(fp);
								}
							}
						}
						break;
					case 5:
						printf("\n\nPlease enter your old password:\t");
						scanf("%s",password);
						if(!strcmp(password,user.password)){
							printf("\n\nPlease enter your new password:\t");
							scanf("%s",password);
							strcpy(user.password,password);
							strcpy(filename,user.phone);
							fp = fopen(strcat(filename,".dat"),"w");
							fwrite(&user,sizeof(struct user),1,fp);
							fclose(fp);
							printf("\nPassword successfully changed");
						}else printf("\nSorry your password is wrong");
						break;

                    case 6:
						printf("\n\nPlease enter your current phone number:\t");
						scanf("%s",phone);
						if(!strcmp(phone,user.phone)){
							printf("\n\nPlease enter your new phone number:\t");
							scanf("%s",phone);
							strcpy(user.phone,phone);
							strcpy(filename,user.phone);
							fp = fopen(strcat(filename,".dat"),"w");
							fwrite(&user,sizeof(struct user),1,fp);
							fclose(fp);
							printf("\nPhone number successfully changed");
						}else printf("\nSorry your phone number is wrong");
						break;
                    case 7:
						printf("Your name is: %s",user.name);
						printf("\nYour phone number is: %s",user.phone);
						printf("\nYour current balance is TK %.2f",user.balance);

					default:
					break;
				}//switch ends here
				printf("\n\nDo you want to continue?[y/n]:\t");
				scanf("%s",&cont);
				}
			}
			else {
				printf("Invalid password");
			}
		}
		printf("\n\n***Thank you for banking with us***\n\n");
	}

	return 0;
}
