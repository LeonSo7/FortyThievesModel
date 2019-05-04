/**
 * \file GameBoard.h
 * \author Leon So | macid: sol4
 * \date 2019-03-26
 */
#ifndef A3_GAME_BOARD_H_
#define A3_GAME_BOARD_H_

#include "CardTypes.h"
#include "CardStack.h"
#include <functional>

/**
 * Describes a sequence of card stacks
 */
typedef std::vector<CardStackT> SeqCrdStckT;

/**
 * \brief BoardT abstract data type representing a gameboard of forty thieves
 */
class BoardT
{
private:
  //State variables
  std::vector<CardT> deck;
  SeqCrdStckT T;
  SeqCrdStckT F;
  CardStackT D;
  CardStackT W;

  bool two_decks(SeqCrdStckT T, SeqCrdStckT F, CardStackT D, CardStackT W);
  nat cnt_cards_seq(SeqCrdStckT S, std::function<bool(CardT)> f);
  nat cnt_cards_stack(CardStackT s, std::function<bool(CardT)> f);
  nat cnt_cards(SeqCrdStckT T, SeqCrdStckT F, CardStackT D, CardStackT W, std::function<bool(CardT)> f);
  SeqCrdStckT init_seq(nat n) const;
  SeqCrdStckT tab_deck(std::vector<CardT> deck) const;
  bool is_valid_pos(CategoryT c, nat n) const;
  bool valid_tab_tab(nat n0, nat n1) const;
  bool valid_tab_foundation(nat n0, nat n1) const;
  bool valid_waste_tab(nat n) const;
  bool valid_waste_foundation(nat n) const;
  bool tab_placeable(CardT c, CardT d) const;
  bool foundation_placeable(CardT c, CardT d) const;

public:
  /**
   * \brief Empty constructor for BoardT
   */
  BoardT();

  /**
   * \brief Constructor for BoardT
   */
  BoardT(std::vector<CardT> deck);

  /**
   * \brief Checks if a valid move exists for moving a card from tableau to another category or tableau
   * \param c - the category we want to move a card from tableau to
   * \param n0 - the index of the tableau we want to move from
   * \param n1 - the index of the category we want to move to
   * \return boolean value representing whether a valid move from tableau exists
   */
  bool is_valid_tab_mv(CategoryT c, nat n0, nat n1) const;

  /**
   * \brief Checks if a valid move exists for moving a card from waste to another category or tableau
   * \param c - the category we want to move a card to
   * \param n - the index of the category we want to move to
   * \return boolean value representing whether a valid move from waste exists
   */
  bool is_valid_waste_mv(CategoryT c, nat n) const;

  /**
   * \brief Checks if a valid move exists for moving a card from deck to waste
   * \return boolean value representing whether a valid move from deck exists
   */
  bool is_valid_deck_mv() const;

  /**
   * \brief Moves a card from a tableau to another tableau or foundation
   * \param c - the category we want to move a card from tableau to
   * \param n0 - the index of the tableau we want to move from
   * \param n1 - the index of the category we want to move to
   */
  void tab_mv(CategoryT c, nat n0, nat n1);

  /**
   * \brief Moves a card from waste to another category or tableau
   * \param c - the category we want to move a card to
   * \param n - the index of the category we want to move to
   */
  void waste_mv(CategoryT c, nat n);

  /**
   * \brief Moves a card from deck to waste
   */
  void deck_mv();

  /**
   * \brief Accessor - Gets the stack of cards from the tableau at index i
   * \param i - the index of the tableau we want to get
   * \return a stack of cards from the tableau at index i
   */
  CardStackT get_tab(nat i) const;

  /**
   * \brief Accessor - Gets the stack of cards from the foundation at index i
   * \param i - the index of the foundation we want to get
   * \return the stack of cards from the foundation at index i
   */
  CardStackT get_foundation(nat i) const;

  /**
   * \brief Accessor - Gets the deck
   * \return the stack of cards which is the deck
   */
  CardStackT get_deck() const;

  /**
   * \brief Accessor - Gets the waste
   * \return the stack of cards which is the waste
   */
  CardStackT get_waste() const;

  /**
   * \brief Checks if a valid move exists
   * \return a boolean value representing whether a move exists
   */
  bool valid_mv_exists() const;

  /**
   * \brief Checks whether the game has been won
   * \return a boolean value representing whether the game has been won
   */
  bool is_win_state() const;
};

#endif
