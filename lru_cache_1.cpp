#include<bits/stdc++.h>
using namespace std;

int cacheSize=3;
list<int> cache;
unordered_map<int,list<int> :: iterator> TLB;

void access(int page){
	if(TLB.find(page)==TLB.end()){
		cout << "Cache Miss. Adding page to cache...\n\t";
		if(cache.size()==3){
			cout << "All cache lines full.\n\tRemoving LRU page...\n\t";
			int page_to_be_removed=cache.back();
			cout << "Removed page"<< page_to_be_removed << endl;
			cache.pop_back();
			TLB.erase(page_to_be_removed);
			cache.push_front(page);
			TLB[page]=cache.begin();
			cout << "\tPage" << page <<" added to cache" << endl;
		}
		else{
			cache.push_front(page);
			TLB[page]=cache.begin();
			cout << "\tPage" << page <<" added to cache" << endl;
		}
	}
	else{
		cache.remove(page);
		cache.push_front(page);
		TLB[page]=cache.begin();
		cout << "Cache Hit, timeline updated\n";
	}
	cout<<endl;
}
int main(){
	access(1);
	access(2);
	access(3);
	access(1);
	access(4);
	access(5);
	access(5);
	access(1);
	access(6);
	access(4);
	return 0;
}