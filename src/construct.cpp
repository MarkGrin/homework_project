#include "construct.hpp"

namespace Expresser
{

namespace
{

class ParseTransaction
{
    ParseTransaction () = delete;
    ParseTransaction (const ParseTransaction&) = delete;
    ParseTransaction (ParseTransaction&&) = delete;
    ParseTransaction& operator = (const ParseTransaction&) = delete;
    ParseTransaction& operator = (ParseTransaction&&) = delete;

    std::list<Token>::iterator backup;
    std::list<Token>::iterator& it;
    const ExprNode* left;
    const ExprNode* right;
    const ExprNode* middle;

    bool success;

    public:

    ParseTransaction (std::list<Token>::iterator& save)
        :
            backup  (it),
            it      (save),
            success (false)
    {}

    void setLeft (const ExprNode* l)
    {
        left = l;
    }
    void setRight (const ExprNode* r)
    {
        right = r;
    }
    void setMiddle (const ExprNode* m)
    {
        middle = m;
    }
    void commit ()
    {
        success = true;
    }

    ~ParseTransaction ()
    {
        if ( success )
            return ;
        it = backup;
        if ( left )
            delete left;
        if ( right )
            delete right;
        if ( middle )
            delete middle;
    }

};    

ExprNode* getGr0 (std::list<Token>::iterator& it, std::list<Token>::iterator end, std::string& error);
ExprNode* getExpression (std::list<Token>::iterator& it, std::list<Token>::iterator end, std::string& error);
ExprNode* getAddSub (std::list<Token>::iterator& it, std::list<Token>::iterator end, std::string& error);
ExprNode* getBrackets (std::list<Token>::iterator& it, std::list<Token>::iterator end, std::string& error);
ExprNode* getLeaf (std::list<Token>::iterator& it, std::list<Token>::iterator end, std::string& error);

ExprNode* getGr0 (std::list<Token>::iterator& it, std::list<Token>::iterator end, std::string& error)
{
    return getExpression (it, end, error);
}

ExprNode* getExpression (std::list<Token>::iterator& it, std::list<Token>::iterator end, std::string& error)
{
    return getAddSub (it, end, error);
}

ExprNode* getAddSub (std::list<Token>::iterator& it, std::list<Token>::iterator end, std::string& error)
{
    if (it == end)
        return nullptr;

    ParseTransaction transaction (it);

    ExprNode* left;
    ExprNode* right;
    ExprNode* result;

    left = getBrackets (it, end, error);
    if ( !left )
        left = getLeaf (it, end, error);
    if ( !left )
        return nullptr;

    transaction.setLeft (left);

    if ( it == end )
        return nullptr;

    if ( it->type != TokenType::ADD && it->type != TokenType::SUB)
        return error += ", expected +/-:", nullptr;

    transaction.setMiddle(result = new ExprNode);
    if ( it->type == TokenType::ADD )
        result->setData ("+");
    else
        result->setData ("-");

    it++;

    right = getBrackets (it, end, error);
    if ( !right )
        right = getLeaf (it, end, error);
    if ( !right )
        return nullptr;


    result->setLeft (left);
    result->setRight (right);

    transaction.commit();
    return result;
}

ExprNode* getBrackets (std::list<Token>::iterator& it, std::list<Token>::iterator end, std::string& error)
{
    if ( it->type == TokenType::BRACKET_OPEN )
    {
        ParseTransaction transaction(it);
        it++;
        ExprNode* result = getExpression (it, end, error);
        transaction.setMiddle (result);
        if ( it == end || it->type != TokenType::BRACKET_CLOSE )
        {
            error += ", bracket mismatch";
            return nullptr;
        }
        return result;
    }
    else return nullptr;
 
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
