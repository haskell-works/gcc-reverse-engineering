{-# OPTIONS_GHC -mavx #-}
{-# OPTIONS_GHC -msse4 #-}
{-# LANGUAGE MagicHash #-}
{-# LANGUAGE UnboxedTuples #-}

import GHC.Exts

main :: IO ()
main = do
 case unpackInt64X4# (packInt64X4# (# 1#, 2#, 3#, 4# #)) of
   (# a, b, c, d #) -> print (I# a)
