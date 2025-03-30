#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define PASSWORD "koXwXG"  // The hidden password
#define MAX_ATTEMPTS 5

// Simple hash function to simulate encryption
int encrypt_char(char c) {
    return (c + 3) * 2;  // Simple encoding technique (shift + multiply)
}

// Function to compare the encrypted password with a guess
int check_guess(char *guess) {
    int i, match_count = 0;
    for (i = 0; i < strlen(PASSWORD); i++) {
        if (encrypt_char(guess[i]) == encrypt_char(PASSWORD[i])) {
            match_count++;
        }
    }
    return match_count;
}

int main() {
    char guess[100];
    int attempts = 0;
    int match_count;

    printf("Welcome to the 'Guess the Password' game!\n");
    printf("You have %d attempts to guess the password.\n", MAX_ATTEMPTS);

    while (attempts < MAX_ATTEMPTS) {
        printf("Enter your guess: ");
        fgets(guess, sizeof(guess), stdin);
        guess[strcspn(guess, "\n")] = '\0';  // Remove newline character from input

        // Ensure guess only contains alphabets and digits
        int valid_input = 1;
        for (int i = 0; i < strlen(guess); i++) {
            if (!isalnum(guess[i])) {
                valid_input = 0;
                break;
            }
        }
        
        if (!valid_input) {
            printf("Invalid input. Please enter only alphabets and digits.\n");
            continue;
        }

        match_count = check_guess(guess);

        if (match_count == strlen(PASSWORD)) {
            printf("Congratulations! You guessed the password correctly: %s\n", guess);
            break;
        } else {
            printf("Your guess is close! %d character(s) match.\n", match_count);
            attempts++;
        }
        
        if (attempts == MAX_ATTEMPTS) {
            printf("Sorry, you've run out of attempts.\n");
        }
    }

    return 0;
}
