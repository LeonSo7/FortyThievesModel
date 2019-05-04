/**
 * \file Stack.h
 * \author Leon So | macid: sol4
 * \date 2019-03-26
 */
#ifndef A3_STACK_H_
#define A3_STACK_H_

#include <vector>

/**
 * \brief Describes a natural number.
 */
typedef unsigned int nat;

template <class T>

/**
 * \brief Stack abstract data type
 */
class Stack
{
    private:
        std::vector<T> s;

    public:
        /**
         * \brief Empty constructor for a stack
         */
        Stack();

        /**
         * \brief Empty constructor for a stack
         */
        Stack(std::vector<T> s);

        /**
         * \brief Mutator - push element into stack
         * \param e - Element to be pushed of type T
         * \return Ouput a new stack
         */
        Stack push(T e);

        /**
         * \brief Mutator - pop element off stack
         * \return Ouput a new stack
         */
        Stack pop();

        /**
         * \brief Accessor - gets top of stack
         * \return Ouput element at top of stack
         */
        T top() const;

        /**
         * \brief Gets size of stack
         * \return Ouput size of stack
         */
        nat size() const;

        /**
         * \brief Accessor - get stack in form of sequence
         * \return Stack in form of sequence
         */
        std::vector<T> toSeq() const;
};

#endif
