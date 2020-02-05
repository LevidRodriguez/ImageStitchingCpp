import cv2
import sys
import os

def resizeImages(image_dir, key_frame, output_dir):
    key_frame_file = os.path.split(key_frame)[-1]
    dir_list = os.listdir(image_dir)
    try:
        dir_list.remove('.DS_Store')
    except: ValueError

    out_dir_list = filter(lambda x: x != key_frame, dir_list)

    dir_list = map(lambda x: os.path.join(image_dir, x), dir_list)
    dir_list = filter(lambda x: x != key_frame, dir_list)
    print (dir_list)
    for image in dir_list:
        img = cv2.resize(cv2.imread(image), (1280, 720))
        print (image.replace(image_dir, output_dir))
        image = image.replace(image_dir, output_dir)
        cv2.imwrite(image, img)
        pass
    pass

if __name__ == "__main__":
    if (len(sys.argv)<4):
        print >> sys.stderr, ("Usage: %s <image_dir> <key_frame> <output>" % sys.argv[0])
        sys.exit(-1)
        pass
    resizeImages(sys.argv[1], sys.argv[2], sys.argv[3])
    pass