/**
 * \file Stack.cpp
 * \author Leon So | macid: sol4
 * \date 2019-03-26
 */

#include "Stack.h"
#include "CardTypes.h"
#include <vector>
#include <stdexcept>
#include <iostream>

template <class T>
Stack<T>::Stack()
{
    this->s = std::vector<T>();
}

template <class T>
Stack<T>::Stack(std::vector<T> s)
{
    this->s = s;
}

template <class T>
Stack<T> Stack<T>::push(T e)
{
    this->s.push_back(e);

    return Stack(this->s);
}

template <class T>
Stack<T> Stack<T>::pop()
{
    if (this->s.size() == 0) throw std::out_of_range("Out of range");
    this->s.pop_back();
    return Stack(this->s);
}

template <class T>
T Stack<T>::top() const
{
    if (this->s.size() == 0) throw std::out_of_range("Out of range");
    return this->s.back();
}

template <class T>
nat Stack<T>::size() const
{
    return this->s.size();
}

template <class T>
std::vector<T> Stack<T>::toSeq() const
{
    return this->s;
}

// Keep this at bottom
template class Stack<CardT>;
