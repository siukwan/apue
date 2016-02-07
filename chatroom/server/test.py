#-*-coding=UTF-8-*-
import select
import socket
import sys
import signal
import cPickle
import struct
import argparse

SERVER_HOST = 'localhost'
CHAT_SERVER_NAME = 'server'

#通用的工具函数
def send(channel , *args):
	buffer = cPickle.dumps(args)
	value = socket.htonl(len(buffer))
	size = struct.pack("L",value)
	channel.send(size)
	channel.send(buffer)

def receive(channel):
	size = struct.calcsize("L")
	size = channel.recv(size)
	try:
		size = socket.ntohl(struct.unpack("L",size)[0])
	except struct.error,e:
		return ''
	buf = ""
	while len(buf)<size:
		buf = channel.recv(size - len(buf))
	return cPickle.loads(buf)[0]


#定义聊天服务器类
class ChatServer(object):
	"""A example chat server using select """
	def __init__ (self, port, backlog=5): #backlog:用于设定服务器监听的连接队列的最大数量
		self.clients = 0
		self.clientmap = {}
		self.outputs = [] #list output sockets
		self.server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
		self.server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR,-1)
		self.server.bind((SERVER_HOST,port))
		print 'Server listening to port: %s ...'%port
		self.server.listen(backlog)
		#Catch keyboard interrupts，当用户输入终端中断字符（ctrl＋c）
		signal.signal(signal.SIGINT, self.sighandler)

	def sighandler(self,signum,frame):
		"""Clean up client outputs"""
		#Close the server
		print 'Shutting down server...'
	#Close existing client sockets
		for output in self.outputs:
			output.close()
		self.server.close()
	
	def get_client_name(self,client):
		"""Return the name of the client"""
		info = self.clientmap[client]
		host, name = info[0][0],info[1]
		return '@'.join((name,host))

	#执行方法
	def run(self):
		inputs = [self.server, sys.stdin]
		self.outputs = []
		running =True;
		while running:
			try:
				#select.selelct()得到三个列表：可读套接字，可写套接字，异常套接字;服务器只关心可读套接字
				readable,writeable,exceptional = select.select(inputs,self.outputs,[])
			except select.error, e:
				break
			for sock in readable:
				#如果可读套接字事服务器本身，证明又一个新客户端连到服务器上了
				if sock == self.server:
					#handle the server socket
					client, address = self.server.accept()
					print "Chat server:got connection %d from %s" %(client.fileno(),address)

					#Read the login name
					cname = receive(client).split('NAME: ')[1]
	
					#Compute client name and send back
					self.clients +=1
					send(client, 'CLIENT: ' + str(address[0]))
					inputs.append(client)
					self.clientmap[client] = (address,cname)
					#Send joining information to other clients
					msg = "\n(Connected: New client (%d) from %s)" % (self.clients,self.get_client_name(client))

					for output in self.outputs:
						send(output,msg)
					self.outputs.append(client)

				#如果是标准输入
				elif sock == sys.stdin:
					#handle standard input
					junk = sys.stdin.readline()
					running = False

				#处理其它套接字	
				else:
					#handle all other sockets
					try:
						data = receive(sock)
						if data:
							#Send as new client's message ...
							msg = '\n#[' + self.get_client_name(sock)+ ']>>' +data
							#Send data to all except ourself
							for output in self.outputs:
								if output !=sock:
										send(output,msg)
						else:
							print "Chat server: %d hung up" % sock.fileno()
							self.clients -= 1
							sock.close()
							inputs.remove(sock)
							self.outputs.remove(sock)

							#Sending client leaving information to others
							msg = "\n(Now hung up: Client from %s)" % self.get_client_name(sock)
							for output in self.outputs:
								send(output,msg)
					except socket.error, e:
						#Remove
						inputs.remove(sock)
						self.outputs.remove(sock)
		self.server.close()
				



class ChatClient(object):
	"""A command line chat client using select"""
	
	def __init__(self, name, port , host = SERVER_HOST):
		self.name = name
		self.connected = False
		self.host = host
		self.port = port
		
		#Initial prompt
		self.prompt='['+'@'.join((name,socket.gethostname().split('.')[0])) + ']> '

		#Connect to server at port
		try:
			self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
			self.sock.connect((host,self.port))
			print "Now connected to chat server@ port %d" % self.port
			self.connected = True
			#Send my name...
			send(self.sock, 'NAME: '+self.name)
			data = receive(self.sock)

			#Contains client address, set it
			addr = data.split('CLIENT: ')[1]
			self.prompt = '['+'@'.join((self.name,addr))+']> '
		except socket.error, e:
			print "Failed to connect to chat server @ port %d" %self.port
			sys.exit()
			
	def run(self):
		"""Chat client main loop"""
		while self.connected:
			try:
				sys.stdout.write(self.prompt)
				sys.stdout.flush()#刷新缓冲区

				#Wait for input from stdin and socket
				readable,writeable,exceptional = select.select([0,self.sock],[],[])
				for sock in readable:
					if sock == 0:
						data = sys.stdin.readline().strip()
						if data: send(self.sock, data)
					elif sock == self.sock:
						data = receive(self.sock)
						if not data:
							print 'Client shutting down.'
							self.connected = False
							break
						else:
							sys.stdout.write(data + '\n')
							sys.stdout.flush()

			except KeyboardInterrupt:
				print " Client interrupted."
				self.sock.close()
				break;

if __name__ == "__main__":
	parser = argparse.ArgumentParser(description = 'Socket Server Example with Select')
	parser.add_argument('--name',action="store",dest="name",required=True)
	parser.add_argument('--port',action="store",dest="port",type = int,required=True)
	given_args = parser.parse_args()
	port = given_args.port
	name = given_args.name
	if name == CHAT_SERVER_NAME:
		server = ChatServer(port)
		server.run()
	else:
		client = ChatClient(name=name,port=port)
		client.run()



