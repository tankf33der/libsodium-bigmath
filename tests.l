`(== 64 64)
(load "functions.l")

#{

# inc, add
(for A (list 8 12 24)
   (for N (range 0 255)
      (let Lst (need A N)
         (test (soda-inc Lst) (soda-inc-asm Lst))
         (test (soda-add Lst Lst) (soda-add-asm Lst Lst)) ) ) )
(for A (list 8 12 24)
   (do 10000
      (let (Lst (randL A)  Lst2 (randL A))
         (test (soda-inc Lst) (soda-inc-asm Lst))
         (test (soda-add Lst Lst2) (soda-add-asm Lst Lst2)) ) ) )
# sub
(do 10000
   (let (Lst (randL 64)  Lst2 (randL 64))
      (test
         (soda-sub-asm Lst Lst2)
         (soda-sub Lst Lst2) ) ) )
}#

(do 10240000000000
   (let
      (L1 (randL 4)
         L2 (randL 4)
         N1 (endian L1)
         N2 (endian L2) )
      (test
         (soda-compare L1 L2)
         (comp N1 N2) ) ) )
(msg 'ok)
(bye)
