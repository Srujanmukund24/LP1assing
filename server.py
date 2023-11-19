from xmlrpc.server import SimpleXMLRPCServer

def factorial(number):
    fact=1
    if(number<0):
        return 0
    for i in range(1,number+1):
        fact=fact*i
    return fact 
def square(number):
    return number*number

port=8000
server=SimpleXMLRPCServer(("localhost",port),logRequests=True)
server.register_function(factorial,'factorial_rpc')
server.register_function(square,'square_rpc')

try:
    print("staring the server at ",port)
    server.serve_forever()
except:
    print("server cloced")    