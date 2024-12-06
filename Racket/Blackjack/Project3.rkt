#lang racket
; Michael Mowad
; Project 3
; Functions for usage in a digital BlackJack game 


; global variabels
(define faces `(2 3 4 5 6 7 8 9 J Q K A))
(define suits `(Clubs Diamonds Hearts Spades))

; (make-card face suit)
; Generates a linked pair given a face and suit value
(define make-card
  (lambda (face suit)
    (cons face suit)))

; (make-deck)
; Generates a list of a full deck of cards
(define make-deck
  (lambda ()
    ; Helper function to recursively go through list of faceas and suits and create card
      (letrec ([make-deck-card (lambda (facesList suitsList)
                               (cond
                                 ; Base case: create last card
                                 [(and (empty? (rest suitsList)) (empty? (rest facesList))) (list (make-card (first facesList) (first suitsList)))]
                                 ; If face list is empty, call with replenished faces and rest of suitlist
                                 [(empty? facesList) (make-deck-card faces (rest suitsList))]
                                 ; Else add card to list
                                 [else (cons (make-card (first facesList) (first suitsList)) (make-deck-card (rest facesList) suitsList))]))])
        ; Call recursive function
        (make-deck-card faces suits))))

; (eval-hand hand)
; Determines best case value of cards in hand
(define eval-hand
  (lambda (hand)
    ; Helper function recursively goes through hand and sums card values
   (letrec ([cardvalue (lambda (hand acehigh)
                          (cond
                            [(empty? hand) 0]
                            [(or (equal? (car (first hand)) `J) (equal? (car (first hand)) 'Q) (equal? (car (first hand)) 'K)) (+ 10 (cardvalue (rest hand) acehigh))]
                            [(and (equal? (car (first hand)) `A) acehigh) (+ 11 (cardvalue (rest hand) acehigh))]
                            [(equal? (car (first hand)) `A) (+ 1 (cardvalue (rest hand) acehigh))]
                            [else (+ (car (first hand)) (cardvalue (rest hand) acehigh))]))]) 

     ; If sum when ace is counted high is greater than 21, count ace low instead
    (if (>= 21 (cardvalue hand #t))
        (cardvalue hand #t)
        (cardvalue hand #f)
    ))))

; (deal! deck)
; Deals new hand with top two cards of deck
(define deal!
  (lambda (deckList)

    ; Remove top two cards from  global deck
    (set! deck (rest (rest deck)))
    ; Add top two cards from parameter deck to list and return
    (list (first deckList) (first (rest deckList)))))

;(hit! hand deck)
; Adds one card from top of deck to hand
(define hit!
  (lambda (handList deckList)

    (set! deck (rest deck))

    (append handList (list (first deckList)))
))

; (show-hand hand type string)
; Displays either full or partial hand and string
(define show-hand
  (lambda (handList type string)

    (display string)
    (cond
        [(equal? type `Full) handList]
        [else (append (list `*****) (rest handList))])))
      
































