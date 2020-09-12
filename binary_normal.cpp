//
// Created by inejka on 10.09.2020.
//

#include <iostream>
#include "binary_normal.h"
#include <vector>
using namespace  std;
int pow(int a) {
    int c = 1;
    for (int i = 1; i <= a; i++)
        c *= 2;
    return c;
}

int min(int a, int b) {
    return a > b ? b : a;
}

int max(int a, int b) {
    return a > b ? b : a;
}

binary_normal::binary_normal(int tmp) {
    int int_part_pointer = 31;
    for (int i = 0; i < 32; i++)
        int_part[i] = false;
    if (tmp < 0) {
        tmp *= -1;
        int_part[0] = true;
    }
    while (tmp > 0 && int_part_pointer > 0) {
        if (tmp % 2 == 1)int_part[int_part_pointer] = true;
        int_part_pointer--;
        tmp /= 2;
    }
}

int binary_normal::to_int() {
    int tmp = 0;
    for (int i = 0; i < 31; i++)
        if (int_part[31 - i])tmp += pow(i);
    if (int_part[0])tmp *= -1;
    return tmp;
}

void binary_normal::print() {
    for (int i = 0; i < 32; i++)
        if (int_part[i])std::cout << 1; else std::cout << 0;
}

binary_normal binary_normal::operator+(const binary_normal &rhs) {
    bool check = rhs.int_part[0]!=this->int_part[0]?true:false ;
    for(int i = 1 ; i < 32 ; i++)
        if(!(rhs.int_part[i]== (this->int_part[i]))){
            check= false;
            break;
        }
    if(check){
        return binary_normal(0);
    }
    if (rhs.int_part[0] == this->int_part[0]){binary_normal tmp1;tmp1=add(*this, rhs);tmp1.int_part[0]=rhs.int_part[0];return tmp1;}
    else {
        if (rhs.int_part[0] == true) {
            binary_normal tmp2 = rhs;
            tmp2.s_to_reverse();
            tmp2.r_to_add();
            tmp2 = add(*this, tmp2);
            if(tmp2.int_part[0]){
            tmp2.add_to_reverse();
            tmp2.r_to_straight();
            }
            return tmp2;
        } else {
            binary_normal tmp2 = *this;
            tmp2.s_to_reverse();
            tmp2.r_to_add();
            tmp2 = add(rhs, tmp2);

            if(tmp2.int_part[0]){
                tmp2.add_to_reverse();
                tmp2.r_to_straight();
            }
            return tmp2;
        }
    }
}

binary_normal add(const binary_normal &a, const binary_normal &b) {
    bool ans[32];
    bool tmp[32];
    for(int i = 0 ; i < 32 ; i++){
        ans[i]=tmp[i]= false;
    }
    for (int i = 31; i >-1; i--) {
        int tmp1 = 0;
        tmp1 += tmp[i];
        tmp1 += a.int_part[i];
        tmp1 += b.int_part[i];
        switch (tmp1) {
            case 0:
                ans[i] = false;
                break;
            case 1:
                ans[i] = true;
                break;
            case 2:
                ans[i] = false;
                if(i!=0)
                tmp[i - 1] = true;
                break;
            case 3:
                ans[i] = true;
                tmp[i - 1] = true;
                break;
        }
    }
    binary_normal tmp3;
    for (int j = 31; j > -1; j--)
        tmp3.int_part[j] = ans[j];
    return tmp3;
}


binary_normal::binary_normal() {
    for(int i = 0 ; i < 32 ; i++)
        int_part[i]= false;
}

void binary_normal::s_to_reverse() {
    bool tmp[32] ;
    for (int i = 1; i < 32; i++)
        tmp[i] = int_part[i];
    for (int i = 1; i < 32; i++)
        int_part[i] = !tmp[i];
}

void binary_normal::r_to_straight() {
    bool tmp[32] ;
    for (int i = 1; i < 32; i++)
        tmp[i] = int_part[i];
    for (int i = 1; i < 32; i++)
        int_part[i] = !tmp[i];
}

void binary_normal::r_to_add() {
    *this = add(*this ,binary_normal(1));
}

void binary_normal::add_to_reverse() {
    int i = 31;
    if (int_part[i])int_part[i] = false;
    else {
        while (!int_part[i])i--;
        int_part[i] = false;
        for (int j = i + 1; j < 32; j++)
            int_part[j] = true;
    }
}

binary_normal binary_normal::operator-(const binary_normal &rhs) {
    binary_normal F=rhs;
    F.int_part[0]=!F.int_part[0];
    return (*this+F);
}

binary_normal binary_normal::operator*(const binary_normal &rhs) {
    int c=0;
    for(int i = 1 ; i < 32 ; i++)
        if(rhs.int_part[i]){
            c=i;
            break;
        }
    vector <binary_normal> to_sum(32-c);
    int d=0;
    for(int i = 1 ; i < 32 ; i++)
        if(this->int_part[i]){
            d=i;
            break;
        }
    vector<bool>paste(32-d);
    for(int i = 0 ; i < 32 - d ; i++ ) paste[i]= this->int_part[31-i];
        for(int i = 0 ; i < 32 - c ; i++)
            if(rhs.int_part[31-i])
                for(int j = 0 ; j < 32 - d ; j++)
                    to_sum[i].int_part[31-i-j]=paste[j];
    binary_normal ans ;
    for(int i = 0 ; i < 32 - c ; i++)
        if(rhs.int_part[31-i])
            ans = ans + to_sum[i];
        if(rhs.int_part[0]!=this->int_part[0])ans.int_part[0]=true;
        return ans;
}

binary_normal dividef(binary_normal a, binary_normal b) {
    a=a*binary_normal(100000);
    binary_normal res;
    bool check= false;
    if(a.int_part[0]!=b.int_part[0])check=true;
    a.int_part[0]=b.int_part[0]=false;
    while(!(a-b).int_part[0]){
        a=a-b;
        res=res + binary_normal(1);
    }
    if(check)res.int_part[0]= true;
    return res;
}

bool binary_normal::sdright() {
    for(int i = 2 ; i < 31 ; i++)
        int_part[i]=int_part[i-1];
}
