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
