#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void swap(int index_1, int index_2);
int partition(int low, int high);
void quick_sort(int low, int high);
bool check_cycle(int loser, int winner);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = candidate_count; i >= 0; i--)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;
    for (int i = candidate_count; i >= 0; i--)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    quick_sort(0, pair_count - 1);
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
        if (check_cycle(pairs[i].loser, pairs[i].winner) == true)
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    bool is_winner;
    for (int j = 0; j < candidate_count; j++)
    {
        is_winner = true;
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][j] == true)
            {
                is_winner = false;
                break;
            }
        }
        if (is_winner == true)
        {
            printf("%s\n", candidates[j]);
            return;
        }
    }
    return;
}

// Swap the places of the pairs array at the two indices
void swap(int index_1, int index_2)
{
    pair first = pairs[index_1];
    pairs[index_1] = pairs[index_2];
    pairs[index_2] = first;
}

// Splits the array of the pairs. This allows the quick sort to split based on the pivot
int partition(int low, int high)
{
    pair pivot = pairs[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (preferences[pairs[j].winner][pairs[j].loser] > preferences[pivot.winner][pivot.loser])
        {
            i++;mkdir pset4
            swap(i, j);
        }
    }
    swap(i + 1, high);
    return (i + 1);
}

// Quick sort the pairs
void quick_sort(int low, int high)
{
    if (low < high)
    {
        int pi = partition(low, high);
        quick_sort(low, pi - 1);
        quick_sort(pi + 1, high);
    }
}

// Check if the loser leads into a cycle. Returns true if it is a cycle and returns false if not a cycle
bool check_cycle(int loser, int winner)
{
    if (loser == winner)
    {
        return true; //if it the original winner is now the loser, it is a cycle
    }
    for (int i = 0; i < pair_count; i++)
    {
        if (locked[loser][i] && check_cycle(i, winner))
        {
            return true;
        }
    }
    return false;
}