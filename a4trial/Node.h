#pragma once
#include "stdafx.h"
#include<iostream>
#include <queue>
#include <vector>

#ifndef NODE_H
#define NODE_H



class Node {
public:
	//member variables
	int element_value;
	int arr_num;

	//constructor
	//@param value of array element
	//@param array number
	Node(int ev, int an);

};


#endif