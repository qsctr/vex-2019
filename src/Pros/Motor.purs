module Pros.Motor
    ( Motor
    ) where

import Pros.Port

foreign import data Motor :: Type

foreign import newMotor :: Port -> Gearset -> Boolean -> EncoderUnits -> Motor

foreign import data Gearset :: Type

foreign import gearset36 :: Gearset
foreign import gearset18 :: Gearset
foreign import gearset6 :: Gearset

foreign import data EncoderUnits :: Type

foreign import degrees :: EncoderUnits
foreign import rotations :: EncoderUnits
foreign import counts :: EncoderUnits
