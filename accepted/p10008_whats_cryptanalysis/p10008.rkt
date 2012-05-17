#! /usr/local/bin/racket
#lang racket

;;; Solution to Problem 10008 - What's Cryptanalysis?

(define (count-occurences item lst)
  (length (filter (lambda (x) (eq? item x)) lst)))

(define (get-results input)
  (define (occurence>? x y)
    (if (= (last x) (last y)) 
      (char<? (first x) (first y))
      (> (last x) (last y))))

  (letrec ([all-chars (filter char-alphabetic? (string->list (string-upcase input)))]
           [set-of-chars (remove-duplicates all-chars)]
           [unsorted (map (lambda (x) (list x (count-occurences x all-chars))) set-of-chars)])
    (sort unsorted occurence>?)))

(define (show-results res)
  (for-each (lambda (x) 
              (display (string-append (string (first x)) " " (number->string (last x)) "\n")))
            res))

(define (get-input)
  (call-with-input-file "input.txt" 
                        (lambda (in) 
                          (read-line in)   ; ignore first line containing # of lines to follow
                          (port->string in))))

(define (run)
  (show-results (get-results (get-input))))

(run)
