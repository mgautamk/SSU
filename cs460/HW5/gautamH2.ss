q;;;Question 6
(define reciprocal
  (lambda (n)
    (if (= n 0)
	"oops!"
	(/ 1 n))))

;;;Question 7
(reciprocal 10) ;;; returns 1/10 
(reciprocal 1/10) ;;; returns 10
(reciprocal 0) ;;; returns opps
reciprocal (reciprocal 1/10) ;;; returns 10


;;;Question 8


