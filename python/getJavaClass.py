#! /usr/bin/env python
"""

"""
import os
import shutil
#import re

def recursion(src, cls, dst):
    lists = os.listdir(src)
    for each in lists:
        sub1 = os.path.join(src,each)
        sub2 = ""
        sub3 = ""
        if os.path.isdir(sub1):
            sub2 = os.path.join(cls,each)
            sub3 = os.path.join(dst,each)
            
            if not os.path.exists(sub3):
                os.mkdir(sub3)
            if not os.path.isdir(sub3):
                os.rmdir(sub3)
                os.mkdir(sbu3)

            recursion(sub1, sub2, sub3)

        if os.path.isfile(sub1):
            eachtmp = each
            if each[-5:] == '.java':
                eachtmp = each[:-5] + '.class'
            sub2 = os.path.join(cls,eachtmp)
            sub3 = os.path.join(dst,eachtmp)
            shutil.copy(sub2, sub3)
            #shutil.copy(sub1, sub3)




def checkPath(srcsrc, srcclass, dstclass):
    
    flag = True
    if not os.path.exists(srcsrc) or not os.path.isdir(srcsrc):
        print "%s : is not exist or a directory...", srcsrc
        flag = False
    
    if not os.path.exists(srcclass) or not os.path.isdir(srcclass):
        print "%s : is not exist or a directory...", srcclass
        flag = False

    if not os.path.exists(dstclass) or not os.path.isdir(dstclass):
        print "%s : is not exist or a directory...", dstclass
        flag = False

    return flag

    
if __name__=="__main__":
    path1 = raw_input("the path of java-src-file directory:")
    path2 = raw_input("the path of compiled-class-file directory:")
    path3 = raw_input("the path of output-class-file directory:")

    if not checkPath(path1,path2,path3):
        sys.exit()

    recursion(path1,path2,path3)




