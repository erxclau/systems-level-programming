#include "networking.h"
#include "random.h"

int main(int argc, char **argv) {

    int client_0;
    char buffer[BUFFER_SIZE];

    struct response {
        int type; // 0 is question, 1 is guess, 2 is answer, 3 is done, 4 is gameover
        char content[256];
    };

    int prev_turn = 0;
    int client_turn = 0;

    if (argc == 2) {

        char buffer[BUFFER_SIZE];

        int listen_socket;
        listen_socket = client_listen();

        printf("Waiting for player...\n");

        int client_1 = client_accept(listen_socket);

        printf("Player connected!\n");

        char characters[6][20] = {"x","y","z","a","b","c"};
        char chosen[20]; 
        strcpy(chosen, characters[2]);
        write(client_1, &characters, sizeof(characters));
        printf("Your character is: %s\n", chosen);

        printf("Ask a question: ");
        struct response res;
        res.type = 0;
        fgets(res.content, sizeof(res.content), stdin);
        *strchr(res.content, '\n') = 0;
        write(client_1, &res, sizeof(res));

        while(1) {
            struct response res;
            read(client_1, &res, sizeof(res));
            
            // checking res type
            // res = question
            if (res.type == 0) {
                printf("You were asked: %s\n", res.content);
                printf("Your answer: ");
                res.type = 2;
                fgets(res.content, sizeof(res.content), stdin);
                *strchr(res.content, '\n') = 0;
            }
            // res = guess
            else if (res.type == 1) {
                printf("Your opponent guessed: %s\n", res.content);
                if (strcmp(res.content, chosen) == 0) {
                    printf("HAHAHAHAH U TRASH U LOST\n");
                    res.type = 4;
                    strcpy(res.content, "Game Over");
                    write(client_1, &res, sizeof(res));
                    exit(0);
                } 
                else {
                    printf("The guess was incorrect\n");
                }
                printf("Ask a question or type g to guess: ");
                char input[256];
                fgets(input, sizeof(input), stdin);
                *strchr(input, '\n') = 0;
                if (strcmp(input, "g") == 0) {
                    printf("Make a guess: ");
                    res.type = 1;
                    fgets(res.content, sizeof(res.content), stdin);
                    *strchr(res.content, '\n') = 0;
                }
                else {
                    res.type = 0;
                    strcpy(res.content, input);
                }
            }
            // res = answer
            else if (res.type == 2) {
                printf("Your opponent answered: %s\n", res.content);
                printf("Enter characters name to flip or type done when finished: ");
                char currflip[20];
                fgets(currflip, sizeof(currflip), stdin);
                *strchr(currflip, '\n') = 0;
                while (strcmp(currflip, "done") != 0) {
                    //modify board
                    printf("You flipped: %s\n", currflip);
                    printf("Enter another characters name to flip or type done when finished: ");
                    fgets(currflip, sizeof(currflip), stdin);
                    *strchr(currflip, '\n') = 0;
                }
                res.type = 3;
                strcpy(res.content, "flipping done");
            }
            // res = done
            else if (res.type == 3) {
                printf("Ask a question or type g to guess: ");
                char input[256];
                fgets(input, sizeof(input), stdin);
                *strchr(input, '\n') = 0;
                if (strcmp(input, "g") == 0) {
                    printf("Make a guess: ");
                    res.type = 1;
                    fgets(res.content, sizeof(res.content), stdin);
                    *strchr(res.content, '\n') = 0;
                }
                else {
                    res.type = 0;
                    strcpy(res.content, input);
                }
            }
            // res = gameover
            else if (res.type == 4) {
                printf("Congratulations u are slightly less trash than other guy\n");
                exit(0);
            }
            write(client_1, &res, sizeof(res));
        }
    }
    else {
        client_0 = client_connect( TEST_IP );

        printf("You have successfuly connected!\n");
        
        char characters[6][20];
        read(client_0, &characters, sizeof(characters));
        char chosen[20];
        strcpy(chosen, characters[3]);
        printf("Your character is: %s\n", chosen);

        while(1) {
            struct response res;
            read(client_0, &res, sizeof(res));
            
            // checking res type
            // res = question
            if (res.type == 0) {
                printf("You were asked: %s\n", res.content);
                printf("Your answer: ");
                res.type = 2;
                fgets(res.content, sizeof(res.content), stdin);
                *strchr(res.content, '\n') = 0;
            }
            // res = guess
            else if (res.type == 1) {
                printf("Your opponent guessed: %s\n", res.content);
                if (strcmp(res.content, chosen) == 0) {
                    printf("HAHAHAHAH U TRASH U LOST\n");
                    res.type = 4;
                    strcpy(res.content, "Game Over");
                    write(client_0, &res, sizeof(res));
                    exit(0);
                } 
                else {
                    printf("The guess was incorrect\n");
                }
                printf("Ask a question or type g to guess: ");
                char input[256];
                fgets(input, sizeof(input), stdin);
                *strchr(input, '\n') = 0;
                if (strcmp(input, "g") == 0) {
                    printf("Make a guess: ");
                    res.type = 1;
                    fgets(res.content, sizeof(res.content), stdin);
                    *strchr(res.content, '\n') = 0;
                }
                else {
                    res.type = 0;
                    strcpy(res.content, input);
                }
            }
            // res = answer
            else if (res.type == 2) {
                printf("Your opponent answered: %s\n", res.content);
                printf("Enter characters name to flip or type done when finished: ");
                char currflip[20];
                fgets(currflip, sizeof(currflip), stdin);
                *strchr(currflip, '\n') = 0;
                while (strcmp(currflip, "done") != 0) {
                    //modify board
                    printf("You flipped: %s\n", currflip);
                    printf("Enter another characters name to flip or type done when finished: ");
                    fgets(currflip, sizeof(currflip), stdin);
                    *strchr(currflip, '\n') = 0;
                }
                res.type = 3;
                strcpy(res.content, "flipping done");
            }
            // res = done
            else if (res.type == 3) {
                printf("Ask a question or type g to guess: ");
                char input[256];
                fgets(input, sizeof(input), stdin);
                *strchr(input, '\n') = 0;
                if (strcmp(input, "g") == 0) {
                    printf("Make a guess: ");
                    res.type = 1;
                    fgets(res.content, sizeof(res.content), stdin);
                    *strchr(res.content, '\n') = 0;
                }
                else {
                    res.type = 0;
                    strcpy(res.content, input);
                }
            }
            // res = gameover
            else if (res.type == 4) {
                printf("Congratulations u are slightly less trash than other guy\n");
                exit(0);
            }
            write(client_0, &res, sizeof(res));
        }
    }
}
