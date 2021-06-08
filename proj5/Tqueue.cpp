#ifndef TQUEUE_CPP
#define TQUEUE_CPP

#include <iostream>
#include <cstdlib>
using namespace std;

template <class T, int N>
class Tqueue {
public:
  //Name: Tqueue - Default Constructor
  //Precondition: None (Must be templated)
  //Postcondition: Creates a queue using dynamic m_dataay
  Tqueue(); //Default Constructor
  //Name: Copy Constructor
  //Precondition: Existing Tqueue
  //Postcondition: Copies an existing Tqueue
  Tqueue( const Tqueue<T,N>& x); //Copy Constructor
  //Name: Destructor
  //Desc: Empties m_data
  //Precondition: Existing Tqueue
  //Postcondition: Destructs existing Tqueue
  ~Tqueue(); //Destructor
  //Name: ClearData
  //Desc: Empties m_data
  //Precondition: Existing Tqueue
  //Postcondition: Empty m_data
  void ClearData();
  //Name: Enqueue
  //Desc: Adds item to the back of queue
  //Precondition: Existing Tqueue
  //Postcondition: Returns true if successful else false
  void Enqueue(T data); //Adds item to queue (to back)
  //Name: Dequeue
  //Desc: Removes item from queue (from front)
  //Precondition: Existing Tqueue
  //Postcondition: Returns true if successful else false
  void Dequeue();
  //Name: Sort
  //Desc: Sorts the contents of the Tqueue
  //NOTE: You may implement to only deal with dereferenced pointers
  //Precondition: Existing Tqueue
  //Postcondition: Contents of Tqueue is sorted (ascending)
  void Sort();
  //Name: IsEmpty
  //Precondition: Existing Tqueue
  //Postcondition: Returns 1 if queue is empty else 0
  int IsEmpty(); //Returns 1 if queue is empty else 0
  //Name: IsFull
  //Precondition: Existing Tqueue
  //Postcondition: Returns 1 if queue is full else 0
  int IsFull(); //Returns 1 if queue is full else 0
  //Name: Size
  //Desc: Returns size of queue
  //Precondition: Existing Tqueue
  //Postcondition: Returns size of queue
  int Size();
  //Name: Overloaded assignment operator
  //Precondition: Existing Tqueue
  //Postcondition: Sets one Tqueue to same as a second Tqueue using =
  Tqueue<T,N>& operator=( Tqueue<T,N> y); //Overloaded assignment operator for queue
  //Name: Overloaded [] operator
  //Precondition: Existing Tqueue
  //Postcondition: Returns object from Tqueue using []
  T& operator[] (int x);//Overloaded [] operator to pull data from queue
private:
  T* m_data; //Data of the queue (Must be dynamically allocated m_dataay)
  int m_front; //Front of the queue
  int m_back; //Back of the queue
};

//**** Add class definition below ****
//Name: Tqueue - Default Constructor
//Precondition: None (Must be templated)
//Postcondition: Creates a queue using dynamic m_dataay
template <class T, int N>
Tqueue<T,N>::Tqueue(){
    m_data = new T[N];
    m_front = 0;
    m_back = 0;
} //Default Constructor

//Name: Copy Constructor
//Precondition: Existing Tqueue
//Postcondition: Copies an existing Tqueue
template <class T, int N>
Tqueue<T,N>::Tqueue(const Tqueue<T,N>& x){
    m_data = new T[N];
    m_front = x.m_front;
    m_back = x.m_back;
    for (int i = 0; i < m_back; i++){
        m_data[i] = x.m_data[i];
    }
} //Copy Constructor

//Name: Destructor
//Desc: Empties m_data
//Precondition: Existing Tqueue
//Postcondition: Destructs existing Tqueue
template <class T, int N>
Tqueue<T,N>::~Tqueue(){
    ClearData();
    delete [] m_data;
} //Destructor

//Name: ClearData
//Desc: Empties m_data
//Precondition: Existing Tqueue
//Postcondition: Empty m_data
template <class T, int N>
void Tqueue<T,N>::ClearData(){
    for (int i = 0; i < m_back; i++){
        m_data[i] = 0;
    }
    m_back = 0;
}

//Name: Enqueue
//Desc: Adds item to the back of queue
//Precondition: Existing Tqueue
//Postcondition: Returns true if successful else false *****
template <class T, int N>
void Tqueue<T,N>::Enqueue(T data){
    m_data[m_back] = data;
    m_back++;
} //Adds item to queue (to back)

//Name: Dequeue
//Desc: Removes item from queue (from front)
//Precondition: Existing Tqueue
//Postcondition: Returns true if successful else false
template <class T, int N>
void Tqueue<T,N>::Dequeue(){
    for (int i = 0; i < (m_back - 1); i++){
        m_data[i] = m_data[i+1];
    }
    m_back--;
}

