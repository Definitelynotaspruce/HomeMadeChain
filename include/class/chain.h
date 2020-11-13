#pragma once

#include "block.h"

class Chain
{
    public:

    Block currentBlock;
    
    Chain *previous = nullptr;
    Chain *next = nullptr;    

    

    Chain(Block block) {currentBlock = block;};

    Chain(Block block, Chain *previous) {currentBlock = block; this->previous = previous;};

    Chain* addToChain(Block block)
    {
        Chain* beforeNull = this;
        while(beforeNull->next != nullptr)
        {
            beforeNull = beforeNull->next;  // Reaching end of defined
        }
        //Addition of a new chain here
        beforeNull->next = new Chain(block, previous);
    }

    /* Chain* addToChain(Chain *tail, Block &block)
    {
        tail->next = new Chain(block, previous);
    } */
};