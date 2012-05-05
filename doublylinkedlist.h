#pragma once

template <class T>
class List {
public:
    List<T>* next;
    List<T>* prev;
    T value;

    List(T _value);

    void splitInsert(T _value);
    void remove();
};

template <class T>
List<T>::List
