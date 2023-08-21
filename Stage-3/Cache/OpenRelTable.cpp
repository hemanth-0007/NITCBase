#include "OpenRelTable.h"
#include<cstdlib>
#include <cstring>

OpenRelTable::OpenRelTable() {

  // initialize relCache and attrCache with nullptr
  for (int i = 0; i < MAX_OPEN; ++i) {
    RelCacheTable::relCache[i] = nullptr;
    AttrCacheTable::attrCache[i] = nullptr;
  }

  /**** Setting up Relation Cache entries ****/
  // (we need to populate relation cache with entries for the relation catalog
  //  and attribute catalog.)



  /** setting up Relation Catalog relation in the Relation Cache Table**/
  RecBuffer relCatBlock(RELCAT_BLOCK);
  
  
  Attribute relCatRecord[RELCAT_NO_ATTRS];
  relCatBlock.getRecord(relCatRecord, RELCAT_SLOTNUM_FOR_RELCAT);
  
  struct RelCacheEntry relCacheEntry;
  RelCacheTable::recordToRelCatEntry(relCatRecord, &relCacheEntry.relCatEntry);
  relCacheEntry.recId.block = RELCAT_BLOCK;
  relCacheEntry.recId.slot = RELCAT_SLOTNUM_FOR_RELCAT;

  // allocate this on the heap because we want it to persist outside this function
  RelCacheTable::relCache[RELCAT_RELID] = (struct RelCacheEntry*)malloc(sizeof(RelCacheEntry));
  *(RelCacheTable::relCache[RELCAT_RELID]) = relCacheEntry;

  /** setting up Attribute Catalog relation in the Relation Cache Table **/
  
 
  Attribute attrCatRecord[ATTRCAT_NO_ATTRS];
  
  relCatBlock.getRecord(attrCatRecord, RELCAT_SLOTNUM_FOR_ATTRCAT);
  struct RelCacheEntry relCacheEntry_1;
  RelCacheTable::recordToRelCatEntry(attrCatRecord, &relCacheEntry_1.relCatEntry);
  relCacheEntry_1.recId.block = ATTRCAT_BLOCK;
  relCacheEntry_1.recId.slot = RELCAT_SLOTNUM_FOR_RELCAT;

  // set up the relation cache entry for the attribute catalog similarly
  // from the record at RELCAT_SLOTNUM_FOR_ATTRCAT
   RelCacheTable::relCache[ATTRCAT_RELID] = (struct RelCacheEntry*)malloc(sizeof(RelCacheEntry));
  *(RelCacheTable::relCache[ATTRCAT_RELID]) = relCacheEntry_1;

  // set the value at RelCacheTable::relCache[ATTRCAT_RELID]


  /**** Setting up Attribute cache entries ****/
  // (we need to populate attribute cache with entries for the relation catalog
  //  and attribute catalog.)

  /** setting up Relation Catalog relation in the Attribute Cache Table **/
  

  

  // iterate through all the attributes of the relation catalog and create a linked
  // list of AttrCacheEntry (slots 0 to 5)
  // for each of the entries, set
  //    attrCacheEntry.recId.block = ATTRCAT_BLOCK;
  //    attrCacheEntry.recId.slot = i   (0 to 5)
  //    and allocate each entry dynamically using malloc attrCacheEntry.next appropriately
  // NOTE: 
  // set the next field in the last entry to nullptr
  RecBuffer attrCatBlock(ATTRCAT_BLOCK);
  struct AttrCacheEntry *head=nullptr;
  struct AttrCacheEntry *dhead = nullptr;
  for(int i=0;i<6;i++) 
  {
  	
  	Attribute attrCatRecord[ATTRCAT_NO_ATTRS];
  	
   AttrCacheEntry *attrCacheEntry = (struct AttrCacheEntry *)malloc(sizeof(struct AttrCacheEntry));
   attrCatBlock.getRecord(attrCatRecord,i);
  	AttrCacheTable::recordToAttrCatEntry(attrCatRecord,&attrCacheEntry->attrCatEntry);
  	attrCacheEntry->recId.block = ATTRCAT_BLOCK;
  	attrCacheEntry->recId.slot = i;
   attrCacheEntry->next = nullptr;
  
  	
  	if(head==NULL)
  	{
  		head = attrCacheEntry;
  		dhead = attrCacheEntry;
  		
  	}
  	else {
  		dhead->next = attrCacheEntry;
  		dhead = attrCacheEntry;
  		}
  	
  
  }
  
  	
  	

  AttrCacheTable::attrCache[RELCAT_RELID] = head;/* head of the linked list */;

  /** setting up Attribute Catalog relation in the Attribute Cache Table **/

  // set up the attributes of the attribute cache similarly.
  // read slots 6-11 from attrCatBlock and initialise recId appropriately

  // set the value at AttrCacheTable::attrCache[ATTRCAT_RELID]
  head=nullptr;
  dhead = nullptr;
  for(int i=6;i<12;i++)
  {
  	Attribute attrCatRecord[ATTRCAT_NO_ATTRS];
  	attrCatBlock.getRecord(attrCatRecord,i);
    	struct AttrCacheEntry *attrcacheEntry1;
    	attrcacheEntry1= (struct AttrCacheEntry *)malloc(sizeof(struct AttrCacheEntry));
  	AttrCacheTable::recordToAttrCatEntry(attrCatRecord,&attrcacheEntry1->attrCatEntry);
  	attrcacheEntry1->recId.block = ATTRCAT_BLOCK;
  	attrcacheEntry1->recId.slot = i;
  	struct AttrCacheEntry *temp = attrcacheEntry1;
  	if(head==NULL)
  	{
  		head = temp;
  		dhead = temp;
  		
  	}
  	else {
  		dhead->next = temp;
  		dhead = temp;  		
        }
  	
     
	}
	AttrCacheTable::attrCache[ATTRCAT_RELID] = head;

}

OpenRelTable::~OpenRelTable() {
	
 for(int i=0;i<MAX_OPEN;i++)
   {
      RelCacheTable::relCache[i] = nullptr;
      AttrCacheTable::attrCache[i] = nullptr;
   }  // free all the memory that you allocated in the constructor
}