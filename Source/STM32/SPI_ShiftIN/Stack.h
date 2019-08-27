/* *  Stack.h *{{{
 *  Library implementing a, dynamic stack (array version).
 *
 *  ---
 *  baset on
 *
 *  Copyright (C) 2010  Efstathios Chatzikyriakidis (contact@efxa.org)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 *  --- }}}*/

// header defining the interface of the source.
#ifndef STACK_H
#define STACK_H

// include Arduino basic header.
#include <Arduino.h>

// the definition of the stack class.{{{
template<typename T>
class Stack {
  public:/*{{{*/
    // init the stack (constructor).
    Stack (int );
    Stack ( );
    // clear the stack (destructor).
    ~Stack ();
    // push an item to the stack.
    void push (const T i);
    void pushEx (const T i);
    // pop an item from the stack.
    T pop ();
    T popEx ();
    // get an item from the stack.
    T peek () const;
    T peekEx () const;
    // check if the stack is empty.
    bool isEmpty () const;
    // get the number of items in the stack.
    int count () const;
    // check if the stack is full.
    bool isFull () const;
    // set the printer of the stack.
    void setPrinter (Print & p);
	 void reset(void);
    // resize the size of the stack.
    void resize (const int s);
/*}}}*/
  private:/*{{{*/
    // exit report method in case of error.
    void exit (const char * m) const;
    // led blinking method in case of error.
    void blink () const;
    // the initial size of the stack.
    static const int initialSize = 2;
    // the pin number of the on-board led.
    static const int ledPin = 13;
    Print * printer; // the printer of the stack.
    T * contents;    // the array of the stack.
    int size;        // the size of the stack.
    int top;         // the top index of the stack.
	 /*}}}*/
};/*}}}*/

// init the stack (constructor).{{{
template<typename T>
Stack<T>::Stack () {
  size = 0;       // set the size of stack to zero.
  top = 0;        // set the initial top index of the stack.
  printer = NULL; // set the printer of stack to point nowhere.

  // allocate enough memory for the array.
  contents = (T *) malloc (sizeof (T) * initialSize);

  // if there is a memory allocation error.
  if (contents == NULL)
    exit ("STACK: insufficient memory to initialize stack.");

  // set the initial size of the stack.
  size = initialSize;
}
template<typename T>
Stack<T>::Stack (int elemts) {
  size = 0;       // set the size of stack to zero.
  top = 0;        // set the initial top index of the stack.
  printer = NULL; // set the printer of stack to point nowhere.

  // allocate enough memory for the array.
  contents = (T *) malloc (sizeof (T) * elemts);

  // if there is a memory allocation error.
  if (contents == NULL)
    exit ("STACK: insufficient memory to initialize stack.");

  // set the initial size of the stack.
  size = elemts;
	}/*}}}*/
// clear the stack (destructor).{{{
template<typename T>
Stack<T>::~Stack () {
  free (contents); // deallocate the array of the stack.

  contents = NULL; // set stack's array pointer to nowhere.
  printer = NULL;  // set the printer of stack to point nowhere.
  size = 0;        // set the size of stack to zero.
  top = 0;         // set the initial top index of the stack.
}/*}}}*/

// resize the size of the stack.{{{
template<typename T>
void Stack<T>::resize (const int s) {
  // defensive issue.
  if (s <= 0)
    exit ("STACK: error due to undesirable size for stack size.");

  // reallocate enough memory for the array.
  contents = (T *) realloc (contents, sizeof (T) * s);

  // if there is a memory allocation error.
  if (contents == NULL)
    exit ("STACK: insufficient memory to resize stack.");

  if (top > s)top = s;
  // set the new size of the stack.
  size = s;
}/*}}}*/

// pushEx an item to the stack.{{{
template<typename T>
void Stack<T>::pushEx (const T i) {
  // check if the stack is full.
  if (isFull ())
    // double size of array.
    resize (size * 2);

  // store the item to the array.
  contents[top++] = i;
}/*}}}*/
// push an item to the stack.{{{
template<typename T>
void Stack<T>::push (const T i) {
  // check if the stack is full.
  if (isFull ()) top = 0;
  // store the item to the array.
  contents[top++] = i;
}/*}}}*/

// pop an item from the stack.{{{
template<typename T>
T Stack<T>::pop () {
  // check if the stack is empty.
	if (isEmpty ()) top = size;
  // return the top item from the array.
  return  contents[--top];
}/*}}}*/
// popEx an item from the stack.{{{
template<typename T>
T Stack<T>::popEx () {
  // check if the stack is empty.
  if (isEmpty ())
    exit ("STACK: can't pop item from stack: stack is empty.");

  // fetch the top item from the array.
  T item = contents[--top];

  // shrink size of array if necessary.
  if (!isEmpty () && (top <= size / 4))
    resize (size / 2);

  // return the top item from the array.
  return item;
}/*}}}*/

// peek - get an item from the stack.{{{
template<typename T>
T Stack<T>::peek () const {
  // check if the stack is empty.
  if (isEmpty ())
	  return contents[size - 1];

  // get the top item from the array.
  return contents[top - 1];
}/*}}}*/
// EX get an item from the stack.{{{
template<typename T>
T Stack<T>::peekEx () const {
  // check if the stack is empty.
  if (isEmpty ())
    exit ("STACK: can't peek item from stack: stack is empty.");

  // get the top item from the array.
  return contents[top - 1];
}/*}}}*/

// check if the stack is empty.{{{
template<typename T>
bool Stack<T>::isEmpty () const {
  return top == 0;
}/*}}}*/
// check if the stack is full.{{{
template<typename T>
bool Stack<T>::isFull () const {
  return top == size;
}/*}}}*/

// reset set top of stack to 0.{{{
template<typename T>
void Stack<T>::reset () {
   top = 0;
}/*}}}*/
// get the number of items in the stack.{{{
template<typename T>
int Stack<T>::count () const {
  return top;
}/*}}}*/

// set the printer of the stack.{{{
template<typename T>
void Stack<T>::setPrinter (Print & p) {
  printer = &p;
}/*}}}*/

// exit report method in case of error.{{{
template<typename T>
void Stack<T>::exit (const char * m) const {
  // print the message if there is a printer.
  if (printer)
    printer->println (m);

  // loop blinking until hardware reset.
  blink ();
}/*}}}*/

// led blinking method in case of error.{{{
template<typename T>
void Stack<T>::blink () const {
  // set led pin as output.
  pinMode (ledPin, OUTPUT);

  // continue looping until hardware reset.
  while (true) {
    digitalWrite (ledPin, HIGH); // sets the LED on.
    delay (250);                 // pauses 1/4 of second.
    digitalWrite (ledPin, LOW);  // sets the LED off.
    delay (250);                 // pauses 1/4 of second.
  }

  // solution selected due to lack of exit() and assert().
} /*}}}*/
#endif // STACK_H