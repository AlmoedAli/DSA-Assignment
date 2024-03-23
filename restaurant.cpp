#include "main.h"
class info
{
    public:
        int ID;
        string Name;
        int Age;
    public:
        info(const int& ID, const string& Name, const int& Age)
        {
            this->Age= Age;
            this->Name= Name;
            this->ID= ID;
        }
        info()
        {
            this->ID= this->Age= 0;
            this->Name= "";
        }
};
class Node
{
    public:
        Node* next;
        info obj;
        int St;
    public:
        Node( const int& ID, const string& Name,  const int& Age, const int& St)
        {
            obj= info(ID, Name, Age);
            this->St= St;
            this->next= NULL;
        }
        Node()
        {
            this->next= NULL;
            this->St= 0;
        }
};
class stack
{
    public:
        Node* head;
        int size;
    public:
        stack()
        {
            this->head= NULL;
            this->size= 0;
        }
        ~stack()
        {
            this->clear();
        }
        void clear()
        {
            if (this->size!= 0)
            {
                Node* temp= NULL;
                Node* removeNode= this->head;
                while (removeNode)
                {
                    temp= removeNode->next;
                    delete removeNode;
                    removeNode= temp;
                }
                temp= removeNode= NULL;
                this->size= 0;
            }
            else
                return;
        }
        Node* creatNode(const int& ID, const string& Name, const int& Age)
        {
            Node* temp= new Node(ID, Name, Age, 0);
            return temp;
        }
        bool  push(const int& ID, const string& Name, const int& Age)
        {
            if (this->size >= 2*MAXSIZE)
                return false;
            Node* temp= this->creatNode(ID, Name, Age);
            if (this->head)
            {
                temp->next= this->head;
                this->head= temp;
            }
            else
                this->head= temp;
            return true;
        }
        bool empty()
        {
            if (this->size== 0)
                return true;
            return false;
        }
        void remove(const string& Name, const int& Age)
        { 
            if (this->head)
            {
                Node* temp= this->head;
                if ((temp->obj.Name== Name) && (temp->obj.Age== Age))
                {
                    this->head= this->head->next;
                    delete temp;
                    temp= NULL;
                }
                else
                {
                    while ((temp->next->obj.Age!= Age) || (temp->next->obj.Name!= Name))
                        temp= temp->next;
                    Node* removeNode= temp->next;
                    temp->next= temp->next->next;
                    delete removeNode;
                    removeNode= NULL;
                }
            }
            else    
                return;
        }
        int amountNode()
        {
            int size= 0;
            Node* temp= this->head;
            while (temp)
            {
                size++;
                temp= temp->next;
            }
            return size;
        }
};
class Queue
{
    public:
        Node* head;
        Node* tail;
        int size;
    public:
        Queue()
        {
            this->head= this->tail= NULL;
            this->size= 0;
        }
        ~Queue()
        {
            this->clear();
        }
        Node* creatNode(const int& ID, const string& Name, const int& Age)
        {
            Node* temp= new Node(ID, Name, Age, this->size+ 1);
            return temp;
        }
        void push(const int& ID, const string& Name, const int& Age)
        {
            if (this->size>= MAXSIZE)
                return;
            Node* temp= this->creatNode(ID, Name, Age);
            this->size++;
            if (this->head)
            {
                temp->next= this->tail->next;
                this->tail->next= temp;
                this->tail= temp;           
            }
            else
            {
                this->head= this->tail= temp;
                this->head->next= this->head;
            }
        }
        void remove(const string& Name, const int& Age)
        {
            if (this->size== 0)
                return;
            else   // this->size!= 0
            {
                if (this->size== 1)
                {
                    delete this->head;
                    this->head= this->tail= NULL;
                    this->size--;
                }
                else   // this->size >= 2
                {
                    Node* temp= this->head;
                    int pivot;
                    while ((temp->next->obj.Name!= Name) || (temp->next->obj.Age!= Age))
                        temp= temp->next;
                    pivot= temp->next->St;
                    if (temp->next== this->head)
                    {
                        Node* removeNode= temp->next;
                        this->head= this->head->next;
                        temp->next= this->head;
                        delete removeNode;
                        this->size--;
                        removeNode= NULL;
                    }
                    else
                    {
                        if (temp->next== this->tail)
                        {
                            Node* removeNode= temp->next;
                            temp->next= temp->next->next;
                            delete removeNode;
                            this->tail= temp;
                            this->size--;
                            removeNode= NULL;
                        }
                        else   // temp->next != this->tail && temp->next != this->head
                        {
                            Node* removeNode= temp->next;
                            temp->next= temp->next->next;
                            delete removeNode;
                            this->size--;
                            removeNode= NULL;
                        }
                    }
                    // update STT in 
                    temp= this->tail;
                    if (temp)
                    {   
                        do
                        {
                            temp= temp->next;
                            if (temp->St > pivot)
                                temp->St-= 1;
                        } while (temp != this->tail);          
                    }
                    else
                        return;
                }
            }
        }
        info top()
        {
            if (this->size== 0)
                throw std:: out_of_range("Segmentation fault!");
            else
                return this->head->obj;
        }
        void  clear()
        {
            if (this->size== 0)
                return;
            else   // this->size!= 0
            {     // this->size >= 1
                Node* removeNode= this->tail->next;
                Node* temp= NULL;
                while (removeNode!= this->tail)
                {
                    temp= removeNode->next;
                    delete removeNode;
                    removeNode= temp;
                }
                delete removeNode;
                this->head= this->tail= removeNode= temp= NULL;
                this->size= 0;
            }
        }
        bool empty()
        {
            if (this->size== 0)
                return true;
            return false;
        }
};

