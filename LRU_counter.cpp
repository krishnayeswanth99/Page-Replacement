#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

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
int timer = 0;
int faults=0;
void refer(int page, int table_size, int counter[]){
  if(presentPages.find(page)){
   // Already exists
    cout<<"Page "<<page<<" already exists in the page table"<<endl;
  }
  else if(presentPages.size() < table_size){
    //Doesn't exist - but has space
    faults++;
    cout<<"Page fault: page "<<page<<" doesn't exist in the table but the table is not full"<<endl;
    presentPages.insert(page);
    cout<<"Page "<<page<<" has been added to the page table"<<endl;
  }
  else{
    //Doesn't exist and all slots are occupied
    faults++;
    cout<<"Page fault: page "<<page<<" doesn't exist in the table and the table is full"<<endl;
    //Finding existing page with the least count
    int min = 1000000;
    int lru_page; //storage for the least recently used page
    vector<int>::iterator iter;
    for (iter = presentPages.vect.begin();iter!=presentPages.vect.end();iter++){
      if(counter[*iter] < min){
        min = counter[*iter];
        lru_page = *iter;
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
  int table_size,n,max_page=0;
  cout<<"Enter size of the page table"<<endl;
  cin>>table_size;
  cout<<"Enter no. of page references"<<endl;
  cin>>n;

  int pages[n];
  cout<<"Enter "<<n<<" space separated page references"<<endl;
  for(int i=0;i<n;i++){
    int inp;
    cin>>inp;
    pages[i] = inp;
    if(inp>max_page)
      max_page = inp;
  }

  int counter[max_page]; // Counter for LRU
  for(int i=0;i<max_page;i++)
    counter[i]=0;

  clock_t begin = clock();
  //Refer page by page
  for(int i=0;i<n;i++){
    refer(pages[i], table_size, counter);
  }
  clock_t end = clock();

  cout<<"\n\n\nTotal no. of page references: "<<n<<endl;
  cout<<"Total no. of page faults: "<<faults<<endl;
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout<<"Time taken: "<<elapsed_secs<<endl;
}
