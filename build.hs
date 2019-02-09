-- stack --resolver lts-11.22 script --package turtle
{-# LANGUAGE OverloadedStrings #-}

import Turtle

main = do
    args <- arguments
    when ("clean" `elem` args) $ do
        echo "clean"
        procs "make" ["-f", "purs.mk", "clean"] empty
        procs "prosv5" ["make", "clean"] empty
    when ("build" `elem` args || null args) $ do
        echo "build"
        cptree "cpp" "output/src"
        cptree "psn-runtime" "output/src"
        procs "make" ["-f", "purs.mk"] empty
        procs "prosv5" ["make"] empty
    when ("upload" `elem` args) $ do
        echo "upload"
        procs "prosv5" ["upload"] empty
