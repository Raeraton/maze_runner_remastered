#include "globals.h"


namespace globals{
    

    double _deltatime = 1.0;
    double& deltatime(){
        return _deltatime;
    }


} // namespace globals
