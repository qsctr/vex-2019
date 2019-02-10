#include "purescript.h"

FOREIGN_BEGIN(Effect_Exception)

exports["throw"] = [](const boxed& message) -> boxed {
    return [=]() -> boxed {
        throw std::runtime_error(unbox<string>(message));
        return boxed();
    };
};

FOREIGN_END
