#! /usr/local/bin/racket
#lang racket

;;; Solution to Problem 195 - Anagram

(define (permute lst)
  (if (= (length lst) 1)
    (list lst)
    (apply append (map (lambda (i) 
                         (map (lambda (j) (cons i j)) 
                              (permute (remove i lst)))) 
                       lst))))

(define (get-results input)
  (map (lambda (x) (map list->string x)) 
       (map remove-duplicates 
            (map permute 
                 (map (lambda (x) (sort x char<?)) 
                      (map string->list input))))))

(define (show-results res)
  (map display-lines res)
  (display-lines '()))    ; to avoid returning a value

(define (get-input)
  (call-with-input-file "input.txt" 
                        (lambda (in) 
                          (read-line in)   ; ignore first line containing # of lines to follow
                          (port->lines in))))

(define (run)
  (show-results (get-results (get-input))))

(run)
