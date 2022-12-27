//Admin module of quiz program
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"header.h"
coordinator *c_root = NULL;
extern contestant *co_root ;
//To find the length of the coordinator list
int len_list(coordinator *p)
{
        int count = 0;
        while(p!=NULL)
        {
                count++;
                p = p->next;
        }
        return count;
}
//Admin menu
void admin()
{
        system("clear");
        int ch,exit_flag_1 = 0,exit_flag_2 = 0,exit_flag_3 = 0 ;
        static int chek_list_flag = 0;
        design();
        printf("Welcome to Admin Page \n");
        char user_id[BUFFER_SIZE];
        char temp[15];
	c_root = NULL;
	c_root = new_coordinator(c_root);
	if(c_root != NULL)
		printf("Coordinator listed\n");	
        while(1)
	{
                design();
                printf("1) Manage Coordinator details\n");
                printf("2) Manage Contestant details\n");
                printf("3) Logout and exit\n");
                printf("0) Exit\n");
                design();
                //scanf("%d",&ch);
		ch=int_ans_choice(0,3);
                switch(ch)
                {
                        case COORDINATOR: //Managing coordinator details
                                while(1)
                                {
                                        design();
                                        printf("1) New Coordinator \n");
                                        printf("2) Update Coordinator \n");
                                        printf("3) Delete Coordinator \n");
                                        printf("4) Display Coordinator list\n");
                                        printf("5) Back to previous menu\n");
                                        design();
                                        //scanf("%d",&ch);
					ch=int_ans_choice(1,5);
                                        switch(ch)
                                        {
						case CREATE:
                                                        adding_new_coordinator_to_file();
							c_root=NULL;
                                                        c_root = new_coordinator(c_root);
                                                        break;
                                                case UPDATE:
                                                        printf("enter user-id \n");
                                                        while(1)
                                                        {
                                                                scanf("%s",user_id);
                                                                if(alpha_validator(user_id))
                                                                        break;
                                                                else
                                                                        printf("use only characters\n");
                                                        }

                                                        if((c_root = update_coordinator(user_id,c_root)) == NULL)
                                                        {
                                                                printf("user-id is not found please enter correct user id %s\n",user_id);
                                                        }
                                                        else
                                                        {
                                                                save_coordinator_data_into_file(c_root);
                                                                printf("updated succesfully\n");
                                                        }
                                                        break;
                                                case DELETE: printf("enter user-id \n");
                                                        while(1)
                                                        {
                                                                scanf("%s",user_id);
                                                                if(alpha_validator(user_id))
                                                                        break;
                                                                else
                                                                        printf("use only characters\n");
                                                        }
                                                        c_root = delete_coordinator(user_id,c_root);
                                                        save_coordinator_data_into_file(c_root);
                                                        break;
                                                case DISPLAY:
                                                        display_coordinator(c_root);
                                                        break;
                                                case PREVIOUS:
                                                        exit_flag_1 =1;
                                        }
                                        if(exit_flag_1 == 1)
                                                break;
                                }
                                break ;
                        case CONTESTANT://Managing contestant details
                                while(1)
                                {
                                        design();
					printf("1) Delete Contestant\n");
                                        printf("2) View contestant\n");
                                        printf("0) Back\n");
                                        design();
                                        //scanf("%d",&ch);
					ch=int_ans_choice(0,2);
                                        switch(ch)
                                        {
                                                case 1: 
                                                        printf("enter user-id \n");
                                                        while(1)
                                                        {
                                                                scanf("%s",user_id);
                                                                if(alpha_validator(user_id))
                                                                        break;
                                                                else
                                                                        printf("use only characters\n");
                                                        }
                                                        co_root = delete_contestant(co_root ,user_id);
                                                        save_contestant_data_into_file(co_root);
                                                        break ;
                                                case 2: view_contestant();
                                                        break;
                                                case 0:
                                                        exit_flag_2 = 1;
                                        }
                                        if(exit_flag_2 == 1)
                                                break;
                                }
				break ;

                        case LOGOUT:
                                exit_flag_3 = 1;
                                break ;
                        case EXIT:
                                exit(0);
                                break;
                        default: printf("Invalid option");
                }

                if(exit_flag_3 == 1)
                        break;
        }
}
//Creating list for coordinator
coordinator *create_list_for_cordinator(coordinator *source ,coordinator Data )
{
        if(source == NULL)
        {
                source  = (coordinator *)malloc(sizeof(coordinator));
                strcpy(source->name ,Data.name);
                strcpy(source->userid,Data.userid);
                source->phone_num = Data.phone_num;
                strcpy(source->Email_id, Data.Email_id);
                strcpy(source->pswd , Data.pswd);
                source->next = NULL;
        }
        else
	{
                coordinator *p = source ;
                coordinator *temp = (coordinator *) malloc(sizeof(coordinator));
                strcpy(temp->name ,Data.name);
                strcpy(temp->userid , Data.userid);
                temp->phone_num = Data.phone_num;
                strcpy(temp->Email_id, Data.Email_id);
                strcpy(temp->pswd , Data.pswd);
                 while(p->next != NULL)
                 {
                        p = p->next;
                 }
                p->next = temp;
                temp->next = NULL;
        }
	return source ;
}
//Creation of new coordinator
coordinator *new_coordinator(coordinator *source)
{
        char *cordinator_file = "coordinator_info.txt";
        char buffer[QUESTION_BUFFER_SIZE];
        coordinator c_data ;
        FILE *fptr = fopen(cordinator_file,"r");
        if(fptr == NULL)
        {
                printf("%s file is not found\n",cordinator_file);
        }
        else
	{
                while(!feof(fptr))
                {
                        if(!(fgets(buffer,QUESTION_BUFFER_SIZE,fptr)))
                        {
                                break;
                        }
                        else
                        {
                                c_data = data_extraction_from_cordinator_file(buffer ,c_data);
                                 source = create_list_for_cordinator(source , c_data);
                        }
                }
        }
        fclose(fptr);
        return source;
}
//Updating coordinator
coordinator *update_coordinator(char *str , coordinator *source)
{
        int flag = 0;
        char ch;
        coordinator *p = source ;
        char buffer[20];
        char temp[15];
        while(p!= NULL)
        {
                if(strcmp(p->userid , str) == 0)
		{
                        flag =1;
                        printf("user-id is %s\n",p->userid);
                        printf("name is %s\n",p->name);
                        printf("phone number %ld\n",p->phone_num);
                        printf("Email-id %s\n",p->Email_id);
                        printf("pswd is %s\n",p->pswd);
                        printf("enter y to update\n");
                        scanf(" %c",&ch);
                        if(ch == 'y' || ch == 'Y')
                        {
                                printf("enter the user name \n");
                                while(1)
                                {
                                        getchar();
                                        fgets(p->name , 20 , stdin);
                                        p->name[strlen(p->name)-1] = '\0';
                                        if(alpha_validator(p->name))
                                                break;
                                        else
                                                printf("use only characters\n");
                                }
                                printf("enter phone number\n");
				scanf("%ld",&p->phone_num);
                                printf("enter the email-id\n");
                                while(1)
                                {
                                        getchar();
                                        fgets(p->Email_id,20,stdin);
                                        p->Email_id[strlen(p->Email_id)-1] = '\0';
                                        if(email_validation(p->Email_id))
                                                break;
                                        else
                                                printf("enter correct format of mail\n");
                                }
                                printf("enter the password\n");
                                while(1)
                                {
                                        scanf("%s",p->pswd);
                                        if(password_validation(p->pswd))
                                                break;
                                        else
                                                printf("enter correct format of password\n");
                                }
                        }
                        break;
                }
                p = p->next ;
        }
	if(flag == 0)
        	return NULL;
	else
        	return source;
}
//Display coordinator details
void display_coordinator(coordinator *source)
{
        while(source != NULL)
        {
                printf("user-name is %s user-id is %s \n",source->name , source->userid);
                source = source->next;
        }
}
//to get the length of the coordinator list
int* len_of_list_coordinator(coordinator  *source ,int *index)
{
        int count =0;
        if(source ==  NULL)
        {
                printf("list is empty\n") ;
                return NULL ;
        }
        coordinator *p = source ;
        while(p!=NULL)
        {
                 count ++;
		 p = p->next ;
        }
        *index = count;
        return index;
}

