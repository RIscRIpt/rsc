#include "TL.h"

using namespace rsc;

TL::TL(unsigned char const *buffer)
    : tag_(buffer)
    , length_(buffer + tag_.size())
{}