int tableEmpty(restaurant*& r)
{
    int size= 0;
    table* temp= r->recentTable;
    do
    {
        temp= temp->next;
        if (temp->name== "" && temp->age== 0)
            size++;
    } while (temp!= r->recentTable);
    temp= NULL;
    return size;
}

void clearTable(restaurant*& r)
{
    table* temp= NULL;
    table* removeNode= r->recentTable->next;
    while (removeNode!= r->recentTable)
    {
        temp= removeNode->next;
        delete removeNode;
        removeNode= temp;
    }
    delete removeNode;
    removeNode= temp= r->recentTable= NULL;
}

bool checkInstruction(const string& s)
{
    if (s== "REG" || s== "REGM" || s== "CLE" || s== "PS" || s== "PQ" || s== "SQ" || s== "PT")
        return true;
    return false;
}

bool checkRestaurantFull(restaurant*& r)
{
    table* temp= r->recentTable;
    do
    {
        temp= temp->next;
        if (temp->name== "")
            return false;
    }while (temp!= r->recentTable);
    return true;
}

void REGFunction(info& Info, restaurant*& r, table*& IDREGMFu, bool flag, table*& tablePT, Queue*& queueSt,
                Queue*& queueCus, stack*& allCus)
{
    if (Info.Age > 115 || Info.Age < 16 || Info.ID > MAXSIZE || Info.ID < 0)
        return;
    if (Info.ID == 0)
    {
        if (checkRestaurantFull(r))
        {
            queueCus->push(Info.ID, Info.Name, Info.Age);
            queueSt->push(Info.ID, Info.Name, Info.Age);
            if (allCus->push(Info.ID, Info.Name, Info.Age) && flag)
                allCus->size+= 1;
        }
        else
        {
            table* temp= r->recentTable->next;
            while (true)
            {
                if (temp->name== "")
                {
                    temp->name= Info.Name;
                    temp->age= Info.Age;
                    tablePT= temp;
                    if (flag && allCus->push(Info.ID, Info.Name, Info.Age))
                        allCus->size+= 1;
                    break;
                }
                temp= temp->next;
            }
        }
    }
    else
    {
        if (checkRestaurantFull(r))
        {
                queueCus->push(Info.ID, Info.Name, Info.Age);
                queueSt->push(Info.ID, Info.Name, Info.Age);
                if (flag  && allCus->push(Info.ID, Info.Name, Info.Age))
                    allCus->size+= 1;
        }
        else 
        {
            bool flag1= false;
            table* temp= r->recentTable;
            do
            {
                temp= temp->next;
                if (temp->ID == Info.ID)
                {
                    flag1= true;
                    break;
                }
            }while (temp!= r->recentTable);

            if (flag1)   // exist ID in restaurant
            {
                if (temp->name != "")   // this table has other people
                {
                    temp= temp->next;
                    while (true)
                    {
                        if (temp->name== "")
                        {
      
                            temp->name= Info.Name;
                            temp->age= Info.Age;
                            tablePT= temp;
                            if (flag && allCus->push(Info.ID, Info.Name, Info.Age))
                                allCus->size+= 1;
                            break;
                        }
                        temp= temp->next;
                    }
                }
                else    // this table is empty
                {
                    temp->name= Info.Name;
                    temp->age= Info.Age;
                    tablePT= temp;
                    if (flag && allCus->push(Info.ID, Info.Name, Info.Age))
                        allCus->size+= 1;
                }
            }
            else    // not exist ID in table (restaurant)
            {
                table* temp= IDREGMFu->next;
                while (true)
                {
                    if (temp->name== "")
                    {
                        temp->name= Info.Name;
                        temp->age= Info.Age;
                        tablePT= temp;
                        if (flag && allCus->push(Info.ID, Info.Name, Info.Age))
                            allCus->size+= 1;
                        break;
                    }
                    temp= temp->next;
                }
            }
        }
    }
}

