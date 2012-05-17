#! /usr/local/bin/racket
#lang racket

;;; Solution to Problem 400 - Unix ls

(define MAX-LEN 60)

(define (range n)
  (for/list ([i (in-range n)]) i))

(define (get-results input)
  (define (ls group)
    (define COLUMN-SEPARATOR "  ")
    (define col-sep-len (string-length COLUMN-SEPARATOR))
    (define empty-line (make-string MAX-LEN #\space))

    (define (build-output-lst sorted-lst ncols nrows colsize)
      (define (row-filter rownum row-lst)
        (define (in-row? idx)
          (= rownum (remainder idx nrows)))

        (define (row-indexes)
          (filter (lambda (x) (in-row? x)) (range (length row-lst))))

        (map (lambda (x) (list-ref row-lst x)) (row-indexes)))

      (define (merge-cols row colsize)
        (apply string-append (map (lambda (x) (substring (string-append x empty-line) 0 (+ colsize col-sep-len))) row)))

      (let ([output-lst (map (lambda (x) (row-filter x sorted-lst)) (range nrows))])
        (map (lambda (x) (merge-cols x colsize)) output-lst)))

    (define (item->string item)
      (cond [(symbol? item) (symbol->string item)]
            [(number? item) (number->string item)]
            [else (raise "invalid item")]))

    (let ([list-of-strings (map item->string group)])
      (let ([sorted-lst (sort list-of-strings string<?)]
            [max-file-len (apply max (map string-length list-of-strings))])
        (letrec ([ncols (floor (/ (+ MAX-LEN col-sep-len) (+ max-file-len col-sep-len)))]
                 [nrows (ceiling (/ (length group) ncols))])
          (build-output-lst sorted-lst ncols nrows max-file-len)))))

  (map ls input))


(define (show-results res)
  (define (print-separator)
    (let ([separator (string-append (make-string MAX-LEN #\-) "\n")])
      (display separator)))

  (define (show-result one-res)
    (print-separator)
    (display-lines one-res))

  (map show-result res)
  (display-lines '()))  ; added to avoid return value


(define (get-input)
  (define (parse-input in)
    (define (load-entries nentries entry-lst)
      (if (> nentries 0) (load-entries (- nentries 1) (append entry-lst (list (read in))))
        entry-lst))

    (let ([nentries (read in)])
      (if (eof-object? nentries)
        '()
        (cons (load-entries nentries '()) (parse-input in)))))

  (call-with-input-file "input.txt" 
                        (lambda (in) (parse-input in))))


(define (run)
  (show-results (get-results (get-input))))

(run)
