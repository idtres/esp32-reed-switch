import socket
import datetime


#UDP_PORT = int(input("puerto a escuchar? "))
 
UDP_IP = "127.0.0.1"
UDP_PORT = 41235




puerto = int(input("Puerto a escuchar ( 0 para 41235) "))
if puerto == 0:
    UDP_PORT = 41235
else:
    UDP_PORT = puerto

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind(('', UDP_PORT))

print("Escuchando UDP en puerto " + str(UDP_PORT))



while True:
    data, addr = sock.recvfrom(4096) #
    
    date = str(datetime.datetime.now())
    output = str(data.decode())
    output = date + "  " + output
    print(output)

    #print(output.decode())1
