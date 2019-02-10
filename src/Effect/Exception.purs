module Effect.Exception
    ( throw
    ) where

import Effect

foreign import throw :: forall a. String -> Effect a
