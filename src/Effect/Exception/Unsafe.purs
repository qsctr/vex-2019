module Effect.Exception.Unsafe
    ( unsafeThrow
    ) where

foreign import unsafeThrow :: forall a. String -> a
