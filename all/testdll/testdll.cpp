// testdll.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <stdio.h>
#include <iostream>
using std::string;
using std::vector;
#include <windows.h>
using namespace std;
typedef void(*AddFunc)(char *file_name, char *out_name, int bound, int type, int step, int dev_id);

int main(int argc, char *argv[])
{
	HMODULE hDll = LoadLibraryW(_T("F://vsworkspace//dense_flow//x64//release//dense_warp_flow_gpu.dll"));
	if (hDll != NULL)
	{
		AddFunc calcDenseWarpFlowGPU = (AddFunc)GetProcAddress(hDll, "calcDenseWarpFlowGPU");
		std::vector<std::vector<uchar> > out_vec_x, out_vec_y, out_vec_img;
		if (calcDenseWarpFlowGPU != NULL)
		{
			char *out_path = "E://test//";
			calcDenseWarpFlowGPU("F://vsworkspace//dense_flow//dense_flow//test.avi", out_path, 15, 0, 1,0);

		}
		FreeLibrary(hDll);
	}
}