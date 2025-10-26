#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(){
    //读取视频
    string path = "images/TrafficLight.mp4";
    VideoCapture cap(path);
    if (!cap.isOpened()){
        cerr << "无法打开视频文件" << endl;
        return -1;
    }
    //获取频率、宽、高
    double fps = cap.get(CAP_PROP_FPS);
    int width = static_cast<int>(cap.get(CAP_PROP_FRAME_WIDTH));
    int height =static_cast<int>(cap.get(CAP_PROP_FRAME_HEIGHT));
    
    //创建输出视频
    VideoWriter writer("/home/dsp/Videos/result.avi",VideoWriter::fourcc('M','J','P','G'),fps,Size(width,height));
    if(!writer.isOpened()){
        cerr << "无法创建输出视频文件！" << endl;
        cap.release();
        return -1;
    }
    Mat frame,hsvFrame,redMask,greenMask;
    //逐帧处理视频
    while(cap.read(frame)){
        if(frame.empty()) break;
        //转换到HSV颜色空间，HSV比BGR更容易分割颜色
        cvtColor(frame,hsvFrame,COLOR_BGR2HSV);

        //检测红灯信号
        Scalar lowerRed1 = Scalar(0,100,100);
        Scalar upperRed1 = Scalar(0,255,255);
        Scalar lowerRed2 = Scalar(170,100,100);
        Scalar upperRed2 = Scalar(180,255,255);
        inRange(hsvFrame,lowerRed1,upperRed1,redMask);
        Mat redMask2;
        inRange(hsvFrame, lowerRed2,upperRed2,redMask2);
        redMask = redMask | redMask2;  //合并两个红色区间掩码

        //检测绿灯信号
        Scalar lowerGreen = Scalar(35,100,100);
        Scalar upperGreen = Scalar(77,255,255);
        inRange(hsvFrame,lowerGreen,upperGreen,greenMask);

        //轮廓检测与标注
        vector<vector<Point>> redContours, greenContours;
        vector<Vec4i> redHierarchy,greenHierarchy; 

        //检测红色区域的轮廓
        findContours(redMask,redContours,redHierarchy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
        findContours(greenMask,greenContours,greenHierarchy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);

        bool isRed = false, isGreen = false;
        Rect redRect,greenRect;


        //处理红色轮廓，筛选合理区域并标注
        for (size_t i =0;i < redContours.size();++i){
            double area = contourArea(redContours[i]);
            if (area > 100){
                redRect = boundingRect(redContours[i]);
                rectangle(frame,redRect,Scalar(0,0,255),2);
                isRed = true;
            }
        }
        //处理绿色轮廓，筛选合理区域并标注
        for (size_t i =0;i < greenContours.size();++i){
            double area = contourArea(greenContours[i]);
            if (area > 100){
                greenRect = boundingRect(greenContours[i]);
                rectangle(frame,greenRect,Scalar(0,255,0),2);
                isGreen = true;
            }
        }

        //左上角显示颜色文字
        if(isRed){
            putText(frame,"red",Point(10,30),FONT_HERSHEY_SIMPLEX,1,Scalar(0,0,255),2);
        }
        else if (isGreen){
            putText(frame,"green",Point(10,30),FONT_HERSHEY_SIMPLEX,1,Scalar(0,255,0),2);
        }

        writer.write(frame);
    
    }
    cap.release();
    writer.release();
    cout << "处理完成" << endl;
    return 0;
}