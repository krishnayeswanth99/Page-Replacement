#include <iostream>
#include<deque>
#include<set>
#include<algorithm>
using namespace std;
set<int> presentPages;
deque<int> lru;

void refer(int page,int max_size){
  set<int>::iterator it;
  it = presentPages.find(page);
  if(it != presentPages.end()){
    // Already exists
    cout<<"Page "<<page<<" already exists in the page table"<<endl;
    deque<int>::iterator lru_it = find(lru.begin(),lru.end(),page);
    lru.erase(lru_it);
    lru.push_back(page);
  }
  else if(presentPages.size() < max_size){
    //Doesn't exist - but has space
    cout<<"Page fault: page "<<page<<" doesn't exist in the table but the table is not full"<<endl;
    presentPages.insert(page);
    lru.push_back(page);
    cout<<"Page "<<page<<" has been added to the page table"<<endl;
  }
  else{
    //Doesn't exist and all slots are occupied
    cout<<"Page fault: page "<<page<<" doesn't exist in the table and the table is full"<<endl;
    //Finding existing page with the least count
    int lru_page = lru.front();
    lru.erase(lru.begin());
    cout<<"Page "<<lru_page<<" is LRU and is being replaced by page "<<page<<endl;
    presentPages.erase(lru_page);    //Remove the page with the least count;
    presentPages.insert(page);
    lru.push_back(page);      //Adding the new page
  }
}
int main() {
  int max_size;
  int n;
  cout<<"Enter size of the page table"<<endl;
  cin>>max_size;
  cout<<"Enter no. of page references"<<endl;
  cin>>n;
  int pages[n];
  cout<<"Enter "<<n<<" space separated page references"<<endl;
  for(int i=0;i<n;i++){
    cin>>pages[i];
  }

  //Refer page by page
  for(int i=0;i<n;i++){
    refer(pages[i], max_size);
  }
}