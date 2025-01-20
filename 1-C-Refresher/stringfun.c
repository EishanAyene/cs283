#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define BUFFER_SZ 50

//prototypes
void usage(char *);
void print_buff(char *, int);
int  setup_buff(char *, char *, int);

//prototypes for functions to handle required functionality
int  count_words(char *, int, int);
//add additional prototypes here
void reverse_string(char *, int);
void print_words(char *, int,int);
void replace_string(char *, int, char *, char *);

int setup_buff(char *buff, char *user_str, int len){
    char *src = user_str;
    char *dest = buff;
    int count = 0;
    int space = 0;

    while (*src && count < len) {
        if (*src == ' ' || *src == '\t') {
            if (!space && count > 0) {
                *dest = ' ';
                dest++;
                count++;
                space = 1;
            }
        } else {
            *dest = *src;
            dest++;
            count++;
            space = 0;
        }
        src++;
    }

    if (count > 0 && *(dest - 1) == ' ') {
        dest--;
        count--;
    }
    while (count < len) {
        *dest = '.';
        dest++;
        count++;
    }
    if (*src) {
        return -1;
    } else {
       return count;
    }
}


void print_buff(char *buff, int len){
    printf("Buffer:  [");
    for (int i=0; i<len; i++){
        putchar(*(buff+i));
    }
    printf("]\n");
}

void usage(char *exename){
    printf("usage: %s [-h|c|r|w|x] \"string\" [other args]\n", exename);

}

int count_words(char *buff, int len, int str_len){
    int word_count = 0;
    int in_word = 0;
    char *ptr = buff;

    while (ptr < buff + str_len) {
       if (*ptr != ' ' && *ptr != '.') {
          if (!in_word) {
              word_count++;
              in_word = 1;
          }
        }else{
          in_word = 0;
        }
        ptr++;
    }

    return word_count;
}

//ADD OTHER HELPER FUNCTIONS HERE FOR OTHER REQUIRED PROGRAM OPTIONS

// Reverse string function
void reverse_string(char *buff, int str_len) {
    char *start = buff;
    char *end = buff + str_len - 1;

    while (end > start && *end == '.') {
        end--;
    }
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

// Print words function
void print_words(char *buff, int len, int str_len) {
    printf("Word Print\n----------\n");

    int word_index = 1, char_count = 0, word_count = 0;
    char *ptr = buff;

    while (ptr < buff + str_len) {
        if (*ptr != ' ' && *ptr != '.') {
            if (char_count == 0) {
                word_count++;
                printf("%d. ", word_index++);
            }
            putchar(*ptr);
            char_count++;
        } else if (char_count > 0) {
            printf("(%d)\n", char_count);
            char_count = 0;
        }
        ptr++;
    }

    if (char_count > 0) {
        printf("(%d)\n", char_count);
    }

    printf("\nNumber of words returned: %d\n", word_count);
}


// Replace string function
void replace_string(char *buff, int str_len, char *find, char *replace) {
    char temp[BUFFER_SZ];
    char *src = buff;
    char *dest = temp;
    char *f = find;
    char *r = replace;
    int find_len = 0;
    int replace_len = 0;
    int replaced = 0;
    int found = 0;

    while (*f++) {
        find_len++;
    }

    while (*r++) {
        replace_len++;
    }

    while (*src && (dest - temp) < BUFFER_SZ) {
        char *s = src;
        char *f_check = find;
        found = 1;

        while (*f_check) {
            if (*s == '\0' || *s != *f_check) {
                found = 0;
                break;
            }
            s++;
            f_check++;
        }

        if (!replaced && found) {
            r = replace;
            while (*r && (dest - temp) < BUFFER_SZ) {
                *dest++ = *r++;
            }
            src += find_len;
            replaced = 1;
        } else {
            *dest++ = *src++;
        }
    }

    if (!replaced) {
        printf("Not Implemented!\n");
        exit(1);
    }

    while ((dest - temp) < BUFFER_SZ) {
        *dest++ = '.';
    }
    dest = temp;
    char *b = buff;
    while ((b - buff) < BUFFER_SZ) {
        if ((dest - temp) < BUFFER_SZ) {
            *b = *dest++;
        } else {
            *b = '.';
        }
        b++;
    }
}


int main(int argc, char *argv[]){

    char *buff;             //placehoder for the internal buffer
    char *input_string;     //holds the string provided by the user on cmd line
    char opt;               //used to capture user option from cmd line
    int  rc;                //used for return codes
    int  user_str_len;      //length of user supplied string

    //TODO:  #1. WHY IS THIS SAFE, aka what if arv[1] does not exist?
    //      PLACE A COMMENT BLOCK HERE EXPLAINING
    //It is safe since we have a check to ensure that theres
    //a valid argument and if there is not, the program quits.
    if ((argc < 2) || (*argv[1] != '-')){
        usage(argv[0]);
        exit(1);
    }

    opt = (char)*(argv[1]+1);   //get the option flag

    //handle the help flag and then exit normally
    if (opt == 'h'){
        usage(argv[0]);
        exit(0);
    }

    //WE NOW WILL HANDLE THE REQUIRED OPERATIONS

    //TODO:  #2 Document the purpose of the if statement below
    //      PLACE A COMMENT BLOCK HERE EXPLAINING
    //The purpose of the if statement is to make sure that
    // the user provides the number of arguments that are needed
    if (argc < 3){
        usage(argv[0]);
        exit(1);
    }

    input_string = argv[2]; //capture the user input string

    //TODO:  #3 Allocate space for the buffer using malloc and
    //          handle error if malloc fails by exiting with a 
    //          return code of 99
    // CODE GOES HERE FOR #3

    buff = (char *)malloc(BUFFER_SZ);
    if (!buff) {
        exit(99);
    }


    user_str_len = setup_buff(buff, input_string, BUFFER_SZ);     //see todos
    if (user_str_len < 0){
        printf("Error setting up buffer, error = %d", user_str_len);
        exit(2);
    }

    switch (opt){
        case 'c':
            rc = count_words(buff, BUFFER_SZ, user_str_len);  //you need to implement
            if (rc < 0){
                printf("Error counting words, rc = %d", rc);
                exit(2);
            }
            printf("Word Count: %d\n", rc);
            break;


        //TODO:  #5 Implement the other cases for 'r' and 'w' by extending
        //       the case statement options


        case 'r': {
            reverse_string(buff, user_str_len);
            break;
        }
        case 'w': {
            print_words(buff, BUFFER_SZ, user_str_len);
            break;
        }
        case 'x': {
            if (argc < 5) {
                free(buff);
                exit(1);
            }
            replace_string(buff, user_str_len, argv[3], argv[4]);
            break;
        }

        default:
            usage(argv[0]);
            exit(1);
    }

    //TODO:  #6 Dont forget to free your buffer before exiting
    print_buff(buff,BUFFER_SZ);
    free(buff);
    exit(0);
}

//TODO:  #7  Notice all of the helper functions provided in the
//          starter take both the buffer as well as the length.  Why
//          do you think providing both the pointer and the length
//          is a good practice, after all we know from main() that
//          the buff variable will have exactly 50 bytes?
//
//          PLACE YOUR ANSWER HERE
// It is good practice since it makes functions reusable for other code and
// it makes it easier to do future changes as well. We never know if we may
//need to change the buffer or the length so this makes it easier for the future.