//Name: Sort
//Desc: Sorts the contents of the Tqueue
//NOTE: You may implement to only deal with dereferenced pointers
//Precondition: Existing Tqueue
//Postcondition: Contents of Tqueue is sorted (ascending)
template <class T, int N>
void Tqueue<T,N>::Sort(){
    //execute if m_data is not empty
    if (IsEmpty() == 0){
        for (int i = 0; i < Size(); i++){
            for (int j = i+1; j < Size(); j++){
                if (*m_data[j] < *m_data[i]){
                    T temp = m_data[i];
                    m_data[i] = m_data[j];
                    m_data[j] = temp;
                }
            }
        }
    }
}

//Name: IsEmpty
//Precondition: Existing Tqueue
//Postcondition: Returns 1 if queue is empty else 0
template <class T, int N>
int Tqueue<T,N>::IsEmpty(){
    if (m_back > 0){
        return 0;
    }
    return 1;
} //Returns 1 if queue is empty else 0

//Name: IsFull
//Precondition: Existing Tqueue
//Postcondition: Returns 1 if queue is full else 0
template <class T, int N>
int Tqueue<T,N>::IsFull(){
    if (m_back == N){
        return 1;
    }
    return 0;
} //Returns 1 if queue is full else 0

//Name: Size
//Desc: Returns size of queue
//Precondition: Existing Tqueue
//Postcondition: Returns size of queue
template <class T, int N>
int Tqueue<T,N>::Size(){
    return m_back;
}

//Name: Overloaded assignment operator
//Precondition: Existing Tqueue
//Postcondition: Sets one Tqueue to same as a second Tqueue using =
template <class T, int N>
Tqueue<T,N>& Tqueue<T,N>::operator=(Tqueue<T,N> y){
    //avoids self-assignment: x = x
    if (this != &y){
        delete [] m_data;
        m_data = new T[N];
        m_front = y.m_front;
        m_back = y.m_back;
        for (int i = 0; i < m_back; i++){
            m_data[i] = y.m_data[i];
        }
    }
    return *this;
} //Overloaded assignment operator for queue

//Name: Overloaded [] operator
//Precondition: Existing Tqueue
//Postcondition: Returns object from Tqueue using []
template <class T, int N>
T& Tqueue<int,10>::operator[](int x){
    N = 10
    T array
    return m_data[x];
} //Overloaded [] operator to pull data from queue

// To test just Lqueue follow these instructions:
//   1.  Uncomment out int main below
//   2.  make Tqueue
//   3.  ./Tqueue (try valgrind too!)

int main () {
    //Test 1 - Default Constructor and Push
    cout << "Test 1 - Default Constructor and Push Running" << endl;
    //Test Default Constructor
    Tqueue <int, 10> newTQ1;
    //Push 4 nodes into Lqueue
    newTQ1.Enqueue(100);
    newTQ1.Enqueue(90);
    newTQ1.Enqueue(80);
    newTQ1.Enqueue(70);
    newTQ1.Enqueue(60);
    newTQ1.Enqueue(50);
    newTQ1.Enqueue(40);
    newTQ1.Enqueue(30);
    newTQ1.Enqueue(20);
    newTQ1.Enqueue(10);
    for (int i = 0; i < newTQ1.Size(); i++){
        cout << newTQ1[i] << endl;
    }
    cout << endl;
    //Test 2 - Copy Constructor and Assignment Operator
    cout << "Test 2 - Copy Constructor and Assignment Operator Running" << endl;
    //Test Copy constructor
    cout << "Copy Constructor Running" << endl;
    Tqueue <int, 10> newTQ2(newTQ1);
    for (int i = 0; i < newTQ2.Size(); i++){
        cout << newTQ2[i] << endl;
    }
    cout << endl;
    //Test Overloaded Assignment Operator
    Tqueue <int, 10> newTQ3;
    cout << "Assignment Operator Running" << endl;
    newTQ3 = newTQ1;
    for (int i = 0; i < newTQ3.Size(); i++){
        cout << newTQ3[i] << endl;
    }
    cout << endl;
    //Test 3 - Test Dequeue
    cout << "Test 3 - Dequeue" << endl;
    newTQ1.Dequeue();
    for (int i = 0; i < newTQ1.Size(); i++){
        cout << newTQ1[i] << endl;
    }
    cout << endl;
    //Test 4 - Test Overloaded []
    cout << "Test 4 - Test Overloaded []" << endl;
    for(int i = 0; i < newTQ1.Size(); i++){
        cout << newTQ1[i] << endl;
    }
    //Test 5 - Test Size and ClearData
    cout << "Test 5 - Size and ClearData" << endl;
    //Test GetSize()
    cout << "Outputting the size" << endl;
    cout << newTQ1.Size() << endl;
    //Test Clear()
    cout << "Clearing all nodes" << endl;
    newTQ1.ClearData();
    cout << "Outputting the size" << endl;
    cout << newTQ1.Size() << endl;
    cout << endl;
    //Test 5 - Test Sort
    cout << "Test 6 - Sort" << endl;
    newTQ2.Sort();
    for (int i = 0; i < newTQ2.Size(); i++){
        cout << newTQ2[i] << endl;
    }
    return 0;
}
*/
#endif
