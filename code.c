#include <stdio.h>
#include <string.h>

struct User {
    char name[100];
    int account_number;
    float balance;
    int pin;
};

void checkBalance(struct User user);
void withdrawMoney(struct User *user);
void depositMoney(struct User *user);
void transferMoney(struct User *user, struct User *recipient);
void changePIN(struct User *user);
void transactionReceipt(struct User user, char *transactionType, float amount);


int main() {
    struct User user = {"John Doe", 906804403, 1000.00, 2117};
    struct User recipient = {"hassain", 987654321, 500.00, 4321};
    
    int option, enteredPIN, attempts = 0;
    
    
    do {
        printf("Enter your 4-digit PIN: ");
        scanf("%d", &enteredPIN);
        
        if (enteredPIN != user.pin) {
            printf("Incorrect PIN. Please try again.\n");
            attempts++;
        }
        
        if (attempts == 3) {
            printf("Too many incorrect attempts. Exiting...\n");
            return 1;
        }
    } while (enteredPIN != user.pin);
    
    do {
        printf("\n--- ATM MENU ---\n");
        printf("1. Check Balance\n");
        printf("2. Withdraw Money\n");
        printf("3. Deposit Money\n");
        printf("4. Transfer Money\n");
        printf("5. Change PIN\n");
        printf("6. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &option);
        
        switch(option) {
            case 1:
                checkBalance(user);
                break;
            case 2:
                withdrawMoney(&user);
                break;
            case 3:
                depositMoney(&user);
                break;
            case 4:
                transferMoney(&user, &recipient);
                break;
            case 5:
                changePIN(&user);
                break;
            case 6:
                printf("Thank you for using the ATM. Goodbye!\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (option != 6);
    
    return 0;
}


void checkBalance(struct User user) {
    printf("\nYour current balance is: $%.2f\n", user.balance);
}


void withdrawMoney(struct User *user) {
    float amount;
    printf("\nEnter the amount to withdraw: ");
    scanf("%f", &amount);
    
    if (amount > user->balance) {
        printf("Insufficient balance!\n");
    } else {
        user->balance -= amount;
        printf("Please collect your cash.\n");
        transactionReceipt(*user, "Withdrawal", amount);
    }
}


void depositMoney(struct User *user) {
    float amount;
    printf("\nEnter the amount to deposit: ");
    scanf("%f", &amount);
    
    user->balance += amount;
    printf("Deposit successful.\n");
    transactionReceipt(*user, "Deposit", amount);
}


void transferMoney(struct User *user, struct User *recipient) {
    float amount;
    printf("\nEnter the amount to transfer: ");
    scanf("%f", &amount);
    
    if (amount > user->balance) {
        printf("Insufficient balance!\n");
    } else {
        user->balance -= amount;
        recipient->balance += amount;
        printf("Transfer successful to %s.\n", recipient->name);
        transactionReceipt(*user, "Transfer", amount);
    }
}


void changePIN(struct User *user) {
    int newPIN, confirmPIN;
    printf("\nEnter your new 4-digit PIN: ");
    scanf("%d", &newPIN);
    
    printf("Confirm your new 4-digit PIN: ");
    scanf("%d", &confirmPIN);
    
    if (newPIN == confirmPIN) {
        user->pin = newPIN;
        printf("PIN successfully changed.\n");
    } else {
        printf("PINs do not match. Please try again.\n");
    }
}

void transactionReceipt(struct User user, char *transactionType, float amount) {
    printf("\n--- TRANSACTION RECEIPT ---\n");
    printf("Transaction: %s\n", transactionType);
    printf("Amount: $%.2f\n", amount);
    printf("Account Number: %d\n", user.account_number);
    printf("Remaining Balance: $%.2f\n", user.balance);
    printf("---------------------------\n");
}









