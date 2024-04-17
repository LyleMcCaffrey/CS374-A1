// If you are not compiling with the gcc option --std=gnu99, then
// uncomment the following line or you might get a compiler warning
//#define _GNU_SOURCE

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

        // Is this the first node in the linked list?
        if (head == NULL)
        {
            // This is the first node in the linked link
            // Set the head and the tail to this node
            head = newNode;
            tail = newNode;
        }
        else
        {
            // This is not the first node.
            // Add this node to the list and advance the tail
            tail->next = newNode;
            tail = newNode;
        }
    }
    
    printf("Processed file %s and parsed data from %d movies \n\n", filePath, listLen);
    free(currLine);
    fclose(movieFile);
    return head;
}

int promptUser(void){

    int response;
    do {
        printf("1. Show movies released in the specified year \n"
               "2. Show highest rated movie for each year \n"
               "3. Show the title and year of release of all movies in a specific language \n"
               "4. Exit from the program \n\n");

        printf("Enter a number from 1 to 4:");
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
*   Process the file provided as an argument to the program to
*   create a linked list of movie structs
*   Compile the program as follows:
*       gcc --std=gnu99 -o movies main.c
*/

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("You must provide the name of the file to process\n");
        printf("Example usage: ./movies movies_sample.csv\n");
        return EXIT_FAILURE;
    }
    struct movie *list = processFile(argv[1]);

    int choice = promptUser();
    //switch(choice){
    //case 1:

    //case 2:

    //case 3:

    //case 4: 
    //}

    return EXIT_SUCCESS;
}
