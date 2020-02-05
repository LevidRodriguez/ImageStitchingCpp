#include <memory>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <cuda_runtime.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/stitching.hpp>
#include <opencv2/core/utility.hpp>

// CUDA-C includes
#include <cuda.h>

using namespace std;
using namespace cv;

cv::Stitcher::Mode mode = cv::Stitcher::PANORAMA;
cv::Stitcher::Mode modeSCANS = cv::Stitcher::SCANS;
std::vector<cv::Mat> imgs;

int main(int argc, char **argv)
{
    // CUDA Drivers
    std::cout<<"Starting..."<<argv[0]<<std::endl<<std::endl;
    std::cout<<"CUDA Device Query (Runtime API) version (CUDART static linking)"<<std::endl<<std::endl;
    int deviceCount = 0;
    cudaError_t error_id = cudaGetDeviceCount(&deviceCount);
    
    if (error_id != cudaSuccess){
        std::cout<<"cudaGetDeviceCount returned "<< (int)error_id<< cudaGetErrorString(error_id)<<std::endl;
        std::cout<<"Result = FAIL"<<std::endl;
        exit(EXIT_FAILURE);
    }
    // This function call returns 0 if there are no CUDA capable devices.
    if (deviceCount == 0)
        std::cout<<"There are no available device(s) that support CUDA"<<std::endl;
    else
        std::cout<<"Detected "<< deviceCount<<" CUDA Capable device(s)"<<std::endl<<std::endl;
    int dev, driverVersion = 0, runtimeVersion = 0;
    for (dev = 0; dev < deviceCount; ++dev){
        cudaSetDevice(dev);
        cudaDeviceProp deviceProp;
        cudaGetDeviceProperties(&deviceProp, dev);
        std::cout<<"Device: "<<dev<<" "<<deviceProp.name<<std::endl;
        // Console log
        cudaDriverGetVersion(&driverVersion);
        cudaRuntimeGetVersion(&runtimeVersion);
        std::cout<<"CUDA Driver Version / Runtime Version          "<< driverVersion/1000
                << (driverVersion%100)/10<<runtimeVersion/1000<<(runtimeVersion%100)/10<<std::endl;
        std::cout<<"CUDA Capability Major / Minor version number:          "<< driverVersion/1000
                << deviceProp.major<<deviceProp.minor<<std::endl<<std::endl;
    }
    
    // Stitching de Imagenes
    std::cout<<"Stitching de Imagenes"<<std::endl<<std::endl;
    for (int i = 1; i < argc; ++i) { 
        cv::Mat img = cv::imread(argv[i]);
        // std::cout<<argv[i]<<" Processing... "<<std::endl; 
        if (img.empty()) { 
            // Exit if image is not present 
            cout << "Can't read image '" << argv[i] << "'\n"; 
            return -1; 
        } 
        // cv::Size size(1280,720);
        // cv::Size size(640,480);
        // cv::resize(img, img, size);
        imgs.push_back(img); 
    } 
    std::cout<<"Pano size: "<< imgs.size()<<std::endl;
    
    std::cout<<"Define object to store the stitched image "<<std::endl;
    cv::Mat pano; // (1280,720,CV_8UC3); 
    
    std::cout<<"Create a Stitcher class object with mode panoroma "<<std::endl;
    cv::Ptr<cv::Stitcher> stitcher = cv::Stitcher::create(mode, false); 
    
    std::cout<<"Command to stitch all the images present in the image array "<<std::endl;
    cv::Stitcher::Status status = stitcher->stitch(imgs, pano);
    std::cout<<"Status: "<<status<<std::endl;
    std::cout<<"cv::Stitcher::OK: "<<cv::Stitcher::OK<<std::endl;
    std::cout<<"Pano size: "<< pano.size()<<std::endl;//src.size().width
    // cv::Size size(1280,720);
    // cv::resize(pano, pano, size);
    // std::cout<<"Pano size: "<< pano.size()<<std::endl;//src.size().width

    if (status != cv::Stitcher::OK) { 
        cout << "Can't stitch images\n"; 
        return -1; 
    } 
    std::cout<<"pano done..."<<std::endl;
    std::cout<<"Store a new image stiched from the given  "<<std::endl;
    cv::imwrite("resultPano.jpg", pano);
    std::cout<<"Results is written"<<std::endl;
    return 0;
}