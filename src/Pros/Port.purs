module Pros.Port
    ( Port
    , mkPort
    ) where

import Effect.Exception.Unsafe
import Prelude

newtype Port = Port Int

mkPort :: Int -> Port
mkPort x
    | x >= 1, x <= 21 = Port x
    | otherwise = unsafeThrow $ "Invalid port: " <> show x
