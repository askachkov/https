#include "socketstream.h"

SocketStream::SocketStream(const Socket & val):
    mSocket(val)
{

}

void SocketStream::closeSocket()
{
    mSocket.close();
}

SocketStream::int_type SocketStream::underflow(){
    int bytesRead = 0;
    try{
        bytesRead = mSocket.read(reinterpret_cast<uint8_t*>( mInputBuffer ),BUFFER_SIZE-1);
        if( bytesRead <= 0 ){
            return traits_type::eof();
        }
    }catch(...){
        std::cerr<<"Unable to read data"<<std::endl;
        return traits_type::eof();
    }
    setg(mInputBuffer,mInputBuffer,mInputBuffer+bytesRead);
    return traits_type::to_int_type(mInputBuffer[0]);
}

SocketStream::int_type SocketStream::overflow(SocketStream::int_type c){
    int bytesWritten = 0;
    try{
        if(pptr() - pbase() > 0){
            uint32_t size = static_cast<uint32_t>(pptr() - pbase());
            bytesWritten = mSocket.write(reinterpret_cast<uint8_t*>(pbase()),size);
            if( bytesWritten <= 0 )  return traits_type::not_eof(c);
        }
    }catch(...){
        std::cerr<<"Unable to write data"<<std::endl;
        return traits_type::eof();
    }
    mOutputBuffer[0] = traits_type::to_char_type(c);
    setp(mOutputBuffer,mOutputBuffer+BUFFER_SIZE);
    return traits_type::not_eof(c);
}

ServerSocketStream::ServerSocketStream(uint16_t portNo)
{
    mSocket.setPort(portNo);
}

int ServerSocketStream::bind()
{
    return mSocket.bind();
}

int ServerSocketStream::listen(int n)
{
    return mSocket.listen(n);
}

SocketStream ServerSocketStream::accept()
{
    return SocketStream(mSocket.accept());
}

void ServerSocketStream::closeSocket()
{
    mSocket.close();
}

int SocketStream::connect(const char *host, uint16_t portNo)
{
    return mSocket.connect(host, portNo);
}
