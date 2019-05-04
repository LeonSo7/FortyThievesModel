/**
 * \file CardTypes.h
 * \author Leon So | macid: sol4
 * \date 2019-03-26
 */
#ifndef A3_CARD_TYPES_H_
#define A3_CARD_TYPES_H_

/**
 * \brief Describes a natural number.
 */
typedef unsigned int nat;

/**
 * \brief Describes the rank of a card.
 */
typedef unsigned short int RankT;

/**
 * \brief RankT for an Ace.
 */
#define ACE    1

/**
 * \brief RankT for an Jack.
 */
#define JACK   11

/**
 * \brief RankT for a Queen.
 */
#define QUEEN  12

/**
 * \brief RankT for a King.
 */
#define KING   13

/**
 * \brief Total number of cards
 */
#define TOTAL_CARDS 104

/**
 * \brief Describes the category of a stack of cards
 */
enum CategoryT {Tableau, Foundation, Deck, Waste};

/**
 * \brief Describes the suit of a card
 */
enum SuitT {Heart, Diamond, Club, Spade};

/**
 *  \brief Describes a card
 */
struct CardT{
    SuitT s;
    RankT r;
};

#endif
