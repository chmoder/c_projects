/* Thomas Cross */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//#define DICTIONARY "urbandictionary.txt"

int getNumLines(char *, char *);
void printArray(char **, const int);
char ** makeWordsArray(char *, char *, char **, const int);

int main(int argc, char *argv[])
{
    char * dictionary_name;
    if(argc > 1)
    {
        dictionary_name = (char*)malloc(sizeof(char) * strlen(argv[1]) + 1);
        strcpy(dictionary_name, argv[1]);
    }
    else
    {
        printf("Please input a dictionary file.\nex:./dictionary/where/it/is/dictionary.txt\n");
        exit(1);
    }
    puts(dictionary_name);
    const int number_of_words = getNumLines(dictionary_name, "r");
    char ** words_array;
    words_array = makeWordsArray(dictionary_name, "r", words_array, number_of_words);
    printArray(words_array,number_of_words);

    //Free the array
    int i;
    for(i = 0; i < number_of_words; i++)
    {
        free(words_array[i]);
    }
    free(words_array);
    free(dictionary_name);
    return 0;
}

void printArray(char **words_array, const int number_of_words)
{
    int counter = 0;
    for( ; counter < number_of_words; ++counter )
    {
        int temp = 0;
        while(words_array[counter][temp] != '\0')
        {
            printf("%c", words_array[counter][temp++]);
        }
            printf("\n");
    }
}

char ** makeWordsArray( char * location, char * operation, char **dict_arr, const int number_of_words)
{   
    FILE *dict;
        dict = fopen( location, operation);
    if(!dict)
    {
        fprintf(stderr,"File did not open properly");
        exit(1);
    }

    char * temp_array;
    temp_array = malloc(2000 * sizeof(char));
    dict_arr = malloc(number_of_words * sizeof(long *));    
    if(dict_arr == NULL)
    {
        fprintf(stderr, "out of memory\n");
        exit(0);
    }
    int counter = 0;
    while(fgets(temp_array, number_of_words, dict))
    {
        char *p = strchr( temp_array, '\n' );
        if ( p ) *p = '\0';
        {
            dict_arr[counter] = malloc( (strlen(temp_array) + 1) * sizeof(char));
            strcpy(dict_arr[counter], temp_array);
            ++counter;
        }
    }
    free(temp_array);
    fclose(dict);
    return dict_arr;
}

int getNumLines(char * location, char * operation)
{
    FILE *dict;
    dict = fopen(location, "r");
    if(!dict)
    {
        fprintf(stderr,"File did not open properly.");
        exit(1);
    }

    int numlines = 0;
    char c = getc(dict);
    while(c != EOF)
    {   
        if(c == '\n')
        {
            numlines++;
        }
        c = getc(dict);
    }
    //printf("numlines=%d\n",numlines);

    fclose(dict);
    
    return numlines;
}
