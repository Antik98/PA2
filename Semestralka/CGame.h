//
// Created by Duc Minh Pham on 2019-05-06.
//

#ifndef SEMESTRALKA_CGame_H
#define SEMESTRALKA_CGame_H



class CGame {
public:
    CGame();
    virtual ~CGame();
    bool play();
    bool init();
    bool save();
    bool load();
};


#endif //SEMESTRALKA_CGame_H
