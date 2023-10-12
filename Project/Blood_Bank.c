#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<windows.h>

struct Donor{
    char name[100];
    char group[5];
    char location[100];
    char contact[15];
};


//global variables
struct Donor donors[100];
int donors_size = 2;

char state[100] = "main_menu";
char action;


//functions
void main_menu();
void purchase_donor();
void add_donor();
void edit_donor();
void donated_list();
void view_donor();



int main(){
    struct Donor d;
    strcpy(d.name,"Nayer Ali");
    strcpy(d.group,"b+");
    strcpy(d.location,"NSU");
    strcpy(d.contact, "18212312");

    donors[0] = d;
    donors[1] = d;

    printf("%s %d",d.name,d.contact);

    while(state != "EXIT"){
        if(strcmp(state,"main_menu") == 0){
            main_menu();
        }
        if(strcmp(state,"purchase_donor") == 0){
            purchase_donor();
        }
        if(strcmp(state,"add_donor") == 0){
            add_donor();
        }
        if(strcmp(state,"edit_donor") == 0){
            edit_donor();
        }
        if(strcmp(state,"view_donor") == 0){
            view_donor();
        }
        if(strcmp(state,"donated_list") == 0){
            donated_list();
        }
    }
    return 0;
}


void main_menu(){
    system("cls");
    printf("<<<<<<<<<<<<<<<<<<<<<Welcome To blood bank>>>>>>>>>>>>>>>>>>>>\n\n");
    printf("1. Purchase Donation\n");
    printf("2. add Donor\n");
    printf("3. edit donor\n");
    printf("4. view available Donors\n");
    printf("5. view donated list\n");

    printf("press any option...\n");
    action = getch();

    switch(action){
    case '1':
        strcpy(state, "purchase_donor");
        break;
    case '2':
        strcpy(state, "add_donor");
        break;
    case '3':
        strcpy(state, "edit_donor");
        break;
    case '4':
        strcpy(state, "view_donor");
        break;
    case '5':
        strcpy(state, "donated_list");
        break;
    default:
        printf("wrong input");
        getch();
        break;
    }
}



void purchase_donor(){
    system("cls");

    printf("<<<<<<<<<<<<<<<<<<<<<< Purchase donnor>>>>>>>>>>>>>>>>>>>>>>>>\n\n");
    printf("Info:-");

    getch();
    return;
}

void add_donor(){
    return;
}

void edit_donor(){
    return;
}

void donated_list(){
    return;
}

void view_donor(){
    system("cls");

    printf("<<<<<<<<<<<<<<<<<<<<<view available donor>>>>>>>>>>>>>>>>>>>>>>>\n\n");
    printf("          Name           group             location          contact\n");
    for(int i = 0; i < donors_size; i++){
        struct Donor d = donors[i];
        printf("%d. %s %s %s %s\n",i+1,d.name,d.group,d.location,d.contact);
    }
    getch();
    return;
}
