/**
 * \file testCardStack.cpp
 * \author Leon So | macid: sol4
 * \date 2019-03-26
 */
#include "catch.h"
#include "CardStack.h"
#include "Stack.h"
#include "CardTypes.h"

#include <stdexcept>

TEST_CASE( "tests for CardStackT", "[CardStackT]" ) {
  
  std::vector<CardT> cards;
  CardT card1 = {Heart,12};
  CardT card2 = {Spade,5};
  CardT card3 = {Club,3};
  cards.push_back(card1);
  cards.push_back(card2);
  cards.push_back(card3);

  CardStackT deck(cards);
  CardStackT emptyDeck = CardStackT();
  
  SECTION( "boundary test for CardStackT() - empty" ){
    REQUIRE(CardStackT().size()==0);
  }

  SECTION( "general test for CardStackT(cards)" ){
    REQUIRE(CardStackT(cards).size()==3);
  }

  SECTION( "general tests for top" ){
    REQUIRE(( 
          deck.top().r == card3.r
      &&  deck.top().s == card3.s
    ));
  }

  SECTION( "general tests for size" ){
    REQUIRE(deck.size() == 3);
  }
  
  SECTION( "general tests for push" ){
    CardT card4 = {Diamond, 2};
    deck = deck.push(card4);
    REQUIRE((
          deck.size() == 4
      &&  deck.top().r == card4.r
      &&  deck.top().s == card4.s
    ));
  }

  SECTION( "general tests for pop" ){
    deck = deck.pop();
    REQUIRE((
          deck.size() == 2
      &&  deck.top().r == card2.r
      &&  deck.top().s == card2.s
    ));
  }

  SECTION( "general tests for toSeq" ){
    REQUIRE((
          deck.toSeq()[0].r == cards[0].r
      &&  deck.toSeq()[0].s == cards[0].s
      &&  deck.toSeq()[1].r == cards[1].r
      &&  deck.toSeq()[1].s == cards[1].s
      &&  deck.toSeq()[2].r == cards[2].r
      &&  deck.toSeq()[2].s == cards[2].s
      &&  deck.toSeq().size() == cards.size()
    ));
  } 

  SECTION( "boundary test for size - size of empty stack" ){
    REQUIRE(emptyDeck.size() == 0);
  }

  SECTION( "boundary test for pop - pop from empty stack" ){
    REQUIRE_THROWS_AS(emptyDeck.pop(), std::out_of_range);
  }

  SECTION( "boundary test for top - top of empty stack" ){
    REQUIRE_THROWS_AS(emptyDeck.top(), std::out_of_range);
  }

  SECTION( "boundary test for push - push to empty stack" ){
    emptyDeck.push(card1);
    REQUIRE((
          emptyDeck.top().r == card1.r
      &&  emptyDeck.top().s == card1.s
    ));
  }

  SECTION( "boundary test for toSeq - toSeq for empty stack" ){
    REQUIRE((
        emptyDeck.toSeq().empty()
    ));
  }

}
