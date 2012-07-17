#!/bin/sh
#chkconfig: 2345 99 06
#description: oracle dabase deamons
#/etc/init.d/oracle11g
 
export ORACLE_BASE=/oradir/oracle
export ORACLE_HOME=$ORACLE_BASE/product/11.2.0/db_1
export ORACLE_SID=orcl
export ORACLE_OWNER=oracle
export ORACLE_LOCK_FILE=/var/lock/subsys/oracle11g
export PATH=$PATH:$ORACLE_HOME/bin
 
case "$1" in
    'start')
        ORACLE_PROCESS=`ps aux | grep ora_ | grep -v grep |wc -l`
        if [ $ORACLE_PROCESS -ne 0 ];then
                echo "ERROR: Oracle already running."
                sleep 1
       else
            echo -n "Starting Oracle: "
            su - $ORACLE_OWNER -c $ORACLE_HOME/bin/dbstart
            touch $ORACLE_LOCK_FILE
            echo -n "Success"
            sleep 2
        fi
        ORACLE_LISTENER=`ps -e |grep tnslsnr |wc -l`
        if [ $ORACLE_LISTENER -ne 0 ];
            then
                echo "ERROR: Listener already running."
                sleep 1
            else
                echo -n "Starting Listener: "
                su - $ORACLE_OWNER -c "$ORACLE_HOME/bin/lsnrctl start"
                echo -n "Success"
                sleep 2
        fi
        ORACLE_EM=`ps -ef | grep dbconsole | grep -v dbconsole | wc -l`
        if [ $ORACLE_EM -ne 0 ]; then
                echo -n "ERROR: em dbconsole already running."
                sleep 1
        else
                echo -n "Starting em dbconsole: "
                su - $ORACLE_OWNER -c "$ORACLE_HOME/bin/emctl start dbconsole"
                echo -n "Success"
                sleep 2
        echo
        ;;
 
    'stop')
        ORACLE_LISTENER=`ps -e |grep tnslsnr |wc -l`
        if [ $ORACLE_LISTENER -ne 0 ];  then
            echo -n "Shutting down Listener: "
            su - $ORACLE_OWNER -c "$ORACLE_HOME/bin/lsnrctl stop"
            echo -n "Success"
            sleep 2
        else
            echo "ERROR: Listener already shutdown."
            sleep 1
        fi
        ORACLE_PROCESS=`ps aux | grep ora_ | grep -v grep |wc -l`
        if [ $ORACLE_PROCESS -ne 0 ];   then
            echo -n "Shutting down Oracle: "
            su - $ORACLE_OWNER -c $ORACLE_HOME/bin/dbshut
            rm -f $ORACLE_LOCK_FILE
            echo -n "Success"
            sleep 2
        else
            echo "ERROR: Oracle already shutdown."
            sleep 1
        fi
        echo
        ;;
 
    'restart')
        echo "Restarting Oracle: "
        $0 stop
        $0 start
        echo
        ;;
 
    *)
        echo "Usage: oracle { start | stop | restart }"
        exit 1
 
esac
exit 0
