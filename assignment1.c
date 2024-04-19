
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
void printMovie(struct movie* aMovie, int option){
    switch(option){
    case 1:
        printf("%s\n", aMovie->title);
    break;
    case 2:
        printf("%s, %s %s\n", aMovie->year,
                aMovie->rating,
                aMovie->title);
    break;
    case 3:
        printf("%s, %s\n", aMovie->year,
                aMovie->title);
    break;      
    }
}
/*
Take an input for the year for which movies should be displayed
Loop through linked list and print each movie from the given year
*/  
void displayYear(struct movie *list)
{
    // variable used to track whether any movies can be found for the given year
    int moviesCheck = 0;
    printf("Enter the year for which you want to see movies: ");
    char input[4];
    scanf("%s", &input);
    const char *inputYear = input;
    while (list != NULL)
    {
        if (0 == strcmp(list->year, inputYear)){
            printMovie(list, 1);
            moviesCheck = 1;
        }
        list = list->next;
    }
    if (moviesCheck == 0){
        printf("No data about movies released in the year %s.\n\n", input);
    }
    printf("\n");
}

/*
void displayHighestRated(struct movie *list)
{
    //loop through
    // if the year is not in the array, save the item  

    while (list != NULL)
    {
        if (){
            printMovie(list, 2);
        }
        list = list->next;
    }
}
*/

/*
Take an input for the language for which movies should be displayed
Loop through linked list and print each movie made in the given language
*/
void displayLanguage(struct movie *list)
{
    char langInput[20];
    int movieFound = 0;
    printf("Enter the language for which you want to see movies: ");
    scanf("%s", &langInput);
    const char *langCheck = langInput;
    while (list != NULL)
    {
        if (strstr(list->languages, langCheck) != NULL){
            printMovie(list, 3);
            movieFound = 1;
        }
        list = list->next;
    }
    if (movieFound = 0){
        printf("No data released about movies released in %s ", langInput);
    }
    printf("\n");
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
        displayYear(list);
        break;
        case 2:
        //displayHighestRates(list);
        break;
        case 3:
        displayLanguage(list);
        break;
        case 4:
        break;
        }
    }
    return EXIT_SUCCESS;
}
