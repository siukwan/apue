#-*-coding=UTF-8-*-
import select
import socket
import sys
import signal
import cPickle
import struct
import argparse

SERVER_HOST = ''
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
	print 'size大小为：'+str(size)
	size = channel.recv(size)
	print 'size内容为：'+size
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
					receiveData = receive(client)
					print "receive data:"+receiveData
					if receiveData =='':
						cname = 'unknown'
					else:
						cname = receiveData.split('NAME: ')[1]
	
					#Compute client name and send back
					self.clients +=1
					sendData = 'CLIENT: '+str(address[0])
					send(client, sendData)
					print '发送数据为：'+sendData
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
if __name__ == "__main__":
	port = 8800
	server = ChatServer(port)
	server.run()



