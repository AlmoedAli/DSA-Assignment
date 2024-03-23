// build Huffman tree
#include<bits/stdc++.h> 
#include <iostream>
#include <vector>
using namespace std;
class huffTree
{
	public:
		class Node;
	private:
		Node* root;
		Node** Array;
		int size;
		int STT;
	public:
		class Node
		{
			private:
				int freq;
				char character;
				int stt;
				Node* left;
				Node* right;
				friend class huffTree;
			public:
				Node(const char& character, const int & freq, int stt= 0)
				{
					this->left= this->right= NULL;
					this->character= character;
					this->freq= freq;
					this->stt= stt;
				}
				Node()
				{

				}
		};
		void swap(Node*&  temp1, Node*& temp2)
		{
			Node* temp= temp1;
			temp1= temp2;
			temp2= temp;
		}
		huffTree(const int& size, int Array[], const int & Arraysize)
		{
			this->size=  this->STT= 0;
			this->root= NULL;
			this->Array= new Node*[size];
			for (int i= 0; i < Arraysize; i++)
			{
				if (Array[i] != 0)
				{
					if (i >= 0 && i <= 25)
					{
						Node* newNode= new Node(char (i+ 65), Array[i]);
						this->Array[this->size]= newNode;
					}
					else
					{
						if (i >= 26 && i <= 51)
						{
							Node* newNode=  new Node(char(i+ 65+ 6), Array[i]);
							this->Array[this->size]= newNode;
						}
					}
					this->size+= 1;
				}
		
			}
		}
		~huffTree()
		{
			this->clear(this->root);
			delete [] this->Array;
			//cout << "oke";
		}
		void clear(Node*& root)
		{
			if (root)
			{
				clear(root->left);
				clear(root->right);
				delete root;
				root= NULL;
			}
		}
		void heapify(int index)
		{
			int min= index;
			int left= 2* index+ 1;
			int right= 2* index+ 2;
			if (left < this->size)
			{
				if (this->Array[left]->freq < this->Array[min]->freq)
				{
					min= left;
				}
				else   // this->Array[left]->freq  >= this->Array[min]->freq
				{
					if (this->Array[left]->freq== this->Array[min]->freq)
					{
						if (this->Array[left]->character == '|' || this->Array[min]->character== '|')
						{
							if (this->Array[left]->stt < this->Array[min]->stt)
							{
								min= left;
							}
						}
						else
						{
							if (this->Array[left]->character < this->Array[min]->character)
							{
								min= left;
							}
						}
					}
				}
			}
			if (right < this->size)
			{
				if (this->Array[right]->freq < this->Array[min]->freq)
					min= right;
				else
				{
					if (this->Array[right]->freq== this->Array[min]->freq)
					{
						if (this->Array[right]->character== '|' || this->Array[min]->character== '|')
						{
							if (this->Array[right]->stt < this->Array[min]->stt)
								min= right;
						}
						else
						{
							if (this->Array[right]->character < this->Array[min]->character)
								min= right;
						}
					}
				}
			}
			if (min != index)
			{
				swap(this->Array[min], this->Array[index]);
				heapify(min);
			}
		}
		void pop()
		{
			this->Array[0]= this->Array[this->size-1];
			this->size-= 1;
			heapify(0);
		}
		void push(Node*& temp)
		{
			this->Array[this->size]= temp;
			this->size+= 1;
			if (this->size== 1)
				return;
			else
			{
				int i= this->size - 1;
				while (i > 0)
				{
					int parent= (i-1)/2;
					if (this->Array[parent]->freq > this->Array[i]->freq)
					{
						swap(this->Array[i], this->Array[parent]);
						i= parent;
					}
					else
					{
						if (this->Array[parent]->freq== this->Array[i]->freq)
						{
							if (this->Array[parent]->character == '|' || this->Array[i]->character== '|')
							{
								if (this->Array[parent]->stt > this->Array[i]->stt)
								{
									swap(this->Array[i], this->Array[parent]);
									i= parent;
								}
								else
									break;
							}
							else
							{
								if (this->Array[parent]->character > this->Array[i]->character)
								{
									swap(this->Array[parent], this->Array[i]);
									i= parent;
								}
								else
									break;
							}
						}
						else
							break;
					}
				}
			}
		}
		void buildHuffTree()
		{
			for (int i = (this->size-2)/2; i>= 0; i--)
				heapify(i);
			this->printArray();
			cout << endl;
			while (this->size > 1)
			{
				Node* tempLeft= this->Array[0];
				this->pop();
				
				Node* tempRight= this->Array[0];
				this->pop();
				
				this->STT+= 1;
				Node* newNode= new Node('|', tempLeft->freq+ tempRight->freq, this->STT);
				newNode->left= tempLeft;
				newNode->right= tempRight;
				
				this->push(newNode);
				
			}
			
			this->root= this->Array[0];
		}
		void printArray()
		{
			for (int i= 0; i < this->size; i++)
				cout << this->Array[i]->character << " " << this->Array[i]->freq << endl;
		}
		// void print(Node*& root, int space)
		// {
		// 	if (root)
		// 	{
		// 		print(root->right, space+ 10);
		// 		for (int i= 10; i < space+ 10; i++)
		// 			cout << " ";
		// 		if (root->left== NULL && root->right== NULL)
		// 			cout << root->freq << " " << root->character << endl;
		// 		else
		// 			cout << root->freq << endl;
		// 		print(root->left, space+ 10);
		// 	}
		// }
		// void printhfTree()
		// {
		// 	this->print(this->root, 0);
		// }	
		Node* getroot()
		{
			return this->root;
		}
		void encode(Node* root, string temp, string & KQ, char &character)
		{
			if (root== NULL)
				return;
			if(root->character != character)
			{
				encode(root->left, temp+ "0", KQ, character);
				encode(root->right, temp+ "1", KQ, character);
			}
			else
			{
				KQ+= temp;
				return;
			}
		}
		void replaceCoding(string & temp, string & KQ, char character)
		{
			this->encode(this->root, temp, KQ, character);
		}
};
void Statics(string & informString, int Array [], int size)
{
	for (int i= 0; i < size; i++)
		Array[i]= 0;
	for (int i= 0; i < informString.size(); i++)
	{
		if (informString[i] >= 'A' && informString[i] <= 'Z')
			Array[int(informString[i])-65]+= 1;
		else
		{
			if (informString[i] >= 'a' && informString[i] <= 'z')
				Array[int(informString[i])- 65- 6]+= 1;
		}
	}
}
double changeBinaryToDecimal(string & KQ)
{
	double Result= 0;
	double a= 1;
	string temp;
	if (KQ.size() <= 15)
		temp= KQ;
	else
	{
		temp= KQ.substr(KQ.size()- 15);
	}
	for (int i= temp.size()-1; i >= 0; i--)
	{
		if (temp[i]== '1')
		{
			Result+= a;
		}
		a*= 2;
	}
	return Result;
}
void REGfunction(string & informString)
{
	int size= 52;
	int Array[size];
	Statics(informString, Array, size);
	int count= 0;
	string KQ= "";
	string temp= "";
	for (int i= 0; i < size; i++)
		if (Array[i]!= 0)
			count+= 1;
	double Result;
	if (count== 1)
	{
		if (informString.size() > 1)
		{
			for (int i= 0; i < informString.size(); i++)
				KQ+= "1";
		}
		else
			KQ= "1";
	}
	else
	{
		huffTree hfTree(count, Array, size);
		hfTree.buildHuffTree();
		for (int i= 0; i < informString.size(); i++)
		{
			temp= "";
			if (informString[i] >= 'a' && informString[i] <= 'z')
				hfTree.replaceCoding(temp, KQ, informString[i]);
			else
			{
				if (informString[i] >= 'A'  && informString[i] <= 'Z')
					hfTree.replaceCoding(temp, KQ, informString[i]);
			}
		}
	}
	Result= changeBinaryToDecimal(KQ);
	cout << Result << endl;
}
template <class T>
class queueTraversal
{
	public:
		class Node;
	private:
		Node* head;
		Node* tail;
		int size;
	public:
		class Node
		{
			private:
				T data;
				Node* next;
				friend class queueTraversal;
			public:
				Node(const T & data)
				{
					this->data= data;
					this->next= NULL;
				}
		};
		queueTraversal()
		{
			this->head= this->tail= NULL;
			this->size= 0;
		}
		void push (const T & data)
		{
			Node* newNode= new Node(data);
			this->size+= 1;
			if (this->head== NULL)
				this->head= this->tail= newNode;
			else
			{
				this->tail->next= newNode;
				this->tail= newNode;
			}
		}
		T front()
		{
			return this->head->data;
		}
		void pop()
		{
			if (this->head== NULL)
				return;
			else
			{
				if (this->size== 1)
				{
					delete this->head;
					//delete this->tail;
					//this->head= this->tail= NULL;
					this->size-= 1;
				}
				else
				{
					Node* temp= this->head;
					this->head= this->head->next;
					this->size-= 1;
					delete temp;
				}
			}
		}
		void clear()
		{
			while (this->size != 0)
			{
				this->pop();
			}
		}
		bool empty()
		{
			if (this->size== 0)
				return true;
			else
				return false;
		}
		int getsize()
		{
			return this->size;
		}
		Node* getRoot()
		{
			return this->head;
		}
		int getdata()
		{
			return this->head->data;
		}
};
int main()
{
	int * newNode= new int (10);
	int * a= newNode;
	int * b= newNode;
	cout << * a << endl <<  * b << endl;
	delete a;
	cout << *b << endl;
	delete b;
	cout << * b;
}