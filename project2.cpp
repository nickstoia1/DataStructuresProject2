#include <iostream>

using namespace std;

// used to empty a given string A of length n
void emptyString (char* A, int n) {
    for (int i=0; i < n; i++) {
        A[i] = '\0';
    }
}

// copy a string A to B of length n
void stringCopy (char* A, int n, char* B) {
    for (int i=0; i < n; i++) {
        B[i] = A[i];
    }
}

// return the length of a given string A
int stringLength (char* A) {
    int size = 0;
    while (A[size] != '\0') size++;
    return size; //size is the last index position
}

class myString;

class myString {
    friend ostream& operator << (ostream& s, myString& A); // makes it so you can cout << the myString
protected:
    char* strArray; // the letters in the string
    int size; // length of the string
    void strCpy (char* A, char* B, int n); // deletes A and then copies B to a new A of size n
public:
    myString (); // default constructor
    ~myString(); // destructor destroying strArray
    myString(char* inpStr); // constructor initializing strArray with inpStr
    myString (myString& B); // copy constructor
    int Size(); // gets the size
    char* getWord(); // gets the word
    bool operator == (myString& B); // checks if they are equal
    bool operator > (myString& B); // checks if greater by alphabetical then size
    bool operator < (myString& B); // checks if lesser by alphabetical then size
    myString& operator = (myString& B); // overrides = to be able to initialize with &myString
    myString& operator = (char* B); // overrides = to be able to initialize with char*
};

// outputs a given string A
ostream& operator << (ostream& s, myString& A) {
    s << A.strArray;
    return s;
}

// default constructor - initializes with a NULL as the first character
myString::myString () {
    size = 0;
    strArray = new char[1];
    strArray[0] = '\0';
}

// non default constructor - initialize object with an existing string
myString::myString (char* inpStr) {
    int i = 0;
    while (inpStr[i] != '\0')
        i++;
    size = i;
    strArray = new char[size];
    emptyString (strArray, size);
    for (int j=0; j < size; j++){
        char t = inpStr[j];
        strArray[j] = t;
    }

}

// non default constructor - initialize object with an existing mystring object
myString::myString (myString& B) {
    strArray = NULL;
    size = B.size;
    strArray = new char[size +1 ];
    emptyString(strArray, size + 1);
    for (int i = 0; i < size; i++){
        strArray[i] = B.strArray[i];
    }
}

// returns the string
char* myString::getWord()
{
    return strArray;
}

// getter for size of myString
int myString::Size () {
    return size;
}

// overloading = operator - initialize object with an existing string
myString& myString::operator = (char* B) {
    // get the length/size of B
    int i = 0;
    while (B[i] != '\0')
        i++;
    size = i;
    // set the strArray to size +1 to have end null char
    strArray = new char[size + 1];
    emptyString (strArray, size + 1);
    // copy B to strArray
    for (int j=0; j < size; j++)
        strArray[j] = B[j];
    // return myString
    return *this;
}

// overloading = operator - initialize object with an existing mystring object
myString& myString::operator = (myString& B) {
    // check to make see if they are already equal
    if (this == &B){
        return *this;
    }
    // delete the existing strArray
    delete [] strArray;
    strArray = NULL;
    size = B.size;
    // initialize empty strArray and copy
    strArray = new char[size + 1];
    emptyString(strArray, size + 1);
    stringCopy (B.strArray, size, strArray);
    return *this;
}

// checking if two myString objects are the same - return true or false
bool myString::operator == (myString& B) {
    // not equivalent if sizes are different
    if (size != B.Size()){
        return false;
    }
    // check if each char is same if not return false
    for (int i = 0; i < size; i++){
        if (strArray[i] != B.strArray[i]){
            return false;
        }
    }
    return true;
}

