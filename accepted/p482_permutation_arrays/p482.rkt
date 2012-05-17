#! /usr/local/bin/racket
#lang racket

;;; Solution to Problem 482 - Permutation Arrays

(define (get-results input)
  (define (idx<? a b)
    (< (car a) (car b)))

  (let ([idx (car input)]
        [floats (last input)])
    (map cdr 
         (sort (map cons idx floats) 
               idx<?))))

(define (show-results res)
  (display-lines res))

(define (get-input)
  (define (parse-line)
    (let ([next (read)])
      (if (eof-object? next)
        '()
        (append (list next) (parse-line)))))

  (let ([input (call-with-input-file "input.txt" 
                                     (lambda (in) 
                                       (port->lines in)))])
    (map (lambda (x) (with-input-from-string x parse-line)) input)))

(define (run)
  (show-results (get-results (get-input))))

(run)

