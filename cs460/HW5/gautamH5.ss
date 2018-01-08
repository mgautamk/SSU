;;**********************************************************************************
;;Author: Mahesh Gautam
;;Instructor: Dr. Marcia Watts
;;Class: CS 460
;;Assignmenet: Homework 5 in scheme
;;;Description: This homework focuses on scheme tutorial
;;***********************************************************************************
; Question: 1
(car '(a b c)) ; result = a

(cdr '(a b c)) ; result = (b c)

(cons 'a '(b c)) ; result = (a b c)

(cons '(a b) '(c d)) ; result = ((a b) c d)

(car '((1 2) (3 4) (5 6))) ; result = (1 2)

(cdr '((1 2) (3 4) (5 6))) ; result = ((3 4) (5 6))

(cons '55 '((1 2) (3 4) (5 6))) ; result = (55 (1 2) (3 4) (5 6))

(cons '(5 5) '((1 2) (3 4) (5 6))) ; result = ((5 5) (1 2) (3 4) (5 6))

;Question 2, describe the function of each of the scheme functions above

;car:  This function extracts the 1st pointer from the cons cell. Cons cell
         ; is composed of two pointers, car is the first one

;cdr:  This functon extracts the 2nd pointer from the cons cell. Cons cell
         ; is composed of two pointers and car is the second one.

;cons: Cons cell is composed of two pointers, car and cdr. This function concatinates
         ; the elemensts in two pointers. Two pointers could be a list or an array.
         ; Cons could aslo adds an element to existing list or an array

;Question 3, Predict the output of the following scheme command:
(cons (car '(a b c))
      (cdr '(d e f)))
;prediction: (a, e, f), prediction was correct!

;Question 4
(define square
  (lambda (n)
    (* n n)))

;Question 5
(square 5) 
(square -200) 
(square 0.5) 
(square -1/2)

;Question 6
(define reciprocal
  (lambda (n)
    (if (= n 0)
	"oops!"
	(/ 1 n))))

;Question 7
(reciprocal 10) ; returns 1/10
(reciprocal 1/10) ; returns 10
(reciprocal 0) ; returns opps
(reciprocal (reciprocal 1/10)) ; returns 10

;Question 8
;1st command that uses both the reciprocal and the square procedures
;Redifined Procedure:
(define squareOfReciprocal
  (lambda (x)
    (square (reciprocal x))))

;Command:
(squareOfReciprocal 10)

;Result:1/100

;2nd command that uses both the reciprocal and the square procedures
;Redifined Procedure:
(define reciprocalOfSquare
  (lambda (x)
    (reciprocal (square x))))

;Command:
(reciprocalOfSquare 5)

;;;Result:1/25

;Question 9
(+ 2 5) ; result is 7
(* 1.5 2.3) ;result is  3.4499999999999997
(-(* 2 2/5)(/ 2 5)) ; result is 2/5

;Question 10
(display "Question 10\n")
;;;a 1.2 * (2 - 1/3) + -8.7:
(- (* 1.2 (- 2 1/3)) 8.7)
;;;b (2/3 + 2/9)/(5/1 -2/3):
(/(+(/ 2 3) (/ 2 9) (-(/ 5 1)(/ 2 3))))
;;;c 1 + 1/(2 + 1/(1 + 1/2)):
(+ 1 (/ 1 (+ 2 (/ 1 (+ 1 1/2)))))
;;;d 1 × -2 × 3 × -2 × 5 × -6 × 7:
(* 1 (* -2 (* 3 (* -2 (* 5 (* -6 7))))))  

;Question 11
;1st command that uses simple arithmetic operations and the reciprocal and square procedures.
;Redifined Procedure:
(define doubleReciprocalOfSquare
  (lambda (x)
    (* 2 (reciprocalOfSquare x))))

;Command:
(doubleReciprocalOfSquare 5) ;;;Result: 2/25
;2nd command that uses simple arithmetic operations and the reciprocal and square procedures.
;;;Redifined Procedure:
(define halfSquareOfReciprocal
  (lambda (x)
    (/ (squareOfReciprocal x) 2)))

;;;Command:
(halfSquareOfReciprocal 25)  ;;;Result: 1/1250

;;;Question 12
;;;atom: The term atom refers to a datum that is not a "cons" pair.

;;;primitive: In Scheme, primitive is the syntax and procedures you need to Implement
;;;              in the underlaying system. E.g. "if" is primitive syntax while "cond" is
;;;              called library syntax.

;;;lambda expression: In Scheme, all control and environment structures can be represented
;;;                      by lambda expressions and applications of lambdas.

;;;free variable: In Scheme, free variables are those variables that are defined outside
;;;                  the procedure, but referred to from inside it.

;;;top level definition:In Scheme, (define <variable> expression) has essentially the same effect
;;;                     as the assignement expression (set! <variable> <expression>) if variable
;;;                     is bound or not howeve the definition will bind variable to a new location
;;;                     before performing the assignment.

;;;predicate:A function that returns either a true or false.

;;;type predicate:In general, if a type predicate is true of a number then all higher type predicates
;;;               are also true for that number. Consequently, if a type predicate is false then all
;;;               lower type predicates are also false for that number.

;;;lexical scoping: The identifier is fixed at interpretation and or compilation in some region in the
;;;                 source code containing the identifiers declaration

;;;Question 13
;;;list? : When list is invoked with two arguments, it considers them to be two proposed elements
;;;        for a new two element list. List doesnt care whether the arguments are themselves lists,
;;;        words or anything else; it just creates a new list whose elements are the arguments.

;;;number? : Scheme provides the data type, number, which includes the integerm rational, real
;;;          and complex numbers.

;;;null? : Returns \#t if the {\bf obj}ect is the null list, (). It returns the null list, (),
;;;        if the object is anything else.

;;;cddddr: hese procedures are compositions of car and cdr, where for example caddr could be
;;;        defined by (define caddr (lambda (x) (car (cdr (cdr x)))))

;;;if: Evaluates test-expr. If it produces any value other than #f, then then-expr is evaluated,
;;;    and its results are the result for the if form.

;;;let: Let establishes local variable binding. Use let whenever the values are independent of
;;;     the variable and the order of evaluation is unimportant.  

;;;Question 14
(define insert-first
  (lambda (lst val)
    (if (list? lst)
	(cons val lst)
	"First argument must be a list")))

;;;test insert-first
(insert-first '(2 3) 1)

;;;Question 15
(define remove-first
  (lambda (lst)
    (cond
     ((not (list? lst)) "First argument must be a list")
     ((null? lst) "First argument must not be an empty list")
     (else (cdr lst)))))

;;;test remove-first
(remove-first '(1 2 3))

;;;Question 16
;;;What happens when you enter (insert-first 1 2)?
;;;It gives out a message "First argument should be a list".

;;;Question 17
;;;What happens when you enter (remove-first 1)?
;;;It gives out a message "Argument must be a list".

;;;Question 18
;;;It already throws informative error message

;;;Question 19
;;;It already throes informative error message

;;;Question 20
;;;List Copy - Formal argument should be a list
(define list-copy
  (lambda (lst)
    (cond
     ((not (list? lst)) "First argument must be a list")
     ((null? lst) lst)
     (else (cons (car lst) (list-copy(cdr lst)))))))

;;;Question 21
;;; Odd Copy - Formal argument should be a lost
(define odd-copy
  (lambda (lst)
    (cond
     ((not (list? lst)) "First argument must be a list")
     ((or (null? lst) (null? (cdr lst))) lst)
     (else (cons (car lst) (odd-copy (cddr lst)))))))

;;;Question 22
;;;Even copy - Formal argument must be a list
(define even-copy
  (lambda (lst)
    (cond
     ((not (list? lst)) "First argument must be a list")
     ((or (null? lst) (null? (cdr lst))) '())
     (else (cons (car (cdr lst)) (even-copy (cddr lst)))))))

;;;Question 23
;;;Insert-last, Formal arguments must be a list and the value to be inserted to the list
(define insert-last
  (lambda (lst val)
    (if (list? lst)
	(append lst (list val))
	"First argument must be a list")))

;;;Question 24
;;;Remove-last
(define remove-last
  (lambda (lst)
    (cond
     ((not (list? lst)) "First argument must be a list")
     ((or (null? lst) (null? (cdr lst))) '())
     (else (cons (car lst) (remove-last (cdr lst)))))))

;;;Test
(remove-last '(2 3 5))

;;;Question 25
;;;List-reverse
(define list-reverse
  (lambda (lst)
    (cond
     ((not (list? lst)) "First argument must be a list")
     ((null? lst) lst)
     (else (append (list-reverse (cdr lst)) (list (car lst)))))))
;;;Test
(list-reverse '(7 8 9))

;;;Question 26
;;;Square root
(define square-root (lambda (a)
   (exp (* 0.5 (log a)))))
;;;Test
(square-root 25)

