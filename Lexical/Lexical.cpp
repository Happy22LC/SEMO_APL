#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// Enum class to define different types of tokens
enum class TokenType {
    KEYWORD,
    IDENTIFIER,
    INTEGER_LITERAL,
    FLOAT_LITERAL,
    OPERATOR,
    PUNCTUATOR,
    UNKNOWN
};

// Struct to represent a token with its type and value
struct Token {
    TokenType type;
    string value;

    Token(TokenType t, const string& v)
        : type(t)
        , value(v)
    {
    }
};

// Class that implements the lexical analyzer
class LexicalAnalyzer {
private:
    string input;
    size_t position;
    unordered_map<string, TokenType> keywords;

    // TO DO: Implement the initKeywords function
    void initKeywords()
    {
        // Initialize the keywords map
        keywords["int"] = TokenType::KEYWORD;
        keywords["float"] = TokenType::KEYWORD;
        keywords["main"] = TokenType::KEYWORD;
        keywords["return"] = TokenType::KEYWORD;
        keywords["if"] = TokenType::KEYWORD;
        keywords["else"] = TokenType::KEYWORD;
    }

    // TO DO: Implement the isWhitespace function
    bool isWhitespace(char c)
    {
        // Check if a character is whitespace
        // Check if the given character is a space,tab,newline

        return c == ' ' || c == '\t' || c == '\n';
    }

    // TO DO: Implement the isAlpha function
    bool isAlpha(char c)
    {
        // Check if a character is alphabetic
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }

    // TO DO: Implement the isDigit function
    bool isDigit(char c)
    {
        // Check if a character is a digit
        return c >= '0' && c <= '9';
    }

    // TO DO: Implement the isAlphaNumeric function
    bool isAlphaNumeric(char c)
    {
        // Check if a character is alphanumeric
        // Check either letter or a digit
        return isAlpha(c) || isDigit(c);
    }

    // TO DO: Implement the getNextWord function
    // read the next word from input.
    string getNextWord()
    {
        // Get the next word (identifier or keyword) from the input
        string word;
        while (position < input.length() && isAlphaNumeric(input[position]))
        {
            word += input[position++];
        }
        return word;
    }

    // TO DO: Implement the getNextNumber function
    string getNextNumber()
    {
        // Get the next number (integer or float) from the input
        string number;
        bool isFloat = false;
        while (position < input.length() && (isDigit(input[position]) || input[position] == '.'))
        {
            if (input[position] == '.')
            {
                isFloat = true;
            }
            number += input[position++];
        }
        return number;
    }

public:
    // Constructor for LexicalAnalyzer
    LexicalAnalyzer(const string& source)
        : input(source)
        , position(0)
    {
        initKeywords();
    }

    // TO DO: Implement the tokenize function
    vector<Token> tokenize()
    {
        // Tokenize the input string
        vector<Token> tokens;
        while (position < input.length())
        {
            if (isWhitespace(input[position]))
            {
                position++;  // Skip whitespaces
                continue;
            }

            if (isAlpha(input[position]))
            {
                string word = getNextWord();
                if (keywords.find(word) != keywords.end())
                {
                    tokens.push_back(Token(TokenType::KEYWORD, word));
                }
                else
                {
                    tokens.push_back(Token(TokenType::IDENTIFIER, word));
                }
            }
            else if (isDigit(input[position]))
            {
                string number = getNextNumber();
                if (number.find('.') != string::npos)
                {
                    tokens.push_back(Token(TokenType::FLOAT_LITERAL, number));
                }
                else
                {
                    tokens.push_back(Token(TokenType::INTEGER_LITERAL, number));
                }
            }
            else if (input[position] == '+' || input[position] == '-' || input[position] == '*' || input[position] == '/' || input[position] == '=')
            {
                tokens.push_back(Token(TokenType::OPERATOR, string(1, input[position])));
                position++;
            }
            else if (input[position] == '(' || input[position] == ')' || input[position] == '{' || input[position] == '}' || input[position] == ';' || input[position] == ',' || input[position] == '[' || input[position] == ']')
            {
                tokens.push_back(Token(TokenType::PUNCTUATOR, string(1, input[position])));
                position++;
            }
            else
            {
                tokens.push_back(Token(TokenType::UNKNOWN, string(1, input[position])));
                position++;
            }
        }
        return tokens;
    }
};

// TO DO: Implement the getTokenTypeName function
string getTokenTypeName(TokenType type)
{
    // Convert TokenType to string for printing
    switch (type)
    {
    case TokenType::KEYWORD:
        return "keyword";
    case TokenType::IDENTIFIER:
        return "identifier";
    case TokenType::INTEGER_LITERAL:
        return "integer_literal";
    case TokenType::FLOAT_LITERAL:
        return "float_literal";
    case TokenType::OPERATOR:
        return "operator";
    case TokenType::PUNCTUATOR:
        return "punctuator";
    case TokenType::UNKNOWN:
        return "unknown";
    default:
        return "unknown";
    }
}

// TO DO: Implement the printTokens function
void printTokens(const vector<Token>& tokens)
{
    // Print all tokens
    for (const auto& token : tokens)
    {
        cout << "type: " << getTokenTypeName(token.type) << ", value: " << token.value << endl;
    }
}

// Driver Code
int main(int argc, char* argv[])
{
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <source_code>" << endl;
        return 1;
    }

    string sourceCode = argv[1];

    // Create a LexicalAnalyzer object
    LexicalAnalyzer lexer(sourceCode);

    // Tokenize the source code
    vector<Token> tokens = lexer.tokenize();

    // Print the original source code
    cout << "Source code: " << sourceCode << endl << endl;

    // Print all identified tokens
    cout << "Tokens Generated by Lexical Analyzer:" << endl;
    printTokens(tokens);

    return 0;
}


