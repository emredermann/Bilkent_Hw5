#include <string>
#include "Person.h"

using namespace std;
class FriendNet {
	class Queue
	{
		int* array;		
		int capacity;	
		int front;		
		int rear;		
		int count;		

	public:
		Queue(int size); 	// constructor
		~Queue();   				// destructor

		void dequeue();
		void enqueue(int );
		int getTop();
		int size();

		bool isEmpty();
		bool isFull();
	};
	struct node
	{
		int data;
		node* next;
		
	};
	class LinkedList
	{
	private:
		node* head;
		int size;
	public:
		LinkedList()
		{
			head = NULL;
			size = 0;

		}
		~LinkedList() {
			while (!isEmpty()) {
				deleteNode();
			}
		//	delete head;
		}
		bool addNode(int  n)
		{
			node* tmp = new node;
			tmp->data = n;
			tmp->next = NULL;

			if (head == NULL)
			{
				head = tmp;
				 
			}
			else
			{
				node* cur = head;
				while (cur->next != NULL) { cur = cur->next; }
				cur->next = tmp;
			
			}
			size++;			
			//delete tmp;			
			return true;
		}
		void deleteNode() {
			if (!isEmpty()) {
				node* tmp = head;
				head = head->next;
			
			//	delete tmp;
			}
		}
		bool isEmpty() {
			return head == NULL;
		}
		int getNode(int i) {
			node* cur = head;
			for (int k = 0; k < i; k++) {
				cur = cur->next;
			}
			return cur->data;
		}
		int getSize() { return size; }
		 
		
	};
public:
	 
	FriendNet(const string fileName); // constructor
	FriendNet(const FriendNet& aNet); // copy constructor
	~FriendNet(); // destructor
	void listFriends(const string personName, const int hopNo);
	void displayAverageDegrees();
	void displayDiameters();

	bool searchById(int Id,Person*,int);
	bool searchById(int Id, Person&);
	bool searchByName(string personName,Person &);
	bool comparator(string a, string b);
	void dfs(int v,bool*, double& average, int &averageCounter);
	void dfsForComp(int u, bool* a, LinkedList & d);
	int* connectedDiameterGiver(int &);
	void  bfsForDiameter(int u, bool* visit, int,int& averageCounter);
private:
	void addEdges(int Id,int dest);

	int SizeOfTheNet;
	Person * arr;
	int componentNumber;

};
