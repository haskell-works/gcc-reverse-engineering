{-# OPTIONS_GHC -mavx #-}
{-# OPTIONS_GHC -msse4 #-}
{-# LANGUAGE MagicHash #-}
{-# LANGUAGE UnboxedTuples #-}

import GHC.Exts

main :: IO ()
main = do
    case unpackFloatX4# (broadcastFloatX4# 1.5#) of
        (# a, b, c, d #) -> print (F# a, F# b, F# c, F# d)
