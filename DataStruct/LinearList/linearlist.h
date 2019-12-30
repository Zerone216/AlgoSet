/*
 > Declaration: 
 >  Copyright (c) 2009-2019 Zhang Sheng <zerone216@163.com>
 >  See my homepage: https://zerone216.cn
 > 
 >  This program is free software; you can redistribute it and/or modify it under 
 >  the terms of the GNU General Public License as published by the Free Software 
 >  Foundation, either version 2 or any later version.
 >  
 >  Redistribution and use in source and binary forms, with or without modification,
 >  are permitted provided that the following conditions are met: 
 >  
 >  1. Redistributions of source code must retain the above copyright notice, this
 >  list of conditions and the following disclaimer.
 >  
 >  2. Redistributions in binary form must reproduce the above copyright notice,
 >  this list of conditions and the following disclaimer in the documentation and/or 
 >  other materials provided with the distribution. 
 > 
 >  This program is distributed in the hope that it will be useful, but WITHOUT ANY 
 >  WARRANTY; without even the implied warranty of MERCHANTABILITY or ITNESS FOR A 
 >  PARTICULAR PURPOSE. See the GNU General Public License for more details. A copy 
 >  of the GNU General Public License is available at: 
 >  http://www.fsf.org/licensing/licenses 
 >  
 >  All manufacturing, reproduction, use, and sales rights pertaining to this subject 
 >  matter are governed bythe license agreement. The recipient of this software 
 >  implicitly accepts the terms of the license.
 > 
 > Author: Zhang Sheng
 > FilePath: /zerone216/AlgoSet/DataStruct/LinearList/linearlist.h
 > CreateTime: 2019-12-30 21:13:27
 > ModifyTime: 2019-12-30 21:13:29
 > LastEditors: 
 > Description: 
 > version: 
 > Repository: https://github.com/zerone216/
 > Support: 
 > Others: 
 > Changelogs: 
 */

#ifndef __LINEAR_LIST_H__
#define __LINEAR_LIST_H__

#include <iostream>


//抽象类 linearlist
template<class T>
class linearlist
{
    public:
        virtual ~linearlist() {};
        virtual bool empty() const = 0; //返回true,当且仅当线性表为空

        virtual int size() const = 0; //返回线性表的元素个数

        virtual T& get(int theIndex) const = 0; //返回索引为theIndex的元素

        virtual int indexOf(const T& theElement) const = 0; //返回theElement第一次出现时的索引

        virtual void erase(int theIndex) = 0; //删除索引为theIndex的元素

        virtual void insert(int theIndex, const T& theElement) = 0; //把theElement元素插入线性表中索引为theIndex的位置

        virtual void output(ostream& out) const = 0; //把线性表插入输出流out
};

#endif // __LINEAR_LIST_H__
