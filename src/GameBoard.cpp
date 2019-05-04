/**
 * \file GameBoard.cpp
 * \author Leon So | macid: sol4
 * \date 2019-03-26
 */

#include "CardTypes.h"
#include "CardStack.h"
#include "GameBoard.h"
#include "Stack.h"
#include <iostream>

#include <vector>
#include <stdexcept>
#include <functional>

// BoardT::BoardT() {}

BoardT::BoardT(std::vector<CardT> deck):deck()
{
    if (two_decks(init_seq(10), init_seq(8), CardStackT(deck), CardStackT()) == 0)
        throw std::invalid_argument("Invalid argument");

    std::vector<CardT> deckTab(deck.cbegin(), deck.cbegin() + 39 + 1);
    std::vector<CardT> deckDeck(deck.cbegin() + 40, deck.cbegin() + 103 + 1);

    this->T = tab_deck(deckTab);
    this->F = init_seq(8);
    this->D = CardStackT(deckDeck);
    this->W = CardStackT();
}

//comment here tmr
bool BoardT::is_valid_tab_mv(CategoryT c, nat n0, nat n1) const
{
    if (c == Tableau)
    {
        if ((is_valid_pos(Tableau, n0) && is_valid_pos(Tableau, n1)) == 0)
            throw std::out_of_range("Out of range");

        return valid_tab_tab(n0, n1);
    }
    else if (c == Foundation)
    {
        if ((is_valid_pos(Tableau, n0) && is_valid_pos(Foundation, n1)) == 0)
            throw std::out_of_range("Out of range");

        return valid_tab_foundation(n0, n1);
    }
    return false; //if c == Deck or c == Waste
}

bool BoardT::is_valid_waste_mv(CategoryT c, nat n) const
{
    if (this->W.size() == 0)
        throw std::invalid_argument("Invalid argument");

    if (c == Tableau)
    {
        if (is_valid_pos(Tableau, n) == 0)
            throw std::out_of_range("Out of range");

        return valid_waste_tab(n);
    }
    else if (c == Foundation)
    {
        if (is_valid_pos(Foundation, n) == 0)
            throw std::out_of_range("Out of range");

        return valid_waste_foundation(n);
    }
    return false; //if c == Deck or c == Waste
}

bool BoardT::is_valid_deck_mv() const
{
    return (this->D.size() > 0);
}

void BoardT::tab_mv(CategoryT c, nat n0, nat n1)
{
    if (is_valid_tab_mv(c, n0, n1) == 0)
        throw std::invalid_argument("Invalid argument");

    if (c == Tableau)
    {
        this->T[n1] = this->T[n1].push(this->T[n0].top());
        this->T[n0] = this->T[n0].pop();
    }
    else if (c == Foundation)
    {
        this->F[n1] = this->F[n1].push(this->T[n0].top());
        this->T[n0] = this->T[n0].pop();
    }
}

void BoardT::waste_mv(CategoryT c, nat n)
{
    if (is_valid_waste_mv(c, n) == 0)
        throw std::invalid_argument("Invalid argument");

    if (c == Tableau)
    {
        this->T[n] = this->T[n].push(this->W.top());
        this->W = this->W.pop();
    }
    else if (c == Foundation)
    {
        this->F[n] = this->F[n].push(this->W.top());
        this->W = this->W.pop();
    }
}

void BoardT::deck_mv()
{
    if (is_valid_deck_mv() == 0)
        throw std::invalid_argument("Invalid argument");
    this->W = this->W.push(this->D.top());
    this->D = this->D.pop();
}

CardStackT BoardT::get_tab(nat i) const
{
    if (is_valid_pos(Tableau, i) == 0)
        throw std::out_of_range("Out of range");

    return this->T[i];
}

CardStackT BoardT::get_foundation(nat i) const
{
    if (is_valid_pos(Foundation, i) == 0)
        throw std::out_of_range("Out of range");

    return this->F[i];
}

CardStackT BoardT::get_deck() const
{
    return this->D;
}

CardStackT BoardT::get_waste() const
{
    return this->W;
}

bool BoardT::valid_mv_exists() const
{
    for (int i = 0; i < 10; i++)
    {

        for (int j = 0; j < 10; j++)
        {
            if (is_valid_pos(Tableau, i) && is_valid_pos(Tableau, j) && is_valid_tab_mv(Tableau, i, j))
                return true;
        }

        for (int j = 0; j < 8; j++)
        {
            if (is_valid_pos(Tableau, i)) {
                if (is_valid_pos(Foundation, j)){
                    if(is_valid_tab_mv(Foundation, i, j)){
                        return true;
                    }
                }
            }
        }
    }

    for (int i = 0; i < 10; i++)
    {
        if (is_valid_pos(Tableau, i) && this->W.size() != 0 && is_valid_waste_mv(Tableau, i))
        {
            return true;
        }
    }

    for (int i = 0; i < 8; i++)
    {
        if (is_valid_pos(Foundation, i) && this->W.size() != 0 && is_valid_waste_mv(Foundation, i))
        {
            return true;
        }
    }
    return (is_valid_deck_mv());
}

