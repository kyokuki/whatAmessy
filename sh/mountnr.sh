#/bin/sh -x
#
#description:
#		mount a shared directory from a windwos PC to local linux PC
#		
#mount -o username=administrator,password=shzx //10.28.97.38/nr /home/oracle/windir/


# start here 

PATH=$PATH:/usr/bin:/bin:/usr/local/bin
WIN_IP=10.28.97.38
WIN_DIR=nr
WIN_USER=administrator
WIN_PASSWORD=shzx
#echo $WIN_PATH

WIN_PATH=//${WIN_IP}/${WIN_DIR}
MOUNT_PATH=/home/oracle/orcltemp

LOGFILE=/home/oracle/.mountnr.log

# if the logfile has more than 1000 lines, then clean it up.
COUNT=$(wc -l ${LOGFILE} | awk '{print $1}')
if [ $COUNT -gt 500 ]; then
    echo "" > ${LOGFILE}
fi

# already mounted ?
COUNT=0
FLAG=0
COUNT=$(mount | grep ${MOUNT_PATH} | wc -l)
if [ ${COUNT} -ge 1 ]; then
    #echo "$(date +%F-%T)  : ${WIN_PATH} already mounted on ${MOUNT_PATH}..." >> ${LOGFILE}
    FLAG=1
    #exit 1
fi

# test the win host is up, exit when not, timeout is 3 secends
ping -w 3  ${WIN_IP}
if [ $? -ne 0 ]; then
    if [ ${FLAG} -eq 1 ]; then
        umount ${MOUNT_PATH}
        echo "$(date +%F-%T)  : ${WIN_PATH} already mounted on ${MOUNT_PATH}...but the host is down...umount and will try later..." >> ${LOGFILE}
        exit 1
    fi
    echo "$(date +%F-%T)  : the host ${WIN_IP} is not up...will try later" >> ${LOGFILE}
    exit 1
fi
echo "$(date +%F-%T)  : the host ${WIN_IP} is up..." >> ${LOGFILE}

# the host is up and already mounted , then abort...
if [ ${FLAG} -eq 1 ]; then
    echo "$(date +%F-%T)  : ${WIN_PATH} already mounted on ${MOUNT_PATH}...will do nothing" >> ${LOGFILE}
    exit 1
fi

# test if the win host has  dir shared, exit when not 
smbclient ${WIN_PATH} ${WIN_PASSWORD} --user=administrator -c "list" | grep -c "${WIN_DIR}"
if [ $? -ne 0 ]; then
    echo "$(date +%F-%T)  : the host ${WIN_IP} has no directory shared...will try later" >> ${LOGFILE}
    exit 1
fi
echo "$(date +%F-%T)  : the path ${WIN_PATH} will be mounted..." >> ${LOGFILE}

# mount the win host shared directory to /home/oracle/orcltemp
mount -o username=${WIN_USER},password=${WIN_PASSWORD} ${WIN_PATH} ${MOUNT_PATH}
echo "$(date +%F-%T)  : mount ${WIN_PATH} ${MOUNT_PATH}"  >> ${LOGFILE}

# end  here 
