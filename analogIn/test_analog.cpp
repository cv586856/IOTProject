
#include <iostream>
#include "analogIn.h"
#include <iomanip>


using namespace std;

int main(){
 AnalogIn AIN(0);
   cout << "Using AIN" << AIN.getNumber() << " to read analog value." << std::endl;
    cout << "ADC value is: " << AIN.readAdcSample() << endl;
     cout << endl;
      cout << endl;
}//main


