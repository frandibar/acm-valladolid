#! /usr/local/bin/racket
#lang racket

;;; Solution to Problem 673 - Parentheses Balance

(define (paren-balanced? parens-lst)
  (define (balance left right)
    (define (open-parens? p)
      (or (eq? p #\() (eq? p #\[)))

    (define (paren-pair? a b)
      (cond [(eq? a #\)) (eq? b #\()]
            [(eq? a #\() (eq? b #\))]
            [(eq? a #\]) (eq? b #\[)]
            [(eq? a #\[) (eq? b #\])]
            [else false]))

    (let ([current (car right)])
      (if (empty? (cdr right)) 
        (and (= (length left) 1) 
             (paren-pair? (last left) current))
        (if (open-parens? current)
          (balance (append left (list current)) (cdr right))
          (if (and (not (empty? left)) 
                   (paren-pair? (last left) current))
            (balance (take left (- (length left) 1)) (cdr right))
            false)))))

  (if (or (odd? (length parens-lst)) 
          (empty? parens-lst))
    false
    (balance '() parens-lst)))


(define (get-results input)
  (map paren-balanced? (map string->list input)))

(define (show-results res)
  (display-lines (map (lambda (x) (if x "Yes" "No")) res)))

(define (get-input)
  (call-with-input-file "input.txt" 
                        (lambda (in) 
                          (read-line in)   ; ignore first line containing # of lines to follow
                          (port->lines in))))

(define (run)
  (show-results (get-results (get-input))))

(run)
