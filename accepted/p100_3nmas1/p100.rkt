#! /usr/local/bin/racket
#lang racket

;;; Solution to Problem 100 - The 3n + 1 problem

(define (range a b)
  (for/list ([i (in-range a (+ 1 b))]) i))

(define (get-results input)
  (define (cycles n)
    (let loop ([i n]
               [ncycles 1])
      (if (= i 1)
        ncycles
        (let ([new-i (if (odd? i) 
                       (+ (* 3 i) 1)
                       (/ i 2))])
          (loop new-i (+ ncycles 1))))))

  (define (max-cycles from-to)
    (let ([i (first from-to)]
          [j (second from-to)])
      (let ([a (min i j)]
            [b (max i j)])
        (apply max (map cycles (range a b))))))

  (map (lambda (x) (append x (list (max-cycles x)))) input))


(define (show-results res)
  ; converts tuple (1 2 3) to string "1 2 3"
  (define (tuple-to-string tuple)
    (let ([str-tuple (map number->string tuple)])
      (string-append (first str-tuple) " " (second str-tuple) " " (third str-tuple))))

  (display-lines (map tuple-to-string res)))


(define (get-input)
  (define (parse-input in)
    ; converts input line to tuple (i j)
    (define (parse-line line)
      (define (parse-i-j)
        (list (read) (read)))
      (with-input-from-string line parse-i-j))

    ; necessary to ignore empty lines from input
    (define (eof-free? lst)
      (> (length lst) (length (filter eof-object? lst))))

    (let ([dirty-input (port->lines in)])
      (filter eof-free? (map (lambda (x) (parse-line x)) dirty-input))))

  (call-with-input-file "input.txt" 
                        (lambda (in) (parse-input in))))

(define (run)
  (show-results (get-results (get-input))))

(run)
