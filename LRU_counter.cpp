#include <iostream>
#include <set>
#include <map>
using namespace std;
set<int> presentPages;
map<int, int> counter; // Counter for LRU
int timer = 0;

void refer(int page, int max_size){
  if(presentPages.find(page) != presentPages.end()){
   // Already exists
    cout<<"Page "<<page<<" already exists in the page table"<<endl;
  }
  else if(presentPages.size() < max_size){
    //Doesn't exist - but has space
    cout<<"Page fault: page "<<page<<" doesn't exist in the table but the table is not full"<<endl;
    presentPages.insert(page);
    cout<<"Page "<<page<<" has been added to the page table"<<endl;
  }
  else{
    //Doesn't exist and all slots are occupied
    cout<<"Page fault: page "<<page<<" doesn't exist in the table and the table is full"<<endl;
    //Finding existing page with the least count
    set<int>::iterator it;
    int min = 1000000;
    int lru_page; //storage for the least recently used page
    for (it = presentPages.begin(); it != presentPages.end(); it++){
      if(counter[*it] < min){
        min = counter[*it];
        lru_page = *it;
      }
    }
    cout<<"Page "<<lru_page<<" is LRU and is being replaced by page "<<page<<endl;
    presentPages.erase(lru_page);    //Remove the page with the least count;
    presentPages.insert(page);      //Adding the new page
  }
  //Compulsory statements
  timer++; //Increment the global timer
  counter[page] = timer; //Set the new page's time as the current global time.
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