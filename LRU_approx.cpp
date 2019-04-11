#include <iostream>
#include<deque>
#include<set>
#include<algorithm>
#include <utility>
//0 4 1 4 2 4 3 4 2 4 0 4 1 4 2 4 3 4
using namespace std;
int timer=0;
set<int> presentPages;
int one_counter = 0;
void refer(int page,int max_size, pair<int, bool> pageTable[]){
  if(presentPages.find(page) != presentPages.end()){
    // Already exists
    cout<<"Page "<<page<<" already exists in the page table"<<endl;
    int i;
    for(i=0;i<max_size;i++){
      if(pageTable[i].first==page){
       // if(pageTable[i].second==0){
          pageTable[i].second = 1; // Giving 2nd chance
        break; 
      }
    }    
  }
  else if(presentPages.size() < max_size){
    //Doesn't exist - but has space
    cout<<"Page fault: page "<<page<<" doesn't exist in the table but the table is not full"<<endl;
    presentPages.insert(page);
    pageTable[timer] = make_pair(page, 0);
    cout<<"Page "<<page<<" has been added to the page table"<<endl;
    timer = (timer+1)%max_size;
  }
  else{
    //Doesn't exist and all slots are occupied
    cout<<"Page fault: page "<<page<<" doesn't exist in the table and the table is full"<<endl;
    //Finding next page with bool = 0
    for(int i = 0;i<max_size;i++){
      if(pageTable[timer].second==0){
        cout<<"Page "<<pageTable[timer].first<<" has been replaced by "<<page<<endl;
        presentPages.erase(pageTable[timer].first); //Removing old page from set
        pageTable[timer] = make_pair(page,0);        //Adding new page to table
        presentPages.insert(page);                //Adding new page to set
        break;
      }
      else{
        pageTable[timer].second = 0;
      }
    timer = (timer+1)%max_size;
    }
    timer = (timer+1)%max_size;
  }
}
int main() {
  int max_size;
  int n;
  cout<<"Enter size of the page table"<<endl;
  cin>>max_size;
  cout<<"Enter no. of page references"<<endl;
  cin>>n;

  pair<int, bool> pageTable[max_size];
  int pages[n];
  cout<<"Enter "<<n<<" space separated page references"<<endl;
  for(int i=0;i<n;i++){
    int x;
    cin>>x;
    pages[i] = x;
  }

  //Refer page by page
  for(int i=0;i<n;i++){
    refer(pages[i], max_size, pageTable);
  }
}