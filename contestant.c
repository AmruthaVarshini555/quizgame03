//Program for contestant module
#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
#include<fcnt1.h>
#include<errno.h>
#include<time.h>
#include"header.h"
extern question_ans *QA_root[2] ;
contestant *co_root = NULL;
//Contestant menu
contestant *Contestant()
{
	system("clear");
	co_root = NULL;
	char *quize_file = "updated_QA_file.txt";
	char *quize_file_2 = "updated_QA_file_second.txt";
	if(QA_root[0] == NULL)
	 	QA_root[0]= add_new_quiz( QA_root[0],quize_file);
	if(QA_root[1] == NULL) 
	  	QA_root[1] = add_new_quiz(QA_root[1] , quize_file_2);
	design();
	printf("Welcome to Contestant \n");
	design(); 
	int ch,exit_flag = 0;
	char user_id[BUFFER_SIZE] ;
	char pswd[BUFFER_SIZE];
	int count = 0;
	co_root = NULL;		
	co_root = registration_contestant(co_root);
	if(co_root !=NULL)
	    printf("Contest is listed\n");
	while(1)
	{
		design();
		printf("1) Contestant Registration\n");
		printf("2) Play new quiz\n");
		printf("3) Continue quiz\n");
		printf("4) Check score\n");
		printf("5) Rules\n");
		printf("6) exit\n");
		design();
		//scanf("%d",&ch);
		ch=int_ans_choice(1,6);
		if(ch==-1){
			break;
			exit(EXIT_SUCCESS);
		}
		switch(ch)
		{
			case 1:
				adding_contestant_to_file();
				co_root=NULL;
				co_root = registration_contestant(co_root);
				break ;
			case 2: 
				printf("enter the user-id \n");
				while(1){
					scanf("%s",user_id);
					if(alpha_validator(user_id))
						break;
					else
						printf("use only characters\n");
				}
				printf("enter the password\n");
				while(1){
					scanf("%s",pswd);
					if(password_validation(pswd))
						break;
					else
						printf("Please enter correct password\n");
				}
				play_quiz(user_id , pswd ,co_root,QA_root[0] );
				save_score_to_file(co_root);
				break ;
			case 3: 
				printf("enter the user-id \n");
				while(1){
					scanf("%s",user_id);
					if(alpha_validator(user_id))
						break;
					else
						printf("\nUse only characters\n");
				}
				printf("enter the password\n");
				while(1){
					scanf("%s",pswd);
					if(password_validation(pswd))
						break;
					else
						printf("Please enter correct format of password\n");
				}
				continue_quize_game(user_id,pswd ,co_root,QA_root[1]);	
				break ;
			case 4: 
				check_score_contestants(co_root);
				break;
			case 5:
				rules();
				break;
			case 6:
				exit_flag = 1;
				break;	
		}
			if(exit_flag == 1)
			break;
	}
}

contestant *create_list_of_contestant(contestant *source , contestant Data)
{
	if(source == NULL)
	{
		source  = (contestant *)malloc(sizeof(contestant));
		strcpy(source->user_name ,Data.user_name);
		strcpy(source->user_id , Data.user_id);
		strcpy(source->phone_num , Data.phone_num);
		strcpy(source->email_id, Data.email_id);
		strcpy(source->pswd , Data.pswd);
		source->next = NULL;
	}
	else 
	{
		contestant *p = source ;	
		contestant *temp = (contestant *) malloc(sizeof(contestant));
		strcpy(temp->user_name ,Data.user_name);
		strcpy(temp->user_id , Data.user_id);
		strcpy(temp->phone_num , Data.phone_num);
		strcpy(temp->email_id, Data.email_id);
		strcpy(temp->pswd , Data.pswd);
		 while(p->next != NULL)
		 {
		 	p = p->next ;		 	
		 }
		p->next = temp ;
		temp->next = NULL;	 
	}
	return source;
}

