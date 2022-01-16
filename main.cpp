// stb
#define STBDS_NO_SHORT_NAMES
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#define STBDS_REALLOC(context,ptr,size) better_realloc
#define STBDS_FREE(context,ptr)         better_free
// stb

// std
#include <stdio.h>  
#include <stdint.h>
#include <ctype.h>
#include <algorithm>
#include <string.h>
// std

#define global_variable static;

#define INCLUDE_STB_DS_H

#define CHUNK 1024 /* read 1024 bytes at a time */

enum TokenTypes
{
	// Single-character tokens.
	TOKEN_LEFT_PAREN, TOKEN_RIGHT_PAREN,
	TOKEN_LEFT_BRACE, TOKEN_RIGHT_BRACE,
	TOKEN_COMMA, TOKEN_DOT, TOKEN_MINUS, TOKEN_PLUS,
	TOKEN_SEMICOLON, TOKEN_COLON, TOKEN_SLASH, TOKEN_STAR,

	// One or two character tokens.
	TOKEN_BANG, TOKEN_BANG_EQUAL,
	TOKEN_EQUAL, TOKEN_EQUAL_EQUAL,
	TOKEN_GREATER, TOKEN_GREATER_EQUAL,
	TOKEN_LESS, TOKEN_LESS_EQUAL,

	// Literals.
	TOKEN_IDENTIFIER, TOKEN_STRING_LITERAL, TOKEN_INTEGER_LITERAL, TOKEN_FLOAT_LITERAL,
	TOKEN_FALSE_LITERAL, TOKEN_TRUE_LITERAL,

	// Keywords.
	TOKEN_STRING, TOKEN_INTEGER, TOKEN_FLOAT, TOKEN_BOOLEAN,
	TOKEN_AND, TOKEN_OR, TOKEN_NOT, 
	TOKEN_IF, TOKEN_ELSE, TOKEN_ELSEIF, 
	TOKEN_STRUCT, 
	TOKEN_FOR, TOKEN_WHILE, TOKEN_WHEN,
	TOKEN_FUNCTION, TOKEN_PROCEDURE, 
	TOKEN_RETURN, TOKEN_BREAK,

	TOKEN_EOF
};

struct Token 
{
	TokenTypes tokenType;
	int		   index;
	int		   length;
	int        line;
};

struct Keyword
{
	char      *key; 
	TokenTypes value;
};

const char* get_token_type_name(enum TokenTypes tokenTypes) 
{
	switch (tokenTypes) 
	{
		case TOKEN_LEFT_PAREN:      return "(";
		case TOKEN_RIGHT_PAREN:     return ")";
		case  TOKEN_LEFT_BRACE:      return "{";
		case TOKEN_RIGHT_BRACE:     return "}";
		case TOKEN_COMMA:           return ","; 
		case TOKEN_DOT:             return "."; 
		case TOKEN_MINUS:           return "-"; 
		case TOKEN_PLUS:            return "+";
		case TOKEN_SEMICOLON:       return ";";
		case TOKEN_COLON:           return ":"; 
		case TOKEN_SLASH:           return "/"; 
		case TOKEN_STAR:            return "*";
		case TOKEN_BANG:            return "!"; 
		case TOKEN_BANG_EQUAL:      return "!=";
		case TOKEN_EQUAL:           return "="; 
		case TOKEN_EQUAL_EQUAL:     return "==";
		case TOKEN_GREATER:         return ">"; 
		case TOKEN_GREATER_EQUAL:   return ">=";
		case TOKEN_LESS:            return "<"; 
		case TOKEN_LESS_EQUAL:      return "<=";
		case TOKEN_IDENTIFIER:      return "Identifier"; 
		case TOKEN_STRING_LITERAL:  return "string literal"; 
		case TOKEN_INTEGER_LITERAL: return "integer literal"; 
		case TOKEN_FLOAT_LITERAL:   return "float literal";
		case TOKEN_FALSE_LITERAL:   return "false"; 
		case TOKEN_TRUE_LITERAL:    return "true";
		case TOKEN_STRING:          return "string"; 
		case TOKEN_INTEGER:         return "integer"; 
		case TOKEN_FLOAT:           return "float"; 
		case TOKEN_BOOLEAN:         return "bool";
		case TOKEN_AND:             return "and"; 
		case TOKEN_OR:              return "or"; 
		case TOKEN_NOT:             return "not"; 
		case TOKEN_IF:              return "if"; 
		case TOKEN_ELSEIF:          return "elseif";
		case TOKEN_ELSE:            return "else"; 
		case TOKEN_STRUCT:          return "struct"; 
		case TOKEN_FOR:             return "for"; 
		case TOKEN_WHILE:           return "while"; 
		case TOKEN_WHEN:            return "when";
		case TOKEN_FUNCTION:        return "function"; 
		case TOKEN_PROCEDURE:       return "procedure"; 
		case TOKEN_RETURN:          return "return"; 
		case TOKEN_BREAK:           return "break";
		case TOKEN_EOF:             return "EndOfFile";	
	}
}

