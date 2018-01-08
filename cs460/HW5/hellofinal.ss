;;;Question 8
(define insert-last
(lambda (lst val)
  (if (list? lst)
      (append lst (list val))
      "First argument must be a list")))


(define (split-hlpr lst templst intlst alphalst)
;(set! templst '()) 
(if(not(null? lst))
     (begin 
       (if(number? (car lst))
	  (set! intlst (insert-last intlst  (car lst)))
	  (set! alphalst (insert-last alphalst  (car lst)))
	  )
       
       (set! templst (split-hlpr (cdr lst) templst intlst alphalst))
        ;(set! templst '())
	(set! intlst '()) 
	(set! alphalst '())
 
	)
     
     )
(if(null? lst)
  (begin
	(set! templst (cons intlst templst))
  	(set! templst (cons alphalst templst))
)
)
  templst
  
  )

(define (split lst)
  (define templst '())
  (define intlst '())
  (define alphalst '())
  (set! templst (split-hlpr lst templst intlst alphalst))
  
  ;(display templst)
  templst
  )

;;function to sum the list
(define (sum-helper elemList)
  (if
   (null? elemList)
   0
   (+ (car elemList) (sum-helper (cdr elemList)))
   )
  )
(define (summit lst)
(define answer 0)
(define templist '())
(if (list? lst)
    (begin
      (set! templist (split lst))
      (set! answer (sum-helper (car (cdr templist))))
      
      (if(not (null? (list-ref templist 0)))
	 (begin
	   (set! lst (list-ref templist 0))
	   (set! lst (cons answer lst))
	   )
	 (set! lst (cons answer '()))
	 )
      )
    
    (display "Must be a list"))
lst
)


(define llst '(a b c 1 2 3))
(split llst)
(summit llst)

(define llst '(1 2 3 4))
(summit llst)

(define llst '(a b cde abcd))
(summit llst)

(define llst 1)
(summit llst)