//Contestant Registration
contestant *registration_contestant(contestant *source)
{
	char *str = "contestant_details.txt" ;
	char buffer[QUESTION_BUFFER_SIZE];
	contestant c_data;
	FILE *fptr = fopen(str,"r");
	if(fptr == NULL)
	{
		printf("%s file is not found\n",str);
		return NULL;
	}
	else 
	{
		while(!feof(fptr))
		{
			if(!(fgets(buffer,QUESTION_BUFFER_SIZE,fptr)))
			{
				//printf("string reading is fail\n");
				break ;
			}
			else 
			{
				c_data = data_extraction_from_contestant_file(buffer ,  c_data);
				//printf("user name %s\n",c_data.user_name);
			 	 source = create_list_of_contestant(source , c_data);						
			}
		}
	}
	fclose(fptr);	
	return source;		
}
//Contestant login
contestant *user_login(char *user_id , char *pswd ,contestant *c_root )
{
	int flag =0;
	contestant *p = c_root ;
	//printf("user-id %s len %d , pswd %s , len %d \n",user_id,strlen(user_id),pswd,strlen(pswd));
	while(p!= NULL)
	{
		//printf("user-id %s ,%d , pswd %s ,%d\n",p->user_id,strlen(p->user_id),p->pswd,strlen(p->pswd));
		if(strcmp(p->user_id ,user_id )== 0)
		{
			if(strcmp(p->pswd ,pswd )== 0)
			{
				flag = 1;
				printf("well come %s\n",p->user_name);
				return p;
			}
		}
		p = p->next;
	}
	if(flag == 0)
	{
		printf("user name or passwors is not matching\n");
		return NULL;
	}	
}

int get_ans(char ch)
{
	if(ch == 'A' || ch == 'a')
		return 1;
	else if(ch == 'B' || ch == 'b')
		return 2;
	else if(ch == 'c' || ch == 'C')
		return 3;
	else if(ch == 'D' || ch == 'd')
		return 4;
}

//Adding contestant to file
void adding_contestant_to_file()
{
	contestant Data ;
	char buffer[30];
	char *str = "contestant_details.txt" ;
	FILE *fptr ;
	fptr = fopen(str,"a");
	if(fptr == NULL)
	{
		printf("%s file opening error\n",str);
		return ;
	}
	else
	{
		printf("enter the name\n");
		getchar();
		fgets(Data.user_name,20,stdin);
		Data.user_name[strlen(Data.user_name)-1] = '\0';
		
		printf("enter user-id \n");
		fgets(Data.user_id,20,stdin);
		Data.user_id[strlen(Data.user_id)-1] = '\0';
		
		printf("enter Phone Number\n");
		fgets(Data.phone_num , 20 , stdin);
		Data.phone_num[strlen(Data.phone_num)-1] = '\0';
		printf("phone number %s\n",Data.phone_num);
		
		printf("enter email-id\n");
		//fgets(Data.email_id , 20 , stdin);
		scanf("%s",Data.email_id);
		Data.email_id[strlen(Data.email_id)] = '\0';
		
		printf("enter the password\n");
		getchar();	
		fgets(Data.pswd , 20 , stdin);
		Data.pswd[strlen(Data.pswd)-1] = '\0';
		
		fprintf(fptr,"%s,%s,%s,%s,%s\n",Data.user_name ,Data.user_id ,Data.phone_num ,Data.email_id ,Data.pswd );	
	}
	fclose(fptr);
}

//Extraction of contestant details from file
contestant data_extraction_from_contestant_file(char *str , contestant Data)
{
	int index = 0;
	char *piece ;
		piece = strtok(str,",");
		while(piece !=NULL)
		{
			//printf("str : %s\n",piece);
			if(index == 0)
			{
				strcpy(Data.user_name ,piece );
				index =1;
			}
			else if(index ==1)
			{
				strcpy(Data.user_id ,piece );
				index =2;	
			}
			else if(index == 2)
			{
				strcpy(Data.phone_num ,piece );
				index =3;
			}
			else if(index == 3)
			{
				strcpy(Data.email_id ,piece );
				index =4;		
			}
			else if(index == 4)
			{
				strcpy(Data.pswd ,piece );
				Data.pswd[strlen(Data.pswd)-1] = '\0';
				index = 5;	
			}
			piece = strtok(NULL,",");			
		}
	return Data;	
}
//Play quiz
contestant *play_quiz(char *user_id , char *pswd , contestant *c_root)
{
	contestant *user = c_root ; 
	if(QA_root[0] == NULL)
	{
		return NULL;
	 	printf("First Round Questions are not available\n");
	 }
	 	
	 if(QA_root[1] == NULL) 
		printf("second Round Questions are not available\n");
	if(user_id == NULL)
	{
		printf("No user are found\n");
		return NULL;
	}
	user = user_login(user_id,pswd,user);	
	if(user!=NULL)
	{
		design();
		printf("------WELCOME TO FIRST ROUND-------\n");
		design();
		first_round_of_quiz_game(user,1);
		printf("first round score is %d\n",user->first_score);	
		design();
		if(user->first_score >= 3)
		{
			design();
			design();
			printf("CONGRATULATION %s \n",user->user_name);
			printf("WELLCOME TO SECOND ROUND\n");
			design();
			design();
			//second_round_of_quiz_game(user,2);
			first_round_of_quiz_game(user,2);
			design();	
			printf("second round is %d\n",user->second_socre);
		}	
	}
	else
	printf("USER IS NOT FOUND PLEASE REGISTER \n");				
}

