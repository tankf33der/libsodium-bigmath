(seed (in "/dev/urandom" (rd 8)))
(de randL (N)
   (make (do N (link (rand 0 255)))) )
(de endian (L) # little
   (apply
      |
      (mapcar >> (0 -8 -16 -24) L) ) )
# only 8, 12, 24
(de soda-inc-asm (Lst)
   (let (Len (length Lst)  R)
      (native
         "libsobig.so.0"
         "sodium_inc_asm"
         NIL
         (cons 'R (cons Len 'B Len) Lst)
         Len )
      R ) )
(de soda-inc (Lst)
   (let (Len (length Lst) R)
      (native
         "libsobig.so.0"
         "sodium_inc"
         NIL
         (cons 'R (cons Len 'B Len) Lst)
         Len )
      R ) )
# only 8, 12, 24
(de soda-add-asm (A B)
   (let (Len (length A)  R)
      (native
         "libsobig.so.0"
         "sodium_add_asm"
         NIL
         (cons 'R (cons Len 'B Len) A)
         (cons NIL (cons Len) B)
         Len )
      R ) )
(de soda-add (A B)
   (let (Len (length A)  R)
      (native
         "libsobig.so.0"
         "sodium_add"
         NIL
         (cons 'R (cons Len 'B Len) A)
         (cons NIL (cons Len) B)
         Len )
      R ) )
# only 64
(de soda-sub-asm (A B)
   (let (Len 64  R)
      (native
         "libsobig.so.0"
         "sodium_sub_asm"
         NIL
         (cons 'R (cons Len 'B Len) A)
         (cons NIL (cons Len) B)
         Len )
      R ) )
(de soda-sub (A B)
   (let (Len 64  R)
      (native
         "libsobig.so.0"
         "sodium_sub"
         NIL
         (cons 'R (cons Len 'B Len) A)
         (cons NIL (cons Len) B)
         Len )
      R ) )
# 4 only!
(de soda-compare (A B)
   (native
      "libsodium.so"
      "sodium_compare"
      'I
      (cons NIL (4) A)
      (cons NIL (4) B)
      4 ) )
(de comp (A B)
   (cond
      ((> A B) 1)
      ((< A B) -1)
      (T 0) ) )
