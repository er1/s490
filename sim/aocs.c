#include "aocs.h"

void aocs_exec()
{
  short unsigned ret; 

  printf("AOCS Module Executing...\n");

  ret = aocs_OK();

  if (!aocs_OK()) {
    printf("  :: AOCS module OK "); 
  } else {
    printf("  :: AOCS module BAD : %d", ret); 
  }
}

/** Function to see that AOCS module is ok. 
\return 0 on ok, error code on fail. */
unsigned short aocs_OK(){
  return 0;
}
