#include "block.h"

class Chain
{
    public:
    Chain *previous = nullptr;
    Chain *next = nullptr;
    Chain *head = nullptr;

    Block currentBlock;

    Chain(Block block) {currentBlock = block;};
};