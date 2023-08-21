#include<iostream>
#include<cstring>
#include "Buffer/StaticBuffer.h"
#include "Cache/OpenRelTable.h"
#include "Disk_Class/Disk.h"
#include "FrontendInterface/FrontendInterface.h"
using namespace std;

 

  int main(int argc, char *argv[]) {
  Disk disk_run;
  StaticBuffer buffer;
  OpenRelTable cache;

   
    for(int i = 0 ; i<=2 ; i++){
        struct RelCatEntry* relCatEntry = (struct  RelCatEntry*)malloc(sizeof(struct RelCatEntry));
        int result = RelCacheTable::getRelCatEntry(i, relCatEntry);
        if(result == SUCCESS){
          cout<<"Relation: "<<relCatEntry->relName<<endl;
          int numAttrOfRel = relCatEntry->numAttrs;
          for(int j = 0 ; j <= numAttrOfRel-1; j++){
            struct AttrCatEntry* attrCatEntry = (struct  AttrCatEntry*)malloc(sizeof(struct AttrCatEntry));
              int getAttrCatEntry_result = AttrCacheTable::getAttrCatEntry(i , j , attrCatEntry); 
              
              if(getAttrCatEntry_result == SUCCESS){
                 string attr_type = "";
                 if(attrCatEntry->attrType == 1) attr_type = "STR";
                 else attr_type = "NUM";
                cout<<"  "<<attrCatEntry->attrName<<": "<<attr_type<<endl;
              }
          }
      
        }
    }
  return 0;
}