//Searching for coordinator
int *lookup_coordinator(coordinator *source, char *str , int *index )
{
         int count = 1 , check_flag = 0;
         if(source ==  NULL)
         {
                printf("list is empty\n");
                return NULL;
          }
        coordinator *p = source;
        FILE *fptr = fopen(str,"a");
        int i = 0 , j =0;
        while(p!=NULL)
        {
                if(strcmp(p->userid ,str) == 0 )
                {
                        printf("user-id is %s\n",p->userid);
                        printf("name is %s\n",p->name);
                        check_flag = 1;
                        break;
                }
                else
                {
			count++ ;
                }
                p = p->next ;
        }
        if(check_flag == 1)
        {
                *index = count ;
        }
        else
                *index = -1;
        return index;
}

//Deletion of coordinator
coordinator *delete_coordinator(char *str,coordinator *source)
{
        printf("delete_coordinator \n");
        int position = 0,len = 0,link =1;
        char ch;
        if(source ==  NULL)
        {
                printf("list is empty\n") ;
                return NULL ;
         }
        coordinator *p = source ;
        coordinator *temp = source  ;
        position = *lookup_coordinator(p,str,&position) ;
        len = *len_of_list_coordinator(p,&len);
	printf("please enter y to delete \n");
        scanf(" %c",&ch);
        if((ch == 'y' || ch == 'Y')&&position >0)
        {
                if(position == 1)
                {
                        source = temp->next ;
                        temp->next = NULL ;
                }
                else if(position < len)
                {
                        while(link < position-1)
                        {
                                temp = temp->next;
                                link++;
                        }
                        coordinator* del = temp->next;
                        del->next = del->next ;
                        temp->next = del->next ;
                }
                else if(position == len)
                {
                        link = 1 ;
                        while(link < position-1)
                        {
                                temp = temp->next;
                                link++;
                        }
                        temp->next = NULL;
		}
        }
        else
        printf("user-id is not deleted\n");
        return source;
}
//To find the length of the list of contestant
int* len_of_list_contestant(contestant *source ,int *index)
{
        int count =0;
        if(source ==  NULL)
        {
                printf("list is empty\n");
                return NULL;
        }
        contestant *p = source ;
        while(p!=NULL)
        {
                count ++;
                p = p->next ;
        }
        *index = count;
        return index;
}
//Searching for contestant
int *lookup_contestant(contestant *source,char *str,int *index)
{
        int count = 1,check_flag = 0;
        if(source ==  NULL)
	{
                printf("list is empty\n") ;
                return NULL ;
          }
        char *str_1 = "contestant_login_history.txt";
        char *user_delete = "DELETE";
        FILE *fptr = fopen(str_1,"a");
        if(fptr = NULL)
        {
                printf("%s file opening is error \n",str);
        }
        contestant *p = source;
        int i = 0 , j =0;
        while(p!=NULL)
        {
                if(strcmp(p->user_id ,str) == 0 )
                {
                        printf("user-id is %s\n",p->user_id);
                        printf("name is %s\n",p->user_name);
                        check_flag = 1;
                        fprintf(fptr ,"%s,%s,%s\n",p->user_name,p->user_id ,user_delete);
                        fclose(fptr);
                        break;
                }
                else
                {
                        count++ ;
		}
                p = p->next ;
        }
        if(check_flag == 1)
        {
                *index = count ;
        }
        else
                *index = -1;

        return index ;
}
//deleting contestant
contestant *delete_contestant(contestant *source , char *str)
{
        printf("delete_contestant \n");
        int position = 0,len = 0,link =1;
        char ch ;
        if(source ==  NULL)
        {
                printf("list is empty\n") ;
                return NULL;
         }
        contestant *p = source;
        contestant *temp = source;
        position = *lookup_contestant(p,str,&position);
        len = *len_of_list_contestant(p,&len);
        printf("please enter y to delete \n");
        scanf(" %c",&ch);
	if((ch == 'y' || ch == 'Y')&&position >0)
        {
                if(position == 1)
                {
                        source = temp->next ;
                        temp->next = NULL ;
                }
                else if(position < len)
                {
                        while(link < position-1)
                        {
                                temp = temp->next;
                                link++;
                        }
                        contestant* del = temp->next;
                        del->next = del->next ;
                        temp->next = del->next ;
                }
                else if(position == len)
                {
                        link = 1;
                        while(link < position-1)
                        {
                                temp = temp->next;
                                link++;
                        }
                        temp->next = NULL;
                }
	}
        else
        printf("user-id is  not deleted\n");
        return source;
}
//To view the contestant
void view_contestant()
{
        contestant *p = co_root;
        while(p!=NULL)
        {
                printf("%s,%s,%s,%s,%s\n",p->user_name ,p->user_id ,p->phone_num ,p->email_id ,p->pswd );
                p=p->next;
        }
}
//Adding new coordinator to file
void adding_new_coordinator_to_file()
{
        char *coordinator_file = "coordinator_details.txt";
        coordinator source ;
        FILE *fptr = fopen(coordinator_file , "a");
        if(fptr == NULL)
        {
                printf("%s file opening is failed \n",coordinator_file);
                return ;
        }
        else
	 {
                printf("enter the user name \n");
                getchar();
                fgets(source.name,20,stdin);
                source.name[strlen(source.name)-1] = '\0';
                printf("enter the user-id\n");
                scanf("%s",source.userid);
                printf("enter the phone number\n");
                scanf("%ld",&source.phone_num);
                printf("enter the email-id\n");
                /*getchar();
                fgets(source.Email_id , 20 , stdin);
                source.userid[strlen(source.Email_id)] = '\0';
                */
                scanf("%s",source.Email_id);
                printf("enter the password\n");
                getchar();
                fgets(source.pswd , 20 , stdin);
                source.pswd[strlen(source.pswd)-2] = '\0';
                fprintf(fptr,"%s,%s,%ld,%s,%s\n",source.name,source.userid,source.phone_num,source.Email_id,source.pswd);
        }
        fclose(fptr);
}
//Data extraction from coordinator file
coordinator data_extraction_from_cordinator_file(char *str ,  coordinator Data)
{
	int index = 0;
        char *piece ;
                piece = strtok(str,",");
                while(piece !=NULL)
                {
                        //printf("str : %s\n",piece);
                        if(index == 0)
                        {
                                strcpy(Data.name ,piece );
                                index =1;
                        }
                        else if(index ==1)
                        {
                                strcpy(Data.userid ,piece );
                                index =2;
                        }
                        else if(index == 2)
                        {
                                //printf("str : %s and %ld\n",piece ,atoi(piece));
                                Data.phone_num = atoi(piece);
                                index =3;
                        }
                        else if(index == 3)
                        {
                                strcpy(Data.Email_id ,piece );
                                index =4;
                        }
                        else if(index == 4)
                        {
				strcpy(Data.pswd ,piece );
                                index = 5;
                        }
                        piece = strtok(NULL,",");
                }
		return Data;
}
//To save coordinator data into file
void save_coordinator_data_into_file(coordinator *source)
{
        char *coordinator_file = "coordinator_details.txt";
        FILE *fptr = fopen(coordinator_file , "w");
        int count = 0 ;
        if(fptr == NULL)
        {
                printf("%s file opening is failed \n",coordinator_file);
                return ;
        }
        else
        {
                while(source!= NULL)
                {
                        fprintf(fptr,"%s,%s,%ld,%s,%s\n",source->name,source->userid,source->phone_num,source->Email_id,source->pswd);
                        source = source->next ;
		}
        }
        fclose(fptr);
}

//Saving data into file
void save_contestant_data_into_file(contestant *source)
{
        contestant *p = source;
        char *coordinator_file = "contestant_details.txt";
        FILE *fptr = fopen(coordinator_file , "w");
        int count = 0 ;
        if(fptr == NULL)
        {
                printf("%s file opening is failed \n",coordinator_file);
                return ;
        }
        else
        {
                while(source!= NULL)
                {
                        fprintf(fptr,"%s,%s,%s,%s,%s\n",p->user_name ,p->user_id ,p->phone_num ,p->email_id ,p->pswd );
                        source = source->next ;
                }
        }
        fclose(fptr);
}




