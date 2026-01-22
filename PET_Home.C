#include <stdio.h>
#include <string.h>

int selection =0;


typedef struct {
    int id;
    char date[9]; // in YYYYMMDD
    char category[30];
    float amount;
    char description[51];
} expense;

int login(int n){
    long int pass = 123456;
    if(n==pass) return 1;
    else return 0;
};

int getIndex(){
    FILE *fexp = fopen("Expenses/ExpenseRecord.txt", "r");
    int id =0;
    char date[9], cat[30], desc[51];
    float amount;

    if (fexp == NULL) return 1; //For intial ID = 1
    rewind(fexp);
    while (fscanf(fexp,"%d %s %s %f %[^\n]", &id, date, cat, &amount, desc)!= EOF) {
    }

    fclose(fexp);
    return id + 1 ;
}

void addExpense(){
    expense e;
    FILE *fexp = fopen("Expenses/ExpenseRecord.txt", "a+");
    FILE *fbackup = fopen("Expenses/Backup-ExpenseRecord.txt", "a+");
    if (fexp == NULL) { printf("Error opening the File!"); return;}
    if (fbackup == NULL) { printf("Error opening the File!"); return;}
    e.id = getIndex();
    printf("\nAssigned ID: %d\n", e.id);
    printf("Enter Date (YYYYMMDD): ");
    scanf("%s", e.date);
    printf("Enter Category: ");
    scanf("%s", e.category);
    printf("Enter Amount: ");
    scanf("%f", &e.amount);
    getchar(); // To create a buffer for \n expected post previous scanf. (To let just next fgets work)
    printf("Enter Description: ");
    fgets(e.description, 51, stdin);

    fprintf(fexp, "%d %s %s %f %s\n", e.id, e.date, e.category, e.amount, e.description);
    fprintf(fbackup, "%d %s %s %f %s\n", e.id, e.date, e.category, e.amount, e.description);
    
    fclose(fexp);
    fclose(fbackup);

    return;
}

void viewAllExpense(){
    FILE *fexp = fopen("Expenses/ExpenseRecord.txt", "r");
    if (fexp == NULL) { printf("Error opening the File!"); return;}
    char strID[5] = "ID", strDate[12] = "DATE", strCat[30] = "CATEGORY", strAmnt[16] = "AMOUNT", strDes[51] = "DECRIPTION";

    
    printf("\n|%5s|%-12s|%-30s|%-16s|%-51s|\n", strID, strDate, strCat, strAmnt, strDes);
    for(int i=0; i<sizeof(strID)+sizeof(strDate)+sizeof(strCat)+sizeof(strAmnt)+sizeof(strDes)+6; i++){ printf("-"); }
    printf("\n");

    expense e2;
    while (fscanf(fexp,"%d %s %s %f %[^\n]", &e2.id, e2.date, e2.category, &e2.amount, e2.description)!= EOF)
    {
        // fscanf(fexp,"%d %s %s %f %[^\n]", &e2.id, e2.date, e2.category, &e2.amount, e2.description);
        printf("|%5d| %.4s-%.2s-%.2s |%-30s|%16f|%-51s|\n", e2.id, e2.date, e2.date+4, e2.date+6, e2.category, e2.amount, e2.description);
    }
    printf("\n");
    fclose(fexp);
    return;
}

void viewExpenseCategory(){
    FILE *fexp = fopen("Expenses/ExpenseRecord.txt", "r");
    if (fexp == NULL) { printf("Error opening the File!"); return;}
    
    float total = 0 ;
    expense e3;
    char searchCat[30];
    printf("Enter the Category to be searched: ");
    getchar();
    fgets(searchCat, 30, stdin);
    searchCat[strcspn(searchCat, "\n")] = 0;
    
    char strID[5] = "ID", strDate[12] = "DATE", strCat[30] = "CATEGORY", strAmnt[16] = "AMOUNT", strDes[51] = "DECRIPTION";

    
    printf("\n|%5s|%-12s|%-30s|%-16s|%-51s|\n", strID, strDate, strCat, strAmnt, strDes);
    for(int i=0; i<sizeof(strID)+sizeof(strDate)+sizeof(strCat)+sizeof(strAmnt)+sizeof(strDes)+6; i++){ printf("-"); }
    printf("\n");

    while (fscanf(fexp,"%d %s %s %f %[^\n]", &e3.id, e3.date, e3.category, &e3.amount, e3.description)!= EOF){
        if (strcmp(searchCat, e3.category)==0){
            printf("|%5d| %.4s-%.2s-%.2s |%-30s|%16f|%-51s|\n", e3.id, e3.date, e3.date+4, e3.date+6, e3.category, e3.amount, e3.description);
            total = total + e3.amount;

        }
        
    }
    printf("Total Expenses for %s : %.2f", searchCat, total);

    fclose(fexp);
    return;
}

void totalExpense(){
    expense e4;
    float total = 0;
    FILE *fexp = fopen("Expenses/ExpenseRecord.txt", "r");
    if (fexp == NULL) { printf("Error opening the File!"); return;}

    while (fscanf(fexp,"%d %s %s %f %[^\n]", &e4.id, e4.date, e4.category, &e4.amount, e4.description)!= EOF){
        total = total + e4.amount;
    }
    
    printf("Your Total Expenditure is = %.2f", total);
    fclose(fexp);
    return;
}

void deleteExpense(){
    expense e5;
    FILE *fexp = fopen("Expenses/ExpenseRecord.txt", "r");
    FILE *ftemp = fopen("Expenses/Temp.txt", "w+");
    if (fexp == NULL) { printf("Error opening the File!"); return;}    
    if (ftemp == NULL) { printf("Error opening the File!"); return;}

    int n;
    printf("Choose the ID number to be deleted: ");
    scanf("%d", &n);

    for (int i =1;fscanf(fexp,"%d %s %s %f %[^\n]", &e5.id, e5.date, e5.category, &e5.amount, e5.description)!= EOF; i++){
        if (e5.id!=n)
        {
            fprintf(ftemp, "%d %s %s %f %s\n", e5.id, e5.date, e5.category, e5.amount, e5.description);
        }
    }
    fclose(fexp);
    fclose(ftemp);

    remove("Expenses/ExpenseRecord.txt");
    rename("Expenses/Temp.txt", "Expenses/ExpenseRecord.txt");

    return;
}


void homemenu(){
    while (selection!= 6)
    {       
        printf("\n\nChoose your objective:\t");
        printf("\n1. Add an Expense"); 
        printf("\n2. View all Expenses");
        printf("\n3. View Expense by Category");
        printf("\n4. View total Spending");
        printf("\n5. Delete any spending");
        printf("\n6. Exit");
        printf("\nYour Selection: ");
        scanf("%d", &selection);   
        
        switch(selection){
            case 1: addExpense(); break;
            case 2: viewAllExpense(); break;
            case 3: viewExpenseCategory(); break;
            case 4: totalExpense(); break;
            case 5: deleteExpense(); break;
            case 6: return;
            default: printf("Invalid Selection. Retry:"); break;
        }
        
    }
    return;
};


int main() {
    
    printf("\n\t\t\t~Welcome to Personal Expense Tracker~\t\t\t\n");
    
    int pass;
    printf("Enter your 6-digit PIN:");
    scanf("%d", &pass);
    
    if(login(pass)==1){
        printf("Password Verified!!\n");
        homemenu(); 
    }
    else printf("Login Failed!!!!\n");
    
    printf("\nPrograme Completed Sucessfully");
    return 0;
}
