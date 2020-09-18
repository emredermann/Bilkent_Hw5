

#include "FriendNet.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;
 
/*
*Author: Emre Derman
*Date: 01.05.2020
* Id : 21703508
*/

FriendNet::FriendNet(const string fileName)
{
  
    ifstream input;
    input.open(fileName);
    if (input) {
        input >> SizeOfTheNet;
        int ID, degree;
        string name;
        arr = new Person[SizeOfTheNet];                 

        for (int i = 0; i < SizeOfTheNet; i++) {
            input >> ID;
            input >> name;
            input >> degree;
            Person tmp(name, ID, degree);
        
            int hold;

            for (int j = 0; j < degree; j++) {
                input >> hold;
                tmp.addConnection(hold);

            }
            arr[i] = tmp;
        }
    }
    else {
        SizeOfTheNet = 0;
        arr = new Person[SizeOfTheNet];
    }
    }

FriendNet::FriendNet(const FriendNet& aNet)
{
   
    SizeOfTheNet = aNet.SizeOfTheNet;
    if (aNet.arr == NULL) {
    }
    else {
        arr = new Person[SizeOfTheNet];
       
        for (int i = 0; i < SizeOfTheNet; i++) {
            arr[i] = aNet.arr[i];                                
    }
    }
}

FriendNet::~FriendNet()
{
    delete[] arr;
}

void FriendNet::listFriends(const string personName, const int hopNo)
{
    
    if(hopNo < 1){
        cout << "People accessible from " << personName << " within " << hopNo << " hops: NOBODY"  << endl;
    }
    else {
        
        Person hold; 
        string outputForm = "";
        
         
        if (searchByName(personName, hold)) {
           
            Person tmp;
            Person* connectionPersons = new Person[SizeOfTheNet];
            int counter = 0;
            
            for (int i = 0; i < hold.getDegree(); i++)
            {
                searchById(hold.getConnection(i), tmp);
            
                if (!searchById(tmp.getId(), connectionPersons, counter)  && (tmp.getName() != personName)) {
                    connectionPersons[counter] = tmp;
                    counter++;          
                }
            }
            
            int secondCounter;
            if (hopNo > 1 && hopNo < SizeOfTheNet) {
                for (int k = 1; k < hopNo; k++) {
                    secondCounter = counter;
                    for (int j = 0; j < secondCounter; j++) {
                        for (int i = 0; i < connectionPersons[j].getDegree(); i++) {
                            searchById(connectionPersons[j].getConnection(i), tmp);
                            
                            if(!searchById(tmp.getId(), connectionPersons, counter) && (tmp.getName() != personName )) {
                                connectionPersons[counter] = tmp;
                                counter++;
                            
                            }
                        }
                    }
                }
            }

            // if there are no connections 
            if (counter == 0) { outputForm = "NOBODY"; }

            else {

                for (int j = 0; j < counter; j++) {
                    for (int i = 0; i < counter - 1; i++) {
                        if (comparator(connectionPersons[i].getName(), connectionPersons[i + 1].getName())) {
                            Person tmp = connectionPersons[i];
                            connectionPersons[i] = connectionPersons[i + 1];
                            connectionPersons[i + 1] = tmp;
                        }
                    }
                }

                for (int i = 0; i < counter; i++) {
                    if (i == 0) { outputForm = connectionPersons[i].getName(); }
                    else {
                        outputForm = connectionPersons[i].getName() + ", " + outputForm;
                    }
                }
            }
            cout << "People accessible from " << personName << " within " << hopNo << " hops: " << outputForm << endl;
     
            delete[] connectionPersons;
        }
        else {
            cout << personName << " does not exist in the network." << endl;
        }
    }
}

void FriendNet::displayAverageDegrees()
{
    int count;          
    bool* visited = new bool [SizeOfTheNet];
    for (int i = 0; i < SizeOfTheNet; i++) {
        visited[i] = false;
    }

    double average;
    int averageCounter;
    double* averageCollector = new double[SizeOfTheNet];            
    count = 0;                                                      
    for (int i = 0; i < SizeOfTheNet; i++) {
        if (!visited[i]) {
            average = 0.0;
            averageCounter = 0;
            dfs(i, visited, average, averageCounter);
            averageCollector[count] = (double)(average / averageCounter);
            count++;
        }      
    }
    cout << "There are " << count << " connected components.The average degrees are :" << endl;
    for (int i = 0; i < count; i++) {
        cout << "For component " << i << " : "<< setprecision(3) << (double) averageCollector[i] << endl;
    }
    componentNumber = count;
    delete [] averageCollector;
    delete [] visited;
}

void FriendNet::displayDiameters()
{
    
    int count = 0;
    int * pathCollector = connectedDiameterGiver(count);
     cout << "There are " << count << " connected components.The diameters are: " << endl;
     for (int i = 0; i < count; i++) {
           cout << "For component " << i << " : " << pathCollector[i] << endl;
     }
     delete [] pathCollector;
}

bool FriendNet::searchById(int Id, Person* arr,int sizeOfArr)
{
    for (int i = 0; i < sizeOfArr; i++) {
        if (arr[i].getId() == Id) {
            return true;
        }
    }
    return false;
}

