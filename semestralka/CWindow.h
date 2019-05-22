//
// Created by David on 17.05.2019.
//

#ifndef SEMESTRALKA_CWINDOW_H
#define SEMESTRALKA_CWINDOW_H


class CWindow {
public:
    CWindow()= default;
    virtual ~CWindow()= default;
    virtual void render() const=0;
    virtual void parseInput() =0;

};


#endif //SEMESTRALKA_CWINDOW_H
