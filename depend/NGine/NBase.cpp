#include "NBase.h"

/***************************************************************************************************************/
void crash(const char errorMsg[]){

	cerr << "ERROR: " << errorMsg << endl;
	exit(-123456789);
}
/***************************************************************************************************************/
