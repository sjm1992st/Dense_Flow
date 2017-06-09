//
// Created by yjxiong on 11/18/15.
//

#ifndef DENSEFLOW_DENSE_FLOW_H
#define DENSEFLOW_DENSE_FLOW_H

#include "common.h"

#ifndef _MYCODE_H_
#define _MYCODE_H_
#ifdef DLLDEMO1_EXPORTS
#define EXPORTS_DEMO _declspec( dllexport )
#else
#define EXPORTS_DEMO _declspec(dllimport)
#endif
extern "C" EXPORTS_DEMO int calcDenseFlow(char *file_name, int bound, int type,  int *p_x, int *p_y, int new_width, int new_height);
#endif

void MatchFromFlow_copy(const Mat& prev_grey, const Mat& flow_x, const Mat& flow_y, std::vector<Point2f>& prev_pts, std::vector<Point2f>& pts, const Mat& mask);

#endif //DENSEFLOW_DENSE_FLOW_H
