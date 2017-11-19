#include "construct.hpp"
#include "parseTransaction.hpp"

#include <iostream>

namespace Expresser
{

namespace
{

ExprNode* getGr0 (std::list<Token>::iterator& it, std::list<Token>::iterator end);
ExprNode* getExpression (std::list<Token>::iterator& it, std::list<Token>::iterator end);
ExprNode* getAddSub (std::list<Token>::iterator& it, std::list<Token>::iterator end);
ExprNode* getMulDiv (std::list<Token>::iterator& it, std::list<Token>::iterator end);
ExprNode* getBrackets (std::list<Token>::iterator& it, std::list<Token>::iterator end);
ExprNode* getLeaf (std::list<Token>::iterator& it, std::list<Token>::iterator end);

ExprNode* getGr0 (std::list<Token>::iterator& it, std::list<Token>::iterator end)
{
    return getExpression (it, end);
}

ExprNode* getExpression (std::list<Token>::iterator& it, std::list<Token>::iterator end)
{
    ExprNode* result =  getAddSub (it, end);
    if ( !result )
        result = getMulDiv (it, end);
    return result;
}

ExprNode* getAddSub (std::list<Token>::iterator& it, std::list<Token>::iterator end)
{
    if (it == end)
        return nullptr;

    ParseTransaction transaction (it);

    ExprNode* left;
    ExprNode* right;
    ExprNode* result;

    left = getMulDiv (it, end);
    if ( !left )
        left = getBrackets (it, end);
    if ( !left )
        left = getLeaf (it, end);
    if ( !left )
        return nullptr;

    transaction.setLeft (left);

    if ( it == end )
        return nullptr;

    if ( it->type != TokenType::ADD && it->type != TokenType::SUB)
        return std::cout <<  ", expected +,-:", nullptr;

    transaction.setMiddle(result = new ExprNode);
    if ( it->type == TokenType::ADD )
        result->setData ("+");
    else
        result->setData ("-");

    it++;

    right = getExpression (it, end);
    if ( !right )
        right = getBrackets (it, end);
    if ( !right )
        right = getLeaf (it, end);
    if ( !right )
        return nullptr;


    result->setLeft (left);
    result->setRight (right);

    transaction.commit();
    return result;
}

ExprNode* getMulDiv (std::list<Token>::iterator& it, std::list<Token>::iterator end)
{
    if (it == end)
        return nullptr;

    ParseTransaction transaction (it);

    ExprNode* left;
    ExprNode* right;
    ExprNode* result;

    left = getBrackets (it, end);
    if ( !left )
        left = getLeaf (it, end);
    if ( !left )
        return nullptr;

    transaction.setLeft (left);

    if ( it == end )
        return nullptr;

    if ( it->type != TokenType::MUL && it->type != TokenType::DIV)
        return std::cout << ", expected *,/:", nullptr;

    transaction.setMiddle(result = new ExprNode);
    if ( it->type == TokenType::MUL )
        result->setData ("*");
    else
        result->setData ("/");

    it++;

    right = getMulDiv (it, end);
    if ( !right )
        right = getBrackets (it, end);
    if ( !right )
        right = getLeaf (it, end);
    if ( !right )
        return nullptr;


    result->setLeft (left);
    result->setRight (right);

    transaction.commit();
    return result;
}

ExprNode* getBrackets (std::list<Token>::iterator& it, std::list<Token>::iterator end)
{
    if ( it->type == TokenType::BRACKET_OPEN )
    {
        ParseTransaction transaction(it);
        it++;
        ExprNode* result = getExpression (it, end);
        transaction.setMiddle (result);
        if ( it == end || it->type != TokenType::BRACKET_CLOSE )
        {
            std::cout << ", bracket mismatch";
            return nullptr;
        }
        it++;
        transaction.commit();
        return result;
    }
    else return nullptr;
 
}

ExprNode* getLeaf (std::list<Token>::iterator& it, std::list<Token>::iterator end)
{
    ParseTransaction transaction (it);
    ExprNode* result = nullptr;
    if ( it == end )
        return result; 
    if ( it->type == TokenType::NUMBER )
    {
        result = new ExprNode;
        result->setData (it->value);
        it++;
    }
    else if ( it->type == TokenType::IDENTIFIER )
    {
        result = new ExprNode;
        ExprNode* left = new ExprNode;
        ExprNode* right = nullptr;
        transaction.setMiddle (result);
        transaction.setLeft (left);
        left->setData (it->value);
        result->setData ("func eval");
        it++;

        right = getBrackets (it, end);
        if ( !right )
            return nullptr;
        result->setLeft (left);
        result->setRight (right);
    }
    transaction.commit();
    return result;
}

} /* namespace */


ExprNode* constructTree (std::list<Token>& tokens)
{
    auto it = tokens.begin ();
    auto end = tokens.end ();
    if ( it == end )
        return nullptr;

    return getGr0 (it, end);
}

} /* namespace Expresser */
