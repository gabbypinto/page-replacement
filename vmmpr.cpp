//Katherine Hansen 2326665
//Gabriela Pinto  2318655
#include <queue>
#include <unordered_set>
#include <iostream>
#include <cstring>

using namespace std; 

#define NUM_PAGES 3

int pageTable[NUM_PAGES]; 
int tlbIdx = 0;
//FIFO replacement
int fifo(char *pages[]){
    //a set of the current values in the page table that are easily searchable
    unordered_set<char> current;
    //the page table
    queue<char> pageTable;
    int pageFaults=0;
    //cout<<pages[1];
    for(int i=0;i<strlen(pages[1]);i+=2){
            
            if(current.size()<NUM_PAGES){
                if(current.find(pages[1][i])==current.end()){
                    current.insert(pages[1][i]);
                    pageFaults++;
                    pageTable.push(pages[1][i]);

                }
            }   
            else{
                if(current.find(pages[1][i])==current.end()){
                    char front = pageTable.front();
                    pageTable.pop();
                    current.erase(front);
                    current.insert(pages[1][i]);
                    pageTable.push(pages[1][i]);
                    pageFaults++;
                }
            }
    }
        
    return pageFaults;
}
//if page is found in page table for optimal replacement
bool found(int page, vector<int>& pageTable){
    for(int i=0;i<pageTable.size();i++){
        if(page==pageTable[i])
            return true;
    }
    return false;
}
//if page is in pagetable for LRU replacement
bool foundLRU(int page, int pageTable[]){
    for(int i=0;i<3;i++){
        if(page==pageTable[i])
            return true;
    }
    return false;
}
//finding which page to delete for optimal replacement
int toDelete(char *pages[], vector<int>& pageTable, int ind){
    int next1=-1;
    int next2=-1;
    for(int j=ind;j<strlen(pages[1]);j+=2){//looking ahead at the pages
        if(found(pages[1][j], pageTable)){
            if(next1==-1)
                next1=pages[1][j];
            else{
                next2=pages[1][j];
                break;
            }
        }
            
    }
    for(int i=0;i<pageTable.size();i++){
        if(pageTable[i]==next1)
            continue;
        else if(pageTable[i]==next2)
            continue;
        else
            return pageTable[i];
        
    }
    return -1;
}
//optimal page replacement
int optimal(char *pages[]){
    vector <int> pageTable;
    int pageFaults=0;

    for(int i =0; i<strlen(pages[1]);i+=2){
        if(found(pages[1][i], pageTable))
            continue;
        //not found in page table, so ++ pageFaults
        pageFaults++;
        if (pageTable.size() < 3) {
            pageTable.push_back(pages[1][i]); 
        }   
        else { 
            int del = toDelete(pages, pageTable,i);
            for(int j=0;j<pageTable.size();j++){
                if(pageTable[j] == del)
                    pageTable[j]=pages[1][i];
            }

        } 
        
    }
    return pageFaults;
}
//least recently used
int lru(char *pages[]){
    int pageFaults=0;
    int pageTable[3]={-1,-1,-1};
    for(int i =0; i<strlen(pages[1]);i+=2){
        if(foundLRU(pages[1][i], pageTable))
            continue;
        //if page table is not full yet
        if(pageTable[0]==-1){
            pageTable[0]=pages[1][i]-'0';
            pageFaults++;
        }
        else if(pageTable[1]==-1){
            pageTable[1]=pages[1][i]-'0';
            pageFaults++;
        }
        else if(pageTable[2]==-1){
            pageTable[2]=pages[1][i]-'0';
            pageFaults++;
        }
        //if page table is already full
        else{
            if(!foundLRU(pages[1][i]-'0', pageTable)){//if it is not already in the page table
                pageFaults++;
                for(int j=0;j<2;j++){
                    pageTable[j]=pageTable[j+1];
                }
                pageTable[2]=pages[1][i]-'0';
            }
            else{//already in page frame, need to update recently used status
                if(pageTable[2]==pages[1][i]-'0')//already in the right place
                    continue;
                else if(pageTable[1]==pages[1][i]-'0'){//needs to move one spot over
                    pageTable[1]=pageTable[2];
                    pageTable[2]=pages[1][i]-'0';
                }
                else{//needs to move two spots over
                    pageTable[0]=pageTable[1];
                    pageTable[1]=pageTable[2];
                    pageTable[2]=pages[1][i]-'0';
                }
            }
        }
    }
    return pageFaults;
}

int main(int argc, char *argv[]){
    if(argc!=2){
        cout <<"Incorrect number of parameters"<<endl;
        exit(0);
    }

    int numFaults=fifo(argv);
    cout<<"Number of Faults with FIFO: "<<numFaults<<endl;

    numFaults=lru(argv);
    cout<<"Number of Faults with LRU: "<<numFaults<<endl;

    numFaults=optimal(argv);
    cout<<"Number of Faults with Optimal Page Replacement: "<<numFaults<<endl;

 }