#include<iostream>
#include<cstdlib>
using namespace std;

struct item{
    int info;
    struct item *next;
};

class Queue{
private:
    item *tail;
    item *head;
    
public:
    Queue();
    void enqueue();
    void dequeue();
    void display();
};

Queue::Queue(){
    tail = NULL;
    head = NULL;
}

void Queue::enqueue(){
    int data;
    item *temp = new item;
    cout<<"Enter the data to enqueue: ";
    cin>>data;
    temp->info = data;
    temp->next = NULL;
    if(head == NULL){
        head = temp;
    }else{
        tail->next = temp;
    }
    tail = temp;
}

void Queue::dequeue(){
    item *temp = new item;
    if(head == NULL){
        cout<<"\nQueue is Emtpty\n";
    }else{
        temp = head;
        head = head->next;
        cout<<"The data Dequeued is "<<temp->info;
        delete temp;
    }
}

void Queue::display(){
    item *p = new item;
    p = head;
    if(head == NULL){
        cout<<"\nNothing to Display\n";
    }else{
        while(p!=NULL){
            cout<<endl<<p->info;
            p = p->next;
        }
    }
}

int main(){
    Queue queue;
    int choice;
    while(true){
        cout<<"\n1.Enqueue\n2. Dequeue\n3. Display\n 4.Quit";
        cout<<"\nEnter your choice: ";
        cin>>choice;
        switch(choice){
            case 1:
                queue.enqueue();
                break;
            case 2:
                queue.dequeue();
                break;
            case 3:
                queue.display();
                break;
            case 4:
                exit(0);
                break;
            default:
                cout<<"\nInvalid Input. Try again! \n";
                break;
        }
    }
    return 0;
}