Token create_token(TokenTypes tokenType, char code[], int startIndex, int endIndex, int line)
{
	Token token = {};
	token.tokenType = tokenType;
	token.index     = startIndex;
	token.length    = startIndex + endIndex;
	token.line      = line;
	return token;
}

Token scan_tokens(char source[])
{
	Token *tokens = NULL;
	int index = 0;
	int line  = 1;
	while(source[index]!= '\0') 
	{
		char character = source[index];
		switch (character) 
		{
			case ' ' : // Whitespace.
			case '\t': // Horizontal tab. 
			case '\r': // Carriage return.
			case '\v': // Vertical tab.
			{
				index++;
			} break;

			case '\n': // New line
			{
				line++; 
				index++; 
			} break;

			case '/': 
			{	
				// peeks the next char
				if (source[index+1] == '/')
				{   // Comment goes the end of the line.
					while (source[index] != '\n' && source[index] != '\0') 
						index++;
				}
				else
				{
					stbds_arrput(tokens, create_token(TOKEN_SLASH, source, index, index + 1, line));
					index++;
				}
			} break;

			case ':':
			{
				stbds_arrput(tokens, create_token(TOKEN_COLON, source, index, index + 1, line)); 
				index++;
			} break;

			case '(': 
			{
				stbds_arrput(tokens, create_token(TOKEN_LEFT_PAREN, source, index, index + 1, line));  
				index++; 
			} break;

			case ')': 
			{
				stbds_arrput(tokens, create_token(TOKEN_RIGHT_PAREN, source, index, index + 1, line)); 
				index++; 
			} break;

			case '{': 
			{
				stbds_arrput(tokens, create_token(TOKEN_LEFT_BRACE, source, index, index + 1, line)); 
				index++;
			} break;

			case '}': 
			{
				stbds_arrput(tokens, create_token(TOKEN_RIGHT_BRACE, source, index, index + 1, line)); 
				index++; 
			} break;

			case ',':
			{
				stbds_arrput(tokens, create_token(TOKEN_COMMA, source, index, index + 1, line)); 
				index++; 
			} break;

			case '.':
			{
				stbds_arrput(tokens, create_token(TOKEN_DOT, source, index, index + 1, line));
				index++; 
			} break;

			case '-':
			{
				stbds_arrput(tokens, create_token(TOKEN_MINUS, source, index, index + 1, line)); 
				index++; 
			} break;

			case '+':
			{
				stbds_arrput(tokens, create_token(TOKEN_PLUS, source, index, index + 1, line)); 
				index++;
			} break;

			case ';':
			{
				stbds_arrput(tokens, create_token(TOKEN_SEMICOLON, source, index, index + 1, line)); 
				index++;
			} break;

			case '*':
			{
				stbds_arrput(tokens, create_token(TOKEN_STAR, source, index, index + 1, line)); 
				index++; 
			} break;

			case '=':
			{
				if (source[index + 1] == '=')
				{
					stbds_arrput(tokens, create_token(TOKEN_EQUAL_EQUAL, source, index, index + 2, line));
					index += 2;
				} 
				else
				{
					stbds_arrput(tokens, create_token(TOKEN_EQUAL, source, index, index + 1, line)); 
					index++; 
				}
			} break;

			case '<':
			{
				if (source[index + 1] == '=')
				{
					stbds_arrput(tokens, create_token(TOKEN_LESS_EQUAL, source, index, index + 2, line)); 
					index += 2;
				} 
				else
				{
					stbds_arrput(tokens, create_token(TOKEN_LESS, source, index, index + 1, line)); 
					index++; 
				}
			} break;

			case '>':
			{
				if (source[index + 1] == '=')
				{
					stbds_arrput(tokens, create_token(TOKEN_GREATER_EQUAL, source, index, index + 2, line)); 
					index += 2;
				} 
				else
				{
					stbds_arrput(tokens, create_token(TOKEN_GREATER, source, index, index + 1, line)); 
					index++; 
				}
			} break;

			case '!': 
			{
				if (source[index + 1] == '=')
				{
					stbds_arrput(tokens, create_token(TOKEN_BANG_EQUAL, source, index, index + 2, line));       
					index += 2;
				} 
				else
				{
					stbds_arrput(tokens, create_token(TOKEN_BANG, source, index, index + 1, line)); 
					index++; 
				}
				
			} break;

			case '"' :
			{
				int startIndex = index;
				while (source[index] != '"' && source[index] != '\0') 
				{
					if (source[index] == '\n') 
						line++;

					index++;
				}
				
				if (source[index] == '\0') {
					printf("Unterminated string at index %d line %d", index, line); // TODO: Error
					break;
				}

				// closing quota
				index++;  
				stbds_arrput(tokens, create_token(TOKEN_STRING_LITERAL, source, startIndex, index, line));
			}
			break;
			default:
			{
				if (isdigit(character))
				{
					int startIndex = index;

					while (isdigit(source[index])) index++;
					bool isFloat = false;
					if (source[index] == '.' & isdigit(source[index + 1]))
					{
						isFloat = true;
						while (isdigit(source[index])) index++;
					}

					if(isFloat)
						stbds_arrput(tokens, create_token(TOKEN_FLOAT_LITERAL, source, startIndex, index, line));
					else
						stbds_arrput(tokens, create_token(TOKEN_INTEGER_LITERAL, source, startIndex, index, line));
				}
				else if (isalpha(character)) // TODO: reafactor
				{
					int startIndex = index;

					while (isalpha(source[index]) || isdigit(source[index])) index++;

					int tokenLength = index - startIndex;
					// xxx cleaup
					switch (source[startIndex])
					{
						case 'a': 
						{
							if (tokenLength == 3 && memcmp(source + startIndex, "and", 3) == 0)
								stbds_arrput(tokens, create_token(TOKEN_AND, source, startIndex, index, line));
							else 
								stbds_arrput(tokens, create_token(TOKEN_IDENTIFIER, source, startIndex, index, line));
						} break;
						case 'b': 
						{
							if (tokenLength == 5 && memcmp(source + startIndex, "break", 5) == 0)
								stbds_arrput(tokens, create_token(TOKEN_BREAK, source, startIndex, index, line));
							else if (tokenLength == 4 && memcmp(source + startIndex, "bool", 4) == 0)
								stbds_arrput(tokens, create_token(TOKEN_BREAK, source, startIndex, index, line));
							else 
								stbds_arrput(tokens, create_token(TOKEN_IDENTIFIER, source, startIndex, index, line));
						} break;
						case 'e': 
						{
							if (tokenLength == 4 && memcmp(source + startIndex, "else", 4) == 0)
								stbds_arrput(tokens, create_token(TOKEN_ELSE, source, startIndex, index, line));
							else if (tokenLength == 6 && memcmp(source + startIndex, "elseif", 6) == 0)
								stbds_arrput(tokens, create_token(TOKEN_ELSEIF, source, startIndex, index, line));
							else 
								stbds_arrput(tokens, create_token(TOKEN_IDENTIFIER, source, startIndex, index, line));
						} break;
						case 'f':
						{
							if (tokenLength == 3 && memcmp(source + startIndex, "for", 3) == 0)
								stbds_arrput(tokens, create_token(TOKEN_FOR, source, startIndex, index, line));
							else if (tokenLength == 5 && memcmp(source + startIndex, "false", 5) == 0)
								stbds_arrput(tokens, create_token(TOKEN_FALSE_LITERAL, source, startIndex, index, line));
							else if (tokenLength == 4 && memcmp(source + startIndex, "func", 4) == 0)
								stbds_arrput(tokens, create_token(TOKEN_FUNCTION, source, startIndex, index, line));
							else 
								stbds_arrput(tokens, create_token(TOKEN_IDENTIFIER, source, startIndex, index, line));
						} break;
						case 'i': 
						{
							if (tokenLength == 2 && memcmp(source + startIndex, "if", 2) == 0)
								stbds_arrput(tokens, create_token(TOKEN_IF, source, startIndex, index, line));
							else 
								stbds_arrput(tokens, create_token(TOKEN_IDENTIFIER, source, startIndex, index, line));
						} break;
						case 'o':
						{
							if (tokenLength == 2 && memcmp(source + startIndex, "or", 2) == 0)
								stbds_arrput(tokens, create_token(TOKEN_OR, source, startIndex, index, line));
							else 
								stbds_arrput(tokens, create_token(TOKEN_IDENTIFIER, source, startIndex, index, line));
						} break;
						case 'p':
						{
							if (tokenLength == 4 && memcmp(source + startIndex, "proc", 4) == 0)
								stbds_arrput(tokens, create_token(TOKEN_PROCEDURE, source, startIndex, index, line));
							else 
								stbds_arrput(tokens, create_token(TOKEN_IDENTIFIER, source, startIndex, index, line));
						} break;
						case 'r':
						{
							if (tokenLength == 6 && memcmp(source + startIndex, "return", 6) == 0)
								stbds_arrput(tokens, create_token(TOKEN_RETURN, source, startIndex, index, line));
							else 
								stbds_arrput(tokens, create_token(TOKEN_IDENTIFIER, source, startIndex, index, line));
						}
						case 't':
						{
							if (tokenLength == 4 && memcmp(source + startIndex, "true", 4) == 0)
								stbds_arrput(tokens, create_token(TOKEN_TRUE_LITERAL, source, startIndex, index, line));
							else 
								stbds_arrput(tokens, create_token(TOKEN_IDENTIFIER, source, startIndex, index, line));
						}
						break;
						case 'w':
						{
							if (tokenLength == 5 && memcmp(source + startIndex, "while", 5) == 0)
								stbds_arrput(tokens, create_token(TOKEN_WHILE, source, startIndex, index, line));
							if (tokenLength == 4 && memcmp(source + startIndex, "when", 4) == 0)
								stbds_arrput(tokens, create_token(TOKEN_WHEN, source, startIndex, index, line));
							else 
								stbds_arrput(tokens, create_token(TOKEN_IDENTIFIER, source, startIndex, index, line));
						}
						break;
					}
				}
				else
				{
					printf("Unexptexted character: %c", character);
				}
			}
			break;
		}
	}

	printf("Tokens: \n");
	for (int i = 0; i < stbds_arrlen(tokens); ++i)
	{
		printf("_________________________________________\n");
		printf("TokenType : %s \n", get_token_type_name(tokens[i].tokenType));
		printf("index     : %d \n", tokens[i].index);
		printf("line      : %d \n", tokens[i].line);
		printf("_________________________________________\n");
	}


	return *tokens;
}

