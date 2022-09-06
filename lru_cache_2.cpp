#include<bits/stdc++.h>
using namespace std;

class LRUCache{
	public:
		class Node{
			public:
				int key,value;
				Node *next,*prev;
				Node(int _key,int _value){
					key=_key;
					value=_value;
				}
		};
		Node *head = new Node(-1,-1);
		Node *tail = new Node(-1,-1);
		int cacheSize;
		unordered_map<int,Node*> TLB;
		LRUCache(int size){
			cacheSize=size;
			head->next=tail;
			tail->prev=head;
		}
		void addNode(Node *node){
			Node *temp=head->next;
			node->next=temp;
			temp->prev=node;
			node->prev=head;
			head->next=node;
		}
		void deleteNode(Node *node){
			Node *prevNode=node->prev;
			Node *nextNode=node->next;
			prevNode->next=nextNode;
			nextNode->prev=prevNode;
		}
		int get(int key){
			if(TLB.find(key)!=TLB.end()){
				Node *node_to_be_removed = TLB[key];
				int val=node_to_be_removed->value;
				TLB.erase(key);
				deleteNode(node_to_be_removed);
				addNode(node_to_be_removed);
				TLB[key]=head->next;
				return val;
			}
			return -1;
		}
		void put(int key,int value){
			if(TLB.find(key)!=TLB.end()){
				Node *address=TLB[key];
				deleteNode(address);
				TLB.erase(key);
				addNode(new Node(key,value));
				TLB[key]=head->next;
				cout<<key<<" Already In Cache. Address of "<<key<<" updated"<<endl;
			}
			else if(TLB.find(key)==TLB.end()){
				if(TLB.size()==cacheSize){
					int item_to_be_removed=tail->prev->value;
					cout<<"Cache Size Is Full, Removing Least Used Item "<<item_to_be_removed<<" and Adding New Item i.e "<<key<<endl;
					TLB.erase(tail->prev->key);
					deleteNode(tail->prev);
					addNode(new Node(key,value));
					TLB[key]=head->next;
				}
				else{
					cout<<"Adding "<<key<<" to cache at beginning"<<endl;
					addNode(new Node(key,value));
					TLB[key]=head->next;
				}
			}
			
		}
};
int main(){
	LRUCache cache(3);
	cache.put(1,1);
	cache.put(2,2);
	cache.put(3,3);
	cache.put(4,4);
	cache.put(3,3);
	cout<<cache.get(2)<<endl;
	cache.put(5,5);
	
	return 0;
}