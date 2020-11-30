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
    for(int i=0; i<strlen(pages[1]);i++){
        if(pages[1][i]=='0'||pages[1][i]=='1'||pages[1][i]=='2'||pages[1][i]=='3'||pages[1][i]=='4'||pages[1][i]=='5'||pages[1][i]=='6'||pages[1][i]=='7'||pages[1][i]=='8'||pages[1][i]=='9'){
            
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
    }
        
    return pageFaults;
}
// bool checkPageTable(char pageTable, char element){
//     for(int i=0;i<sizeof(pageTable);i++){
//         if(pageTable[i]==element)
//             return true;
//     }
//     return false;
// }
// int lru(char *pages[]){
//     unordered_set<char> current;
//     //unordered_map<char,int> pageTable;
//     char pageTable[3];
//     for(int i=0;i<3;i++){
//         pageTable[i]=' ';
//     }
//     int pageFaults=0;
//     for(int i=0; i<strlen(pages[1]);i++){
//         if(current.size()<NUM_PAGES){
//             if(current.find(pages[1][i])==current.end()){
//                 current.insert(pages[1][i]);
//                 pageFaults++;
//             }
//             pageTable[pages[1][i]]=i;
//         }
//         else{
//             if(current.find(pages[1][i])==current.end()){
                
//             }
//         }
//         if(!checkPageTable(pageTable, pages[1][i])){//not in page table
//             for(int i=0;i<sizeof(pageTable);i++){
//                 if(pageTable[i]==' ')
//                     pageTable[i]=pages[1][i];
//                 else{
//                     for(int i=0;i<sizeof(pageTable)-1;i++){
//                         pageTable[i]=pageTable[i+1];
//                     }
//                     pageTable[sizeof(pageTable)-1]=pages[1][i];
//                 }
//             }
//         }
//         else{//already in page table
//             for(int i=0;i<sizeof(pageTable)-1;i++){
//                 if(pageTable[i]==pages[1][i]){//found current location of page
//                     for(int j=i;j<sizeof(pageTable)-1;j++){
//                         pageTable[j]=pageTable[j+1];
//                     }
//                     pageTable[sizeof(pageTable)-1]=pages[1][i];
//                     break;
//                 }
//             }
//         }

//     }
//     return pageFaults;
// }


int main(int argc, char *argv[]){
    char pages[argc];

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

    int numFaults=fifo(argv);
    cout<<"Number of Faults:"<<numFaults<<endl;

 }