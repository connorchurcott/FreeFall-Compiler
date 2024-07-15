#include<stdio.h> 
#include<stdlib.h> 
#define MAX_TOKENS 1000 
#define MAX_KEYWORD_SIZE 75

/*----------Structs-----------*/

//Types of literals
typedef enum {
    INT, 
} LiteralType; 

//Types of keywords
typedef enum {
    EXIT, 
    RETURN
} KeywordType; 

//Types of seperators
typedef enum {
   SEMICOLON,
   OPEN_PAREN,
   CLOSE_PAREN,
} SeperatorType; 

//Types of tokens
typedef enum {
    LITERAL, 
    KEYWORD, 
    SEPERATOR
} TokenType; 

//Anatomy of a token (Calling function must check tokenType to determine which struct within the union is being used)
typedef struct {
    TokenType tokenType; 

    union {
        struct {
            LiteralType type; 
            int value; 
        } Literal; 

        struct {
            KeywordType type; 
        } Keyword; 

        struct {
            SeperatorType type; 
        } Seperator; 
    } Data; 

} Token; 

//Used to store the array of tokens and how many tokens are in that array 
typedef struct {
   int tokenCount; 
   Token* tokenArray; 
} AllTokens;


/*----------Function prototypes-----------*/

//Returns one instnace of the AllTokens class, requires a pointer to a FILE object
// NOTE: THIS FUNCTION MALLOCS, AND THE CALLING FUNCTION IS REQUIRED TO free(this.tokenArray)
AllTokens lexer(FILE* file); 

//Returns one token per function call, requires a pointer to a FILE object and a pointer to a char object 
Token createToken(FILE* file, char* curChar); 