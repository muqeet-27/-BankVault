// .\banking-system.exe
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

#define MAX_ACCOUNTS 100  // Maximum number of accounts

// Define Account structure
struct Account {
    int accountNumber;
    char name[50];
    double balance;
    char aadhaar[12];  // Aadhaar number as part of the account details
};

// Declare an array of accounts
struct Account accounts[MAX_ACCOUNTS];
int accountCount = 0;  // Counter to keep track of number of accounts

// Function prototypes
void addAccount();
void viewAccount();
void updateAccount();
void deleteAccount();
void deposit();
void withdraw();
int findAccountIndex(int accountNumber);
int validateAadhaar(char *aadhaar);

// Main function
int main() {
    int choice;
    
    while (1) {
        // Display menu
        printf("\nBank Management System\n");
        printf("1. Add Account\n");
        printf("2. View Account\n");
        printf("3. Update Account\n");
        printf("4. Delete Account\n");
        printf("5. Deposit\n");
        printf("6. Withdraw\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addAccount();
                break;
            case 2:
                viewAccount();
                break;
            case 3:
                updateAccount();
                break;
            case 4:
                deleteAccount();
                break;
            case 5:
                deposit();
                break;
            case 6:
                withdraw();
                break;
            case 7:
                printf("Exiting the system...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

// Function to add a new account
void addAccount() {
    struct Account newAccount;
    
    printf("Enter account number: ");
    scanf("%d", &newAccount.accountNumber);
    
    // Check if account number already exists
    if (findAccountIndex(newAccount.accountNumber) != -1) {
        printf("Account with this number already exists!\n");
        return;
    }

    // Aadhaar number input with validation
    printf("Enter Aadhaar number (11 digits): ");
    scanf("%s", newAccount.aadhaar);
    if (validateAadhaar(newAccount.aadhaar) != 0) {
        printf("Invalid Aadhaar number. It should be exactly 11 digits.\n");
        return;
    }

    printf("Enter account holder name: ");
    getchar();  // Clear newline character left by scanf
    fgets(newAccount.name, sizeof(newAccount.name), stdin);
    newAccount.name[strcspn(newAccount.name, "\n")] = '\0';  // Remove newline at the end of string
    
    printf("Enter initial deposit: ");
    scanf("%lf", &newAccount.balance);
    
    // Add the new account to the accounts array
    accounts[accountCount++] = newAccount;
    printf("Account created successfully!\n");
}

// Function to view an account
void viewAccount() {
    int accountNumber;
    printf("Enter account number: ");
    scanf("%d", &accountNumber);
    
    int index = findAccountIndex(accountNumber);
    if (index != -1) {
        printf("Account Number: %d\n", accounts[index].accountNumber);
        printf("Account Holder: %s\n", accounts[index].name);
        printf("Aadhaar Number: %s\n", accounts[index].aadhaar);
        printf("Balance: %.2f\n", accounts[index].balance);
    } else {
        printf("Account not found!\n");
    }
}

// Function to update account information
void updateAccount() {
    int accountNumber;
    printf("Enter account number to update: ");
    scanf("%d", &accountNumber);
    
    int index = findAccountIndex(accountNumber);
    if (index != -1) {
        printf("Enter new name: ");
        getchar();  // Consume the newline character
        fgets(accounts[index].name, sizeof(accounts[index].name), stdin);
        accounts[index].name[strcspn(accounts[index].name, "\n")] = '\0';  // Remove newline
        
        printf("Enter new balance: ");
        scanf("%lf", &accounts[index].balance);
        
        printf("Account updated successfully!\n");
    } else {
        printf("Account not found!\n");
    }
}

// Function to delete an account
void deleteAccount() {
    int accountNumber;
    printf("Enter account number to delete: ");
    scanf("%d", &accountNumber);
    
    int index = findAccountIndex(accountNumber);
    if (index != -1) {
        // Shift the remaining accounts to remove the account from the array
        for (int i = index; i < accountCount - 1; i++) {
            accounts[i] = accounts[i + 1];
        }
        accountCount--;
        printf("Account deleted successfully!\n");
    } else {
        printf("Account not found!\n");
    }
}

// Function to deposit money into an account
void deposit() {
    int accountNumber;
    double amount;
    
    printf("Enter account number to deposit into: ");
    scanf("%d", &accountNumber);
    
    int index = findAccountIndex(accountNumber);
    if (index != -1) {
        printf("Enter amount to deposit: ");
        scanf("%lf", &amount);
        
        if (amount > 0) {
            accounts[index].balance += amount;
            printf("Deposited %.2f successfully!\n", amount);
        } else {
            printf("Invalid deposit amount!\n");
        }
    } else {
        printf("Account not found!\n");
    }
}

// Function to withdraw money from an account
void withdraw() {
    int accountNumber;
    double amount;
    
    printf("Enter account number to withdraw from: ");
    scanf("%d", &accountNumber);
    
    int index = findAccountIndex(accountNumber);
    if (index != -1) {
        printf("Enter amount to withdraw: ");
        scanf("%lf", &amount);
        
        if (amount > 0 && accounts[index].balance >= amount) {
            accounts[index].balance -= amount;
            printf("Withdrew %.2f successfully!\n", amount);
        } else {
            printf("Insufficient funds or invalid amount!\n");
        }
    } else {
        printf("Account not found!\n");
    }
}

// Function to find the index of an account by its account number
int findAccountIndex(int accountNumber) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            return i;
        }
    }
    return -1;  // Account not found
}

// Function to validate Aadhaar number
int validateAadhaar(char *aadhaar) {
    // Ensure Aadhaar is exactly 11 digits
    if (strlen(aadhaar) != 11) {
        return -1;
    }
    // Check if all characters are digits
    for (int i = 0; i < 11; i++) {
        if (aadhaar[i] < '0' || aadhaar[i] > '9') {
            return -1;
        }
    }
    return 0;
}
