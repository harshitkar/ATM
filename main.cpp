#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<string.h>

//Global Declarations

//Structure of Data in bank server
struct server{
	int acc_no;
	int pin;
	float balance;
};

//Demo data
struct server s[4]={
	{98,1111,10000},
	{99,2222,10000},
	{89,3333,10000},
	{64,4444,10000},
};

int max_attempts = 3,i;

//Function to verify entered pin
int verify_pin()
{
	int count=0,flag=0;
	//Dynamic memory allocation to account no and pin input
	int *input_acc_no=(int*)malloc(sizeof(int)),*input_pin=(int*)malloc(sizeof(int));
	xx:
	
	printf("\nEnter Your Account number: ");
	scanf("%d",input_acc_no);
	
	//to find account index from server
	for(i=0;i<4;i++){
		if(s[i].acc_no==*input_acc_no)
		{
		    flag=1;
			break;
		}
	}
	
	//If account number doesn't match with any name in server
	if(flag==0)
	{
		printf("\nSORRY! We cannot find your account\n*");
		//If account number is incorrect then it again asks the user
		goto xx;
	}
	
	//value of i is from last iteration of previous loop
	while(*input_pin!=s[i].pin)
	{
		printf("\nWelcome\nPlease Enter Your PIN : ");
		scanf("%d",input_pin);
		if(*input_pin!=s[i].pin)
		{
			//Beep sound frequency-610 and Duration- 5 seconds 
			Beep(610,500);
			printf("\nINVALID PIN!!");
		}
		count++;
		if(count==max_attempts&&*input_pin!=s[i].pin)
		{
			printf("\n\nYou have already took %d attempts!\n\t*Try Next time*",max_attempts);
			return 0;
		}
	}
	free(input_acc_no);
	free(input_pin);
}

//MAIN MENU
int menu()
{
	int choice; // The user's choice
    printf("\n*** ATM ready for your service ***\n");
    printf("1. Check Balance\n");
    printf("2. Withdraw Cash\n");
    printf("3. Deposit Cash\n");
    printf("4. Transfer Money\n");
    printf("5. Clear and exit from your account\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice); // Get the user's choice
    return choice;
}

//Function to deposit cash
void deposit()
{
	float amount;
	d1:
    printf("\nEnter the amount which you want to deposit in your account : ");
    scanf("%f",&amount);

    if (amount <= 0)
    {
        printf("\nInvalid amount");
        //If the amount is invalid then it again asks the user for input
        goto d1;
    }

    s[i].balance+=amount;
    printf("\n%.2f RS successfully deposited in your account.\n", amount);
    printf("Your Current balance is : %.2f RS\n", s[i].balance);

}

//Function to withdraw cash
void withdraw()
{
	float amount;
	w1:
	printf("\nEnter the amount to be withdrawn : ");
	scanf("%f",&amount);
	if (amount <= 0)
    {
        printf("\nInvalid amount");
        goto w1;
    }
	else if (s[i].balance<amount)
	{
		printf("\nError : Insufficient funds!!");
		goto w1;
	}
	else 
	{
		s[i].balance-=amount;
		printf("\n%.2f RS successfully withdrawn",amount);
		printf("\nYour Remaining balance is : %f",s[i].balance);
	}
}

//Function to check the current balance
void check_bal()
{
	printf("\nYour Balance is %.2f RS\n",s[i].balance);
}

//Function to transfer money
void transfer()
{
	int j,flag=0;
	
	//Dynamic memory allocation to reviever account number
	int *reciever=(int*)malloc(sizeof(int));
	
	t0:
	printf("\nEnter Account number to which you want to transfer : ");
	scanf("%d",reciever);
	
	//to find reciever's account index from server
	for(j=0;j<4;j++){
		if(s[j].acc_no==*reciever)
		{
		    flag=1;
			break;
		}
	}
	if(flag==0)
	{
		printf("\nSORRY! We cannot find your account\n*");
		goto t0;
	}
	
	float amount;
	t1:
	printf("\nEnter the amount to be transferred : ");
	scanf("%f",&amount);
	if (amount <= 0)
    {
        printf("\nInvalid amount");
        goto t1;
    }
	else if (s[i].balance<amount)
	{
		printf("\nError : Insufficient Balance!!");
		goto t1;
	}
	else 
	{
		s[i].balance-=amount;
		s[j].balance+=amount;
		printf("\nAmount successfully Transferred!!");
		printf("\nYour Remaining balance is : %f",s[i].balance);
	}
}
 
//MAIN FUNCTION
int main()
{
	yy:
	
	//color 9-light blue and f- bright white
	//use system("color \e[0;33m"); to access color menu
	system("color 9f");
	
	//data type used to define variable containing time
	time_t now;
	
	//time() returns current time
	time(&now);
	printf("\n");
	
	//ctime() is used to set time_t object that contains a time value
	//This function accepts single parameter time_ptr
	printf("\t\t\t\t\t      %s",ctime(&now));
	printf("\n\t\t\t\t-------------------*Welcome To ATM*-------------------\n");
	
	int choice;

	if (verify_pin()) 
	{ 
		system("cls");
        do 
		{
            choice = menu(); 
            switch (choice) 
			{ 
                case 1: 
                    check_bal();
                    break;
                case 2: 
                    withdraw(); 
                    break;
                case 3: 
                    deposit(); 
                    break;
                case 4: 
                    transfer(); 
                    break;
                default: 
                    printf("\nInvalid choice. Please try again.\n"); 
                    break;
            }
        } while (choice != 5);
        system("cls");
        goto yy;
	}
    return 0;
}