//continue the quiz game where the contestant stopped
contestant *continue_quize_game(char *user_id , char *pswd,contestant *c_root ,question_ans *QA_root)
{
	contestant *p = c_root ;
	contestant *user = NULL ;
	question_ans *q = QA_root;
	int count = 0;
	if(p == NULL)
	{
		printf("No user are found\n");
		return NULL;
	}
	if(q == NULL)
	{
		printf("questions are not found\n");
		return NULL;
	}
	user = user_login(user_id,pswd,p);
	//printf("return user id address %p\n",user);
	if(user!=NULL)
	{
		char ch ;
		int ans;
		if( user->first_score >= 3 && user->check == 1)
		{
			if(user->check==1){
				printf("You already played the second game\n");
				printf("You are score is %d\n",user->second_score);
			}
			design();
			printf("welcome to second round %s\n",user->user_name);
			design();
			first_round_of_game(user,2);
			printf("second round marks is %d\n",user->second_score);
		}
		else{
			printf("you are first round marks are less than 3 so you can't procced for second round \n");
			printf("please clear the first round\n");
		}
	}
	else
		printf("please check the login credentials\n");
	return c_root;
}
//checking score of the contestants			
void check_score_contestants(contestant *p)
{
	while(p!=NULL)
	{
		if(p->check == 1)
		{
			printf("%s first round socre is %d\n",p->user_name ,p->first_score );
			if(p->check_2 == 1)
			{
				printf("%s first round socre is %d\n",p->user_name ,p->second_score);
			}
			else
			{
				printf("%s is not started the second round\n",p->user_name);
			}
		}
		printf("%s is not started the game\n",p->user_name);
		p=p->next;	
	}	
}
//first round of quiz
void first_round_of_quiz_game(contestant *c_root , int round)
{
	contestant *user = c_root ;
	question_ans *q = NULL;
	if(round == 1)
		q = QA_root[0];
	else if(round == 2)
		 q = QA_root[1];
		int  count = 0;
		char ch;
		while(q!=NULL)
		{
			printf("Q_n %d::",q->q_num);
			printf("%s\n",q->question);
			if(q->check_flag == 1)
			{
				for(int i = 0 ; i < 4 ; i++)
					printf("%c) %s\n",65+i,q->ans_string[i]);
				
				scanf(" %c",&ch) ;
				if(q->ans_int == get_ans(ch))
				{
					printf("correct ans \n");
					count++;
				}
				else
					printf("wrong ans\n");
			}
			else if(q->check_flag == 2)
			{
				for(int i = 0 ; i < 4 ; i++)
					printf("%c) %d\n",65+i,q->ans_integer[i]);
				scanf(" %c",&ch);
				if(q->ans_int == get_ans(ch))
				{
					printf("correct ans \n");
					count++;
				}
				else
					printf("wrong ans\n");
			}
			q = q->next;
		}
		if(round == 1)
		{
			user->first_score = count ;
			user->check = 1;
		}
		else if(round == 2)
		{
			user->second_score = count ;
			user->check_2 = 1;
		}				
}
//Second round of quiz
void second_round_of_quiz_game(contestant *c_root , int round)
{
	contestant *user = c_root ;
	question_ans *q = NULL;
	int count ;
	q = QA_root[1];
		while(q!=NULL)
		{
			printf("Q_n %d::",q->q_num);
			printf("%s\n",q->question);
			if(q->check_flag == 1)
			{
				for(int i = 0 ; i < 4 ; i++)
					printf("%c) %s\n",65+i,q->ans_string[i]);

				if(q->ans_int == ans(1))
				{
					printf("correct ans \n");
					count++;
				}
				else
					printf("wrong ans\n");
			}
			else if(q->check_flag == 2)
			{
				for(int i = 0 ; i < 4 ; i++)
					printf("%c) %d\n",65+i,q->ans_integer[i]);
				//scanf(" %c",&ch);	
				if(q->ans_int == ans(1))
				{
					printf("correct ans \n");
					count++;
				}
				else
					printf("wrong ans\n");
			}
			q = q->next;
		}
			user->second_score = count ;
			user->check_2 = 1;		
}

