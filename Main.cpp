/*
 * Main.cpp
 *
 *  Created on: May 1, 2020
 *      Author: OS1
 */
#include"System.h"
//#include<stdio.h>
#include<iostream.h>

extern int userMain(int argc, char* argv[]);



 int main(int argc, char* argv[])
 {



	System::init_system();

	int tmp = userMain(argc, argv);

	System::restore_system();



    return tmp;
 }



