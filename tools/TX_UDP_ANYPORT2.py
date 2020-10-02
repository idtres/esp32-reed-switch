import socket
socket.getaddrinfo('localhost', 41235)

UDP_IP = "127.0.0.1"
UDP_PORT = 41235


puerto = int(input("Puerto al cual eniviar? ( 0 = 41235 ) "))
if puerto == 0:
    UDP_PORT = 41235
else:
    UDP_PORT = puerto

IPDestino = input(str("IP a enviar? (no admite brodcast) "))




UDP_IP = str(IPDestino)

print("UDP target IP:", UDP_IP)
print("UDP target port:", UDP_PORT)

mensaje = " "

while mensaje != "":
    
    mensaje = input("mensaje a enviar ?  ")
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
    #sock.sendto(bytes(mensaje, "utf-8"), (UDP_IP, UDP_PORT))
    sock.sendto(bytes(mensaje, "utf-8"), (UDP_IP, UDP_PORT))
    print("enviando...")

print("end")
