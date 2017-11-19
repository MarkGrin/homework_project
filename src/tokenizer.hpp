#ifndef H_CD0455C3A344497DB063A4DE72C9A90A

#define H_CD0455C3A344497DB063A4DE72C9A90A


#include <string>
#include <list>

namespace Expresser
{

namespace TokenType
{
    enum : std::size_t
    {
        NUMBER,
        ADD,
        SUB,
        MUL,
        DIV,
        IDENTIFIER,
        BRACKET_OPEN,
        BRACKET_CLOSE,
    };
}

struct Token {
    std::string value;
    std::size_t type;
};

std::list<Token> tokenize (const std::string& text);

} /* namespace Expresser */

#endif /* H_CD0455C3A344497DB063A4DE72C9A90A */
