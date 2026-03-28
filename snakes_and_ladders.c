#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 100
#define NUM_PLAYERS 4

// Structure to store player information
typedef struct {
    int position;
    int total_moves;
    int dice_rolls;
    int win_rank;
} Player;

// Function prototypes
int rollDice();
void initializeSnakesAndLadders(int board[]);
void displayBoard(Player players[], int snakes_ladders[]);
void movePlayer(Player *player, int dice_value, int snakes_ladders[]);
void displayStats(Player players[], int turns);
int checkWinner(Player players[]);

int main() {
    Player players[NUM_PLAYERS];
    int snakes_ladders[BOARD_SIZE + 1];
    int current_player = 0;
    int dice_value;
    int winner_count = 0;
    int ranks[NUM_PLAYERS];
    char input;
    int turn = 0;

    srand(time(0));

    // Initialize players
    printf("================================\n");
    printf("  SNAKE AND LADDER GAME (4P)   \n");
    printf("================================\n\n");

    for (int i = 0; i < NUM_PLAYERS; i++) {
        players[i].position = 0;
        players[i].total_moves = 0;
        players[i].dice_rolls = 0;
        players[i].win_rank = -1;
    }

    // Initialize snakes and ladders on the board
    initializeSnakesAndLadders(snakes_ladders);

    printf("Game Setup:\n");
    printf("-----------\n");
    printf("Board Size: 1-100\n");
    printf("Number of Players: 4\n");
    printf("Objective: First player to reach 100 wins!\n\n");

    // Main game loop
    while (winner_count < NUM_PLAYERS) {
        printf("================================\n");
        printf("Turn %d - Player %d's Turn\n", turn + 1, current_player + 1);
        printf("================================\n");

        displayBoard(players, snakes_ladders);

        // Check if player has already won
        if (players[current_player].win_rank != -1) {
            printf("\nPlayer %d has already finished at rank %d!\n", 
                   current_player + 1, players[current_player].win_rank);
            current_player = (current_player + 1) % NUM_PLAYERS;
            turn++;
            continue;
        }

        printf("\nPlayer %d (Position: %d)\n", current_player + 1, players[current_player].position);
        printf("Press 'r' to roll the dice or 'q' to quit: ");
        scanf(" %c", &input);

        if (input == 'q' || input == 'Q') {
            printf("\nGame Interrupted! Final Statistics:\n");
            displayStats(players, turn);
            break;
        }

        if (input == 'r' || input == 'R') {
            dice_value = rollDice();
            printf("🎲 Dice rolled: %d\n", dice_value);

            players[current_player].dice_rolls++;

            // Calculate new position
            int new_position = players[current_player].position + dice_value;

            if (new_position <= BOARD_SIZE) {
                movePlayer(&players[current_player], dice_value, snakes_ladders);
                players[current_player].total_moves++;

                printf("Player %d moves to position: %d\n", 
                       current_player + 1, players[current_player].position);

                // Check if landed on snake or ladder
                if (snakes_ladders[players[current_player].position] != players[current_player].position) {
                    if (snakes_ladders[players[current_player].position] > players[current_player].position) {
                        printf("🪜 Ladder! Climbed to position %d\n", 
                               snakes_ladders[players[current_player].position]);
                    } else {
                        printf("🐍 Snake! Fell to position %d\n", 
                               snakes_ladders[players[current_player].position]);
                    }
                }

                // Check for winner
                if (checkWinner(players) == current_player) {
                    winner_count++;
                    players[current_player].win_rank = winner_count;
                    printf("\n✨🎉 Player %d WINS! (Rank %d)\n", 
                           current_player + 1, winner_count);
                }
            } else {
                printf("❌ Cannot move! You need %d to reach exactly 100.\n", 
                       BOARD_SIZE - players[current_player].position);
                players[current_player].total_moves++;
            }
        }

        printf("\n");
        current_player = (current_player + 1) % NUM_PLAYERS;
        turn++;
    }

    // Display final statistics
    printf("\n================================\n");
    printf("        GAME FINISHED!         \n");
    printf("================================\n");
    displayStats(players, turn);

    return 0;
}

// Roll a six-sided dice
int rollDice() {
    return (rand() % 6) + 1;
}

// Initialize snakes and ladders on the board
void initializeSnakesAndLadders(int board[]) {
    // Initialize board (each position points to itself initially)
    for (int i = 0; i <= BOARD_SIZE; i++) {
        board[i] = i;
    }

    // Snakes (destination < source)
    board[16] = 6;      // Snake at 16 -> 6
    board[47] = 26;     // Snake at 47 -> 26
    board[56] = 53;     // Snake at 56 -> 53
    board[62] = 19;     // Snake at 62 -> 19
    board[87] = 36;     // Snake at 87 -> 36
    board[93] = 73;     // Snake at 93 -> 73
    board[95] = 75;     // Snake at 95 -> 75
    board[98] = 79;     // Snake at 98 -> 79

    // Ladders (destination > source)
    board[1] = 38;      // Ladder at 1 -> 38
    board[4] = 14;      // Ladder at 4 -> 14
    board[9] = 31;      // Ladder at 9 -> 31
    board[21] = 42;     // Ladder at 21 -> 42
    board[28] = 84;     // Ladder at 28 -> 84
    board[51] = 67;     // Ladder at 51 -> 67
    board[72] = 91;     // Ladder at 72 -> 91
    board[80] = 99;     // Ladder at 80 -> 99
}

// Move player and handle snakes/ladders
void movePlayer(Player *player, int dice_value, int snakes_ladders[]) {
    player->position += dice_value;

    if (player->position > BOARD_SIZE) {
        player->position -= dice_value;
    } else if (snakes_ladders[player->position] != player->position) {
        player->position = snakes_ladders[player->position];
    }
}

// Check if a player has won (reached 100)
int checkWinner(Player players[]) {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        if (players[i].position == BOARD_SIZE) {
            return i;
        }
    }
    return -1;
}

// Display current board state
void displayBoard(Player players[], int snakes_ladders[]) {
    printf("\n--- Current Positions ---\n");
    for (int i = 0; i < NUM_PLAYERS; i++) {
        if (players[i].win_rank == -1) {
            printf("Player %d: Position %3d ", i + 1, players[i].position);
        } else {
            printf("Player %d: ✓ FINISHED (Rank %d) ", i + 1, players[i].win_rank);
        }
        printf("| Total Moves: %d | Dice Rolls: %d\n", 
               players[i].total_moves, players[i].dice_rolls);
    }
}

// Display game statistics
void displayStats(Player players[], int total_turns) {
    printf("\n========== FINAL STATISTICS ==========\n");
    printf("Total Turns Played: %d\n\n", total_turns);

    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("--- Player %d ---\n", i + 1);
        printf("  Final Position:  %d/100\n", players[i].position);
        printf("  Total Moves:     %d\n", players[i].total_moves);
        printf("  Dice Rolls:      %d\n", players[i].dice_rolls);
        if (players[i].win_rank != -1) {
            printf("  Rank:            %d (WINNER!)\n", players[i].win_rank);
        }
        printf("\n");
    }
    printf("======================================\n");
}
