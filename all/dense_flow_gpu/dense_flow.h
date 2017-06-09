//
// Created by yjxiong on 11/18/15.
//

#ifndef DENSEFLOW_DENSE_FLOW_H
#define DENSEFLOW_DENSE_FLOW_H

#include "common.h"
//#include "easylogging++.h"

#ifndef _MYCODE_H_
#define _MYCODE_H_
#ifdef DLLDEMO1_EXPORTS
#define EXPORTS_DEMO _declspec( dllexport )
#else
#define EXPORTS_DEMO _declspec(dllimport)
#endif
extern "C" EXPORTS_DEMO int calcDenseFlowGPU(char *file_name, int bound, int type, int dev_id, int *p_x, int *p_y,
		int new_width = 0, int new_height = 0);
#endif
#endif //DENSEFLOW_DENSE_FLOW_H
