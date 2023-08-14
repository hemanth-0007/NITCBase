#include<iostream>
#include "Buffer/StaticBuffer.h"
#include "Cache/OpenRelTable.h"
#include "Disk_Class/Disk.h"
#include "FrontendInterface/FrontendInterface.h"

int main(int argc, char *argv[]) {
  Disk disk_run;

  // create objects for the relation catalog and attribute catalog
  RecBuffer relCatBuffer(RELCAT_BLOCK);
  RecBuffer attrCatBuffer(ATTRCAT_BLOCK);

  HeadInfo relCatHeader;
  HeadInfo attrCatHeader;

  // load the headers of both the blocks into relCatHeader and attrCatHeader.
  // (we will implement these functions later)
  relCatBuffer.getHeader(&relCatHeader);
  attrCatBuffer.getHeader(&attrCatHeader);
  int totalRelationCount = relCatHeader.numEntries;
  int numAttrEntries = attrCatHeader.numEntries;
  for (int i = 0 ; i < totalRelationCount; i++) {

    Attribute relCatRecord[RELCAT_NO_ATTRS]; // will store the record from the relation catalog

    relCatBuffer.getRecord(relCatRecord, i);

    printf("Relation: %s\n", relCatRecord[RELCAT_REL_NAME_INDEX].sVal);

    for (int j = 0 ; j < numAttrEntries; j++) {

      // declare attrCatRecord and load the attribute catalog entry into it
       Attribute attrCatRecord[ATTRCAT_NO_ATTRS]; 
        attrCatBuffer.getRecord(attrCatRecord, j);

      if (relCatRecord[RELCAT_REL_NAME_INDEX].sVal == attrCatRecord[ATTRCAT_REL_NAME_INDEX].sVal) {
        const char *attrType = attrCatRecord[ATTRCAT_ATTR_TYPE_INDEX].nVal == NUMBER ? "NUM" : "STR";
        printf("  %s: %s\n",attrCatRecord[ATTRCAT_ATTR_NAME_INDEX].sVal, attrType);
      }
    }
    printf("\n");
  }

  return 0;
}



// int main(int argc, char *argv[]) {
 
//   Disk disk_run;
//   // StaticBuffer buffer;
//   // OpenRelTable cache;

//   unsigned char buffer[BLOCK_SIZE];
//     Disk::readBlock(buffer, 7000);
//     char message[] = "hello";
//     memcpy(buffer + 20, message, 6);
//     Disk::writeBlock(buffer, 7000);

//     unsigned char buffer2[BLOCK_SIZE];
//     char message2[6];
//     Disk::readBlock(buffer2, 7000);
//     memcpy(message2, buffer2 + 20, 6);
//     std :: cout << message2;
//   return FrontendInterface::handleFrontend(argc, argv);
// }