bool FriendNet::searchById(int Id, Person& p)
{
    for (int i = 0; i < SizeOfTheNet; i++) {
        if (arr[i].getId() == Id) {
            p = arr[i];
            return true;
        }
    }
    return false;
}

bool FriendNet::searchByName(string personName, Person & p)
{
   
    for (int i = 0; i < SizeOfTheNet; i++) {
        if (arr[i].getName() == personName) {
            p = arr[i];
            return true;
        }
    }
    return false;
}

bool FriendNet::comparator(string a, string b)
{
    return a < b;
}


void FriendNet::dfs(int u, bool * visit, double &average,int &averageCounter)
{
    visit[u] = true;
    averageCounter = averageCounter + 1;
    average = average + arr[u].getDegree();
    for (int i = 0; i < arr[u].getDegree(); i++) {
       
        int v = arr[u].getConnection(i);                          
        if (!visit[v]) {                                          // checking if neighbour is already visited or not           
            dfs(v,visit,average,averageCounter);     
        }
          }
}

void FriendNet::dfsForComp(int u, bool* visit, LinkedList& compHolder)
{
    
    visit[u] = true;
    compHolder.addNode(u);
    for (int i = 0; i < arr[u].getDegree(); i++) {
        int v = arr[u].getConnection(i);
        if (!visit[v]) {                                          // checking if neighbour is already visited or not           
           
           dfsForComp(v, visit, compHolder);
        }
    }
}

int* FriendNet::connectedDiameterGiver(int & size)
{
    int componentNo;
    bool* visited = new bool[SizeOfTheNet];
    for (int i = 0; i < SizeOfTheNet; i++) {
        visited[i] = false;
    }
    double average;
    int averageCounter;
    componentNo = 0;                      
                                                                        // Counter that counts the no of graph
    for (int i = 0; i < SizeOfTheNet; i++) {
        if (!visited[i]) {
            dfs(i, visited, average, averageCounter);
            componentNo++;
        }
    }
                                                                    
    LinkedList* totalNet = new LinkedList[componentNo];
    for (int i = 0; i < SizeOfTheNet; i++) {
        visited[i] = false;
    }
   // k holds for component number.                                                                 
    int k = 0;
        for (int i = 0; i < SizeOfTheNet; i++) {
            if (!visited[i]) {
                
                LinkedList  person;
                dfsForComp(i, visited, person);
                totalNet[k] = person;                                   
                k++;
            }
        }
    
                                                                        
    int* diameterHolder = new int[componentNo];
    for (int i = 0; i < SizeOfTheNet; i++) {
        visited[i] = false;
    }

     for (int i = 0; i < k; i++) {
            
         int max = 0;
         int counter;

             if (totalNet[i].getSize() > 1)
            {
                for (int j = 0; j < totalNet[i].getSize(); j++) {
                    counter = -1;

                    for (int l = 0; l < SizeOfTheNet; l++) {
                        visited[l] = false;
                    }

                    bfsForDiameter(totalNet[i].getNode(j), visited, totalNet[i].getSize(), counter);

                    if (counter > max)
                    {
                        max = counter;
                    }
                }
            }
            diameterHolder[i] = max;
    }
    size = k;
    delete []totalNet;
    delete []visited;
    return diameterHolder;
}


void FriendNet::bfsForDiameter(int u, bool* visit,int size ,int& counter )
{
   
    Queue q(size);

    // Mark the current node as visited and enqueue it 
    visit[u] = true;
    q.enqueue(u);
     int i = 0;

    int childAdded = 1;

    while (!q.isEmpty())
    { 
        
        counter++;       
        int currentChild = 0;
      
       
        for (int j = 0; j < childAdded; j++) {
            
            u = q.getTop();
            
            q.dequeue();
            
            for (i = 0; i < arr[u].getDegree(); ++i)
            {           
                if (!visit[arr[u].getConnection(i)])
                {
                    currentChild++;
                    visit[arr[u].getConnection(i)] = true;                   
                    q.enqueue(arr[u].getConnection(i));
                }
            }           
        }
        childAdded = currentChild;
     }

}


FriendNet::Queue::Queue(int size)
{
    array = new int[size];
    capacity = size;
    front = 0;
    rear = -1;
    count = 0;
}

FriendNet::Queue::~Queue()
{
    delete [] array;

}

void FriendNet::Queue::dequeue()
{
    if (!isEmpty())
    {
        front = (front + 1) % capacity;
        count--;
    }
   
}

void FriendNet::Queue::enqueue(int data)
{
    if (!isFull())
    {
        rear = (rear + 1) % capacity;
        array[rear] = data;
        count++;
    }
 
}

int FriendNet::Queue::getTop()
{
    if (!isEmpty())
    {
        return array[front];
    }
    
}

int FriendNet::Queue::size()
{
    return count;
}

bool FriendNet::Queue::isEmpty()
{
    return  size() == 0 ;
}

bool FriendNet::Queue::isFull()
{
    return  size() == capacity ;
}
