#include "construct.hpp"

namespace Expresser
{

namespace
{

ExprNode* getGr0 (std::list<Token>::iterator& it, std::list<Token>::iterator end, std::string& error);
ExprNode* getExpression (std::list<Token>::iterator& it, std::list<Token>::iterator end, std::string& error);
ExprNode* getAdd (std::list<Token>::iterator& it, std::list<Token>::iterator end, std::string& error);
ExprNode* getLeaf (std::list<Token>::iterator& it, std::list<Token>::iterator end, std::string& error);

ExprNode* getGr0 (std::list<Token>::iterator& it, std::list<Token>::iterator end, std::string& error)
{
    return getExpression (it, end, error);
}

ExprNode* getExpression (std::list<Token>::iterator& it, std::list<Token>::iterator end, std::string& error)
{
    return getAdd (it, end, error);
}

ExprNode* getAdd (std::list<Token>::iterator& it, std::list<Token>::iterator end, std::string& error)
{
    if (it == end)
        return nullptr;

    ExprNode* left;
    ExprNode* right;
    ExprNode* result;
    if ( it->type == TokenType::BRACKET_OPEN )
    {
        it++;
        left = getExpression (it, end, error);
        if ( it == end || it->type != TokenType::BRACKET_CLOSE )
        {
            error += ", bracket mismatch";
            return nullptr;
        }
    }
    else
        left = getLeaf (it, end, error);

    if ( it == end )
        return delete left, nullptr;

    if ( it->type != TokenType::ADD )
        return delete left, error += ", expected +", nullptr;

    result = new ExprNode;
    result->setData("+");
    it++;

    if ( it->type == TokenType::BRACKET_OPEN )
    {
        it++;
        right = getExpression (it, end, error);
        if ( it == end || it->type != TokenType::BRACKET_CLOSE )
        {
            error += ", bracket mismatch";
            return nullptr;
        }
    }
    else
        right = getLeaf (it, end, error);

    result->setLeft (left);
    result->setRight (right);
    return result;
}

ExprNode* getLeaf (std::list<Token>::iterator& it, std::list<Token>::iterator end, std::string& error)
{
    ExprNode* result = nullptr;
    if ( it == end )
        return result; 
    if ( it->type == TokenType::NUMBER )
    {
        result = new ExprNode;
        result->setData (it->value);
    }
    else if ( it->type == TokenType::IDENTIFIER )
    {
        result = new ExprNode;
        result->setData (it->value);
    }
    it++;
    return result;
}

} /* namespace */


ExprNode* constructTree (std::list<Token>& tokens, std::string& error)
{
    auto it = tokens.begin ();
    auto end = tokens.end ();
    if ( it == end )
        return nullptr;

    return getGr0 (it, end, error);
}

} /* namespace Expresser */
