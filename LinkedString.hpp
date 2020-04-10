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

    void operator += (const StringSegment&);
    void operator += (const char*);

    StringSegment* next;
    char* segment;
    //is Full is only false when segment contains '\0' character
    bool isFull;

private:
};

StringSegment::StringSegment(const char* cString, int index = 0)
{
    isFull = false;
    next = NULL;
    segment = new char[SEGMENT_LENGTH];
    for (int i = 0; i < SEGMENT_LENGTH; i++){
        segment[i] = '#';
    }

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

void StringSegment::operator+=(const StringSegment& input){
    *this += input.segment;

    if(input.next != NULL){
        StringSegment* traverse = input.next;
        while (traverse->next != NULL)
        {
            *this += traverse->segment;
            traverse = traverse->next;
        }
    }
    
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
    //LinkedString operator + (const LinkedString&);
    LinkedString operator + (const char*);

    const char* ToCString() const;
    int getLength() const;

    //move to private
    StringSegment* head;

private:

    int length;
    char* cString;
};

LinkedString::LinkedString(/* args */)
{
    length = 0;
    head = NULL;
}

LinkedString::~LinkedString()
{
    delete head;
    delete cString;
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
    *this->head += *input.head;


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

//TODO: Update for segments
LinkedString LinkedString::operator+ (const char* input){

    int inputLength = 0;
    for (int i = 0; input[i] != '\0' && i < MAX_LENGTH ; i++)
    {
        inputLength++;
    }

    //+1 for end character
    char* temp = new char[length + inputLength + 1];

    for (int i = 0; i < length; i++)
    {
        temp[i] = cString[i];
    }

    for (int i = 0; i < inputLength; i++)
    {
        temp[i + length] = input[i];
    }

    temp[length + inputLength] = '\0';

    LinkedString result;
    result = temp;
    
    return result;
}

const char* LinkedString::ToCString() const {
    //+1 for null character '\0'
    char* cString = new char[length + 1];

    if(head == 0){
        return "Error, string not defined";
    }

    StringSegment* traverse = head;
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

int LinkedString::getLength() const{
    return length;
}

#endif