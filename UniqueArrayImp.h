//
// Created by Yifta on 06/01/2020.
//

#ifndef MTMPARKINGLOT_UNIQUEARRAYIMP_H
#define MTMPARKINGLOT_UNIQUEARRAYIMP_H

template <class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(unsigned int size) : backingData(new Element  *[size]),
                                                                length(size){
    for (unsigned int i = 0; i < length; i++)
    {
        backingData[i] = nullptr;
    }
}

template <class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(const UniqueArray &other) : backingData(new Element  *[other.length]),
                                                                       length(other.length){
    for (unsigned int i = 0; i < length; i++)
    {
        if (other.backingData[i])
        {
            backingData[i] = new Element(*other.backingData[i]);
        }
        else
        {
            backingData[i] = nullptr;
        }
    }
}
template <class Element, class Compare>
UniqueArray<Element, Compare>::~UniqueArray()
{
    for (unsigned int i = 0; i < length; i++)
    {
        if (backingData[i])
        {
            delete backingData[i];
        }
    }

    delete[] backingData;
}
template <class Element, class Compare>
bool UniqueArray<Element, Compare>::getIndex(const Element &element, unsigned int &index) const{
    for (unsigned int i = 0; i < length; i++)
    {
        if (backingData[i])
        {
            if (comperator(*backingData[i], element))
            {
                index = i;
                return true;
            }
        }
    }
    return false;
}

template <class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::insert(const Element &element){
    unsigned int index;
    if(getIndex(element,index)){
        return index;
    }
    for (unsigned int i = 0; i < length; i++)
    {
        if (!backingData[i])
        {
                backingData[i] = new Element(element);
                return i;
        }
    }
    //in case of no empty place, the code reaches this point.
    throw UniqueArrayIsFullException();
}

template <class Element, class Compare>
const Element *UniqueArray<Element, Compare>::operator[](const Element &element) const{
    for (unsigned int i = 0; i < length; i++)
    {
        if (backingData[i])
        {
            if (comperator(*backingData[i], element))
                return backingData[i];
        }
    }
    return nullptr;
}

template <class Element, class Compare>
bool UniqueArray<Element, Compare>::remove(const Element &element){
    for (unsigned int i = 0; i < length; i++)
    {
        if (backingData[i])
        {
            if (comperator(*backingData[i], element))
            {
                delete backingData[i];
                backingData[i] = nullptr;
                return true;
            }
        }
    }
    return false;
}

template <class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::getSize() const{
    return length;
}

template <class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::getCount() const{
    int counter = 0;
    for (unsigned int i = 0; i < length; i++)
    {
        if (backingData[i])
        {
            counter++;
        }
    }
    return counter;
}

template <class Element, class Compare>
UniqueArray<Element, Compare> UniqueArray<Element, Compare>::filter(const UniqueArray::Filter &f) const{
    UniqueArray<Element, Compare> copy = UniqueArray(length);
    for (unsigned int i = 0; i < length; i++)
    {
        if (backingData[i])
        {
            if (f(*backingData[i]))
            {
                copy.insert(*backingData[i]);
            }
        }
    }
    return copy;
}

#endif //UNIQUEARRAYTEST_UNIQUEARRAYIMP_H