table* REGMFunction(info& Info, const int& Num, restaurant*& r, table*& tablePT, stack*& allCus)
{
    
    if (Info.Age < 16 || Info.Age > 115 || Num > tableEmpty(r) || Num < 1)
        return NULL;
    table* head= r->recentTable->next;
    table* tail= r->recentTable->next;
    table* temp= r->recentTable->next;
    bool flag= false;
    int distance= (head->name== "")? 1: 0;
    int tempHead= head->ID;
    do
    {
        if (tail->name!= "")
        {
            tail= tail->next;
            tempHead= head->ID;
            head= tail;
            distance= (head->name== "")? 1: 0;
        }
        else  // tail->name== ""
        {
            if (head->name=="")
            {    
                if (distance== Num)
                {
                    temp= (head->ID > temp->ID)? head: temp;
                    flag = true;
                    tempHead= head->ID;
                    head= head->next;
                    tail= tail->next;
                }
                else  // distance!= NUM
                {
                    tail= tail->next;
                    distance= (tail->name== "")? distance+ 1: distance;
                }
            }
        }
    }while (tempHead <= head->ID);
    if (flag)  // có chỗ trong nhaf hàng để gộp bàn
    {
        temp->age= Info.Age;
        temp->name= Info.Name;
        tablePT= temp;
        allCus->push(temp->ID, Info.Name, Info.Age);
        allCus->size+= Num;
        table* remove= temp->next;
        table* ptr= remove;
        for (int i= 0; i < Num -1 ; i++)
        {
            ptr= remove->next;
            if (remove->ID== r->recentTable->ID)
                r->recentTable= temp;
            delete remove;
            remove= ptr;
        }    
        temp->next= ptr;
        remove= NULL;
        ptr= NULL;
        return temp;
    }
    return NULL;
}

