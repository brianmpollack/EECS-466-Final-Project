#pragma once
class Edge;
class Mesh;
class Vertex;
class MeshReader;
class Face;
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
#include <queue>
#include <functional>
#include <memory>
#include <set>
#include "Vector3.h"
#include "Vector4.h"
#include "ThreeMatrix.h"
#include "FourMatrix.h"

typedef struct _point {
	float x, y, z;
} point;

typedef struct _faceStruct {
	int v1, v2, v3;
	int n1, n2, n3;
} faceStruct;


#define PI 3.1415926535897