// comparison of myString A if less than myString B - return true or false
bool myString::operator < (myString& B) {
    // get the size of smaller to not go out of bounds of the strArrays
    int sizeOfSmaller;
    if (size < B.Size()) sizeOfSmaller = size;
    else sizeOfSmaller = B.Size();
    // check each char to see if they are not the same
    // if not the same if less than true else false
    for (int i = 0; i < sizeOfSmaller; i++){
        if (strArray[i] != B.strArray[i]) {
            if (strArray[i] < B.strArray[i]) return true;
            else return false;
        }
    }
    // if they are the same up to smallerSize
    // make sure they are not the same size
    // if size of smaller is this then true else false
    if (sizeOfSmaller == size && size != B.Size()) return true;
    else return false;
}

// comparison of myString A if greater than myString B - return true or false
bool myString::operator > (myString& B) {
    // get the size of smaller to not go out of bounds of the strArrays
    int sizeOfSmaller;
    if (size < B.Size()) sizeOfSmaller = size;
    else sizeOfSmaller = B.Size();
    // check each char to see if they are not the same
    // if not the same if less than false else true
    for (int i = 0; i < sizeOfSmaller; i++){
        if (strArray[i] != B.strArray[i]) {
            if (strArray[i] < B.strArray[i]) return false;
            else return true;
        }
    }
    // if they are the same up to smallerSize
    // if same size return false
    // if size of smaller is this then false else false
    if (size == B.Size() || sizeOfSmaller == size) return false;
    else return true;
}
// destroys A and reinitialise it to be a copy of B
void myString::strCpy(char *A, char *B, int n) {
    // de
    delete[] A;
    A = new char[n];
    for (int i = 0; i < n; i++){
        A[i] = B[i];
    }
}
// destructor
myString::~myString() {
    delete [] strArray; // destroys strArray
    // clean up
    size = 0;
}

