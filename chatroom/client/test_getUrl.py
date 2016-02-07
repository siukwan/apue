#-*-coding=UTF-8-*-
import httplib

REMOTE_SERVER_HOST = 'www.siukwan.sinaapp.com'
REMOTE_SERVER_PATH = '/ipport.php'

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
		PortStr  = IPandPortStr[splitPos:]
		return IPStr,PortStr
if __name__ == "__main__":
	serverIP,serverPort = HTTPClient.getIPandPort()	
	print "IP为："+serverIP
	print "Port为："+serverPort 
