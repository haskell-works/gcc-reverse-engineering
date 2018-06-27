{-# OPTIONS_GHC -mavx #-}
{-# OPTIONS_GHC -msse4 #-}
{-# LANGUAGE MagicHash #-}
{-# LANGUAGE UnboxedTuples #-}

import GHC.Exts

main :: IO ()
main = do
 case unpackInt64X4# (broadcastInt64X4# 1#) of
   (# a, b, c, d #) -> print (I# a)