//Saving score to file
void save_score_to_file(contestant *p)
{
	char *str = "contestant_score_card.txt";
	char *str_co="history.txt";
	FILE *fptr = fopen(str,"a");
	FILE *fptr_login=fopen(str_co,"a");
	if(fptr == NULL)
	{
		printf("%s file opening error\n",str);
		break;	
	}
	else
	{
		while(p!=NULL)
		{
			if(p->check == 1)
			{
				if(p->check_2 == 1)
				{
					fprintf(fptr,"%s,%s,%d,%d\n",p->user_name , p->user_id , p->first_score , p->second_score);
					fprintf(fptr_login,"%s,%s,%s\n",p->user_name , p->user_id ,"LOGIN");		
				}
				else
				{
					fprintf(fptr,"%s,%s,%d,%d\n",p->user_name , p->user_id , p->first_score , 0);
					fprintf(fptr_login,"%s,%s,%s\n",p->user_name , p->user_id ,"LOGIN");		
				}
			}
			p=p->next;
		}	
	}
	fclose(fptr);
	fclose(fptr_login);	
}

int ans(int num)
{
	// get stdin flags
    int flags = fcntl(0, F_GETFL, 0);
    if (flags == -1) {
        // fcntl unsupported
        perror("fcntl");
        return -1;
    }
    // set stdin to non-blocking
    flags |= O_NONBLOCK;
    if(fcntl(0, F_SETFL, flags) == -1) {
        // fcntl unsupported
        perror("fcntl");
        return -1;
    }
	char ch;
    //char st[1024] = {0}; // initialize the first character in the buffer, this is generally good practice
   // printf ("Please enter a line of text : ");
    time_t end = time(0) + 20; //5 seconds time limit.
    // while
    while(time(0) < end  // not timed out
        && scanf(" %c", &ch) < 1 // not read a word
        && errno == EAGAIN); // no error, but would block

	//printf("str :%s\n",st);
	
	if(ch >= 'a' && ch < 'd')
	{
		if(ch == 'a')
			return 1;
		else if(ch == 'b')
			return 2;
		else if(ch == 'c')
			return 3;
		else if(ch == 'd')
			return 4;
		else 
			return 0;
	}	
	else if(ch >= 'A' && ch <= 'D')
	{
		
		if(ch == 'A')
			return 1;
		else if(ch == 'B')
			return 2;
		else if(ch == 'C')
			return 3;
		else if(ch == 'D')
			return 4;
		else 
			return 0;
	}	
	else
		return 0;	
}

//Rules for playing quiz
void rules()
{
	printf("\n---------------------RULES----------------");
	printf("\n>>In this game there are 2 rounds, WARMUP ROUND & CHALLENGE ROUND");
	printf("\n>>In Warmup round you'll be asked a total of 5 questions to test your");
	printf("\n  knowledge. You must be able to answer 3 questions out of 5 so that");
	printf("\n  you'll be eligible to the 2nd round.. Otherwise you can't play the game");
	printf("\n>>In 2nd round i.e Challenge round, you'll be given with 10 questions and");	
	printf("\n  to make the quiz a bit interesting there'll be time limit of 20 seconds");
	printf("\n  for each question in the quiz...");
	printf("\n>>You will be given with options A, B, C, and D and you have to choose the");
	printf("\n  right option from these four options.");
	printf("\n>>If you answer all the questions correctly then you are the champion...!!");
	printf("\n>>No negative marking for wrong answers");
	printf("\n------------------ALL THE BEST-----------------");
	printf("\nPress enter to continue..");
	getchar();
	exit(0);
}


