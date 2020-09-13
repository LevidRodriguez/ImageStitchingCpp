from math import log10, sqrt 
import cv2 
import numpy as np 
import os
import sys
  
def PSNR(original, compressed): 
    mse = np.mean((original - compressed) ** 2) 
    if(mse == 0):   # MSE is zero means no noise is present in the signal . 
                    # Therefore PSNR have no importance. 
        return 100
    max_pixel = 255.0
    psnr = 20 * log10(max_pixel / sqrt(mse)) 
    return psnr 
  
def main(original_image, compressed_image): 
    original = cv2.imread(original_image) 
    compressed = cv2.imread(compressed_image, 1) 
    value = PSNR(original, compressed) 
    print ("SNR value is %s dB" % value)
       
if __name__ == "__main__": 
    if (len(sys.argv)<3):
        print >> sys.stderr, ("Usage: %s <original_image> <compressed_image>" % sys.argv[0])
        sys.exit(-1)
        pass
    main(sys.argv[1], sys.argv[2])
    # main() 