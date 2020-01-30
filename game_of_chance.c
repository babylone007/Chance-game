#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include "hacking.h"

#define DATAFILE "/var/chance.data"         // File to store user data

// Custom user struct to store information about users
struct user {
    int uid;
    int credits;
    int highscore;
    char name[100];
    int (*current_game) ();
};

// Function prototypes
int get_player_data();
void register_new_player();
void update_player_data();
void show_highscore();
void jackpot();
void input_name();
void print_cards(char *, char *, int *);
int take_wager(int, int);
void play_the_game();
int pick_a_number();
int dealer_no_match();
int find_the_ace();
// void fatal(char *); // Already declared in "hacking.h"

// Global variable
struct user player;

int main(){
    int choice, last_game;

    srand(time(0));     // Seed the randomizer with the current time;

    if (get_player_data() == -1)     // Try to read player data from file.
        register_new_player();      // If there is no data, register new player.

    while (choice != 7) {
        printf("-=[ Game of chance Menu ]=-\n");
        printf("1 - Play the Pick a Number game\n");
        printf("2 - Play the No Match Dealer game \n");
        printf("3 - Play the Find the Ace game\n");
        printf("4 - View current high score\n");
        printf("5 - Change your user name\n");
        printf("6 - Reset your account at 100 credits\n");
        printf("7 - Exit\n");
        printf("[Name: %s]\n", player.name);
        scanf("%d\n", &choice);     // Scanf expect all it's arguments to be poiters.

        if ((choice < 1) || (choice > 7))
            printf("\n[!!] The number %d is an invalid selection.\n\n", choice);
        else if (choice < 4){
            if (choice != last_game){       // If the function ptr is n't set
                if (choice == 1) player.current_game = pick_a_number;
                else if (choice == 2) player.current_game = dealer_no_match;
                else player.current_game = find_the_ace;
                last_game = choice;
            }
            play_the_game();
        }
        else if (choice == 4) show_highscore();
        else if (choice == 5){
            printf("\nChange user name\n");
            printf("Enter your new name: \n");
            input_name();
            printf("Your name has been change.\n\n");
        }
        else if(choice = 6){
            printf("\nYour account has been reset with 100 credits.\n\n");
            player.credits = 100;
        }
        }
        update_player_data();
        printf("\nThanks for playing!\n");
}


// This function reads the player data for the current UID from the file.
// It returns -1 if it's unable to find player data for the current UID.
// player UID
int get_player_data(){
    int fd, uid, read_bytes;
    struct user entry;
    uid = getuid();

    fd = open(DATAFILE, O_RDONLY);
    if(fd == -1) return -1;     // Can't open the file, maybe it doesn't exist
    read_bytes = read(fd, &entry, sizeof(struct user));     // Read the first chunk
    while((entry.uid != uid) && (read_bytes > 0)){          // Loop until proper uid is found
        read_bytes = read(fd, &entry, sizeof(struct user)); // Keep reading
    }
    close(fd);  // Close the file
    if (read_bytes > siseof(struct user)) return -1; // This means that the end of the file is reached.
    else player = entry;    // Copy the read data into the player struct.
    return 1;
}

// This is the new user registration function.
// It will create a new player account adn append it to the file.
void register_new_player(){
    int fd;
    printf("-=-={ New Player Registration }=-=-\n");
    printf("Enter your name: ");
    input_name();

    player.uid = getuid();
    player.highscore = player.credits = 100;

    fd = open(DATAFILE, O_WRONLY|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR);
    if(fd == -1) fatal("in register_new_player() while opening a new file.");
    write(fd, &player, sizeof(struct player));
    close(fd);

    printf("\nWelcom to the Game of Chance %s\n", player.name);
    printf("You have been given %u credits.\n", Player.credits);
}


// This function write the current player data to the end of the file.
// It's used primarily for updating the credits after game.
void update_player_data(){
    int fd, i, read_uid;
    char burned_byte;

    fd = open(fd, O_RDRW);
    if(fd == -1) fatal("in update_player_data() while opening file.")
    read(fd, &read_uid, 4);     //Read the uid from the first struct.
    while (read_uid != player.uid) {    // Loop until the correct uid is found.
        for (i=0; i < sizeof(struct user) - 4; i++){    // Read through the rest
            read(fd, &burned_byte, 1);                  // of that struct.
        }
        read(fd, &read_uid, 4);     // Read the uid from the next struct.
    }
    write(fd, &(player.credits), 4);
    write(fd, &(player.highscore), 4);
    write(fd, &(player.name), 100);
    close(fd);

}

// This function will display the current high score and the name of the person
// who set that high score.
void show_highscore(){
    unsigned int top_score = 0;
    char top_name[100];
    struct user entry;
    int fd;

    printf("\n======================| High Score |======================|\n", );
    fd = open(DATAFILE, O_RDONLY);
    if (fd == -1) fatal("in show_highscore() while opening file.");
    while () {
        /* code */
    }
}
