#include<stdio.h>
//#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>

#define MAX_DONORS 100

typedef struct Donor SD;

struct Donor{
    char name[23];
    char group[7];
    char location[14];
    char contact[18];
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
void delete_donor(SD donors[]);
void view_donor(SD donors[]);


void save(SD donors[]);
void search_donors(char *grp,int *searched_index,SD donors[]);
void view_list(int size,SD list[]);
void delete_index(int index,SD list[]);


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
        if(strcmp(state,"delete_donor") == 0){
            delete_donor(donors);
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
    printf("2. Add Donor\n");
    printf("3. Edit Donor\n");
    printf("4. View Available Donors\n");
    printf("5. Delete Donor\n");

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
        strcpy(state, "delete_donor");
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
    int searched_index[MAX_DONORS];

    for(int i = 0; i < MAX_DONORS; i++) searched_index[i] = -1;

    printf("<<<<<<<<<<<<<<<<<<<<<< Purchase donnor >>>>>>>>>>>>>>>>>>>>>>>>\n\n");
    printf("Info:-\n");

    printf("Enter blood group: ");
    scanf("%s",grp);


    search_donors(grp,searched_index,donors);
    printf("Press the index of donor which you would like to purchase...\n\n");
    printf("press x to exit.\n");

    action = getch();
    if(action == 'x'){
        strcpy(state,"main_menu");
        return;
    }
    int index = searched_index[action-'0'-1];
    system("cls");
    view_list(1,&donors[index]);
    printf("are you sure you want to purchase this donor?\n");
    printf("press y/n:\n");
    action = getch();
    switch(action){
    case 'y':
        delete_index(index,donors);
        save(donors);
        break;
    }
    printf("press any key to continue to main menu..\n");
    getch();
    strcpy(state,"main_menu");
}

void add_donor(SD donors[]){
    system("cls");
    fflush(stdin);

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


    donors[donors_size] = d;
    donors_size++;

    save(donors);
    printf("donor added to database...\n");
    printf("press any key to continue.");
    getch();
    strcpy(state, "main_menu");


}

void edit_donor(SD donors[]){
    system("cls");
    printf("<<<<<<<<<<<<<<<<<<<<Edit donor>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");

    printf("These are the donors added in database:-\n");
    view_list(donors_size,donors);

    printf("Enter index of which one to edit...");
    action = getch();
    SD *d = &donors[action-'0'-1];




    system("cls");
    view_list(1,d);
    //printf("%s %d %s %f %s %s\n",d->name,d->age,d->group,d->hemoglobin,d->location,d->contact);

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
        strcpy(state,"edit_donor");
        return;

    default:
        break;
    }
    save(donors);
    fflush(stdin);

}

void delete_donor(SD donors[]){
    system("cls");
    printf("<<<<<<<<<<<<<<<<<<<<<<<<Delete Donor >>>>>>>>>>>>>>>>>>>>>>>\n\n");
    printf("these are the donors added in the database:-\n");

    view_list(donors_size,donors);

    printf("Enter the index of donor which you want to delete...");
    action = getch();

    system("cls");

    int index = action-'0'-1;
    view_list(1,&donors[index]);

    printf("Are you sure you want to delete this donor?\n");
    printf("press y/n:\n\n");
    printf("press x to exit");
    action = getch();
    if(action == 'x'){
        strcpy(state,"main_menu");
        return;
    }
    delete_index(index,donors);


    getch();


}

void view_donor(SD donors[]){
    system("cls");

    printf("<<<<<<<<<<<<<<<<<<<<<view available donor>>>>>>>>>>>>>>>>>>>>>>>\n\n");
    printf("These are the donors available:-\n");
    view_list(donors_size,donors);

    getch();
    strcpy(state,"main_menu");
}



void save(SD donors[]){
    FILE *f = fopen("donors.txt","wt");
    for(int i = 0; i < donors_size; i++){
        struct Donor d = donors[i];
        fprintf(f,"%s\n%s\n%s\n%s\n%d\n%f\n",d.name,d.group,d.location,d.contact,d.age,d.hemoglobin);
    }
    fclose(f);
}

void search_donors(char *grp,int *searched_index,SD donors[]){

    SD searched_dornors[MAX_DONORS];
    int size = 0;

    for(int i = 0; i < donors_size; i++){
        SD d = donors[i];
        if(strcmp(d.group,grp) == 0){
            searched_dornors[size] = d;
            size++;
            *searched_index = i;
            searched_index++;
        }
    }
    printf("Searched List:-\n");
    view_list(size,searched_dornors);
}


void view_list(int size,SD list[]){
    printf("+----------------------------------------------------------------------------------------------------+\n");
    printf("| SL |          Name         |    Age   |    Group   |  Hemoglobin |   Location   |      Contact     |\n");
    printf("+----------------------------------------------------------------------------------------------------+\n");


    for(int i = 0; i < size; i++){
        SD d = list[i];

        printf("| %d.",i+1);
        if(i < 10) printf(" ");
        printf("|");

        printf("%s",d.name);
        for(int i = 0; i < sizeof(d.name)-strlen(d.name); i++) printf(" ");
        printf("|");

        printf("    %d    |",d.age);

        printf("     %s",d.group);
        for(int i = 0; i < sizeof(d.group)-strlen(d.group); i++) printf(" ");
        printf("|");

        printf("     %0.1f    ",d.hemoglobin);
        if(d.hemoglobin < 10) printf(" ");
        printf("|");

        printf("%s",d.location);
        for(int i = 0; i < sizeof(d.location)-strlen(d.location);i++) printf(" ");
        printf("|");

        printf("%s",d.contact);
        for(int i = 0; i < sizeof(d.contact)-strlen(d.contact); i++) printf(" ");
        printf("|");



        printf("\n");

        //printf("%d. %s %d %s %f %s %s\n",i+1,d.name,d.age,d.group,d.hemoglobin,d.location,d.contact);
    }
    printf("+----------------------------------------------------------------------------------------------------+\n");
}

void delete_index(int index,SD list[]){
    for(int i = index; i < donors_size; i++){
        list[i] = list[i+1];
    }
    donors_size--;
    printf("donor deleted from database.");
    save(list);
}