bool BoardT::is_win_state() const
{
    for (int i = 0; i < 8; i++)
    {
        if ((this->F[i].size() > 0 && this->F[i].top().r == KING) == 0)
            return false;
    }

    return true;
}

//Private methods
nat BoardT::cnt_cards(SeqCrdStckT T, SeqCrdStckT F, CardStackT D, CardStackT W, std::function<bool(CardT)> f)
{
    nat sumCards = 0;
    sumCards = sumCards + cnt_cards_seq(T, f);
    sumCards = sumCards + cnt_cards_seq(F, f);
    sumCards = sumCards + cnt_cards_stack(D, f);
    sumCards = sumCards + cnt_cards_stack(W, f);
    return sumCards;
}

nat BoardT::cnt_cards_seq(SeqCrdStckT S, std::function<bool(CardT)> f)
{
    nat sumCards = 0;

    for (nat i = 0; i < S.size(); i++)
    {
        sumCards = cnt_cards_stack(S[i], f);
    }

    return sumCards;
}

nat BoardT::cnt_cards_stack(CardStackT s, std::function<bool(CardT)> f)
{
    nat sumCards = 0;

    std::vector<CardT> cardSeq = s.toSeq();

    for (nat i = 0; i < cardSeq.size(); i++)
    {
        if (f(cardSeq[i]))
        {
            sumCards = sumCards + 1;
        }
    }

    return sumCards;
}

bool BoardT::foundation_placeable(CardT c, CardT d) const
{
    return (c.s == d.s && c.r == d.r + 1);
}

SeqCrdStckT BoardT::init_seq(nat n) const
{
    SeqCrdStckT s;

    for (nat i = 0; i <= n - 1; i++)
    {
        s.push_back(CardStackT());
    }

    return s;
}

bool BoardT::is_valid_pos(CategoryT c, nat n) const
{
    if (c == Tableau)
    {
        if (n >= 0 && n < 10)
            return true;
    }
    else if (c == Foundation)
    {
        if (n >= 0 && n < 8)
            return true;
    }
    return false;
}

SeqCrdStckT BoardT::tab_deck(std::vector<CardT> deck) const
{
    SeqCrdStckT tab;
    for (int i = 0; i < 10; i++)
    {
        std::vector<CardT> temp(deck.cbegin() + 4 * i, deck.cbegin() + 4 * (i + 1) - 1 + 1);
        tab.push_back(CardStackT(temp));
    }

    return tab;
}

bool BoardT::tab_placeable(CardT c, CardT d) const
{
    return (c.s == d.s && c.r == d.r - 1);
}

bool BoardT::two_decks(SeqCrdStckT T, SeqCrdStckT F, CardStackT D, CardStackT W)
{

    for (RankT rk = ACE; rk <= KING; rk++)
    {
        for (int suitInt = Heart; suitInt <= Spade; suitInt++)
        {
            SuitT st = static_cast<SuitT>(suitInt);
            std::function<bool(CardT)> f = [&](CardT c) {
                return (c.s == st && c.r == rk);
            };

            if ((cnt_cards(T, F, D, W, f) == 2) == 0)
                return false;
        }
    }

    return true;
}

bool BoardT::valid_tab_foundation(nat n0, nat n1) const
{
    if (this->T[n0].size() > 0)
    {
        if (this->F[n1].size() > 0)
        {
            return foundation_placeable(this->T[n0].top(), this->F[n1].top());
        }
        else if (this->F[n1].size() == 0)
        {
            return (this->T[n0].top().r == ACE);
        }
    }

    return false; //if T[n0].size() == 0
}

bool BoardT::valid_tab_tab(nat n0, nat n1) const
{
    if (this->T[n0].size() > 0)
    {
        if (this->T[n1].size() > 0)
        {
            return tab_placeable(this->T[n0].top(), this->T[n1].top());
        }
        else if (this->T[n1].size() == 0)
        {
            return true;
        }
    }

    return false; //if T[n0].size() == 0
}

bool BoardT::valid_waste_foundation(nat n) const
{
    if (this->F[n].size() > 0)
    {
        return foundation_placeable(this->W.top(), this->F[n].top());
    }
    return (this->W.top().r == ACE);
}

bool BoardT::valid_waste_tab(nat n) const
{
    if (this->T[n].size() > 0)
    {
        return tab_placeable(this->W.top(), this->T[n].top());
    }
    return true;
}