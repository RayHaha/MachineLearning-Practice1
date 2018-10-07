#include "stdafx.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include<fstream>
#include<string.h>

using namespace cv;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	
	char theline [100] ;
	
	//read file
	fstream fin;
	fin.open("data.txt",ios::in);
	double data[400][100];


	//initial
	for(int i=0; i<400; i++){
		for(int j=0; j<100; j++){
			data[i][j] = 0 ;
		}
	}
	//分割字串存入二維陣列
	char *token = NULL;
	char *next_token = NULL;
	char seps[]   = " ,\t\n";
	int a=0;
	while(fin.getline(theline,sizeof(theline),'\n')){
		int b = 0;
		token = strtok_s( theline, seps, &next_token);
		while (token != NULL){
			data[a][b] = atof(token);
            token = strtok_s( NULL, seps, &next_token);
			b++;
		}
		a++;
	}

	bool again = true;
	double h = 0;
	double w[5] = {0,0,0,0,0};
	int start = 0;
	int countstop = 0;
	int count = 0;
	//start PLA
	while(again){
		again = false;
		countstop++;
		double temp = w[0]*1 + w[1]*data[start][0] +  w[2]*data[start][1] + w[3]*data[start][2] + w[4]*data[start][3] ;
		if(temp>0){
			h = 1 ;
		}else{
			h = -1;
		}
		if(h == data[start][4]){

		}else{
			w[0] = w[0] + data[start][4] * 1;
			w[1] = w[1] + data[start][4] * data[start][0] ;
			w[2] = w[2] + data[start][4] * data[start][1] ;
			w[3] = w[3] + data[start][4] * data[start][2] ;
			w[4] = w[4] + data[start][4] * data[start][3] ;
			countstop=0;
			count++;
		}
		start++ ;
		if(start==400){
			start = 0 ;
		}
		if(countstop!=400){
			again = true;
		}
		
	}
	cout<<count<<endl;//update times
	cout<<start<<endl;//the last index
	
	system("pause");
	return 0;
}