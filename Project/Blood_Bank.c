#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>

#define MAX_DONORS 100

typedef struct Donor SD;

struct Donor{
    char name[100];
    char group[5];
    char location[100];
    char contact[15];
    int age;
    float hemoglobin;
};


//global variables

int donors_size;

char state[100] = "main_menu";
char action;


//functions
void init(SD donors[]);
void main_menu();
void purchase_donor(SD donors[]);
void add_donor(SD donors[]);
void edit_donor(SD donors[]);
void donated_list();
void view_donor(SD donors[]);

void save(SD donors[]);



int main(){
    SD donors[MAX_DONORS];
    init(donors);
    while(state != "EXIT"){
        if(strcmp(state,"main_menu") == 0){
            main_menu();
        }
        if(strcmp(state,"purchase_donor") == 0){
            purchase_donor(donors);
        }
        if(strcmp(state,"add_donor") == 0){
            add_donor(donors);
        }
        if(strcmp(state,"edit_donor") == 0){
            edit_donor(donors);
        }
        if(strcmp(state,"view_donor") == 0){
            view_donor(donors);
        }
        if(strcmp(state,"donated_list") == 0){
            donated_list();
        }
    }
    return 0;
}


void init(SD donors[]){
    donors_size = 0;
    FILE *f = fopen("donors.txt","r");
    while(1){
        SD d;
        if(!fgets(d.name,100,f)) break;

        d.name[strcspn(d.name,"\n")] = '\0';
        fscanf(f,"%s",d.group);
        fscanf(f,"%s",d.location);
        fscanf(f,"%s",d.contact);
        fscanf(f,"%d",&d.age);
        fscanf(f,"%f ",&d.hemoglobin);

        //printf("%s %s %s %s %d %f\n",d.name,d.group,d.location,d.contact,d.age,d.hemoglobin);
        donors[donors_size] = d;
        donors_size++;

    }
}

void main_menu(){
    system("cls");
    printf("<<<<<<<<<<<<<<<<<<<<<Welcome To blood bank>>>>>>>>>>>>>>>>>>>>\n\n");
    printf("1. Purchase Donation\n");
    printf("2. add Donor\n");
    printf("3. edit donor\n");
    printf("4. view available Donors\n");
    printf("5. view donated list\n");

    printf("press any option...");
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



void purchase_donor(SD donors[]){
    system("cls");

    char grp[5];

    printf("<<<<<<<<<<<<<<<<<<<<<< Purchase donnor >>>>>>>>>>>>>>>>>>>>>>>>\n\n");
    printf("Info:-\n");

    printf("Enter blood group: ");
    scanf("%s",grp);
    int j = 1;
    printf("searched List:-\n");
    for(int i = 0; i < donors_size; i++){
        SD d = donors[i];
        if(strcmp(d.group,grp) == 0){
            printf("%d. %s %s %s %s %d %f\n",j,d.name,d.group,d.location,d.contact,d.age,d.hemoglobin);
            j++;
        }
    }
    getch();
    return;
}

void add_donor(SD donors[]){
    system("cls");
    struct Donor d;
    printf("<<<<<<<<<<<<<<<<<< add donor >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");
    printf("Donor Info          :-\n");
    printf("donor Name          :- ");
    gets(d.name);
    printf("donor blood group   :- ");
    gets(d.group);
    printf("Location            :- ");
    gets(d.location);
    printf("Contact             :- ");
    gets(d.contact);
    printf("Donor Age           :- ");
    scanf("%d",&d.age);
    printf("Donor hemoglobin    :- ");
    scanf("%f",&d.hemoglobin);
    fflush(stdin);

    donors[donors_size] = d;
    donors_size++;

    save(donors);
    getch();
    strcpy(state, "main_menu");


}

void edit_donor(SD donors[]){
    system("cls");
    printf("<<<<<<<<<<<<<<<<<<<<Edit donor>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");


    printf("+----------------------------------------------------------------------------------------------------+\n");
    printf("| SL |          Name         |    Age   |    Group   |  Hemoglobin |   Location   |      Contact     |\n");
    printf("+----------------------------------------------------------------------------------------------------+\n");

    for(int i = 0; i < donors_size; i++){
        struct Donor d = donors[i];
        printf("%d. %s %d %s %f %s %s\n",i+1,d.name,d.age,d.group,d.hemoglobin,d.location,d.contact);
    }
    printf("Enter index of which one to edit...");
    action = getch();
    SD *d = &donors[action-'0'-1];




    system("cls");
    printf("%s %d %s %f %s %s\n",d->name,d->age,d->group,d->hemoglobin,d->location,d->contact);

    printf("What would you like to edit:-\n");
    printf("1.Name\n");
    printf("2.Age\n");
    printf("3.group\n");
    printf("4.hemoglobin\n");
    printf("5.Location\n");
    printf("6.contact\n");

    printf("7.exit\n");

    action = getch();
    system("cls");
    switch(action){
    case '1':
        printf("Change Name: ");
        gets(d->name);
        break;
    case '2':
        printf("Change age: ");
        scanf("%d",&d->age);
        break;
    case '3':
        printf("Change Group: ");
        scanf("%s",d->group);
        break;
    case '4':
        printf("Change Hemoglobin: ");
        scanf("%f",&d->hemoglobin);
        break;
    case '5':
        printf("Change Location: ");
        scanf("%s",d->location);
        break;
    case '6':
        printf("Change Contact: ");
        scanf("%s",d->contact);
        break;
    case '7':
        strcpy(state,"edit_view");
        return;

    default:
        break;
    }
    save(donors);
    fflush(stdin);

}

void donated_list(){
    return;
}

void view_donor(SD donors[]){
    system("cls");

    printf("<<<<<<<<<<<<<<<<<<<<<view available donor>>>>>>>>>>>>>>>>>>>>>>>\n\n");
    printf("+----------------------------------------------------------------------------------------------------+\n");
    printf("| SL |          Name         |    Age   |    Group   |  Hemoglobin |   Location   |      Contact     |\n");
    printf("+----------------------------------------------------------------------------------------------------+\n");


    for(int i = 0; i < donors_size; i++){
        struct Donor d = donors[i];
        printf("%d. %s %d %s %f %s %s\n",i+1,d.name,d.age,d.group,d.hemoglobin,d.location,d.contact);
    }
    getch();
    strcpy(state,"main_menu");
}

void save(SD donors[]){
    FILE *f = fopen("donors.txt","w");
    for(int i = 0; i < donors_size; i++){
        struct Donor d = donors[i];
        fprintf(f,"%s\n%s\n%s\n%s\n%d\n%f\n",d.name,d.group,d.location,d.contact,d.age,d.hemoglobin);
    }
    fclose(f);
    printf("Donor added to database.\n");
}
