#include <iostream>
#include <ctime>
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
Set presentPages;
Set lru;
int faults=0;
void refer(int page,int max_size){
  if(presentPages.find(page)){
    // Already exists
    cout<<"Page "<<page<<" already exists in the page table"<<endl;
    lru.find(page);
    lru.erase(page);
    lru.insert(page);
  }
  else if(presentPages.size() < max_size){
    //Doesn't exist - but has space
    faults++;
    cout<<"Page fault: page "<<page<<" doesn't exist in the table but the table is not full"<<endl;
    presentPages.insert(page);
    lru.insert(page);
    cout<<"Page "<<page<<" has been added to the page table"<<endl;
  }
  else{
    //Doesn't exist and all slots are occupied
    faults++;
    cout<<"Page fault: page "<<page<<" doesn't exist in the table and the table is full"<<endl;
    //Finding existing page with the least count
    int lru_page = *lru.vect.begin();
    lru.erase(lru_page);
    cout<<"Page "<<lru_page<<" is LRU and is being replaced by page "<<page<<endl;
    presentPages.erase(lru_page);    //Remove the page with the least count;
    presentPages.insert(page);
    lru.insert(page);      //Adding the new page
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
