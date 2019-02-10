#include "purescript.h"

FOREIGN_BEGIN(Effect_Exception_Unsafe)

exports["unsafeThrow"] = [](const boxed& message) -> boxed {
    throw std::runtime_error(unbox<string>(message));
    return boxed();
};

FOREIGN_END
