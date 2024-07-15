#include "lexer.h"

int main() {
    FILE* file = fopen("test.ff", "r"); 
    AllTokens allTokens = lexer(file); 
    fclose(file); 

    printf("tokArrSize:  %d\n", allTokens.tokenCount); 

    for(int i = 0; i < allTokens.tokenCount; i++){

        Token token = allTokens.tokenArray[i];
        switch (token.tokenType) {
            case LITERAL:
                printf("Literal: %d\n", token.Data.Literal.value);
                break;
            case KEYWORD:
                printf("Keyword: %d\n", token.Data.Keyword.type); 
                break;
            case SEPERATOR:
                printf("Seperator: %d\n", token.Data.Seperator.type); 
                break; 

            default:
                printf("Unknown token type\n");
        }
    }; 
    
    free(allTokens.tokenArray); 
}

