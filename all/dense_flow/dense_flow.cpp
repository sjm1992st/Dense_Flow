//
// Created by yjxiong on 11/18/15.
//

#include "stdafx.h"
//#include "common.h"
#include "dense_flow.h"

int calcDenseFlow(char *file_name, char *out_name, int bound, int type, int step, int new_width, int new_height){

    VideoCapture video_stream(file_name);
	std::vector<std::vector<uchar> > output_x, output_y, output_img;
    //CHECK(video_stream.isOpened())<<"Cannot open video stream \""
                                  //<<file_name
                                 // <<"\" for optical flow extraction.";

    Mat capture_frame, capture_image, prev_image, capture_gray, prev_gray;
    Mat flow, flow_split[2];

	Size new_size(new_width, new_height);

    cv::Ptr<cv::DualTVL1OpticalFlow> alg_tvl1 = cv::createOptFlow_DualTVL1();
	bool do_resize = (new_height > 0) && (new_width > 0);
    bool initialized = false;
    for(int iter = 0;; iter++){
        video_stream >> capture_frame;
        if (capture_frame.empty()) break; // read frames until end

        //build mats for the first frame
		if (!do_resize){
			initializeMats(capture_frame, capture_image, capture_gray,
				prev_image, prev_gray);
			capture_frame.copyTo(prev_image);
		}
		else{
			capture_image.create(new_size, CV_8UC3);
			capture_gray.create(new_size, CV_8UC1);
			prev_image.create(new_size, CV_8UC3);
			prev_gray.create(new_size, CV_8UC1);
			cv::resize(capture_frame, prev_image, new_size);
		}
            cvtColor(prev_image, prev_gray, CV_BGR2GRAY);
            initialized = true;
//            LOG(INFO)<<"Initialized";

            switch(type){
                case 0: {
                    calcOpticalFlowFarneback(prev_gray, capture_gray, flow,
                                             0.702, 5, 10, 2, 7, 1.5,
                                             cv::OPTFLOW_FARNEBACK_GAUSSIAN );
                    break;
                }
                case 1: {
                    alg_tvl1->calc(prev_gray, capture_gray, flow);
                    break;
                }
                default:
                    ////LOG(WARNING)<<"Unknown optical method. Using Farneback";
                    calcOpticalFlowFarneback(prev_gray, capture_gray, flow,
                                             0.702, 5, 10, 2, 7, 1.5,
                                             cv::OPTFLOW_FARNEBACK_GAUSSIAN );
            }

            std::vector<uchar> str_x, str_y, str_img;
            split(flow, flow_split);
            encodeFlowMap(flow_split[0], flow_split[1], str_x, str_y, bound);
            imencode(".jpg", capture_image, str_img);

            output_x.push_back(str_x);
            output_y.push_back(str_y);
            output_img.push_back(str_img);
//            LOG(INFO)<<iter;

            std::swap(prev_gray, capture_gray);
            std::swap(prev_image, capture_image);
        }
    
	std::string xFlowFile = string(out_name) + "flow_x";
	std::string yFlowFile = string(out_name)+ "flow_y";
	std::string imgFile = string(out_name) +"flow_i";
	writeImages(output_x, xFlowFile);
	writeImages(output_y, yFlowFile);
	writeImages(output_img, imgFile);
	return 0;
}

int main()
{
	std::vector<std::vector<uchar> > out_vec_x, out_vec_y, out_vec_img;
	char *out_path = "E://test_好好//";
	calcDenseFlow("E://好好//test_好.avi", out_path, 15, 0, 1, 10,10);
	return 0;
}