#include "lexer.h"

//Returns one instnace of the AllTokens class, requires a pointer to a FILE object
AllTokens lexer(FILE* file) {
    char curChar = fgetc(file); 
    int  tokCount= 0;
    AllTokens result;  

    result.tokenArray = (Token*)malloc(MAX_TOKENS * sizeof(Token));
    if( result.tokenArray == NULL) { printf("MEMORY ALLOCATION FAILED\n"); exit(EXIT_FAILURE); }

    while(curChar != EOF) {
        Token token = createToken(file, &curChar); 

        result.tokenArray[tokCount] = token; 
        tokCount++; 
        curChar = fgetc(file); 
    }

    result.tokenCount = tokCount; 
    return result; 
}

//Returns one token per function call, requires a pointer to a FILE object and a pointer to a char object 
Token createToken(FILE* file, char* curChar) {
    Token result; 

    //Check if curChar is a seperator token 
    if(*curChar == ';'){
        result.tokenType = SEPERATOR; 
        result.Data.Seperator.type = SEMICOLON; 

    } else if (*curChar == '(') {
        result.tokenType = SEPERATOR; 
        result.Data.Seperator.type = OPEN_PAREN; 

    } else if (*curChar == ')') {
        result.tokenType = SEPERATOR; 
        result.Data.Seperator.type = CLOSE_PAREN; 
    }

    //Check if curChar is a literal token 
    else if (isdigit(*curChar)) {
        int retValue = 0; 
        retValue = *curChar - '0'; 
        *curChar = fgetc(file);  

        while(isdigit(*curChar)){
            retValue = retValue * 10 + (*curChar - '0'); 
            *curChar = fgetc(file);
        }

        result.tokenType = LITERAL; 
        result.Data.Literal.type = INT; 
        result.Data.Literal.value = retValue; 

        //push one char back onto the character stream otherwise the lexer function will skip one token
        ungetc(*curChar, file); 
    }

    //Check if curChar is a keyword 
    else if(isalpha(*curChar)) {

        char buffer[MAX_KEYWORD_SIZE]; 
        int count = 0; 

        while(isalpha(*curChar)){
            if((count + 1) > MAX_KEYWORD_SIZE) { printf("KEYWORD/VARIABLE CHAR SIZE OVER MAXIMUM"); exit(EXIT_FAILURE); }

            buffer[count] = *curChar; 
            count++; 
            *curChar = fgetc(file); 
        }
        
        count++; 
        buffer[count] = '\n'; 

        //Check to see if the characters form a keyword
        if(strcmp(buffer, "exit") == 0){
            result.tokenType = KEYWORD; 
            result.Data.Keyword.type = EXIT; 
        } else if (strcmp(buffer, "return") == 0){
            result.tokenType = KEYWORD; 
            result.Data.Keyword.type = RETURN; 
        }

        //If characters do not form a keyword, it is a variable name


        //push one char back onto the character stream otherwise the lexer function will skip one token
        ungetc(*curChar, file); 
    }

    return result; 
}