/**
 * \file testGameBoard.cpp
 * \author Leon So | macid: sol4
 * \date 2019-03-26
 */
#include "catch.h"
#include "CardStack.h"
#include "Stack.h"
#include "CardTypes.h"
#include "GameBoard.h"
#include <iostream>

#include <stdexcept>

TEST_CASE("general tests for GameBoard", "[GameBoard]")
{
  // Creating winning game board
  std::vector<CardT> d;
  for (int i = 1; i <= 2; i++)
  {
    for (unsigned int suit = 0; suit < 4; suit++)
    {
      for (RankT rank = KING; rank >= 10; rank--)
      {

        CardT n = {static_cast<SuitT>(suit), rank};
        d.push_back(n);
      }
    }
  }

  for (int i = 0; i <= 1; i++)
  {
    for (RankT rank = 9; rank >= 6; rank--)
    {
      CardT n = {static_cast<SuitT>(i), rank};
      d.push_back(n);
    }
  }

  for (unsigned int suit = 0; suit <= 3; suit++)
  {
    for (RankT rank = 9; rank >= ACE; rank--)
    {
      CardT n = {static_cast<SuitT>(suit), rank};
      d.push_back(n);
    }
  }

  for (unsigned int suit = 2; suit <= 3; suit++)
  {
    for (RankT rank = 9; rank >= ACE; rank--)
    {
      CardT n = {static_cast<SuitT>(suit), rank};
      d.push_back(n);
    }
  }

  for (unsigned int suit = 0; suit <= 1; suit++)
  {
    for (RankT rank = 5; rank >= ACE; rank--)
    {
      CardT n = {static_cast<SuitT>(suit), rank};
      d.push_back(n);
    }
  }

  BoardT board(d);
  BoardT board2(d);

  //Playing game til win

  for (int i = 0; i <= 1; i++)
  {
    for (int j = 1; j <= 5; j++)
    {
      board.deck_mv();
      board.waste_mv(Foundation, i);
    }
  }

  int f = 0;
  for (int i = 9; i >= 8; i--)
  {
    for (int j = 6; j <= 9; j++)
    {
      board.tab_mv(Foundation, i, f);
    }
    f = f + 1;
  }

  for (int i = 3; i >= 2; i--)
  {
    for (int j = ACE; j <= 9; j++)
    {
      board.deck_mv();
      board.waste_mv(Foundation, i);
    }
  }

  for (int i = 7; i >= 4; i--)
  {
    for (int j = 1; j <= 9; j++)
    {
      board.deck_mv();
      board.waste_mv(Foundation, i);
    }
  }

  f = 0;
  for (int i = 1; i >= 0; i--)
  {
    for (int j = 10; j <= KING; j++)
    {
      board.tab_mv(Foundation, i, f);
    }
    f = f + 1;
  }

  f = 2;
  for (int i = 2; i <= 7; i++)
  {
    for (int j = 10; j <= KING; j++)
    {
      board.tab_mv(Foundation, i, f);
    }
    f = f + 1;
  }

  SECTION("abnormal test for boardT"){
    std::vector<CardT> test;
    for (int i = 1; i <= 2; i++)
    {
      for (unsigned int suit = 0; suit < 4; suit++)
      {
        for (RankT rank = KING; rank >= 10; rank--)
        {

          CardT n = {static_cast<SuitT>(suit), rank};
          test.push_back(n);
        }
      }
    }

    REQUIRE_THROWS_AS(BoardT(test), std::invalid_argument);
  }

  SECTION("general test for boardT"){
    REQUIRE((
          BoardT(d).get_tab(0).top().r == 10
      &&  BoardT(d).get_tab(0).top().s == 0
      &&  BoardT(d).get_tab(1).top().r == 10
      &&  BoardT(d).get_tab(1).top().s == 1
      &&  BoardT(d).get_tab(2).top().r == 10
      &&  BoardT(d).get_tab(2).top().s == 2
      &&  BoardT(d).get_tab(3).top().r == 10
      &&  BoardT(d).get_tab(3).top().s == 3
      &&  BoardT(d).get_tab(4).top().r == 10
      &&  BoardT(d).get_tab(4).top().s == 0
      &&  BoardT(d).get_tab(5).top().r == 10
      &&  BoardT(d).get_tab(5).top().s == 1
      &&  BoardT(d).get_tab(6).top().r == 10
      &&  BoardT(d).get_tab(6).top().s == 2
      &&  BoardT(d).get_tab(7).top().r == 10
      &&  BoardT(d).get_tab(7).top().s == 3
      &&  BoardT(d).get_tab(8).top().r == 6
      &&  BoardT(d).get_tab(8).top().s == 0
      &&  BoardT(d).get_tab(9).top().r == 6
      &&  BoardT(d).get_tab(9).top().s == 1
      &&  BoardT(d).get_waste().size() == 0
      &&  BoardT(d).get_foundation(0).size() == 0
      &&  BoardT(d).get_foundation(1).size() == 0
      &&  BoardT(d).get_foundation(2).size() == 0
      &&  BoardT(d).get_foundation(3).size() == 0
      &&  BoardT(d).get_foundation(4).size() == 0
      &&  BoardT(d).get_foundation(5).size() == 0
      &&  BoardT(d).get_foundation(6).size() == 0
      &&  BoardT(d).get_foundation(7).size() == 0
      &&  BoardT(d).get_deck().size() == (104-40)
      &&  BoardT(d).get_deck().top().r == 1
      &&  BoardT(d).get_deck().top().s == ACE
    ));
  }

  SECTION("boundary test for get_foundation - empty foundation at start of game")
  {
    REQUIRE(BoardT(d).get_foundation(0).size() == 0);
  }

  SECTION("boundary test for get_waste - empty waste at start of game")
  {
    REQUIRE(BoardT(d).get_waste().size() == 0);
  }

  SECTION("boundary test for is_win_state - for completed winning board")
  {
    REQUIRE((
        board.is_win_state()));
  }

  SECTION("boundary test for valid_mv_exists - for completed winning board")
  {
    REQUIRE((
        board.valid_mv_exists() == false));
  }

  SECTION("abnormal test for tab_mv - for completed winning board, moving to tableau")
  {
    REQUIRE_THROWS_AS(board.tab_mv(Tableau, 0, 1), std::invalid_argument);
  }

  SECTION("abnormal test for tab_mv - for completed winning board, moving to foundation")
  {
    REQUIRE_THROWS_AS(board.tab_mv(Foundation, 0, 1), std::invalid_argument);
  }

  SECTION("abnormal test for waste_mv - for completed winning board, moving to tableau")
  {
    REQUIRE_THROWS_AS(board.waste_mv(Tableau, 1), std::invalid_argument);
  }

  SECTION("abnormal test for waste_mv - for completed winning board, moving to foundation")
  {
    REQUIRE_THROWS_AS(board.waste_mv(Foundation, 1), std::invalid_argument);
  }

  SECTION("abnormal test for deck_mv - for completed winning board")
  {
    REQUIRE_THROWS_AS(board.deck_mv(), std::invalid_argument);
  }

  SECTION("boundary test for is_valid_tab_mv - for completed winning board, moving to tableau")
  {
    REQUIRE(board.is_valid_tab_mv(Tableau, 0, 1) == false);
  }

  SECTION("boundary test for is_valid_tab_mv - for completed winning board, moving to foundation")
  {
    REQUIRE(board.is_valid_tab_mv(Foundation, 0, 1) == false);
  }

  SECTION("abnormal test 1 for is_valid_tab_mv - for completed winning board, out of range")
  {
    REQUIRE_THROWS_AS(board.is_valid_tab_mv(Foundation, 10, 1), std::out_of_range);
  }

  SECTION("abnormal test 2 for is_valid_tab_mv - for completed winning board, out of range")
  {
    REQUIRE_THROWS_AS(board.is_valid_tab_mv(Foundation, 1, 10), std::out_of_range);
  }

    SECTION("abnormal test 3 for is_valid_tab_mv - for completed winning board, out of range")
  {
    REQUIRE_THROWS_AS(board.is_valid_tab_mv(Tableau, 10, 1), std::out_of_range);
  }

  SECTION("abnormal test 4 for is_valid_tab_mv - for completed winning board, out of range")
  {
    REQUIRE_THROWS_AS(board.is_valid_tab_mv(Tableau, 1, 10), std::out_of_range);
  }

  SECTION("abnormal test for is_valid_waste_mv - for completed winning board, invalid argument")
  {
    REQUIRE_THROWS_AS(board.is_valid_waste_mv(Tableau, 10), std::invalid_argument);
  }

  SECTION("boundary test for is_valid_deck_mv - for completed winning board, invalid argument")
  {
    REQUIRE(board.is_valid_deck_mv() == false);
  }

  SECTION("boundary test for get_tab - for completed winning board, empty tab")
  {
    REQUIRE(board.get_tab(0).size() == 0);
  }

  SECTION("abnormal test for get_tab - for completed winning board, out of range")
  {
    REQUIRE_THROWS_AS(board.get_tab(10), std::out_of_range);
  }

  SECTION("boundary test for get_foundation - for completed winning board, empty tab")
  {
    REQUIRE((
          board.get_foundation(0).size() == 13
      &&  board.get_foundation(0).top().r == KING
      &&  board.get_foundation(0).top().s == Diamond
    ));
  }

  SECTION("abnormal test for get_foundation - for completed winning board, out of range")
  {
    REQUIRE_THROWS_AS(board.get_foundation(10), std::out_of_range);
  }

  SECTION("boundary test for get_deck - for completed winning board, empty deck")
  {
    REQUIRE(board.get_deck().size() == 0);
  }

  SECTION("boundary test for get_waste - for completed winning board, empty waste")
  {
    REQUIRE(board.get_waste().size() == 0);
  }

  SECTION("general test for is_win_state - not win state")
  {
    REQUIRE(board2.is_win_state() == false);
  }

  SECTION("general test for is_valid_deck_mv")
  {
    REQUIRE(board2.is_valid_deck_mv());
  }

  SECTION("general test for is_valid_waste_mv")
  {
    board2.deck_mv();
    REQUIRE(board2.is_valid_waste_mv(Foundation, 0));
  }

  SECTION("general test for is_valid_waste_mv")
  {
    board2.deck_mv();
    REQUIRE(board2.is_valid_waste_mv(Tableau, 0) == false);
  }

  SECTION("general test for is_valid_tab_mv")
  {
    REQUIRE(board2.is_valid_tab_mv(Tableau, 0, 1) == false);
  }

  SECTION("general test for is_valid_tab_mv")
  {
    board2.deck_mv();
    board2.waste_mv(Foundation, 0);
    board2.deck_mv();
    board2.waste_mv(Foundation, 0);
    board2.deck_mv();
    board2.waste_mv(Foundation, 0);
    board2.deck_mv();
    board2.waste_mv(Foundation, 0);
    board2.deck_mv();
    board2.waste_mv(Foundation, 0);
    REQUIRE(board2.is_valid_tab_mv(Foundation, 9, 0) == true);
  }

  SECTION("general test for get_foundation")
  {
    board2.deck_mv();
    board2.waste_mv(Foundation, 0);
    board2.deck_mv();
    board2.waste_mv(Foundation, 0);
    board2.deck_mv();
    board2.waste_mv(Foundation, 0);
    board2.deck_mv();
    board2.waste_mv(Foundation, 0);
    board2.deck_mv();
    board2.waste_mv(Foundation, 0);
    REQUIRE((
          board2.get_foundation(0).top().r == 5
      &&  board2.get_foundation(0).top().s == 1
      &&  board2.get_foundation(0).size() == 5
    ));
  }

  SECTION("boundary test for get_foundation - empty")
  {
    REQUIRE(board2.get_foundation(0).size() == 0);
  }

  SECTION("general test for tab_mv")
  {
    board2.deck_mv();
    board2.waste_mv(Foundation, 0);
    board2.deck_mv();
    board2.waste_mv(Foundation, 0);
    board2.deck_mv();
    board2.waste_mv(Foundation, 0);
    board2.deck_mv();
    board2.waste_mv(Foundation, 0);
    board2.deck_mv();
    board2.waste_mv(Foundation, 0);
    board2.tab_mv(Foundation, 9, 0);
    REQUIRE((
          board2.get_foundation(0).top().r == 6
      &&  board2.get_foundation(0).top().s == 1
    ));
  }

  SECTION("general test for get_tab")
  {
    REQUIRE((
          board2.get_tab(0).top().r == 10
      &&  board2.get_tab(0).top().s == 0
      &&  board2.get_tab(0).size() == 4
    ));
  }

  SECTION("general test for get_deck")
  {
    REQUIRE((
          board2.get_deck().top().r == ACE
      &&  board2.get_deck().top().s == 1
      &&  board2.get_deck().size() == (104-40)
    ));
  }

  SECTION("general test for get_waste")
  {
    board2.deck_mv();
    REQUIRE((
          board2.get_waste().top().r == ACE
      &&  board2.get_waste().top().s == 1
      &&  board2.get_waste().size() == 1
    ));
  }

  SECTION("general test for valid_mv_exists")
  {
    REQUIRE(board2.valid_mv_exists());
  }

  SECTION("abnormal test for waste_mv - empty waste at start of game")
  {
    REQUIRE_THROWS_AS(BoardT(d).waste_mv(Foundation, 0), std::invalid_argument);
  }
}