int main(int argc, char *argv[]) 
{
	/*char *path = argv[1];
	FILE* file = fopen(path, "rb");*/
	char *path = "C:/Users/gamer/Documents/GitHub/beep/source/literals.beep\0";
	FILE* file = fopen(path, "rb");

	if (file == NULL) {
		fprintf(stderr, "Could not open file \"%s\".\n", path);
		exit(74);
	}
	
	fseek(file, 0L, SEEK_END);     // Sets the position of the file to the given offset(SEEK_END)
	size_t fileSize = ftell(file); // returns the current file position of the file (End. This will give you its size)
	rewind(file);                  // Sets the position  file to the beginning (we want to read it from the beginning so rewind);

	char* source = (char*)malloc(fileSize + 1); // memmory allocate size of file + 1( 1 = sizeof(char). used for the null termination)  
	if (source == NULL) {
		fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
		exit(74);
	}
	
	size_t bytesRead = fread(source, sizeof(char), fileSize, file); // reads data from the given stream into the array(source)
	if (bytesRead < fileSize) {
		fprintf(stderr, "Could not read file \"%s\".\n", path);
		exit(74);
	}
	fclose(file); // closes the file stream. 
	 
	source[bytesRead] = '\0';  // adds the nukk termination
	
	Token tokens = scan_tokens(source);

	return 0;
} 