void CLEFunction(const int& ID, int& NumREGM, restaurant*& r, table*& IDREGMFu, table*& tablePT, stack*& allCus,
                Queue*& queueSt, Queue*& queueCus)
{
    if (ID <= 0 && ID > MAXSIZE)
        return;
    table* temp= r->recentTable;
    bool valid= false;
    // check ID is valid????
    if (temp)
    {
        do
        {
            temp= temp->next;
            if (temp->ID== ID)
            {
                valid= true;
                break;
            }
        } while (temp != r->recentTable);
    }
    // ID is valid
    if (valid)
    {
        if ((temp->name== "") && (temp->age== 0))
            return;
        if (IDREGMFu && (ID== IDREGMFu->ID))
        {
            int index= ID;
            allCus->remove(temp->name, temp->age);
            allCus->size-= NumREGM;
            temp->age= 0;
            temp->name= "";
            tablePT= temp;
            for (int i= 0; i < NumREGM -1; i++)
            {
                index++;
                if (index > MAXSIZE)
                    index= 1;
                table* newTable= new table(index, "", 0, NULL);
                if (newTable->ID== MAXSIZE)
                    r->recentTable= newTable;
                newTable->next= temp->next;
                temp->next= newTable;
                temp= newTable;
            }
            IDREGMFu= NULL;
            if (!queueCus->empty())
            {
                for (int i= 0; i < NumREGM; i++)
                {
                    info Info(queueCus->top().ID, queueCus->top().Name, queueCus->top().Age);
                    REGFunction(Info, r, IDREGMFu, false, tablePT, queueSt, queueCus, allCus);
                    queueSt->remove(queueCus->top().Name, queueCus->top().Age);
                    queueCus->remove(queueCus->top().Name, queueCus->top().Age);            
                    if (queueCus->empty())
                        break;
                } 
            }
            else
                return; 
        }
        else
        {
            
            allCus->remove(temp->name, temp->age);
            allCus->size-= 1;
            temp->name= "";
            temp->age= 0;
            tablePT= temp;
            if (!queueSt->empty())
            {
                info Info(queueCus->top().ID, queueCus->top().Name, queueCus->top().Age);
                REGFunction(Info, r, IDREGMFu, false, tablePT, queueSt, queueCus, allCus);
                queueSt->remove(queueCus->top().Name, queueCus->top().Age);
                queueCus->remove(queueCus->top().Name, queueCus->top().Age);         
            }
            else
                return;
        }
    }
    else
        return;
}

void PSFunction(const int& Num, int& NumREGM, table*& IDREGMFu, stack*& allCus)   // allCus is the stack
{
    // allCus has stack structure
    if (allCus->empty())
        cout << "Empty\n";
    else
    {
        if ((Num <= 2*MAXSIZE) && (Num >= 0))
        {
            Node* temp= allCus->head;
            if (Num== 0 || Num > allCus->amountNode())
            {
                while (temp)
                {
                    cout << temp->obj.Name << endl;
                    temp= temp->next;
                }
            }
            else  // Num != 0 && Num <= allCus->amountNode()
            {
                for (int i= 0; i < Num; i++)
                {
                    cout << temp->obj.Name << endl;
                    temp= temp->next;
                }
            }
        }
        else
            return;
    }
}

void PQFunction(const int& Num, Queue*& queueSt)
{
    // queueSt has queue structure
    if (queueSt->empty())
        cout << "Empty\n";
    else    // Queue is not empty
    {
        if ((Num <= MAXSIZE) && (Num >= 0))
        {
            Node* temp= queueSt->tail;
            if (Num == 0 || Num > queueSt->size)
            {
                do
                {   
                    temp= temp->next;
                    cout << temp->obj.Name << endl;
                }while (temp!= queueSt->tail);
            }
            else   // Num != 0 && Num <= queueSt.size
            {
                temp= temp->next;
                for (int i= 0; i < Num; i++)
                {
                    cout << temp->obj.Name << endl;
                    temp= temp->next;
                }
            }
            temp= NULL;
        }
        else
            return;
    }
}

void PTFunction(table*& tablePT)
{
    table* temp= tablePT;
    if (temp)
    {
        do
        {
            if (temp->name!= "")
                cout << temp->ID << "-" << temp->name << endl;
            temp= temp->next;
        }while (temp!= tablePT);
    }
    else
        return;
}

