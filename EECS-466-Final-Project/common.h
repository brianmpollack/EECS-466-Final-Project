#pragma once
#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <gl/glut.h>
#include <windows.h>
#include <string>
#include <math.h>
#include <iostream>
#include <map>
#include <vector>

typedef struct _point {
	float x, y, z;
} point;

typedef struct _faceStruct {
	int v1, v2, v3;
	int n1, n2, n3;
} faceStruct;


#define PI 3.1415926535897