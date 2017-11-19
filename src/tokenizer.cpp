#include "tokenizer.hpp"

#include <cctype>

namespace {
    bool isalpha (char x)
    {
        return std::isalpha(static_cast<unsigned char>(x));
    }
    bool isdigit (char x)
    {
        return std::isdigit(x);
    }

    unsigned short toshort (char x) /* N4659 $5.3/3 */
    {
        return x - '0';
    }
    char tochar (unsigned short x) /* N4659 $5.3/3 */
    {
        return x + '0';
    }

    std::string getIdentifier (std::string::const_iterator& it, std::string::const_iterator end)
    {
        std::string value;
        while ( it != end && isalpha(*it) )
        {
            value.push_back (*it);
            it++;
        }
        it--;
        return value;
    }

    std::string getNumber (std::string::const_iterator& it, std::string::const_iterator end)
    {
        std::string value;
        while ( it != end && isdigit(*it) )
        {
            value.push_back (*it);
            it++;
        }
        it--;
        return value;
    }
} /* namespace */

namespace Expresser
{

std::list<Token> tokenize (const std::string& text)
{
    if ( text.empty() )
        return {};

    std::list<Token> result;
    std::string::const_iterator it = text.begin();
    while ( true )
    {
        if ( *it == '(' )
            result.push_back (Token{{}, TokenType::BRACKET_OPEN});
        else if ( *it == ')' )
            result.push_back (Token{{}, TokenType::BRACKET_CLOSE});
        else if ( *it == '+' )
            result.push_back (Token{{}, TokenType::ADD});
        else if ( *it == '-' )
            result.push_back (Token{{}, TokenType::SUB});
        else if ( *it == '*' )
            result.push_back (Token{{}, TokenType::MUL});
        else if ( *it == '/' )
            result.push_back (Token{{}, TokenType::DIV});
        else if ( isdigit(*it) )
            result.push_back(Token{getNumber(it, text.end()), TokenType::NUMBER});
        else if ( isalpha(*it) )
            result.push_back(Token{getIdentifier(it, text.end()), TokenType::IDENTIFIER});

        if ( it != text.end() )
            it++;
        else
            break;
    }
    return result;
}

} /* namespace Expresser */
