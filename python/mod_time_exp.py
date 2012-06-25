#/usr/bin/env python
#encoding=utf-8

import time

print '--------------------------------------'
seconds_f = time.time() #return current time in seconds since the Epoch as a float
clock_f = time.clock() #return CPU time since process start as a float
struct_time = time.gmtime() #convert seconds since Epoch to UTC tuple
tuple_time = tuple(struct_time) #

print 'time.time():', seconds_f
print 'time.clock():', clock_f
print 'time.gmtime():', struct_time
print 'tuple(struct_time):', tuple_time
print '--------------------------------------'
print 'seconds_f:', seconds_f
print 'clock_f:', clock_f
print 'struct_time:', struct_time
print 'tuple_time:', tuple_time


print '--------------------------------------'
print 'time.asctime():', time.asctime()
print 'time.asctime(struct_time):', time.asctime(struct_time)
print 'time.asctime(tuple_time):', time.asctime(tuple_time)

print '--------------------------------------'
print 'time.gmtime():', time.gmtime()
print 'time.gmtime(seconds_f):',time.gmtime(seconds_f)

print '--------------------------------------'
print 'time.localtime():',time.localtime()
print 'time.localtime(seconds_f):',time.localtime(seconds_f)

print '--------------------------------------'
print 'time.ctime():',time.ctime()
print 'time.ctime(seconds_f):',time.ctime(seconds_f)

print '--------------------------------------'
print 'time.mktime(tuple_time):',time.mktime(tuple_time)
print 'time.mktime(struct_time):',time.mktime(struct_time)

print '--------------------------------------'
print "\nUsing strftime():"
print "Day and Date:", time.strftime("%a %m/%d/%y", time.localtime())
print "Day, Date :", time.strftime("%A, %B %d, %Y", time.localtime())
print "Time (12hr) :", time.strftime("%I:%M:%S %p", time.localtime())
print "Time (24hr) :", time.strftime("%H:%M:%S", time.localtime())
print "DayMonthYear:",time.strftime("%d%b%Y", time.localtime())
print "year/month/day hour:minute:second :",time.strftime("%Y/%m/%d %H:%M:%S", time.localtime())