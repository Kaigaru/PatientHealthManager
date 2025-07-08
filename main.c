#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structure for patient
struct Patient{
    char fName[50];
    char sName[50];
    int day, month, year;
    float height;
    int weight;
    char nutritionStatus[50];
    //extra
    float bmi;
    struct Patient *next;

};

void SearchPatient(struct Patient*, char*);
void UpdateNutritionalStatus(struct Patient *);
struct Patient *initialisePatients(char *);

struct Patient *createNode(char*, char*, int, int, int, float, int, char*);
struct Patient *sortedInsert(struct Patient*, struct Patient *);
//struct Patient *insertionSort(struct Patient*);
struct Patient *InsertNewPatient(struct Patient *,char*, char*, int, int, int, float, int, char*);
struct Patient *initialiseUnhealthyPatientList(struct Patient*,struct Patient*);
struct Patient *deleteNode(struct Patient *, struct Patient *, struct Patient*);


void printPatients(struct Patient*);

int main() {
    struct Patient *head = NULL;
    struct Patient *unhealthyList = NULL;
    head = initialisePatients("patient.txt");
    char fName[50];
    char sName[50];
    int day, month, year;
    float height;
    int weight;
    char nutritionStatus[50] = "NA";

    int choice = 0;
    while(choice != 6){
        printf("\n----- MENU -----\n"
               "1. Add patient\n"
               "2. Show patients\n"
               "3. Search patient\n"
               "4. Create an unhealthy patient list\n"
               "5. Show unhealthy patients\n"
               "6. Exit\n");
        printf("\nEnter your option:");
        scanf("%d",&choice);
        switch (choice) {
            case 1:
                printf("\n");
                printf("Enter patient's first name:");
                scanf("%s",fName);
                printf("Enter patient's last name:");
                scanf("%s",sName);
                printf("Enter patient's date of birth:");
                scanf("%d/%d/%d",&day, &month, &year);
                printf("Enter patient's height (m):");
                scanf("%f", &height);
                printf("Enter patient's weight (kg):");
                scanf("%d",&weight);
                head = InsertNewPatient(head,fName, sName,
                                        day, month, year,height,
                                        weight, nutritionStatus);
                //printPatients(head);
                break;
            case 2:
                printf("Patients are as follows:\n");
                printPatients(head);
                //printf("end\n");
                break;
            case 3:
                printf("Enter the name of the patient you want to search:");
                scanf("%s",fName);
                printf("Results:\n");
                SearchPatient(head,fName);
                break;
            case 4:

                //this function takes list and from it rewrites unhealthy patients
                //creating a new unhealthy list
                //it doesn't store previous unhealthy list
                unhealthyList = initialiseUnhealthyPatientList(head,unhealthyList);
                //printPatients(unhealthyList);
                break;
            case 5:
                printPatients(unhealthyList);
                break;

            default:
                if(choice!=6){
                    printf("\nThere is no option like this\nTry again!!!\n");
                    fflush(stdin);
                }
                break;
        }

    }

    return 0;
}
//general traverse
void SearchPatient(struct Patient* head, char *name){
    if(head == NULL){
        printf("no list");
        return;
    }
    int f = 0;
    struct Patient *temp = head;
    while(temp!=NULL){
        if(strcmp(temp->fName,name)==0){
            printf("%s;%s;%d/%d/%d;%.2f;%d;%s;\n", temp->fName, temp->sName,temp->day,
                   temp->month,temp->year,temp->height,temp->weight,temp->nutritionStatus);
            f++;
        }
        temp = temp->next;
    }
    if(f==0){
        printf("\nPatient not found!!!");
    }
}

struct Patient *deleteNode(struct Patient *prevNode, struct Patient *deleteNode, struct Patient *head){

    //head
    if(prevNode==NULL){
        head = head->next;
    }
    //tail
    //check if deleteNode next NUll
    else if (deleteNode->next == NULL){
        prevNode->next=NULL;
    }
    else{
        prevNode->next = deleteNode->next;
    }
    free(deleteNode);

    return head;
}

//updates every time, when you will call the function
struct Patient *initialiseUnhealthyPatientList(struct Patient *allList,struct Patient *uList ){
    if(allList==NULL){
        printf("List of patients is empty");
        return uList;
    }
        //traverse
        struct Patient *temp = allList;
        struct Patient *prev;
        prev = NULL;
        int count = 0;

