#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <cstring>

using namespace std; 

#define NUM_PAGES 3

int pageTable[NUM_PAGES]; 
int tlbIdx = 0;

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
bool found(int page, vector<int>& pageTable){
    for(int i=0;i<pageTable.size();i++){
        if(page==pageTable[i])
            return true;
    }
    return false;
}
bool foundLRU(int page, int pageTable[]){
    for(int i=0;i<3;i++){
        if(page==pageTable[i])
            return true;
    }
    return false;
}
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

int lru(char *pages[]){
    int pageFaults=0;
    int pageTable[3]={-1,-1,-1};
    for(int i =0; i<strlen(pages[1]);i+=2){
        if(foundLRU(pages[1][i], pageTable))
            continue;
        //not found in page table, so ++ pageFaults
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
        else{
            if(!foundLRU(pages[1][i]-'0', pageTable)){
                
                pageFaults++;
                for(int j=0;j<2;j++){
                    pageTable[j]=pageTable[j+1];
                }
                pageTable[2]=pages[1][i]-'0';
            }
            else{//already in page frame, need to update recently used status
               
                if(pageTable[2]==pages[1][i]-'0')
                    continue;
                else if(pageTable[1]==pages[1][i]){
                    pageTable[1]=pageTable[2];
                    pageTable[2]=pages[1][i]-'0';
                }
                else{
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
    //char pages[argc];

    int numFaults=fifo(argv);
    cout<<"Number of Faults with FIFO: "<<numFaults<<endl;

    numFaults=lru(argv);
    cout<<"Number of Faults with LRU: "<<numFaults<<endl;

    numFaults=optimal(argv);
    cout<<"Number of Faults with Optimal Page Replacement: "<<numFaults<<endl;


    // for(int i=0;i<strlen(argv[1])/2;i+=2){
    //     cout<< argv[1][i];
    // }
    // int numFaults=fifo(argv, argc);
    //cout << strlen(argv[1]);
//     for(int i=0;i<sizeof(argv[1]);i++){
//         //pages[i]=argv[1][i];
//         cout<<argv[1][i];
//         //cout <<pages[i];
//     }
    // cout<<argv[1][4];
    // for (int i=0; i<argc;i++){
    //     cout<<"i: "<<i<<"argv[i]"<<argv[i]<<endl;
        
    // }
    // cout<<strlen(argv[1])<<endl;




    // int count=0;
    // for(int i=0; i<strlen(argv[1]);i+=2){
    //     pages[count]=argv[1][i];
    //     count++;
    //     cout<<"argv:"<<argv[1][i]<<"\n"<< endl;
    //     cout<<pages[count]<<"\n"<<endl;
    // }

    

 }