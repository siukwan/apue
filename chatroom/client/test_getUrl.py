#-*-coding=UTF-8-*-
import httplib
import socket
import select
import cPickle
import struct
import sys
REMOTE_SERVER_HOST = 'www.siukwan.sinaapp.com'
REMOTE_SERVER_PATH = '/ipport.php'

def send(channel,*args):
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

class HTTPClient:
	
	def __init__(self,host):
		self.host =host

	def fetch(self,path):
		http = httplib.HTTP(self.host)

		#Prepare header
		http.putrequest("CHT",path)
		http.putheader("User-Agent",__file__)
		http.putheader("Host",self.host)
		http.putheader("Accept","*/*")
		http.endheaders()

		try:
			errcode,errmsg,headers = http.getreply()
		except Exception,e:
			print "Client failed error code:%s message:%s headers:%s" %(errcode,errmsg,headers)
		#else:
		#	print "Got homepage from %s"%self.host
		file = http.getfile()
		return file.read()

	@staticmethod       #标明为静态方法
	def getIPandPort(): #获取ip和port
		client = HTTPClient(REMOTE_SERVER_HOST)
		IPandPortStr = client.fetch(REMOTE_SERVER_PATH)
		splitPos = IPandPortStr.index(':')
		IPStr    = IPandPortStr[:splitPos]
		PortStr  = IPandPortStr[splitPos+1:]
		return IPStr,PortStr

class ChatClient(object):
	
	def __init__(self,name,port,host):
		self.name = name
		self.connected = False
		self.host = host
		self.port = port

		#Initial prompt
		self.prompt = '['+'@'.join((name,socket.gethostname().split('.')[0]))+']>'

		#Connect to server at port
		try:
			self.sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
			self.sock.connect((host,self.port))
			print "Now connected to chat server@ port %d"%self.port
			self.connected = True
			# Send my name...
			send(self.sock,'NAME: '+self.name)
			data = receive(self.sock)
			# Contains client address, set it
			addr = data.split('CLIENT: ')[1]
			self.prompt = '['+'@'.join((self.name,addr))+']> '
		except socket.error, e:
			print "Failed to connect to chat server(%s) @ port %d" %( self.host,self.port)
			sys.exit(1)
	
	def run(self):
		"""Chat client main loop"""
		while self.connected:
			try:
				sys.stdout.write(self.prompt)
				sys.stdout.flush() #刷新缓冲区
				# Wait for input from stdin and socket
				readable,writeable,exceptional = select.select([0,self.sock],[],[])
				for sock in readable:
					if sock == 0:
						data = sys.stdin.readline().strip()
						if data:send(self.sock,data)
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
				print "Client interrupted."
				self.sock.close()
				break

if __name__ == "__main__":
	serverIP,serverPort = HTTPClient.getIPandPort()
	client = ChatClient(name="siukwan",port=int(serverPort),host="192.168.0.104")
	client.run()	
