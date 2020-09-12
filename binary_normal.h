//
// Created by inejka on 10.09.2020.
//

#ifndef SEM3_LAB1_MOIS_BINARY_NORMAL_H
#define SEM3_LAB1_MOIS_BINARY_NORMAL_H


class binary_normal {
public:
    bool int_part[32];
    binary_normal();
    binary_normal(int);
    int to_int();
    void print();
    void s_to_reverse();
    void r_to_straight();
    void r_to_add();
    void add_to_reverse();
    binary_normal operator+(const binary_normal&);
    binary_normal operator-(const binary_normal&);
    binary_normal operator*(const binary_normal&);
    bool sdright();
    bool sdleft();
};

binary_normal add(const binary_normal&,const binary_normal&);

binary_normal dividef(binary_normal a ,binary_normal b);// a\b

#endif //SEM3_LAB1_MOIS_BINARY_NORMAL_H
