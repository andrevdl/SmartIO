#include "SIOTokenWalker.h"

inline SIOToken* SIOTokenWalker::_pop()
{
    return (*it++);
}

inline SIOToken* SIOTokenWalker::_peek()
{
    return (*it);
}

SIOTokenWalker::SIOTokenWalker(SIOTokenizer* tokenizer)
{
    this->tokenizer = tokenizer;
    begin = tokenizer->begin();
    end = tokenizer->end();

    it = begin;
}

SIOToken* SIOTokenWalker::pop()
{
    return eof() ? nullptr : _pop();
}

SIOToken* SIOTokenWalker::peek()
{
    return eof() ? nullptr : _peek();
}

bool SIOTokenWalker::rollback()
{
    if (!eof())
    {
        --it;
        return true;
    }
    return false;
}

bool SIOTokenWalker::eof()
{
    return it == end;
}

SIOTokenType SIOTokenWalker::pop_type()
{
    return eof() ? SIOTokenType::EMPTY : _pop()->type;
}

SIOTokenType SIOTokenWalker::peek_type()
{
    return eof() ? SIOTokenType::EMPTY : _peek()->type;
}
