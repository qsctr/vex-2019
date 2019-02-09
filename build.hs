-- stack --resolver lts-11.22 script
{-# LANGUAGE OverloadedStrings #-}

import Turtle
import qualified Data.Text as T

main = do
    name <- either id id . toText . basename <$> pwd
    echo $ unsafeTextToLine $ "Building project " <> name
    args <- arguments
    let build = do
            echo "[build]"
            cptree "cpp" "output/src"
            cptree "psn-runtime" "output/src"
            procs "make" ["-f", "purs.mk"] empty
            procs "prosv5" ["make"] empty
        upload = do
            echo "[upload]"
            procs "prosv5" ["upload", "--name", name] empty
        checkConnected = do
            echo "[check connected]"
            (exitCode, output) <- procStrict "prosv5" ["v5", "status"] empty
            pure $ exitCode == ExitSuccess
                && "Connected to V5 on" `T.isPrefixOf` output
        clean = do
            echo "[clean]"
            procs "make" ["-f", "purs.mk", "clean"] empty
            procs "prosv5" ["make", "clean"] empty
    if null args then do
        build
        connected <- checkConnected
        if connected then do
            echo "V5 connected, uploading"
            upload
        else do
            echo "No V5 connected, not uploading"
    else do
        when ("clean" `elem` args) clean
        when ("build" `elem` args) build
        when ("upload" `elem` args) upload