        while(temp!=NULL){
            if(temp->bmi>29.9){

                count++;
                //copy
                struct Patient *newNode = createNode(temp->fName, temp->sName,
                        temp->day, temp->month, temp->year, temp->height,
                        temp->weight, temp->nutritionStatus);
                uList = sortedInsert(uList,newNode);
                UpdateNutritionalStatus(uList);

                allList = deleteNode(prev,temp,allList);
                if (prev == NULL) {
                    temp = allList;  //new head
                } else {
                    temp = prev->next;  // Otherwise, continue from the next node after prev
                }
            }
            else{
                //move
                prev=temp;
                temp=temp->next;
            }
        }
        printf("The number of patients removed from the patient list and moved to "
               "the unhealthy patients list is %d",count);
    return uList;
}

struct Patient *InsertNewPatient(struct Patient *head,char name[50], char sName[50], int day, int month,
        int year, float height, int weight, char nutritionStatus[50]){
    struct Patient *newNode = createNode(name, sName, day, month, year, height, weight, nutritionStatus);
    head = sortedInsert(head,newNode);
    UpdateNutritionalStatus(head);
    printf("The patient has been added!\n");
    return head;
}

struct Patient *initialisePatients(char fileName[50]){
    FILE *File = fopen(fileName,"r");
    if(File == NULL){
        printf("File cannot be open\n");
    }

    char fName[50];
    char sName[50];
    int day, month, year;
    float height;
    int weight;
    char nutritionStatus[50];
    struct Patient *head = NULL;

    while(fscanf(File,"%[^;];%[^;];%d/%d/%d;%f;%d;%[^;\n]\n",
                 fName, sName, &day, &month, &year,
                 &height, &weight,nutritionStatus) != EOF){
        struct Patient *newNode = createNode(fName, sName, day, month, year, height, weight, nutritionStatus);
        head = sortedInsert(head,newNode);

    }
    printf("The %s file has been loaded successfully.\n",fileName);
    UpdateNutritionalStatus(head);
    //printPatients(head);
    return head;

}

struct Patient *createNode(char name[50], char sName[50], int day, int month, int year, float height, int weight, char nutritionStatus[50]){
    struct Patient *newNode = malloc(sizeof(struct Patient));
    if(newNode==NULL){
        printf("cannot allocate memory");
        exit(1);
    }

    strcpy(newNode->fName,name);
    strcpy(newNode->sName,sName);
    newNode->day = day;
    newNode->month = month;
    newNode->year = year;
    newNode->height = height;
    newNode->weight = weight;
    newNode->next = NULL;
    strcpy(newNode->nutritionStatus,nutritionStatus);
    return newNode;
}

void printPatients(struct Patient* head) {
    if(head == NULL){
        printf("the list is empty");
    }
    struct Patient* temp = head;
    printf("\n");
    while (temp != NULL) {
        printf("%s;%s;%d/%d/%d;%.2f;%d;%s\n", temp->fName, temp->sName,temp->day,
               temp->month,temp->year,temp->height,temp->weight,temp->nutritionStatus);
        temp = temp->next;
    }

}

struct Patient* sortedInsert(struct Patient* head, struct Patient* newNode) {

    // case when you need to insert at head and if it is empty
    if (head == NULL || strcmp(newNode->fName, head->fName) < 0) {
        newNode->next = head;
        return newNode;
    }

    struct Patient* current = head;
    //find position -insertion sort
    while (current->next != NULL && strcmp(current->next->fName,newNode->fName) < 0) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;

    UpdateNutritionalStatus(head);
    return head;

}

void UpdateNutritionalStatus(struct Patient *head){
    struct Patient *temp = head;
    if(head == NULL){
        printf("There is no list");
        return;}
    float BMI;
    while(temp!=NULL){
        BMI = temp->weight/(temp->height*temp->height);
        temp->bmi = BMI;
        if(BMI<18.5){
            strcpy(temp->nutritionStatus,"Underweight");
        }
        else if(BMI<24.9)
            strcpy(temp->nutritionStatus,"Normal weight");
        else if(BMI<29.9)
            strcpy(temp->nutritionStatus,"Pre-obesity");
        else if(BMI<34.9)
            strcpy(temp->nutritionStatus,"Obese class I");
        else if(BMI<39.9)
            strcpy(temp->nutritionStatus,"Obese class II");
        else
            strcpy(temp->nutritionStatus,"Obese class III");

        temp = temp->next;
    }



}

