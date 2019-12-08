import serial

ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=5)
ser.flushInput()

while True:
    if ser.in_waiting > 0:
	
	A = ser.readline().split()
	print(A)
	for i in A:
		if(A[0] == '1.00' and A[3] > '700'):
			#import espeak module
			#from subprocess import call
			#open text file for node one
			#file = open('Node1.txt', 'r')
			#text = file.read().strip()
			#file.close
			#convert text to speech
			#speech = text
			#call epseak
			#call(["espeak",speech])
			#break
			#import Twilio module 
			from twilio.rest import Client
			#Account ID and Authentication Token for messages
			account_sid = 'ACad53d98d696e5886f1da70dd1c3bee4b'
    			auth_token = 'd121a1a4c6485e5aa647347b4c7737b7'
    			client = Client(account_sid, auth_token)
			#Your telephone number 
    			tel = '+12024928238'
    			twil = '12029159181'
			#Create out going SMS message
    			client.messages.create(
  				to=tel,
  				from_=twil,
  				body='Warning there is a possible fire in room 1066! ' + u'\U0001f680'
			)
			#Create outgoing phone call
    			call = client.calls.create(
				#demo phone message
        			url='http://demo.twilio.com/docs/voice.xml',
        			to=tel,
        			from_=twil

   			)				
    			print(call.sid)
		elif(A[0] == '1.00' and A[4] > '550'):
			from subprocess import call
			file = open('Node1_Carb.txt', 'r')
			text = file.read().strip()
			file.close
			speech = text
			call(["espeak",speech])
			break
		elif(A[0] == '1.00' and A[3] > '600'):
			from subprocess import call
			file = open('Node1_smoke.txt', 'r')
			text = file.read().strip()
			file.close
			speech = text
			call(["espeak",speech])
			break	
		elif(A[0] == '2.00' and A[3] > '500'):
			#import espeak module
			from subprocess import call
			#open text file for Node 2
                        file = open('Node2_Smoke.txt', 'r')
                        text = file.read().strip()
                        file.close
                        speech = text
			#call epseak
                        call(["espeak",speech])
                        break
		elif(A[0] == '2.00' and A[4] > '350'):
			from subprocess import call
                        file = open('Node2_Carb.txt', 'r')
                        text = file.read().strip()
                        file.close
                        speech = text
                        call(["espeak",speech])
                        break
 		elif(A[0] == '2.00' and A[2] > '600'):
			from subprocess import call
                        file = open('Node2_Temp.txt', 'r')
                        text = file.read().strip()
                        file.close
                        speech = text
                        call(["espeak",speech])
                        break
		elif(A[0] == '3.00' and A[3] > '450'):
			from subprocess import call
                        file = open('Node3_Smoke.txt', 'r')
                        text = file.read().strip()
                        file.close
                        speech = text
                        call(["espeak",speech])
                        break
		elif(A[0] == '3.00' and A[4] > '300'):
			from subprocess import call
                        file = open('Node3_Carb.txt', 'r')
                        text = file.read().strip()
                        file.close
                        speech = text
                        call(["espeak",speech])
                        break
		elif(A[0] == '3.00' and A[2] > '600'):
			from subprocess import call
                        file = open('Node3_Temp.txt', 'r')
                        text = file.read().strip()
                        file.close
                        speech = text
                        call(["espeak",speech])
                        break