// get one token from redirected input and return that string (alphanumeric)
char* getNextToken () {
    char* str = new char[20]; //assumes a max token size of 20
    emptyString (str, 20);

    char c;
    int i = 0;
    while (!cin.eof()) {
        cin.get(c);
        if (!cin.eof ()) {
            if ((c != '\n') && (c != ' ')) {
                if ( ((c >= 'a') && (c <= 'z')) ||
                     ((c >= 'A') && (c <= 'Z')) ||
                     ((c >= '0') && (c <= '9')) )
                    str[i++] = c;
            }
            else if ((c == '\n') && (i > 0))
                return str;
            else if ((c == ' ') && (i > 0))
                return str;
        }
    }
    if (i > 0) return str;
    else return NULL;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class bagOfWords {
private:
    int binarySearchAndInsert (myString& W);
protected:
    myString* _words; // array of strings
    int* _frequencies; // corresponding frequency of strings in _words
    int _size; // number of strings

public:
    bagOfWords (); // default constructor
    bagOfWords (int numOfWords); // initializes with known total number of words

    myString* get_Words(); // gets _words and returns
    int* get_Freq(); // gets _frequencies and returns
    int get_size(); // returns the _size

    void setSize(int i); // sets the size

    void addWord (myString& W);//insert word w into the array _words - keep it sorted alphabetically
    void sortFreq(); //sort words array based on frequency
    void sortWords(); //sort words array alphabetically
    void display(); //print word followed by a colon followed by a single space and frequency
    bagOfWords* removeStopWords(myString* stopWords, int numStopWords); //stopWords from _words array
    void insertion(myString& word, int insertionIndex); // inserts the word at the InsertionIndex
    ~bagOfWords(); // destructor
};

// default constructor - initializes with no words
bagOfWords::bagOfWords()
{
    _size = 0;
    _words = new myString[0];
    _frequencies = new int[0];
}

// non default constructor - initializes with a known number of words
bagOfWords::bagOfWords (int numOfWords)
{
    _size = numOfWords;
    _words = new myString[numOfWords];
    _frequencies = new int[numOfWords];
}

myString* bagOfWords::get_Words()
{
    return _words;
}

int* bagOfWords::get_Freq()
{
    return _frequencies;
}

int bagOfWords::get_size()
{
    return _size;
}

void bagOfWords::setSize(int i)
{
    _size = i;
}

// print the bag of words in dictionary format
void bagOfWords::display()
{
    // Displays number of words in bag
    // then the words with corresponding frequency
    cout << "Bag of Words: " << _size << endl;
    for (int i = 0; i < _size; i++){
        cout << _words[i] << ": " << _frequencies[i] << endl;
    }

}

// sort the _words and _frequencies based on frequencies
void bagOfWords::sortFreq()
{
    // Selection sort - sorted in frequency order ascending
    // get the index with the smallest frequency and first alphabetic of that frequency
    for (int i = 0; i < _size - 1; i ++){
            int minId = i;
            for (int j = i + 1; j < _size; j++){
                // checking for smaller frequency
                if (_frequencies[j] < _frequencies[minId]){
                    minId = j;
                }
                // checking ones with minId to see if smaller in alphabet
                else if (_frequencies[j] == _frequencies[minId] && _words[j] < _words[minId]){
                    minId = j;
                }
            }
            // swaps the current word and frequency with minimum if current index is not minimum index
            if (minId!=i){
                myString* temp = new myString(_words[minId]);
                _words[minId] = _words[i];
                _words[i] = *temp;
                int tempFreq = _frequencies[minId];
                _frequencies[minId]= _frequencies[i];
                _frequencies[i] = tempFreq;
                delete temp;
            }
    }
}

// sort the _words and _frequencies, alphabetically
void bagOfWords::sortWords()
{
    // selection sort - sorted in alphabetical order ascending
    // gets the minimum word alphabetically and swaps with curr
    for (int i = 0; i < _size - 1; i ++){
        int minId = i;
        for (int j = i + 1; j < _size; j++){
            // check if smaller alphabetically
            if (_words[j] < _words[minId]){
                minId = j;
            }
        }
        // swaps word and frequency if not the same index
        if (minId!=i){
            myString* temp = new myString(_words[minId]);
            _words[minId] = _words[i];
            _words[i] = *temp;
            int tempFreq = _frequencies[minId];
            _frequencies[minId]= _frequencies[i];
            _frequencies[i] = tempFreq;
            delete temp;
        }
    }
}
// removes stopWords from this bag
bagOfWords* bagOfWords::removeStopWords(myString* stopWords, int numStopWords)
{
    // creates a new bag to hold words in this but not stopWords
    bagOfWords* temp = new bagOfWords();
    myString* currWord;
    bool contains = false;
    // checks if each word is not in stop words
    // if not in stopWords add to new Bag
    for (int i = 0; i < _size; i++){
        currWord = new myString(_words[i]);
        for(int j = 0; j < numStopWords; j ++){
            if (stopWords[j] == *currWord){
                contains = true;
            }
        }
        // does not contain then add number of times there is frequency in this
        if (!contains){
            for (int f = 0; f < _frequencies[i]; f++){
                temp->addWord(*currWord);
            }
        }
        delete currWord;
        contains = false;
    }
    // return new bag
    return temp;
}

// to search for a given word in _words and add it - returns 0 if not found and then added, 1 if found
int bagOfWords::binarySearchAndInsert (myString& wordToFind)
{
    // Binary search for the index found or index to insert using alphabetical order
    // if found during search increment frequency
    // if not found insert word at the correct location
    int start = 0;
    int end = _size - 1;
    int mid;
    int insertIndex;
    // when start is > end it is not found
    while (start <= end){
        mid = (end+start) / 2;
        // if same, found and increment frequency at mid
        if (_words[mid] == wordToFind){
            _frequencies[mid]++;
            return 1;
        }
        // if less than make new start mid + 1 and run again
        else if (_words[mid] < wordToFind){
            start = mid + 1;
        }
        // if greater than make new end mid - 1 and run again
        else {
            end = mid - 1;
        }
    }
    // check if string at mid is before or after wordToFind to get insertIndex
    // if before add 1 to mid is insertIndex
    // else mid is insertIndex
    if (_words[mid] < wordToFind) insertIndex = mid + 1;
    else insertIndex = mid;
    // insert the wordToFind at the insertIndex
    insertion(wordToFind, insertIndex);
    // return not found since word had to be added
    return 0;
}

// method to add words to the bagOfWords object
void bagOfWords::addWord(myString & newWord)
{
    // if no words in the bag reinitialize words and frequency to size = 1 and add word
    if (_size == 0){
        delete[] _words;
        delete [] _frequencies;
        _words = new myString[1];
        _words[0] = newWord;
        _frequencies = new int[1]{1};
        _size++;
    }
    // add word in correct alphabetical location
    else {
        binarySearchAndInsert(newWord);
    }
}
// inserts word at the given insertIndex
void bagOfWords::insertion(myString &word, int insertIndex) {
    bool inserted = false; // checks if inserted
    int* tempFreq;
    myString* tempWords;
    _size++; // size incremented to be one larger with new word added
    tempFreq = new int[_size]; // empty array to put frequency
    tempWords = new myString[_size]; // empty array to put words
    int i = 0;
    // loop to initialize temps
    while (i < _size){
        // if the word has been put in temp
        // use index i - 1 to get values from frequency and words for temps
        if (inserted){
            tempFreq[i] = _frequencies[i-1];
            tempWords[i] = _words[i-1];
        }
        else {
            // not inserted and not the insertIndex
            // use index i to get values from frequency and words for temps
            if (i != insertIndex){
                tempFreq[i] = _frequencies[i];
                tempWords[i] = _words[i];
            }
            // index of insertIndex should be word
            else {
                tempFreq[i] = 1;
                tempWords[i] = word;
                inserted = true;

            }

        }
        i++; // increment
    }
    // delete the current _words and _frequency
    delete [] _words;
    delete [] _frequencies;
    // initialize by copying temps
    _words = new myString[_size];
    _frequencies = new int[_size];
    for (int i = 0; i < _size; i++) {
        _words[i] = tempWords[i];
        _frequencies[i] = tempFreq[i];
    }
    // take out trash of the temps
    delete [] tempWords;
    delete [] tempFreq;
}
// destructor to delete _words and _frequencies
bagOfWords::~bagOfWords() {
    // take out trash and cleanup
    delete [] _words;
    _size = 0;
    delete [] _frequencies;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main () {

    int numStopWords;
    char* token;
    myString* tokenString;

    //read the first number from the file that contains the number of stop words
    cin >> numStopWords;
    cout << "Number of Stop words: " << numStopWords << endl;
    myString* stopWordsList = new myString[numStopWords];

    //read the stop words
    for (int i=0; i < numStopWords; i++)
    {
        token = getNextToken ();
        stopWordsList[i] = token;//calls the overloaded = operator on myString class
        delete [] token;
    }

    //Now read a text and put them in the bagOfWords instance.
    bagOfWords* myBag = new bagOfWords ();

    token = getNextToken (); // v2: this was the error.

int i =0;
    while (token != NULL)
    {
        tokenString = new myString (token); //create a myString object with the token
        (*myBag).addWord(*tokenString);//add token to myBag
        token = getNextToken ();
    }

    // this should display the token and frequency;
    // note that becuase you are using binary search and insert the tokens will
    // be sorted alphabetically
    cout << endl;
    cout << "Input display:" << endl;
    (*myBag).display ();
    // outputs the words in frequency order
    (*myBag).sortFreq ();
    cout << endl;
    cout << "myBag - Sorted based on frequency:" << endl;
    (*myBag).display ();
    // back to sorted order and outputs
    (*myBag).sortWords();
    cout << endl;
    cout << "myBag - Sorted alphabetically:" << endl;
    (*myBag).display ();
    // new bag with words from old bag not in stopWordsList
    // outputs newBag in sorted order
    bagOfWords* newBag = (*myBag).removeStopWords(stopWordsList, numStopWords); // new parameter added here
    cout << endl;
    cout << "newBag - Sorted alphabetically:" << endl;
    (*newBag).display();
    // outputs newBag in frequency order
    (*newBag).sortFreq ();
    cout << endl;
    cout << "newBag - Sorted based on frequency:" << endl;
    (*newBag).display ();
    // taking out the trash
    delete tokenString;
    delete [] stopWordsList;
    delete myBag;
    delete newBag;

}
