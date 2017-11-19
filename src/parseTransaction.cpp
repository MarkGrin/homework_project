#include "parseTransaction.hpp"

namespace Expresser
{

ParseTransaction::ParseTransaction (std::list<Token>::iterator& save)
    :
        backup  (save),
        it      (save),
        left    (nullptr),
        right   (nullptr),
        middle  (nullptr),
        success (false)
{}

void ParseTransaction::setLeft (const ExprNode* l)
{
    left = l;
}
void ParseTransaction::setRight (const ExprNode* r)
{
    right = r;
}
void ParseTransaction::setMiddle (const ExprNode* m)
{
    middle = m;
}
void ParseTransaction::commit ()
{
    success = true;
}

ParseTransaction::~ParseTransaction ()
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

} /* namespace Expresser */