void SQFunction(const int& Num, Queue*& queueCus)
{
    if (queueCus->empty()) 
        cout << "Empty\n";
    else
    {
        if (Num < 1 || Num > MAXSIZE)
            return;
        Node* front= queueCus->head;
        Node* rear= NULL;
        Node* temp= NULL;
        int index= -1;
        for (front= queueCus->head; front!= queueCus->tail; front= front->next)
        {
            if (Num <= queueCus->size)
            {
                index++;
                if (index == Num)
                    break;
            }
            temp= front;
            for (rear= front->next; rear!= queueCus->head; rear= rear->next)
            {
                if (temp->obj.Age < rear->obj.Age)
                    temp= rear;
                else
                {
                    if (temp->obj.Age== rear->obj.Age)
                    {
                        if (temp->St > rear->St)
                            temp= rear;
                    }
                }
            }
            if (temp!= front)
            {
                int ID= temp->obj.ID;
                temp->obj.ID= front->obj.ID;
                front->obj.ID= ID;

                string Name= temp->obj.Name;
                temp->obj.Name= front->obj.Name;
                front->obj.Name= Name;

                int St= temp->St;
                temp->St= front->St;
                front->St= St;

                int Age= temp->obj.Age;
                temp->obj.Age= front->obj.Age;
                front->obj.Age= Age;
            }
        }
        front= rear= temp= NULL;
        temp= queueCus->tail;
        if (temp)
        {
            do
            {
                temp= temp->next;
                cout << temp->obj.Name << endl;
            } while (temp!= queueCus->tail);    
        }
        else
            return;
       
    }  
}

