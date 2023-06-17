#include <iostream>
#include<winbgim.h>
#include <string.h>
#include <time.h>
#include <vector>
#include <fstream>
#include "danhmucsach.h"
#include "dausach.h"
#include "muontra.h"
#include "docgia.h"
#include "dohoa.h"
#include "xuly.h"
using namespace std;
int main( ) {
	initwindow( 1400 , 700);
	settextstyle(10,0,3);
	initMapID();
	run();
	return 0;
}
