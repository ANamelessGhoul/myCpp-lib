#ifndef GENERICLIST_HPP
#define GENERICLIST_HPP

#ifndef NULL
#define NULL 0
#endif


template <typename T> 
class GenericList;

template <typename T> 
class GenericNode;


//---------------------------------------------------------------//

//---------------------------------------------------------------//

//---------------------------------------------------------------//



template <typename T> 
class GenericList
{
public:
    GenericList();
    ~GenericList();

    T& operator[](int);

    void Add(const T&);
    int getLength();


    //move to private

private:
    GenericNode<T>* head;
    int length;
};

template <typename T> 
GenericList<T>::GenericList()
{
    head = NULL;
    length = 0;
}

template <typename T> 
GenericList<T>::~GenericList()
{
    if(head != NULL)
        delete head;
}

template <typename T> 
T& GenericList<T>::operator[](int index){
    GenericNode<T>* traverse = head;

    for (int i = 0; i < index; i++)
    {
        traverse = traverse->next;
        if (traverse == NULL)
        {
            //index out of range

        }
    }
    
    return traverse->data;
}

template <typename T> 
void GenericList<T>::Add(const T& input){
    if(head == NULL){
        head = new GenericNode<T>(input);
        length++;
    }
    else
    {
        GenericNode<T>* traverse = head;

        //Traverse to end of list
        while (traverse->next != NULL)
        {
            traverse = traverse->next;
        }

        traverse->next = new GenericNode<T>(input);
        length++;
    }
}

template <typename T> 
int GenericList<T>::getLength(){
    return length;
}


//---------------------------------------------------------------//

//---------------------------------------------------------------//

//---------------------------------------------------------------//


template <typename T> 
class GenericNode
{
friend class GenericList<T>;
public:
    GenericNode(const T&);
    ~GenericNode();
    //move to private

private:
    T data;
    GenericNode<T>* next;
};

template <typename T> 
GenericNode<T>::GenericNode(const T& input)
{
    next = NULL;
    data = input;
}

template <typename T> 
GenericNode<T>::~GenericNode()
{
    if(next != NULL)
        delete next;
}

#endif