void simulate(string filename, restaurant* r)
{
    ifstream file(filename);
    string s= "";
    file >> s;
    string temp1, temp2, temp3;
    stack* allCus;
    Queue* queueCus;
    Queue* queueSt;
    queueCus= new Queue();
    queueSt= new Queue();
    allCus= new stack();
    int NumREGM= 0;
    table* IDREGMFu= NULL;
    table* tablePT= NULL;
    while (s!= "Binh")
    {
        temp1="", temp2="", temp3="";
        if (s== "REG")
        {
            s= "Binh";
            file >> temp1 >> temp2 >> temp3;
            if (file.eof())
            {
                if (temp3.empty())
                {
                    info Info(0, temp1, stoi(temp2));
                    REGFunction(Info, r, IDREGMFu, true, tablePT, queueSt, queueCus, allCus);
                    break;
                }
                else
                {
                    if (checkInstruction(temp3))
                    {
                        s= temp3;
                        info Info(0, temp1, stoi(temp2));
                        REGFunction(Info, r, IDREGMFu, true, tablePT, queueSt, queueCus, allCus);
                        continue;
                    }
                    else
                    {
                        info Info(stoi(temp1), temp2, stoi(temp3));
                        REGFunction(Info, r, IDREGMFu, true, tablePT, queueSt, queueCus, allCus);
                        break;
                    }
                }           
            }
            else
            {
                if (!checkInstruction(temp3))  // temp3 is not instruction
                {
                    file >> s;
                    info Info(stoi(temp1), temp2, stoi(temp3));
                    REGFunction(Info, r, IDREGMFu, true, tablePT, queueSt, queueCus, allCus);
                    continue;
                }
                else  // temp3 is instruction
                {
                    s= temp3;
                    info Info(0, temp1, stoi(temp2));
                    REGFunction(Info, r, IDREGMFu, true, tablePT, queueSt, queueCus, allCus);
                    continue;
                }
            }
        }
        else
        {
            if (s== "REGM")
            {
                s= "Binh";
                file >> temp1 >> temp2 >> temp3;
                if (file.eof())
                {
                    if (IDREGMFu)
                        break;
                    info Info(0, temp1, stoi(temp2));
                    IDREGMFu= REGMFunction(Info, stoi(temp3), r, tablePT, allCus);
                    break;
                }
                else
                {
                    if (IDREGMFu)
                    {
                        file >> s;
                        continue;
                    }
                    else
                    {
                        info Info(0, temp1, stoi(temp2));
                        IDREGMFu= REGMFunction(Info, stoi(temp3), r, tablePT, allCus);
                        if (IDREGMFu)
                            NumREGM= stoi(temp3);
                        file >> s;
                        continue;
                    }
                }                  
            }
            else
            {
                if (s== "CLE")
                {
                    s= "Binh";
                    file >> temp3;
                    if (file.eof())
                    {
                        CLEFunction(stoi(temp3), NumREGM, r, IDREGMFu, tablePT, allCus, queueSt, queueCus);
                        break;
                    }
                    else
                    {

                        CLEFunction(stoi(temp3), NumREGM, r, IDREGMFu, tablePT, allCus, queueSt, queueCus);
                        file >> s;
                        continue;
                    }
                }
                else
                {
                    if (s== "PS")
                    {
                        s= "Binh";
                        file >> temp3;
                        if (file.eof())
                        {
                            if (temp3.empty())
                            {
                                PSFunction(0, NumREGM, IDREGMFu, allCus);
                                break;
                            }
                            else
                            {
                                if (checkInstruction(temp3))
                                {
                                    PSFunction(0, NumREGM, IDREGMFu, allCus);
                                    s= temp3;
                                    continue;
                                }
                                else
                                {
                                    PSFunction(stoi(temp3), NumREGM, IDREGMFu, allCus);
                                    break;
                                }
                            }
                        }
                        else
                        {
                            if (checkInstruction(temp3))
                            {
                                s= temp3;
                                PSFunction(0, NumREGM, IDREGMFu, allCus);
                                continue;
                            }
                            else
                            {
                                file >> s;
                                PSFunction(stoi(temp3), NumREGM, IDREGMFu, allCus);
                                continue;
                            }
                        }
                    }
                    else
                    {
                        if (s== "PQ")
                        {
                            s= "Binh";
                            file >> temp3;
                            if (file.eof())
                            {
                                if (temp3.empty())
                                {
                                    PQFunction(0, queueSt);
                                    break;
                                }
                                else
                                {
                                    if (checkInstruction(temp3))
                                    {
                                        s= temp3;
                                        PQFunction(0, queueSt);
                                        continue;
                                    }
                                    else
                                    {
                                        PQFunction(stoi(temp3), queueSt);
                                        break;
                                    }
                                }
                            }
                            else
                            {
                                if (checkInstruction(temp3))
                                {
                                    s= temp3;
                                    PQFunction(0, queueSt);
                                    continue;
                                }
                                else
                                {
                                    file >> s;
                                    PQFunction(stoi(temp3), queueSt);
                                    continue;
                                }
                            }
                        }
                        else
                        {
                            if (s== "SQ")    // bắt buộc có tham số truyền vào
                            {
                                s= "Binh";
                                file >> temp3;
                                if (file.eof())
                                {
                                    SQFunction(stoi(temp3), queueCus);
                                    break;
                                }
                                else
                                {
                                    SQFunction(stoi(temp3), queueCus);
                                    file >> s;
                                    continue;
                                }
                                
                            }
                            else
                            {
                                if (s== "PT")
                                {
                                    s= "Binh";
                                    if (file.eof())
                                    {
                                        PTFunction(tablePT);
                                        break;
                                    }
                                    else
                                    {
                                        PTFunction(tablePT);
                                        file >> s;
                                        continue;
                                    }
                                }
                                else
                                    break;
                            }
                        }
                    }
                }
            }
        }
    }
    file.close();
    queueCus->clear();
    queueSt->clear();
    allCus->clear();
    delete queueCus;
    delete queueSt;
    delete allCus;
    queueCus= queueSt= NULL;
    allCus= NULL;
    clearTable(r);
    return;
}
