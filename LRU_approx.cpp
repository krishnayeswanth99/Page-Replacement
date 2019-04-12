#include <iostream>
#include<vector>
//0 4 1 4 2 4 3 4 2 4 0 4 1 4 2 4 3 4
using namespace std;

class Pair{
  public:
  int first;
  bool second;
  
  Pair(){

  }
  Pair(int a, int b){
    first = a;
    second = b;
  }
};

class Set{
  public:
  vector<int> vect;
  vector<int>::iterator it;

  int size(){
    return vect.size();
  }
  void insert(int page){
    vect.push_back(page);
  }

  bool find(int page){
    bool found = false;
    for(it = vect.begin();it != vect.end();it++){
      if (*it==page){
        found = true;
        break;
      }
    }
    return found;
  }

  void erase(int page){
    for(it = vect.begin();it != vect.end();it++){
      if (*it==page){
        vect.erase(it);
        break;
      }
    }
  }
};

Set presentPages;
int timer=0;
int one_counter = 0;
int faults=0;
void refer(int page,int max_size, Pair pageTable[]){
  if(presentPages.find(page)){
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
    faults++;
    cout<<"Page fault: page "<<page<<" doesn't exist in the table but the table is not full"<<endl;
    presentPages.insert(page);
    pageTable[timer] = Pair(page, 0);
    cout<<"Page "<<page<<" has been added to the page table"<<endl;
    timer = (timer+1)%max_size;
  }
  else{
    //Doesn't exist and all slots are occupied
    faults++;
    cout<<"Page fault: page "<<page<<" doesn't exist in the table and the table is full"<<endl;
    //Finding next page with bool = 0
    for(int i = 0;i<max_size;i++){
      if(pageTable[timer].second==0){
        cout<<"Page "<<pageTable[timer].first<<" has been replaced by "<<page<<endl;
        presentPages.erase(pageTable[timer].first); //Removing old page from set
        pageTable[timer] = Pair(page,0);        //Adding new page to table
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

  Pair pageTable[max_size];
  int pages[n];
  cout<<"Enter "<<n<<" space separated page references"<<endl;
  for(int i=0;i<n;i++){
    int x;
    cin>>x;
    pages[i] = x;
  }

  clock_t begin = clock();
  //Refer page by page
  for(int i=0;i<n;i++){
    refer(pages[i], max_size, pageTable);
  }
  clock_t end = clock();

  cout<<"\n\n\nTotal no. of page references: "<<n<<endl;
  cout<<"Total no. of page faults: "<<faults<<endl;
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout<<"Time taken: "<<elapsed_secs<<endl;
}
