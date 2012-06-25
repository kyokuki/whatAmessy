#!/usr/bin/env python
#encoding=utf-8
import urllib2  
import urllib  
import cookielib
import hashlib
import time
import sys


login_page = "http://bbs.pediy.com/login.php?do=login"
visit_page = "http://bbs.pediy.com/"

class PediyUser :
    
    def __init__(self) :
        self.cookiejar = cookielib.CookieJar() 
        self.opener=urllib2.build_opener(urllib2.HTTPCookieProcessor(self.cookiejar))  


    def login(self,user,password):  
        hash = hashlib.md5(password)
        md5pwd = hash.hexdigest()
        try:  
            #获得一个cookieJar实例  
            #cj = cookielib.CookieJar()  
            #cookieJar作为参数，获得一个opener的实例  
            #=urllib2.build_opener(urllib2.HTTPCookieProcessor(cj))  
            #伪装成一个正常的浏览器，避免有些web服务器拒绝访问。  
            self.opener.addheaders = [('User-agent','Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1)')]  
            #生成Post数据，含有登陆用户名密码。
            login_data = (('vb_login_username',user),
                ('cookieuser','1'),
                ('vb_login_password',''),
                ('s',md5pwd),
                ('securitytoken','guest'),
                ('do','login'),
                ('vb_login_md5password',md5pwd),
                ('vb_login_md5password_utf',md5pwd))
            #以post的方法访问登陆页面，访问之后cookieJar会自定保存cookie  
            self.opener.open(login_page,urllib.urlencode(login_data))  
            #以带cookie的方式访问页面  
            #op=opener.open(visit_page)  
            #读取页面源码  
            #data= op.read()  
            #return data  
        except Exception,e:  
            print str(e)  
    
    def brower(self,url=visit_page) :
        try :
            op = self.opener.open(url)
            data = op.read()
            return data
        except Exception,e:
            print str(e)
        

if __name__ == '__main__' :

    user = sys.argv[1]
    pwd = sys.argv[2]
    
    if not user or not pwd :
        print "username or password missing."
        exit

    me = PediyUser()
    me.login(user,pwd)
    print me.brower()
    while True:
        me.brower()
        time.sleep(60)