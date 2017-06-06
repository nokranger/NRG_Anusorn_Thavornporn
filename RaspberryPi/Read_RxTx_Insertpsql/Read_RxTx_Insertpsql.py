#import sqlite3 as lite
import sys

import serial
import time
import RPi.GPIO as GPIO

#from picamera import PiCamera
from time import sleep
import psycopg2

ser = serial.Serial('/dev/serial0')
ser.close()
ser.open()
i=0
conn = psycopg2.connect("dbname='d9te6ilabpm2pg' user='lopiflzjhklibp' host='ec2-184-73-199-72.compute-1.amazonaws.com' password='a9926e0e7f54cc09ef89f7e406e18ab86337b84e6a981702714d69b0d4c97408'")

try:
        cur = conn.cursor()
        print('Post DB Success')
except:
        print('Error')
while True:
        try:
                readByte = ser.readline()
                date_time = time.strftime("%H:%M:%S") 
               	print( date_time,"Receive Data : ",float(readByte) )
               	time.sleep(5)
                try:
                        cur = conn.cursor()
                        sql_insert = """INSERT INTO "iot_KNP_23" (time,temp,hum) VALUES ('00:00:00',39,34)"""
                        cur.execute(sql_insert)
                        conn.commit();
                        print('Send Data Success')
                except:
                        print('Send Error');
        except:
                pass

        
