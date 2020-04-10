#ifndef LINKEDSTRING_HPP
#define LINKEDSTRING_HPP

#define MAX_LENGTH 255
#define SEGMENT_LENGTH 8

#ifndef NULL
#define NULL 0
#endif

class StringSegment
{
public:
    StringSegment(const char*, int);
    ~StringSegment();

    void operator += (const char*);

    const char * ToCString(int);
private:
    StringSegment* next;
    char* segment;
    //is Full is only false when segment contains '\0' character
    bool isFull;
};

StringSegment::StringSegment(const char* cString, int index = 0)
{
    isFull = false;
    next = NULL;
    segment = new char[SEGMENT_LENGTH];
    /*
    //initialization to a character for easier debug
    for (int i = 0; i < SEGMENT_LENGTH; i++){
        segment[i] = '#';
    }
    */

    for (int i = 0; i < SEGMENT_LENGTH; i++)
    {
        char nextChar = cString[index + i];
        segment[i] = nextChar;

        if(nextChar == '\0'){
            return;
        }
    }
    isFull = true;
    next = new StringSegment(cString, index + SEGMENT_LENGTH);
}

StringSegment::~StringSegment()
{
    delete segment;
    delete next;
}

const char * StringSegment::ToCString(int length){
    //+1 for null character '\0'
    char* cString = new char[length + 1];
    StringSegment* traverse = this;
    int index = 0;

    while(traverse != 0){

        for (int i = 0; i < SEGMENT_LENGTH; i++)
        {
            char nextChar = traverse->segment[i];
            cString[(index * SEGMENT_LENGTH) + i] = nextChar;
            if(nextChar == '\0')
                break;
        }
        index++;
        traverse = traverse->next;
    }

    return cString;
}


void StringSegment::operator+=(const char* input){
    StringSegment* traverse = this;
    //traverse to end of string
    while (traverse->next != NULL)
    {
        traverse = traverse->next;
    }
  
    
    int segmentLength = 0;
    //if segment is not full it must have a null character
    //count characters up to null character
    while(traverse->segment[segmentLength] != '\0' && segmentLength < SEGMENT_LENGTH)
    {
        segmentLength++;
    }

    int freeSpace = SEGMENT_LENGTH - segmentLength;
    int i;
    for (i = 0; i < freeSpace; i++)
    {
        char nextChar = input[i];
        traverse->segment[i + segmentLength] = nextChar;
        if(nextChar == '\0'){
            return;
        }
    }

    traverse->isFull = true;
    traverse->next = new StringSegment(input, i);
        
    
    
    
}

class LinkedString
{
public:
    LinkedString(/* args */);
    ~LinkedString();
    void operator = (const LinkedString&);
    void operator = (const char*);
    void operator += (const LinkedString&);
    void operator += (const char*);

    bool operator == (const LinkedString&);
    bool operator == (const char*);

    const char* ToCString() const;
    int getLength() const;

    //move to private

private:

    StringSegment* head;
    int length;
};

LinkedString::LinkedString(/* args */)
{
    length = 0;
    head = NULL;
}

LinkedString::~LinkedString()
{
    delete head;
}

void LinkedString::operator = (const LinkedString& inputString){
    length = inputString.length;
    head = new StringSegment(inputString.ToCString());
}


void LinkedString::operator = (const char* input){

    int inputLength = 0;
    for (int i = 0; input[i] != '\0' && i < MAX_LENGTH ; i++)
    {
        inputLength++;
    }
    length = inputLength;

    head = new StringSegment(input);
}

void LinkedString::operator+=(const LinkedString& input){
    int inputLength = input.getLength();
    *this->head += input.ToCString();


    length += inputLength;
}

void LinkedString::operator+=(const char* input){
    int inputLength = 0;
    for (int i = 0; input[i] != '\0' && i < MAX_LENGTH ; i++)
    {
        inputLength++;
    }

    *head += input;

    length += inputLength;
}

bool LinkedString::operator == (const LinkedString& operand){
    //if lengths are not the same then strings are not equivalent
    if(this->length != operand.length)
        return false;

    //converting both strings for easy random access
    const char* operand1 = this->ToCString();
    const char* operand2 = operand.ToCString();

    //checking every character until different characters are found
    for (int i = 0; i < this->length; i++)
    {
        if(operand1[i] != operand2[i]){
            return false;
        }
    }
    
    return true;
}

bool LinkedString::operator == (const char* operand){
    //converting string for easy random access
    const char* operand1 = this->ToCString();

//checking every character until different characters are found
    for (int i = 0; i < this->length; i++)
    {
        char nextChar = operand[i];
        if(nextChar == '\0' || operand1[i] != nextChar){
            return false;
        }
    }

    return true;
}

const char* LinkedString::ToCString() const {
    if(head == NULL){
        return "Error, string not defined";
    }
    
    return head->ToCString(length);
}

int LinkedString::getLength() const{
    return length;
}

#endif