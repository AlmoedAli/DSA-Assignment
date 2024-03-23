#include "main.h"

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
					this->head= this->tail= NULL;
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
};
class informCustomer
{
	public:
		int Result;
		int Campus;
		int ID;
		int Num;
        string Name;
        int order;
		informCustomer()
		{
            this->order= 1;
		}
		informCustomer(const int & Result, int Campus, int ID, const string & Name)
		{
			this->Result= Result;
			this->Campus= Campus;
			this->ID= ID;
			this->Num= 1;
            this->Name= Name;
            this->order= 1;
		}
		void setAgain()
		{
			this->Campus= this->Result= this->ID= this->Num= this->order= 0;
			this->Name= "";
		}
};
class queueCustomer
{
	public:
		class Node;
	public:	
		Node* head;
		Node* tail;
		int size;
	public:
		class Node	
		{
			private:
				informCustomer data;
				Node* next;
				friend class queueCustomer;
			public:
				Node(const informCustomer & data)
				{
					this->data= data;
					this->next= NULL;
				}
		};
		queueCustomer()
		{
			this->head= this->tail= NULL;
			this->size = 0;
		}
		void push(const informCustomer & data, bool priorityOrder)
		{
			if (priorityOrder)
			{
				if (this->head== NULL)
				{
					this->head= this->tail= new Node(data);
					this->size+= 1;
				}
				else
				{
					Node* temp= this->head;
					Node* prevTemp= NULL;
					while (temp)
					{
						if (temp->data.Name== data.Name)
						{
							temp->data.Num += 1;
							break;
						}
						else
						{
							prevTemp= temp;
							temp= temp->next;
						}
					}
					if (temp== NULL)
					{
						Node* newNode= new Node(data);
						this->tail->next= newNode;
						this->size+= 1;
						this->tail= newNode;
					}
					else
					{
						if (prevTemp== NULL)
						{
							if (this->size == 1)
								return;
							else
							{
								this->head= this->head->next;
								delete temp;
								Node* newNode= new Node(data);
								this->tail->next= newNode;
								this->tail= newNode;
							}
						}
						else
						{
							if (temp== this->tail)
								return;
							else
							{
								prevTemp->next= temp->next;
								delete temp;
								Node* newNode= new Node(data);
								this->tail->next= newNode;
								this->tail= newNode;
							}
						}
					}
				}
			}
			else
			{
				if (this->head== NULL)
				{
					this->head= this->tail= new Node(data);
					this->size+= 1;
				}
				else
				{
					Node* temp=  this->head;
					while (temp)
					{
						if (temp->data.Name== data.Name)
						{
							temp->data.Num+= 1;
							break;
						}
						else
						{
							if (temp == this->tail)
							{
								Node* newNode= new Node(data);
								this->size+= 1;
								this->tail->next= newNode;
								this->tail= newNode;
								break;
							}
							else
								temp= temp->next;
						}
					}
				}
			}
			
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
					this->head= this->tail= NULL;
					this->size-= 1;
				}
				else
				{
					Node* temp= this->head;
					this->head= this->head->next;
					delete temp;
					this->size-= 1;
				}
			}
		}
		void removeAt(informCustomer & inform)
		{
			if (this->head== NULL)
				return;
			else
			{
				if (this->size== 1)
				{
					if (this->head->data.Name== inform.Name)
					{
						delete this->head;
						this->head= this->tail= NULL;
						this->size-=1;
					}
					else	
						return;
				}
				else
				{
					Node* temp= this->head;
					Node* prevTemp= NULL;
					while (temp)
					{
						if (temp->data.Name== inform.Name)
						{
							if (prevTemp== NULL)
							{
								this->head= this->head->next;
								delete temp;
								this->size-= 1;
								break;
							}
							else
							{
								prevTemp->next= temp->next;
								if (temp== this->tail)
									this->tail= prevTemp;
								delete temp;
								this->size-= 1;
								break;
							}
						}
						else
						{
							prevTemp= temp;
							temp= temp->next;
						}
					}
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
		informCustomer top()
		{
			return this->head->data;
		}
};
class Hash
{
    public:
        int size;
        informCustomer* Array;
    public:
        Hash()
        {
			this->size= MAXSIZE/2;
			this->Array= new informCustomer[this->size];
			for (int i= 0; i < this->size; i++)
				this->Array[i].setAgain();	
		}
		void clear()
		{
			delete [] this->Array;
		}
        int hashFunction(const int & data)
        {
            return data% this->size;
        }
        void push(const informCustomer & inform)
        {
			for (int i= 0; i < this->size; i++)
			{
				if (this->Array[i].Name== inform.Name)
				{
					this->Array[i].Num += 1;
					return;
				}
			}
			int index= this->hashFunction(inform.Result);
            while (this->Array[index].Campus != 0)
            {
                if (this->Array[index].Name== inform.Name)
                {
                    this->Array[index].Num+= 1;
                    return;
                }
                index+= 1;
                index%= this->size;
            } 
            this->Array[index]= inform;
        }
        void removeAt(const informCustomer & inform)
        {
			for (int i= 0; i < this->size; i++)
			{
				if (this->Array[i].Name == inform.Name)
				{
					this->Array[i].setAgain();
					break;
				}
			}
        }
};
class AVL
{
	public:
		class Node;
	public:	
		Node* root;
	public:
		class Node
		{
			public:
				informCustomer inform;
				Node* left;
				Node* right;
				int height;
				friend class AVL;
			public:
				Node(const informCustomer & inform)
				{
					this->inform= inform;
					this->right= this->left= NULL;
					this->height= 1;
				}
		};
		AVL()
		{
			this->root= NULL;
		}
		void LRN(Node*& root)
		{
			if (root)
			{
				LRN(root->left);
				LRN(root->right);
				delete root;
				root= NULL;
			}
		}
		void clear()
		{
			this->LRN(this->root);
		}
		int getHeight(Node*& root)
		{
			if (root== NULL)
				return 0;
			else	
				return root->height;
		}
		int setHeight(Node*& root)
		{
			return (getHeight(root->left) > getHeight(root->right))? getHeight(root->left)+ 1:
																	getHeight(root->right) + 1;
		}
		void rotateRight(Node*& root)
		{
			Node* temp= root->left;
			root->left= temp->right;
			temp->right= root;
            root->height= setHeight(root);
            temp->height= setHeight(temp);
			root= temp;
		}
		void rotateLeft(Node*& root)
		{
			Node* temp= root->right;
			root->right= temp->left;
			temp->left= root;
            root->height= setHeight(root);
            temp->height= setHeight(temp);
			root= temp;
		}
		void balance(Node*& root)
		{
            if (root== NULL)
                return;
			if (this->getHeight(root->left) - this->getHeight(root->right) > 1)   // L
			{
				if (this->getHeight(root->left->left)- this->getHeight(root->left->right) >= 0)
					this->rotateRight(root);
				else
				{
					this->rotateLeft(root->left);
					this->rotateRight(root);		
				}
			}
			else
			{
				if (this->getHeight(root->right) - this->getHeight(root->left) > 1)    // R
				{
					if (this->getHeight(root->right->right) - this->getHeight(root->right->left) >= 0)
						this->rotateLeft(root);
					else
					{
						this->rotateRight(root->right);
						this->rotateLeft(root);
					}
				}
			}
			root->height= setHeight(root);
		}
		void Insert(Node*& root, const informCustomer & inform)
		{
			if (root== NULL)
				root= new Node(inform);
			else
			{
				bool flag= true;
				queueTraversal <Node* > Queue;
				Node* temp= root;
				Queue.push(temp);
				Node* front= NULL;
				while (!Queue.empty())
				{
					front= Queue.front();
					Queue.pop();
					if (front->inform.Name == inform.Name)
					{
						front->inform.Num += 1;
						flag= false;
						break;
					}
					else
					{
						if (front->left)
							Queue.push(front->left);
						if (front->right)
							Queue.push(front->right);
					}
				}
				Queue.clear();
				if (flag== true)
				{
					if (root->inform.Result < inform.Result)
						this->Insert(root->right, inform);
					else
					{
						if (root->inform.Result == inform.Result)
							this->Insert(root->right, inform);
						else
							this->Insert(root->left, inform);
					}	
					this->balance(root);
				}
				else
					return;
			}
		}
		void Remove(Node*& root, const informCustomer & inform)
		{
			if (root== NULL)
				return;
			else
			{
				if (root->inform.Result < inform.Result)
				{
					this->Remove(root->right, inform);
					this->balance(root);
				}
				else
				{
					if (root->inform.Result > inform.Result)
					{
						this->Remove(root->left, inform);
						this->balance(root);
					}
					else
					{
						if (root->inform.Name != inform.Name)
						{
							this->Remove(root->left, inform);
							this->balance(root);
							this->Remove(root->right, inform);
							this->balance(root);
						}
						else  
						{
							if (root->left== NULL && root->right== NULL)
							{
								delete root;
								root= NULL;
							}
							else
							{
								if (root->left== NULL || root->right== NULL)
								{
									Node* temp= root;
									root= (root->left== NULL)? root->right: root->left;
									delete temp;
								}
								else
								{
									Node* temp= root->right;
									while (temp->left!= NULL)
										temp= temp->left;
									root->inform= temp->inform;
									Remove(root->right, temp->inform);
								}
							}
							this->balance(root);
						}

					}
				}
			}
		}
		void insert(const informCustomer & inform)
		{
			this->Insert(this->root, inform);
		}
		void remove(const informCustomer & inform)
		{
			this->Remove(this->root, inform);
		}
		void printAVL()
		{
			Node* temp= this->root;
			if (temp)
			{
				queueTraversal <Node* > Queue;
				Queue.push(temp);
				Node* front= NULL;
				while (!Queue.empty())
				{
					front= Queue.front();
					Queue.pop();
					cout << front->inform.ID << "-" << front->inform.Result << "-" << front->inform.Num << endl;
					if (front->left)
						Queue.push(front->left);
					if (front->right)
						Queue.push(front->right);
				}
				Queue.clear();
			}
			else
				return;
		}
};
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
		void LRN( Node*& root)
		{
			if (root)
			{
				this->LRN(root->left);
				this->LRN(root->right);
				delete root;
				root= NULL;
			}
		}
		void clear()
		{
			this->LRN(this->root);
			delete [] this->Array;
		}
		void heapify(int index)
		{
			int min= index;
			int left= 2* index+ 1;
			int right= 2* index+ 2;
			if (left < this->size)
			{
				if (this->Array[left]->freq < this->Array[min]->freq)
					min= left;
				else
				{
					if (this->Array[left]->freq== this->Array[min]->freq)
					{
						if (this->Array[left]->character == '|' || this->Array[min]->character== '|')
						{
							if (this->Array[left]->stt < this->Array[min]->stt)
								min= left;
						}
						else
						{
							if (this->Array[left]->character < this->Array[min]->character)
								min= left;
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
class Heap
{
	public:
		class Node;
    private:
        informCustomer* Array;
        int size;
        int count;
        int STT;
    public:
        Heap()
        {
            this->size= MAXSIZE;
            this->Array= new informCustomer[this->size];
			for (int i= 0; i < this->size; i++)
				this->Array[i].setAgain();
            this->count= 0;
            this->STT= 0;
        }
		void swap(informCustomer & a, informCustomer & b)
		{
			informCustomer temp= a;
			a= b;
			b= temp;
		}
        void reHeapDown(int index)
        {
            int priority= index;
            int left= 2* index+ 1;
            int right= 2* index+ 2;
            if (left < this->count)
            {
                if (this->Array[left].Num < this->Array[priority].Num)
                    priority= left;
                else
                {
                    if (this->Array[left].Num == this->Array[priority].Num)
                    {
                        if (this->Array[left].order < this->Array[priority].order)
                            priority = left;
                    }
                }
            }
            if (right < this->count)
            {
                if (this->Array[right]. Num < this->Array[priority].Num)
                    priority= right;
                else
                {
                    if (this->Array[right].Num == this->Array[priority].Num)
                    {
                        if (this->Array[right].order < this->Array[priority].order)
                            priority = right;
                    }
                }
            }
            if (priority != index)
            {
                this->swap(this->Array[index], this->Array[priority]);
                reHeapDown(priority);
            }
        }
        void reHeapUp(int index)
        {
            while (index > 0)
            {
                int parent= (index-1)/2;
                if (this->Array[parent].Num > this->Array[index].Num)
                {
                    this->swap(this->Array[parent], this->Array[index]);
                    index= parent;
                }
                else 
                {
                    if (this->Array[parent].Num == this->Array[index].Num)
                    {
                        if (this->Array[parent].order > this->Array[index].order)
                        {
                            this->swap(this->Array[parent], this->Array[index]);
                            index= parent;
                        }
                        else
                            break;
                    }
                    else
                        break;
                }
            }
        }
        void push(const informCustomer & inform)
        {
			if (this->count== 0)
			{
				this->Array[this->count]= inform;
				this->Array[this->count].order= this->STT;
				this->count+= 1;
				this->STT+= 1;
				int index= this->count-1;
				this->reHeapUp(index);
			}
			else // this->count >= 1
			{
				for (int i= 0; i < this->count; i++)
				{
					if (this->Array[i].Name == inform.Name)
					{
						if (i== this->count- 1)
						{
							this->Array[i].Num += 1;
							this->reHeapUp(i);
							return;
						}
						else
						{
							this->Array[i].Num += 1;
							informCustomer temp= this->Array[i];
							this->Array[i]= this->Array[this->count-1];
							this->count-= 1;
							this->reHeapUp(i);
							this->reHeapDown(i);
							this->Array[this->count]= temp;
							this->count+= 1;
							this->reHeapUp(this->count-1);
							return;
						}			
					}
				}
				this->Array[this->count]= inform;
				this->Array[this->count].order= this->STT;
				this->count+= 1;
				this->STT+= 1;
				int index= this->count-1;
				this->reHeapUp(index);
			}      
        }
        void pop()
        {
			if (this->count == 1)
				this->count-= 1;
			else
			{
				if (this->count== 0)
					return;
				else
				{
					this->Array[0]= this->Array[this->count-1];
					this->count-= 1;
					this->reHeapDown(0);
				}
			}
           
        }
        void removeAt(informCustomer & inform)
        {
            for (int i= 0; i < this->count; i++)
            {
                if (this->Array[i].Name == inform.Name)
                {  
					if (i== this->count- 1)
						this->count-= 1;
					else
					{
						this->Array[i].setAgain();
						this->Array[i]= this->Array[this->count-1];
                    	this->count-= 1;
						reHeapUp(i);
                   		reHeapDown(i);
                    	break;
					}      
                }
            }
        }
        informCustomer top()
        {
            return this->Array[0];
        }
        void clear()
        {
            delete [] this->Array;
        }
		void printPreorderFoo(int index)
		{
			if (index < this->count)
			{
				cout << this->Array[index].ID << "-" << this->Array[index].Num << endl;
				this->printPreorderFoo(index*2+ 1);
				this->printPreorderFoo(2*index + 2);
			}
		}
		void printPreorder()
        {
			this->printPreorderFoo(0);
        }
};
class CampusGeneral
{
	public:
		informCustomer* Table;
		AVL Tree;
        Hash Hashing;
        queueCustomer queueCampus1;
        queueCustomer queueCampus2;
	public:
		CampusGeneral()
		{
			this->Table= new informCustomer[MAXSIZE];
			for (int i= 0; i < MAXSIZE; i++)
				this->Table[i].setAgain();
		}
		void insert(const int& Result, const string & Name, queueCustomer & queueFIFO, queueCustomer & queueLRCO, Heap & minHeapLFCO)
		{
			bool flag= true;
			int index= 0;
			for (; index < MAXSIZE; index++)
			{
				if (this->Table[index].Campus != 0)
				{
					if (this->Table[index].Name == Name)
					{
						this->Table[index].Num+= 1;
						flag= false;
						break;
					}
				}
			}
			if (this->queueCampus1.size+ this->queueCampus2.size < MAXSIZE)
			{
				if (flag== true)
				{
					index= Result%MAXSIZE;
					while (this->Table[index].Campus!= 0)
					{
						index+=1 ;
						index%= MAXSIZE;
					}
					if (Result%2== 0)  // enter kv 2
					{
						if (this->queueCampus2.size < MAXSIZE/2)
						{	
							this->Table[index]= informCustomer(Result, 2, index+ 1, Name);
							this->Tree.insert(this->Table[index]);
							this->queueCampus2.push(this->Table[index], false);
						}
						else   // this->sizeCampus2 >= MAXSIZE/2 
						{
							if (this->queueCampus1.size < MAXSIZE/2)
							{
								this->Table[index]= informCustomer(Result, 1, index+ 1, Name);
								this->Hashing.push(this->Table[index]);
								this->queueCampus1.push(this->Table[index], false);
							}
						}
					}
					else    // kv1
					{
						if (this->queueCampus1.size < MAXSIZE/2)
						{
							this->Table[index]= informCustomer(Result, 1, index+ 1, Name);
							this->Hashing.push(this->Table[index]);
							this->queueCampus1.push(this->Table[index], false);
						}
						else   // this->sizecampus1 >= MAXSIZE/2
						{
							if (this->queueCampus2.size < MAXSIZE/2)
							{
								this->Table[index]= informCustomer(Result, 2, index+ 1, Name);
								this->Tree.insert(this->Table[index]);
								this->queueCampus2.push(this->Table[index], false);
							}
						}
					}
				}
				else   // flag== false
				{
					if (this->Table[index].Campus == 1)
					{
						this->queueCampus1.push(this->Table[index], false);
						this->Hashing.push(this->Table[index]);
					}
					else
					{
						if (this->Table[index].Campus ==2)
						{
							this->queueCampus2.push(this->Table[index], false);
							this->Tree.insert(this->Table[index]);
						}
						else
							return;
					}
				}
                queueFIFO.push(this->Table[index], false);
				queueLRCO.push(this->Table[index], true);
                minHeapLFCO.push(this->Table[index]);
			}
			else   // this->sizeCampus1+ this->sizeCampus2 >= MAXSIZE
			{
				if (flag== true)
				{
					int OTP= Result% 3;
					if (OTP== 0)
						this->FIFOfunction(queueFIFO, queueLRCO, minHeapLFCO);
					else
					{
						if (OTP== 1)
							this->LRCOfunction(queueFIFO, queueLRCO, minHeapLFCO);
						else
						{
							if (OTP== 2)
								this->LFCOfunction(queueFIFO, queueLRCO, minHeapLFCO);
							else
								return;
						}
					}
					this->insert(Result, Name, queueFIFO, queueLRCO, minHeapLFCO);
				}
				else
				{
					queueFIFO.push(this->Table[index], false);
					queueLRCO.push(this->Table[index], true);
					minHeapLFCO.push(this->Table[index]);
					if (this->Table[index].Campus== 1)
					{
						this->queueCampus1.push(this->Table[index], false);
						this->Hashing.push(this->Table[index]);
					}
					else
					{
						if (this->Table[index].Campus == 2)
						{
							this->queueCampus2.push(this->Table[index], false);
							this->Tree.insert(this->Table[index]);
						}
						else
							return;
					}
				}
			}
		}
		void FIFOfunction(queueCustomer & queueFIFO, queueCustomer & queueLRCO, Heap & minHeapLFCO)
		{
			informCustomer inform = queueFIFO.top();
			queueFIFO.pop();
			this->Table[inform.ID-1].setAgain();
			if (inform.Campus == 1)
            {
				this->Hashing.removeAt(inform);
                this->queueCampus1.removeAt(inform);
                minHeapLFCO.removeAt(inform);
				queueLRCO.removeAt(inform);
            }
			else
			{
				if (inform.Campus == 2)
                {
                    this->Tree.remove(inform);
                    this->queueCampus2.removeAt(inform);
                    minHeapLFCO.removeAt(inform);
					queueLRCO.removeAt(inform);
                }
				else	
					return;
			}	
		}
		void LRCOfunction(queueCustomer & queueFIFO, queueCustomer & queueLRCO, Heap & minHeapLFCO)
		{ 
			informCustomer inform = queueLRCO.top();
			this->Table[inform.ID - 1].setAgain();
			queueLRCO.pop();
			if (inform.Campus == 1)
			{
				this->Hashing.removeAt(inform);
				this->queueCampus1.removeAt(inform);
				queueFIFO.removeAt(inform);
				minHeapLFCO.removeAt(inform);
			}
			else
			{
				if (inform.Campus == 2)
				{
					this->Tree.remove(inform);
					this->queueCampus2.removeAt(inform);
					queueFIFO.removeAt(inform);
					minHeapLFCO.removeAt(inform);
				}
				else
					return;
			}
		}
		void LFCOfunction(queueCustomer & queueFIFO, queueCustomer & queueLRCO, Heap & minHeapLFCO)
		{
            informCustomer inform = minHeapLFCO.top();
            this->Table[inform.ID- 1].setAgain();
            minHeapLFCO.pop();
            if (inform.Campus == 1)
            {
                this->Hashing.removeAt(inform);
                this->queueCampus1.removeAt(inform);
                queueFIFO.removeAt(inform);
				queueLRCO.removeAt(inform);
            }
            else
			{
                if (inform.Campus== 2)
                {
                    this->Tree.remove(inform);
                    this->queueCampus2.removeAt(inform);
                    queueFIFO.removeAt(inform);
					queueLRCO.removeAt(inform);
                }
				else
					return;
			}            
		}
		void clear()
		{
           
            this->Tree.clear();
            this->Hashing.clear();
			this->queueCampus1.clear();
			this->queueCampus2.clear();
			delete [] this->Table;
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
		temp= KQ.substr(KQ.size()- 15);
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
void REGfunction(string & informString, queueCustomer & queueFIFO, queueCustomer & queueLRCO, Heap & minHeapLFCO, CampusGeneral & objCampusGeneral)
{
	int size= 52;
	int Array[size];
	Statics(informString, Array, size);
	int count= 0;
	for (int i= 0; i < size; i++)
		if (Array[i]!= 0)
			count+= 1;
	double Result;
	string KQ= "";
	string temp= "";
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
			hfTree.replaceCoding(temp, KQ, informString[i]);
		}
		hfTree.clear();
	}
	Result= changeBinaryToDecimal(KQ);
	objCampusGeneral.insert(Result, informString, queueFIFO, queueLRCO, minHeapLFCO);
}
void CLEfunction(int & Num, CampusGeneral & objCampusGeneral, Heap & minHeapLFCO, queueCustomer & queueFIFO, queueCustomer & queueLRCO)
{
	if (Num < 1)
	{
		while (objCampusGeneral.queueCampus1.size != 0)
		{
			informCustomer inform = objCampusGeneral.queueCampus1.top();
			objCampusGeneral.queueCampus1.pop();
			queueFIFO.removeAt(inform);
			queueLRCO.removeAt(inform);
			minHeapLFCO.removeAt(inform);
			objCampusGeneral.Hashing.removeAt(inform);
			objCampusGeneral.Table[inform.ID- 1].setAgain();
		}
	}
	else   // Num >= 1
	{
		if (Num > MAXSIZE)
		{
			while (objCampusGeneral.queueCampus2.size != 0)
			{
				informCustomer inform = objCampusGeneral.queueCampus2.top();
				objCampusGeneral.queueCampus2.pop();
				queueFIFO.removeAt(inform);
				queueLRCO.removeAt(inform);
				minHeapLFCO.removeAt(inform);
				objCampusGeneral.Tree.remove(inform);
				objCampusGeneral.Table[inform.ID- 1].setAgain();
			}
		}
		else   // Num <= MAXSIZE
		{
			if (objCampusGeneral.Table[Num-1].Campus == 1)
			{
				
				objCampusGeneral.queueCampus1.removeAt(objCampusGeneral.Table[Num -1]);
				objCampusGeneral.Hashing.removeAt(objCampusGeneral.Table[Num -1]);
				minHeapLFCO.removeAt(objCampusGeneral.Table[Num-1]);
				queueFIFO.removeAt(objCampusGeneral.Table[Num -1]);
				queueLRCO.removeAt(objCampusGeneral.Table[Num-1]);
				objCampusGeneral.Table[Num-1].setAgain();
			}
			else
			{
				if (objCampusGeneral.Table[Num-1].Campus == 2)
				{
					//cout << Num << endl;
					objCampusGeneral.queueCampus2.removeAt(objCampusGeneral.Table[Num-1]);
					objCampusGeneral.Tree.remove(objCampusGeneral.Table[Num-1]);
					minHeapLFCO.removeAt(objCampusGeneral.Table[Num-1]);
					queueFIFO.removeAt(objCampusGeneral.Table[Num -1]);
					queueLRCO.removeAt(objCampusGeneral.Table[Num -1 ]);
					objCampusGeneral.Table[Num-1].setAgain();
				}
				else
					return;
			}
		}
	}	
}
void printMHfunction(Heap & minHeapLFCO)
{
	minHeapLFCO.printPreorder();
}
void printAVLfunction(CampusGeneral & objCampusGeneral)
{
	objCampusGeneral.Tree.printAVL();
}	
void printHTfunction(CampusGeneral & objCampusGeneral)
{
	for (int i= 0; i < objCampusGeneral.Hashing.size; i++)
	{ 
		if (objCampusGeneral.Hashing.Array[i].Name != "")
		{
			cout << objCampusGeneral.Hashing.Array[i].ID << "-" <<
			objCampusGeneral.Hashing.Array[i].Result << "-" << 
			objCampusGeneral.Hashing.Array[i].Num << endl;
		}
		
	}
}
void simulate(string filename)
{
	Heap minHeapLFCO;
	CampusGeneral objCampusGeneral;
	queueCustomer queueFIFO;
	queueCustomer queueLRCO;
	stringstream ss;
	ifstream file(filename);
	string tempString, instructionString, informString, temp;
	int Num;
	while (!file.eof())
	{
		tempString= instructionString= informString= temp= "";
		ss.clear();
		getline(file, tempString);
		if (tempString == "")
			continue;
		int amountCommon= 0;
		for (int i= 0; i < tempString.size(); i++)
		{
			if (tempString[i]== ' ')
			{
				amountCommon+= 1;
				if (amountCommon== 2)
					break;
			}
		}
		if (amountCommon== 1 || amountCommon== 0)
		{
			ss << tempString;
			if (amountCommon== 1)
			{
				ss >> instructionString;
				if (instructionString == "REG")
				{
					ss >> informString;
					if (informString == "")
					{
						while (!ss.eof())
							ss >> temp;
					}
					else
					{
						bool flag= true;
						for (int i= 0; i < informString.size(); i++)
						{
							if (informString[i] < 'A' || informString[i] > 'Z' && 
								informString[i] < 'a' || informString[i] > 'z')
							{
								flag= false;
								break;
							}
						}
						if (flag)
						{
							//cout << informString << endl;
							REGfunction(informString, queueFIFO, queueLRCO, minHeapLFCO, objCampusGeneral);
						}
						else
						{
							while (!ss.eof())
								ss >> temp;
						}
					}
				}
				else
				{
					if (instructionString == "CLE")
					{
						ss >> informString;
						if (informString == "")
						{
							while (!ss.eof())
								ss >> temp;
						}
						else
						{
							if (informString.size()== 1)
							{
								if (informString[0] >= '0' && informString[0] <= '9')
								{
									Num= stoi(informString);
									CLEfunction(Num, objCampusGeneral, minHeapLFCO, queueFIFO, queueLRCO);
									//cout << Num << endl;
								}
								else
								{
									while (!ss.eof())
										ss >> temp;
								}
							}
							else
							{
								bool flag= true;
								if (informString[0]== '-')
								{
									for (int i= 1; i < informString.size(); i++)
									{
										if (informString[i] < '0' || informString[i] > '9')
										{
											flag= false;
											break;
										}
									}
								}
								else
								{
									for (int i= 0; i < informString.size(); i++)
									{
										if (informString[i] < '0' || informString[i] > '9')
										{
											flag= false;
											break;
										}
									}
								}
								
								if (flag)
								{
									Num= stoi(informString);
									CLEfunction(Num, objCampusGeneral, minHeapLFCO, queueFIFO, queueLRCO);
									// cout << Num << endl;
								}
								else
								{
									while (!ss.eof())
										ss >> temp;
								}
							}
						}
					}
					else
						while (!ss.eof())
							ss >> temp;
				}
			}
			else    //// amountCommon == 0
			{
				ss >> instructionString;
				if (instructionString== "PrintAVL")
				{
					//cout << instructionString << endl;
					printAVLfunction(objCampusGeneral);
				}
				else
				{
					if (instructionString== "PrintHT")
					{
						//cout << instructionString << endl;
						printHTfunction(objCampusGeneral);
					}
					else
					{
						if (instructionString== "PrintMH")
						{
							//cout << instructionString << endl;
							printMHfunction(minHeapLFCO);
							
						}
						else
						{		
							while (!ss.eof())
								ss >> temp;
						}
					}
				}
			}
		}
	}
	minHeapLFCO.clear();
	queueFIFO.clear();
	queueLRCO.clear();
	objCampusGeneral.clear();
	return;
}