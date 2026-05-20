#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Expense {
    char date[20];
    char category[30];
    char description[50];
    float amount;
};

void addExpense();
void viewExpenses();
void searchCategory();
void totalExpense();

FILE *fp;

int main() {
    int choice;

    while (1) {
        printf("\n====== SMART EXPENSE TRACKER ======\n");
        printf("1. Add Expense\n");
        printf("2. View Expenses\n");
        printf("3. Search by Category\n");
        printf("4. Calculate Total Expense\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addExpense();
                break;

            case 2:
                viewExpenses();
                break;

            case 3:
                searchCategory();
                break;

            case 4:
                totalExpense();
                break;

            case 5:
                printf("Exiting Program...\n");
                exit(0);

            default:
                printf("Invalid Choice!\n");
        }
    }

    return 0;
}

void addExpense() {
    struct Expense e;

    fp = fopen("expenses.txt", "a");

    if (fp == NULL) {
        printf("File cannot be opened!\n");
        return;
    }

    printf("\nEnter Date (DD/MM/YYYY): ");
    scanf("%s", e.date);

    printf("Enter Category: ");
    scanf("%s", e.category);

    printf("Enter Description: ");
    scanf("%s", e.description);

    printf("Enter Amount: ");
    scanf("%f", &e.amount);

    fprintf(fp, "%s %s %s %.2f\n",
            e.date,
            e.category,
            e.description,
            e.amount);

    fclose(fp);

    printf("Expense Added Successfully!\n");
}

void viewExpenses() {
    struct Expense e;

    fp = fopen("expenses.txt", "r");

    if (fp == NULL) {
        printf("No expense records found!\n");
        return;
    }

    printf("\n====== EXPENSE LIST ======\n");

    printf("%-15s %-15s %-20s %-10s\n",
           "Date",
           "Category",
           "Description",
           "Amount");

    while (fscanf(fp, "%s %s %s %f",
                  e.date,
                  e.category,
                  e.description,
                  &e.amount) != EOF) {

        printf("%-15s %-15s %-20s %.2f\n",
               e.date,
               e.category,
               e.description,
               e.amount);
    }

    fclose(fp);
}

void searchCategory() {
    struct Expense e;
    char search[30];
    int found = 0;

    fp = fopen("expenses.txt", "r");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("Enter Category to Search: ");
    scanf("%s", search);

    printf("\nMatching Expenses:\n");

    while (fscanf(fp, "%s %s %s %f",
                  e.date,
                  e.category,
                  e.description,
                  &e.amount) != EOF) {

        if (strcmp(search, e.category) == 0) {

            printf("%s %s %s %.2f\n",
                   e.date,
                   e.category,
                   e.description,
                   e.amount);

            found = 1;
        }
    }

    if (!found) {
        printf("No expenses found in this category.\n");
    }

    fclose(fp);
}

void totalExpense() {
    struct Expense e;
    float total = 0;

    fp = fopen("expenses.txt", "r");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    while (fscanf(fp, "%s %s %s %f",
                  e.date,
                  e.category,
                  e.description,
                  &e.amount) != EOF) {

        total += e.amount;
    }

    printf("\nTotal Expense = %.2f\n", total);

    fclose(fp);
}
