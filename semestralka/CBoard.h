//
// Created by David on 17.05.2019.
//

#ifndef SEMESTRALKA_CBOARD_H
#define SEMESTRALKA_CBOARD_H
#include "CWindow.h"

class CBoard : public CWindow {
public:
    void render() const;
    void  processInput();

protected:

};


#endif //SEMESTRALKA_CBOARD_H
