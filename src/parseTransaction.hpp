#ifndef H_F333D2BAD05746F0ACB19BD21C7923DA

#define H_F333D2BAD05746F0ACB19BD21C7923DA

#include "tokenizer.hpp"
#include "tree.hpp"

namespace Expresser
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

    explicit ParseTransaction (std::list<Token>::iterator& save);

    void setLeft (const ExprNode* l);
    void setRight (const ExprNode* r);
    void setMiddle (const ExprNode* m);
    void commit ();

    ~ParseTransaction ();

};    

} /* namespace Expresser */

#endif /* H_F333D2BAD05746F0ACB19BD21C7923DA */
