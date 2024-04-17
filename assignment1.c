
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* struct for movie information */
struct movie
{
    char *title;
    char *year;
    char *languages;
    char *rating;
    struct movie *next;
};

/* Parse the current line which is space delimited and create a
*  movie struct with the data in this line
*/
struct movie *createMovie(char *currLine)
{
    struct movie *currMovie = malloc(sizeof(struct movie));

    // For use with strtok_r
    char *saveptr;

    // The first token is the ONID
    char *token = strtok_r(currLine, ",", &saveptr);
    currMovie->title = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->title, token);

    // The next token is the lastName
    token = strtok_r(NULL, ",", &saveptr);
    currMovie->year = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->year, token);

    // The next token is the firstName
    token = strtok_r(NULL, ",", &saveptr);
    currMovie->languages = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->languages, token);

    // The last token is the major
    token = strtok_r(NULL, "\n", &saveptr);
    currMovie->rating = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->rating, token);

    // Set the next node to NULL in the newly created movie entry
    currMovie->next = NULL;

    return currMovie;
}

/*
* Return a linked list of movies by parsing data from
* each line of the specified file.
*/
struct movie *processFile(char *filePath)
{
    // Open the specified file for reading only
    FILE *movieFile = fopen(filePath, "r");

    char *currLine = NULL;
    size_t len = 0;
    size_t nread;
    char *token;
    int listLen;

    // The head of the linked list
    struct movie *head = NULL;
    // The tail of the linked list
    struct movie *tail = NULL;

    // Read the file line by line
    while ((nread = getline(&currLine, &len, movieFile)) != -1)
    {
        // Get a new movie node corresponding to the current line
        struct movie *newNode = createMovie(currLine);
        listLen++;

        //check if this is the first node
        if (head == NULL)
        {
            //if this is the first, set the head and the tail to this node
            head = newNode;
            tail = newNode;
        }
        else
        {
            //if this is not the first, add this node to the list and advance the tail
            tail->next = newNode;
            tail = newNode;
        }
    }
    
    printf("Processed file %s and parsed data from %d movies \n\n", filePath, listLen);
    free(currLine);
    fclose(movieFile);
    return head;
}

/*
Present the user with the menu of choices, retrieve and validate their input
*/
int promptUser(void){

    int response;
    //loop runs at least once, then repeats if the user enters an invalid input
    do {
        printf("1. Show movies released in the specified year \n"
               "2. Show highest rated movie for each year \n"
               "3. Show the title and year of release of all movies in a specific language \n"
               "4. Exit from the program \n\n");

        printf("Enter a number from 1 to 4: ");
        scanf("%i", &response);
        if (response > 4 || response < 1){
            fprintf(stderr, "You entered an incorrect choice. Try again.\n\n");
        }
    } while (response > 4 || response <1);

    return response;
}

/*
* Print data for the given movie
*/
void printMovie(struct movie* aMovie){
  printf("%s, %s %s, %s\n", aMovie->title,
               aMovie->year,
               aMovie->languages,
               aMovie->rating);
}
/*
* Print the linked list of movies
*/
void printMovieList(struct movie *list)
{
    while (list != NULL)
    {
        printMovie(list);
        list = list->next;
    }
}

/*
Process movies data into a linked list of all movies
Ask user to choose from the menu of options
Perform selected function and repeat menu unless exit was chosen
*/

int main(int argc, char *argv[])
{
    //process data into a linked list of all movies
    struct movie *list = processFile(argv[1]);

    int choice = 0;
    //repeat the menu and resulting functions until the user inputs 4
    while (choice != 4){
        choice = promptUser();
        switch(choice){
        case 1:
        //yet to be implemented
        break;
        case 2:
        //yet to be implemented
        break;
        case 3:
        //yet to be implemented
        break;
        case 4:
        break;
        }
    }
    return EXIT_SUCCESS;
}
