#include "random.h"

void get_characters(char ** characters) {
    FILE * charfile;
    charfile = fopen("characters", "r");
    char temp[255];
    int i;
    for (i = 0; i < 133; i++) {
        fgets(temp, 255, charfile);
        char *pos;
        if ((pos=strchr(temp, '\n')) != NULL)
            *pos = '\0';
        char * str = malloc(strlen(temp)+1);
        strcpy(str, temp);
        characters[i] = str;
    }
    fclose(charfile);
}

int _random(int div) {
    int random;
    int fd = open("/dev/random", O_RDONLY);
    if (fd < 0) {
        printf("errno %d error: %s\n", errno, strerror(errno));
        return 1;
    }
    if (read(fd, &random, sizeof(int)) < 0) {
        printf("errno: %d error: %s\n", errno, strerror(errno));
        return 0;
    }
    close(fd);
    return abs(random) % div;
}

int get_random(char random_characters[16][20]) {
    char ** characters = malloc(sizeof(char * ) * 133);
    get_characters(characters);
    int random_ints[16];
    int i, j, x;
    for( i = 0; i < 16; i++ ) {
        x = _random(133);
        for( j = 0; j < i; j++) {
            while(x == random_ints[j]) {
                x = _random(133);
            }
        }
        random_ints[i] = x;
        strcpy(random_characters[i], characters[random_ints[i]]);
    }
    return 0;
}

int get_chosen(char * chosen, char characters[16][20]) {
    strcpy(chosen, characters[_random(16)]);
    return 0;
}