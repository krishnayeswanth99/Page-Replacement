#include <iostream>
#include<ctime>
#include<vector>
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
class Pair{
  public:
  int first;
  unsigned short second;
  Pair(){

  }
  Pair(int a,unsigned short b){
    first = a;
    second = b;
  }
};

class Map{
  public:
  vector<Pair> vect;
  vector<Pair>::iterator ip;

  int size(){
    return vect.size();
  }
  void insert(int page){
    Pair p(page,0);
    vect.push_back(p);
  }
  bool find(int page){
    bool found = false;
    for(ip = vect.begin();ip != vect.end();ip++){
      if (ip->first==page){
        found = true;
        break;
      }
    }
    return found;
  }

  void erase(int page){
    for(ip = vect.begin();ip != vect.end();ip++){
      if (ip->first==page){
        vect.erase(ip);
        break;
      }
    }
  }
};

Set presentPages;
Map aging;
int faults = 0;

void refer(int page, int max_size){
  if(presentPages.find(page)){
    // Already exists
    cout<<"Page "<<page<<" already exists in the page table"<<endl;
  }
  else if(presentPages.size() < max_size){
    //Doesn't exist - but has space
    cout<<"Page fault: page "<<page<<" doesn't exist in the table but the table is not full"<<endl;
    presentPages.insert(page);
    aging.insert(page);
    cout<<"Page "<<page<<" has been added to the page table"<<endl;
    faults++;
  }
  else{
    //Doesn't exist and all slots are occupied
    cout<<"Page fault: page "<<page<<" doesn't exist in the table and the table is full"<<endl;
    //Finding existing page with the least count
    unsigned short min = 65535;
    int lru_page; //storage for the least recently used page
    vector<int>::iterator it;
    for (it = presentPages.vect.begin(); it != presentPages.vect.end(); it++){
      aging.find(*it);
      if(aging.ip->second < min){
        min = aging.ip->second;
        lru_page = *it;
      }
    }
    cout<<"Page "<<lru_page<<" is LRU and is being replaced by page "<<page<<endl;
    aging.erase(lru_page);
    aging.insert(page);
    presentPages.erase(lru_page);    //Remove the page with the least count;
    presentPages.insert(page);      //Adding the new page
    faults++;
  }
  vector<Pair>::iterator itt; 
  for(itt = aging.vect.begin();itt!=aging.vect.end();itt++){
    itt->second = itt->second>>1;
  }
  aging.find(page);
  aging.ip->second *= 32768;
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
  clock_t begin = clock();
  //Refer page by page
  for(int i=0;i<n;i++){
    refer(pages[i], max_size);
  }
  clock_t end = clock();
  cout<<"\n\n\nTotal no. of page references: "<<n<<endl;
  cout<<"Total no. of page faults: "<<faults<<endl;
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout<<"Time taken: "<<elapsed_secs<<endl;
}
